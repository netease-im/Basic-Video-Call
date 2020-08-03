//  Created by NetEase on 8/3/2020.
//  Copyright (c) 2014-2020 NetEase, Inc. All rights reserved.
//

#ifndef NRTC_ENGINE_H
#define NRTC_ENGINE_H

#include <memory>
#include <QString>
#include <QVariant>
#include <QCoreApplication>
#include "nertc_engine_ex.h"
#include "nertc_audio_device_manager.h"
#include "nertc_video_device_manager.h"
#include "videorenderimpl.h"
#include "frameprovider.h"

#define APP_KEY ""              // put your app key here, testing
#define MAX_PATH 260            //max length of the log's directory path

class QQuickItem;
class QWindow;

class NRTCEngine : public QObject
{
    Q_OBJECT
public:
    explicit NRTCEngine(QObject* parent = nullptr);
    ~NRTCEngine();

    nertc::IRtcEngineEx* GetRtcEngine() { return rtc_engine_; }

    bool Init(const char* app_key, const char* log_dir_path, uint32_t log_file_max_size_KBytes);
    void Uninit();

    Q_INVOKABLE int joinChannel(const QString& roomid);
    Q_INVOKABLE int leaveChannel();
    Q_INVOKABLE int muteLocalAudioStream(bool mute);
    Q_INVOKABLE int enableVideo(bool enabled);
    Q_INVOKABLE int setupLocalVideo(FrameProvider * view);
    Q_INVOKABLE int setupRemoteVideo(unsigned int uid, FrameProvider * view);

    void setLocalVideoProfileType(nertc::NERtcVideoProfileType max_profile);
    void subscribeRemoteUserVideoStream(nertc::uid_t uid);
    void subscribeRemoteUserAudioStream(nertc::uid_t uid);
    void unsubscribeRemoteUserVideoStream(nertc::uid_t uid);
    void unsubscribeRemoteUserAudioStream(nertc::uid_t uid);


signals:
    void joiningChannel();
    void leavingChannel();
    void videoStopped(unsigned long long uid);
    void videoStart(unsigned long long uid, int max_profile);
    void joinedChannelSuccess();
    void userJoined(unsigned long long uid);
    void userOffline(unsigned long long uid);
    void userVideoEnabled(bool enabled);

private:
    static void onReceiveVideoFrame(nertc::uid_t uid, void* data, uint32_t type, uint32_t width, uint32_t height,
        uint32_t count, uint32_t offset[4], uint32_t stride[4], uint32_t rotation, void* user_data);

private:
    // 网易云通信 SDK 引擎
    nertc::IRtcEngineEx* rtc_engine_;
    // 初始化引擎所需要的参数集合
    nertc::NERtcEngineContext rtc_engine_context_;
    // 当前连接状态
    nertc::NERtcConnectionStateType connection_state_;

    std::unique_ptr<nertc::IRtcEngineEventHandlerEx> rtc_engine_handler_;
    QString app_key_;
    nertc::uid_t user_id_;

};

#endif // NRTC_ENGINE_H
