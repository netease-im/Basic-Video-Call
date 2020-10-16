#ifndef NRTC_ENGINE_H
#define NRTC_ENGINE_H

#include <memory>
#include <QString>
#include <QVariant>
#include <QCoreApplication>
#include "nertc_engine_ex.h"
#include "nertc_audio_device_manager.h"
#include "nertc_video_device_manager.h"
//#include "videowidget.h"

#define APP_KEY          // put your app key here, testing
#define MAX_PATH 260            //max length of the log's directory path

namespace smaple_nertc {

struct NRTCParameter{
    bool initialized; //if has been initialized
    //bool p2p_mode_;
    bool audio_aec_enable;
    bool audio_agc_enable;
    bool audio_ns_enable;
    bool audio_external_mix_enable;
    bool audio_earphone;
    bool record_host_enabled;
    bool record_audio_enabled;
    bool record_video_enabled;
    nertc::NERtcRecordType record_type;
    bool auto_start_local_audio;
    bool auto_start_local_video;
    bool auto_subscribe_audio;
    //bool auto_subscribe_video;
    //bool force_auto_subscribe_video;
    bool publish_self_stream_enabled;
    nertc::NERtcLogLevel log_level;
    //bool video_capture_observer_enabled;
    bool video_smooth_enabled;
    bool video_watermark_enabled;
    bool video_filter_enabled;
    bool audio_filter_enabled;
    NRTCParameter()
    {
        initialized = false;
        //p2p_mode_ = false;
        audio_aec_enable = true;
        audio_agc_enable = true;
        audio_ns_enable = true;
        audio_external_mix_enable = false;
        audio_earphone = false;
        record_host_enabled = true;
        record_audio_enabled = true;
        record_video_enabled = true;
        record_type = nertc::kNERtcRecordTypeAll;
        auto_start_local_audio = true;
        auto_start_local_video = true;
        auto_subscribe_audio = true;
        //auto_subscribe_video = true;
        //force_auto_subscribe_video = true;
        //video_capture_observer_enabled = true;
        publish_self_stream_enabled = false;
        log_level = nertc::kNERtcLogLevelInfo;
        video_smooth_enabled = false;
        video_watermark_enabled = false;
        video_filter_enabled = false;
        audio_filter_enabled = false;
    }
};




class NRTCEngine : public QObject
{
    Q_OBJECT
public:
    explicit NRTCEngine(QObject *parent = nullptr);
    ~NRTCEngine();

    nertc::IRtcEngineEx * GetRtcEngine() { return rtc_engine_; }

    bool Init(const char *app_key, const char *log_dir_path, uint32_t log_file_max_size_KBytes);
    void Uninit();

    int joinChannel(const QString& token, const QString& roomid, const QString& uid,
                                bool autoStartVideo, bool autoStartAudio, int video_resolution);
    int leaveChannel();
    void setCurrentVideoProfile(unsigned int index);
    int muteLocalAudioStream(bool mute);

    int enableVideo(bool enabled);
    QVariantMap getRecordingDeviceList();
    QVariantMap getPlayoutDeviceList();
    QVariantMap getVideoDeviceList();
    int setRecordingDevice(const QString& guid);
    int setPlayoutDevice(const QString& guid);
    int setVideoDevice(const QString& guid);
    int getRecordingDeviceVolume();
    int getPalyoutDeviceVolume();
    int setRecordingDeviceVolume(int volume);
    int setPalyoutDeviceVolume(int volume);

    int setupLocalVideo(void* hwnd);
    int setupRemoteVideo(unsigned int uid, void* hwnd);
    void autoStartVideo();
    void autoStartAudio();
    

    void setLocalVideoProfileType(nertc::NERtcVideoProfileType max_profile);
    void setParameter(const NRTCParameter &rtc_parameter);
    void startRemoteVideo(nertc::uid_t uid);
    void stopRemoteVideo(nertc::uid_t uid);
    void startRemoteAudio(nertc::uid_t uid);
    void stopRemoteAudio(nertc::uid_t uid);
    

signals:
    void joiningChannel();
    void leavingChannel();
    void videoStopped(unsigned long long uid);
    void videoStart(unsigned long long uid, int max_profile);
    void joinedChannelSuccess();
    void userJoined(quint64 uid);
    void userLeft(quint64 uid);

private:
    // 网易云通信 SDK 引擎
    nertc::IRtcEngineEx * rtc_engine_;
    // 初始化引擎所需要的参数集合
    nertc::NERtcEngineContext rtc_engine_context_;
    // 当前连接状态
    nertc::NERtcConnectionStateType connection_state_;
    // User ID
    nertc::uid_t cur_my_uid_;

    NRTCParameter rtc_parameter_;

    nertc::IAudioDeviceManager *audio_device_manager;
    nertc::IVideoDeviceManager *video_device_manager;

    std::unique_ptr<nertc::IRtcEngineEventHandlerEx> rtc_engine_handler_;
    QString app_key_;
    bool auto_start_video_;
    bool auto_start_audio_;
    nertc::NERtcVideoProfileType current_video_profile;

};

}

#endif // NRTC_ENGINE_H
