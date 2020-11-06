#include <QDebug>
#include <QWindow>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStandardPaths>
#include "nrtc_engine.h"
#include "videowidget.h"
#include "mainwindow.h"

namespace smaple_nertc {

using namespace nertc;
class NRTCEngineEvent : public IRtcEngineEventHandlerEx
{
    NRTCEngine& m_engine;
public:
    NRTCEngineEvent(NRTCEngine & engine)
        :m_engine(engine)
    {}


    virtual void onUserVideoStop(nertc::uid_t uid) override{
        emit m_engine.videoStopped(uid);
        m_engine.stopRemoteVideo(uid);
    }

    virtual void onUserVideoStart(nertc::uid_t uid, NERtcVideoProfileType max_profile) override {
        emit m_engine.videoStart(uid, (int) max_profile);
        m_engine.startRemoteVideo(uid);
    }

    virtual void onUserAudioStop(nertc::uid_t uid) override {
        m_engine.stopRemoteAudio(uid);
    }

    virtual void onUserAudioStart(nertc::uid_t uid) override {
        m_engine.startRemoteAudio(uid);
    }

    virtual void onJoinChannel(channel_id_t cid, nertc::uid_t uid, NERtcErrorCode result, uint64_t elapsed) override{
        if (!result){
            emit m_engine.joinedChannelSuccess();

        }else{
            qDebug("[INFO] uid %d joining channel %d unsuccessfully, ERROR CODE: %d", uid, cid, result);
        }
    }

    virtual void onUserJoined(nertc::uid_t uid, const char * user_name) override{
        qDebug("[INFO] Remote user %lld joined channel successuflly.", uid);
        emit m_engine.userJoined((quint64)uid);
    }

    virtual void onUserLeft(nertc::uid_t uid, NERtcSessionLeaveReason reason) override{
        qDebug("[INFO] Remote user %lld left channel.", uid);
        emit m_engine.userLeft((quint64)uid);
    }

};


NRTCEngine::NRTCEngine(QObject *parent) : QObject(parent) ,
    rtc_engine_handler_(new NRTCEngineEvent(*this))
{
    rtc_engine_ = nullptr;
    audio_device_manager = nullptr;
    video_device_manager = nullptr;
    connection_state_ = kNERtcConnectionStateDisconnected;
    cur_my_uid_ = 0;
    app_key_ = APP_KEY;
    current_video_profile = kNERtcVideoProfileStandard;

    auto appDataDir = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    auto rtcLog = appDataDir + "/NeRTC";
    auto byteLogDir = rtcLog.toUtf8();

    //init engine
    bool ret = Init(app_key_.toUtf8().data(), byteLogDir.data(), 10240);
    if (false == ret)
    {
        qDebug("[ERROR] Failed to initialize NERtc engine! NERtc SDK can't work!");
    }

}

NRTCEngine::~NRTCEngine(){
    Uninit();
}

bool NRTCEngine::Init(const char *app_key, const char *log_dir_path, uint32_t log_file_max_size_KBytes){
    rtc_engine_ = static_cast<IRtcEngineEx *>(createNERtcEngine());
    rtc_engine_context_ = {0};
    rtc_engine_context_.app_key = app_key;
    rtc_engine_context_.log_dir_path = log_dir_path;
    rtc_engine_context_.log_level = kNERtcLogLevelInfo;
    rtc_engine_context_.log_file_max_size_KBytes = log_file_max_size_KBytes;
    rtc_engine_context_.event_handler = rtc_engine_handler_.get();


    auto ret = rtc_engine_->initialize(rtc_engine_context_);
    //Init NERTC engine
    if (kNERtcNoError != ret){
        qDebug("ERROR: Failed to initialize NERtc Engine\n");
        return false;
    }

    //Init audio/video device manager
    ret = rtc_engine_->queryInterface(kNERtcIIDAudioDeviceManager, (void**)&audio_device_manager);
    ret = rtc_engine_->queryInterface(kNERtcIIDVideoDeviceManager, (void**)&video_device_manager);

    return true;
}

void NRTCEngine::setLocalVideoProfileType(nertc::NERtcVideoProfileType max_profile){
    if (rtc_engine_){
        NERtcVideoConfig video_config_;
        qDebug("max_profile: %d", max_profile);
        video_config_.max_profile = max_profile;
        video_config_.crop_mode_ = kNERtcVideoCropModeDefault;
        int ret = rtc_engine_->setVideoConfig(video_config_);
        if(ret)
            qDebug("[ERROR] Cannot set video config, ERROR CODE: %d", ret);
        else{
            QString profile_str;
            switch(max_profile){
            case 0:
                profile_str = "160x90/120, 15fps";
                break;
            case 1:
                profile_str = "320x180/240, 15fps";
                break;
            case 2:
                profile_str = "640x360/480, 30fps";
                break;
            case 3:
                profile_str = "1280x720, 30fps";
                break;
            case 4:
                profile_str = "1920x1080, 30fps";
                break;
            case 5:
                profile_str = "None";
                break;
            default:
                profile_str = "640x360/480, 30fps";

            }
            qDebug("[INFO] set video config: %s", profile_str.toUtf8().data());
        }
    }
}

int NRTCEngine::joinChannel(const QString& token, const QString& roomid, const QString& uid,
                            bool autoStartVideo, bool autoStartAudio, int video_resolution){
    int ret = kNERtcNoError;

    //set video/audio auto starting config
    auto_start_audio_ = autoStartAudio;
    auto_start_video_ = autoStartVideo;
    setLocalVideoProfileType((NERtcVideoProfileType)video_resolution);

//    NRTCParameter param;
//    param.auto_start_local_audio = autoStartAudio;
//    param.auto_start_local_video = autoStartVideo;
//    setParameter(param);

    //Join channel
    cur_my_uid_ = uid.toULongLong();
    ret = rtc_engine_->joinChannel(token.toUtf8().data(), roomid.toUtf8().data(), cur_my_uid_);

    if(ret == kNERtcNoError){
        emit joiningChannel();
        qDebug() << "[INFO] join channel successfully!";
    }else{
        qDebug("[ERROR] can't join channel, ERROR CODE: %d", ret);
    }
    qDebug("[INFO] current connection state: %d", rtc_engine_->getConnectionState());
    return ret;
}

int NRTCEngine::leaveChannel(){
    int ret = kNERtcNoError;
    qDebug("[INFO] current connection state: %d", rtc_engine_->getConnectionState());
    if (rtc_engine_){
        ret = rtc_engine_->enableLocalAudio(false);
        ret = rtc_engine_->enableLocalVideo(false);
        ret = rtc_engine_->leaveChannel();
        if (kNERtcNoError == ret){
            emit leavingChannel();
        }else{
            qDebug("[ERROR] Can't leave channel, ERROR CODE: %d", ret);
        }
    }
    return ret;
}

void NRTCEngine::setCurrentVideoProfile(unsigned int index) {
    current_video_profile = (NERtcVideoProfileType) index;
}

int NRTCEngine::muteLocalAudioStream(bool mute){
    return rtc_engine_->muteLocalAudioStream(mute);
}

int NRTCEngine::enableVideo(bool enabled){
    return rtc_engine_->enableLocalVideo(enabled);
}

QVariantMap NRTCEngine::getRecordingDeviceList(){
    QVariantMap res;
    if(audio_device_manager == nullptr){
        qDebug() << "[WARNING] Please init the audio device manager!";
        return res;
    }
    IDeviceCollection * recordingDeviceList = audio_device_manager->enumerateRecordDevices();

    QVariantList names;
    QVariantList ids;
    int count = recordingDeviceList->getCount();
    for(int i = 0; i < count; ++i){
        char ID[kNERtcMaxDeviceIDLength];
        char name[kNERtcMaxDeviceNameLength];
        memset(ID, 0, sizeof(ID));
        memset(name, 0, sizeof(name));
        recordingDeviceList->getDevice(i, name, ID);
        names.push_back(QString(name));
        ids.push_back(QString(ID));
    }
    res.insert("name", names);
    res.insert("guid", ids);
    res.insert("length", names.length());
    recordingDeviceList->destroy();
    return res;
}

QVariantMap NRTCEngine::getPlayoutDeviceList(){
    QVariantMap res;
    if(audio_device_manager == nullptr){
        qDebug() << "[WARNING] Please init the audio device manager!";
        return res;
    }
    IDeviceCollection * playoutDeviceList = audio_device_manager->enumeratePlayoutDevices();

    QVariantList names;
    QVariantList ids;
    int count = playoutDeviceList->getCount();
    for(int i = 0; i < count; ++i){
        char ID[kNERtcMaxDeviceIDLength];
        char name[kNERtcMaxDeviceNameLength];
        memset(ID, 0, sizeof(ID));
        memset(name, 0, sizeof(name));
        playoutDeviceList->getDevice(i, name, ID);
        names.push_back(QString(name));
        ids.push_back(QString(ID));
    }
    res.insert("name", names);
    res.insert("guid", ids);
    res.insert("length", names.length());
    playoutDeviceList->destroy();
    return res;
}

QVariantMap NRTCEngine::getVideoDeviceList(){
    QVariantMap res;
    if(video_device_manager == nullptr){
        qDebug() << "[WARNING] Please init the video device manager!";
        return res;
    }
    IDeviceCollection * videoDeviceList = video_device_manager->enumerateCaptureDevices();

    QVariantList names;
    QVariantList ids;
    int count = videoDeviceList->getCount();
    for(int i = 0; i < count; ++i){
        char ID[kNERtcMaxDeviceIDLength];
        char name[kNERtcMaxDeviceNameLength];
        memset(ID, 0, sizeof(ID));
        memset(name, 0, sizeof(name));
        videoDeviceList->getDevice(i, name, ID);
        names.push_back(QString(name));
        ids.push_back(QString(ID));
    }
    res.insert("name", names);
    res.insert("guid", ids);
    res.insert("length", names.length());
    videoDeviceList->destroy();
    return res;
}

int NRTCEngine::setRecordingDevice(const QString &guid){
    if(guid.length() < 1){
        qDebug() << "[ERROR] Can not set recording device, your guid is empty!";
        return -1;
    }
    int ret = audio_device_manager->setRecordDevice(guid.toUtf8().data());
    if(ret){
        qDebug("[ERROR] Can not set recording device, ERROR CODE: %d", ret);
    }
    return ret;
}

int NRTCEngine::setPlayoutDevice(const QString &guid){
    if(guid.length() < 1){
        qDebug() << "[ERROR] Can not set playout device, your guid is empty!";
        return -1;
    }
    int ret = audio_device_manager->setPlayoutDevice(guid.toUtf8().data());
    if(ret){
        qDebug("[ERROR] Can not set playout device, ERROR CODE: %d", ret);
    }
    return ret;
}

int NRTCEngine::setVideoDevice(const QString &guid){
    if(guid.length() < 1){
        qDebug() << "[ERROR] Can not set video device, your guid is empty!";
        return -1;
    }
    int ret = video_device_manager->setDevice(guid.toUtf8().data());
    if(ret){
        qDebug("[ERROR] Can not set video device, ERROR CODE: %d", ret);
    }
    return ret;
}

int NRTCEngine::getRecordingDeviceVolume(){
    unsigned int volume = 0;
    int ret = audio_device_manager->getRecordDeviceVolume(&volume);
    if(ret){
        qDebug("[ERROR] Can not get recording device volume ERROR CODE: %d", ret);
    }else{
        qDebug("[INFO] Get recording device volume: %d", volume);
    }

    return volume;
}

int NRTCEngine::getPalyoutDeviceVolume(){
    unsigned int volume = 0;
    int ret = audio_device_manager->getPlayoutDeviceVolume(&volume);
    if(ret){
        qDebug("[ERROR] Can not get playout device volume ERROR CODE: %d", ret);
    }else{
        qDebug("[INFO] Get recording device volume: %d", volume);
    }

    return volume;
}

int NRTCEngine::setRecordingDeviceVolume(int volume){
    int ret = audio_device_manager->setRecordDeviceVolume(volume);
    if(ret){
        qDebug("[ERROR] Can not set recording device volume ERROR CODE: %d", ret);
    }else{
        qDebug("[INFO] set recording device volume : %d", volume);
    }
    return ret;
}

int NRTCEngine::setPalyoutDeviceVolume(int volume){
    int ret = audio_device_manager->setPlayoutDeviceVolume(volume);
    if(ret){
        qDebug("[ERROR] Can not set playout device volume ERROR CODE: %d", ret);
    }else{
        qDebug("[INFO] set playout device volume : %d", volume);
    }
    return ret;
}



int NRTCEngine::setupLocalVideo(void* hwnd){
   
    NERtcVideoCanvas canvas;
    canvas.cb = nullptr;
    canvas.user_data = nullptr;
    canvas.window = hwnd;
    canvas.scaling_mode = kNERtcVideoScaleFit;
    int ret = rtc_engine_->setupLocalVideoCanvas(&canvas);
    if(ret){
        qDebug("ERROR: Can not setup local video canvas! ERROR CODE: %d", ret);
    }
    return ret;
}

int NRTCEngine::setupRemoteVideo(unsigned int uid, void* hwnd){
    NERtcVideoCanvas canvas;
    canvas.cb = nullptr;
    canvas.user_data = nullptr;
    canvas.window = hwnd;
    canvas.scaling_mode = kNERtcVideoScaleFit;
    int ret = rtc_engine_->setupRemoteVideoCanvas(uid, &canvas);
    if(ret){
        qDebug("[ERROR] Can not setup remote video canvas! ERROR CODE: %d", ret);
    }
    int ret_temp = rtc_engine_->subscribeRemoteVideoStream(uid, kNERtcRemoteVideoStreamTypeHigh, true);
    if (ret_temp) {
        qDebug("[ERROR] can not subscribe remote video stream! ERROR CODE: %d", ret_temp);
    }
    ret_temp = rtc_engine_->subscribeRemoteAudioStream(uid, true); 
    if (ret_temp) {
        qDebug("[ERROR] can not subscribe remote audio stream! ERROR CODE: %d", ret_temp);
    }
    return ret;
}

void NRTCEngine::Uninit(){
    if (rtc_engine_){
        //Sleep(500);//等待底层异步关闭
        //同步退出
        rtc_engine_->release(true);
        destroyNERtcEngine((void *&)rtc_engine_);
        rtc_engine_ = nullptr;
    }
}

void NRTCEngine::setParameter(const NRTCParameter &rtc_parameter){
    rtc_parameter_ = rtc_parameter;
    QJsonObject values;
    //values[kNERtcKeySetP2PMode] = rtc_parameter_.p2p_mode_;
    values[kNERtcKeyAudioProcessingAECEnable] = rtc_parameter_.audio_aec_enable;
    values[kNERtcKeyAudioProcessingAGCEnable] = rtc_parameter_.audio_agc_enable;
    values[kNERtcKeyAudioProcessingNSEnable] = rtc_parameter_.audio_ns_enable;
    values[kNERtcKeyAudioProcessingExternalAudioMixEnable] = rtc_parameter_.audio_external_mix_enable;
    values[kNERtcKeyAudioProcessingEarphone] = rtc_parameter_.audio_earphone;
    values[kNERtcKeyRecordHostEnabled] = rtc_parameter_.record_host_enabled;
    values[kNERtcKeyRecordAudioEnabled] = rtc_parameter_.record_audio_enabled;
    values[kNERtcKeyRecordVideoEnabled] = rtc_parameter_.record_video_enabled;
    values[kNERtcKeyRecordType] = rtc_parameter_.record_type;
//     values[kNERtcKeyAutoStartLocalAudio] = rtc_parameter_.auto_start_local_audio;
//     values[kNERtcKeyAutoStartLocalVideo] = rtc_parameter_.auto_start_local_video;
    //rtc_engine_->enableLocalAudio(rtc_parameter_.auto_start_local_audio);
    //rtc_engine_->enableLocalVideo(rtc_parameter_.auto_start_local_video);
    values[kNERtcKeyAutoSubscribeAudio] = rtc_parameter_.auto_subscribe_audio;
    //values[kNERtcKeyAutoSubscribeVideo] = rtc_parameter_.auto_subscribe_video;
    values[kNERtcKeyPublishSelfStreamEnabled] = rtc_parameter_.publish_self_stream_enabled;
    values[kNERtcKeyLogLevel] = rtc_parameter_.log_level;
    //values[kNERtcKeyVideoCaptureObserverEnabled] = rtc_parameter_.video_capture_observer_enabled;
    QString parameters = QString(QJsonDocument(values).toJson());
    int ret = rtc_engine_->setParameters(parameters.toUtf8().data());
    if(ret){
        qDebug("[ERROR] Cannot set parameters ERROR CODE: %d", ret);
    }
}

void NRTCEngine::startRemoteVideo(nertc::uid_t uid) {
    rtc_engine_->subscribeRemoteVideoStream(uid, kNERtcRemoteVideoStreamTypeHigh, true);
}

void NRTCEngine::stopRemoteVideo(nertc::uid_t uid) {
    rtc_engine_->subscribeRemoteVideoStream(uid, kNERtcRemoteVideoStreamTypeHigh, false);
}

void NRTCEngine::startRemoteAudio(nertc::uid_t uid) {
    rtc_engine_->subscribeRemoteAudioStream(uid, true);
}

void NRTCEngine::stopRemoteAudio(nertc::uid_t uid) {
    rtc_engine_->subscribeRemoteAudioStream(uid, false);
}

void NRTCEngine::autoStartVideo() {
    rtc_engine_->enableLocalVideo(auto_start_video_);
}

void NRTCEngine::autoStartAudio() {
    rtc_engine_->enableLocalAudio(auto_start_audio_);
}

}

