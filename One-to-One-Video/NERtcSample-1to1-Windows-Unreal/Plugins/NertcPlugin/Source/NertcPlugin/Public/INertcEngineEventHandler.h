/**
 * @file nertc_engine_event_handler.h
 * @brief The interface header file of expansion callback of the NERTC SDK.
 * All parameter descriptions of the NERTC SDK. All string-related parameters (char *) are encoded in UTF-8.
 * @copyright (c) 2021, NetEase Inc. All rights reserved.
 */

#pragma once

#include "NertcBaseTypes.h"
#include "NertcEngineDefines.h"
#include "NertcErrorCode.h"
#include "NertcWarnCode.h"

/**
 * @namespace nertc
 * @brief namespace nertc
 */
namespace nertc {
/**
 * @if English
 * IRtcEngineEventHandler callback interface class is used to send callback event notifications to the app from SDK. The app
 * gets event notifications from the SDK through inheriting the interface class. All methods in this interface class have their
 * (empty) default implementations, and the application can inherit only some of the required events instead of all of them.
 * When calling a callback method, the application must not implement time-consuming operations or call blocking-triggered APIs.
 * For example, if you want to enable audio and video, the SDK may be affected in the runtime.
 * @endif
 * @if Chinese
 * IRtcEngineEventHandler 回调接口类用于 SDK 向 App 发送回调事件通知，App 通过继承该接口类的方法获取 SDK 的事件通知。
 * 接口类的所有方法都有缺省（空）实现，App 可以根据需要只继承关心的事件。在回调方法中，App 不应该做耗时或者调用可能会引起阻塞的
 * API（如开启音频或视频等），否则可能影响 SDK 的运行。
 * @endif
 */
class IRtcEngineEventHandler {
 public:
  virtual ~IRtcEngineEventHandler() {}

   /**
    * @if English
    * Occurs when the error occurs.
    * <br>The callback is triggered to report an error related to network or media during SDK runtime. In most cases, the SDK
    * cannot fix the issue and resume running. The SDK requires the app to take action or informs the user of the issue.
    * @param error_code        The error code. For more information, see NERtcDMErrorCode.
    * @param msg               Error description.
    * @endif
    * @if Chinese
    * 发生错误回调。
    * <br>该回调方法表示 SDK 运行时出现了（网络或媒体相关的）错误。通常情况下，SDK上报的错误意味着SDK无法自动恢复，需要 App
    * 干预或提示用户。
    * @param error_code        错误码。详细信息请参考 NERtcDMErrorCode
    * @param msg 错误描述。
    * @endif
    */
  virtual void onError(int error_code, const char* msg) {
    (void)error_code;
    (void)msg;
  }

    /**
    * @if English
    * Occurs when a warning occurs.
    * <br>The callback is triggered to report a warning related to network or media during SDK runtime. In most cases, the app
    * ignores the warning message and the SDK resumes running.
    * @param warn_code     The warning code. For more information, see {@link NERtcWarnCode}.
    * @param msg        The warning description.
    * @endif
    * @if Chinese
    * 发生警告回调。
    * <br>该回调方法表示 SDK 运行时出现了（网络或媒体相关的）警告。通常情况下，SDK 上报的警告信息 App 可以忽略，SDK 会自动恢复。
    * @param warn_code 警告码。详细信息请参考 {@link NERtcWarnCode}。
    * @param msg 警告描述。
    * @endif
    */
  virtual void onWarning(int warn_code, const char* msg) {
    (void)warn_code;
    (void)msg;
  }
 /**
    * @if English
    * Occurs when an API call finished.
    * <br>This callback method indicates that the SDK has finished executing a user's API call.
    * @param api_name     The API name.
    * @param error        The execute result code.
    * @param message      The execute result message.
    * @endif
    * @if Chinese
    * API调用结束回调。
    * <br>该回调方法表示 SDK 执行完了一个用户的API调用。
    * @param api_name     API名称
    * @param error        API执行结果错误码。
    * @param message      API执行结果描述。
    * @endif
    */
  virtual void onApiCallExecuted(const char* api_name, NERtcErrorCode error_code, const char* msg) {
    (void)api_name;
    (void)error_code;
    (void)msg;
  };

/**
    * @if English
    * Occurs when the hardware resources are released.
    * <br>The SDK prompts whether hardware resources are successfully released.
    * @param result    The result.
    * @endif
    * @if Chinese
    * 释放硬件资源的回调。
    * <br>SDK提示释放硬件资源是否成功。
    * @param result    返回结果。
    * @endif
    */
  virtual void onReleasedHwResources(NERtcErrorCode result) { (void)result; }

    /**
    * @if English
    * Allows a user to join a room. The callback indicates that the client has already signed in.
    * @param cid     The ID of the room that the client joins.
    * @param uid     Specifies the ID of a user. If you specify the uid in the joinChannel method, a specificed ID is returned at
    * the time. If not, the  ID automatically assigned by the CommsEase’s server is returned.
    * @param result  Indicates the result.
    * @param elapsed The time elapsed from calling the joinChannel method to the occurrence of this event. Unit: milliseconds.
    * @endif
    * @if Chinese
    * 加入房间回调，表示客户端已经登入服务器。
    * @param cid     客户端加入的房间 ID。
    * @param uid     用户 ID。 如果在 joinChannel 方法中指定了 uid，此处会返回指定的 ID; 如果未指定
    * uid，此处将返回云信服务器自动分配的 ID。
    * @param result  返回结果。
    * @param elapsed 从 joinChannel 开始到发生此事件过去的时间，单位为毫秒。
    * @endif
    */
  virtual void onJoinChannel(channel_id_t cid, uid_t uid, NERtcErrorCode result, uint64_t elapsed) {
    (void)cid;
    (void)uid;
    (void)result;
    (void)elapsed;
  }

    /**
    * @if English
    * Triggers reconnection.
    * <br>In some cases, a client may be disconnected from the server, the SDK starts reconnecting. The callback is triggered
    * when the reconnection starts.
    * @param cid Specifies the ID of a room.
    * @param uid Specifies the ID of a user.
    * @endif
    * @if Chinese
    * 触发重连。
    * <br>有时候由于网络原因，客户端可能会和服务器失去连接，SDK会进行自动重连，开始自动重连后触发此回调。
    * @param cid  房间 ID。
    * @param uid  用户 ID。
    * @endif
    */
  virtual void onReconnectingStart(channel_id_t cid, uid_t uid) {
    (void)cid;
    (void)uid;
  }

    /**
    * @if English
    * Occurs when the state of network connection is changed.
    * <br>The callback is triggered when the state of network connection is changed. The callback returns the current state of
    * network connection and the reason why the network state changes.
    * @param state  The state of current network connection.
    * @param reason The reason why the network state changes.
    * @endif
    * @if Chinese
    * 网络连接状态已改变回调。
    * <br>该回调在网络连接状态发生改变的时候触发，并告知用户当前的网络连接状态和引起网络状态改变的原因。
    * @param state  当前的网络连接状态。
    * @param reason  引起当前网络连接状态发生改变的原因。
    * @endif
    */
  virtual void onConnectionStateChange(NERtcConnectionStateType state, NERtcReasonConnectionChangedType reason) {
    (void)state;
    (void)reason;
  }
    /**
    * @if English
    * Occurs when the network type is changed.
    * <br>The callback is triggered when network is changed. The callback returns the current network type.
    * @param new_type  The new type of current network.
    * @endif
    * @if Chinese
    * 网络类型已经改变的回调。
    * <br>该回调在网络发生改变的时候触发，并告知用户当前的网络类型。
    * @param new_type  当前的网络类型。
    * @endif
    */
  virtual void onNetworkTypeChanged(NERtcNetworkType new_type) {
      (void)new_type;
  };
    /**
    * @if English
    * Occurs when a user rejoins a room.
    * <br>If a client is disconnected from the server due to poor network quality, the SDK starts reconnecting. If the client and
    * server are reconnected, the callback is triggered.
    * @param cid       The ID of the room that the client joins.
    * @param uid       The ID of a user.
    * @param result    The result.
    * @param elapsed   The time elapsed from reconnection to the occurrence of this event. Unit: milliseconds.
    * @endif
    * @if Chinese
    * 重新加入房间回调。
    * <br>在弱网环境下，若客户端和服务器失去连接，SDK会自动重连。自动重连成功后触发此回调方法。
    * @param cid       客户端加入的房间 ID。
    * @param uid       用户 ID。
    * @param result    返回结果。
    * @param elapsed   从开始重连到发生此事件过去的时间，单位为毫秒。
    * @endif
    */
  virtual void onRejoinChannel(channel_id_t cid, uid_t uid, NERtcErrorCode result, uint64_t elapsed) {
    (void)cid;
    (void)uid;
    (void)result;
    (void)elapsed;
  }

    /**
    * @if English
    * Occurs when a user leaves a room.
    * <br>After an app invokes the leaveChannel method, SDK prompts whether the app successfully leaves the room.
    * @param result    The result.
    * @endif
    * @if Chinese
    * 退出房间回调。
    * <br>App 调用 leaveChannel 方法后，SDK 提示 App 退出房间是否成功。
    * @param result        返回结果。
    * @param channel_id    离开的channel的ID。
    * @endif
    */
  virtual void onLeaveChannel(NERtcErrorCode result, uint64_t channel_id) { 
        (void)result;
        (void)channel_id;
}

    /**
    * @if English
    * Network connection interruption.
    * @note
    * - The callback is triggered if the SDK fails to connect to the server three consecutive times after you successfully call
    * the joinChannel method.
    * - A client may be disconnected from the server in poor network connection. At this time,  the SDK needs not automatically
    * reconnecting until the SDK triggers the callback method.
    * @param reason    The reason why the network is disconnected.
    * @endif
    * @if Chinese
    * 网络连接中断
    * @note
    * - SDK 在调用 joinChannel 加入房间成功后，如果和服务器失去连接且连续 3 次重连失败，就会触发该回调。
    * - 由于非网络原因，客户端可能会和服务器失去连接，此时SDK无需自动重连，直接触发此回调方法。
    * @param reason    网络连接中断原因。
    * @endif
    */
  virtual void onDisconnect(NERtcErrorCode reason) { (void)reason; }

    /**
    * @if English
    * Occurs when a user changes the role in live streaming.
    * <br>After the local user joins a room, the user can call the \ref IRtcEngine::setClientRole "setClientRole" to change the
    * role. Then, the callback is triggered. For example, you can switch the role from host to audience, or from audience to
    * host.
    * @note In live streaming, if you join a room and successfully call this method to change the role, the following callbacks
    * are triggered.
    * - If the role changes from host to audience, the onClientRoleChange is locally triggered, and the \ref
    * nertc::IRtcEngineEventHandler::onUserLeft "onUserLeft" is remotely triggered.
    * - If the role is changed from audience to host, the onClientRoleChange callback is locally triggered, and the \ref
    * nertc::IRtcEngineEventHandler::onUserJoined "onUserJoined" is remotely triggered.
    * @param oldRole  The role before the user changes the role.
    * @param newRole  The role after the change.
    * @endif
    * @if Chinese
    * 直播场景下用户角色已切换回调。
    * <br>本地用户加入房间后，通过 \ref IRtcEngine::setClientRole "setClientRole"
    * 切换用户角色后会触发此回调。例如主播切换为观众、从观众切换为主播。
    * @note 直播场景下，如果您在加入房间后调用该方法切换用户角色，调用成功后，会触发以下回调：
    * - 主播切观众，本端触发onClientRoleChanged回调，远端触发\ref nertc::IRtcEngineEventHandler::onUserLeft "onUserLeft"回调。
    * - 观众切主播，本端触发onClientRoleChanged回调，远端触发\ref nertc::IRtcEngineEventHandler::onUserJoined
    * "onUserJoined"回调。
    * @param oldRole  切换前的角色。
    * @param newRole  切换后的角色。
    * @endif
    */
  virtual void onClientRoleChanged(NERtcClientRole oldRole, NERtcClientRole newRole) {
    (void)oldRole;
    (void)newRole;
  }

    /**
    * @if English
    * Occurs when a remote user joins the current room.
    * <br>The callback prompts that a remote user joins the room and returns the ID of the user that joins the room. If the user
    * ID already exists, the remote user also receives a message that the user already joins the room, which is returned by the
    * callback.
    * @param uid           The ID of the user that joins the room.
    * @param user_name     The name of the remote user who joins the room.
    * @endif
    * @if Chinese
    * 远端用户加入当前房间回调。
    * <br>该回调提示有远端用户加入了房间，并返回新加入用户的
    * ID；如果加入之前，已经有其他用户在房间中了，新加入的用户也会收到这些已有用户加入房间的回调。
    * @param uid           新加入房间的远端用户 ID。
    * @param user_name     新加入房间的远端用户名。
    * @param custom_info   该远端用户加入的额外信息。
    * @endif
    */
  virtual void onUserJoined(uid_t uid, const char* user_name, const NERtcUserJoinExtraInfo& custom_info) {
    (void)uid;
    (void)user_name;
    (void)custom_info;
  }

    /**
    * @if English
    * Occurs when a remote user leaves a room.
    * <br>A message is returned indicates that a remote user leaves the room or becomes disconnected. In most cases, a user
    * leaves a room due to the following reasons: The user exit the room or connections time out.
    * - When a user leaves a room, remote users will receive callback notifications that users leave the room. In this way, users
    * can be specified to leave the room.
    * - If the connection times out, and the user does not receive data packets for a time period of 40 to 50 seconds, then the
    * user becomes disconnected.
    * @param uid           The ID of the user that leaves the room.
    * @param reason        The reason why remote user leaves.
    * @endif
    * @if Chinese
    * 远端用户离开当前房间的回调。
    * <br>提示有远端用户离开了房间（或掉线）。通常情况下，用户离开房间有两个原因，即正常离开和超时掉线：
    * - 正常离开的时候，远端用户会收到正常离开房间的回调提醒，判断用户离开房间。
    * - 超时掉线的依据是，在一定时间内（40~50s），用户没有收到对方的任何数据包，则判定为对方掉线。
    * @param uid           离开房间的远端用户 ID。
    * @param reason        远端用户离开原因。
    * @param custom_info   该远端用户离开的额外信息。
    * @endif
    */
  virtual void onUserLeft(uid_t uid, NERtcSessionLeaveReason reason, const NERtcUserJoinExtraInfo& custom_info) {
    (void)uid;
    (void)reason;
    (void)custom_info;
  }
    /**
    * @if English
    * Occurs when a remote user enables audio.
    * @param uid           The ID of a remote user.
    * @endif
    * @if Chinese
    * 远端用户开启音频的回调。
    * @param type    远端用户流类型。
    * @param uid           远端用户ID。
    * @endif
    */
  virtual void onUserAudioStart(NERtcAudioStreamType type, uid_t uid) {
    (void)type;
    (void)uid;
  }
    /**
    * @if English
    * Occurs when a remote user disables audio.
    * @param uid           The ID of a remote user.
    * @endif
    * @if Chinese
    * 远端用户停用音频的回调。
    * @param uid           远端用户ID。
    * @endif
    */
  virtual void onUserAudioStop(NERtcAudioStreamType type, uid_t uid) { 
    (void)type;
    (void)uid;
  }
    /**
    * @if English
    * Occurs when a remote user enables video.
    * @param uid           The ID of a remote user.
    * @param max_profile   The resolution of video encoding measures the encoding quality.
    * @endif
    * @if Chinese
    * 远端用户开启视频的回调。
    * @param type    远端用户流类型。
    * @param uid           远端用户ID。
    * @param max_profile   视频编码的分辨率，用于衡量编码质量。
    * @endif
    */
  virtual void onUserVideoStart(NERtcVideoStreamType type, uid_t uid, NERtcVideoProfileType max_profile) {
    (void)type;
    (void)uid;
    (void)max_profile;
  }
    /**
    * @if English
    * Occurs when a remote user disables video.
    * @param uid           The ID of a remote user.
    * @endif
    * @if Chinese
    * 远端用户停用视频的回调。
    * @param type    远端用户流类型。
    * @param uid           远端用户ID。
    * @endif
    */
  virtual void onUserVideoStop(NERtcVideoStreamType type, uid_t uid) {
    (void)type;
    (void)uid;
}
/**
    * @if English
    * Occurs when screen sharing is paused/resumed/started/ended.
    * <br>The method applies to Windows only.
    * @since V4.2.0
    * @param status    Screen capture status. For more information, see #nertc_screen_capture_status_t.
    * @endif
    * @if Chinese
    * 屏幕共享状态变化回调。
    * <br>该方法仅适用于 Windows 平台。
    * @since V4.2.0
    * @param status    屏幕共享状态。详细信息请参考 #nertc_screen_capture_status_t 。
    * @endif
    */
    virtual void onScreenCaptureStatusChanged(NERtcScreenCaptureStatus status) {(void)status;}
    /**
    * @if English
    * Occurs when video configurations of remote users are updated.
    * @param uid           The ID of a remote user.
    * @param max_profile   The resolution of video encoding measures the encoding quality.
    * @endif
    * @if Chinese
    * @param uid           远端用户 ID。
    * @param max_profile   视频编码的分辨率，用于衡量编码质量。
    * @endif
    */
    virtual void onUserVideoProfileUpdate(uid_t uid, NERtcVideoProfileType max_profile) {
        (void)uid;
        (void)max_profile;
    }
    /**
    * @if English
    * Callbacks that specify whether to mute remote users.
    * @param uid       The ID of a remote user.
    * @param mute      indicates whether to unmute the remote user.
    * @endif
    * @if Chinese
    * 远端用户是否静音的回调。
    * @param type       音频流类型。
    * @param uid               远端用户ID。
    * @param mute              是否静音。
    * @endif
    */
    virtual void onUserAudioMute(NERtcAudioStreamType stream_type, uid_t uid, bool mute) {
        (void)stream_type;
        (void)uid;
        (void)mute;
    }
    /**
    * @if English
    * Occurs when a remote user stops or resumes sending video streams.
    * @param uid       The ID of a remote user.
    * @param mute      Whether to disable video streams.
    * @endif
    * @if Chinese
    * 远端用户暂停或恢复发送视频流的回调。
    * @param type       视频流类型。
    * @param uid               远端用户ID。
    * @param mute              是否禁视频流。
    * @endif
    */
    virtual void onUserVideoMute(NERtcVideoStreamType stream_type, uid_t uid, bool mute){
        (void)stream_type;
        (void)uid;
        (void)mute;
    }
    /**
    * @if English
    * Occurs when the audio routing changes.
    * @param routing The current audio output routing.
    * @endif
    * @if Chinese
    * 音频路由变化回调。
    * @param routing 当前音频输出路由。
    * @endif
    */
    virtual void onAudioDeviceRoutingDidChange(NERtcAudioOutputRouting routing){
       (void)routing;
    }
    /**
    * @if English
    * Occurs when the state of the audio device changes.
    * @param device_id    Device ID.
    * @param device_type  The type of the device. For more information, see NERtcAudioDeviceType_t.
    * @param device_state The state of the audio device.
    * @endif
    * @if Chinese
    * 音频设备状态更改的回调。
    * @param device_id     设备ID。
    * @param device_type   音频设备类型。详细信息请参考 NERtcAudioDeviceType_t。
    * @param device_state  音频设备状态。
    * @endif
    */
    virtual void onAudioDeviceStateChanged(const char* device_id,NERtcAudioDeviceType device_type, NERtcAudioDeviceState device_state) {
        (void)device_id;
        (void)device_type;
        (void)device_state;
    }
    /**
    * @if English
    * Occurs when the default audio devices changes.
    * @param device_id     Device ID.
    * @param device_type   The type of the device.
    * @endif
    * @if Chinese
    * 音频默认设备更改的回调。
    * @param device_id     设备ID。
    * @param device_type   音频设备类型。
    * @endif
    */
    virtual void onAudioDefaultDeviceChanged(const char* device_id, NERtcAudioDeviceType device_type){
        (void)device_id;
        (void)device_type;
    }
    /**
    * @if English
    * Occurs when the state of the video device is changed.
    * @param device_id     Device ID.
    * @param device_type   The type of the video device.
    * @param device_state  The state of the video device.
    * @endif
    * @if Chinese
    * 视频设备状态已改变的回调。
    * @param device_id     设备ID。
    * @param device_type   视频设备类型。
    * @param device_state  视频设备状态。
    * @endif
    */
    virtual void onVideoDeviceStateChanged(const char* device_id,NERtcVideoDeviceType device_type,NERtcVideoDeviceState device_state){
        (void)device_id;
        (void)device_type;
        (void)device_state;
    }
    /**
    * @if English
    * Occurs when the camera focus position changes.
    * The callback indicates that the camera focus position changes.
    * The callback is triggered if a local user calls the setCameraFocusPosition method to change the focus position.
    * @note The audio-only SDK disables this API. If you need to use the API, you can download the standard SDK from the official
    * website of CommsEase and replace the audio-only SDK.
    * @param info The new focusposition.
    * @endif
    * @if Chinese
    * 摄像头对焦区域已改变回调。
    * 该回调表示相机的对焦区域发生了改变。
    * 该回调是由本地用户调用 setCameraFocusPosition 方法改变对焦位置触发的。
    * @note 纯音频 SDK 禁用该接口，如需使用请前往云信官网下载并替换成视频 SDK。
    * @param info 新的对焦区域位置。
    * @endif
    */
    virtual void onCameraFocusChanged(const NERtcCameraFocusAndExposureInfo& info){
      (void)info;
    }
    /**
    * @if English
    * Occurs when the camera exposure position changes.
    * The callback is triggered if a local user calls the setCameraExposurePosition method to change the exposure position.
    * @note The audio-only SDK disables this API. If you need to use the API, you can download the standard SDK from the official
    * website of CommsEase and replace the audio-only SDK.
    * @param info The new exposure position.
    * @endif
    * @if Chinese
    * 摄像头曝光区域已改变回调。
    * 该回调是由本地用户调用 setCameraExposurePosition方法改变曝光位置触发的。
    * @note 纯音频 SDK 禁用该接口，如需使用请前往云信官网下载并替换成视频 SDK。
    * @param info 新的曝光区域位置信息。
    * @endif
    */
    virtual void onCameraExposureChanged(const NERtcCameraFocusAndExposureInfo& info) {
      (void)info;
    }
    /**
    * @if English
    * Occurs when the first audio frame from a remote user is received.
    * @param uid       The ID of a remote user whose audio streams are sent.
    * @endif
    * @if Chinese
    * 已接收到远端音频首帧的回调。
    * @param type       音频流类型。
    * @param uid               远端用户 ID，指定是哪个用户的音频流。
    * @endif
    */
    virtual void onFirstAudioDataReceived(NERtcAudioStreamType type, uid_t uid) {
      (void)type;
      (void)uid;
    }
    /**
    * @if English
    * Occurs when the first video frame from a remote user is displayed.
    * <br>If the first video frame from a remote user is displayed in the view, the callback is triggered.
    * @param uid       The ID of a user whose audio streams are sent.
    * @endif
    * @if Chinese
    * 已显示首帧远端视频的回调。
    * 第一帧远端视频显示在视图上时，触发此调用。
    * @param type       视频流类型。
    * @param uid               用户 ID，指定是哪个用户的视频流。
    * @endif
    */
    virtual void onFirstVideoDataReceived(NERtcVideoStreamType type, uid_t uid){
        (void)uid;
        (void)type;
    } 
    /**
    * @if English
    * Occurs when the first audio frame from a remote user is decoded.
    * @param uid       The ID of a remote user whose audio streams are sent.
    * @endif
    * @if Chinese
    * 已解码远端音频首帧的回调。
    * @param uid       远端用户 ID，指定是哪个用户的音频流。
    * @endif
    */
    virtual void onFirstAudioFrameDecoded(NERtcAudioStreamType type, uid_t uid){
        (void)type;
        (void)uid;
    }
    /**
    * @if English
    * Occurs when the remote video is received and decoded.
    * <br>If the engine receives the first frame of remote video streams, the callback is triggered.
    * @param uid       The ID of a user whose audio streams are sent.
    * @param width     The width of video streams (px).
    * @param height    The height of video streams(px).
    * @endif
    * @if Chinese
    * 已接收到远端视频并完成解码的回调。
    * <br>引擎收到第一帧远端视频流并解码成功时，触发此调用。
    * @param type   视频频流类型。
    * @param uid           用户 ID，指定是哪个用户的视频流。
    * @param width         视频流宽（px）。
    * @param height        视频流高（px）。
    * @endif
    */
    virtual void onFirstVideoFrameDecoded(NERtcVideoStreamType type, uid_t uid, uint32_t width, uint32_t height){
        (void)type;
        (void)uid;
        (void)width;
        (void)height;
    } 
    /**
    * @if English
    * Occurs when video data are captured.
    * @param data      The video frame data.
    * @param type      The type of the video data.
    * @param width     The width of the video frame.
    * @param height    The height of the video frame.
    * @param count     Video plane count.
    * @param offset    Video offset.
    * @param stride    Video stride.
    * @param rotation  The video rotation angle.
    * @endif
    * @if Chinese
    * 采集视频数据回调。

    * @param data      采集视频数据。
    * @param type      视频类型。
    * @param width     视频宽度。
    * @param height    视频高度。
    * @param count     视频Plane Count。
    * @param offset    视频offset。
    * @param stride    视频stride。
    * @param rotation  视频旋转角度。
    * @endif
    */
    void onCaptureVideoFrame(
                                             void* data,
                                             NERtcVideoType type,
                                             uint32_t width,
                                             uint32_t height,
                                             uint32_t count,
                                             uint32_t* offset,
                                             uint32_t* stride,
                                             NERtcVideoRotation rotation){
        (void)data;
        (void)type;
        (void)width;
        (void)height;
        (void)count;
        (void)offset;
        (void)stride;
        (void)rotation;
    }
    /**
    * @if English
    * Occurs when the playback state of a local music file changes.
    * <br>If you call the startAudioMixing method to play a mixing music file and the playback state changes, the callback is
    * triggered.
    * - If the playback of the music file ends normally, the state parameter returned in the response contains the corresponding
    * status code kNERtcAudioMixingState_tFinished, and the error_code parameter contains kNERtcAudioMixingErrorOK.
    * - If an error occurs in the playback, the kNERtcAudioMixingState_tFailed status code is returned, and the error_code
    * parameter returned contains the corresponding reason.
    * - If the local music file does not exist, the file format is not supported, or the URL of the online music file cannot be
    * accessed, the error_code parameter returned contains kNERtcAudioMixingErrorCanNotOpen.
    * @param state         The playback state of the music file. For more information, see #NERtcAudioMixingState_t.
    * @param error_code    The error code. For more information, see #NERtcAudioMixingErrorCode_t.
    * @endif
    * @if Chinese
    * 本地用户的音乐文件播放状态改变回调。
    * <br>调用 startAudioMixing 播放混音音乐文件后，当音乐文件的播放状态发生改变时，会触发该回调。
    * - 如果播放音乐文件正常结束，state 会返回相应的状态码 kNERtcAudioMixingState_tFinished，error_code 返回
    * kNERtcAudioMixingErrorOK。
    * - 如果播放出错，则返回状态码 kNERtcAudioMixingState_tFailed，error_code 返回相应的出错原因。
    * - 如果本地音乐文件不存在、文件格式不支持、无法访问在线音乐文件 URL，error_code都会返回 kNERtcAudioMixingErrorCanNotOpen。
    * @param state         音乐文件播放状态，详见 #NERtcAudioMixingState_t.
    * @param error_code    错误码，详见 #NERtcAudioMixingErrorCode_t.
    * @endif
    */
    virtual void onAudioMixingStateChanged(NERtcAudioMixingState state, NERtcAudioMixingErrorCode error_code){
        (void)state;
        (void)error_code;
    }
    /**
    * @if English
    * Occurs when the playback position of a local music file changes.
    * <br>If you call the startAudioMixing method to play a mixing music file and the position of the playing operation changes,
    * the callback is triggered.
    * @param timestamp_ms      The position of the music file playing. Unit: milliseconds.
    * @endif
    * @if Chinese
    * 本地用户的音乐文件播放进度回调。
    * <br>调用 startAudioMixing 播放混音音乐文件后，当音乐文件的播放进度改变时，会触发该回调。
    * @param timestamp_ms      音乐文件播放进度，单位为毫秒
    * @endif
    */
    virtual void onAudioMixingTimestampUpdate(uint64_t timestamp_ms){
        (void)timestamp_ms;
    }
    /**
    * @if English
    * Occurs when the playback position of a local effect file changes.
    * <br>If you call the playEffect method to play a effect file and the position of the playing operation
    * changes, the callback is triggered.
    * @param effect_id      The effect file id.f
    * @param timestamp_ms      The position of the music file playing. Unit: milliseconds.
    * @endif
    * @if Chinese
    * 本地用户的指定音效文件播放进度回调。
    * - 调用 \ref nertc::IRtcEngineEx::playEffect "playEffect"播放音效文件后，SDK 会触发该回调，默认每 1s 返回一次。
    * @since V4.6.29
    * @par 使用前提
    * 请在 IRtcEngineEventHandlerEx 接口类中通过 \ref nertc::IRtcEngine::initialize "initialize" 接口设置回调监听。
    * @par 参数说明
    * <table>
    *  <tr>
    *      <th>**参数名称**</th>
    *      <th>**类型**</th>
    *      <th>**描述**</th>
    *  </tr>
    *  <tr>
    *      <td>effect_id</td>
    *      <td>uint32_t</td>
    *      <td>指定音效文件的 ID。每个音效均有唯一的 ID。</td>
    *  </tr>
    *  <tr>
    *      <td>timestamp_ms</td>
    *      <td>uint64_t</td>
    *      <td>指定音效文件的当前播放进度。单位为毫秒。</td>
    *  </tr>
    * </table> 
    * @endif
    */
    virtual void onAudioEffectTimestampUpdate(uint32_t effect_id, uint64_t timestamp_ms){ 
        (void)effect_id;
        (void)timestamp_ms;
    }
    /**
    * @if English
    * Occurs when the playback of a music file ends.
    * <br>After the audio effect ends the playback, the callback is triggered.
    * @param effect_id         The ID of the specified audio effect. Each audio effect has a unique ID.
    * @endif
    * @if Chinese
    * 本地音效文件播放已结束回调。
    * <br>当播放音效结束后，会触发该回调。
    * @param effect_id         指定音效的 ID。每个音效均有唯一的 ID。
    * @endif
    */
    virtual void onAudioEffectFinished(uint32_t effect_id){
        (void)effect_id;
    }
    /**
    * @if English
    * Occurs when the system prompts current local audio volume.
    * - This callback is disabled by default. You can enable the callback by calling the \ref IRtcEngineEx::enableAudioVolumeIndication "enableAudioVolumeIndication" method.
    * - After the callback is enabled, if a local user speaks, the SDK triggers the callback based on the time interval specified in the \ref IRtcEngineEx::enableAudioVolumeIndication "enableAudioVolumeIndication" method.
    * - If a local user sets a mute by calling \ref IRtcEngineEx::muteLocalAudioStream "muteLocalAudioStream", the SDK sets the value of volume as 0, and calls back to the application layer.
    * @param volume    The volume of audio mixing. Value range: 0 to 100.
    * @param enable_vad  Whether human voice is detected.
    * @endif
    * @if Chinese
    * 提示房间内本地用户瞬时音量的回调。
    * - 该回调默认禁用。可以通过 \ref IRtcEngineEx::enableAudioVolumeIndication "enableAudioVolumeIndication" 方法开启。
    * - 开启后，本地用户说话，SDK 会按  \ref IRtcEngineEx::enableAudioVolumeIndication "enableAudioVolumeIndication" 方法中设置的时间间隔触发该回调。
    * - 如果本地用户将自己静音（调用了 \ref IRtcEngineEx::muteLocalAudioStream "muteLocalAudioStream"），SDK 将音量设置为 0 后回调给应用层。
    * @param volume    （混音后的）音量，取值范围为 [0,100]。
    * @param enable_vad  是否检测到人声。
    * @endif
    */
    virtual void onLocalAudioVolumeIndication(int volume, bool enable_vad){
        (void)volume;
        (void)enable_vad;
    }
    /**
    * @if English
    * Occurs when the system prompts the active speaker and the audio volume.
    * By default, the callback is disabled. You can enable the callback by calling the enableAudioVolumeIndication method. After
    * the callback is enabled, if a local user speaks, the SDK triggers the callback based on the time interval specified in the
    * enableAudioVolumeIndication method. In the array of speakers returned:
    * - If a uid is contained in the array returned in the last response but not in the array returned in the current response.
    * The remote user with the uid does not speak by default.
    * - If the volume is 0, the user does not speak.
    * - If the array is empty, the remote user does not speak.
    * @param speakers          The array that contains the information about user IDs and volumes is NERtcAudioVolumeInfo.
    * @param speaker_number    The size of speakers array, which indicates the number of speakers.
    * @param total_volume      The total volume (after audio mixing). Value range: 0 to 100.
    * @endif
    * @if Chinese
    * 提示房间内谁正在说话及说话者瞬时音量的回调。
    * <br>该回调默认为关闭状态。可以通过 enableAudioVolumeIndication 方法开启。开启后，无论房间内是否有人说话，SDK 都会按
    * enableAudioVolumeIndication 方法中设置的时间间隔触发该回调。 <br>在返回的 speakers 数组中:
    * - 如果有 uid 出现在上次返回的数组中，但不在本次返回的数组中，则默认该 uid 对应的远端用户没有说话。
    * - 如果volume 为 0，表示该用户没有说话。
    *  - 如果speakers 数组为空，则表示此时远端没有人说话。
    * @param speakers          每个说话者的用户 ID 和音量信息的数组: NERtcAudioVolumeInfo
    * @param speaker_number    speakers 数组的大小，即说话者的人数。
    * @param total_volume      （混音后的）总音量，取值范围为 [0,100]。
    * @endif
    */
    virtual void onRemoteAudioVolumeIndication(const NERtcAudioVolumeInfo* speakers,uint32_t speaker_number,int total_volume){
        (void)speakers;
        (void)speaker_number;
        (void)total_volume;
    }
    /**
    * @if English
    * Notifies to add the result of live stream.
    * <br>The callback asynchronously returns the callback result of \ref IRtcEngineEx::addLiveStreamTask "addLiveStreamTask".
    * For information about actual pushing state, see \ref IRtcEngineEventHandlerEx::onLiveStreamState "onLiveStreamState".
    * @param task_id       The ID of a stream-push task.
    * @param url           Task ID.
    * @param error_code    The result.
    * - 0: Success.
    * - Other values: Failure.
    * @endif
    * @if Chinese
    * 通知添加直播任务结果。
    * <br>该回调异步返回 \ref IRtcEngineEx::addLiveStreamTask "addLiveStreamTask" 接口的调用结果；实际推流状态参考 \ref
    * IRtcEngineEventHandlerEx::onLiveStreamState "onLiveStreamState"
    * @param task_id       任务id
    * @param url           推流地址
    * @param error_code    结果
    * - 0: 调用成功；
    * - 其他: 调用失败。
    * @endif
    */
    virtual void onAddLiveStreamTask(const char* task_id, const char* url, int error_code) {
        (void)task_id;
        (void)url;
        (void)error_code;
    }
    /**
    * @if English
    * Notifies to Updates the result of live stream.
    * <br>The callback asynchronously returns the callback result of ref IRtcEngineEx::addLiveStreamTask "addLiveStreamTask". For
    * information about actual pushing state, see \ref IRtcEngineEventHandlerEx::onLiveStreamState "onLiveStreamState".
    * @param task_id       The ID of a stream-push task.
    * @param url           The URL for the streaming task.
    * @param error_code    The result.
    * - 0: Success.
    * - Other values: Failure.
    * @endif
    * @if Chinese
    * 通知更新直播任务结果。
    * 该回调异步返回 \ref IRtcEngineEx::updateLiveStreamTask "updateLiveStreamTask" 接口的调用结果；实际推流状态参考 \ref
    * IRtcEngineEventHandlerEx::onLiveStreamState "onLiveStreamState"
    * @param task_id       任务id
    * @param url           推流地址
    * @param error_code    结果
    * - 0: 调用成功；
    * - 其他: 调用失败。
    * @endif
    */
    virtual void onUpdateLiveStreamTask(const char* task_id, const char* url, int error_code){
        (void)task_id;
        (void)url;
        (void)error_code;
    }
    /**
    * @if English
    * Notifies to delete the result of live stream.
    * <br>The callback asynchronously returns the callback result of ref IRtcEngineEx::addLiveStreamTask "addLiveStreamTask". For
    * information about actual pushing state, see \ref IRtcEngineEventHandlerEx::onLiveStreamState "onLiveStreamState".
    * @param task_id       The ID of a task.
    * @param error_code    The result.
    * - 0: Success.
    * - Other values: Failure.
    * @endif
    * @if Chinese
    * 通知删除直播任务结果。
    * <br>该回调异步返回 \ref IRtcEngineEx::removeLiveStreamTask "removeLiveStreamTask" 接口的调用结果；实际推流状态参考 \ref
    * IRtcEngineEventHandlerEx::onLiveStreamState "onLiveStreamState"
    *  @param task_id      任务id
    * @param error_code    结果
    * - 0: 调用成功；
    * - 其他: 调用失败。
    * @endif
    */
    virtual void onRemoveLiveStreamTask(const char* task_id, int error_code){
        (void)task_id;
        (void)error_code;
    }
    /**
    * @if English
    * Notifies the status in live stream-pushing.
    * @note The callback is valid in a call.
    * @param task_id       The ID of a task.
    * @param url           The URL for the streaming task.
    * @param state         #NERtcLiveStreamStateCode The state of live stream-pushing.
    * - 505: Pushing.
    * - 506: Pushing fails.
    * - 511: Pushing ends.
    * @endif
    * @if Chinese
    * 通知直播推流状态
    * @note 该回调在通话中有效。
    * @param task_id       任务id
    * @param url           推流地址
    * @param state         #NERtcLiveStreamStateCode, 直播推流状态
    * - 505: 推流中；
    * - 506: 推流失败；
    * - 511: 推流结束；
    * @endif
    */
    virtual void onLiveStreamStateChanged(const char* task_id, const char* url, NERtcLiveStreamStateCode state){
        (void)task_id;
        (void)url;
        (void)state;
    }
    /**
    * @if English
    * Occurs when howling is detected.
    * When the distance between the sound source and the PA equipment is too close, howling may occur. The NERTC SDK supports the
    * howling detection. When a howling signal is detected, the callback is automatically triggered until the howling stops. The
    * application layer can prompt the user to mute the microphone or directly mute the microphone when the app receives the
    * howling information returned by the callback.
    * @note
    * Howling detection is used in audio-only scenarios, such as audio chat rooms or online meetings. We recommend that you do
    * not use howling detection in entertainment scenes that include background music.
    * @param howling       Whether a howling occurs.
    * - true: Howling occurs.
    * - false: Normal state.
    * @endif
    * @if Chinese
    * 检测到啸叫回调。
    * <br>当声源与扩音设备之间因距离过近时，可能会产生啸叫。NERTC SDK
    * 支持啸叫检测，当检测到有啸叫信号产生的时候，自动触发该回调直至啸叫停止。App
    * 应用层可以在收到啸叫回调时，提示用户静音麦克风，或直接静音麦克风。
    * @note
    * 啸叫检测功能一般用于语音聊天室或在线会议等纯人声环境，不推荐在包含背景音乐的娱乐场景中使用。
    * @param howling       是否出现啸叫
    * - true: 啸叫。
    * - false: 正常。
    * @endif
    */
    virtual void onAudioHowling(bool howling){
        (void)howling;
    }
    /**
    * @if English
    * Occurs when the content of remote SEI is received.
    * <br>After a remote client successfully sends SEI, the local client receives a message returned by the callback.
    * @param[in] uid       The ID of the user who sends the SEI.
    * @param[in] data      The received SEI data.
    * @param[in] dataSize  The size of received SEI data.
    * @endif
    * @if Chinese
    * 收到远端流的 SEI 内容回调。
    * <br>当远端成功发送 SEI 后，本端会收到此回调。
    * @param[in] uid       发送该 sei 的用户 id
    * @param[in] data      接收到的 sei 数据
    * @param[in] dataSize  接收到 sei 数据的大小
    * @endif
    */
    virtual void onRecvSEIMsg(uid_t uid, const uint8_t* data, uint32_t dataSize){
        (void)uid;
        (void)data;
        (void)dataSize;
    }
    /**
    * @if English
    * Returns the audio recording state.
    *  @param code         The status code of the audio recording. For more information, see NERtcAudioRecordingCode.
    * @param file_path     The path based on which the recording file is stored.
    * @endif
    * @if Chinese
    * 音频录制状态回调。
    * @param code          音频录制状态码。详细信息请参考 NERtcAudioRecordingCode。
    * @param file_path     音频录制文件保存路径。
    * @endif
    */
    virtual void onAudioRecording(NERtcAudioRecordingCode code, const char* file_path){
        (void)code;
        (void)file_path;
    }
    /**
    * @if English
    * Occurs when the state of the media stream is relayed.
    * @since V4.3.0
    * @param state         The state of the media stream.
    * @param channel_name  The name of the destination room where the media streams are relayed.
    * @endif
    * @if Chinese
    * 跨房间媒体流转发状态发生改变回调。
    * @since V4.3.0
    * @param state         当前跨房间媒体流转发状态。详细信息请参考 #NERtcChannelMediaRelayState
    * @param channel_name  媒体流转发的目标房间名。
    * @endif
    */
    virtual void onMediaRelayStateChanged(NERtcChannelMediaRelayState state, const char* channel_name){
        (void)state;
        (void)channel_name;
    }
    /**
    * @if English
    * Occurs when events related to media stream relay are triggered.
    * @since V4.3.0
    * @param event         The media stream relay event.
    * @param channel_name  The name of the destination room where the media streams are relayed.
    * @param error         Specific error codes.
    * @endif
    * @if Chinese
    * 媒体流相关转发事件回调。
    * @since V4.3.0
    * @param event         当前媒体流转发事件。详细信息请参考 #NERtcChannelMediaRelayEvent 。
    * @param channel_name  转发的目标房间名。
    * @param error         相关错误码。详细信息请参考 #NERtcErrorCode_t 。
    * @endif
    */
    virtual void onMediaRelayEvent(NERtcChannelMediaRelayEvent event,const char* channel_name, NERtcErrorCode error){
        (void)event;
        (void)channel_name;
        (void)error;
    }
    /**
    * @if English
    * Occurs when the published local media stream falls back to an audio-only stream due to poor network conditions or switches
    * back to audio and video stream after the network conditions improve. <br>If you call setLocalPublishFallbackOption and set
    * option to #kNERtcStreamFallbackAudioOnly, this callback is triggered when the locally published stream falls back to
    * audio-only mode due to poor uplink network conditions, or when the audio stream switches back to the audio and video stream
    * after the uplink network conditions improve.
    * @since V4.3.0
    * @param is_fallback   The locally published stream falls back to audio-only mode or switches back to audio and video stream.
    * - true: The published stream from a local client falls back to audio-only mode due to poor uplink network conditions.
    * - false: The audio stream switches back to the audio and video stream after the upstream network condition improves.
    * @param type   The type of the video stream, such as mainstream and substream.
    * @endif
    * @if Chinese
    * 本地发布流已回退为音频流、或已恢复为音视频流回调。
    * <br>如果您调用了设置本地推流回退选项 setLocalPublishFallbackOption 接口，并将 option 设置为 #kNERtcStreamFallbackAudioOnly
    * 后，当上行网络环境不理想、本地发布的媒体流回退为音频流时，或当上行网络改善、媒体流恢复为音视频流时，会触发该回调。
    * @since V4.3.0
    * @param is_fallback   本地发布流已回退或已恢复。
    * - true： 由于网络环境不理想，发布的媒体流已回退为音频流。
    * - false：由于网络环境改善，从音频流恢复为音视频流。
    * @param type   对应的视频流类型，即主流或辅流。
    * @endif
    */
    virtual void onPublishFallbackToAudioOnly(bool is_fallback, NERtcVideoStreamType type){
        (void)is_fallback;
        (void)type;
    }
    /**
    * @if English
    * Occurs when the subscribed remote media stream falls back to an audio-only stream due to poor network conditions or
    * switches back to the audio and video stream after the network condition improves. <br>If you call
    * setLocalPublishFallbackOption and set option to #kNERtcStreamFallbackAudioOnly, this callback is triggered when the locally
    * published stream falls back to audio-only mode due to poor uplink network conditions, or when the audio stream switches
    * back to the audio and video stream after the uplink network condition improves.
    * @since V4.3.0
    * @param uid           The ID of a remote user.
    * @param is_fallback   The subscribed remote media stream falls back to audio-only mode or switches back to the audio and
    * video stream.
    * - true: The subscribed remote media stream falls back to audio-only mode due to poor downstream network conditions.
    * - false: The subscribed remote media stream switches back to the audio and video stream after the downstream network
    * condition improves.
    * @param type   The type of the video stream, such as mainstream and substream.
    * @endif
    * @if Chinese
    * 订阅的远端流已回退为音频流、或已恢复为音视频流回调。
    * <br>如果你调用了设置远端订阅流回退选项 setRemoteSubscribeFallbackOption 接口并将 option 设置 #kNERtcStreamFallbackAudioOnly
    * 后，当下行网络环境不理想、仅接收远端音频流时，或当下行网络改善、恢复订阅音视频流时，会触发该回调。
    * @since V4.3.0
    * @param uid           远端用户的 ID。
    * @param is_fallback   远端订阅流已回退或恢复：
    * - true： 由于网络环境不理想，订阅的远端流已回退为音频流。
    * - false：由于网络环境改善，订阅的远端流从音频流恢复为音视频流。
    * @param type   对应的视频流类型，即主流或辅流。
    * @endif
    */
    virtual void onSubscribeFallbackToAudioOnly(uid_t uid, bool is_fallback, NERtcVideoStreamType type){
        (void)uid;
        (void)is_fallback;
        (void)type;
    }
    /**
    * @if English
    * Reports the last mile network quality of the local user once every two seconds before the user joins the channel.
    * <br> After the application calls the startLastmileProbeTest method, this callback reports once every five seconds the
    * uplink and downlink last mile network conditions of the local user before the user joins the channel.
    * @since V4.5.0
    * @param quality       The last mile network quality.
    * @endif
    * @if Chinese
    * 通话前网络上下行 last mile 质量状态回调。
    * <br>该回调描述本地用户在加入房间前的 last mile
    * 网络探测的结果，以打分形式描述上下行网络质量的主观体验，您可以通过该回调预估本地用户在音视频通话中的网络体验。 <br>在调用
    * startLastmileProbeTest 之后，SDK 会在约 5 秒内返回该回调。
    * @since V4.5.0
    * @param quality       网络上下行质量，基于上下行网络的丢包率和抖动计算，探测结果主要反映上行网络的状态。
    * @endif
    */
    virtual void onLastmileQuality(NERtcNetworkQualityType quality){ 
        (void)quality;
    }
    /**
    * @if English
    * Reports the last-mile network probe result.
    * <br>This callback describes a detailed last-mile network detection report of a local user before joining a channel. The
    * report provides objective data about the upstream and downstream network quality, including network jitter and packet loss
    * rate.  You can use the report to objectively predict the network status of local users during an audio and video call.
    * <br>The SDK triggers this callback within 30 seconds after the app calls the startLastmileProbeTest method.
    * @since V4.5.0
    * @param result        The uplink and downlink last-mile network probe test result.
    * @endif
    * @if Chinese
    * 通话前网络上下行 Last mile 质量探测报告回调。
    * <br>该回调描述本地用户在加入房间前的 last mile
    * 网络探测详细报告，报告中通过客观数据反馈上下行网络质量，包括网络抖动、丢包率等数据。您可以通过该回调客观预测本地用户在音视频通话中的网络状态。
    * <br>在调用 startLastmileProbeTest 之后，SDK 会在约 30 秒内返回该回调。
    * @since V4.5.0
    * @param result        上下行 Last mile 质量探测结果。
    * @endif
    */
    virtual void onLastmileProbeResult(const NERtcLastmileProbeResult& result){ 
        (void)result; 
    }
    /**
    * @if English
    * Audio/Video Callback when banned by server.
    * @since v4.6.0
    * @param isAudioBannedByServer indicates whether to ban the audio.
    * - true: banned
    * - false unbanned
    * @param isVideoBannedByServer indicates whether to ban the video.
    * - true: banned
    * - false unbanned
    * @endif
    * @if Chinese
    * 服务端禁言音视频权限变化回调。
    * @since v4.6.0
    * @param is_audio_banned 是否禁用音频。
    * - true：禁用音频。
    * - false：取消禁用音频。
    * @param is_video_banned 是否禁用视频。
    * - true：禁用视频。
    * - false：取消禁用视频。
    * @endif
    */
    virtual void onMediaRightChange(bool is_audio_banned, bool is_video_banned){
        (void)is_audio_banned;
        (void)is_video_banned;
    }
    /**
    * @if English
    * Gets notified if the audio driver plug-in is installed (only for Mac)
    * <br> You can call {@link checkNECastAudioDriver} to install the audio driver plug-in and capture and play audio data in the Mac system
    * @param  result indicates the result of audio driver plug-in installation. For more information, see {@link NERtcInstallCastAudioDriverResult}.
    * @endif
    * @if Chinese
    * 收到检测安装声卡的内容回调（仅适用于 Mac 系统）。
    * <br> 在 Mac 系统上，您可以通过调用 checkNECastAudioDriver 为当前系统安装一个音频驱动，并让 SDK 通过该音频驱动捕获当前 Mac 系统播放出的声音。
    * @param  result 安装虚拟声卡的结果。详细信息请参考 {@link NERtcInstallCastAudioDriverResult}。
    * @endif
    */
    virtual void onCheckNECastAudioDriverResult(NERtcInstallCastAudioDriverResult result){
        (void)result;
    }
    
    /**
    * @if English
    * Reports whether the virtual background is successfully enabled. (beta feature)
    * @since v4.6.0
    * After you call \ref IRtcEngine::enableVirtualBackground "enableVirtualBackground", the SDK triggers this callback
    * to report whether the virtual background is successfully enabled.
    * @note If the background image customized in the virtual background is in PNG or JPG format, the triggering of this
    * callback is delayed until the image is read.
    * @param enabled Whether the virtual background is successfully enabled:
    * - true: The virtual background is successfully enabled.
    * - false: The virtual background is not successfully enabled.
    * @param reason The reason why the virtual background is not successfully enabled or the message that confirms
    * success. See #NERtcVirtualBackgroundSourceStateReason.
    * @endif
    * @if Chinese
    * 通知虚拟背景功能是否成功启用的回调。
    * <br> 调用 \ref IRtcEngineEx::enableVirtualBackground "enableVirtualBackground" 方法后，SDK 返回此回调通知虚拟背景功能是否成功启用。
    * @since V4.6.0
    * @note 如果您设置虚拟背景为 PNG 或 JPG 格式的自定义图像，此回调会等到图像被完全读取后才会返回，因此会有一段时间的延迟。
    * @param enabled 是否成功启用虚拟背景。
    * - true：成功启用。
    * - false：未成功启用。
    * @param reason 虚拟背景功能未成功启用的原因或成功启用虚拟背景功能的通知。详细信息请参考 {@link NERtcVirtualBackgroundSourceStateReason}。
    * @endif
    */
    virtual void onVirtualBackgroundSourceEnabled(bool enabled, NERtcVirtualBackgroundSourceStateReason reason){
      (void)enabled;
      (void)reason;
    }
    
    /**
    * @if English
    * Occurs when the local video watermark takes affect.
    * <br>If you enables the local video watermark by calling \ref nertc::IRtcEngineEx::setLocalVideoWatermarkConfigs "setLocalVideoWatermarkConfigs", the SDK will trigger this callback.
    * @since V4.6.10
    * @param videoStreamType Type of video stream, main stream or substream. For more information, see {@link video.NERtcVideoStreamType}.
    * @param state           Watermark status. For more information, see {@link NERtcConstants.NERtcLocalVideoWatermarkState}.
    * @endif
    * @if Chinese
    * 本地视频水印生效结果回调。
    * <br>调用 \ref nertc::IRtcEngineEx::setLocalVideoWatermarkConfigs "setLocalVideoWatermarkConfigs" 接口启用本地视频水印后，SDK 会触发此回调。
    * @since V4.6.10
    * @param type 对应的视频流类型，即主流或辅流。详细信息请参考 {@link NERtcVideoStreamType}。
    * @param state           水印状态。详细信息请参考 {@link NERtcLocalVideoWatermarkState}。
    * @endif
    */
    virtual void onLocalVideoWatermarkState(NERtcVideoStreamType type, NERtcLocalVideoWatermarkState state){
        (void)type;
        (void)state;
    }

    /**
    * @if English
    * The right key is about to expire.
    * Because the PermissionKey has a certain time effect, if the PermissionKey is about to expire during a call, the SDK
    * will trigger the callback in advance to remind the App to update the Token.
    * When receiving the callback, the user needs to regenerate a new PermissionKey on the server,
    * and then call ref IRtcEngineEx:: updatePermissionKey "updatePermissionKey" to transfer the newly generated PermissionKey to the SDK.
    * @param key      Permission key value.
    * @param error    Relevant error code. Please refer to # NERtcErrorCode for details.
    * @param timeout  Timeout, in seconds, valid when successful.
    * @endif
    * @if Chinese
    * 权限密钥即将过期事件回调。
    * - 由于 PermissionKey 具有一定的时效，在通话过程中如果 PermissionKey 即将失效，SDK 会提前 30 秒触发该回调，提醒用户更新 PermissionKey。
    * @since V4.6.29
    * @par 使用前提
    * 请在 IRtcEngineEventHandlerEx 接口类中通过 \ref IRtcEngine::initialize "initialize" 接口设置回调监听。
    * @par 相关接口
    * 在收到此回调后可以调用 \ref IRtcEngineEx::updatePermissionKey "updatePermissionKey" 方法更新权限密钥。
    * @endif
    */
    virtual void onPermissionKeyWillExpire(){}

    /**
    * @if English
    * Update authority key event callback.
    * @param key      Permission key value.
    * @param error    Relevant error code. Please refer to # NERtcErrorCode for details.
    * @param timeout  Timeout, in seconds, valid when successful.
    * @endif
    * @if Chinese
    * 更新权限密钥事件回调。
    * - 调用 \ref IRtcEngineEx::updatePermissionKey "updatePermissionKey"  方法主动更新权限密钥后，SDK 会触发该回调，返回权限密钥更新的结果。
    * @since V4.6.29
    * @par 使用前提
    * 请在 IRtcEngineEventHandlerEx 接口类中通过 \ref IRtcEngine::initialize "initialize" 接口设置回调监听。
    * @par 参数说明
    * <table>
    *  <tr>
    *      <th>**参数名称**</th>
    *      <th>**类型**</th>
    *      <th>**描述**</th>
    *  </tr>
    *  <tr>
    *      <td>key</td>
    *      <td>const char*</td>
    *      <td>新的权限密钥。</td>
    *  </tr>
    *  <tr>
    *      <td>error</td>
    *      <td> \ref nertc::NERtcErrorCode "NERtcErrorCode" </td>
    *      <td>错误码。<ul><li>kNERtcErrChannelPermissionKeyError（30901）：权限密钥错误。<li>kNERtcErrChannelPermissionKeyTimeout（30902）：权限密钥超时。</td>
    *  </tr>
    *  <tr>
    *      <td>timeout</td>
    *      <td>int</td>
    *      <td>更新后的权限密钥剩余有效时间。单位为秒。</td>
    *  </tr>
    * </table> 
    * @endif
    */
    virtual void onUpdatePermissionKey(const char* key, NERtcErrorCode error, int timeout){
        (void)key;
        (void)error;
        (void)timeout;
    }
  
    /**
    * @if English
    * Occurs when a remote user send data by data channel.
    * @param uid           The ID of a remote user.
    * @param data    The received data channel data.
    * @param size      The size of received data channel data.
    * @endif
    * @if Chinese
    * 远端用户通过数据通道发送数据的回调。
    * @param uid       远端用户ID。
    * @param source_id 远端source ID。
    * @param data     数据。
    * @param size      接收数据长度。
    * @endif
    */
    virtual void onUserDataReceiveMessage(uid_t uid, const char* source_id, void* data, uint64_t size){
        (void)uid;
        (void)data;
        (void)size;
    }
      
    /**
    * @if English
    * Occurs when a remote user enables data channel.
    * @param uid           The ID of a remote user.
    * @since V5.0.0
    * @endif
    * @if Chinese
    * 远端用户开启数据通道的回调。
    * @param uid           远端用户ID。
    * @since V5.0.0
    * @endif
    */
    virtual void onUserDataStart(uid_t uid){
        (void)uid;
    }
    
    /**
    * @if English
    * Occurs when a remote user disables data channel.
    * @param uid           The ID of a remote user.
    * @endif
    * @if Chinese
    * 远端用户停用数据通道的回调。
    * @param uid           远端用户ID。
    * @endif
    */
    virtual void onUserDataStop(uid_t uid){
        (void)uid;
    }
    
    /**
    * @if English
    * Occurs when a Remote user data channel status changed.
    * @param uid           The ID of a remote user.
    * @param source_id     The source id.
    * @endif
    * @if Chinese
    * 远端用户数据通道状态变更回调。
    * @param uid           远端用户ID。
    * @param source_id     远端用户source ID。
    * @endif
    */
    virtual void onUserDataStateChanged(uid_t uid, const char* source_id){
        (void)uid;
        (void)source_id;
    }
    
    /**
    * @if English
    * Occurs when a Remote user data channel buffer amount changed.
    * @param uid             The ID of a remote user.
    * @param source_id     The source id.
    * @param previousAmount  The amount before changed.
    * @endif
    * @if Chinese
    * 远端用户数据通道buffer变更回调。
    * @param uid             远端用户ID。
    * @param source_id     远端用户source ID。
    * @param previousAmount  变更前大小。
    * @endif
    */
    virtual void onUserDataBufferedAmountChanged(uid_t uid, const char* source_id, uint64_t previous_amount){
        (void)uid;
        (void)source_id;
        (void)previous_amount;
    }
};
}  // namespace nertc
