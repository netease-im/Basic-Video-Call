/** @file nertc_channel.h
 * @brief NERTC SDK IRtcChannel接口头文件。
 * NERTC SDK所有接口参数说明: 所有与字符串相关的参数(char *)全部为UTF-8编码。
 * @copyright (c) 2015-2021, NetEase Inc. All rights reserved
 * @date 2021/05/10
 */

#ifndef NERTC_CHANNEL_H
#define NERTC_CHANNEL_H

#include "nertc_channel_events.h"


NERTC_BEGIN_DECLS

/**
 * @if English
 * Gets the engine object.
 * @since V4.5.0
 * @endif
 * @if Chinese
 * 获取channel关联的nertc_engine实例
 * @since V4.5.0
 * @endif
 */
NERTC_API struct nertc_engine* NERTC_CALL nertc_channel_get_engine(struct nertc_channel* self);

/**
 * @if English
 * Destroys an IRtcChannel instance to release resources.
 * @since V4.5.0
 * @endif
 * @if Chinese
 * 销毁 IRtcChannel 实例，释放资源。
 * @since V4.5.0
 * @endif
 */
NERTC_API void NERTC_CALL nertc_channel_destroy(struct nertc_channel* self);

/**
 * @if English
 * Gets the current channel name.
 * @since V4.5.0
 * @return
 * - Success: Return IRtcChannel channel name.
 * - Fail: Return nothing.
 * @endif
 * @if Chinese
 * 获取当前房间名。
 * @since V4.5.0
 * @return
 *- 成功：当前IRtcChannel房间名。
 *- 失败：返回空。
 * @endif
 */
NERTC_API const char* NERTC_CALL nertc_channel_get_channel_name(struct nertc_channel* self);

/**
 * @if English
 * Sets the event handler of the IRtcChannel.
 * <br>You can set the event handler to monitor the channel event of IRtcChannel, and receive user video information in the
 * channel.
 * @since V4.5.0
 * @param[in] handler Event handler.
 * @return
 * - Success: Return IRtcChannel channel name.
 * - Fail: Return nothing.
 * @endif
 * @if Chinese
 * 设置 IRtcChannel 对象的事件句柄。
 * <br>你可以通过设置的事件句柄，监听当前IRtcChannel对象对应房间的事件，并接收房间中用户视频信息等。
 * @since V4.5.0
 * @param[in] handler 事件监听句柄对象
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 *
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_set_channel_event_handler(struct nertc_channel* self, struct nertc_channel_events* handler);

/**
 * @if English
 *  Joins a channel of audio and video call.
 * @note
 * - The user ID for each user in the channel must be unique, and the uid in the current IRtcChannel will reuse the UID in the
IRtcEngine channel.
 * - The channel name is the channel_id of IRtcChannel specified when created.
 * @since V4.5.0
 * @param[in] token The certification signature used in authentication (NERTC Token). Valid values:
                    - Null. You can set the value to null in the debugging mode. This poses a security risk. We recommend that
you contact your business manager to change to the default safe mode before your product is officially launched.
                    - NERTC Token acquired. In safe mode, the acquired token must be specified. If the specified token is
invalid, users are unable to join a room. We recommend that you use the safe mode.
 * @param[in] uid  The unique identifier of a user. The uid of each user in a room must be unique.
 <br> uid is optional. The default value is 0. If the uid is not specified (set to 0), the SDK automatically
assigns a random uid and returns the uid in the callback of onJoinChannel. The application layer must keep and maintain the
return value. The SDK does not maintain the return value.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 加入音视频房间。
 * @note
 * - 房间内每个用户的用户 ID 必须是唯一的，当前 IRtcChannel 中的 uid 复用 IRtcEngine 房间中的 uid。
 * - 房间名对应 IRtcChannel 创建时的 channel_id。
 * @since V4.5.0
 * @param[in] token         安全认证签名（NERTC Token）。可设置为：
                            - null。调试模式下可设置为
null。安全性不高，建议在产品正式上线前在云信控制台中将鉴权方式恢复为默认的安全模式。
                            - 已获取的NERTC Token。安全模式下必须设置为获取到的 Token 。若未传入正确的 Token
将无法进入房间。推荐使用安全模式。
 * @param[in] uid           用户的唯一标识 id，房间内每个用户的 uid 必须是唯一的。
 <br>uid 可选，默认为 0。如果不指定（即设为 0），SDK 会自动分配一个随机 uid，并在 onJoinChannel
回调方法中返回，App 层必须记住该返回值并维护，SDK 不对该返回值进行维护。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
* @endif
*/
NERTC_API int NERTC_CALL nertc_channel_join_channel(struct nertc_channel* self,
                                                    const char* token,
                                                    nertc_uid_t uid,
                                                    struct nertc_join_channel_options* channel_options);

/**
 * @if English
 * Leaves the room.
 * <br>Leaves a room for hang up or calls ended.
 * <br>A user can call the leaveChannel method to end the call before the user makes another call.
 * <br>After the method is called successfully, the onLeaveChannel callback is locally triggered, and the onUserLeave callback
 * is remotely triggered.
 * @note
 * - The method is asynchronous call. Users cannot exit the room when the method is called and returned. After users exit the
 * room, the SDK triggers the onLeaveChannel callback.
 * - If you call leaveChannel method and instantly call release method, the SDK cannot trigger onLeaveChannel callback.
 * @since V4.5.0
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 离开房间。
 * <br>离开房间，即挂断或退出通话。
 * <br>结束通话时，必须调用leaveChannel结束通话，否则无法开始下一次通话。
 * <br>成功调用该方法离开房间后，本地会触发onLeaveChannel回调，远端会触发onUserLeave回调。
 * @note
 * - 该方法是异步操作，调用返回时并没有真正退出房间。在真正退出房间后，SDK 会触发onLeaveChannel回调。
 * - 如果您调用了leaveChannel后立即调用release，SDK 将无法触发onLeaveChannel回调。
 * @since V4.5.0
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_leave_channel(struct nertc_channel* self);

/**
 * @if English
 * Registers a stats observer.
 * @since V4.5.0
 * @param[in] observer      The stats observer.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 注册统计信息观测器。
 * @since V4.5.0
 * @param[in] observer      统计信息观测器
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_set_stats_observer(struct nertc_channel* self, struct nertc_media_stats_observer* observer);

/**
 * @if English
 * @deprecated This method is deprecated.
 * Enables volume indication for the speaker.
 * <br>The method allows the SDK to report to the app the information about the volume of the user that pushes local streams
 * and the remote user (up to three users) that has the highest instantaneous volume. The information about the current
 * speaker and the volume is reported. <br>If this method is enabled, when a user joins a room and pushes streams, the SDK
 * triggers \ref IRtcEngineEventHandlerEx::onRemoteAudioVolumeIndication "onRemoteAudioVolumeIndication" based on the preset
 * time intervals.
 * @param enable        Whether to prompt the speaker volume.
 * @param interval      The time interval at which volume prompt is displayed. Unit: milliseconds. The value must be the
 * multiples of 100 milliseconds.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * @deprecated 这个方法已废弃。
 * 启用说话者音量提示。
 * <br>通过此接口可以实现允许 SDK 定期向 App 反馈房间内发音频流的用户和瞬时音量最高的远端用户（最多 3
 * 位，包括本端）的音量相关信息，即当前谁在说话以及说话者的音量。
 * @since V3.5.0
 * @par 调用时机
 * 请在引擎初始化之后调用此接口，且该方法在加入房间前后均可调用。
 * @par 业务场景
 * 适用于通过发言者的人声相关信息做出 UI 上的音量展示的场景，或根据发言者的音量大小进行视图布局的动态调整。
 *  @note
 * 该方法在 leaveChannel 后设置失效，将恢复至默认。如果您离开房间后重新加入房间，需要重新调用本接口。
 * @par 参数说明
 * <table>
 *  <tr>
 *      <th>**参数名称**</th>
 *      <th>**类型**</th>
 *      <th>**描述**</th>
 *  </tr>
 *  <tr>
 *      <td>enable</td>
 *      <td>bool</td>
 *      <td>是否启用说话者音量提示：<ul><li>true：启用说话者音量提示。<li>false：关闭说话者音量提示。</td>
 *  <tr>
 *      <td>interval</td>
 *      <td>uint64_t</td>
 *      <td>指定音量提示的时间间隔。单位为毫秒。必须设置为 100 毫秒的整数倍值，建议设置为 200 毫秒以上。</td>
 *  </tr>
 * </table>
 * @par 示例代码
 * @code
 * //设置间隔为500ms的人声音量提示
 * rtc_engine_->enableAudioVolumeIndication(true, 500);
 * @endcode
 * @par 相关回调
 * 启用该方法后，只要房间内有发流用户，无论是否有人说话，SDK 都会在加入房间后根据预设的时间间隔触发 \ref
 * IRtcEngineEventHandlerEx::onRemoteAudioVolumeIndication  "onRemoteAudioVolumeIndication" 回调。
 * @par 相关接口
 * 若您希望在返回音量相关信息的同时检测是否有真实人声存在，请调用 \ref nertc::IRtcEngineEx::enableAudioVolumeIndication(bool
 * enable, uint64_t interval, bool enable_vad) "enableAudioVolumeIndication" 方法。
 * @return
 * - 0（kNERtcNoError）：方法调用成功。
 * - 其他：方法调用失败。
 *         - 30003（kNERtcErrInvalidParam）：参数错误，比如时间间隔小于 100ms。
 *         - 30005（kNERtcErrInvalidState）：状态错误，比如引擎未初始化。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_enable_audio_volume_indication(struct nertc_channel* self,
                                                                      bool enable,
                                                                      uint64_t interval,
                                                                      bool enable_vad);

/**
 * @if English
 * Enables or disables local audio capture.
 * <br>The method can enable the local audio again to start local audio capture and processing.
 * <br>The method does not affect receiving or playing remote audio and audio streams.
 * @note The method is different from \ref IRtcEngineEx::muteLocalAudioStream "muteLocalAudioStream" in:.
 * - \ref IRtcEngine::enableLocalAudio "enableLocalAudio": Enables local audio capture and processing.
 * - \ref IRtcEngineEx::muteLocalAudioStream "muteLocalAudioStream": Stops or continues publishing local audio streams.
 * @note The method enables the internal engine, which is still valid after you call \ref IRtcEngine::leaveChannel
 * "leaveChannel".
 * @since V4.5.0
 * @param[in] enabled
 * - true: Enables local audio feature again. You can enable local audio capture or processing by default.
 * - false: Disables local audio feature again. You can stop local audio capture or processing.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 开启/关闭本地音频采集
 * <br>该方法可以重新开启本地语音功能，重新开始本地音频采集及处理。
 * <br>该方法不影响接收或播放远端音频流。
 * @note 该方法与 \ref IRtcEngineEx::muteLocalAudioStream "muteLocalAudioStream" 的区别在于:
 * - \ref IRtcEngine::enableLocalAudio "enableLocalAudio": 开启本地语音采集及处理
 * - \ref IRtcEngineEx::muteLocalAudioStream "muteLocalAudioStream": 停止或继续发送本地音频流
 * @note 该方法设置内部引擎为启用状态，在 \ref IRtcEngine::leaveChannel "leaveChannel" 后仍然有效。
 * @since V4.5.0
 * @param[in] enabled
 * - true: 重新开启本地语音功能，即开启本地语音采集或处理（默认）
 * - false: 关闭本地语音功能，即停止本地语音采集或处理
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_enable_local_audio(struct nertc_channel* self, nertc_audio_stream_type stream_type, bool enabled);

/**
 * @if English
 * Enables or disabling publishing the local audio stream. The method is used to enable or disable publishing the local audio
 * stream.
 * @note
 * - This method does not change the state of the audio-recording device because the audio-recording devices are not disabled.
 * - The mute state is reset to unmuted after the call ends.
 * @since V4.5.0
 * @param[in] mute       Mute or Unmute.
 * - true: Mutes the local audio stream.
 * - false: Unmutes the local audio stream (Default).
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 开关本地音频发送。该方法用于允许或禁止向网络发送本地音频流。
 * @note
 * - 该方法不影响录音状态，因为并没有禁用录音设备。
 * - 静音状态会在通话结束后被重置为非静音
 * @since V4.5.0
 * @param[in] mute      静音/取消静音:
 * - true: 静音本地音频
 * - false: 取消静音本地音频（默认）
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_mute_local_audio_stream(struct nertc_channel* self, nertc_audio_stream_type stream_type, bool mute);

/**
 * @if English
 * Enables or disables local audio capture and rendering.
 * <br>The method enables local video capture.
 * @note
 * - You can call this method before or after you join a room.
 * - The method enables the internal engine, which is still valid after you call \ref IRtcEngine::leaveChannel "leaveChannel".
 * - After local video capture is successfully enabled or disabled,  the onUserVideoStop or onUserVideoStart callback is
 * remotely triggered.
 * @since V4.5.0
 * @param[in] enabled Whether to enable local video capture and rendering.
 * - true: Enables the local video capture and rendering.
 * - false: Disables the local camera device. After local video capture is disabled, remote users cannot receive video streams
 * from local users. However, local users can still receive video streams from remote users. If the setting is false, the
 * local camera is not required to call the method.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 开启或关闭本地视频采集和渲染。
 * <br>该方法启用本地视频采集功能。
 * @note
 * - 该方法在加入房间前和加入房间后均可调用。
 * - 该方法设置内部引擎为启用状态，在 \ref IRtcEngine::leaveChannel "leaveChannel" 后仍然有效。
 * - 成功启用或禁用本地视频采集和渲染后，远端会触发 onUserVideoStop 或 onUserVideoStart  回调。
 * @since V4.5.0
 * @param[in] enabled 是否启用本地视频采集和渲染:
 * - true: 开启本地视频采集和渲染 (默认)；
 * - false: 关闭使用本地摄像头设备。关闭后，远端用户会接收不到本地用户的视频流；但本地用户依然可以接收远端用户的视频流。设置为
 * false 时，该方法不需要本地有摄像头。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_enable_local_video(struct nertc_channel* self, nertc_video_stream_type stream_type, bool enabled);

/**
 * @if English
 * Stops or resumes sending the local video stream.
 * <br>If the method is called Successfully, onUserVideoMute is triggered remotely.
 * @note
 * - When you call the method to disable video streams,  the SDK doesn’t send local video streams but the camera is still
 * working.
 * - The method can be called before or after a user joins a room.
 * - If you stop publishing the local video stream by calling this method, the option is reset to the default state that
 * allows the app to publish the local video stream.
 * - \ref nertc::IRtcEngine::enableLocalVideo "enableLocalVideo" (false) is different from \ref
 * nertc::IRtcEngine::enableLocalVideo "enableLocalVideo" (false). The enableLocalVideo(false) method turns off local camera
 * devices. The muteLocalVideoStreamvideo method does not affect local video capture, or disable cameras, and responds faster.
 * @since V4.5.0
 * @param[in] mute
 * - true: Not publishing local video streams.
 * - false: Publishing local video streams (default).
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 取消或恢复发布本地视频流。
 * <br>成功调用该方法后，远端会触发 onUserVideoMute 回调。
 * @note
 * - 调用该方法禁视频流时，SDK 不再发送本地视频流，但摄像头仍然处于工作状态。
 * - 该方法在加入房间前后均可调用。
 * - 若调用该方法取消发布本地视频流，通话结束后会被重置为默认状态，即默认发布本地视频流。
 * - 该方法与 \ref nertc::IRtcEngine::enableLocalVideo "enableLocalVideo" (false) 的区别在于， \ref
 * nertc::IRtcEngine::enableLocalVideo "enableLocalVideo" (false)
 * 会关闭本地摄像头设备，muteLocalVideoStream不影响本地视频流采集，不禁用摄像头，且响应速度更快。
 * @since V4.5.0
 * @param[in] mute
 * - true: 不发送本地视频流
 * - false: 发送本地视频流（默认）
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_mute_local_video_stream(struct nertc_channel* self, nertc_video_stream_type stream_type, bool mute);

/**
 * @if English
 * Shares screens through specifying regions. Shares a certain screen or part of region of a screen. Users need to specify the
 * screen region they wants to share in the method. <br>When calling the method, you need to specify the screen region to be
 * shared, and share the overall frame of the screen or designated regions. <br>If you join a room and successfully call this
 * method to enable the substream, the onUserSubStreamVideoStart and setExcludeWindowList callback is remotely triggered.
 * @note
 * - The method applies to Windows only.
 * - The method enables video substreams.
 * @since V4.5.0
 * @param  screen_rect      The relative position of the screen to virtual screens that is shared.
 * @param  region_rect      The relative position of shared screen to the full screen. If you set the shared region beyond the
 * frame of the screen, only content within the screen is shared. If you set the value of width or height as 0, the full
 * screen is shared.
 * @param  capture_params   The configurations of screen sharing.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 *
 * @endif
 * @if Chinese
 * 开启屏幕共享，共享范围为指定屏幕的指定区域。
 * <br>调用该方法时，可以选择共享整个虚拟屏、指定屏幕，或虚拟屏、整个屏幕的某些区域范围。
 * <br>此方法调用成功后，远端触发 onUserSubStreamVideoStart 和 setExcludeWindowList 回调。
 *  @note
 * - 该方法仅适用于 Windows。macOS 平台请使用方法 startScreenCaptureByDisplayId。
 * - 该方法需要在加入房间后调用。
 * @since V4.5.0
 * @param  screen_rect      指定待共享的屏幕相对于虚拟屏的位置。
 * @param  region_rect
 * 指定待共享区域相对于整个屏幕屏幕的位置。如果设置的共享区域超出了屏幕的边界，则只共享屏幕内的内容；如果将 width 或 height
 * 设为 0, 则共享整个屏幕。
 * @param  capture_params   屏幕共享的编码参数配置。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_start_screen_capture_by_screen_rect(struct nertc_channel* self,const struct nertc_rectangle* screen_rect,const struct nertc_rectangle* region_rect,const struct nertc_screen_capture_parameters* capture_params);

/**
 * @if English
 * Enables screen sharing by specifying the ID of the screen. The content of screen sharing is sent by substreams.
 * <br>If you join a room and call this method to enable the substream, the onUserSubStreamVideoStart and
 onScreenCaptureStatus callback is remotely triggered.
 * @note
 * - The method applies to only macOS.
 * - The method enables video substreams.
 * @since V4.5.0
 * @param  display_id       The ID of the screen to be shared. Developers need to specify the screen they share through the
 parameters.
 * @param  region_rect      The relative position of shared screen to the full screen.
 * @param  capture_params   The configurations of screen sharing.
 * @return
 * - 0: Success.
 * - Other values: Failure.

 *  @endif
 *  @if Chinese
 * 通过指定屏幕 ID 开启屏幕共享，屏幕共享内容以辅流形式发送。
 * <br>此方法调用成功后，远端触发 onUserSubStreamVideoStart 回调。
 * @note
 * - 该方法仅适用于 macOS。Windows 平台请使用方法 startScreenCaptureByScreenRect。
 * - 该方法需要在加入房间后设置。
 * @since V4.5.0
 * @param  display_id       指定待共享的屏幕 ID。开发者需要自行实现枚举屏幕 ID 的方法，并通过该参数指定需要共享的屏幕。
 * @param  region_rect
 指定待共享的区域相对于整个窗口的位置。如果设置的共享区域超出了窗口的边界，则只共享窗口内的内容；如果宽或高为
 0，则共享整个窗口。
 * @param  capture_params   屏幕共享的参数配置，包括码率、帧率、编码策略、屏蔽窗口列表等。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_start_screen_capture_by_display_id(struct nertc_channel* self,uint64_t display_id,const struct nertc_rectangle* region_rect,const struct nertc_screen_capture_parameters* capture_params);

/**
 * @if English
 * Enables screen sharing by specifying the ID of the window. The content of screen sharing is sent by substreams.
 * <br>If you join a room and call this method to enable the substream, the onUserSubStreamVideoStart and setExcludeWindowList
 * callback is remotely triggered.
 * @note
 * - The method applies to Windows only and macOS.
 * - The method enables video substreams.
 * @since V4.5.0
 * @param  window_id        The ID of the window to be shared.
 * @param  region_rect      The relative position of shared screen to the full screen.
 * @param  capture_params   The configurations of screen sharing.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 *
 * @endif
 * @if Chinese
 * 通过指定窗口 ID 开启屏幕共享，屏幕共享内容以辅流形式发送。
 * <br>调用该方法时需要指定待共享的屏幕 ID，共享该屏幕的整体画面或指定区域。
 * <br>此方法调用成功后：
 * - Windows 平台远端触发 onUserSubStreamVideoStop 和 onScreenCaptureStatus 回调。
 * - macOS 平台远端触发 onUserSubStreamVideoStop 回调。
 * @note
 * - 该方法适用于 Windows 和 macOS。
 * - 该方法需要在加入房间后调用。
 * @since V4.5.0
 * @param  window_id        指定待共享的窗口 ID。
 * @param  region_rect
 * 指定待共享的区域相对于整个窗口的位置。如果设置的共享区域超出了窗口的边界，则只共享指定区域中窗口内的内容；如果宽或高为
 * 0，则共享整个窗口。
 * @param  capture_params   屏幕共享的参数配置，包括码率、帧率、编码策略、屏蔽窗口列表等。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_start_screen_capture_by_window_id(struct nertc_channel* self,void* window_id,const struct nertc_rectangle* region_rect,const struct nertc_screen_capture_parameters* capture_params);

/**
 * @if English
 * When sharing a screen or window, updates the shared region.
 * @since V4.5.0
 * @param  region_rect      The relative position of shared screen to the full screen. If you set the shared region beyond the
 * frame of the screen, only content within the screen is shared. If you set width or height as 0, the full screen is shared.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 *
 * @endif
 * @if Chinese
 * 在共享屏幕或窗口时，更新共享的区域。
 * <br>在 Windows 平台中，远端会触发 onScreenCaptureStatus 回调。
 * @since V4.5.0
 * @param  region_rect
 * 指定待共享的区域相对于整个窗口或屏幕的位置。如果设置的共享区域超出了边界，则只共享指定区域中，窗口或屏幕内的内容；如果宽或高为
 * 0，则共享整个窗口或屏幕。
 * @return
 * - 0: 方法调用成功。
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_update_screen_capture_region(struct nertc_channel* self,const struct nertc_rectangle* region_rect);

/**
* @if English
* Displays or hides the pointer during screen sharing.
* @since V4.6.10
* @param bool specifies whether to display the pointer.
* - true: displays the pointer.
* - false: hides the pointer.
* @return
* - 0: success
* - Others: failure
* @endif
* @if Chinese
* 在共享屏幕或窗口时，更新是否显示鼠标。
* @since V4.6.10
* @param capture_cursor 屏幕共享时是否捕捉鼠标光标。
* - true：共享屏幕时显示鼠标。
* - false：共享屏幕时不显示鼠标。
* @return
* - 0: 方法调用成功。
* - 其他: 方法调用失败
* @endif
*/
NERTC_API int NERTC_CALL nertc_channel_set_screen_capture_mouse_cursor(struct nertc_channel* self, bool capture_cursor);

/**
 * @if English
 * Stops screen sharing.
 * <br>If you use the method to disable the substream after joining a room, the onUserSubStreamVideoStop callback is remotely
 * triggered.
 * @since V4.5.0
 * @return
 * - 0: Success.
 * - Other values: Failure.
 *
 * @endif
 * @if Chinese
 * 停止屏幕共享。
 * <br>此方法调用成功后：
 * - Windows 平台远端触发 onUserSubStreamVideoStop 和 onScreenCaptureStatus 回调。
 * - macOS 平台远端触发 onUserSubStreamVideoStop 回调。
 * @since V4.5.0
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_stop_screen_capture(struct nertc_channel* self);

/**
 * @if English
 * Pauses screen sharing.
 * @since V4.5.0
 * @return
 * - 0: Success.
 * - Other values: Failure.
 *
 * @endif
 * @if Chinese
 * 暂停屏幕共享。
 * - 暂停屏幕共享后，共享区域内会持续显示暂停前的最后一帧画面，直至通过 resumeScreenCapture 恢复屏幕共享。
 * - 在 Windows 平台中，远端会触发 onScreenCaptureStatus 回调。
 * <p>@since V4.5.0
 * @return
 * - 0: 方法调用成功
 * - 其他: 方法调用失败
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_pause_screen_capture(struct nertc_channel* self);

/**
 * @if English
 * Resumes screen sharing.
 * @since V4.5.0
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 恢复屏幕共享。
 * <br>在 Windows 平台中，远端会触发 onScreenCaptureStatus 回调。
 * @since V4.5.0
 * @return
 * - 0: 方法调用成功
 * - 其他: 方法调用失败
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_resume_screen_capture(struct nertc_channel* self);

/**
 * @if English
 * Sets the window list that need to be blocked in capturing screens. The method can be dynamically called in the capturing.
 * @since V4.5.0
 * @param  window_list      The ID of the screen to be blocked.
 * @param  count            The number of windows that are needed to be blocked.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 *
 * @endif
 * @if Chinese
 * 设置共享整个屏幕或屏幕指定区域时，需要屏蔽的窗口列表。
 * <br>开启屏幕共享时，可以通过 NERtcScreenCaptureParameters 设置需要屏蔽的窗口列表；在 Windows
 * 平台中，开发者可以在开启屏幕共享后，通过此方法动态调整需要屏蔽的窗口列表。被屏蔽的窗口不会显示在屏幕共享区域中。
 * @note
 * - 在 Windows 平台中，该接口在屏幕共享过程中可动态调用；在 macOS 平台中，该接口需要在开启屏幕共享之前，即
 * startScreenCaptureByDisplayId 之前调用。
 * - 在 Windows 平台中，某些窗口在被屏蔽之后，如果被置于图层最上层，此窗口图像可能会黑屏。此时会触发
 * onScreenCaptureStatus.kScreenCaptureStatusCovered 回调，建议应用层在触发此回调时提醒用户将待分享的窗口置于最上层。
 * @since V4.5.0
 * @param  window_list      需要屏蔽的窗口 ID 列表。
 * @param  count            需屏蔽的窗口的数量。
 * @return
 * - 0: 方法调用成功
 * - 其他: 方法调用失败
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_set_exclude_window_list(struct nertc_channel* self, source_id_t* window_list, int count);

/**
 * @if Chinese
 * 更新屏幕共享参数。
 * <br>开始共享屏幕或窗口后，动态更新采集帧率，目标码率，编码分辨率等屏幕共享相关参数。
 * @since V4.6.20
 * @par 调用时机
 * 请在加入房间并成功开启屏幕共享后调用该方法。
 * @note
 * - 调用该方法会重新启动屏幕共享，因此建议不要频繁调用。
 * -
 * 可以通过该方法动态设置是否捕捉鼠标（capture_mouse_cursor）和设置排除窗口（excluded_window_list，excluded_window_count），同时这两项设置也可以通过
 * \ref IRtcEngineEx::setScreenCaptureMouseCursor "setScreenCaptureMouseCursor" 和 \ref IRtcEngineEx::setExcludeWindowList
 * "setExcludeWindowList"  方法实现。
 * @par 参数说明
 * <table>
 *  <tr>
 *      <th>**参数名称**</th>
 *      <th>**类型**</th>
 *      <th>**描述**</th>
 *  </tr>
 *  <tr>
 *      <td>captureParams</td>
 *      <td> \ref nertc::NERtcScreenCaptureParameters "NERtcScreenCaptureParameters"</td>
 *      <td>屏幕共享编码参数配置。</td>
 *  </tr>
 * </table>
 * @par 示例代码
 * @code
 * //调用该方法时，需要维护一个 nertc::NERtcScreenCaptureParameters captureParams 变量记录当前设置。更新设置的时候：
 * nertc::NERtcScreenCaptureParameters captureParams;
 * captureParams.field1 = new_value1;
 * captureParams.field2 = new_value2;
 * ...
 * updateScreenCaptureParameters(captureParams);
 * @endcode
 * @par 相关回调
 * 成功调用该方法后，会触发 \ref IRtcChannelEventHandler::onScreenCaptureStatus "onScreenCaptureStatus" 回调。
 * @return
 * - 0（kNERtcNoError）：方法调用成功。
 * - 其他：方法调用失败。
 *         - 30005（kErrorErrInvalidState）：多房间状态错误。
 *         - 30021（kNERtcErrDesktopCaptureInvalidParam）：传入的参数无效。
 *         - 30101（kNERtcErrChannelNotJoined）：未加入房间。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_update_screen_capture_parameters(struct nertc_channel* self, const struct nertc_screen_capture_parameters* capture_params);

/**
 * @if English
 * Sets local views.
 * <br>This method is used to set the display information about the local video. The method is applicable for only local
 * users. Remote users are not affected. <br>Apps can call this API operation to associate with the view that plays local
 * video streams. During application development, in most cases, before joining a room, you must first call this method to set
 * the local video view after the SDK is initialized.
 * @note  If you use external rendering on the Mac platform, you must set the rendering before the SDK is initialized.
 * @since V4.5.0
 * @param[in] canvas The video canvas information.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置本地视图。
 * <br>该方法设置本地视频显示信息。只影响本地用户看到的视频画面，不影响远端。
 * <br>App 通过调用此接口绑定本地视频流的显示视窗(view)。 在 App
 * 开发中，通常在初始化后调用该方法进行本地视频设置，然后再加入房间。
 * @since V4.5.0
 * @note mac端若使用外部渲染，必须在 SDK 初始化时设置。
 * @param[in] canvas 视频画布信息
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_setup_local_video_canvas(struct nertc_channel* self, nertc_video_stream_type type, struct nertc_video_canvas* canvas);

/**
 * @if English
 * Sets the display mode for local substreams video of screen sharing.
 * This method is used to set the display mode about the local view. The application can repeatedly call the method to change
 * the display mode.
 * @note You must set the local canvas for local substreams through setupLocalSubStreamVideoCanvas.
 * @since V4.5.0
 * @param[in] scaling_mode      The video display mode. #NERtcVideoScalingMode.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置本地视图显示模式。
 * 该方法设置本地视图显示模式。 App 可以多次调用此方法更改显示模式。
 * @note 在打开屏幕共享前必须设置本地辅流画布。
 * @since V4.5.0
 * @param[in] scaling_mode      视频显示模式: #NERtcVideoScalingMode
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_set_local_render_mode(struct nertc_channel* self, nertc_video_stream_type type, nertc_video_scaling_mode scaling_mode);

/**
 * @if English
 * Sets the mirror mode of the local video.
 * The method is used to set whether to enable the mirror mode for the local video. The mirror code determines whether to flip
 * the screen view right or left. Mirror mode for local videos only affects what local users view. The views of remote users
 * are not affected. App can repeatedly call this method to modify the mirror mode.
 * @since V4.5.0
 * @param[in] mirror_mode       The video mirror mode. For more information, see {@link NERtcVideoMirrorMode}.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置本地视频镜像模式。
 * 该方法用于设置本地视频是否开启镜像模式，即画面是否左右翻转。
 * 本地的视频镜像模式仅影响本地用户所见，不影响远端用户所见。App 可以多次调用此方法更改镜像模式。
 * @since V4.5.0
 *  @param[in] mirror_mode      视频镜像模式。详细信息请参考 {@link NERtcVideoMirrorMode}。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_set_local_video_mirror_mode(struct nertc_channel* self, nertc_video_stream_type type, nertc_video_mirror_mode mirror_mode);

/**
 * @if English
 *  Sets views for remote users.
 * <br>This method is used to associate remote users with display views and configure the rendering mode and mirror mode for
 * remote views that are displayed locally. The method affects only video display viewed by local users.
 * @note
 * - You need to specify the uid of remote video when the interface is called. In general cases, the uid can be set before
 * users join the room.
 * - If the user ID is not retrieved, the App calls this method after the onUserJoined event is triggered. To disassociate a
 * specified user from a view, you can leave the canvas parameter empty.
 * - After a user leaves the room, the association between a remote user and the view is cleared.
 * @since V4.5.0
 * @param[in] uid       The ID of a remote user.
 * @param[in] canvas    The video canvas information.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置远端用户视图。
 * <br>该方法绑定远端用户和显示视图，并设置远端用户视图在本地显示时的渲染模式和镜像模式，只影响本地用户看到的视频画面。
 * @note
 * - 调用该接口时需要指定远端视频的 uid，一般可以在用户加入后设置好。
 * - 如果 App 无法事先知道对方的用户 ID，可以在 APP 收到 onUserJoined 事件时设置。- 解除某个用户的绑定视图可以把 canvas
 * 设置为空。
 * - 退出房间后，SDK 会清除远程用户和视图的绑定关系。
 * @since V4.5.0
 * @param[in] uid       远端用户 ID。
 * @param[in] canvas    视频画布信息
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_setup_remote_video_canvas(struct nertc_channel* self,nertc_uid_t uid,nertc_video_stream_type type, struct nertc_video_canvas* canvas);

/**
 * @if English
 * Sets display mode for remote views.
 * This method is used to set the display mode for the remote view. App can repeatedly call this method to modify the display
 * mode.
 * @since V4.5.0
 * @param[in] uid           The ID of a remote user.
 * @param[in] scaling_mode  The video display mode. #NERtcVideoScalingMode.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置远端视图显示模式。
 * 该方法设置远端视图显示模式。App 可以多次调用此方法更改显示模式。
 * @since V4.5.0
 * @param[in] uid           远端用户 ID。
 * @param[in] scaling_mode  视频显示模式: #NERtcVideoScalingMode
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_set_remote_render_mode(struct nertc_channel* self, nertc_uid_t uid, nertc_video_stream_type type, nertc_video_scaling_mode scaling_mode);

/**
 * @if English
 * Sets the role of a user in live streaming.
 * <br>The method sets the role to host or audience. The permissions of a host and a viewer are different.
 * - A host has the permissions to open or close a camera, publish streams, call methods related to publishing streams in
 * interactive live streaming. The status of the host is visible to the users in the room when the host joins or leaves the
 * room.
 * - The audience has no permissions to open or close a camera, call methods related to publishing streams in interactive live
 * streaming, and is invisible to other users in the room when the user that has the audience role joins or leaves the room.
 * <p>@since V4.5.0
 * @note
 * - By default, a user joins a room as a host.
 * - Before a user joins a room, the user can call this method to change the client role to audience. Users can switch the
 * role of a user through the interface after joining the room.
 * - If the user switches the role to audience, the SDK automatically closes the audio and video devices.
 * @param[in] role The role of a user. NERtcClientRole.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 在直播场景中设置用户角色。
 * <br>用户角色支持设置为主播或观众，主播和观众的权限不同。
 * - 主播：可以开关摄像头等设备、可以发布流、可以操作互动直播推流相关接口、上下线对其他房间内用户可见。
 * - 观众：不可以开关摄像头等设备、不可以发布流、不可以操作互动直播推流相关接口、上下线对其他房间内用户不可见。
 * <p>@note
 * - 默认情况下用户以主播角色加入房间。
 * - 在加入房间前，用户可以调用本接口切换本端角色为观众。在加入房间后，用户也可以通过本接口切换用户角色。
 * - 用户切换为观众角色时，SDK 会自动关闭音视频设备。
 * @since V4.5.0
 * @param[in] role 用户角色。 NERtcClientRole
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_set_client_role(struct nertc_channel* self, nertc_client_role role);

/**
 * @if English
 * Sets the priority of media streams from a local user.
 * <br>If a user has a high priority, the media stream from the user also has a high priority. In unreliable network
 connections, the SDK guarantees the quality the media stream from users with a high priority.
 * @note
 * - You must call the method before you call joinChannel.
 * - After switching channels, media priority changes to the default value of normal priority.
 * - An RTC room has only one user that has a high priority. We recommend that only one user in a room call the
 setLocalMediaPriority method to set the local media stream a high priority. Otherwise, you need to enable the preempt mode to
 ensure the high priority of the local media stream.
 * @since V4.5.0
 * @param priority      The priority of the local media stream. The default value is #kNERtcMediaPriorityNormal. For more
 information, see #NERtcMediaPriorityType.
 * @param is_preemptive specifies whether to enable the preempt mode. The default value is false, which indicates that the
 preempt mode is disabled.
                        - If the preempt mode is enabled, the local media stream preempts the high priority over other users.
 The priority of the media stream whose priority is taken becomes normal. After the user whose priority is taken leaves the
 room, other users still keep the normal priority.
                        - If the preempt mode is disabled, and a user in the room has a high priority. After that, the high
 priority of the local client remains invalid and is still normal.
 * @return
        - 0: Success.
        - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置本地用户的媒体流优先级。
 * <br>如果某个用户的优先级为高，那么该用户媒体流的优先级就会高于其他用户，弱网环境下 SDK
 会优先保证其他用户收到的、高优先级用户的媒体流的质量。
 * @note
 * - 请在加入房间（joinChannel）前调用此方法。
 * - 快速切换房间 （switchChannel） 后，媒体优先级会恢复为默认值，即普通优先级。
 * - 一个音视频房间中只有一个高优先级的用户。建议房间中只有一位用户调用 setLocalMediaPriority
 将本端媒体流设为高优先级，否则需要开启抢占模式，保证本地用户的高优先级设置生效。
 * @since V4.5.0
 * @param priority      本地用户的媒体流优先级，默认为 #kNERtcMediaPriorityNormal 。详细信息请参考 #NERtcMediaPriorityType 。
 * @param is_preemptive 是否开启抢占模式。默认为 false，即不开启。
                        -
 抢占模式开启后，本地用户可以抢占其他用户的高优先级，被抢占的用户的媒体优先级变为普通优先级，在抢占者退出房间后，其他用户的优先级仍旧维持普通优先级。
                        - 抢占模式关闭时，如果房间中已有高优先级用户，则本地用户的高优先级设置不生效，仍旧为普通优先级。
 * @return
        - 0: 方法调用成功；
        - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_set_local_media_priority(struct nertc_channel* self,nertc_media_priority_type priority,bool is_preemptive);

/**
 * @if English
 * Gets the current connection status.
 * @since V4.5.0
 * @return Returns the current network status. #NERtcConnectionStateType.
 * @endif
 * @if Chinese
 * 获取当前网络状态。
 * @since V4.5.0
 * @return 当前网络状态。#NERtcConnectionStateType.
 * @endif
 */
NERTC_API nertc_connection_state_type NERTC_CALL nertc_channel_get_connection_state(struct nertc_channel* self);

/**
 * @if English
 * Sets the camera capturer configuration.
 * <br>For a video call or live streaming, generally the SDK controls the camera output parameters. By default, the SDK
 * matches the most appropriate resolution based on the user's setVideoConfig configuration. When the default camera capture
 * settings do not meet special requirements, we recommend using this method to set the camera capturer configuration:
 * - If you want better quality for the local video preview, we recommend setting config as kNERtcCameraOutputQuality. The SDK
 * sets the camera output parameters with higher picture quality.
 * - To customize the width and height of the video image captured by the local camera, set the camera capture configuration
 * as kNERtcCameraOutputManual. <p>@note
 * - Call this method before or after joining the channel. The setting takes effect immediately without restarting the camera.
 * - Higher collection parameters means higher performance consumption, such as CPU and memory usage, especially when video
 * pre-processing is enabled.
 * @since V4.5.0
 * @param config The camera capturer configuration.
 * @return {@code 0} A value of 0 returned indicates that the method call is successful. Otherwise, the method call fails.
 * @endif
 * @if Chinese
 * 设置本地摄像头的采集偏好等配置。
 * <br>在视频通话或直播中，SDK 自动控制摄像头的输出参数。默认情况下，SDK 根据用户的 setVideoConfig
 * 配置匹配最合适的分辨率进行采集。但是在部分业务场景中，如果采集画面质量无法满足实际需求，可以调用该接口调整摄像头的采集配置。
 * - 需要采集并预览高清画质时，可以将采集偏好设置为 kNERtcCameraOutputQuality，此时 SDK
 * 会自动设置较高的摄像头输出参数，本地采集与预览画面比编码参数更加清晰。
 * - 需要自定义设置摄像头采集的视频尺寸时，请通过参数 preference 将采集偏好设为 kNERtcCameraOutputManual，并通过
 * NERtcCameraPreference 中的 captureWidth 和 captureHeight 自定义设置本地摄像头采集的视频宽高。 <p>@note
 * - 该方法可以在加入房间前后动态调用，设置成功后立即生效，无需重启摄像头。
 * - 设置更高的采集参数会导致更大的性能消耗，例如 CPU 和内存占用等，尤其是在开启视频前处理的场景下。
 * @since V4.5.0
 * @param config 摄像头采集配置。详细说明请参考 nertc::NERtcCameraCaptureConfig 。
 * @return {@code 0} 方法调用成功，其他调用失败
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_set_camera_capture_config(struct nertc_channel* self, nertc_video_stream_type stream_type, const struct nertc_camera_capture_config* config);

/**
 * @if English
 * Sets local video parameters.
 * <br>You can call this method before or after you join the room.
 * @note
 * - Each profile has a set of video parameters, such as resolution, frame rate, and bitrate. All the specified values of the
 * parameters are the maximum values in optimal conditions. If the video engine cannot use the maximum value of resolution,
 * due to poor network performance, the value closest to the maximum value is taken.
 * - This method is a full parameter configuration method. If this method is invoked repeatedly, the SDK refreshes all
 * previous parameter configurations and uses the latest parameter.  Therefore, you need to set all parameters each time you
 * modify the configuration, otherwise, unconfigured parameters will be set to the default value.
 * - Since V4.5.0, 'setVideoConfig' method takes effect in real time. In previous versions, the setting takes effect the next
 * time local video is enabled.
 * @since V4.5.0
 * @param[in] config        Sets the video encoding parameters. For more information, see {@link NERtcVideoConfig}.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置本地视频主流的编码属性。
 * <br>可以在加入房间前或加入房间后调用。
 * @note
 * - 每个属性对应一套视频参数，例如分辨率、帧率、码率等。
 * 所有设置的参数均为理想情况下的最大值。当视频引擎因网络环境等原因无法达到设置的分辨率的最大值时，会取最接近最大值的那个值。
 * - setVideoConfig 为全量参数配置接口，重复调用此接口时，SDK
 * 会刷新此前的所有参数配置，以最新的传参为准。所以每次修改配置时都需要设置所有参数，未设置的参数将取默认值。
 * - V4.5.0 开始，`setVideoConfig` 方法实时生效；此前的版本中，`setVideoConfig` 方法设置成功后，下次开启本端视频时生效。
 * @since V4.5.0
 * @param[in] config        视频编码属性配置，详细信息请参考 {@link NERtcVideoConfig}。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_set_video_config(struct nertc_channel* self, nertc_video_stream_type stream_type, const struct nertc_video_config* config);

/**
 * @if English
 * Specifies whether to enable or disable the dual stream mode.
 * <br>The method sets the single-stream mode or dual-stream mode. If the dual-stream mode is enabled, the receiver can choose
 * to receive the high-quality stream or low-quality stream video. The high-quality stream has a high resolution and high
 * bitrate. The low-quality stream has a low resolution and low bitrate.
 * @note
 * - The method applies to camera data only. Video streams from external input and screen sharing are not affected.
 * - You can call this method before or after you join a room. After the method is set, it can take effect after restarting
 * the camera.
 * @since V4.5.0
 * @param[in] enable        Whether to enable dual-stream mode.
 * - true: Enables the dual-stream mode. This is the default value.
 * - false: Disables the dual-stream mode.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置是否开启视频大小流模式。
 * <br>该方法设置单流或者双流模式。发送端开启双流模式后，接收端可以选择接收大流还是小流。其中，大流指高分辨率、高码率的视频流，小流指低分辨率、低码率的视频流。
 * @note
 * - 该方法只对摄像头数据生效，自定义输入、屏幕共享等视频流无效。
 * - 该方法在加入房间前后都能调用。设置后，会在摄像头重启后生效。
 * @since V4.5.0
 * @param[in] enable        指定是否开启双流模式。
 * - true: （默认）开启双流模式。
 * - false: 关闭双流模式。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_enable_dual_stream_mode(struct nertc_channel* self, bool enable);

/**
 * @if English
 * Unsubscribes from or subscribes to audio streams from specified remote users.
 * <br>After a user joins a channel, audio streams from all remote users are subscribed by default. You can call this method
 * to unsubscribe from or subscribe to audio streams from all remote users.
 * @note  When the kNERtcKeyAutoSubscribeAudio is enabled by default, users cannot manually modify the state of audio
 * subscription.
 * @since V4.5.0
 * @param[in] uid           The user ID.
 * @param[in] subscribe
 * - true: Subscribes to specified audio streams (default).
 * - false: Unsubscribes from specified audio streams.
 *  @return
 * - 0: Success.
 * - 30005: State exception that is caused by the invalid interface if users enable the automatic subscription.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 取消或恢复订阅指定远端用户音频流。
 * <br>加入房间时，默认订阅所有远端用户的音频流，您可以通过此方法取消或恢复订阅指定远端用户的音频流。
 * @note 当kNERtcKeyAutoSubscribeAudio默认打开时，用户不能手动修改音频订阅状态
 * @since V4.5.0
 * @param[in] uid           指定用户的 ID。
 * @param[in] subscribe     是否订阅远端用户音频流。
 * - true: 订阅指定音频流（默认）。
 * - false: 取消订阅指定音频流。
 * @return
 * - 0: 方法调用成功。
 * - 30005: 状态异常，可能是自动订阅打开，导致该接口无效。
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_subscribe_remote_audio_stream(struct nertc_channel* self, nertc_audio_stream_type stream_type, nertc_uid_t uid, bool subscribe);

/**
 * @if English
 * Unsubscribes or subscribes to audio streams from all remote users.
 * @note
 * - When joins a room, local user subscribe audio streams from all remote users by default. Under the circumstances, do not
 * call subscribeAllRemoteAudioStream (YES) to subscribe audio streams again.
 * - You can call this method before joining a channel.
 * @since V4.5.0
 * @param subscribe Whether to unsubscribe audio streams from all remote users.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 取消或恢复订阅所有远端用户音频流。
 * @note
 * - 加入房间时，默认订阅所有远端用户的音频，此时请勿调用 subscribeAllRemoteAudioStream(YES) 重复订阅所有远端用户的音频流。
 * - 该方法需要在加入房间后调用，对后续加入的用户也同样生效。
 * @since V4.5.0
 * @param subscribe 是否取消订阅所有远端用户的音频流。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_subscribe_all_remote_audio_stream(struct nertc_channel* self, bool subscribe);

/**
 * @if English
 * Sets the local audio stream can be subscribed by specified participants in a room.
 * <br>All participants in the room can subscribe to the local audio stream by default.
 * @note
 *  - The API must be called after a user joins a room.
 *  - The API cannot be called by user IDs out of the room.
 * @since V4.6.10
 * @param[in] uidArray The list of user IDs that can subscribe to the local audio stream.
 * @note The list contains all participants in a room. If the value is empty or null, all participants can subscribe to the
 * local audio stream.
 * @param[in] size The length of the uid_array array.
 * @return
 * - 0: success
 * - Others: failure.
 * @endif
 * @if Chinese
 * 设置自己的音频只能被房间内指定的人订阅。
 * <br>默认房间所有其他人都可以订阅自己的音频。
 * @note
 *  - 此接口需要在加入房间成功后调用。
 *  - 对于调用接口时不在房间的 uid 不生效。
 * @since V4.6.10
 * @param[in] uid_array 可订阅自己音频的用户uid 列表。
 *                      @note 此列表为全量列表。如果列表为空或 null，表示其他所有人均可订阅自己的音频。
 * @param[in] size uid_array 的数组长度。
 * @return
 * - 0：方法调用成功。
 * - 其他：方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_set_audio_subscribe_only_by(struct nertc_channel* self,nertc_uid_t* uid_array, uint32_t size);

/**
 * @if Chinese
 * 你可以调用该方法指定只订阅的音频流。
 * @note
 *  - 此接口需要在加入房间成功后调用。
 *  - 对于调用接口时不在房间的 uid 不生效。
 * @since V5.4.101
 * @param[in] uid_array 只订阅此 用户uid列表 的音频。
 *                      @note 此列表为全量列表。如果列表为空或 null，取消订阅白名单。
 * @param[in] size uid_array 的数组长度。
 * @return
 * - 0：方法调用成功。
 * - 其他：方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_set_subscribe_audio_allow_list(struct nertc_channel* self, nertc_uid_t* uid_array, uint32_t size);

/**
 * @if Chinese
 * 你可以调用该方法指定不订阅的音频流。
 * @note
 *  - 此接口需要在加入房间成功后调用。
 *  - 对于调用接口时不在房间的 uid 不生效。
 * @since V5.4.101
 * @param[in] uid_array 不订阅此 用户uid列表 的音频。
 *                      @note 此列表为全量列表。如果列表为空或 null，取消订阅黑名单。
 * @param[in] size uid_array 的数组长度。
 * @return
 * - 0：方法调用成功。
 * - 其他：方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_set_subscribe_audio_block_list(struct nertc_channel* self, nertc_uid_t* uid_array, uint32_t size);


/**
 * @if English
 * Subscribes or unsubscribes video streams from specified remote users.
 * - After a user joins a room, the video streams from remote users are not subscribed by default. If you want to view video
 * streams from specified remote users, you can call this method to subscribe to the video streams from the user when the user
 * joins the room or publishes the video streams.
 * - This method can be called only if a user joins a room.
 * @since V4.5.0
 * @param[in] uid       The user ID.
 * @param[in] type      The type of the subscribed video streams. #NERtcRemoteVideoStreamType.
 * @param[in] subscribe
 * - true: Subscribes to specified video streams. This is the default value.
 * - false: Not subscribing to specified video streams.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 订阅或取消订阅指定远端用户的视频流。
 * -
 * 用户加入房间之后，默认不订阅远端用户的视频流，如果希望看到指定远端用户的视频，可以在监听到对方加入房间或发布视频流之后，通过此方法订阅该用户的视频流。
 * - 该方法需要在加入房间后调用。
 * @since V4.5.0
 * @param[in] uid       指定用户的用户 ID。
 * @param[in] type      订阅的视频流类型。 #NERtcRemoteVideoStreamType
 * @param[in] subscribe
 * - true: （默认）订阅指定视频流。
 * - false: 不订阅指定视频流。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_subscribe_remote_video_stream(struct nertc_channel* self,
                                                                     nertc_uid_t uid,
                                                                     nertc_video_stream_type stream_type,
                                                                     nertc_remote_video_stream_type type,
                                                                     bool subscribe);

/**
 * @if English
 * After the method is successfully called, the current user can receive the notification about the status of the live stream.
 * @note
 * - The method is applicable to only live streaming.
 * - You can call the method in a room. The method is valid in calls.
 * - Only one address for the relayed stream is added in each call. You need to call the method for multiple times if you want
 * to push many streams. An RTC room with the same channelid can create three different streaming tasks.
 * - After the method is successfully called, the current user will receive related-status notifications of the live stream.
 * @since V4.5.0
 * @param[in] info indicates information of live task. For more information, see \ref NERtcLiveStreamTaskInfo
 * "NERtcLiveStreamTaskInfo".
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 添加房间推流任务，成功添加后当前用户可以收到该直播流的状态通知。
 * @note
 * - 该方法仅适用直播场景。
 * - 请在房间内调用该方法，该方法在通话中有效。
 * - 该方法每次只能增加一路旁路推流地址。如需推送多路流，则需多次调用该方法。同一个音视频房间（即同一个 channelid）可以创建 3
 * 个不同的推流任务。
 * - 成功添加推流任务后，当前用户会收到该直播流的相关状态通知。
 * @since V4.5.0
 * @param[in] info 直播任务信息。详细信息请参考 \ref NERtcLiveStreamTaskInfo "NERtcLiveStreamTaskInfo"
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_add_live_stream_task(struct nertc_channel* self,const struct nertc_live_stream_task_info* info);

/**
 * @if English
 * Updates and modifies a push task in a room.
 * @note
 * - The method is applicable to only live streaming.
 * - You can call the method in a room. The method is valid in calls.
 * @since V4.5.0
 * @param[in] info indicates information of live task. For more information, see \ref NERtcLiveStreamTaskInfo
 * "NERtcLiveStreamTaskInfo".
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 更新修改房间推流任务。
 * @note
 * - 该方法仅适用直播场景。
 * - 请在房间内调用该方法，该方法在通话中有效。
 * @since V4.5.0
 * @param[in] info 直播任务信息。详细信息请参考 \ref NERtcLiveStreamTaskInfo "NERtcLiveStreamTaskInfo"
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_update_live_stream_task(struct nertc_channel* self,const struct nertc_live_stream_task_info* info);

/**
 * @if English
 * Deletes a push task.
 * @note
 * - The method is applicable to only live streaming.
 * - You can call the method in a room. The method is valid in calls.
 * - When calls stop and all members in the room leave the room, the SDK automatically deletes the streaming task. If some
 * users are still in the room, users who create the streaming task need to delete the streaming task.
 * @since V4.5.0
 * @param[in] task_id  The ID of a live streaming task.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 删除房间推流任务。
 * @note
 * - 该方法仅适用直播场景。
 * - 请在房间内调用该方法，该方法在通话中有效。
 * - 通话结束，房间成员全部离开房间后，推流任务会自动删除。如果房间内还有用户存在，则需要创建推流任务的用户删除推流任务。
 * @since V4.5.0
 * @param[in] task_id  直播任务 ID。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_remove_live_stream_task(struct nertc_channel* self, const char* task_id);

/**
 * @if English
 * Sends SEI messages.
 * <br>While the local video stream is pushed, SEI data is also sent to sync some additional information. After SEI data is
 * sent, the receiver can retrieve the content by listening on \ref IRtcEngineEventHandlerEx::onRecvSEIMsg callback.
 * - Condition: After the video stream (mainstream) is enabled, the function can be invoked.
 * - Data size limits: The SEI data can contain a maximum of 4,096 bytes in size. Sending an SEI message fails if the data
 * exceeds the size limit. If a large amount of data is sent, the video bitrate rises. This degrades the video quality or
 * causes broken video frames.
 * - Frequency limit: we recommend that the maximum video frame rate does not exceed 10 fps.
 * - Time to take effect: After the method is called, the SEI data is sent from the next frame in the fastest fashion or after
 * the next 5 frames at the slowest pace. <p>@note
 * - The SEI data is transmitted together with the video stream. Frame loss may occur in poor network connection. The SEI data
 * will also get lost. We recommend that you send the data many times within the transmission frequency limits. In this way,
 * the receiver can get the data.
 * - By default, the SEI is transmitted by using the mainstream channel.
 * @since V4.5.0
 * @param data      The custom SEI frame data.
 * @param length    The custom SEI data size whose maximum value does not exceed 4096 bytes.
 * @param type      The type of the stream channel with which the SEI data is transmitted. For more information, see
 * #NERtcVideoStreamType.
 * @return The value returned. A value of 0 That the operation is successful.
 * - Success: Successfully joins the queue to be sent. The data are sent after the closest video frame.
 * - failure: Date are limitedly sent for the high sent frequency and the overloaded queue. Or, the maximum data size exceeds
 * 4k.
 * @endif
 * @if Chinese
 * 发送媒体补充增强信息（SEI）。
 * <br>在本端推流传输视频流数据同时，发送流媒体补充增强信息来同步一些其他附加信息。当推流方发送 SEI 后，拉流方可通过监听 \ref
 * IRtcEngineEventHandlerEx::onRecvSEIMsg 的回调获取 SEI 内容。
 * - 调用时机：视频流（主流）开启后，可调用此函数。
 * - 数据长度限制： SEI 最大数据长度为 4096
 * 字节，超限会发送失败。如果频繁发送大量数据会导致视频码率增大，可能会导致视频画质下降甚至卡顿。
 * - 发送频率限制：最高为视频发送的帧率，建议不超过 10 次/秒。
 * - 生效时间：调用本接口之后，最快在下一帧视频数据帧之后发送 SEI 数据，最慢在接下来的 5 帧视频之后发送。
 * <p>@note
 * - SEI 数据跟随视频帧发送，由于在弱网环境下可能丢帧，SEI
 * 数据也可能随之丢失，所以建议在发送频率限制之内多次发送，保证接收端收到的概率。
 * - 调用本接口时，默认使用主流通道发送 SEI。
 * @since V4.5.0
 * @param data      自定义 SEI 数据。
 * @param length    自定义 SEI 数据长度，最大不超过 4096 字节。
 * @param type      发送 SEI 时，使用的流通道类型。详细信息请参考 #NERtcVideoStreamType 。
 * @return 操作返回值，成功则返回 0
 * - 成功:  成功进入待发送队列，会在最近的视频帧之后发送该数据
 * - 失败:  数据被限制发送，可能发送的频率太高，队列已经满了，或者数据大小超过最大值 4k
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_send_sei_msg(struct nertc_channel* self,const unsigned char* data,int length,nertc_video_stream_type type);

/**
 * @if English
 * Takes a local video snapshot.
 * <br>The takeLocalSnapshot method takes a local video snapshot on the local substream or local mainstream, and call \ref
 * NERtcTakeSnapshotCallback "NERtcTakeSnapshotCallback::onTakeSnapshotResult" callback to return data of snapshot screen.
 * @note
 * - Before you call the method to capture the snapshot from the mainstream, you must first call startVideoPreview or
 * enableLocalVideo, and joinChannel.
 * - Before you call the method to capture the snapshot from the substream, you must first call startScreenCapture, and
 * joinChannel.
 * - You can set text, timestamp, and image watermarks at the same time. If different types of watermarks overlap, the layers
 * override previous layers following image, text, and timestamp.
 * @since V4.5.0
 * @param stream_type       The video stream type of the snapshot. You can set the value to mainstream or substream. For more
 * information, see #NERtcVideoStreamType.
 * @param callback          The snapshot callback. For information, see \ref NERtcTakeSnapshotCallback.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 本地视频画面截图。
 * <br>调用 takeLocalSnapshot 截取本地主流或本地辅流的视频画面，并通过 \ref NERtcTakeSnapshotCallback
 * "NERtcTakeSnapshotCallback::onTakeSnapshotResult" 回调返回截图画面的数据。
 * @note
 * - 本地主流截图，需要在 startPreview 或者 enableLocalVideo 并 joinChannel 成功之后调用。
 * - 本地辅流截图，需要在 startScreenCapture 并 joinChannel 成功之后调用。
 * - 同时设置文字、时间戳或图片水印时，如果不同类型的水印位置有重叠，会按照图片、文本、时间戳的顺序进行图层覆盖。
 * @since V4.5.0
 * @param stream_type       截图的视频流类型。支持设置为主流或辅流。详细信息请参考 #NERtcVideoStreamType 。
 * @param callback          截图回调。详细信息请参考 \ref NERtcTakeSnapshotCallback 。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_take_local_snapshot(struct nertc_channel* self,
                                                           nertc_video_stream_type stream_type,
                                                           on_take_snapshot_callback callback);

/**
 * @if English
 * Takes a snapshot of a remote video.
 * <br>You can call takeRemoteSnapshot to specify the uid of video screen of remote mainstreams and substreams, and returns
 * screenshot data of \ref NERtcTakeSnapshotCallback "NERtcTakeSnapshotCallback::onTakeSnapshotResult" callback.
 * @note
 * - You need to call takeRemoteSnapshot after receiving callbacks of onUserVideoStart and onUserSubStreamVideoStart.
 * - You can set text, timestamp, and image watermarks at the same time. If different types of watermarks overlap, the layers
 * override previous layers following image, text, and timestamp.
 * @since V4.5.0
 * @param uid           The ID of a remote user.
 * @param stream_type   The video stream type of the snapshot. You can set the value to mainstream or substream. For more
 * information, see #NERtcVideoStreamType.
 * @param callback      The snapshot callback. For information, see \ref NERtcTakeSnapshotCallback.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 远端视频画面截图。
 * <br>调用 takeRemoteSnapshot 截取指定 uid 远端主流和远端辅流的视频画面，并通过 \ref NERtcTakeSnapshotCallback
 * "NERtcTakeSnapshotCallback::onTakeSnapshotResult" 回调返回截图画面的数据。
 * @note
 * - takeRemoteSnapshot 需要在收到 onUserVideoStart 与 onUserSubStreamVideoStart 回调之后调用。
 * - 同时设置文字、时间戳或图片水印时，如果不同类型的水印位置有重叠，会按照图片、文本、时间戳的顺序进行图层覆盖。
 * @since V4.5.0
 * @param uid           远端用户 ID。
 * @param stream_type   截图的视频流类型。支持设置为主流或辅流。详细信息请参考 #NERtcVideoStreamType 。
 * @param callback      截图回调。详细信息请参考 \ref NERtcTakeSnapshotCallback 。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_take_remote_snapshot(struct nertc_channel* self,
                                                            nertc_uid_t uid,
                                                            nertc_video_stream_type stream_type,
                                                            on_take_snapshot_callback callback);

/**
 * @if English
 * Adjusts the volume of captured signals.
 * @note The method only adjusts the volume of captured signals in the application programs without modifying the volumes of the
 * device. If you need to modify the volume of the device, see related interfaces of device management.
 * @param[in] volume indicates the volume of the captured recording. Valid values: 0 to 400. Where:
 * - 0: Mute.
 * - 100: The original volume.
 * - 400: The maximum value can be four times the original volume. The limit value is protected.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 调节采集信号音量。
 * @note 该方法仅调节应用程序中的采集信号音量，不修改设备音量。如果需要修改设备音量，请查看设备管理相关接口。
 * @param[in] volume 采集录音音量，取值范围为 [0, 400]。其中：
 * - 0: 静音；
 * - 100: 原始音量；
 * - 400: 最大可为原始音量的 4 倍（自带溢出保护）。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_adjust_recording_signal_volume(struct nertc_channel* self, int volume);

/**
 * @if English
 * Adjusts the volume of the audio local playback.
 * @note The method only adjusts the volume of captured signals in the application programs without modifying the volumes of the
 * device. If you need to modify the volume of the device, see related interfaces of device management.
 * @param[in] volume indicates the playback volume. Valid range: 0 to 400. Where:
 * - 0: Mute.
 * - 100: The original volume.
 * - 400: The maximum value can be four times the original volume. The limit value is protected.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 调节本地播放音量。
 * @note 该方法仅调节应用程序中音量，不修改设备音量。如果需要修改设备音量，请查看设备管理相关接口。
 * @param[in] volume 播放音量。取值范围为 [0, 400]。其中：
 * - 0:  静音；
 * - 100: 原始音量；
 * - 400: 最大可为原始音量的 4 倍（自带溢出保护）。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_adjust_playback_signal_volume(struct nertc_channel* self, int volume);

/**
 * @if English
 * Adjusts the volume of local signal playback from a specified remote user.
 * <br>After you join the room, you can call the method to adjust the volume of local audio playback from different remote
 users or repeatedly adjust the volume of audio playback from a specified remote user.
 * @note
 * - You can call this method after joining a room.
 * - The method is valid in the current call. If a remote user exits the room and rejoins the room again, the setting is still
 valid until the call ends.
 * - The method adjusts the volume of the mixing audio published by a specified remote user. The volume of one remote user can
 be adjusted. If you want to adjust multiple remote users, you need to call the method for the required times.
 * @since V4.5.0
 * @param uid    The ID of a remote user.
 * @param volume Playback volume: 0 to 100.
                - 0: Mute.
                - 100: The original volume.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 调节本地播放的指定远端用户的信号音量。
 * <br>加入房间后，您可以多次调用该方法设置本地播放的不同远端用户的音量；也可以反复调节本地播放的某个远端用户的音量。
 *  @note
 * - 请在成功加入房间后调用该方法。
 * - 该方法在本次通话中有效。如果远端用户中途退出房间，则再次加入此房间时仍旧维持该设置，通话结束后设置失效。
 * -
 该方法调节的是本地播放的指定远端用户混音后的音量，且每次只能调整一位远端用户。若需调整多位远端用户在本地播放的音量，则需多次调用该方法。
 * @since V4.5.0
 * @param uid    远端用户 ID。
 * @param volume 播放音量，取值范围为 [0,100]。
                - 0：静音。
                - 100：原始音量。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_adjust_user_playback_signal_volume(struct nertc_channel* self, nertc_uid_t uid, int volume);

/**
 * @if Chinese
 * 调节本地播放的指定房间的所有远端用户的信号音量。
 * <br>通过此接口可以实现在通话过程中随时调节指定房间内的所有远端用户在本地播放的混音音量。
 * @since V4.6.50
 * @par 调用时机
 * 请在引擎初始化之后调用此接口，该方法在加入房间前后都可调用。
 * @note
 * - 该方法设置内部引擎为启用状态，在 leaveChannel 后失效，但在本次通话过程中有效
 * @par 参数说明
 * <table>
 *  <tr>
 *      <th>**参数名称**</th>
 *      <th>**类型**</th>
 *      <th>**描述**</th>
 *  </tr>
 *  <tr>
 *      <td>volume</td>
 *      <td>uint64_t</td>
 *      <td>播放音量，取值范围为 [0,400]。<ul><li>0：静音。<li>100：原始音量。<li>400：最大可为原始音量的 4
 * 倍（自带溢出保护）。</td>
 *  </tr>
 * </table>
 * @return
 * - 0（kNERtcNoError）：方法调用成功。
 * - 其他：方法调用失败。
 *         - 30005（kNERtcErrInvalidState）：状态错误，比如引擎未初始化。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_adjust_channel_playback_signal_volume(struct nertc_channel* self, uint32_t volume);

/**
 * @if English
 * Starts to relay media streams across rooms.
 * - The method can invite co-hosts across rooms. Media streams from up to four rooms can be relayed. A room can receive
 * multiple relayed media streams.
 * - After you call this method, the SDK triggers `onMediaRelayStateChanged` and `onMediaRelayEvent`. The return reports the
 * status and events about the current relayed media streams across rooms.
 * @note
 * - You can call this method after joining a room. Before you call the method, you must set the destination room in the
 * `NERtcChannelMediaRelayConfiguration` parameter in `dest_infos`.
 * - The method is applicable only to the host in live streaming.
 * - If you want to call the method again, you must first call the `stopChannelMediaRelay` method to exit the current relaying
 * status.
 * - If you succeed in relaying the media stream across rooms, and want to change the destination room, for example, add or
 * remove the destination room, you can call `updateChannelMediaRelay` to update the information about the destination room.
 * @since V4.5.0
 * @param config specifies the configuration for the media stream relay across rooms. For more information, see
 * #NERtcChannelMediaRelayConfiguration.
 * @return {@code 0} A value of 0 returned indicates that the method call is successful. Otherwise, the method call fails.
 * @endif
 * @if Chinese
 * 开始跨房间媒体流转发。
 * - 该方法可用于实现跨房间连麦等场景。支持同时转发到 4 个房间，同一个房间可以有多个转发进来的媒体流。
 * - 成功调用该方法后，SDK 会触发 `onMediaRelayStateChanged` 和 `onMediaRelayEvent`
 * 回调，并在回调中报告当前的跨房间媒体流转发状态和事件。
 * @note
 * - 请在成功加入房间后调用该方法。调用此方法前需要通过 `NERtcChannelMediaRelayConfiguration` 中的 `dest_infos` 设置目标房间。
 * - 该方法仅对直播场景下的主播角色有效。
 * - 成功调用该方法后，若您想再次调用该方法，必须先调用 `stopChannelMediaRelay` 方法退出当前的转发状态。
 * - 成功开始跨房间转发媒体流后，如果您需要修改目标房间，例如添加或删减目标房间等，可以调用方法 `updateChannelMediaRelay`
 * 更新目标房间信息。
 * @since V4.5.0
 * @param config 跨房间媒体流转发参数配置信息。
 * @return 成功返回0，其他则失败
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_start_channel_media_relay(struct nertc_channel* self,const struct nertc_channel_media_relay_config* config);

/**
 * @if English
 * Updates the information of the destination room for the media stream relay.
 * <br>You can call this method to relay the media stream to multiple rooms or exit the current room.
 * - You can call this method to change the destination room, for example, add or remove the destination room.
 * - After you call this method, the SDK triggers `onMediaRelayStateChange` and `onMediaRelayEvent`. The return reports the
 * status and events about the current relayed media streams across rooms.
 * @note Before you call the method, you must join the room and call `startChannelMediaRelay` to relay the media stream across
 * rooms. Before you call the method, you must set the destination room in the `NERtcChannelMediaRelayConfiguration` parameter
 * in `dest_infos`.
 * @since V4.5.0
 * @param config The configuration for destination rooms.
 * @return A value of 0 returned indicates that the method call is successful. Otherwise, the method call fails.
 * @endif
 * @if Chinese
 * 更新媒体流转发的目标房间。
 * <br>成功开始跨房间转发媒体流后，如果你希望将流转发到多个目标房间，或退出当前的转发房间，可以调用该方法。
 * - 成功开始跨房间转发媒体流后，如果您需要修改目标房间，例如添加或删减目标房间等，可以调用此方法。
 * - 成功调用该方法后，SDK 会触发 `onMediaRelayStateChange` 和 `onMediaRelayEvent`
 * 回调，并在回调中报告当前的跨房间媒体流转发状态和事件。
 * @note 请在加入房间并成功调用 `startChannelMediaRelay` 开始跨房间媒体流转发后，调用此方法。调用此方法前需要通过
 * `NERtcChannelMediaRelayConfiguration` 中的 `dest_infos` 设置目标房间。
 * @since V4.5.0
 * @param config 目标房间配置信息
 * @return 成功返回0，其他则失败
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_update_channel_media_relay(struct nertc_channel* self,const struct nertc_channel_media_relay_config* config);

/**
 * @if English
 * Stops relaying media streams.
 * <br>If the host leaves the room, media stream replay across rooms automatically stops. You can also call
 * stopChannelMediaRelay. In this case, the host exits all destination rooms.
 * - If you call this method, the SDK triggers the `onMediaRelayStateChange` callback. If `NERtcChannelMediaRelayStateIdle` is
 * returned, the media stream relay stops.
 * - If the method call failed, the SDK triggers the `onMediaRelayStateChange` callback that returns the status code
 * `NERtcChannelMediaRelayStateFailure`.
 * @since V4.5.0
 * @return A value of 0 returned indicates that the method call is successful. Otherwise, the method call fails.
 * @endif
 * @if Chinese
 * 停止跨房间媒体流转发。
 * <br>主播离开房间时，跨房间媒体流转发自动停止，您也可以在需要的时候随时调用 `stopChannelMediaRelay`
 * 方法，此时主播会退出所有目标房间。
 * - 成功调用该方法后，SDK 会触发 `onMediaRelayStateChange` 回调。如果报告
 * `NERtcChannelMediaRelayStateIdle`，则表示已停止转发媒体流。
 * - 如果该方法调用不成功，SDK 会触发 `onMediaRelayStateChange` 回调，并报告状态码 `NERtcChannelMediaRelayStateFailure`。
 * @since V4.5.0
 * @return 成功返回0，其他则失败
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_stop_channel_media_relay(struct nertc_channel* self);

/**
 * @if English
 * Sets the fallback option for the published local video stream based on the network conditions.
 * <br>The quality of the published local audio and video streams is degraded with poor quality network connections. After
 * calling this method and setting the option to #kNERtcStreamFallbackAudioOnly:
 * - With unreliable upstream network connections and the quality of audio and video streams is downgraded, the SDK
 * automatically disables video stream or stops receiving video streams. In this way, the communication quality is guaranteed.
 * - The SDK monitors the network performance and recover audio and video streams if the network quality improves.
 * - If the locally published audio and video stream falls back to audio stream, or recovers to audio and video stream, the
 * SDK triggers the onLocalPublishFallbackToAudioOnly callback. <p>@note You must call the method before you call joinChannel.
 * @since V4.5.0
 * @param option The fallback option of publishing audio and video streams. The fallback kNERtcStreamFallbackAudioOnly is
 * disabled by default. For more information, see nertc::NERTCStreamFallbackOption.
 * @return {@code 0} A value of 0 returned indicates that the method call is successful. Otherwise, the method call fails.
 * @endif
 * @if Chinese
 * 设置弱网条件下发布的音视频流回退选项。
 * <br>在网络不理想的环境下，发布的音视频质量都会下降。使用该接口并将 option 设置为 #kNERtcStreamFallbackAudioOnly 后：
 * - SDK 会在上行弱网且音视频质量严重受影响时，自动关断视频流，尽量保证音频质量。
 * - 同时 SDK 会持续监控网络质量，并在网络质量改善时恢复音视频流。
 * - 当本地发布的音视频流回退为音频流时，或由音频流恢复为音视频流时，SDK 会触发本地发布的媒体流已回退为音频流
 * onLocalPublishFallbackToAudioOnly 回调。 <p>@note 请在加入房间（joinChannel）前调用此方法。
 * @since V4.5.0
 * @param option 发布音视频流的回退选项，默认为不开启回退 kNERtcStreamFallbackAudioOnly。详细信息请参考
 * nertc::NERTCStreamFallbackOption 。
 * @return {@code 0} 方法调用成功，其他调用失败
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_set_local_publish_fallback_option(struct nertc_channel* self,nertc_stream_fallback_option option);

/**
 * @if English
 * Sets the fallback option for the subscribed remote audio and video stream with poor network connections.
 * <br>The quality of the subscribed audio and video streams is degraded with unreliable network connections. You can use the
 * interface to set the option as #kNERtcStreamFallbackVideoStreamLow or #kNERtcStreamFallbackAudioOnly.
 * - In unreliable downstream network connections, the SDK switches to receive a low-quality video stream or stops receiving
 * video streams. In this way, the communication quality is maintained or improved.
 * - The SDK monitors the network quality and resumes the video stream when the network condition improves.
 * - If the subscribed remote video stream falls back to audio only, or the audio-only stream switches back to the video
 * stream, the SDK triggers the onRemoteSubscribeFallbackToAudioOnly callback. <p>@note You must call the method before you
 * call joinChannel.
 * @since V4.5.0
 * @param option    The fallback option for the subscribed remote audio and video stream. With unreliable network connections,
 * the stream falls back to a low-quality video stream of kNERtcStreamFallbackVideoStreamLow. For more information, see
 * nertc::NERTCStreamFallbackOption .
 * @return {@code 0} A value of 0 returned indicates that the method call is successful. Otherwise, the method call fails.
 * @endif
 * @if Chinese
 * 设置弱网条件下订阅的音视频流回退选项。
 * <br>弱网环境下，订阅的音视频质量会下降。使用该接口并将 option 设置为  #kNERtcStreamFallbackVideoStreamLow 或者
 * #kNERtcStreamFallbackAudioOnly 后：
 * - SDK 会在下行弱网且音视频质量严重受影响时，将视频流切换为小流，或关断视频流，从而保证或提高通信质量。
 * - SDK 会持续监控网络质量，并在网络质量改善时自动恢复音视频流。
 * - 当远端订阅流回退为音频流时，或由音频流恢复为音视频流时，SDK 会触发远端订阅流已回退为音频流
 * onRemoteSubscribeFallbackToAudioOnly 回调。 <p>@note 请在加入房间（joinChannel）前调用此方法。
 * @since V4.5.0
 * @param option    订阅音视频流的回退选项，默认为弱网时回退到视频小流 kNERtcStreamFallbackVideoStreamLow。详细信息请参考
 * nertc::NERTCStreamFallbackOption 。
 * @return {@code 0} 方法调用成功，其他调用失败
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_set_remote_subscribe_fallback_option(struct nertc_channel* self, nertc_stream_fallback_option option);

/**
 * @if English
 * Sets a remote audio stream to high priority
 * Sets a remote audio streams to high priority during automatic stream subscription. Users can hear the audio stream with high
 * priority.
 * @note
 * - The priority of a remote audio stream must be set during a call and automatic stream subscription must be enabled (by
 * default)
 * - Only one audio stream can be set to high priority. The subsequent call will override the previous setting.
 * - The priority of the audio stream will be reset after the call ends
 * @param[in] enabled sets or cancels high priority to a remote audio stream.
 * - true: sets high priority to a remote audio stream.
 * - false: cancels high priority of a remote audio stream.
 * @param[in] uid User ID
 * @return
 * - 0: success；
 * - Other values: failure
 * @endif
 * @if Chinese
 * 设置远端用户音频流为高优先级。
 * 支持在音频自动订阅的情况下，设置某一个远端用户的音频为最高优先级，可以优先听到该用户的音频。
 * @note
 * - 该接口需要通话中设置，并需要自动订阅打开（默认打开）。
 * - 该接口只能设置一个用户的优先级，后设置的会覆盖之前的设置。
 * - 该接口通话结束后，优先级设置重置。
 * @param[in] enabled 是否设置音频订阅优先级。
 * - true：设置音频订阅优先级。
 * - false：取消设置音频订阅优先级。
 * @param[in] uid 用户 ID
 * @return
 * - 0: 方法调用成功。
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_set_remote_high_priority_audio_stream(struct nertc_channel* self, bool enabled, nertc_uid_t uid);

/**
* @if English
* Enables or disables the external video source.
* <br>When you enable the external video source through the method, you need to set kNERtcExternalVideoDeviceID as the ID of
* external video source with IVideoDeviceManager::setDevice kNERtcExternalVideoDeviceID method.
* @note The method enables the internal engine, which is still valid after you call \ref IRtcEngine::leaveChannel
* "leaveChannel".
* @param[in] enabled       Specifies whether input external video source data.
* - true: Enables external video source.
* - false: Disables the external video source (default).
* @return
* - 0: Success.
* - Other values: Failure.
* @endif
* @if Chinese
* 开启或关闭外部视频源数据输入。
* <br>通过该方法启用外部视频数据输入功能时，需要通过 IVideoDeviceManager::setDevice 设置 kNERtcExternalVideoDeviceID
* 为外部视频输入源 ID。
* @note 该方法设置内部引擎为启用状态，在 \ref IRtcEngine::leaveChannel "leaveChannel" 后仍然有效。
* @param[in] type 视频流通道类型 #NERtcVideoStreamType
* - kNERTCVideoStreamMain，打开或关闭主流通道的外部源
* - kNERTCVideoStreamSub， 打开或关闭辅流通道的外部源
* @param[in] enabled       是否外部视频源数据输入:
* - true: 开启外部视频源数据输入；
* - false: 关闭外部视频源数据输入 (默认)。
* @return
* - 0: 方法调用成功；
* - 其他: 方法调用失败。
* @endif
*/
NERTC_API int NERTC_CALL nertc_channel_set_external_video_source(struct nertc_channel* self, nertc_video_stream_type type, bool enabled);

/**
 * @if English
 * Pushes the external video frames.
 * <br>The method actively pushes the data of video frames that are encapsulated with the NERtcVideoFrame class to the SDK.
 * Make sure that you have already called setExternalVideoSource with a value of true before you call this method. Otherwise,
 * an error message is repeatedly prompted if you call the method.
 * @note The method enables the internal engine, which is invalid after you call \ref IRtcEngine::leaveChannel "leaveChannel".
 * @param[in] type          The video frame format.
 * @param[in] frame         The video frame data.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 推送外部视频帧。
 * <br>该方法主动将视频帧数据用 NERtcVideoFrame 类封装后传递给 SDK。 请确保在你调用本方法前已调用
 * setExternalVideoSource，并将参数设为 true，否则调用本方法后会一直报错。
 * @note 该方法设置内部引擎为启用状态，在 \ref IRtcEngine::leaveChannel "leaveChannel" 后不再有效。
 * @param[in] type          视频帧数据格式。
 * @param[in] frame         视频帧数据。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_push_external_video_frame(struct nertc_channel* self,
                                                                 nertc_video_stream_type type,
                                                                 struct nertc_video_frame* frame);

/**
 * @if English
 * Publishes or unpublishes the local audio stream.
 * <br>When a user joins a room, the feature is enabled by default.
 * <br>The method does not affect receiving or playing the remote audio stream. The enableLocalAudio(false) method is suitable
 * for scenarios where clients only receives remote media streams and does not publish any local streams.
 * @note
 * - The method controls data transmitted over the main stream
 * - The method can be called before or after a user joins a room.
 * @since V4.6.10
 * @param enabled specifies whether to publish the local audio stream.
 * - true(default): publishes the local audio stream.
 * - false: unpublishes the local audio stream.
 * @param mediaType  media type. Audio type is supported.
 * @return
 * - 0: success
 * - Others: failure
 * @endif
 * @if Chinese
 * 开启或关闭本地媒体流（主流）的发送。
 * <br>该方法用于开始或停止向网络发送本地音频或视频数据。
 * <br>该方法不影响接收或播放远端媒体流，也不会影响本地音频或视频的采集状态。
 * @since V4.6.10
 * @note
 * - 该方法暂时仅支持控制音频流的发送。
 * - 该方法在加入房间前后均可调用。
 * - 停止发送媒体流的状态会在通话结束后被重置为允许发送。
 * - 成功调用该方法切换本地用户的发流状态后，房间内其他用户会收到 \ref IRtcChannelEventHandler::onUserAudioStart
 * "onUserAudioStart"（开启发送音频）或 \ref IRtcChannelEventHandler::onUserAudioStop "onUserAudioStop"（停止发送音频）的回调。
 * @par 相关接口
 * - \ref IRtcChannel::muteLocalAudioStream "muteLocalAudioStream"：
 *         - 在需要开启本地音频采集（监测本地用户音量）但不发送音频流的情况下，您也可以调用 muteLocalAudioStream(true) 方法。
 *         - 两者的差异在于， muteLocalAudioStream(true) 仍然保持与服务器的音频通道连接，而 enableMediaPub(false)
 * 表示断开此通道，因此若您的实际业务场景为多人并发的大房间，建议您调用 enableMediaPub 方法。
 * @param enabled 是否发布本地媒体流。
 * - true（默认）：发布本地媒体流。
 * - false：不发布本地媒体流。
 * @param media_type 媒体发布类型，暂时仅支持音频。
 * @return
 * - 0：方法调用成功。
 * - 其他：方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_enable_media_publish(struct nertc_channel* self,
                                                        bool enabled,
                                                        nertc_media_pub_type media_type);

/**
 * @if Chinese
 * 更新权限密钥。
 * - 通过本接口可以实现当用户权限被变更，或者收到权限密钥即将过期的回调 \ref
 * nertc::IRtcChannelEventHandler::onPermissionKeyWillExpire() "onPermissionKeyWillExpire" 时，更新权限密钥。
 * @since V4.6.29
 * @par 使用前提
 * 请确保已开通高级 Token 鉴权功能，具体请联系网易云信商务经理。
 * @par 调用时机
 * 请在引擎初始化之后调用此接口，且该方法仅可在加入房间后调用。
 * @par 业务场景
 * 适用于变更指定用户加入、创建房间或上下麦时发布流相关权限的场景。
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
 * </table>
 * @par 示例代码
 * @code
 * if (rtc_engine_) {
 * std::string key;//向服务器请求得到的权限key，具体请参考官方文档的高级 Token 鉴权章节。</a>
 * rtc_engine_->updatePermissionKey(key.c_str()));    if (kNERtcNoError != res) {
 * }
 * @endcode
 * @par 相关回调
 * 调用此接口成功更新权限密钥后会触发 \ref nertc::IRtcChannelEventHandler::onUpdatePermissionKey() "onUpdatePermissionKey"
 * 回调。
 * @return
 * - 0（kNERtcNoError）：方法调用成功。
 * - 其他：方法调用失败。
 *         - 30003（kNERtcErrInvalidParam）：参数错误，比如 key 无效。
 *         - 30005（kNERtcErrInvalidState)：当前状态不支持的操作，比如引擎尚未初始化。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_update_permission_key(struct nertc_channel* self, const char* key);
/**
 * @if Chinese
 * 上报自定义事件
 * @param event_name      事件名 不能为空
 * @param custom_identify 自定义标识，比如产品或业务类型，如不需要填null
 * @param parameters    参数键值对 ，参数值支持String 及java基本类型(int 、bool....) ， 如不需要填null
 * @return 操作返回值，成功则返回 0
 * @endif
 */
NERTC_API int NERTC_CALL nertc_channel_report_custom_event(struct nertc_channel* self,
                                                         const char* event_name,
                                                         const char* custom_identify,
                                                         const char* parameters);

/**
 * 设置范围语音模式
 * @note 此接口在加入房间前后均可调用。
 * @param mode 范围语音模式
 * @return 操作返回值，成功则返回 0
 */
NERTC_API int NERTC_CALL nertc_channel_set_range_audio_mode(struct nertc_channel* self, nertc_range_audio_mode mode);

/**
 * 设置范围语音小队
 * @note 此接口在加入房间前后均可调用。
 * @param team_id 小队ID
 * @return 操作返回值，成功则返回 0
 */
NERTC_API int NERTC_CALL nertc_channel_set_range_audio_team_id(struct nertc_channel* self, int32_t team_id);

/**
 * 引擎3D音效算法距离范围设置
 * @param audible_distance 监听器能够听到扬声器并接收其文本消息的距离扬声器的最大距离。无默认值, 有效范围[1, ∞)。
 * @param conversational_distance 控制扬声器音频保持其原始音量的范围，超出该范围时，语音聊天的响度在被听到时开始淡出。
 * 默认值为 1。
 * @param roll_off:距离衰减模式 #NERtcDistanceRolloffModel ，默认值 #kNERtcDistanceRolloffNone
 * @return
 * - 0: 方法调用成功
 * - 其他: 调用失败
 */
NERTC_API int NERTC_CALL nertc_channel_set_audio_recv_range(struct nertc_channel* self, int audible_distance, int conversational_distance, nertc_distance_rolloff_model roll_off);

/**
 * 引擎3D音效算法中本人坐标方位更新接口
 * @note 依赖enableSpatializer接口开启，enableSpatializer接口关闭后重置设置
 * @param speaker_position 嘴巴位置信息，默认值{0,0,0}
 * @param speaker_quaternion 嘴巴方向信息，四元组格式，默认值{0,0,0,0}
 * @param head_position 耳朵位置信息，默认值{0,0,0}
 * @param head_quaternion 耳朵方向信息，四元组格式，默认值{0,0,0,0}
 * @return
 * - 0: 方法调用成功
 * - 其他: 调用失败
 */
NERTC_API int NERTC_CALL nertc_channel_update_self_position(struct nertc_channel* self, const struct nertc_position_info* info);

/**
 * 引擎3D音效算法中房间混响效果开关
 * @note 依赖enableSpatializer接口开启
 * @param enable 混响效果开关，默认值关闭
 * @return
 * - 0: 方法调用成功
 * - 其他: 调用失败
 */
NERTC_API int NERTC_CALL nertc_channel_enable_spatializer_room_effects(struct nertc_channel* self, bool enable);
/**
 * 引擎3D音效算法中房间混响属性
 * @note 依赖enableSpatializer接口开启
 * @param room_property 房间属性 #NERtcSpatializerRoomProperty
 * @return
 * - 0: 方法调用成功
 * - 其他: 调用失败
 */
NERTC_API int NERTC_CALL nertc_channel_set_spatializer_room_property(struct nertc_channel* self, const struct nertc_spatializer_room_property* room_property);

/**
 * 引擎3D音效算法中渲染模式
 * @note 依赖enableSpatializer接口开启
 * @param mode 渲染模式 #NERtcSpatializerRenderMode ，默认值 #kNERtcSpatializerRenderBinauralHighQuality
 * @return
 * - 0: 方法调用成功
 * - 其他: 调用失败
 */
NERTC_API int NERTC_CALL nertc_channel_set_spatializer_render_mode(struct nertc_channel* self, nertc_spatializer_render_mode mode);

/**
 * 初始化引擎3D音效算法
 * @note 此接口在加入房间前调用，退出房间后不重置
 * @return
 * - 0: 方法调用成功
 * - 其他: 调用失败
 */
NERTC_API int NERTC_CALL nertc_channel_init_spatializer(struct nertc_channel* self);

/**
 * 引擎3D音效算法开关
 * @note 通话前调用，通话结束后不重置
 * @param enable 是否打开3D音效算法功能
 * @return
 * - 0: 方法调用成功
 * - 其他: 调用失败
 */
NERTC_API int NERTC_CALL nertc_channel_enable_spatializer(struct nertc_channel* self, bool enable);

NERTC_END_DECLS
#endif
