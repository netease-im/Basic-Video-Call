/** @file nertc_channel_event_handler.h
 * @brief NERTC SDK IRtcChannel回调接口头文件。
 * NERTC SDK所有接口参数说明: 所有与字符串相关的参数(char *)全部为UTF-8编码。
 * @copyright (c) 2015-2021, NetEase Inc. All rights reserved
 * @date 2021/05/10
 */

#ifndef NERTC_CHANNEL_EVENTS_H
#define NERTC_CHANNEL_EVENTS_H

#include "nertc_engine_defines.h"
#include "nertc_error_code.h"
#include "nertc_warn_code.h"

NERTC_BEGIN_DECLS
/**
 * @if English
 * IRtcChannelEventHandler callback interface class is used to send IRtcChannel callback event notifications to the app from
 * SDK. The app gets IRtcChannel event notifications from the SDK through inheriting the interface class. <br>All methods in
 * this interface class have their (empty) default implementations, and the application can inherit only some of the required
 * events instead of all of them. When calling a callback method, the application must not implement time-consuming operations
 * or call blocking-triggered APIs. For example, if you want to enable audio and video, the SDK may be affected in the runtime.
 * @since V4.5.0
 * @endif
 * @if Chinese
 * IRtcChannelEventHandler 回调接口类用于 SDK 向 App 发送IRtcChannel回调事件通知，App 通过继承该接口类的方法获取 SDK
 * IRtcChannel的事件通知。 <br>接口类的所有方法都有缺省（空）实现，App 可以根据需要只继承关心的事件。在回调方法中，App
 * 不应该做耗时或者调用可能会引起阻塞的 API（如开启音频或视频等），否则可能影响 SDK 的运行。
 * @endif
 */
struct nertc_channel_events {
  struct nertc_channel* self;
  /**
   * @if English
   * Occurs when the error occurs.
   * <br>The callback is triggered to report an error related to network or media during SDK runtime. In most cases, the SDK
   * cannot fix the issue and resume running. The SDK requires the app to take action or informs the user of the issue.
   * @param error_code    The error code. For more information, see NERtcDMErrorCode.
   * @param msg           Error description.
   * @since V4.5.0
   * @endif
   * @if Chinese
   * 发生错误回调。
   * <br>该回调方法表示 SDK 运行时出现了（网络或媒体相关的）错误。通常情况下，SDK上报的错误意味着SDK无法自动恢复，需要 App
   * 干预或提示用户。
   * @param error_code    错误码。详细信息请参考 NERtcDMErrorCode
   * @param msg           错误描述。
   * @endif
   */
  void (NERTC_CALL *on_error)(void* self, int error_code, const char* msg);
  /**
   * @if English
   * Occurs when a warning occurs.
   * <br>The callback is triggered to report a warning related to network or media during SDK runtime. In most cases, the app
   * ignores the warning message and the SDK resumes running.
   * @param warn_code     The warning code. For more information, see {@link NERtcWarnCode}.
   * @param msg           The warning description.
   * @since V4.5.0
   * @endif
   * @if Chinese
   * 发生警告回调。
   * <br>该回调方法表示 SDK 运行时出现了（网络或媒体相关的）警告。通常情况下，SDK 上报的警告信息 App 可以忽略，SDK 会自动恢复。
   * @param warn_code     警告码。详细信息请参考 {@link NERtcWarnCode}。
   * @param msg           警告描述。
   * @endif
   */
  void (NERTC_CALL *on_warning)(void* self, int warn_code, const char* msg);
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
  void (NERTC_CALL *on_api_call_executed)(void* self, const char* api_name, nertc_error_code error, const char* message);
  /**
   * @if English
   * Allows a user to join a room. The callback indicates that the client has already signed in.
   * @param cid     The ID of the room that the client joins.
   * @param uid     Specifies the ID of a user. If you specify the uid in the joinChannel method, a specificed ID is returned at
   * the time. If not, the  ID automatically assigned by the CommsEase’s server is returned.
   * @param result  Indicates the result.
   * @param elapsed The time elapsed from calling the joinChannel method to the occurrence of this event. Unit: milliseconds.
   * @since V4.5.0
   * @endif
   * @if Chinese
   * 加入房间回调，表示客户端已经登入服务器。
   * @param cid       客户端加入的房间 ID。
   * @param uid       用户 ID。 如果在 joinChannel 方法中指定了 uid，此处会返回指定的 ID; 如果未指定
   * uid，此处将返回云信服务器自动分配的 ID。
   * @param result    返回结果。
   * @param elapsed   从 joinChannel 开始到发生此事件过去的时间，单位为毫秒。
   * @endif
   */
  void (NERTC_CALL *on_join_channel)(void* self, channel_id_t cid, nertc_uid_t uid, nertc_error_code result, uint64_t elapsed);
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
  void (NERTC_CALL *on_reconnecting_start)(void* self, channel_id_t cid, nertc_uid_t uid);
  /**
   * @if English
   * Occurs when the state of network connection is changed.
   * <br>The callback is triggered when the state of network connection is changed. The callback returns the current state of
   * network connection and the reason why the network state changes.
   * @param state     The state of current network connection.
   * @param reason    The reason why the network state changes.
   * @since V4.5.0
   * @endif
   * @if Chinese
   * 网络连接状态已改变回调。
   * <br>该回调在网络连接状态发生改变的时候触发，并告知用户当前的网络连接状态和引起网络状态改变的原因。
   * @param state     当前的网络连接状态。
   * @param reason    引起当前网络连接状态发生改变的原因。
   * @endif
   */
  void (NERTC_CALL *on_connection_state_change)(void* self,nertc_connection_state_type state,nertc_reason_connection_changed_type reason);
  /**
   * @if English
   * Occurs when a user rejoins a room.
   * <br>If a client is disconnected from the server due to poor network quality, the SDK starts reconnecting. If the client and
   * server are reconnected, the callback is triggered.
   * @param cid       The ID of the room that the client joins.
   * @param uid       The ID of a user.
   * @param result    The result.
   * @param elapsed   The time elapsed from reconnection to the occurrence of this event. Unit: milliseconds.
   * @since V4.5.0
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
  void (NERTC_CALL *on_rejoin_channel)(void* self, channel_id_t cid, nertc_uid_t uid, nertc_error_code result, uint64_t elapsed);
  /**
   * @if English
   * Occurs when a user leaves a room.
   * <br>After an app invokes the leaveChannel method, SDK prompts whether the app successfully leaves the room.
   * @param result    The result.
   * @since V4.5.0
   * @endif
   * @if Chinese
   * 退出房间回调。
   * <br>App 调用 leaveChannel 方法后，SDK 提示 App 退出房间是否成功。
   * @param result    返回结果。
   * @endif
   */
  void (NERTC_CALL *on_leave_channel)(void* self, nertc_error_code result);
  /**
   * @if English
   * Network connection interruption.
   * @note
   * - The callback is triggered if the SDK fails to connect to the server three consecutive times after you successfully call
   * the joinChannel method.
   * - A client may be disconnected from the server in poor network connection. At this time,  the SDK needs not automatically
   * reconnecting until the SDK triggers the callback method.
   * @param reason    The reason why the network is disconnected.
   * @since V4.5.0
   * @endif
   * @if Chinese
   * 网络连接中断
   * @note
   * - SDK 在调用 joinChannel 加入房间成功后，如果和服务器失去连接且连续 3 次重连失败，就会触发该回调。
   * - 由于非网络原因，客户端可能会和服务器失去连接，此时SDK无需自动重连，直接触发此回调方法。
   * @param reason    网络连接中断原因。
   * @endif
   */
  void (NERTC_CALL *on_disconnect)(void* self, nertc_error_code reason);
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
   * @since V4.5.0
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
  void (NERTC_CALL *on_client_role_changed)(void* self, nertc_client_role old_role, nertc_client_role new_role);
  /**
   * @if English
   * Occurs when a remote user joins the current room.
   * <br>The callback prompts that a remote user joins the room and returns the ID of the user that joins the room. If the user
   * ID already exists, the remote user also receives a message that the user already joins the room, which is returned by the
   * callback.
   * @param uid           The ID of the user that joins the room.
   * @param user_name     The name of the remote user who joins the room.
   * @since V4.5.0
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
  void (NERTC_CALL *on_user_joined)(void* self, nertc_uid_t uid, const char* user_name, const struct nertc_user_join_extra_info* custom_info);
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
   * @since V4.5.0
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
  void (NERTC_CALL *on_user_left)(void* self, nertc_uid_t uid, nertc_session_leave_reason reason, const struct nertc_user_join_extra_info* custom_info);
  /**
   * @if English
   * Occurs when a remote user enables audio.
   * @param uid       The ID of a remote user.
   * @since V4.5.0
   * @endif
   * @if Chinese
   * 远端用户开启音频的回调。
   * @param stream_type       音频流类型。@since 4.6.10
   * @param uid               远端用户ID。
   * @endif
   */
  void (NERTC_CALL *on_user_audio_start)(void* self, nertc_audio_stream_type type, nertc_uid_t uid);
  /**
   * @if English
   * Occurs when a remote user disables audio.
   * @param uid       The ID of a remote user.
   * @since V4.5.0
   * @endif
   * @if Chinese
   * 远端用户停用音频的回调。
   * @param stream_type       音频流类型。@since 4.6.10
   * @param uid               远端用户ID。
   * @endif
   */
  void (NERTC_CALL *on_user_audio_stop)(void* self, nertc_audio_stream_type type, nertc_uid_t uid);
  /**
   * @if English
   * Callbacks that specify whether to mute remote users.
   * @param uid       The ID of a remote user.
   * @param mute      Whether to unmute the remote user.
   * @since V4.5.0
   * @endif
   * @if Chinese
   * 远端用户是否静音的回调。
   * @param type       音频流类型。
   * @param uid       远端用户ID。
   * @param mute      是否静音。
   * @endif
   */
  void (NERTC_CALL *on_user_audio_mute)(void* self, nertc_audio_stream_type type, nertc_uid_t uid, bool mute);
  /**
   * @if English
   * Occurs when a remote user enables video.
   * @param uid               The ID of a remote user.
   * @param max_profile       The resolution of video encoding measures the encoding quality.
   * @since V4.5.0
   * @endif
   * @if Chinese
   * 远端用户开启视频的回调。
   * @param type    远端用户流类型。
   * @param uid               远端用户ID。
   * @param max_profile       视频编码的分辨率，用于衡量编码质量。
   * @endif
   */
  void (NERTC_CALL *on_user_video_start)(void* self, nertc_video_stream_type type, nertc_uid_t uid, nertc_video_profile_type max_profile);
  /**
   * @if English
   * Occurs when a remote user disables video.
   * @param uid       The ID of a remote user.
   * @since V4.5.0
   * @endif
   * @if Chinese
   * 远端用户停用视频的回调。
   * @param type    远端用户流类型。
   * @param uid       远端用户ID。
   * @endif
   */
  void (NERTC_CALL *on_user_video_stop)(void* self, nertc_video_stream_type type, nertc_uid_t uid);
  /**
   * @if English
   * Occurs when a remote user stops or resumes sending video streams.
   * @param uid       The ID of a remote user.
   * @param mute      Whether to disable video streams.
   * @since V4.5.0
   * @endif
   * @if Chinese
   * 远端用户暂停或恢复发送视频流的回调。
   * @param type      视频流类型。
   * @param uid       远端用户ID。
   * @param mute      是否禁视频流。
   * @endif
   */
  void (NERTC_CALL *on_user_video_mute)(void* self, nertc_video_stream_type type, nertc_uid_t uid, bool mute);
  /**
   * @if English
   * Occurs when screen sharing is paused/resumed/started/ended.
   * <br>The method applies to Windows only.
   * @since V4.5.0
   * @since V4.5.0
   * @endif
   * @if Chinese
   * 屏幕共享状态变化回调。
   * <br>该方法仅适用于 Windows 平台。
   * @since V4.5.0
   * @endif
   */
  void (NERTC_CALL *on_screen_capture_state_changed)(void* self, nertc_screen_capture_status status);
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
  void (NERTC_CALL *on_user_video_profile_update)(void* self, nertc_uid_t uid, nertc_video_profile_type max_profile);  
  /**
   * @if English
   * Occurs when the first audio frame from a remote user is received.
   * @param uid       The ID of a remote user whose audio streams are sent.
   * @since V4.5.0
   * @endif
   * @if Chinese
   * 已接收到远端音频首帧的回调。
   * @param type 音频流类型。
   * @param uid       远端用户 ID，指定是哪个用户的音频流。
   * @endif
   */
  void (NERTC_CALL *on_first_audio_data_received)(void* self, nertc_audio_stream_type type, nertc_uid_t uid);
  /**
   * @if English
   * Occurs when the first video frame from a remote user is displayed.
   * <br>If the first video frame from a remote user is displayed in the view, the callback is triggered.
   * @param uid       The ID of a user whose audio streams are sent.
   * @since V4.5.0
   * @endif
   * @if Chinese
   * 已显示首帧远端视频的回调。
   * 第一帧远端视频显示在视图上时，触发此调用。
   * @param type 视频流类型。
   * @param uid       用户 ID，指定是哪个用户的视频流。
   * @endif
   */
  void (NERTC_CALL *on_first_video_data_received)(void* self, nertc_video_stream_type type, nertc_uid_t uid);
  /**
   * @if English
   * Occurs when the first audio frame from a remote user is decoded.
   * @param uid       The ID of a remote user whose audio streams are sent.
   * @since V4.5.0
   * @endif
   * @if Chinese
   * 已解码远端音频首帧的回调。
   * @param type 音频流类型。
   * @param uid       远端用户 ID，指定是哪个用户的音频流。
   * @endif
   */
  void (NERTC_CALL *on_first_audio_frame_decoded)(void* self, nertc_audio_stream_type type, nertc_uid_t uid);
  /**
   * @if English
   * Occurs when the remote video is received and decoded.
   * <br>If the engine receives the first frame of remote video streams, the callback is triggered.
   * @param uid       The ID of a user whose audio streams are sent.
   * @param width     The width of video streams (px).
   * @param height    The height of video streams(px).
   * @since V4.5.0
   * @endif
   * @if Chinese
   * 已接收到远端视频并完成解码的回调。
   * <br>引擎收到第一帧远端视频流并解码成功时，触发此调用。
   * @param type 视频流类型。
   * @param uid       用户 ID，指定是哪个用户的视频流。
   * @param width     视频流宽（px）。
   * @param height    视频流高（px）。
   * @endif
   */
  void (NERTC_CALL *on_first_video_frame_decoded)(void* self, nertc_video_stream_type type, nertc_uid_t uid, uint32_t width, uint32_t height);
  /**
   * @if English
   * Occurs when the system prompts current local audio volume.
   * - This callback is disabled by default. You can enable the callback by calling the \ref
   * IRtcEngineEx::enableAudioVolumeIndication "enableAudioVolumeIndication" method.
   * - After the callback is enabled, if a local user speaks, the SDK triggers the callback based on the time interval specified
   * in the \ref IRtcEngineEx::enableAudioVolumeIndication "enableAudioVolumeIndication" method.
   * - If a local user sets a mute by calling \ref IRtcEngineEx::muteLocalAudioStream "muteLocalAudioStream", the SDK sets the
   * value of volume as 0, and calls back to the application layer.
   * @param volume        The volume of audio mixing. Value range: 0 to 100.
   * @since V4.5.0
   * @endif
   * @if Chinese
   * 提示房间内本地用户瞬时音量的回调。
   * - 该回调默认禁用。可以通过 \ref IRtcEngineEx::enableAudioVolumeIndication "enableAudioVolumeIndication" 方法开启。
   * - 开启后，本地用户说话，SDK 会按  \ref IRtcEngineEx::enableAudioVolumeIndication "enableAudioVolumeIndication"
   * 方法中设置的时间间隔触发该回调。
   * - 如果本地用户将自己静音（调用了 \ref IRtcEngineEx::muteLocalAudioStream "muteLocalAudioStream"），SDK 将音量设置为 0
   * 后回调给应用层。
   * @param volume        （混音后的）音量，取值范围为 [0,100]。
   * @param enable_vad     是否检测到人声。
   * @endif
   */
  void (NERTC_CALL *on_local_audio_volume_indication)(void* self, int volume, bool enable_vad);
  /**
   * @if English
   * Occurs when the system prompts the active speaker and the audio volume.
   * <br>By default, the callback is disabled. You can enable the callback by calling the enableAudioVolumeIndication method.
   * After the callback is enabled, if a local user speaks, the SDK triggers the callback based on the time interval specified
   * in the enableAudioVolumeIndication method. <br>In the array of speakers returned:
   * - If a uid is contained in the array returned in the last response but not in the array returned in the current response.
   * The remote user with the uid does not speak by default.
   * - If the volume is 0, the user does not speak.
   * - If the array is empty, the remote user does not speak.
   * @param speakers              The array that contains the information about user IDs and volumes is NERtcAudioVolumeInfo.
   * @param speaker_number        The size of speakers array, which indicates the number of speakers.
   * @param total_volume          The total volume (after audio mixing). Value range: 0 to 100.
   * @since V4.5.0
   * @endif
   * @if Chinese
   * 提示房间内谁正在说话及说话者瞬时音量的回调。
   * <br>该回调默认为关闭状态。可以通过 enableAudioVolumeIndication 方法开启。开启后，无论房间内是否有人说话，SDK 都会按
   * enableAudioVolumeIndication 方法中设置的时间间隔触发该回调。 <br>在返回的 speakers 数组中:
   * - 如果有 uid 出现在上次返回的数组中，但不在本次返回的数组中，则默认该 uid 对应的远端用户没有说话。
   * - 如果volume 为 0，表示该用户没有说话。
   *  - 如果speakers 数组为空，则表示此时远端没有人说话。
   * @param speakers              每个说话者的用户 ID 和音量信息的数组: NERtcAudioVolumeInfo
   * @param speaker_number        speakers 数组的大小，即说话者的人数。
   * @param total_volume          （混音后的）总音量，取值范围为 [0,100]。
   * @endif
   */
  void (NERTC_CALL *on_remote_audio_volume_indication)(void* self,const struct nertc_audio_volume_info* speakers,uint32_t speaker_number,int total_volume);
  /**
   * @if English
   * Notifies to add the result of live stream.
   * <br>The callback asynchronously returns the callback result of \ref IRtcEngineEx::addLiveStreamTask "addLiveStreamTask".
   * For information about actual pushing state, see \ref IRtcEngineEventHandlerEx::onLiveStreamState "onLiveStreamState".
   * @param task_id           The ID of a stream-push task.
   * @param url               Task ID.
   * @param error_code        The result.
   * - 0: Success.
   * - Other values: Failure.
   * @since V4.5.0
   * @endif
   * @if Chinese
   * 通知添加直播任务结果。
   * <br>该回调异步返回 \ref IRtcEngineEx::addLiveStreamTask "addLiveStreamTask" 接口的调用结果；实际推流状态参考 \ref
   * IRtcEngineEventHandlerEx::onLiveStreamState "onLiveStreamState"
   * @param task_id           任务id
   * @param url               推流地址
   * @param error_code        结果
   * - 0: 调用成功；
   * - 其他: 调用失败。
   * @endif
   */
  void (NERTC_CALL *on_add_live_stream_task)(void* self, const char* task_id, const char* url, int error_code);
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
   * @since V4.5.0
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
  void (NERTC_CALL *on_update_live_stream_task)(void* self, const char* task_id, const char* url, int error_code);
  /**
   * @if English
   * Notifies to delete the result of live stream.
   * <br>The callback asynchronously returns the callback result of ref IRtcEngineEx::addLiveStreamTask "addLiveStreamTask". For
   * information about actual pushing state, see \ref IRtcEngineEventHandlerEx::onLiveStreamState "onLiveStreamState".
   * @param task_id       The ID of a task.
   * @param error_code    The result.
   * - 0: Success.
   * - Other values: Failure.
   * @since V4.5.0
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
  void (NERTC_CALL *on_remove_live_stream_task)(void* self, const char* task_id, int error_code);
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
   * @since V4.5.0
   * @endif
   * @if Chinese
   * 通知直播推流状态
   * @note                该回调在通话中有效。
   * @param task_id       任务id
   * @param url           推流地址
   * @param state         #NERtcLiveStreamStateCode, 直播推流状态
   * - 505: 推流中；
   * - 506: 推流失败；
   * - 511: 推流结束；
   * @endif
   */
  void (NERTC_CALL *on_live_stream_state_changed)(void* self, const char* task_id, const char* url, nertc_live_stream_state_code state);
  /**
   * @if English
   * Occurs when the content of remote SEI is received.
   * <br>After a remote client successfully sends SEI, the local client receives a message returned by the callback.
   * @param[in] uid       The ID of the user who sends the SEI.
   * @param[in] data      The received SEI data.
   * @param[in] dataSize  The size of received SEI data.
   * @since V4.5.0
   * @endif
   * @if Chinese
   * 收到远端流的 SEI 内容回调。
   * <br>当远端成功发送 SEI 后，本端会收到此回调。
   * @param[in] uid       发送该 sei 的用户 id
   * @param[in] data      接收到的 sei 数据
   * @param[in] dataSize  接收到 sei 数据的大小
   * @endif
   */
  void (NERTC_CALL *on_receive_sei_message)(void* self, nertc_uid_t uid, const uint8_t* data, uint32_t dataSize);
  /**
   * @if English
   * Occurs when the state of the media stream is relayed.
   * @since V4.5.0
   * @param state         The state of the media stream.
   * @param channel_name  The name of the destination room where the media streams are relayed.
   * @endif
   * @if Chinese
   * 跨房间媒体流转发状态发生改变回调。
   * @since V4.5.0
   * @param state         当前跨房间媒体流转发状态。详细信息请参考 #NERtcChannelMediaRelayState
   * @param channel_name  媒体流转发的目标房间名。
   * @endif
   */
  void (NERTC_CALL *on_media_relay_state_changed)(void* self, nertc_channel_media_relay_state state, const char* channel_name);
  /**
   * @if English
   * Occurs when events related to media stream relay are triggered.
   * @since V4.5.0
   * @param event         The media stream relay event.
   * @param channel_name  The name of the destination room where the media streams are relayed.
   * @param error         Specific error codes.
   * @endif
   * @if Chinese
   * 媒体流相关转发事件回调。
   * @since V4.5.0
   * @param event         当前媒体流转发事件。详细信息请参考 #NERtcChannelMediaRelayEvent 。
   * @param channel_name  转发的目标房间名。
   * @param error         相关错误码。详细信息请参考 #NERtcErrorCode 。
   * @endif
   */
  void (NERTC_CALL *on_media_relay_event)(void* self,nertc_channel_media_relay_event event,const char* channel_name,nertc_error_code error);
  /**
   * @if English
   * Occurs when the published local media stream falls back to an audio-only stream due to poor network conditions or switches
   * back to audio and video stream after the network conditions improve. <br>If you call setLocalPublishFallbackOption and set
   * option to #kNERtcStreamFallbackAudioOnly, this callback is triggered when the locally published stream falls back to
   * audio-only mode due to poor uplink network conditions, or when the audio stream switches back to the audio and video stream
   * after the uplink network conditions improve.
   * @since V4.5.0
   * @param is_fallback   The locally published stream falls back to audio-only mode or switches back to audio and video stream.
   * - true: The published stream from a local client falls back to audio-only mode due to poor uplink network conditions.
   * - false: The audio stream switches back to the audio and video stream after the upstream network condition improves.
   * @param type   The type of the video stream, such as mainstream and substream.
   * @since V4.5.0
   * @endif
   * @if Chinese
   * 本地发布流已回退为音频流、或已恢复为音视频流回调。
   * <br>如果您调用了设置本地推流回退选项 setLocalPublishFallbackOption 接口，并将 option 设置为 #kNERtcStreamFallbackAudioOnly
   * 后，当上行网络环境不理想、本地发布的媒体流回退为音频流时，或当上行网络改善、媒体流恢复为音视频流时，会触发该回调。
   * @since V4.5.0
   * @param is_fallback   本地发布流已回退或已恢复。
   * - true： 由于网络环境不理想，发布的媒体流已回退为音频流。
   * - false：由于网络环境改善，从音频流恢复为音视频流。
   * @param type   对应的视频流类型，即主流或辅流。
   * @endif
   */
  void (NERTC_CALL *on_publish_fallback_to_audio_only)(void* self, bool is_fallback, nertc_video_stream_type stream_type);
  /**
   * @if English
   * Occurs when the subscribed remote media stream falls back to an audio-only stream due to poor network conditions or
   * switches back to the audio and video stream after the network condition improves. <br>If you call
   * setLocalPublishFallbackOption and set option to #kNERtcStreamFallbackAudioOnly, this callback is triggered when the locally
   * published stream falls back to audio-only mode due to poor uplink network conditions, or when the audio stream switches
   * back to the audio and video stream after the uplink network condition improves.
   * @since V4.5.0
   * @param uid           The ID of a remote user.
   * @param is_fallback   The subscribed remote media stream falls back to audio-only mode or switches back to the audio and
   * video stream.
   * - true: The subscribed remote media stream falls back to audio-only mode due to poor downstream network conditions.
   * - false: The subscribed remote media stream switches back to the audio and video stream after the downstream network
   * condition improves.
   * @param stream_type   The type of the video stream, such as mainstream and substream.
   * @since V4.5.0
   * @endif
   * @if Chinese
   * 订阅的远端流已回退为音频流、或已恢复为音视频流回调。
   * <br>如果你调用了设置远端订阅流回退选项 setRemoteSubscribeFallbackOption 接口并将 option 设置 #kNERtcStreamFallbackAudioOnly
   * 后，当下行网络环境不理想、仅接收远端音频流时，或当下行网络改善、恢复订阅音视频流时，会触发该回调。
   * @since V4.5.0
   * @param uid          远端用户的 ID。
   * @param is_fallback  远端订阅流已回退或恢复：
   * - true： 由于网络环境不理想，订阅的远端流已回退为音频流。
   * - false：由于网络环境改善，订阅的远端流从音频流恢复为音视频流。
   * @param stream_type  对应的视频流类型，即主流或辅流。
   * @endif
   */
  void (NERTC_CALL *on_subscribe_fallback_to_audio_only)(void* self,nertc_uid_t uid,bool is_fallback,nertc_video_stream_type stream_type);
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
  void (NERTC_CALL *on_media_right_changed)(void* self, bool is_audio_banned, bool is_video_banned);
  /**
   * @if Chinese
   * 权限密钥即将过期事件回调。
   * - 由于 PermissionKey 具有一定的时效，在通话过程中如果 PermissionKey 即将失效，SDK 会提前 30 秒触发该回调，提醒用户更新
   * PermissionKey。
   * @since V4.6.29
   * @par 使用前提
   * 请在 IRtcChannelEventHandler 接口类中通过 \ref IRtcChannel::setChannelEventHandler "setChannelEventHandler"
   * 接口设置回调监听。
   * @par 相关接口
   * 在收到此回调后可以调用 \ref nertc::IRtcEngineEx::updatePermissionKey "updatePermissionKey" 方法更新权限密钥。
   * @endif
   */
  void (NERTC_CALL *on_permission_key_will_expire)(void* self);
  /**
   * @if Chinese
   * 更新权限密钥事件回调。
   * - 调用 \ref IRtcChannel::updatePermissionKey "updatePermissionKey"  方法主动更新权限密钥后，SDK
   * 会触发该回调，返回权限密钥更新的结果。
   * @since V4.6.29
   * @par 使用前提
   * 请在 IRtcChannelEventHandler 接口类中通过 \ref IRtcChannel::setChannelEventHandler "setChannelEventHandler"
   * 接口设置回调监听。
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
   *      <td>error_code</td>
   *      <td> \ref nertc::NERtcErrorCode "NERtcErrorCode" </td>
   *      <td>错误码。<ul><li>kNERtcErrChannelPermissionKeyError：权限密钥错误。<li>kNERtcErrChannelPermissionKeyTimeout：权限密钥超时。</td>
   *  </tr>
   *  <tr>
   *      <td>timeout</td>
   *      <td>int</td>
   *      <td>更新后的权限密钥剩余有效时间。单位为秒。</td>
   *  </tr>
   * </table>
   * @endif
   */
  void (NERTC_CALL *on_update_permission_key)(void* self, const char* key, nertc_error_code error_code, int timeout);
};

NERTC_END_DECLS
#endif
