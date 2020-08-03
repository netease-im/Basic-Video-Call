//  Created by NetEase on 8/3/2020.
//  Copyright (c) 2014-2020 NetEase, Inc. All rights reserved.
//

#include <QDebug>
#include <QMessageBox>
#include <QWindow>
#include <QRandomGenerator>
#include <QStandardPaths>
#include <QMutex>
#include "nrtc_engine.h"
#include "libyuv.h"

using namespace nertc;

typedef struct {
    std::weak_ptr<VideoRenderImpl> weak;
    QMutex mutex;
} RENDER_PARAMS;

class NRTCEngineEvent : public IRtcEngineEventHandlerEx
{
    NRTCEngine& m_engine;
public:
    NRTCEngineEvent(NRTCEngine& engine)
        :m_engine(engine), remote_user_id(0)
    {}

    virtual void onJoinChannel(channel_id_t cid, nertc::uid_t uid, NERtcErrorCode result, uint64_t elapsed) override {
        if (!result) {
            emit m_engine.joinedChannelSuccess();
            qDebug() << "[INFO] joined channel successfully!";
        }
        else {
            qDebug("[ERROR] uid %d joining channel %d unsuccessfully, ERROR CODE: %d", uid, cid, result);
        }
    }

    virtual void onLeaveChannel(NERtcErrorCode result) {
        if (!result) {
            remote_user_id = 0;
        }
        else {
            qDebug("[ERROR] can not leave channel unsuccessfully, ERROR CODE: %d", result);
        }
    }

    virtual void onUserJoined(nertc::uid_t uid, const char* user_name) override {
        if (remote_user_id) {
            return;
        }
        qDebug("[INFO] Remote user %llu joined channel successuflly.", uid);
        emit m_engine.userJoined((quint64)uid);
        remote_user_id = uid;
    }

    virtual void onUserLeft(nertc::uid_t uid, NERtcSessionLeaveReason reason) override {
        if (remote_user_id != 0 && remote_user_id == uid) {
            qDebug("[INFO] Remote user %llu left channel.", uid);
            emit m_engine.userOffline((quint64)uid);
            //m_engine.unsubscribeRemoteUser(uid);
            remote_user_id = 0;
        }
    }

    virtual void onUserAudioStart(nertc::uid_t uid) override {
        if (remote_user_id != uid) {
            return;
        }
        m_engine.subscribeRemoteUserAudioStream(uid);
    }

    virtual void onUserVideoStart(nertc::uid_t uid, NERtcVideoProfileType max_profile) override {
        if (remote_user_id != uid) {
            return;
        }
        m_engine.subscribeRemoteUserVideoStream(uid);
        m_engine.userVideoEnabled(true);
    }

    virtual void onUserAudioStop(nertc::uid_t uid) override {
        if (remote_user_id != uid) {
            return;
        }
        m_engine.unsubscribeRemoteUserAudioStream(uid);
    }

    virtual void onUserVideoStop(nertc::uid_t uid) override {
        if (remote_user_id != uid) {
            return;
        }
        m_engine.unsubscribeRemoteUserVideoStream(uid);
        m_engine.userVideoEnabled(false);
    }

private:
    nertc::uid_t remote_user_id;

};


NRTCEngine::NRTCEngine(QObject* parent) : QObject(parent),
rtc_engine_handler_(new NRTCEngineEvent(*this))
{
    rtc_engine_ = nullptr;
    //audio_device_manager = nullptr;
    //video_device_manager = nullptr;
    app_key_ = APP_KEY;
    //随机生成user_id
    user_id_ = QRandomGenerator::global()->generate() % 100000;

    QString log_dir_path = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + "/logs/";
    qDebug()<<"[INFO] log directory: " << log_dir_path;

    //初始化引擎
    bool ret = Init(app_key_.toUtf8().data(), log_dir_path.toUtf8().data(), 10240);
    if (false == ret)
    {
        qDebug("[ERROR] Failed to initialize NERtc engine! NERtc SDK can't work!");
    }

}

NRTCEngine::~NRTCEngine() {
    Uninit();
}

bool NRTCEngine::Init(const char* app_key, const char* log_dir_path, uint32_t log_file_max_size_KBytes) {
    rtc_engine_ = static_cast<IRtcEngineEx*>(createNERtcEngine());

    //对初始化需要的参数进行配置
    rtc_engine_context_.app_key = app_key;
    rtc_engine_context_.log_dir_path = log_dir_path;
    rtc_engine_context_.log_level = kNERtcLogLevelInfo;
    rtc_engine_context_.log_file_max_size_KBytes = log_file_max_size_KBytes;
    rtc_engine_context_.event_handler = rtc_engine_handler_.get();
    rtc_engine_context_.video_prefer_hw_codec = false;
    rtc_engine_context_.video_use_exnternal_render = true;

    //初始化引擎
    if (kNERtcNoError != rtc_engine_->initialize(rtc_engine_context_)) {
        qDebug("[ERROR] Failed to initialize NERtc Engine\n");
        return false;
    }

    return true;
}

void NRTCEngine::setLocalVideoProfileType(nertc::NERtcVideoProfileType max_profile) {
    if (rtc_engine_) {
        NERtcVideoConfig video_config_;
        //qDebug("max_profile: %d", max_profile);
        video_config_.max_profile = max_profile;
        video_config_.crop_mode_ = kNERtcVideoCropModeDefault;
        int ret = rtc_engine_->setVideoConfig(video_config_);
        if (ret) {
            qDebug("[ERROR] Cannot set video config, ERROR CODE: %d", ret);
        }
        
    }
}

int NRTCEngine::joinChannel(const QString& roomid) {
    if (roomid.length() >= 12) {
        return -1;
    }

    for (int i = 0; i < roomid.length(); ++i) {
        if (roomid[i] < '0' || roomid[i] > '9') {
            return -1;
        }
    }
    

    int ret = kNERtcNoError;
    //设置本地视频参数，包括分辨率，视频渲染方式等 
    setLocalVideoProfileType(kNERtcVideoProfileStandard);

    //加入频道，token置为空
    ret = rtc_engine_->joinChannel("", roomid.toUtf8().data(), user_id_);

    if (ret == kNERtcNoError) {
        emit joiningChannel();
        qDebug() << "[INFO] start joining channel successfully!";
    }
    else {
        qDebug("[ERROR] can't join channel, ERROR CODE: %d", ret);
    }

    int ret_temp = rtc_engine_->enableLocalAudio(true);
    if (ret_temp) {
        qDebug("[ERROR] can not enable local audio, ERROR CODE: %d", ret_temp);
    }

    //显示引擎的当前状态
    qDebug("[INFO] current connection state: %d", rtc_engine_->getConnectionState());
    return ret;
}

int NRTCEngine::leaveChannel() {
    int ret = kNERtcNoError;
    qDebug("[INFO] current connection state: %d", rtc_engine_->getConnectionState());
    if (rtc_engine_) {
        //关闭音视频
        ret = rtc_engine_->enableLocalAudio(false);
        ret = rtc_engine_->enableLocalVideo(false);

        //离开频道
        ret = rtc_engine_->leaveChannel();
        if (kNERtcNoError == ret) {
            emit leavingChannel();
        }
        else {
            qDebug("[ERROR] Can't leave channel, ERROR CODE: %d", ret);
        }
    }
    return ret;
}

int NRTCEngine::muteLocalAudioStream(bool mute) {
    return rtc_engine_->muteLocalAudioStream(mute);
}

int NRTCEngine::enableVideo(bool enabled) {
    return rtc_engine_->enableLocalVideo(enabled);
    //return rtc_engine_->muteLocalVideoStream(!enabled);
}

void NRTCEngine::onReceiveVideoFrame(nertc::uid_t uid, void* data, uint32_t type, uint32_t width, uint32_t height,
    uint32_t count, uint32_t offset[4], uint32_t stride[4], uint32_t rotation, void* user_data) 
{
    
    auto params = reinterpret_cast<RENDER_PARAMS*>(user_data);

    params->mutex.lock();
    if (params->weak.expired()) {
        params->mutex.unlock();
        qWarning() << "[NRTC] Receive video frame, render pointer is expired.";
        delete params;
        return;
    }

    auto renderImple = params->weak.lock();
    auto rotationWidth = width;
    auto rotationHeight = height;

    libyuv::RotationMode rotate_mode = libyuv::kRotateNone;
    switch (rotation)
    {
    case kNERtcVideoRotation_0:
    {
        rotate_mode = libyuv::kRotate0;
    }
    break;
    case kNERtcVideoRotation_90:
    {
        rotate_mode = libyuv::kRotate90;
        rotationWidth = height;
        rotationHeight = width;
    }
    break;
    case kNERtcVideoRotation_180:
    {
        rotate_mode = libyuv::kRotate180;
    }
    break;
    case kNERtcVideoRotation_270:
    {
        rotate_mode = libyuv::kRotate270;
        rotationWidth = height;
        rotationHeight = width;
    }
    break;
    }

    int frameSize = static_cast<int>(width * height * count / 2);
    QVideoFrame frame(frameSize, QSize(static_cast<int>(rotationWidth), static_cast<int>(rotationHeight)),
        static_cast<int>(rotationWidth), QVideoFrame::Format_YUV420P);

    if (frame.map(QAbstractVideoBuffer::WriteOnly))
    {
        auto src = reinterpret_cast<uint8_t*>(data);
        auto dest = reinterpret_cast<uint8_t*>(frame.bits());

        if (uid == 0) {
            libyuv::I420Mirror(src + offset[0], static_cast<int>(stride[0]),
                src + offset[1], static_cast<int>(stride[1]),
                src + offset[2], static_cast<int>(stride[2]),
                dest, static_cast<int>(rotationWidth),
                dest + rotationWidth * rotationHeight, rotationWidth / 2,
                dest + rotationWidth * rotationHeight + rotationWidth * rotationHeight / 4, rotationWidth / 2,
                static_cast<int>(width), static_cast<int>(height));
        }
        else {
            libyuv::I420Rotate(src + offset[0], static_cast<int>(stride[0]),
                src + offset[1], static_cast<int>(stride[1]),
                src + offset[2], static_cast<int>(stride[2]),
                dest, static_cast<int>(rotationWidth),
                dest + rotationWidth * rotationHeight, rotationWidth / 2,
                dest + rotationWidth * rotationHeight + rotationWidth * rotationHeight / 4, rotationWidth / 2,
                static_cast<int>(width), static_cast<int>(height), rotate_mode);
        }

        frame.setStartTime(0);
        frame.unmap();

        QSize size = QSize(static_cast<int>(rotationWidth), static_cast<int>(rotationHeight));

        emit renderImple->receivedVideoFrame(frame, size);
        
    }

    params->mutex.unlock();
}


int NRTCEngine::setupLocalVideo(FrameProvider * view) {
    RENDER_PARAMS* params = new RENDER_PARAMS;
    if (view != nullptr) {
        std::shared_ptr<VideoRenderImpl>* videoRenderImple = new std::shared_ptr<VideoRenderImpl>(std::make_shared<VideoRenderImpl>(view));
        std::weak_ptr<VideoRenderImpl>* renderWeak = new std::weak_ptr<VideoRenderImpl>;
        (*renderWeak) = *videoRenderImple;
        params->weak = *renderWeak;
    }

    //设置本地视图参数
    NERtcVideoCanvas canvas;
    canvas.cb = view == nullptr ? nullptr : NRTCEngine::onReceiveVideoFrame;
    canvas.user_data = view == nullptr ? nullptr : reinterpret_cast<void*>(params);
    canvas.scaling_mode = kNERtcVideoScaleFit;

    //设置本地视图
    int ret = rtc_engine_->setupLocalVideoCanvas(&canvas);
    if (ret) {
        qDebug("ERROR: Can not setup local video canvas! ERROR CODE: %d", ret);
    }

    if (view != nullptr) {
        rtc_engine_->enableLocalVideo(true);
    }
    else {
        rtc_engine_->enableLocalVideo(false);
    }
    return ret;
}

int NRTCEngine::setupRemoteVideo(unsigned int uid, FrameProvider * view) {
    RENDER_PARAMS* params = new RENDER_PARAMS;
    if (view != nullptr) {
        std::shared_ptr<VideoRenderImpl>* videoRenderImple = new std::shared_ptr<VideoRenderImpl>(std::make_shared<VideoRenderImpl>(view));
        std::weak_ptr<VideoRenderImpl>* renderWeak = new std::weak_ptr<VideoRenderImpl>;
        (*renderWeak) = *videoRenderImple;
        params->weak = *renderWeak;
    }

    //设置远端视图参数
    NERtcVideoCanvas canvas;
    canvas.cb = view == nullptr ? nullptr : NRTCEngine::onReceiveVideoFrame;
    canvas.user_data = view == nullptr ? nullptr : reinterpret_cast<void*>(params);
    canvas.scaling_mode = kNERtcVideoScaleFit;

    //设置远端视图
    int ret = rtc_engine_->setupRemoteVideoCanvas(uid, &canvas);
    if (ret) {
        qDebug("[ERROR] Can not setup remote video canvas! ERROR CODE: %d", ret);
    }
    
    //设置远端视图的画布后，订阅加入频道的用户
    if (view != nullptr) {
        subscribeRemoteUserVideoStream(uid);
        subscribeRemoteUserAudioStream(uid);
    }

    return ret;
}

void NRTCEngine::Uninit() {
    if (rtc_engine_) {
        int res = rtc_engine_->enableLocalAudio(false);
        res = rtc_engine_->enableLocalVideo(false);
        res = rtc_engine_->leaveChannel();

        //Sleep(500);//等待底层异步关闭
        //同步关闭
        rtc_engine_->release(true);
        destroyNERtcEngine((void*&)rtc_engine_);
        rtc_engine_ = nullptr;
    }
}

void NRTCEngine::subscribeRemoteUserVideoStream(nertc::uid_t uid) {
    int ret_temp = rtc_engine_->subscribeRemoteVideoStream(uid, kNERtcRemoteVideoStreamTypeHigh, true);
    if (ret_temp) {
        qDebug("[ERROR] can not subscribe remote video stream! ERROR CODE: %d", ret_temp);
    }
}

void NRTCEngine::subscribeRemoteUserAudioStream(nertc::uid_t uid) {
    int ret_temp = rtc_engine_->subscribeRemoteAudioStream(uid, true);
    if (ret_temp) {
        qDebug("[ERROR] can not subscribe remote audio stream! ERROR CODE: %d", ret_temp);
    }
}

void NRTCEngine::unsubscribeRemoteUserVideoStream(nertc::uid_t uid) {
    int ret_temp = rtc_engine_->subscribeRemoteVideoStream(uid, kNERtcRemoteVideoStreamTypeHigh, false);
    if (ret_temp) {
        qDebug("[ERROR] can not unsubscribe remote video stream! ERROR CODE: %d", ret_temp);
    }
}

void NRTCEngine::unsubscribeRemoteUserAudioStream(nertc::uid_t uid) {
    int ret_temp = rtc_engine_->subscribeRemoteAudioStream(uid, false);
    if (ret_temp) {
        qDebug("[ERROR] can not unsubscribe remote audio stream! ERROR CODE: %d", ret_temp);
    }
}
