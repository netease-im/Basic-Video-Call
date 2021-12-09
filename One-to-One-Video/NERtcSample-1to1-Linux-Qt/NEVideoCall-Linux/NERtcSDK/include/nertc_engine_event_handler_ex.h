/** @file nertc_engine_event_handler_ex.h
* @brief The interface header file of expansion callback of the NERTC SDK.
* All parameter descriptions of the NERTC SDK. All string-related parameters (char *) are encoded in UTF-8.
* @copyright (c) 2021, NetEase Inc. All rights reserved.
*/

#ifndef NERTC_ENGINE_EVENT_HANDLER_EX_H
#define NERTC_ENGINE_EVENT_HANDLER_EX_H

#include "nertc_base_types.h"
#include "nertc_engine_defines.h"
#include "nertc_engine_event_handler.h"

 /**
 * @namespace nertc
 * @brief namespace nertc
 */
namespace nertc
{
/** 
 * @if English
 * IRtcEngineEventHandlerEx callback interface class is used to send callback event notifications to the app from SDK. The app gets event notifications from the SDK through inheriting the interface class.
 * <br>All methods in this interface class have their (empty) default implementations, and the application can inherit only some of the required events instead of all of them. When calling a callback method, the application must not implement time-consuming operations or call blocking-triggered APIs. For example, if you want to enable audio and video, the SDK may be affected in the runtime.
 * @endif
 * @if Chinese
 * IRtcEngineEventHandlerEx 回调扩展接口类用于 SDK 向 App 发送回调事件通知，App 通过继承该接口类的方法获取 SDK 的事件通知。
 * <br>接口类的所有方法都有缺省（空）实现，App 可以根据需要只继承关心的事件。在回调方法中，App 不应该做耗时或者调用可能会引起阻塞的 API（如开启音频或视频等），否则可能影响 SDK 的运行。
 * @endif
 */
class IRtcEngineEventHandlerEx : public IRtcEngineEventHandler
{
public:
    virtual ~IRtcEngineEventHandlerEx() {}

    /** 
     * @if English
     * Occurs when a remote user enables screen sharing by using the substream.
     * @param uid           The ID of a remote user.
     * @param max_profile   The largest resolution of the remote video.
     * 
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 远端用户开启屏幕共享辅流通道的回调。
     * @param uid           远端用户 ID。
     * @param max_profile   最大分辨率。
     * @endif
     */
    virtual void onUserSubStreamVideoStart(uid_t uid, NERtcVideoProfileType max_profile) {
        (void)uid;
        (void)max_profile;
    }
    /** 
     * @if English
     * Occurs when a remote user stops screen sharing by using the substream.
     * @param uid   The ID of a remote user.
     * 
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 远端用户停止屏幕共享辅流通道的回调。
     * @param uid   远端用户ID。
     * @endif
     */
    virtual void onUserSubStreamVideoStop(uid_t uid) {
        (void)uid;
    }

    /** 
     * @if English
     * Occurs when screen sharing is paused/resumed/started/ended. 
     * <br>The method applies to Windows only.
     * @since V4.2.0
     * @param status    Screen capture status. For more information, see #NERtcScreenCaptureStatus.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 屏幕共享状态变化回调。
     * <br>该方法仅适用于 Windows 平台。
     * @since V4.2.0
     * @param status    屏幕共享状态。详细信息请参考 #NERtcScreenCaptureStatus 。
     * @endif
     */
    virtual void onScreenCaptureStatus(NERtcScreenCaptureStatus status) {}
    
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
     * @param uid       远端用户ID。
     * @param mute      是否静音。
     * @endif
     */
    virtual void onUserAudioMute(uid_t uid, bool mute) {
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
     * @param uid       远端用户ID。
     * @param mute      是否禁视频流。
     * @endif
     */
    virtual void onUserVideoMute(uid_t uid, bool mute) {
        (void)uid;
        (void)mute;
    }

    /** 
     * @if English
     * Occurs when the state of the audio device changes.
     * @param device_id    Device ID.
     * @param device_type  The type of the device. For more information, see NERtcAudioDeviceType.
     * @param device_state The state of the audio device.
     * @endif
     * @if Chinese
     * 音频设备状态更改的回调。
     * @param device_id     设备ID。
     * @param device_type   音频设备类型。详细信息请参考 NERtcAudioDeviceType。
     * @param device_state  音频设备状态。
     * @endif
     */
    virtual void onAudioDeviceStateChanged(const char device_id[kNERtcMaxDeviceIDLength],
        NERtcAudioDeviceType device_type,
        NERtcAudioDeviceState device_state) {
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
    virtual void onAudioDefaultDeviceChanged(const char device_id[kNERtcMaxDeviceIDLength],
        NERtcAudioDeviceType device_type) {
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
    virtual void onVideoDeviceStateChanged(const char device_id[kNERtcMaxDeviceIDLength],
        NERtcVideoDeviceType device_type,
        NERtcVideoDeviceState device_state) {
        (void)device_id;
        (void)device_type;
        (void)device_state;
    }

    /** 
     * @if English
     * Occurs when the first audio frame from a remote user is received.
     * @param uid       The ID of a remote user whose audio streams are sent. 
     * @endif
     * @if Chinese
     * 已接收到远端音频首帧的回调。
     * @param uid       远端用户 ID，指定是哪个用户的音频流。 
     * @endif
     */
    virtual void onFirstAudioDataReceived(uid_t uid) {
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
     * @param uid       用户 ID，指定是哪个用户的视频流。
     * @endif
     */
    virtual void onFirstVideoDataReceived(uid_t uid) {
        (void)uid;
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
    virtual void onFirstAudioFrameDecoded(uid_t uid) {
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
     * @param uid       用户 ID，指定是哪个用户的视频流。
     * @param width     视频流宽（px）。
     * @param height    视频流高（px）。
     * @endif
     */
    virtual void onFirstVideoFrameDecoded(uid_t uid, uint32_t width, uint32_t height) {
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
     * @note Linux 暂不支持
     * 
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
    virtual void onCaptureVideoFrame(void *data,
        NERtcVideoType type, 
        uint32_t width, 
        uint32_t height,
        uint32_t count,
        uint32_t offset[kNERtcMaxPlaneCount],
        uint32_t stride[kNERtcMaxPlaneCount],
        NERtcVideoRotation rotation) {
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
     * <br>If you call the startAudioMixing method to play a mixing music file and the playback state changes, the callback is triggered.
     * - If the playback of the music file ends normally, the state parameter returned in the response contains the corresponding status code kNERtcAudioMixingStateFinished, and the error_code parameter contains kNERtcAudioMixingErrorOK.
     * - If an error occurs in the playback, the kNERtcAudioMixingStateFailed status code is returned, and the error_code parameter returned contains the corresponding reason.
     * - If the local music file does not exist, the file format is not supported, or the URL of the online music file cannot be accessed, the error_code parameter returned contains kNERtcAudioMixingErrorCanNotOpen.
     * @param state         The playback state of the music file. For more information, see #NERtcAudioMixingState.
     * @param error_code    The error code. For more information, see #NERtcAudioMixingErrorCode.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 本地用户的音乐文件播放状态改变回调。
     * <br>调用 startAudioMixing 播放混音音乐文件后，当音乐文件的播放状态发生改变时，会触发该回调。
     * - 如果播放音乐文件正常结束，state 会返回相应的状态码 kNERtcAudioMixingStateFinished，error_code 返回 kNERtcAudioMixingErrorOK。
     * - 如果播放出错，则返回状态码 kNERtcAudioMixingStateFailed，error_code 返回相应的出错原因。
     * - 如果本地音乐文件不存在、文件格式不支持、无法访问在线音乐文件 URL，error_code都会返回 kNERtcAudioMixingErrorCanNotOpen。
     * @param state         音乐文件播放状态，详见 #NERtcAudioMixingState.
     * @param error_code    错误码，详见 #NERtcAudioMixingErrorCode.
    * @endif
    */
    virtual void onAudioMixingStateChanged(NERtcAudioMixingState state, NERtcAudioMixingErrorCode error_code) {
        (void)state;
        (void)error_code;
    }

    /** 
     * @if English
     * Occurs when the playback position of a local music file changes.
     * <br>If you call the startAudioMixing method to play a mixing music file and the position of the playing operation changes, the callback is triggered. 
     * @param timestamp_ms      The position of the music file playing. Unit: milliseconds. 
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 本地用户的音乐文件播放进度回调。
     * <br>调用 startAudioMixing 播放混音音乐文件后，当音乐文件的播放进度改变时，会触发该回调。
     * @param timestamp_ms      音乐文件播放进度，单位为毫秒
    * @endif
    */
    virtual void onAudioMixingTimestampUpdate(uint64_t timestamp_ms) {
        (void)timestamp_ms;
    }

    /** 
     * @if English
     * Occurs when the playback of a music file ends.
     * <br>After the audio effect ends the playback, the callback is triggered.
     * @param effect_id         The ID of the specified audio effect. Each audio effect has a unique ID.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 本地音效文件播放已结束回调。
     * <br>当播放音效结束后，会触发该回调。
     * @param effect_id         指定音效的 ID。每个音效均有唯一的 ID。
    * @endif
    */
    virtual void onAudioEffectFinished(uint32_t effect_id) {
        (void)effect_id;
    }

    /** 
     * @if English
     * Occurs when the system prompts current local audio volume.
     * - This callback is disabled by default. You can enable the callback by calling the \ref IRtcEngineEx::enableAudioVolumeIndication "enableAudioVolumeIndication" method.
     * - After the callback is enabled, if a local user speaks, the SDK triggers the callback based on the time interval specified in the \ref IRtcEngineEx::enableAudioVolumeIndication "enableAudioVolumeIndication" method.
     * - If a local user sets a mute by calling \ref IRtcEngineEx::muteLocalAudioStream "muteLocalAudioStream", the SDK sets the value of volume as 0, and calls back to the application layer. 
     * @param volume    The volume of audio mixing. Value range: 0 to 100.
     * @endif
     * @if Chinese
     * 提示房间内本地用户瞬时音量的回调。
     * - 该回调默认禁用。可以通过 \ref IRtcEngineEx::enableAudioVolumeIndication "enableAudioVolumeIndication" 方法开启。
     * - 开启后，本地用户说话，SDK 会按  \ref IRtcEngineEx::enableAudioVolumeIndication "enableAudioVolumeIndication" 方法中设置的时间间隔触发该回调。
     * - 如果本地用户将自己静音（调用了 \ref IRtcEngineEx::muteLocalAudioStream "muteLocalAudioStream"），SDK 将音量设置为 0 后回调给应用层。
     * @param volume    （混音后的）音量，取值范围为 [0,100]。
     * @endif
     */
    virtual void onLocalAudioVolumeIndication(int volume) {
        (void)volume;
    }

    /** 
     * @if English
     * Occurs when the system prompts the active speaker and the audio volume.
     * By default, the callback is disabled. You can enable the callback by calling the enableAudioVolumeIndication method. After the callback is enabled, if a local user speaks, the SDK triggers the callback based on the time interval specified in the enableAudioVolumeIndication method.
     * In the array of speakers returned:
     * - If a uid is contained in the array returned in the last response but not in the array returned in the current response. The remote user with the uid does not speak by default.
     * - If the volume is 0, the user does not speak. 
     * - If the array is empty, the remote user does not speak.
     * @param speakers          The array that contains the information about user IDs and volumes is NERtcAudioVolumeInfo.
     * @param speaker_number    The size of speakers array, which indicates the number of speakers. 
     * @param total_volume      The total volume (after audio mixing). Value range: 0 to 100. 
     * @endif
     * @if Chinese
     * 提示房间内谁正在说话及说话者瞬时音量的回调。
     * <br>该回调默认为关闭状态。可以通过 enableAudioVolumeIndication 方法开启。开启后，无论房间内是否有人说话，SDK 都会按 enableAudioVolumeIndication 方法中设置的时间间隔触发该回调。
     * <br>在返回的 speakers 数组中:
     * - 如果有 uid 出现在上次返回的数组中，但不在本次返回的数组中，则默认该 uid 对应的远端用户没有说话。
     * - 如果volume 为 0，表示该用户没有说话。
     *  - 如果speakers 数组为空，则表示此时远端没有人说话。
     * @param speakers          每个说话者的用户 ID 和音量信息的数组: NERtcAudioVolumeInfo
     * @param speaker_number    speakers 数组的大小，即说话者的人数。
     * @param total_volume      （混音后的）总音量，取值范围为 [0,100]。
     * @endif
     */
    virtual void onRemoteAudioVolumeIndication(const NERtcAudioVolumeInfo *speakers, unsigned int speaker_number, int total_volume) {
        (void)speakers;
        (void)speaker_number;
        (void)total_volume;
    }

    /** 
     * @if English
     * Notifies to add the result of live stream. 
     * <br>The callback asynchronously returns the callback result of \ref IRtcEngineEx::addLiveStreamTask "addLiveStreamTask".  For information about actual pushing state, see \ref IRtcEngineEventHandlerEx::onLiveStreamState "onLiveStreamState".
     * @param task_id       The ID of a stream-push task. 
     * @param url           Task ID. 
     * @param error_code    The result. 
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 通知添加直播任务结果。
     * <br>该回调异步返回 \ref IRtcEngineEx::addLiveStreamTask "addLiveStreamTask" 接口的调用结果；实际推流状态参考 \ref IRtcEngineEventHandlerEx::onLiveStreamState "onLiveStreamState"
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
     * <br>The callback asynchronously returns the callback result of ref IRtcEngineEx::addLiveStreamTask "addLiveStreamTask". For information about actual pushing state, see \ref IRtcEngineEventHandlerEx::onLiveStreamState "onLiveStreamState".
     * @param task_id       The ID of a stream-push task.
     * @param url           The URL for the streaming task.
     * @param error_code    The result.
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 通知更新直播任务结果。
     * 该回调异步返回 \ref IRtcEngineEx::updateLiveStreamTask "updateLiveStreamTask" 接口的调用结果；实际推流状态参考 \ref IRtcEngineEventHandlerEx::onLiveStreamState "onLiveStreamState"
     * @param task_id       任务id
     * @param url           推流地址
     * @param error_code    结果
     * - 0: 调用成功；
     * - 其他: 调用失败。
     * @endif
     */
    virtual void onUpdateLiveStreamTask(const char* task_id, const char* url, int error_code) {
        (void)task_id;
        (void)url;
        (void)error_code;
    }

    /** 
     * @if English
     * Notifies to delete the result of live stream.
     * <br>The callback asynchronously returns the callback result of ref IRtcEngineEx::addLiveStreamTask "addLiveStreamTask". For information about actual pushing state, see \ref IRtcEngineEventHandlerEx::onLiveStreamState "onLiveStreamState".
     * @param task_id       The ID of a task.
     * @param error_code    The result.
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 通知删除直播任务结果。
     * <br>该回调异步返回 \ref IRtcEngineEx::removeLiveStreamTask "removeLiveStreamTask" 接口的调用结果；实际推流状态参考 \ref IRtcEngineEventHandlerEx::onLiveStreamState "onLiveStreamState"
     *  @param task_id      任务id
     * @param error_code    结果
     * - 0: 调用成功；
     * - 其他: 调用失败。
     * @endif
     */
    virtual void onRemoveLiveStreamTask(const char* task_id, int error_code) {
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
     * @note Linux 暂不支持
     * 
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
    virtual void onLiveStreamState(const char* task_id, const char* url, NERtcLiveStreamStateCode state) {
        (void)task_id;
        (void)url;
        (void)state;
    }
    
    /** 
     * @if English
     * Occurs when howling is detected.
     * When the distance between the sound source and the PA equipment is too close, howling may occur. The NERTC SDK supports the howling detection. When a howling signal is detected, the callback is automatically triggered until the howling stops. The application layer can prompt the user to mute the microphone or directly mute the microphone when the app receives the howling information returned by the callback.
     * @note
     * Howling detection is used in audio-only scenarios, such as audio chat rooms or online meetings. We recommend that you do not use howling detection in entertainment scenes that include background music.
     * @param howling       Whether a howling occurs. 
     * - true: Howling occurs.
     * - false: Normal state.
     * @endif
     * @if Chinese
     * 检测到啸叫回调。
     * <br>当声源与扩音设备之间因距离过近时，可能会产生啸叫。NERTC SDK 支持啸叫检测，当检测到有啸叫信号产生的时候，自动触发该回调直至啸叫停止。App 应用层可以在收到啸叫回调时，提示用户静音麦克风，或直接静音麦克风。
     * @note
     * 啸叫检测功能一般用于语音聊天室或在线会议等纯人声环境，不推荐在包含背景音乐的娱乐场景中使用。
     * @param howling       是否出现啸叫
     * - true: 啸叫。
     * - false: 正常。
     * @endif
     */
    virtual void onAudioHowling(bool howling) {
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
	virtual void onRecvSEIMsg(uid_t uid, const char* data, uint32_t dataSize) {
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
     * @note Linux 暂不支持
     * 
     * 音频录制状态回调。
     * @param code          音频录制状态码。详细信息请参考 NERtcAudioRecordingCode。
     * @param file_path     音频录制文件保存路径。
     * @endif
     */
    virtual void onAudioRecording(NERtcAudioRecordingCode code, const char* file_path) {
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
     * @note Linux 暂不支持
     * 
     * 跨房间媒体流转发状态发生改变回调。
     * @since V4.3.0
     * @param state         当前跨房间媒体流转发状态。详细信息请参考 #NERtcChannelMediaRelayState
     * @param channel_name  媒体流转发的目标房间名。
     * @endif
     */
    virtual void onMediaRelayStateChanged(NERtcChannelMediaRelayState state, const char* channel_name) {
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
     * @note Linux 暂不支持
     * 
     * 媒体流相关转发事件回调。
     * @since V4.3.0
     * @param event         当前媒体流转发事件。详细信息请参考 #NERtcChannelMediaRelayEvent 。
     * @param channel_name  转发的目标房间名。
     * @param error         相关错误码。详细信息请参考 #NERtcErrorCode 。
     * @endif
     */
    virtual void onMediaRelayEvent(NERtcChannelMediaRelayEvent event, const char* channel_name, NERtcErrorCode error) {
        (void)event;
        (void)channel_name;
        (void)error;
    }

    /**
     * @if English
     * Occurs when the published local media stream falls back to an audio-only stream due to poor network conditions or switches back to audio and video stream after the network conditions improve.
     * <br>If you call setLocalPublishFallbackOption and set option to #kNERtcStreamFallbackAudioOnly, this callback is triggered when the locally published stream falls back to audio-only mode due to poor uplink network conditions, or when the audio stream switches back to the audio and video stream after the uplink network conditions improve. 
     * @since V4.3.0
     * @param is_fallback   The locally published stream falls back to audio-only mode or switches back to audio and video stream.
     * - true: The published stream from a local client falls back to audio-only mode due to poor uplink network conditions.
     * - false: The audio stream switches back to the audio and video stream after the upstream network condition improves.
     * @param stream_type   The type of the video stream, such as mainstream and substream. 
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 本地发布流已回退为音频流、或已恢复为音视频流回调。
     * <br>如果您调用了设置本地推流回退选项 setLocalPublishFallbackOption 接口，并将 option 设置为 #kNERtcStreamFallbackAudioOnly 后，当上行网络环境不理想、本地发布的媒体流回退为音频流时，或当上行网络改善、媒体流恢复为音视频流时，会触发该回调。 
     * @since V4.3.0
     * @param is_fallback   本地发布流已回退或已恢复。
     * - true： 由于网络环境不理想，发布的媒体流已回退为音频流。
     * - false：由于网络环境改善，从音频流恢复为音视频流。
     * @param stream_type   对应的视频流类型，即主流或辅流。
     * @endif
     */
    virtual void onLocalPublishFallbackToAudioOnly(bool is_fallback, NERtcVideoStreamType stream_type) {
        (void)is_fallback;
    }

    /**
     * @if English
     * Occurs when the subscribed remote media stream falls back to an audio-only stream due to poor network conditions or switches back to the audio and video stream after the network condition improves.
     * <br>If you call setLocalPublishFallbackOption and set option to #kNERtcStreamFallbackAudioOnly, this callback is triggered when the locally published stream falls back to audio-only mode due to poor uplink network conditions, or when the audio stream switches back to the audio and video stream after the uplink network condition improves.
     * @since V4.3.0
     * @param uid           The ID of a remote user.
     * @param is_fallback   The subscribed remote media stream falls back to audio-only mode or switches back to the audio and video stream. 
     * - true: The subscribed remote media stream falls back to audio-only mode due to poor downstream network conditions.
     * - false: The subscribed remote media stream switches back to the audio and video stream after the downstream network condition improves.
     * @param stream_type   The type of the video stream, such as mainstream and substream. 
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 订阅的远端流已回退为音频流、或已恢复为音视频流回调。
     * <br>如果你调用了设置远端订阅流回退选项 setRemoteSubscribeFallbackOption 接口并将 option 设置 #kNERtcStreamFallbackAudioOnly 后，当下行网络环境不理想、仅接收远端音频流时，或当下行网络改善、恢复订阅音视频流时，会触发该回调。
     * @since V4.3.0
     * @param uid           远端用户的 ID。
     * @param is_fallback   远端订阅流已回退或恢复：
     * - true： 由于网络环境不理想，订阅的远端流已回退为音频流。
     * - false：由于网络环境改善，订阅的远端流从音频流恢复为音视频流。
     * @param stream_type   对应的视频流类型，即主流或辅流。
     * @endif
     */
    virtual void onRemoteSubscribeFallbackToAudioOnly(uid_t uid, bool is_fallback, NERtcVideoStreamType stream_type) {
        (void)uid;
        (void)is_fallback;
    }
};
} //namespace nertc

#endif
