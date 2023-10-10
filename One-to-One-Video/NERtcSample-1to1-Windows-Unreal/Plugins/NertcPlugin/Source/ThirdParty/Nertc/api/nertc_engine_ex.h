#ifndef NERTC_ENGINE_EX_H
#define NERTC_ENGINE_EX_H

#include "nertc_engine_defines.h"
#include "nertc_media_stats_observer.h"
#include "nertc_engine_predecode_observer.h"
#include "nertc_engine_video_encoder_qos_observer.h"

NERTC_BEGIN_DECLS

/**
 * @if English
 * Create an IRtcChannel.
 * @param[in] channel_name      The name of the room. Users that use the same name can join the same room. The name must be of
 * STRING type and must be 1 to 64 characters in length. The following 89 characters are supported: a-z, A-Z, 0-9, space,
 * !#$%&()+-:;≤.,>? @[]^_{|}~”.
 * @return IRtcChannel pointer
 * - 0: 方法调用失败。
 * @endif
 * @if Chinese
 * 创建一个 IRtcChannel 对象
 * @param[in] channel_name      房间名。设置相同房间名称的用户会进入同一个通话房间。字符串格式，长度为1~ 64
 * 字节。支持以下89个字符：a-z, A-Z, 0-9, space, !#$%&()+-:;≤.,>? @[]^_{|}~”
 * @return 返回 IRtcChannel 对象指针
 * - 0: 方法调用失败。
 * @endif
 */
  NERTC_API struct nertc_channel* NERTC_CALL nertc_engine_create_channel(struct nertc_engine* self, const char* channel_name);

/**
 * @if English
 * Gets the current connection status.
 * @return Returns the current network status. #NERtcConnectionStateType.
 * @endif
 * @if Chinese
 * 获取当前网络状态。
 * @return 当前网络状态。#NERtcConnectionStateType.
 * @endif
 */
NERTC_API nertc_connection_state_type NERTC_CALL nertc_engine_get_connection_state(struct nertc_engine* self);

/**
 * @if English
 * Enables or disabling publishing the local audio stream. The method is used to enable or disable publishing the local audio
 * stream.
 * @note
 * - This method does not change the state of the audio-recording device because the audio-recording devices are not disabled.
 * - The mute state is reset to unmuted after the call ends.
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
 * @param[in] type      音频流类型:
 * @param[in] mute      静音/取消静音:
 * - true: 静音本地音频
 * - false: 取消静音本地音频（默认）
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_mute_local_audio_stream(struct nertc_engine* self, nertc_audio_stream_type type, bool mute);

/**
 * @if English
 * Sets the audio encoding profile.
 * @note
 * - Sets the method before calling the \ref IRtcEngine::joinChannel "joinChannel". Otherwise, the setting is invalid after
 * \ref IRtcEngine::joinChannel "joinChannel".
 * - In music scenarios, we recommend you to set the profile as kNERtcAudioProfileHighQuality.
 * @param[in] profile       Sets the sample rate, bitrate, encoding mode, and the number of channels. #NERtcAudioProfileType.
 * @param[in] scenario      Sets the type of an audio application scenario. #NERtcAudioScenarioType.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置音频编码属性。
 * @note
 * - 该方法需要在 \ref IRtcEngine::joinChannel "joinChannel" 之前设置好， \ref IRtcEngine::joinChannel "joinChannel"
 * 之后设置不生效。
 * - 音乐场景下，建议将 profile 设置为 kNERtcAudioProfileHighQuality。
 * @param[in]  profile      设置采样率，码率，编码模式和声道数: #NERtcAudioProfileType 。
 * @param[in]  scenario     设置音频应用场景: #NERtcAudioScenarioType 。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_audio_profile(struct nertc_engine* self, nertc_audio_profile_type profile, nertc_audio_scenario_type scenario);

/**
 * @if English
 * Sets the voice changer effect for the SDK-preset voice.
 * The method can add multiple preset audio effects to original human voices and change audio profiles.
 * @note
 * - You can call this method either before or after joining a room. By default, the audio effect is disabled after the call
 * ends.
 * - The method conflicts with setLocalVoicePitch. After you call this method, the voice pitch is reset to the default
 * value 1.0.
 * @param[in] type      The preset voice changer effect. By default, the audio effect is disabled. For more information, see
 * nertc::NERtcVoiceChangerType.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置 SDK 预设的人声的变声音效。
 * 设置变声音效可以将人声原因调整为多种特殊效果，改变声音特性。
 *  @note
 * - 此方法在加入房间前后都能调用，通话结束后重置为默认关闭状态。
 * - 此方法和 setLocalVoicePitch 互斥，调用此方法后，本地语音语调会恢复为默认值 1.0。
 * @param[in] type      预设的变声音效。默认关闭变声音效。详细信息请参考 nertc::NERtcVoiceChangerType 。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_audio_effect_preset(struct nertc_engine* self, nertc_voice_changer_type type);

/**
 * @if English
 * Sets an SDK-preset voice beautifier effect.
 * The method can set a SDK-preset voice beautifier effect for a local user who sends an audio stream.
 * @note By default, the method is reset as disabled after the call ends.
 * @param[in] type      The present voice beautifier effect. By default, the voice beautifier effect is disabled. For more
 * information, see nertc::NERtcVoiceBeautifierType.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置 SDK 预设的美声效果。
 * 调用该方法可以为本地发流用户设置 SDK 预设的人声美声效果。
 * @note 通话结束后重置为默认关闭
 * @param[in] type      预设的美声效果模式。默认关闭美声效果。详细信息请参考 nertc::NERtcVoiceBeautifierType 。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_voice_beautifier_preset(struct nertc_engine* self, nertc_voice_beautifier_type type);

/**
 * @if English
 * Sets the voice pitch of a local voice.
 * The method changes the voice pitch of the local speaker.
 * @note
 * - After the call ends, the setting changes back to the default value 1.0.
 * - The method conflicts with setAudioEffectPreset. After you call this method, the preset voice beautifier effect will be
 * removed.
 * @param[in] pitch         The voice frequency. Valid values: 0.5 to 2.0. Smaller values have lower pitches. The default
 * value is 1, which That the pitch is not changed.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置本地语音音调。
 * 该方法改变本地说话人声音的音调。
 * @note
 * - 通话结束后该设置会重置，默认为 1.0。
 * - 此方法与 setAudioEffectPreset 互斥，调用此方法后，已设置的变声效果会被取消。
 * @param[in] pitch         语音频率。可以在 [0.5, 2.0] 范围内设置。取值越小，则音调越低。默认值为 1.0，表示不需要修改音调。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_local_voice_pitch(struct nertc_engine* self, double pitch);

/**
 * @if English
 * Sets the local voice equalization effect. You can customize the center frequencies of the local voice effects.
 * @note You can call this method either before or after joining a room. By default, the audio effect is disabled after the
 * call ends.
 * @param[in] band_frequency    Sets the band frequency. Value range: 0 to 9. Those numbers represent the respective 10-band
 * center frequencies of the voice effects, including 31, 62, 125, 250, 500, 1k, 2k, 4k, 8k, and 16k Hz.
 * @param[in] band_gain         Sets the gain of each band (dB). Value range: -15 to 15. The default value is 0.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置本地语音音效均衡，即自定义设置本地人声均衡波段的中心频率。
 * @note 该方法在加入房间前后都能调用，通话结束后重置为默认关闭状态。
 * @param[in] band_frequency    频谱子带索引，取值范围是 [0-9]，分别代表 10 个频带，对应的中心频率是
 * [31，62，125，250，500，1k，2k，4k，8k，16k] Hz。
 * @param[in] band_gain         每个 band 的增益，单位是 dB，每一个值的范围是 [-15，15]，默认值为 0。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_local_voice_equalization(struct nertc_engine* self, nertc_voice_equalization_band band_frequency, int band_gain);

/**
 * @if English
 * Unsubscribes from or subscribes to audio streams from specified remote users.
 * <br>After a user joins a channel, audio streams from all remote users are subscribed by default. You can call this method
 * to unsubscribe from or subscribe to audio streams from all remote users.
 * @note  When the kNERtcKeyAutoSubscribeAudio is enabled by default, users cannot manually modify the state of audio
 * subscription.
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
 * @param[in] stream_type 音频流类型: kNERtcAudioStreamTypeMain主流音频，kNERtcAudioStreamTypeSub辅流音频。
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
NERTC_API int NERTC_CALL nertc_engine_subscribe_remote_audio_stream(struct nertc_engine* self, nertc_audio_stream_type stream_type, nertc_uid_t uid, bool subscribe);

/**
 * @if English
 * Unsubscribes or subscribes to audio streams from all remote users.
 * @note
 * - Call this method before or after joining the channel.
 * @since V4.5.0
 * @param subscribe Whether to unsubscribe audio streams from all remote users.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 取消或恢复订阅所有远端用户的音频主流。
 * <br>加入房间时，默认订阅所有远端用户的音频主流，即 \ref nertc::IRtcEngineEx::setParameters "setParameters" 方法的
 * KEY_AUTO_SUBSCRIBE_AUDIO 参数默认设置为 true；只有当该参数的设置为 false 时，此接口的调用才会生效。
 * @since V4.5.0
 * @par 调用时机
 * 请在引擎初始化之后调用此接口，且该方法在加入房间前后均可调用。
 * @par 业务场景
 * 适用于重要会议需要一键全体静音的场景。
 * @note
 * - 设置该方法的 subscribe 参数为 true 后，对后续加入房间的用户同样生效。
 * - 在开启自动订阅（默认）时，设置该方法的 subscribe 参数为 false 可以实现取消订阅所有远端用户的音频流，但此时无法再调用 \ref
 * nertc::IRtcEngineEx::subscribeRemoteAudioStream "subscribeRemoteAudioStream" 方法单独订阅指定远端用户的音频流。
 * @par 参数说明
 * <table>
 *  <tr>
 *      <th>**参数名称**</th>
 *      <th>**类型**</th>
 *      <th>**描述**</th>
 *  </tr>
 *  <tr>
 *      <td>subscribe</td>
 *      <td>bool</td>
 *      <td>是否订阅所有用户的音频主流：<ul><li>true：订阅音频主流。<li>false：取消订阅音频主流。</td>
 *  </tr>
 * </table>
 * @par 示例代码
 * @code
 * //订阅所有远端用户的音频主流
 * rtc_engine_->subscribeAllRemoteAudioStream(true);
 * //取消订阅所有远端用户的音频主流
 * rtc_engine_->subscribeAllRemoteAudioStream(false);
 * @endcode
 * @return
 * - 0（kNERtcNoError）：方法调用成功。
 * - 其他：方法调用失败。
 *      - 30005（kNERtcErrInvalidState)：引擎未初始化。
 *      - 30026：ASL 选路功能启用失败。
 *      - 30400：Transceiver 未找到。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_subscribe_all_remote_audio_stream(struct nertc_engine* self, bool subscribe);

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
NERTC_API int NERTC_CALL nertc_engine_set_audio_subscribe_only_by(struct nertc_engine* self, nertc_uid_t* uid_array, uint32_t size);

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
NERTC_API int NERTC_CALL nertc_engine_set_subscribe_audio_allow_list(struct nertc_engine* self, nertc_uid_t* uid_array, uint32_t size);

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
NERTC_API int NERTC_CALL nertc_engine_set_subscribe_audio_block_list(struct nertc_engine* self, nertc_uid_t* uid_array, uint32_t size);

/**
 * @if English
 * Synchronizes the local time with the server time
 * @since V4.6.10
 * @param enable specifies whether to enable precise synchronization of the local time with the server time
 * - true: enables the precise synchronization
 * - false: disables the precise synchronization.
 * @return
 * - 0: success
 * - Others: failure
 * @endif
 * @if Chinese
 * 开启精准对齐。
 * 通过此接口可以实现精准对齐功能，对齐本地系统与服务端的时间。
 * @since V4.6.10
 * @par 调用时机
 * 请在引擎初始化之后调用此接口，且该方法仅可在加入房间前调用。
 * @par 业务场景
 * 适用于 KTV 实时合唱的场景。
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
 *      <td>是否开启精准对齐功能：<ul><li>true：开启精准对齐功能。<li>false：关闭精准对齐功能。</td>
 *  </tr>
 * </table>
 * @par 示例代码
 * @code
 * if (nrtc_engine_) {
 * nrtc_engine_->setStreamAlignmentProperty(truetrue);
 * }
 * @endcode
 * @par 相关接口
 * 可以调用 \ref nertc::IRtcEngineEx::getNtpTimeOffset "getNtpTimeOffset" 方法获取本地系统时间与服务端时间的差值。
 * @return 无返回值。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_stream_alignment_property(struct nertc_engine* self, bool enable);

/**
 * @if English
 * Gets the difference between the local time and the server time.
 * <br>The method can sync the time between the client and server. To get the current server time, call
 * (System.currentTimeMillis() - offset).
 * @since V4.6.10
 * @return Difference between the local time and the server time. Unit: milliseconds(ms). If a user fails to join a room, a
 * value of 0 is returned.
 * @endif
 * @if Chinese
 * 获取本地系统时间与服务端时间差值。
 * <br>可以用于做时间对齐，通过 (毫秒级系统时间 - offset) 可能得到当前服务端时间。
 * @since V4.6.10
 * @return 本地与服务端时间差值，单位为毫秒（ms）。如果没有成功加入音视频房间，返回 0。
 * @endif
 */
NERTC_API int64_t NERTC_CALL nertc_engine_get_ntp_time_offset(struct nertc_engine* self);
/**
 * @if English
 * Sets permissions of the SDK over Audio Session.
 * <br>This method is only applicable to the iOS platform.
 * <br>This method controls the permissions of the SDK over Audio Session. By default, the SDK and the app have control over the
 * Audio Session. However, in some cases, the app wants to restrict the SDK's permissions over Audio Session and uses other
 * applications or third-party components to control Audio Session. The app can adjust the permissions of the SDK by calling
 * this method. <br>You can call this method only before you join the room.
 * @note If you call this method to restrict the SDK's permissions over Audio Session, the SDK cannot set Audio Session. You
 * need to manage Audio Session or use a third-party component to operate Audio Session.
 * @param restriction The restriction applied to the SDK for Audio Session. For more information, see {@link
 * NERtcAudioSessionOperationRestriction}.
 * @return The value returned. A value of 0 indicates that the operation is successful.
 * @endif
 * @if Chinese
 * 设置 SDK 对 Audio Session 的控制权限。
 * <br>该方法仅适用于 iOS 平台。
 * <br>该方法限制  SDK 对 Audio Session 的操作权限。在默认情况下，SDK 和 App 对 Audio Session 都有控制权，但某些场景下，App
 * 会希望限制  SDK 对 Audio Session 的控制权限，而使用其他应用或第三方组件对 Audio Session 进行操控。调用该方法可以实现该功能。
 * <br>该接口只能在入会之前调用。
 * @note 一旦调用该方法限制了 SDK 对 Audio Session 的控制权限， SDK 将无法对 Audio Session
 * 进行相关设置，而需要用户自己或第三方组件进行维护。
 * @param restriction SDK 对 Audio Session 的控制权限。详细信息请参考 {@link NERtcAudioSessionOperationRestriction}。
 * @return 操作返回值，成功则返回 0
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_audio_session_operation_restriction(struct nertc_engine* self, nertc_audio_session_operation_restriction restriction);

/**
 * @if English
 * Sets the audio focus mode.
 * <br>This method is only applicable to the Android platform.
 * @return {@code 0} A value of 0 returned indicates that the method call is successful. Otherwise, the method call fails.
 * @endif
 * @if Chinese
 * 设置音频焦点模式。
 * <br>该方法仅适用于 Android 平台。
 * @return {@code 0} 方法调用成功，其他失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_audio_focus_mode(struct nertc_engine* self, nertc_audio_focus_mode focus_mode);
/**
 * @if English
 * Mutes or unmutes the audio playback device.
 * @param muted The option whether to mute the playback device. By default, the setting is unmuted.
 * @return The value returned. A value of 0 indicates that the operation is successful.
 * @endif
 * @if Chinese
 * 设置是否静音音频播放设备。
 * @param muted 是否静音播放设备。默认为不静音状态。
 * @return 操作返回值，成功则返回 0
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_playout_device_mute(struct nertc_engine* self, bool muted);

/**
 * @if English
 * Gets the mute status of the audio playback device.
 * @param muted The option whether the device is muted.
 * @return The value returned. A value of 0 indicates that the operation is successful.
 * @endif
 * @if Chinese
 * 获取音频播放设备的静音状态。
 * @param muted 是否静音。
 * @return 操作返回值，成功则返回 0
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_get_playout_device_mute(struct nertc_engine* self, bool* muted);

/**
 * @if English
 * Mutes or unmutes the audio capture device.
 * @param muted The option whether to mute the audio capture device. The default setting is unmuted.
 * @return The value returned. A value of 0 indicates that the operation is successful.
 * @endif
 * @if Chinese
 * 设置是否静音音频采集设备。
 * @param muted 是否静音音频采集设备。默认为不静音。
 * @return 操作返回值，成功则返回 0
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_record_device_mute(struct nertc_engine* self, bool muted);

/**
 * @if English
 * Checks whether the audio capture device is muted.
 * @param muted The option whether the device is muted.
 * @return The value returned. A value of 0 indicates that the operation is successful.
 * @endif
 * @if Chinese
 * 查询当前音频采集设备是否静音。
 * @param muted 是否静音。
 * @return 操作返回值，成功则返回 0
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_get_record_device_mute(struct nertc_engine* self, bool* muted);

/**
 * @if English
 * Checks whether the camera zooming feature is supported.
 * <br>Make sure that you call this method after the camera starts. For example, you can call this method after you call
 * startPreview or joinChannel.
 * @note The audio-only SDK disables this API. If you need to use the API, you can download the standard SDK from the official
 * website of CommsEase and replace the audio-only SDK.
 * @return YES: The camera zooming feature is supported. NO: The camera zooming feature is not supported.
 * @endif
 * @if Chinese
 * 检测设备当前使用的摄像头是否支持缩放功能。
 * <br>该方法需要在相机启动后调用，例如调用 startPreview 或 joinChannel 后。
 * @note 纯音频 SDK 禁用该接口，如需使用请前往云信官网下载并替换成视频 SDK。
 * @return YES 表示支持，NO 表示支持。
 * @endif
 */
NERTC_API bool NERTC_CALL nertc_engine_is_camera_zoom_supported(struct nertc_engine* self);

/**
 * @if English
 * Checks whether the camera flash feature is supported.
 * @note
 * - In most cases, the app opens the front camera by default. If the front camera does not support the flash feature and you
 * call the method, a value of NO is returned. If you want to check whether the rear camera supports the flash feature, before
 * you call this method, you must first call switchCamera to switch the camera.
 * - Make sure that you call this method after the camera starts. For example, you can call this method after you call
 * startPreview or joinChannel.
 * - The audio-only SDK disables this API. If you need to use the API, you can download the standard SDK from the official
 * website of CommsEase and replace the audio-only SDK.
 * @return YES: The camera flash feature is supported. NO: The camera flash feature is not supported.
 * @endif
 * @if Chinese
 * 检测设备是否支持闪光灯常亮。
 * @note
 * - 一般情况下，App 默认开启前置摄像头，因此如果设备前置摄像头不支持闪光灯，直接使用该方法会返回
 * NO。如果需要检查后置摄像头是否支持闪光灯，需要先使用switchCamera切换摄像头，再使用该方法。
 * - 该方法需要在相机启动后调用，例如调用 startPreview 或 joinChannel 后。
 * - 纯音频 SDK 禁用该接口，如需使用请前往云信官网下载并替换成视频 SDK。
 * @return YES 表示支持，NO 表示不支持。
 * @endif
 */
NERTC_API bool NERTC_CALL nertc_engine_is_camera_torch_supported(struct nertc_engine* self);

/**
 * @if English
 * Checks whether the camera manual focus feature is supported.
 * @note
 * - Make sure that you call this method after the camera starts. For example, you can call this method after you call
 * startPreview or joinChannel.
 * - The audio-only SDK disables this API. If you need to use the API, you can download the standard SDK from the official
 * website of CommsEase and replace the audio-only SDK.
 * @return YES: The camera manual focus feature is supported. NO: The camera manual focus feature is not supported.
 * @endif
 * @if Chinese
 * 检测设备是否支持手动对焦功能。
 * @note
 * - 该方法需要在相机启动后调用，例如调用 startPreview 或 joinChannel 后。
 * - 纯音频 SDK 禁用该接口，如需使用请前往云信官网下载并替换成视频 SDK。
 * @return YES 表示支持，NO 表示不支持。
 * @endif
 */
NERTC_API bool NERTC_CALL nertc_engine_is_camera_focus_supported(struct nertc_engine* self);

/**
 * @if English
 * Checks whether the camera exposure feature is supported.
 * @note
 * - Make sure that you call this method after the camera starts. For example, you can call this method after you call
 * startPreview or joinChannel.
 * - The audio-only SDK disables this API. If you need to use the API, you can download the standard SDK from the official
 * website of CommsEase and replace the audio-only SDK.
 * @return YES: The camera exposure feature is supported. NO: The camera exposure feature is not supported.
 * @endif
 * @if Chinese
 * 检测设备是否支持手动曝光功能。
 * @note
 * - 该方法需要在相机启动后调用，例如调用 startPreview 或 joinChannel 后。
 * - 纯音频 SDK 禁用该接口，如需使用请前往云信官网下载并替换成视频 SDK。
 * @return YES 表示支持，NO 表示不支持。
 * @endif
 */
NERTC_API bool NERTC_CALL nertc_engine_is_camera_exposure_position_supported(struct nertc_engine* self);

/**
 * @if English
 * Sets the camera exposure position.
 * <br>After you call the method, the onCameraExposureChanged callback is triggered on the local client.
 * @note
 * - Make sure that you call this method after the camera starts. For example, you can call this method after you call
 * startPreview or joinChannel.
 * - The audio-only SDK disables this API. If you need to use the API, you can download the standard SDK from the official
 * website of CommsEase and replace the audio-only SDK.
 * @param positionInView The exposure position point.
 * @return The value returned. A value of 0 indicates that the operation is successful.
 * @endif
 * @if Chinese
 * 设置当前摄像头手动曝光位置。
 * <br>成功调用该方法后，本地会触发 onCameraExposureChanged 回调。
 * @note
 * - 该方法需要在相机启动后调用，例如调用 startPreview 或 joinChannel 后。
 * - 纯音频 SDK 禁用该接口，如需使用请前往云信官网下载并替换成视频 SDK。
 * @param positionInView 曝光位置点。
 * @return 操作返回值，成功则返回 0
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_camera_exposure_position(struct nertc_engine* self, float pointX, float pointY);

/**
 * @if English
 * Enables or disables the camera flash feature.
 * @note
 * - Make sure that you call this method after the camera starts. For example, you can call this method after you call
 * startPreview or joinChannel.
 * - The audio-only SDK disables this API. If you need to use the API, you can download the standard SDK from the official
 * website of CommsEase and replace the audio-only SDK.
 * @param on YES: turn on. NO: turn off.
 * @return The value returned. A value of 0 indicates that the operation is successful.
 * @endif
 * @if Chinese
 * 设置是否打开闪光灯。
 * @note
 * - 该方法需要在相机启动后调用，例如调用 startPreview 或 joinChannel 后。
 * - 纯音频 SDK 禁用该接口，如需使用请前往云信官网下载并替换成视频 SDK。
 * @param on YES 表示开启；NO 表示关闭。
 * @return 操作返回值，成功则返回 0
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_camera_torch_on(struct nertc_engine* self, bool on);

/**
 * @if English
 * Check whether the flash is turned on on the device.
 * @note The audio-only SDK disables this API. If you need to use the API, you can download the standard SDK from the official
 * website of CommsEase and replace the audio-only SDK.
 * @return YES: turned on; NO: turned off.
 * @endif
 * @if Chinese
 * 查询设备是否开启了闪光灯。
 * @note 纯音频 SDK 禁用该接口，如需使用请前往云信官网下载并替换成视频 SDK。
 * @return YES 表示开启；NO 表示关闭。
 * @endif
 */
NERTC_API bool NERTC_CALL nertc_engine_is_camera_torch_on(struct nertc_engine* self);

/**
 * @if English
 * Sets the current camera zoom ratio.
 * @note
 * - Make sure that you call this method after the camera starts. For example, you can call this method after you call
 * startPreview or joinChannel.
 * - Before you call this method, we recommend that you view the maximum zoom ratio supported by the camera by calling
 * getCameraMaxZoom and set a zooming ratio as required.
 * - The audio-only SDK disables this API. If you need to use the API, you can download the standard SDK from the official
 * website of CommsEase and replace the audio-only SDK.
 * @param factor The zoom ratio supported by the camera.
 * @return The value returned. A value of 0 indicates that the operation is successful.
 * @endif
 * @if Chinese
 * 设置当前摄像头缩放比例。
 * @note
 * - 该方法需要在相机启动后调用，例如调用 startPreview 或 joinChannel 后。
 * - 建议在调用本接口前，先通过 getCameraMaxZoom 查看摄像头支持的最大缩放比例，并根据实际需求合理设置需要的缩放比例。
 * - 纯音频 SDK 禁用该接口，如需使用请前往云信官网下载并替换成视频 SDK。
 * @param factor 摄像头缩放比例。
 * @return 操作返回值，成功则返回 0
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_camera_zoom_factor(struct nertc_engine* self, float factor);

 /**
 * @if English
 * Gets the zoom ratio supported by the current camera.
 * @return The current zoom ratio is returned.
 * @endif
 * @if Chinese
 * 获取当前摄像头缩放比例。
 * @return 当前缩放比例。
 * @endif
 */
NERTC_API float NERTC_CALL nertc_engine_get_camera_current_zoom(struct nertc_engine* self);

/**
 * @if English
 * Gets maximum zoom ratio supported by the camera.
 * @note
 * - Make sure that you call this method after the camera starts. For example, you can call this method after you call
 * startPreview or joinChannel.
 * - The audio-only SDK disables this API. If you need to use the API, you can download the standard SDK from the official
 * website of CommsEase and replace the audio-only SDK.
 * @return The maximum zoom ratio is returned.
 * @endif
 * @if Chinese
 * 获取摄像头支持最大缩放比例。
 * @note
 * - 该方法需要在相机启动后调用，例如调用 startPreview 或 joinChannel 后。
 * - 纯音频 SDK 禁用该接口，如需使用请前往云信官网下载并替换成视频 SDK。
 * @return 最大缩放比例。
 * @endif
 */
NERTC_API float NERTC_CALL nertc_engine_max_camera_zoom_scale(struct nertc_engine* self);

/**
 * @if English
 * Sets the camera manual focus position.
 * <br>After you call the method, the onNERtcCameraFocusChanged callback is triggered on the local client.
 * @note
 * - Make sure that you call this method after the camera starts. For example, you can call this method after you call
 * startPreview or joinChannel.
 * - The audio-only SDK disables this API. If you need to use the API, you can download the standard SDK from the official
 * website of CommsEase and replace the audio-only SDK.
 * @param focusX The horizontal coordinate of the touch point in the view. Value range: 0 to 1.
 * @param focusY The vertical coordinate of the touch point in the view. Value range: 0 to 1.
 * @return The value returned. A value of 0 indicates that the operation is successful.
 * @endif
 * @if Chinese
 * 设置手动对焦位置。
 * <br>成功调用该方法后，本地会触发  onNERtcCameraFocusChanged 回调。
 * @note
 * - 该方法需要在相机启动后调用，例如调用 startPreview 或 joinChannel 后。
 * - 纯音频 SDK 禁用该接口，如需使用请前往云信官网下载并替换成视频 SDK。
 * @param focusX 触摸点相对于视图的横坐标，范围为 0~1。
 * @param focusY 触摸点相对于视图的纵坐标，范围为 0~1。
 * @return 操作返回值，成功则返回 0
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_camera_focus_position(struct nertc_engine* self, float x, float y);

/**
* @if Chinese
* 设置本地摄像头的视频主流或辅流采集配置。
* <br>通过此接口可以设置本地摄像头采集的主流或辅流视频宽度、高度、旋转角度等。
* @since V4.6.20
* @par 调用时机
* 请在初始化后调用该方法，且该方法在加入房间前后均可调用。
* @par 业务场景
* 在视频通话或直播中，SDK 自动控制摄像头的输出参数。默认情况下，SDK
* 会根据用户该接口的配置匹配最合适的分辨率进行采集。但是在部分业务场景中，如果采集画面质量无法满足实际需求，可以调用该接口调整摄像头的采集配置。
* @note
* - 纯音频 SDK 禁用该接口，如需使用请前往<a href="https://doc.yunxin.163.com/nertc/sdk-download"
* target="_blank">云信官网</a>下载并替换成视频 SDK。
* - 调用该接口设置成功后，会自动重启摄像头采集模块。
* @par 参数说明
* <table>
*  <tr>
*      <th>**参数名称**</th>
*      <th>**类型**</th>
*      <th>**描述**</th>
*  </tr>
*  <tr>
*      <td>type</td>
*      <td> \ref nertc::NERtcVideoStreamType "NERtcVideoStreamType"</td>
*      <td>视频通道类型：<ul><li>kNERtcVideoStreamMain：主流。<li>kNERtcVideoStreamSub：辅流。</td>
*  </tr>
*  <tr>
*      <td>captureConfig</td>
*      <td> \ref nertc::NERtcCameraCaptureConfig "NERtcCameraCaptureConfig"</td>
*      <td>本地摄像头采集配置。</td>
*  </tr>
* </table>
* @par 示例代码
* @code
* //设置本地摄像头主流采集配置
* nertc::NERtcVideoStreamType type = nertc::NERtcVideoStreamType::kNERTCVideoStreamMain;
* nertc::NERtcCameraCaptureConfig video_config_ = {};
* video_config_.captureWidth = 1920; // 编码分辨率的宽
* video_config_.captureHeight = 1080; // 编码分辨率的高
* setCameraCaptureConfig(type, video_config_);
* //设置本地摄像头辅流采集配置
* nertc::NERtcVideoStreamType type = nertc::NERtcVideoStreamType::kNERTCVideoStreamSub;
* nertc::NERtcCameraCaptureConfig video_config_ = {};
* video_config_.captureWidth = 1920; // 编码分辨率的宽
* video_config_.captureHeight = 1080; // 编码分辨率的高
* setCameraCaptureConfig(type, video_config_);
* @endcode
* @return
* - 0（kNERtcNoError）：方法调用成功。
* - 其他：方法调用失败。
* @endif
*/
NERTC_API int NERTC_CALL nertc_engine_set_camera_capture_config(struct nertc_engine* self, nertc_video_stream_type stream_type,const struct nertc_camera_capture_config* config);

/**
* @if Chinese
* 设置视频编码属性。
* <br>通过此接口可以设置视频主流或辅流的编码分辨率、裁剪模式、码率、帧率、带宽受限时的视频编码降级偏好、编码的镜像模式、编码的方向模式参数，详细信息请参考[设置视频属性](https://doc.yunxin.163.com/docs/jcyOTA0ODM/zYwMTQyNzE)。
* @since V4.6.20
* @par 调用时机
* 请在初始化后调用该方法，且该方法在加入房间前后均可调用。
* @note
* - 纯音频 SDK 禁用该接口，如需使用请前往<a href="https://doc.yunxin.163.com/nertc/sdk-download"
* target="_blank">云信官网</a>下载并替换成视频 SDK。
* -
* 每个属性对应一套视频参数，例如分辨率、帧率、码率等。所有设置的参数均为理想情况下的最大值。当视频引擎因网络环境等原因无法达到设置的分辨率、帧率或码率的最大值时，会取最接近最大值的那个值。
* - 此接口为全量参数配置接口，重复调用此接口时，SDK
* 会刷新此前的所有参数配置，以最新的传参为准。所以每次修改配置时都需要设置所有参数，未设置的参数将取默认值。
* @par 参数说明
* <table>
*  <tr>
*      <th>**参数名称**</th>
*      <th>**类型**</th>
*      <th>**描述**</th>
*  </tr>
*  <tr>
*      <td>type</td>
*      <td> \ref nertc::NERtcVideoStreamType "NERtcVideoStreamType"</td>
*      <td>视频通道类型：<ul><li>kNERTCVideoStreamMain：主流。<li>kNERTCVideoStreamSub：辅流。</td>
*  </tr>
*  <tr>
*      <td>config</td>
*      <td> \ref nertc::NERtcVideoConfig "NERtcVideoConfig"</td>
*      <td>视频编码属性配置。</td>
*  </tr>
* </table>
* @par 示例代码
* @code
* nertc::NERtcVideoConfig video_config_ = {};
* video_config_.width = 1920; // 编码分辨率的宽
* video_config_.height = 1080; // 编码分辨率的高
* video_config_.mirror_mode = nertc::kNERtcVideoMirrorModeAuto; // 视频镜像模式
* video_config_.orientation_mode = nertc::kNERtcVideoOutputOrientationModeAdaptative; // 视频旋转的方向模式。
* video_config_.max_profile = nertc::kNERtcVideoProfileHD1080P; // 视频编码配置
* video_config_.crop_mode_ = nertc::kNERtcVideoCropModeDefault;//裁剪模式
* video_config_.bitrate = 0; // 视频编码的码率
* video_config_.min_bitrate = 0;//视频编码的最小码率
* video_config_.framerate = 30; // 视频编码的帧率
* video_config_.min_framerate = 2;// 视频编码的最小帧率
* video_config_.degradation_preference = nertc::kNERtcDegradationDefault;// 带宽受限时的视频编码降级偏好
* setVideoConfig(nertc::kNERTCVideoStreamMain, video_config_);
* @endcode
* @return
* - 0（kNERtcNoError）：方法调用成功。
* - 其他：方法调用失败。
*      - 30005（kNERtcErrInvalidState）：引擎尚未初始化。
*      - 30300：Transiver 未找到。
* @endif
*/
NERTC_API int NERTC_CALL nertc_engine_set_video_config(struct nertc_engine* self, nertc_video_stream_type stream_type, const struct nertc_video_config* config);

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
 * @param[in] enable        指定是否开启双流模式。
 * - true: （默认）开启双流模式。
 * - false: 关闭双流模式。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_enable_dual_stream_mode(struct nertc_engine* self, bool enable);

/**
 * @if English
 * Sets the display mode for local substreams video of screen sharing.
 * This method is used to set the display mode about the local view. The application can repeatedly call the method to change
 * the display mode.
 * @note You must set the local canvas for local substreams through setupLocalSubStreamVideoCanvas.
 * @param[in] scaling_mode      The video display mode. #NERtcVideoScalingMode.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置本地视图显示模式。
 * 该方法设置本地视图显示模式。 App 可以多次调用此方法更改显示模式。
 * @note 在打开屏幕共享前必须设置本地辅流画布。
 * @param[in] scaling_mode      视频显示模式: #NERtcVideoScalingMode
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_local_render_mode(struct nertc_engine* self, nertc_video_stream_type type, nertc_video_scaling_mode scaling_mode);

/**
 * @if English
 * Sets the mirror mode of the local video.
 * The method is used to set whether to enable the mirror mode for the local video. The mirror code determines whether to flip
 * the screen view right or left. Mirror mode for local videos only affects what local users view. The views of remote users
 * are not affected. App can repeatedly call this method to modify the mirror mode.
 * @param[in] mirror_mode       The video mirror mode. For more information, see {@link NERtcVideoMirrorMode}.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置本地视频镜像模式。
 * 该方法用于设置本地视频是否开启镜像模式，即画面是否左右翻转。
 * 本地的视频镜像模式仅影响本地用户所见，不影响远端用户所见。App 可以多次调用此方法更改镜像模式。
 *  @param[in] mirror_mode      视频镜像模式。详细信息请参考 {@link NERtcVideoMirrorMode}。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_local_video_mirror_mode(struct nertc_engine* self,  nertc_video_stream_type type, nertc_video_mirror_mode mirror_mode);

/**
 * @if English
 * Sets display mode for remote views.
 * This method is used to set the display mode for the remote view. App can repeatedly call this method to modify the display
 * mode.
 * @param[in] uid           The ID of a remote user.
 * @param[in] scaling_mode  The video display mode. #NERtcVideoScalingMode.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置远端视图显示模式。
 * 该方法设置远端视图显示模式。App 可以多次调用此方法更改显示模式。
 * @param[in] uid           远端用户 ID。
 * @param[in] scaling_mode  视频显示模式: #NERtcVideoScalingMode
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_remote_render_mode(struct nertc_engine* self, nertc_uid_t uid,  nertc_video_stream_type type, nertc_video_scaling_mode scaling_mode);

/**
 * @if English
 * Enables video preview.
 * <br>The method is used to enable local video preview before you join a room. Prerequisites for calling the API:
 * - Calls \ref IRtcEngine::setupLocalVideoCanvas "setupLocalVideoCanvas" to set preview window.
 * @note After the local video preview is enabled, you must first disable the local preview and call \ref
 * IRtcEngineEx::stopVideoPreview "stopVideoPreview" before joining the room.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 开启视频预览。
 * <br>该方法用于在进入房间前启动本地视频预览。调用该 API 前，必须:
 * - 调用 \ref IRtcEngine::setupLocalVideoCanvas "setupLocalVideoCanvas" 设置预览窗口；
 * @note 启用了本地视频预览后，在进入房间前，本地预览必须先关闭，需要先调用 \ref IRtcEngineEx::stopVideoPreview
 * "stopVideoPreview" 。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_start_video_preview(struct nertc_engine* self, nertc_video_stream_type type);

/**
 * @if English
 * Stops video preview.
 * @note This method needs to be called before a user joins a room.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 停止视频预览。
 * @note 该方法需要在加入房间前调用。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_stop_video_preview(struct nertc_engine* self, nertc_video_stream_type type);

/**
 * @if English
 * Enables or disables publishing the local video stream.
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
 * @param[in] mute
 * - true: 不发送本地视频流
 * - false: 发送本地视频流（默认）
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_mute_local_video_stream(struct nertc_engine* self, nertc_video_stream_type stream_type, bool mute);

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
NERTC_API int NERTC_CALL nertc_engine_set_local_media_priority(struct nertc_engine* self, nertc_media_priority_type priority, bool is_preemptive);

/**
 * @if English
 * Sets parameters for audio and video calls. You can configure the SDK through JSON to provide features like technology
 * review and special customization. Publicizes JSON options in a standardized way.
 * @param[in] parameters  Related parameters for audio and video calls whose format is the JSON string.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置音视频通话的相关参数。通过 JSON 配置 SDK 提供技术预览或特别定制功能。以标准化方式公开 JSON 选项。
 * @param[in] parameters 音视频通话的相关参数。  JSON 字符串形式。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_parameters(struct nertc_engine* self, const char* parameters);

/**
 * @if English
 * Sets the audio recording format.
 * <br>The method is used to set audio recording format of \ref nertc::INERtcAudioFrameObserver::onAudioFrameDidRecord
 * "onAudioFrameDidRecord" callback.
 * @note
 * - The method can be called before or after a user joins a room.
 * - Stops listening and sets the value as empty.
 * @param format The sample rate and channels of data returned in the  *onAudioFrameDidRecord*. A value of NULL is allowed.
 * The default value is NULL.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置录制的声音格式。
 * <br>该方法设置 \ref nertc::INERtcAudioFrameObserver::onAudioFrameDidRecord "onAudioFrameDidRecord" 回调的录制声音格式。
 * @note
 * - 该方法在加入房间前后均可设置或修改。
 * - 取消监听，重置为空。
 * @param format 指定 *onAudioFrameDidRecord* 中返回数据的采样率和数据的通道数。允许传入 NULL，默认为 NULL。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_recording_audio_frame_parameters(struct nertc_engine* self, const struct nertc_audio_frame_request_format* format);

/**
 * @if English
 * Sets the audio playback format.
 * <br>The method is used to set audio recording format of \ref nertc::INERtcAudioFrameObserver::onAudioFrameDidRecord
 * "onAudioFrameDidRecord" callback.
 * @note
 * - The method can be called or modified before or after a user joins a room.
 * - Stops listening and sets the value as empty.
 * @param format The sample rate and channels of data returned in the  *onAudioFrameWillPlayback*. A value of NULL is allowed.
 * The default value is NULL.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置播放的声音格式。
 * <br>该方法设置 \ref nertc::INERtcAudioFrameObserver::onAudioFrameWillPlayback "onAudioFrameWillPlayback"
 * 回调的播放声音格式。
 * @note
 * - 该方法在加入房间前后均可设置或修改。
 * - 取消监听，重置为空。
 * @param format 指定 *onAudioFrameWillPlayback* 中返回数据的采样率和数据的通道数。允许传入 NULL，默认为 NULL。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_playback_audio_frame_parameters(struct nertc_engine* self, const struct nertc_audio_frame_request_format* format);

/**
 * @if English
 * Sets the sample rate of audio mixing stream after the audio is recording and playback.
 * <br>The method is used to set audio recording format of \ref nertc::INERtcAudioFrameObserver::onMixedAudioFrame
 * "onMixedAudioFrame" .
 * @note
 * - The method can be called before or after a user joins a room.
 * - Currently supports setting the sample rate only.
 * - If you do not call the interface to set the data format, the sample rate in the callback return the default value set by
 * the SDK.
 * @param sample_rate   The sample rate of data returned in  *onMixedAudioFrame*. Only 8000, 16000, 32000, 44100, and 48000
 * are supported.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置录制和播放声音混音后的采样率。
 * <br>该方法设置 \ref nertc::INERtcAudioFrameObserver::onMixedAudioFrame "onMixedAudioFrame" 回调的声音格式。
 * @note
 * - 该方法在加入房间前后均可设置或修改。
 * - 目前只支持设置采样率。
 * - 未调用该接口设置数据格式时，回调中的采样率返回 SDK 默认值。
 * @param sample_rate   指定 *onMixedAudioFrame* 中返回数据的采样率。仅支持 8000， 16000， 32000， 44100或48000。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_mixed_audio_frame_parameters(struct nertc_engine* self, int sample_rate);

/**
 * @if English
 * Registers the audio observer object.
 * <br>The method is used to set audio capture or play PCM data callbacks. You can use the method to process audios. You need
 * to register callbacks with this method when engine needs to trigger callbacks of \ref
 * nertc::INERtcAudioFrameObserver::onAudioFrameDidRecord "onAudioFrameDidRecord" or \ref
 * nertc::INERtcAudioFrameObserver::onAudioFrameWillPlayback "onAudioFrameWillPlayback".
 * @param observer  The object instance. If you pass in NULL, you cancel the registration and clear the settings of
 * NERtcAudioFrameRequestFormat.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 注册语音观测器对象。
 * <br>该方法用于设置音频采集和播放PCM回调，可用于声音处理等操作。当需要引擎给出 \ref
 * nertc::INERtcAudioFrameObserver::onAudioFrameDidRecord "onAudioFrameDidRecord" 或 \ref
 * nertc::INERtcAudioFrameObserver::onAudioFrameWillPlayback "onAudioFrameWillPlayback" 回调时，需要使用该方法注册回调。
 * @param observer  接口对象实例。如果传入 NULL，则取消注册，同时会清理NERtcAudioFrameRequestFormat相关设置。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_audio_frame_observer(struct nertc_engine* self, struct nertc_audio_frame_observer* observer);

/**
 * @if English
 * Starts recording an audio dump file. Audio dump files can be used to analyze audio issues.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 开始记录音频 dump。 音频 dump 可用于分析音频问题。
 * @param type 音频dump类型
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_start_audio_dump(struct nertc_engine* self, nertc_audio_dump_type type);

/**
 * @if English
 * Finishes recording an audio dump file.
 * @return
 - 0: Success.
 - Other values: Failure.
 * @endif
 * @if Chinese
 * 结束音频dump。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_stop_audio_dump(struct nertc_engine* self);

/**
 设置音频播放扬声器模式（仅iOS/Android有效）

 @param enable 是否使用扬声器模式
 @return 操作返回值，成功则返回 0
 */
NERTC_API int NERTC_CALL nertc_engine_set_loudspeaker_mode(struct nertc_engine* self, bool enable);

/**
 获取目前是否使用扬声器模式（仅iOS/Android有效）

 @param enabled 是否正在使用扬声器模式
 @return
 - 0: 方法调用成功；
 - 其他: 方法调用失败。
 */
NERTC_API int NERTC_CALL nertc_engine_get_loudspeaker_mode(struct nertc_engine* self, bool* enabled);

/**
 * @if English
 * Starts playing a music file.
 * <br>This method mixes the specified local or online audio file with the audio stream captured by the audio devices.
 * - Supported audio formats: MP3, M4A, AAC, 3GP, WMA, and WAV. Files that are stored in local or online URLs are supported.
 * - After you successfully call the method, if the playback status is changed, the local triggers \ref
 * nertc::IRtcEngineEventHandlerEx::onAudioMixingStateChanged "onAudioMixingStateChanged"  callbacks.
 * @note
 * - You can call this method after joining a room.
 * - Since V4.3.0, if you call this method to play a music file during a call, and manually set the playback volume of the
 * audio mixing and the sent volume, the setting is used when you call the method again during the current call.
 * @param[in] option        Options of creating audio mixing configurations that include types, full path or URL. For more
 * information, see {@link NERtcCreateAudioMixingOption}.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 开始播放音乐文件。
 * <br>该方法指定本地或在线音频文件来和录音设备采集的音频流进行混音。
 * - 支持的音乐文件类型包括 MP3、M4A、AAC、3GP、WMA 和 WAV 格式，支持本地文件或在线 URL。
 * - 成功调用该方法后，如果播放状态改变，本地会触发  \ref nertc::IRtcEngineEventHandlerEx::onAudioMixingStateChanged
 * "onAudioMixingStateChanged"  回调。
 * @note
 * - 请在加入房间后调用该方法。
 * - 从 V4.3.0 版本开始，
 * 若您在通话中途调用此接口播放音乐文件时，手动设置了伴音播放音量或发送音量，则当前通话中再次调用时默认沿用此设置。
 * - 在 V4.4.0 版本中，开启或关闭本地音频采集的操作不影响音乐文件在远端的播放，即 enableLocalAudio(false)
 * 后仍旧可以发送伴音。在其他版本中，必须开启音频采集才能发送伴音。
 * @param[in] option        创建混音任务配置的选项，包括混音任务类型、混音文件全路径或URL等。详细信息请参考 {@link
 * NERtcCreateAudioMixingOption}。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_start_audio_mixing(struct nertc_engine* self, struct nertc_create_audio_mixing_option* option);

/**
 * @if English
 * Stops playing music files or audio mixing.
 * <br>The method stops playing the audio mixing. You can call the method when you are in a room.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 停止播放音乐文件及混音。
 * <br>该方法停止播放伴奏。请在房间内调用该方法。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_stop_audio_mixing(struct nertc_engine* self);

/**
 * @if English
 * Stops playing music files or audio mixing.
 * <br>The method pauses playing audio mixing. You can call the method when you are in a room.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 暂停播放音乐文件及混音。
 * <br>该方法暂停播放伴奏。请在房间内调用该方法。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_pause_audio_mixing(struct nertc_engine* self);

/**
 * @if English
 * Resumes playing the audio mixing.
 * <br>The method resumes audio mixing, and continues playing the audio mixing. You can call the method when you are in a
 * room.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 恢复播放伴奏。
 * <br>该方法恢复混音，继续播放伴奏。请在房间内调用该方法。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_resume_audio_mixing(struct nertc_engine* self);

/**
 * @if English
 * Adjusts the audio mixing volume for publishing.
 * <br>The method adjusts the volume for publishing of the audio mixing in the audio mixing. You can call the method when you
 * are in a room.
 * @param[in] volume    The audio mixing volume for publishing. Valid values: 0 to 100. The default value of 100 represents
 * the original volume.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 调节伴奏发送音量。
 * <br>该方法调节混音里伴奏的发送音量大小。请在房间内调用该方法。
 * @param[in] volume    伴奏发送音量。取值范围为 0~100。默认 100 为原始文件音量。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_audio_mixing_send_volume(struct nertc_engine* self, uint32_t volume);

/**
 * @if English
 * Gets the volume for publishing of audio mixing.
 * <br>The method gets the volume for publishing of the audio mixing in the audio mixing. You can call the method when you are
 * in a room.
 * @param[out] volume   The volume for publishing of the audio mixing.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 获取伴奏发送音量。
 * <br>该方法获取混音里伴奏的发送音量大小。请在房间内调用该方法。
 * @param[out] volume   伴奏发送音量。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_get_audio_mixing_send_volume(struct nertc_engine* self, uint32_t* volume);

/**
 * @if English
 * Adjusts the playback volume of the audio mixing.
 * <br>The method adjusts the playback volume of the audio mixing in the audio mixing. You can call the method when you are in
 * a room.
 * @param[in] volume    The volume range of the audio mixing is 0 to 100. The default value of 100 represents the original
 * volume.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 调节伴奏播放音量。
 * <br>该方法调节混音里伴奏的播放音量大小。请在房间内调用该方法。
 * @param[in] volume    伴奏音量范围为 0~100。默认 100 为原始文件音量。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_audio_mixing_playback_volume(struct nertc_engine* self, uint32_t volume);

/**
 * @if English
 * Gets the playback volume of the audio mixing.
 * <br>The method gets the playback volume of the audio mixing in the audio mixing. You can call the method when you are in a
 * room.
 * @param[out] volume   The volume of the audio mixing.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 获取伴奏播放音量。
 * <br>该方法获取混音里伴奏的播放音量大小。请在房间内调用该方法。
 * @param[out] volume   伴奏播放音量。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_get_audio_mixing_playback_volume(struct nertc_engine* self, uint32_t* volume);

/**
 * @if English
 * Gets the duration of the audio mixing.
 * <br>The method gets the duration of the audio mixing. Unit: milliseconds. You can call the method when you are in a room.
 * @param[out] duration     The duration of the audio mixing. Unit: milliseconds.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 获取伴奏时长。
 * <br>该方法获取伴奏时长，单位为毫秒。请在房间内调用该方法。
 * @param[out] duration     伴奏时长，单位为毫秒。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_get_audio_mixing_duration(struct nertc_engine* self, uint64_t* duration);

/**
 * @if English
 * Gets the playback position of the music file.
 * <br>The method gets the playback position of the music file. Unit: milliseconds. You can call the method when you are in a
 * room.
 * @param[out] position     The playback position of the audio mixing file. Unit: milliseconds.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 获取音乐文件的播放进度。
 * <br>该方法获取当前伴奏播放进度，单位为毫秒。请在房间内调用该方法。
 * @param[out] position     伴奏播放进度，单位为毫秒。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_get_audio_mixing_current_position(struct nertc_engine* self, uint64_t* position);

/**
 * @if English
 * Sets the playback position of the music file to a different starting position.
 * <br>The method sets the playback position of the music file to a different starting position. The method allows you to play
 * the music file from the position based on your requirements rather than from the beginning of the music file.
 * @param[in] seek_position     The playback position of the music file. Unit: milliseconds.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置音乐文件的播放位置。
 * <br>该方法可以设置音频文件的播放位置，这样你可以根据实际情况播放文件，而非从头到尾播放整个文件。
 * @param[in] seek_position     进度条位置，单位为毫秒。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_audio_mixing_position(struct nertc_engine* self, uint64_t seek_position);

/**
 * @if Chinese
 * 设置当前伴音文件的音调。
 * - 通过此接口可以实现当本地人声和播放的音乐文件混音时，仅调节音乐文件的音调。
 * @since V4.6.29
 * @par 使用前提
 * 请先调用 \ref nertc::IRtcEngineEx::startAudioMixing "startAudioMixing" 方法开启伴音。
 * @par 调用时机
 * 请在引擎初始化之后调用此接口，且该方法仅可在加入房间后调用。
 * @par 业务场景
 * 适用于 K 歌中为了匹配人声，调节背景音乐音高的场景。
 * @note
 * 当前伴音任务结束后，此接口的设置会恢复至默认。
 * @par 参数说明
 * <table>
 *  <tr>
 *      <th>**参数名称**</th>
 *      <th>**类型**</th>
 *      <th>**描述**</th>
 *  </tr>
 *  <tr>
 *      <td>pitch</td>
 *      <td>int32_t</td>
 *      <td>当前伴音文件的音调。默认值为 0，即不调整音调，取值范围为 -12 ~
 * 12，按半音音阶调整。每相邻两个值的音高距离相差半音；取值的绝对值越大，音调升高或降低得越多。</td>
 *  </tr>
 * </table>
 * @par 示例代码
 * @code
 * int pitch = 0;
 * rtc_engine_->setAudioMixingPitch(pitch);
 * @endcode
 * @par 相关接口
 * 可以调用 \ref nertc::IRtcEngineEx::getAudioMixingPitch "getAudioMixingPitch" 方法获取伴音文件的音调。
 * @return
 * - 0（kNERtcNoError）：方法调用成功。
 * - 其他：方法调用失败。
 *      - 30003（kNERtcErrInvalidParam）：参数有误，比如 pitch 超出范围。
 *      - 30005（kNERtcErrInvalidState）：当前状态不支持的操作，比如找不到对应的伴音任务或引擎尚未初始化。
 *      - 30101（kNERtcErrChannelNotJoined）：尚未加入房间。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_audio_mixing_pitch(struct nertc_engine* self, int32_t pitch);

/**
 * @if Chinese
 * 获取当前伴音文件的音调。
 * @since V4.6.29
 * @par 使用前提
 * 请先调用 \ref nertc::IRtcEngineEx::startAudioMixing "startAudioMixing" 方法开启伴音。
 * @par 调用时机
 * 请在引擎初始化之后调用此接口，且该方法仅可在加入房间后调用。
 * @par 参数说明
 * <table>
 *  <tr>
 *      <th>**参数名称**</th>
 *      <th>**类型**</th>
 *      <th>**描述**</th>
 *  </tr>
 *  <tr>
 *      <td>pitch</td>
 *      <td>int32_t*</td>
 *      <td>当前伴音文件的音调。默认值为 0，即不调整音调，取值范围为 -12 ~
 * 12，按半音音阶调整。每相邻两个值的音高距离相差半音；取值的绝对值越大，音调升高或降低得越多。</td>
 *  </tr>
 * </table>
 * @par 示例代码
 * @code
 * int pitch = 0;
 * rtc_engine_->getAudioMixingPitch(&pitch);
 * @endcode
 * @return
 * - 0（kNERtcNoError）：方法调用成功。
 * - 其他：方法调用失败。
 *      - 30005（kNERtcErrInvalidState）：当前状态不支持的操作，比如找不到对应的伴音任务或引擎尚未初始化。
 *      - 30101（kNERtcErrChannelNotJoined）：尚未加入房间。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_get_audio_mixing_pitch(struct nertc_engine* self, int32_t* pitch);

/**
 * @if English
 * Plays a specified audio effect file.
 * - After the method is successfully called, if the playback ends, the onAudioEffectFinished callback is triggered.
 * - Supported audio formats: MP3, M4A, AAC, 3GP, WMA, and WAV. Files that are stored in local or online URLs are supported.
 * @note
 * - You can call this method after joining a room.
 * - You can call the method for multiple times. You can play multiple audio effect files simultaneously by passing in
 * different effect_ids and options. Various audio effects are mixed. To gain optimal user experience, we recommend you to
 * play no more than three audio effect files at the same time.
 * @param[in] effect_id         The ID of the specified audio effect. Each audio effect has a unique ID.
 * @param[in] option            The options of creating audio effect files configurations including types, full path or URL of
 * audio mixing files. For more information, see {@link NERtcCreateAudioEffectOption}.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 播放指定音效文件。
 * - 成功调用该方法后，如果播放结束，本地会触发 onAudioEffectFinished 回调。
 * - 支持的音效文件类型包括 MP3、M4A、AAC、3GP、WMA 和 WAV 格式，支持本地文件和在线 URL。
 * @note
 * - 请在加入房间后调用该方法。
 * - 您可以多次调用该方法，通过传入不同的音效文件的effect_id 和 option
 * ，同时播放多个音效文件，实现音效叠加。为获得最佳用户体验，建议同时播放的音效文件不超过 3 个。
 * @param[in] effect_id         指定音效的 ID。每个音效均有唯一的 ID。
 * @param[in] option            创建音效任务配置的选项，包括混音任务类型、混音文件全路径或 URL 等。详细说明请参考 {@link
 * NERtcCreateAudioEffectOption}。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_play_effect(struct nertc_engine* self, uint32_t effect_id, struct nertc_create_audio_effect_option* option);

/**
 * @if English
 * Stops playing a specified audio effect file.
 * <br>You can call the method when you are in a room.
 * @param[in] effect_id         The ID of the specified audio effect. Each audio effect has a unique ID.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 停止播放指定音效文件。
 * <br>请在房间内调用该方法。
 * @param[in] effect_id         指定音效的 ID。每个音效均有唯一的 ID。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_stop_effect(struct nertc_engine* self, uint32_t effect_id);

/**
 * @if English
 * Stops playing all audio effects.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 停止播放所有音效文件。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_stop_all_effects(struct nertc_engine* self);

/**
 * @if English
 * Pauses playing all audio effects.
 * <br>You can call the method when you are in a room.
 * @param[in] effect_id     The ID of the specified audio effect. Each audio effect has a unique ID.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 暂停音效文件播放。
 * <br>请在房间内调用该方法。
 * @param[in] effect_id     指定音效的 ID。每个音效均有唯一的 ID。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_pause_effect(struct nertc_engine* self, uint32_t effect_id);

/**
 * @if English
 * Resumes playing a specified audio effect.
 * <br>You can call the method when you are in a room.
 * @param[in] effect_id     The ID of the specified audio effect. Each audio effect has a unique ID.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 恢复播放指定音效文件。
 * <br>请在房间内调用该方法。
 * @param[in] effect_id     指定音效的 ID。每个音效均有唯一的 ID。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_resume_effect(struct nertc_engine* self, uint32_t effect_id);

/**
 * @if English
 * Pauses all audio effect files.
 * <br>You can call the method when you are in a room.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 暂停所有音效文件播放。
 * <br>请在房间内调用该方法。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_pause_all_effects(struct nertc_engine* self);

/**
 * @if English
 * Resumes playing all audio effects files.
 * <br>You can call the method when you are in a room.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 恢复播放所有音效文件。
 * <br>请在房间内调用该方法。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_resume_all_effects(struct nertc_engine* self);

/**
 * @if English
 * Adjusts the audio effect volume for publishing.
 * The method adjusts the audio effect volume for publishing. You can call the method when you are in a room.
 * @param[in] effect_id         The ID of the specified audio effect. Each audio effect has a unique ID.
 * @param[in] volume            The audio effect volume. Value range: 0 to 100. The default value of 100 represents the
 * original volume.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 调节音效发送音量。
 * 该方法调节音效的发送音量大小。请在房间内调用该方法。
 * @param[in] effect_id         指定音效的 ID。每个音效均有唯一的 ID。
 * @param[in] volume            音效音量范围为 0~100。默认 100 为原始文件音量。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_effect_send_volume(struct nertc_engine* self, uint32_t effect_id, uint32_t volume);

/**
 * @if English
 * Gets the audio effect volume for publishing.
 * The method gets the audio effect volume for publishing. You can call the method when you are in a room.
 * @param[in] effect_id         The ID of the specified audio effect. Each audio effect has a unique ID.
 * @param[out] volume           The audio effect volume for publishing.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 获取音效发送音量。
 * 该方法获取音效的发送音量大小。请在房间内调用该方法。
 * @param[in] effect_id         指定音效的 ID。每个音效均有唯一的 ID。
 * @param[out] volume           音效发送音量。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_get_effect_send_volume(struct nertc_engine* self, uint32_t effect_id, uint32_t* volume);

/**
 * @if English
 * Sets the playback volume of an audio effect file.
 * You can call this method after joining a room.
 * @param[in] effect_id         The ID of the specified audio effect. Each audio effect has a unique ID.
 * @param[in] volume            The audio effect volume for publishing. Valid values: 0 to 100. The default value is 100.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置音效文件播放音量。
 * 请在加入房间后调用该方法。
 * @param[in] effect_id         指定音效的 ID。每个音效均有唯一的 ID。
 * @param[in] volume            音效播放音量。范围为0~100，默认为100。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_effect_playback_volume(struct nertc_engine* self, uint32_t effect_id, uint32_t volume);

/**
 * @if English
 * Gets the playback volume of the audio effects files.
 * <br>You can call this method after joining a room.
 * @param[in] effect_id         The ID of the specified audio effect. Each audio effect has a unique ID.
 * @param[out] volume           The audio effect playback volume.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 获取音效文件播放音量。
 * <br>请在加入房间后调用该方法。
 * @param[in] effect_id         指定音效的 ID。每个音效均有唯一的 ID。
 * @param[out] volume           音效播放音量。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_get_effect_playback_volume(struct nertc_engine* self, uint32_t effect_id, uint32_t* volume);

/**
 * @if Chinese
 * 设置指定音效文件的音调。
 * - 通过此接口可以实现当本地人声和播放的音乐文件混音时，仅调节音乐文件的音调。
 * @since V4.6.29
 * @par 使用前提
 * 请先调用 \ref nertc::IRtcEngineEx::playEffect "playEffect" 方法播放音效。
 * @par 调用时机
 * 请在引擎初始化之后调用此接口，且该方法仅可在加入房间后调用。
 * @par 业务场景
 * 适用于 K 歌中为了匹配人声，调节背景音乐音高的场景。
 * @note
 * 当前音效任务结束后，此接口的设置会恢复至默认。
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
 *      <td>指定音效文件的 ID。每个音效文件均对应唯一的 ID。</td>
 *  </tr>
 *  <tr>
 *      <td>pitch</td>
 *      <td>int32_t</td>
 *      <td>指定音效文件的音调。默认值为 0，即不调整音调，取值范围为 -12 ~
 * 12，按半音音阶调整。每相邻两个值的音高距离相差半音；取值的绝对值越大，音调升高或降低得越多。</td>
 *  </tr>
 * </table>
 * @par 示例代码
 * @code
 * uint32 effect_id = 7788;
 * int32_t pitch = 0;
 * rtc_engine_->setEffectPitch(effect_id, pitch);
 * @endcode
 * @par 相关接口
 * 可以调用 \ref nertc::IRtcEngineEx::getEffectPitch "getEffectPitch" 方法获取指定音效文件的音调。
 * @return
 * - 0（kNERtcNoError）：方法调用成功。
 * - 其他：方法调用失败。
 *      - 30003（kNERtcErrInvalidParam）：参数有误，比如 pitch 超出范围。
 *      - 30005（kNERtcErrInvalidState）：当前状态不支持的操作，比如找不到对应的音效任务或引擎尚未初始化。
 *      - 30101（kNERtcErrChannelNotJoined）：尚未加入房间。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_effect_pitch(struct nertc_engine* self, uint32_t effect_id, int32_t pitch);

/**
 * @if Chinese
 * 获取指定音效文件的音调。
 * @since V4.6.29
 * @par 使用前提
 * 请先调用 \ref nertc::IRtcEngineEx::playEffect "playEffect" 方法播放音效。
 * @par 调用时机
 * 请在引擎初始化之后调用此接口，且该方法仅可在加入房间后调用。
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
 *      <td>指定音效文件的 ID。每个音效文件均对应唯一的 ID。</td>
 *  </tr>
 *  <tr>
 *      <td>pitch</td>
 *      <td>int32_t</td>
 *      <td>指定音效文件的音调。默认值为 0，即不调整音调，取值范围为 -12 ~
 * 12，按半音音阶调整。每相邻两个值的音高距离相差半音；取值的绝对值越大，音调升高或降低得越多。</td>
 *  </tr>
 * </table>
 * @par 示例代码
 * @code
 * uint32 effect_id = 7788;
 * int32_t pitch = 0;
 * rtc_engine_->getEffectPitch(effect_id, &pitch);
 * @endcode
 * @return
 * - 0（kNERtcNoError）：方法调用成功。
 * - 其他：方法调用失败。
 *      - 30005（kNERtcErrInvalidState）：当前状态不支持的操作，比如找不到对应的音效任务或引擎尚未初始化。
 *      - 30101（kNERtcErrChannelNotJoined）：尚未加入房间。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_get_effect_pitch(struct nertc_engine* self, uint32_t effect_id, int32_t* pitch);

/**
 * @if English
 * Set the playback position of the sound effect file.
 * This method can set the playback position of the sound effect file, so that you can play the file according to the
 * actual situation, rather than playing the entire file from beginning to end.
 * @param effect_id Effect ID。
 * @param timestamp_ms The playback position of the sound effect file, in milliseconds.
 * @return
 * - 0: success
 * - Others: failure
 * @endif
 * @if Chinese
 * 设置指定音效文件的播放位置。
 * - 通过此接口可以实现根据实际情况播放音效文件，而非从头到尾播放整个文件。
 * @since V4.6.29
 * @par 使用前提
 * 请先调用 \ref nertc::IRtcEngineEx::playEffect "playEffect" 方法播放音效。
 * @par 调用时机
 * 请在引擎初始化之后调用此接口，且该方法仅可在加入房间后调用。
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
 *      <td>指定音效文件的 ID。每个音效文件均对应唯一的 ID。</td>
 *  </tr>
 *  <tr>
 *      <td>timestamp_ms</td>
 *      <td>uint64_t</td>
 *      <td>指定音效文件的起始播放位置。单位为毫秒。</td>
 *  </tr>
 * </table>
 * @par 示例代码
 * @code
 * uint32_t effect_id = 7788;
 * uint64_t timestamp_ms = 0;
 * rtc_engine_->setEffectPosition(effect_id, timestamp_ms);
 * @endcode
 * @par 相关接口
 * - \ref nertc::IRtcEngineEx::getEffectCurrentPosition "getEffectCurrentPosition"：获取指定音效文件的当前播放位置。
 * - \ref nertc::IRtcEngineEventHandlerEx::onAudioEffectTimestampUpdate
 * "onAudioEffectTimestampUpdate"：注册此回调实时获取指定音效文件的当前播放进度，默认为每隔 1s 返回一次。
 * @return
 * - 0（kNERtcNoError）：方法调用成功。
 * - 其他：方法调用失败。
 *      - 30001（kNERtcErrFatal）：接口操作失败或未找到对应的音效任务。
 *      - 30003（kNERtcErrInvalidParam）：参数错误，比如 effect_id 不正确。
 *      - 30101（kNERtcErrChannelNotJoined）：尚未加入房间。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_effect_position(struct nertc_engine* self, uint32_t effect_id, uint64_t timestamp_ms);

/**
 * @if English
 * Get the playback progress of the sound effect.
 * This method obtains the current sound effect playback progress in milliseconds.
 * @note Please call this method in the room.
 * @param effect_id Effect ID。
 * @param timestamp_ms The playback position of the sound effect file, in milliseconds.
 * @return
 * - 0: success
 * - Others: failure
 * @endif
 * @if Chinese
 * 获取指定音效文件的播放进度。
 * @since V4.6.29
 * @par 使用前提
 * 请先调用 \ref nertc::IRtcEngineEx::playEffect "playEffect" 方法播放音效。
 * @par 调用时机
 * 请在引擎初始化之后调用此接口，且该方法仅可在加入房间后调用。
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
 *      <td>指定音效文件的 ID。每个音效文件均对应唯一的 ID。</td>
 *  </tr>
 *  <tr>
 *      <td>timestamp_ms</td>
 *      <td>uint64_t*</td>
 *      <td>指定音效文件的当前播放位置。单位为毫秒。</td>
 *  </tr>
 * </table>
 * @par 示例代码
 * @code
 * uint32 effect_id = 7788;
 * int32_t pitch = 0;
 * rtc_engine_->getEffectCurrentPosition(effect_id, &timestamp_ms);
 * @endcode
 * @return
 * - 0（kNERtcNoError）：方法调用成功。
 * - 其他：方法调用失败。
 *      - 30001（kNERtcErrFatal）：接口操作失败或未找到对应的音效任务。
 *      - 30003（kNERtcErrInvalidParam）：参数错误，比如 effect_id 不正确。
 *      - 30101（kNERtcErrChannelNotJoined）：尚未加入房间。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_get_effect_current_position(struct nertc_engine* self, uint32_t effect_id, uint64_t* timestamp_ms);

/**
 * @if English
 * Get the duration of the sound effect file.
 * This method obtains the duration of the sound effect file, in milliseconds.
 * @note Please call this method in the room.
 * @param effect_id Effect ID。
 * @param timestamp_ms The playback position of the sound effect file, in milliseconds.
 * @return
 * - 0: success
 * - Others: failure
 * @endif
 * @if Chinese
 * 获取指定音效文件的时长。
 * @since V4.6.29
 * @par 使用前提
 * 请先调用 \ref nertc::IRtcEngineEx::playEffect "playEffect" 方法播放音效。
 * @par 调用时机
 * 请在引擎初始化之后调用此接口，且该方法仅可在加入房间后调用。
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
 *      <td>指定音效文件的 ID。每个音效文件均对应唯一的 ID。</td>
 *  </tr>
 *  <tr>
 *      <td>duration_ms</td>
 *      <td>uint64_t*</td>
 *      <td>指定音效文件的时长。单位为毫秒。</td>
 *  </tr>
 * </table>
 * @par 示例代码
 * @code
 * uint32 effect_id = 7788;
 * int32_t pitch = 0;
 * rtc_engine_->getEffectDuration(effect_id, &duration_ms);
 * @endcode
 * @return
 * - 0（kNERtcNoError）：方法调用成功。
 * - 其他：方法调用失败。
 *      - 30001（kNERtcErrFatal）：接口操作失败或未找到对应的音效任务。
 *      - 30003（kNERtcErrInvalidParam）：参数错误，比如 effect_id 不正确。
 *      - 30101（kNERtcErrChannelNotJoined）：尚未加入房间。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_get_effect_duration(struct nertc_engine* self, uint32_t effect_id, uint64_t* duration_ms);

/**
 * @if English
 * Enables or disables in-ear monitoring.
 * @note
 * - You can call the method when you are in a room.
 * - After in-ear monitoring is enabled, you must wear a headset or earpieces to use the in-ear monitoring feature. We
 * recommend that you listen for changes of playback devices through  \ref IRtcEngineEventHandlerEx::onAudioDeviceStateChanged
 * "onAudioDeviceStateChanged" and  \ref IRtcEngineEventHandlerEx::onAudioDefaultDeviceChanged  "onAudioDefaultDeviceChanged".
 * Only when the device changes to headset, you can enable in-ear monitoring.
 * @param[in] enabled   Enabled or disabled.
 * @param[in] volume    The volume of ear-monitoring.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 开启或关闭耳返。
 * @note
 * - 请在房间内调用该方法。
 * - 开启耳返功能后，必须连接上耳机或耳麦，才能正常使用耳返功能。建议通过 \ref
 * IRtcEngineEventHandlerEx::onAudioDeviceStateChanged  "onAudioDeviceStateChanged" 及 \ref
 * IRtcEngineEventHandlerEx::onAudioDefaultDeviceChanged  "onAudioDefaultDeviceChanged"
 * 监听播放设备的变化，当监听到播放设备切换为耳机时才开启耳返。
 * @param[in] enabled   开启或关闭。
 * @param[in] volume    耳返音量。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_enable_earback(struct nertc_engine* self, bool enabled, uint32_t volume);

/**
 * @if English
 * Sets the volume for in-ear monitoring.
 * You can call the method when you are in a room.
 * @param[in] volume    The volume of ear-monitoring. Valid values: to 100. The default value is 100.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置耳返音量。
 * 请在房间内调用该方法。
 * @param[in] volume    耳返音量。可设置为 0~100，默认为 100。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_earback_volume(struct nertc_engine* self, uint32_t volume);

/**
 * @if English
 * Enables or disables local audio capture through the sound card.
 * @since V4.4.0
 * After the feature is enabled, the audio played by the sound card is integrated into local video streams. In this way, you can
 publish the audio to the remote side.
 * @note
 * - The method applies to only macOS and Windows.
 * - The capture feature is not supported on the macOS by default. If you need to enable the feature, the app needs to enable a
 virtual sound card and name the sound card as device_name to pass in the SDK. We recommend that you can use Soundflower as
 virtual sound card to deliver better audio effect.
 * - You can call this method before or after you join a room.
 * @param[in] enabled       Specifies whether to enable the capture feature through the sound card.
                            - true: Enables audio capture through the sound card.
                            - false: Disables audio capture through the sound card (default).
 * @param[in] device_name   The device name of the sound card. The name is set as NULL by default, which indicates capturing
 through the current sound card. <br>The parameter applies to macOS platform only. <br>If users use virtual sound cards such as
 “Soundflower”, you can set the sound card name of virtual card as parameter. In this way, the SDK finds the corresponding
 device of virtual sound cards and starts capturing.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 开启或关闭声卡采集。
 * @since V4.4.0
 * 启用声卡采集功能后，声卡播放的声音会被合到本地音频流中，从而可以发送到远端。
 * @note
 * - 该方法仅适用于 macOS 和 Windows 平台。
 * - 该方法在加入房间前后都能调用。
 * - 您不能同时使用音频自播放和音频共享功能，否则会导致加入音视频通话房间后，无法听到对端用户的音频和本地共享音频的声音。
 * - macOS 系统默认声卡不支持采集功能，如需开启此功能需要 App 自己启用一个虚拟声卡，并将该虚拟声卡的名字作为 device_name 传入
 SDK。 网易云信建议使用 Soundflower 作为虚拟声卡，以获得更好的音频效果。
 * @param[in] enabled       是否开启声卡采集功能。
                            - true: 开启声卡采集。
                            - false: （默认）关闭声卡采集。
 * @param[in] device_name   声卡的设备名。默认设为 NULL，即使用当前声卡采集。<br>该参数仅适用于 macOS
 平台。<br>如果用户使用虚拟声卡，如 “Soundflower”，可以将虚拟声卡名称 “Soundflower” 作为参数，SDK
 会找到对应的虚拟声卡设备，并开始采集。
 * @return
 * - 0: 方法调用成功
 * - 其他: 方法调用失败
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_enable_loopback_recording(struct nertc_engine* self, bool enabled, const char* device_name);

/**
 * @if English
 * Adjusts the volume of captured signals of sound cards.
 * @since V4.4.0
 * After calling sound card capturing by calling \ref nertc::IRtcEngineEx::enableLoopbackRecording "enableLoopbackRecording",
 * you can call the method to adjust the volume of captured signals of sound cards.
 * @param[in] volume        The captured signals volume through sound cards. Value range: 0 to 100. The default value of 100
 * represents the original volume.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 调节声卡采集信号音量。
 * @since V4.4.0
 * 调用 \ref nertc::IRtcEngineEx::enableLoopbackRecording "enableLoopbackRecording"
 * 开启声卡采集后，你可以调用该方法调节声卡采集的信号音量。
 * @param[in] volume        声卡采集信号音量。取值范围为 [0,100]。默认值为 100，表示原始音量。
 * @return
 * - 0: 方法调用成功
 * - 其他: 方法调用失败
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_adjust_loopback_recording_signal_volume(struct nertc_engine* self, int volume);

/**
 * @if English
 * Registers a stats observer.
 * @param[in] observer      The stats observer.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 注册统计信息观测器。
 * @param[in] observer      统计信息观测器
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API void NERTC_CALL nertc_engine_set_stats_observer(struct nertc_engine* self, struct nertc_media_stats_observer* observer);

/**
 * @if English
 * Registers a video encoder qos observer.
 * @note The observer must be set after the SDK is initialized and becomes invalid after the SDK is released.
 * @since V4.6.25
 * @param[in] observer  The object instance. If you pass in NULL, you cancel the registration.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 注册视频编码 QoS 信息监听器。
 * - 通过此接口可以设置 \ref nertc::INERtcVideoEncoderQosObserver::onRequestSendKeyFrame "onRequestSendKeyFrame"、 \ref
 * nertc::INERtcVideoEncoderQosObserver::onVideoCodecUpdated "onVideoCodecUpdated"、 \ref
 * nertc::INERtcVideoEncoderQosObserver::onBitrateUpdated "onBitrateUpdated"
 * 回调监听，并通过返回的相关视频编码数据调整视频编码策略。
 * @since V4.6.29
 * @par 调用时机
 * 请在引擎初始化之后调用此接口，且该方法在加入房间前后均可调用。
 * @par 业务场景
 * 适用于需要自行处理视频数据的采集与编码的场景。
 * @note
 * 该方法设置内部引擎为启用状态，在 \ref IRtcEngine::leaveChannel "leaveChannel"
 * 后仍然有效；如果需要关闭该功能，需要在下次通话前调用此接口关闭视频编码 QoS 信息监听。
 * @par 参数说明
 * <table>
 *  <tr>
 *      <th>**参数名称**</th>
 *      <th>**类型**</th>
 *      <th>**描述**</th>
 *  </tr>
 *  <tr>
 *      <td>observer</td>
 *      <td>INERtcVideoEncoderQosObserver *</td>
 *      <td>接口对象实例。可以传 NULL 表示取消注册。</td>
 *  </tr>
 * </table>
 * @par 示例代码
 * @code
 * auto ret = rtc_engine_->setVideoEncoderQosObserver(observer); // observer为观测器实例地址
 * if (ret != nertc::kNERtcNoError) {
 * // 错误处理
 * }
 * @endcode
 * @par 相关回调
 * \ref nertc::INERtcVideoEncoderQosObserver::onRequestSendKeyFrame "onRequestSendKeyFrame"：I 帧请求回调。
 * \ref nertc::INERtcVideoEncoderQosObserver::onBitrateUpdated "onBitrateUpdated"：码率信息回调。
 * \ref nertc::INERtcVideoEncoderQosObserver::onVideoCodecUpdated "onVideoCodecUpdated"：视频编码器类型信息回调。
 * @return
 * - 0（kNERtcNoError）：方法调用成功。
 * - 其他：方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_video_encoder_qos_observer(struct nertc_engine* self, struct nertc_video_encoder_qos_observer* observer);

/**
 * @if English
 * Registers the pre decode observer object.
 * @note The observer must be set after the SDK is initialized and becomes invalid after the SDK is released.
 * @since V4.6.25
 * @param[in] observer  The object instance. If you pass in NULL, you cancel the registration.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 注册解码前媒体数据观测器。
 * - 通过此接口可以设置 \ref nertc::INERtcPreDecodeObserver::onFrame "onFrame" 回调监听，返回相关解码前媒体数据。
 * @since V4.6.29
 * @par 使用前提
 * 若您需要接收未解码的视频数据，建议先调用 \ref IRtcEngineEx::setParameters "setParameters" 接口关闭 SDK 的视频解码功能。
 * @par 调用时机
 * 请在引擎初始化之后调用此接口，且该方法在加入房间前后均可调用。
 * @par 业务场景
 * 适用于需要自行处理音、视频数据的解码与渲染的场景。
 * @note
 * 目前仅支持传输 OPUS 格式的音频数据和 H.264 格式的视频数据。
 * @par 参数说明
 * <table>
 *  <tr>
 *      <th>**参数名称**</th>
 *      <th>**类型**</th>
 *      <th>**描述**</th>
 *  </tr>
 *  <tr>
 *      <td>observer</td>
 *      <td>INERtcPreDecodeObserver *</td>
 *      <td>接口对象实例。可以传 NULL 表示取消注册。</td>
 *  </tr>
 * </table>
 * @par 示例代码
 * @code
 * auto ret = rtc_engine_->setPreDecodeObserver(observer); //observer为观测器实例地址
 * if (ret != nertc::kNERtcNoError) {
 * // 错误处理
 * }         logDebug(">>>setPreDecodeObserver [0x%x] successful", enable ? this : nullptr);
 * @endcode
 * @par 相关回调
 * \ref nertc::INERtcPreDecodeObserver::onFrame "onFrame"：返回相关解码前媒体数据，包括用户的 UID、媒体数据类型、数据长度等。
 * @return
 * - 0（OK）：方法调用成功。
 * - 其他：方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_pre_decode_observer(struct nertc_engine* self, struct nertc_pre_decode_frame_observer* observer);

/**
 * @if English
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
 * 启用说话者音量提示。
 * <br>该方法允许 SDK 定期向 App 反馈本地发流用户和瞬时音量最高的远端用户（最多 3
 * 位）的音量相关信息，即当前谁在说话以及说话者的音量。 <br>启用该方法后，只要房间内有发流用户，无论是否有人说话，SDK
 * 都会在加入房间后根据预设的时间间隔触发\ref IRtcEngineEventHandlerEx::onRemoteAudioVolumeIndication
 * "onRemoteAudioVolumeIndication"回调。
 * @param enable        是否启用说话者音量提示。
 * @param interval      指定音量提示的时间间隔，单位为毫秒。必须设置为 100 毫秒的整数倍值。
 * @param enable_vad      是否启用本地采集人声监测。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_enable_audio_volume_indication(struct nertc_engine* self, bool enable, uint64_t interval, bool enable_vad);

/**
 * @if English
 * Shares screens through specifying regions. Shares a certain screen or part of region of a screen. Users need to specify the
 * screen region they wants to share in the method. <br>When calling the method, you need to specify the screen region to be
 * shared, and share the overall frame of the screen or designated regions. <br>If you join a room and successfully call this
 * method to enable the substream, the onUserSubStreamVideoStart and setExcludeWindowList callback is remotely triggered.
 * @note
 * - The method applies to Windows only.
 * - The method enables video substreams.
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
NERTC_API int NERTC_CALL nertc_engine_start_screen_capture_by_screen_rect(struct nertc_engine* self,
                                                 const struct nertc_rectangle* screen_rect,
                                                 const struct nertc_rectangle* region_rect,
                                                 const struct nertc_screen_capture_parameters* capture_params);

/**
 * @if English
 * Enables screen sharing by specifying the ID of the screen. The content of screen sharing is sent by substreams.
 * <br>If you join a room and call this method to enable the substream, the onUserSubStreamVideoStart and
 onScreenCaptureStatus callback is remotely triggered.
 * @note
 * - The method applies to only macOS.
 * - The method enables video substreams.
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
NERTC_API int NERTC_CALL nertc_engine_start_screen_capture_by_display_id(struct nertc_engine* self,
                                                uint64_t display_id,
                                                const struct nertc_rectangle* region_rect,
                                                const struct nertc_screen_capture_parameters* capture_params);

/**
 * @if English
 * Enables screen sharing by specifying the ID of the window. The content of screen sharing is sent by substreams.
 * <br>If you join a room and call this method to enable the substream, the onUserSubStreamVideoStart and setExcludeWindowList
 * callback is remotely triggered.
 * @note
 * - The method applies to Windows only and macOS.
 * - The method enables video substreams.
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
NERTC_API int NERTC_CALL nertc_engine_start_screen_capture_by_window_id(struct nertc_engine* self,
                                               void* window_id,
                                               const struct nertc_rectangle* region_rect,
                                               const struct nertc_screen_capture_parameters* capture_params);


/**
 * @if English
 * When sharing a screen or window, updates the shared region.
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
 * @param  region_rect
 * 指定待共享的区域相对于整个窗口或屏幕的位置。如果设置的共享区域超出了边界，则只共享指定区域中，窗口或屏幕内的内容；如果宽或高为
 * 0，则共享整个窗口或屏幕。
 * @return
 * - 0: 方法调用成功。
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_update_screen_capture_region(struct nertc_engine* self, const struct nertc_rectangle* region_rect);

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
NERTC_API int NERTC_CALL nertc_engine_set_screen_capture_mouse_cursor(struct nertc_engine* self, bool capture_cursor);

/**
 * @if English
 * Stops screen sharing.
 * <br>If you use the method to disable the substream after joining a room, the onUserSubStreamVideoStop callback is remotely
 * triggered.
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
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_stop_screen_capture(struct nertc_engine* self);

/**
 * @if English
 * Pauses screen sharing.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 *
 * @endif
 * @if Chinese
 * 暂停屏幕共享。
 * - 暂停屏幕共享后，共享区域内会持续显示暂停前的最后一帧画面，直至通过 resumeScreenCapture 恢复屏幕共享。
 * - 在 Windows 平台中，远端会触发 onScreenCaptureStatus 回调。
 * @return
 * - 0: 方法调用成功
 * - 其他: 方法调用失败
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_pause_screen_capture(struct nertc_engine* self);

/**
 * @if English
 * Resumes screen sharing.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 恢复屏幕共享。
 * <br>在 Windows 平台中，远端会触发 onScreenCaptureStatus 回调。
 * @return
 * - 0: 方法调用成功
 * - 其他: 方法调用失败
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_resume_screen_capture(struct nertc_engine* self);

/**
 * @if English
 * Sets the window list that need to be blocked in capturing screens. The method can be dynamically called in the capturing.
 * @since V4.2.0
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
 * @since V4.2.0
 * @param  window_list      需要屏蔽的窗口 ID 列表。
 * @param  count            需屏蔽的窗口的数量。
 * @return
 * - 0: 方法调用成功
 * - 其他: 方法调用失败
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_exclude_window_list(struct nertc_engine* self, source_id_t* window_list, int count);
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
 *      <td>capture_params</td>
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
NERTC_API int NERTC_CALL nertc_engine_update_screen_capture_parameters(struct nertc_engine* self, const struct nertc_screen_capture_parameters* capture_params);

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
 * 请务必保证视频主流和辅流输入通道各最多只能有一种视频输入源，其中屏幕共享只能通过辅流通道开启，因此：
 * - 若您开启了辅流形式的屏幕共享，请使用主流通道输入外部视频源数据，即设置 type 参数为 kNERTCVideoStreamMain。
 * - 若您已调用 \ref nertc::IRtcEngine::enableLocalVideo(NERtcVideoStreamType type, bool enabled) "enableLocalVideo"方法开启本地主流视频采集，请勿再调用此接口创建主流形式的外部视频源输入，辅流通道同理。
 * @param[in] type          视频通道类型:
 * @param[in] enabled       是否外部视频源数据输入:
 * - true: 开启外部视频源数据输入；
 * - false: 关闭外部视频源数据输入 (默认)。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_external_video_source(struct nertc_engine* self, nertc_video_stream_type type, bool enabled);

/**
 * @if English
 * Pushes the external video frames.
 * <br>The method actively pushes the data of video frames that are encapsulated with the NERtcVideoFrame class to the SDK.
 * Make sure that you have already called setExternalVideoSource with a value of true before you call this method. Otherwise,
 * an error message is repeatedly prompted if you call the method.
 * @note The method enables the internal engine, which is invalid after you call \ref IRtcEngine::leaveChannel "leaveChannel".
 * @param[in] frame         The video frame data.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 推送辅流的外部视频帧。
 * <br>该方法主动将视频帧数据用 NERtcVideoFrame 类封装后传递给 SDK。 请确保在你调用本方法前已调用
 * setExternalVideoSource，并将参数设为 true，否则调用本方法后会一直报错。
 * @note 该方法设置内部引擎为启用状态，在 \ref IRtcEngine::leaveChannel "leaveChannel" 后不再有效。
 * @param[in] type          视频通道类型。
 * @param[in] frame         视频帧数据。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_push_external_video_frame(struct nertc_engine* self, nertc_video_stream_type type, struct nertc_video_frame* frame);

/**
 * @if English
 * Pushes the external video encoded frames.
 * <br>The method actively pushes the data of video encoded frames that are encapsulated with the NERtcVideoEncodedFrame class
 * to the SDK. Make sure that you have already called setExternalVideoSource with a value of true before you call this method.
 * Otherwise, an error message is repeatedly prompted if you call the method. <br>Make sure that you have already called
 * enableDualStreamMode with a value of false before you call this method. Otherwise, the peer may not receive video.
 * @note The method enables the internal engine, which is invalid after you call \ref IRtcEngine::leaveChannel "leaveChannel".
 * @since V4.6.25
 * @param[in] encoded_frame         The video encoded frame data.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 推送外部视频编码帧。
 * - 通过此接口可以实现通过主流或辅流视频通道推送外部视频编码后的数据。
 * @since V4.6.29
 * @par 使用前提
 * 该方法仅在设置 \ref IRtcEngineEx::setExternalVideoSource(NERtcVideoStreamType type, bool enabled) "setExternalVideoSource"
 * 接口的 enable 参数为 true 后调用有效。
 * @par 调用时机
 * 请在引擎初始化之后调用此接口，且该方法仅可在加入房间后调用。
 * @par 业务场景
 * 适用于需要自行处理视频数据的采集与编码的场景。
 * @note
 * - 目前仅支持传输 H.264 格式的视频数据。
 * - 该方法设置内部引擎为启用状态，在 \ref IRtcEngine::leaveChannel "leaveChannel" 后设置会重置为默认状态。
 * - 建议先调用 \ref IRtcEngineEx#enableDualStreamMode "enableDualStreamMode"}
 * 方法关闭视频大小流功能，否则远端可能无法正常接收下行流。
 * - 建议不要同时调用 \ref IRtcEngineEx::pushExternalVideoFrame "pushExternalVideoFrame" 方法。
 * - 外部视频源数据的输入通道、本地视频采集通道与外部视频编码帧数据的推送通道必须同为主流或者辅流通道，否则 SDK 会报错。
 * @par 参数说明
 * <table>
 *  <tr>
 *      <th>**参数名称**</th>
 *      <th>**类型**</th>
 *      <th>**描述**</th>
 *  </tr>
 *  <tr>
 *      <td>encoded_frame</td>
 *      <td>NERtcVideoEncodedFrame*</td>
 *      <td>编码后的视频帧数据。</td>
 *  </tr>
 *  <tr>
 *      <td>type</td>
 *      <td> \ref nertc::NERtcVideoStreamType "NERtcVideoStreamType"</td>
 *      <td>视频通道类型：<ul><li>kNERTCVideoStreamMain：主流。<li>kNERTCVideoStreamSub：辅流。</td>
 *  </tr>
 * </table>
 * @par 示例代码
 * @code
 * nertc::NERtcVideoEncodedFrame frame;
 * memset(&frame, 0, sizeof(frame));
 * frame.codec_type = nertc::kNERtcVideoCodecTypeH264; // H264类型，详见NERtcVideoCodecType
 * frame.frame_type = nertc::kNERtcNalFrameTypeIDR; // IDR帧，详见NERtcNalFrameType
 * frame.nal_count = nalCnt; // nal个数
 * frame.nal_length = nalLen; // 每个nal对应的长度数组
 * frame.nal_data = data; // nal数据
 * frame.timestamp_us = TimeMicros(); // 机器时间，us
 * frame.width = width; // 视频宽
 * frame.height = height; // 视频高
 * auto ret = rtc_engine_->pushExternalVideoEncodedFrame(&frame);
 * if (ret != nertc::kNERtcNoError) {
 * // 错误处理
 * }
 * @endcode
 * @par 相关接口
 * 可以调用 \ref IRtcEngineEx::setVideoEncoderQosObserver "setVideoEncoderQosObserver" 接口设置视频编码 QoS
 * 信息监听器，通过回调的数据信息调整编码策略。
 * @return
 * - 0（kNERtcNoError）：方法调用成功。
 * - 其他：方法调用失败。
 *         - 11403（kNERtcErrInvalid）：无效操作，比如未开启外部视频输入。
 *         - 30003（kNERtcErrInvalidParam）：参数错误，比如传入对象为空。
 *         - 30005（kNERtcErrInvalidState）：状态错误，比如引擎未初始化或视频未开启。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_push_external_video_encoded_frame(struct nertc_engine* self,
                                                                        nertc_video_stream_type type,
                                                                        struct nertc_video_encoded_frame* encoded_frame);

/**
 * @if English
 * Enables or disables the external audio stream source.
 * <br>After you call the method, the setting becomes invalid if you choose audio input device or a sudden restart occurs.
 * After the method is called, you can call pushExternalAudioFrame to send the pulse-code modulation (PCM) data.
 * @note
 * - You can call this method before joining a room.
 * - The method enables the internal engine. After enabled, the virtual component works instead of the physical microphones.
 * The setting remains unchanged after the leaveChannel method is called. If you want to disable the feature, you must disable
 * the setting before next call starts.
 * - After you enable the external audio data input, some functionalities of the speakerphone supported by the SDK are
 * replaced by the external audio source. Settings that are applied to the microphones become invalid or do not take effect in
 * calls. For example, you can hear the external data input when you use loopback for testing.
 * @param[in] enabled       Specifies whether to input external data.
 * - true: Enables external data input.
 * - false: Disables the external data input(default).
 * @param[in] sample_rate   The sample rate of data. You need to input following data in the same sample rate.  Note: If you
 * call the method to disable the functionality, you can pass in a random valid value. In this case, the setting does not take
 * effect.
 * @param[in] channels      The number of channels. You need to input following data in the same number of channels. Note: If
 * you call the method to disable the functionality, you can pass in a random valid value. In this case, the setting does not
 * take effect. Valid values:
 * - 1: Mono sound.
 * - 2: Stereo sound.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 开启或关闭外部音频源数据输入。
 * <br>当该方法调用成功后，音频输入设备选择和异常重启会失效。调用成功后可以使用 pushExternalAudioFrame 接口发送音频 PCM 数据。
 * @note
 * - 请在加入房间前调用该方法。
 * -
 * 该方法设置内部引擎为启用状态，启动时将用虚拟设备代替麦克风工作，在leaveChannel后仍然有效。如果需要关闭该功能，需要在下次通话前调用接口关闭外部音频数据输入功能。
 * - 启用外部音频数据输入功能后，SDK 内部实现部分麦克风由外部输入数据代替，麦克风相关的设置会失败或不在通话中生效。例如进行
 * loopback 检测时，会听到输入的外部数据。
 * @param[in] enabled       是否外部数据输入:
 * - true: 开启外部数据输入；
 * - false: 关闭外部数据输入 (默认)。
 * @param[in] sample_rate   数据采样率，后续数据传入需要按该格式传入。
 * 注意：调用接口关闭功能时可传入任意合法值，此时设置不会生效。
 * @param[in] channels 数据声道数，后续数据传入需要按该格式传入。注意：调用接口关闭功能时可传入任意合法值，此时设置不会生效。
 * 可设置为：
 * - 1：单声道。
 *  2：双声道。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_external_audio_source(struct nertc_engine* self, nertc_audio_stream_type type, bool enabled, int sample_rate, int channels);

/**
 * @if English
 * Pushes the external audio data input.
 * <br>Pushes the audio frame data captured from the external audio source to the internal audio engine. If you enable the
 * external audio data source by calling setExternalAudioSource, you can use pushExternalAudioFrame to send audio PCM data.
 * @note
 * - This method can be called only if a user joins a room.
 * - We recommend that you set the duration of data frames to match a cycle of 10 ms.
 * - External input data frame consists of the data duration and call duration.
 * - The method becomes invalid if the audio input device is turned off. For example, disable local audio, end calls, and shut
 * off the microphone test before calls.
 * @param[in] frame         The data of frame cannot exceed 7680 bytes in length.
 * - External input data frame consists of the data duration and call duration.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 推送外部音频数据输入。
 * <br>将外部音频数据帧推送给内部引擎。 通过 setExternalAudioSource 启用外部音频数据输入功能成功后，可以使用
 * pushExternalAudioFrame 接口发送音频 PCM 数据。
 * @note
 * - 该方法需要在加入房间后调用。
 * - 数据帧时长建议匹配 10ms 周期。
 * - 外部输入数据帧，数据时长和调用周期时长一致。
 * - 该方法在音频输入设备关闭后不再生效。例如关闭本地音频、通话结束、通话前麦克风设备测试关闭等情况下，该设置不再生效。
 * @param[in] frame         帧数据，数据长度不能超过7680:
 * - 外部输入数据帧，数据时长和调用周期时长一致。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_push_external_audio_frame(struct nertc_engine* self, nertc_audio_stream_type type, struct nertc_audio_frame* frame);

/**
 * @if English
 * Pushes the external audio encoded data input.
 * <br>Pushes the audio encoded frame data from the external to the internal audio engine. If you enable the external audio data
 * source by calling setExternalAudioSource, you can use pushExternalAudioEncodedFrame to send audio encoded data.
 * @note
 * - This method can be called only if a user joins a room.
 * - The method becomes invalid if the audio input device is turned off. For example, disable local audio, end calls.
 * @since V4.6.25
 * @param[in] encoded_frame  External input enocde data frame.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 推送外部音频主流编码帧。
 * - 通过此接口可以实现通过主流音频通道推送外部音频编码后的数据。
 * @since V4.6.29
 * @par 使用前提
 * 该方法仅在设置 \ref nertc::IRtcEngineEx::setExternalAudioSource "setExternalAudioSource" 接口的 enabled 参数为 true
 * 后调用有效。
 * @par 调用时机
 * 请在引擎初始化之后调用此接口，且该方法仅可在加入房间后调用。
 * @par 业务场景
 * 适用于需要自行处理音频数据的采集与编码的场景。
 * @note
 * - 目前仅支持传输 OPUS 格式的音频数据。
 * - 建议不要同时调用 \ref nertc::IRtcEngineEx::pushExternalAudioFrame "pushExternalAudioFrame" 方法。
 * - 该方法在音频输入设备关闭后，例如在关闭本地音频、通话结束、通话前麦克风设备测试关闭等情况下，设置会恢复至默认。
 * @par 参数说明
 * <table>
 *  <tr>
 *      <th>**参数名称**</th>
 *      <th>**类型**</th>
 *      <th>**描述**</th>
 *  </tr>
 *  <tr>
 *      <td>encoded_frame</td>
 *      <td>NERtcAudioEncodedFrame*</td>
 *      <td>编码后的音频帧数据。</td>
 *  </tr>
 * </table>
 * @par 示例代码
 * @code
 * int timediff = 20; // opus need 20ms
 * uint64_t encoded_audio_ts = 0;
 * nertc::NERtcAudioEncodedFrame audioFrame;
 * memset(&audioFrame, 0, sizeof(audioFrame));
 * audioFrame.sample_rate = sample_rate; //采样率
 * audioFrame.channels = channels; // 声道数
 * audioFrame.samples_per_channel = sample_rate / 1000 * timediff;  //每声道采样数
 * audioFrame.payload_type = nertc::kNERtcAudioPayloadTypeOPUS; // OPUS, 参考NERtcAudioPayloadType
 * audioFrame.encoded_len = len; // 编码后数据长度
 * audioFrame.data = data; // 编码后数据
 * audioFrame.timestamp_us = TimeMicros(); // 机器时间，us
 * audioFrame.encoded_timestamp = encoded_audio_ts;  // 编码时间, 单位为样本数
 * encoded_audio_ts += audioFrame.samples_per_channel;
 * auto ret = rtc_engine_->pushExternalAudioEncodedFrame(&audioFrame);
 * if (ret != nertc::kNERtcNoError) {
 * // 错误处理
 * }
 * @endcode
 * @return
 * - 0（kNERtcNoError）：方法调用成功。
 * - 其他：方法调用失败。
 *         - 30001（kNERtcErrFatal）：未开启外部音频输入。
 *         - 30003（kNERtcErrInvalidParam）：参数错误，比如传入对象为空。
 *         - 30005（kNERtcErrInvalidState）：状态错误，比如尚未加入房间或未开启本地音频。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_push_external_audio_encoded_frame(struct nertc_engine* self, nertc_audio_stream_type type, struct nertc_audio_encoded_frame* encoded_frame);

/**
 * @if English
 * Sets external audio rendering.
 * <br>The method is suitable for scenarios that require personalized audio rendering. By default, the setting is disabled. If
 * you choose an audio playback device or a sudden restart occurs, the setting becomes invalid. After you call the method, you
 * can use pullExternalAudioFrame to get audio PCM data.
 * @note
 * - You can call this method before joining a room.
 * - The method enables the internal engine. The virtual component works instead of the physical speaker. The setting remains
 * valid after you call the leaveChannel method. If you want to disable the functionality, you must disable the functionality
 * before the next call starts.
 * - After you enable the external audio rendering, some functionalities of the speakerphone supported by the SDK are replaced
 * by the external audio source. Settings that are applied to the speakerphone become invalid or do not take effect in calls.
 * For example, external rendering is required to play the external audio when you use loopback for testing.
 * @param[in] enabled       Specifies whether to output external data.
 * - true: Enables external data rendering.
 * - false: Disables the external data rendering (default).
 * @param[in] sample_rate    The sample rate of data. You need to input following data in the same sample rate.
 * Note: If you call the method to disable the functionality, you can pass in a random valid value. In this case, the setting
 * does not take effect.
 * @param[in] channels       The number of data channels. You need to return following data in the same number of channels.
 * Note: If you call the method to disable the functionality, you can pass in a random valid value. In this case, the setting
 * does not take effect. Valid values:
 * - 1: Mono sound.
 * - 2: Stereo sound.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置外部音频渲染。
 * <br>该方法适用于需要自行渲染音频的场景。默认为关闭状态。当该方法调用成功后，音频播放设备选择和异常重启失效。
 * 调用成功后可以使用 pullExternalAudioFrame 接口获取音频 PCM 数据。
 * @note
 * - 请在加入房间前调用该方法。
 * -
 * 该方法设置内部引擎为启用状态，启动时将用虚拟设备代替扬声器工作，在leaveChannel后仍然有效。如果需要关闭该功能，需要在下次通话前调用接口关闭外部音频数据渲染功能。
 * - 启用外部音频渲染功能后，SDK 内部实现部分扬声器由外部输入数据代替，扬声器相关的设置会失败或不在通话中生效。例如进行
 * loopback 检测时，需要由外部渲染播放。
 * @param[in] enabled           是否外部数据输出:
 * - true: 开启外部数据渲染；
 * - false: 关闭外部数据渲染 (默认)。
 * @param[in] sample_rate       数据采样率，后续数据按该格式返回。
 * 注意：调用接口关闭功能时可传入任意合法值，此时设置不会生效。
 * @param[in] channels          数据声道数，后续数据按该格式返回。
 * 注意：调用接口关闭功能时可传入任意合法值，此时设置不会生效。
 * 可设置为：
 * - 1：单声道。
 * - 2：双声道。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_external_audio_render(struct nertc_engine* self, bool enabled, int sample_rate, int channels);

/**
 * @if English
 * Pulls the external audio data.
 * <br>The method pulls the audio data from the internal audio engine. After you enable the external audio data rendering
 * functionality by calling setExternalAudioRender, you can use pullExternalAudioFrame to get the audio PCM data.
 * @note
 * - This method can be called only if a user joins a room.
 * - We recommend that you set the duration of data frames to match a cycle of 10 ms.
 * - The method becomes invalid if the audio rendering device is turned off. In this case, no data is returned. For example,
 * calls end, and the speakerphone is shut off before calls.
 * @param[out] data         Data pointer. The SDK internally copies data into data.
 * @param[in] len           The size of the audio data that are pulled. Unit: bytes.
 * - We recommend that the duration of the audio data at least last 10 ms, and the data size cannot exceed 7,680 bytes.
 * - Formula: len = sampleRate/1000 × 2 × channels × duration of the audio data in milliseconds.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 拉取外部音频数据。
 * <br>该方法将从内部引擎拉取音频数据。 通过 setExternalAudioRender 启用外部音频数据渲染功能成功后，可以使用
 * pullExternalAudioFrame 接口获取音频 PCM 数据。
 * @note
 * - 该方法需要在加入房间后调用。
 * - 数据帧时长建议匹配 10ms 周期。
 * - 该方法在音频渲染设备关闭后不再生效，此时会返回空数据。例如通话结束、通话前扬声器设备测试关闭等情况下，该设置不再生效。
 * @param[out] data         数据指针，SDK内部会将数据拷贝到data中。
 * @param[in] len           待拉取音频数据的字节数，单位为 byte。
 * - 建议音频数据的时长至少为 10 毫秒，数据长度不能超过 7680字节。
 * - 计算公式为： len = sampleRate/1000 × 2 × channels × 音频数据时长（毫秒）。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_pull_external_audio_frame(struct nertc_engine* self, void* data, int length);

/**
 * @if English
 * Query the SDK version number.
 * - You can call this method before or after you join a room.
 * @param[out] build        The compilation number.
 * @return The version of the current SDK, whose format is string such as 1.0.0.
 * @endif
 * @if Chinese
 * 查询 SDK 版本号。
 * 该方法在加入房间前后都能调用。
 * @return 当前的 SDK 版本号，格式为字符串，如1.0.0.
 * @endif
 */
NERTC_API const char* NERTC_CALL nertc_engine_get_version(struct nertc_engine* self);

/**
 * @if English
 * Check the error description of specified error codes.
 * @note The method is currently invalid. Returns the value of empty only. Please check returned error codes and specific
 * error descriptions in the \ref IRtcEngineEventHandler::onError "onError" .
 * @param[in] error_code        #NERtcErrorCode.
 * @return Detailed descriptions of error codes.
 * @endif
 * @if Chinese
 * 查看指定错误码的错误描述。
 * @note 目前该方法无效，只返回空值。请在 \ref IRtcEngineEventHandler::onError "onError" 中查看返回的错误码及具体的错误描述。
 * @param[in] error_code        #NERtcErrorCode 。
 * @return 详细错误码描述
 * @endif
 */
NERTC_API const char* NERTC_CALL nertc_engine_get_error_description(struct nertc_engine* self, int error_code);

/**
 * @if English
 * Uploads the SDK information.
 * <br>You can call the method only after joining a room.
 * <br>The data that is published contains the log file and the audio dump file.
 * @return void
 * @endif
 * @if Chinese
 * 上传 SDK 信息。
 * <br>只能在加入房间后调用。
 * <br>上传的信息包括 log 和 Audio dump 等文件。
 * @return void
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_upload_sdk_info(struct nertc_engine* self);

/**
 * @if English
 * After the method is successfully called, the current user can receive the notification about the status of the live stream.
 * @note
 * - The method is applicable to only live streaming.
 * - You can call the method in a room. The method is valid in calls.
 * - Only one address for the relayed stream is added in each call. You need to call the method for multiple times if you want
 * to push many streams. An RTC room with the same channelid can create three different streaming tasks.
 * - After the method is successfully called, the current user will receive related-status notifications of the live stream.
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
 * @param[in] info 直播任务信息。详细信息请参考 \ref NERtcLiveStreamTaskInfo "NERtcLiveStreamTaskInfo"
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_add_live_stream_task(struct nertc_engine* self, const struct nertc_live_stream_task_info* info);

/**
 * @if English
 * Updates and modifies a push task in a room.
 * @note
 * - The method is applicable to only live streaming.
 * - You can call the method in a room. The method is valid in calls.
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
 * @param[in] info 直播任务信息。详细信息请参考 \ref NERtcLiveStreamTaskInfo "NERtcLiveStreamTaskInfo"
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_update_live_stream_task(struct nertc_engine* self, const struct nertc_live_stream_task_info* info);

/**
 * @if English
 * Deletes a push task.
 * @note
 * - The method is applicable to only live streaming.
 * - You can call the method in a room. The method is valid in calls.
 * - When calls stop and all members in the room leave the room, the SDK automatically deletes the streaming task. If some
 * users are still in the room, users who create the streaming task need to delete the streaming task.
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
 * @param[in] task_id  直播任务 ID。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_remove_live_stream_task(struct nertc_engine* self, const char* task_id);

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
 * the next 5 frames at the slowest pace.
 * @note
 * - The SEI data is transmitted together with the video stream. Frame loss may occur in poor network connection. The SEI data
 * will also get lost. We recommend that you send the data many times within the transmission frequency limits. In this way,
 * the receiver can get the data.
 * - By default, the SEI is transmitted by using the mainstream channel.
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
 * @note
 * - SEI 数据跟随视频帧发送，由于在弱网环境下可能丢帧，SEI
 * 数据也可能随之丢失，所以建议在发送频率限制之内多次发送，保证接收端收到的概率。
 * - 调用本接口时，默认使用主流通道发送 SEI。
 * @param data      自定义 SEI 数据。
 * @param length    自定义 SEI 数据长度，最大不超过 4096 字节。
 * @param type      发送 SEI 时，使用的流通道类型。详细信息请参考 #NERtcVideoStreamType 。
 * @return 操作返回值，成功则返回 0
 * - 成功:  成功进入待发送队列，会在最近的视频帧之后发送该数据
 * - 失败:  数据被限制发送，可能发送的频率太高，队列已经满了，或者数据大小超过最大值 4k
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_send_sei_msg(struct nertc_engine* self, const unsigned char* data, int length, nertc_video_stream_type type);

/**
 * @if English
 * Set the video watermark, the watermark will take effect in the local preview and sending process.
 * @param enabled add or remove watermark
 * @param type   The type of video streams. You can set the value to mainstream or substream. For more information, see
 #NERtcVideoStreamType.。
 * @param config The configuration of the watermark for the canvas. You can set text watermark, image watermark, and timestamp
 watermark. A value of null is set to remove the watermark.
 * For more information, see \ref NERtcVideoWatermarkConfig.
 * @return
 - 0: Success.
 - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置视频水印，水印在本地预览及发送过程中均生效。
 * @note 设置水印后，建议关注水印状态回调 \ref nertc::IRtcEngineEventHandlerEx::onLocalVideoWatermarkState
 "onLocalVideoWatermarkState"。
 * @since V4.6.10
 * @param enabled 添加或删除水印。
 * - true：添加水印。
 * - false：删除水印。
 * @param type   视频流类型。支持设置为主流或辅流。详细信息请参考 #NERtcVideoStreamType 。
 * @param config 视频水印配置。支持设置文字水印、图片水印和时间戳水印。详细信息请参考 \ref nertc::NERtcVideoWatermarkConfig
 "NERtcVideoWatermarkConfig" 。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_local_video_watermark_configs(struct nertc_engine* self,
                                                                        bool enabled,
                                                                        nertc_video_stream_type type,
                                                                        const nertc_video_watermark_config* config);

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
 * @param stream_type       截图的视频流类型。支持设置为主流或辅流。详细信息请参考 #NERtcVideoStreamType 。
 * @param callback          截图回调。详细信息请参考 \ref NERtcTakeSnapshotCallback 。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_take_local_snapshot(struct nertc_engine* self, nertc_video_stream_type stream_type, on_take_snapshot_callback callback);

 /**
  * @if English
  * Takes a snapshot of a remote video.
  * <br>You can call takeRemoteSnapshot to specify the uid of video screen of remote mainstreams and substreams, and returns
  * screenshot data of \ref NERtcTakeSnapshotCallback "NERtcTakeSnapshotCallback::onTakeSnapshotResult" callback.
  * @note
  * - You need to call takeRemoteSnapshot after receiving callbacks of onUserVideoStart and onUserSubStreamVideoStart.
  * - You can set text, timestamp, and image watermarks at the same time. If different types of watermarks overlap, the layers
  * override previous layers following image, text, and timestamp.
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
  * @param uid           远端用户 ID。
  * @param stream_type   截图的视频流类型。支持设置为主流或辅流。详细信息请参考 #NERtcVideoStreamType 。
  * @param callback      截图回调。详细信息请参考 \ref NERtcTakeSnapshotCallback 。
  * @return
  * - 0: 方法调用成功；
  * - 其他: 方法调用失败。
  * @endif
  */
NERTC_API int NERTC_CALL nertc_engine_take_remote_snapshot(struct nertc_engine* self, nertc_uid_t uid, nertc_video_stream_type stream_type, on_take_snapshot_callback callback);

  /**
   * @if English
   * Starts an audio recording on a client.
   * <br>After calling the method, the client records the audio streams that are mixed by all users, and stores the streams in a
  local file. The onAudioRecording() callback is triggered when the recording starts or ends.
   * <br>If you specify a type of audio quality, the recording file is saved in different formats.
   * - WAV file is large with high quality.
   * - AAC file is small with low quality.
   * @note
   * - You must call the method after calling the method after joining a room.
   * - A client can only run a recording task. If you repeatedly call the startAudioRecording method, the current recording task
  stops and a new recording task starts.
   * - If the current user leaves the room, the audio recording automatically stops. You can call the stopAudioRecording method
  to manually stop recording during calls.
   * @param file_path The absolute path where the recording file is saved. The file name and format must be accurate. For
  example, sdcard/xxx/audio.aac.
                      - Make sure that the specified path is valid and has the write permission.
                      - Only WAV or AAC files are supported.
   * @param sample_rate The audio sample rate (Hz). Valid values: 16000, 32000, 44100, and 48000. The default value is 32000.
   * @param quality     The audio quality. The parameter is valid only the audio file is in AAC format. For more information,
  see NERtcAudioRecordingQuality.
   *  @return
   *  - 0: Success.
   *  - Other values: Failure.
   * @endif
   * @if Chinese
   * 开始客户端录音。
   * <br>调用该方法后，客户端会录制房间内所有用户混音后的音频流，并将其保存在本地一个录音文件中。录制开始或结束时，自动触发
  onAudioRecording() 回调。
   * <br>指定的录音音质不同，录音文件会保存为不同格式：
   * - WAV：音质保真度高，文件大。
   * - AAC：音质保真度低，文件小。
   * @note
   * - 请在加入房间后调用此方法。
   * - 客户端只能同时运行一个录音任务，正在录音时，如果重复调用
  startAudioRecording，会结束当前录制任务，并重新开始新的录音任务。
   * - 当前用户离开房间时，自动停止录音。您也可以在通话中随时调用 stopAudioRecording 手动停止录音。
   * @param file_path 录音文件在本地保存的绝对路径，需要精确到文件名及格式。例如：sdcard/xxx/audio.aac。
                      - 请确保指定的路径存在并且可写。
                      - 目前仅支持 WAV 或 AAC 文件格式。
   * @param sample_rate 录音采样率（Hz），可以设为 16000、32000（默认）、44100 或 48000。
   * @param quality   录音音质，只在 AAC 格式下有效。详细说明请参考 NERtcAudioRecordingQuality。
   * @return
   * - 0: 方法调用成功；
   * - 其他: 方法调用失败。
  * @endif
  */
  NERTC_API int NERTC_CALL nertc_engine_start_audio_recording(struct nertc_engine* self, const char* file_path, int32_t sample_rate, nertc_audio_recording_quality quality);
  /**
   * @if English
   * Starts an audio recording from a client.
   * <br>The method records the mixing audio from all room members in the room, and store the recording file locally. The
   * onAudioRecording() callback is triggered when the recording starts or ends. <br>If you specify a type of audio quality, the
   * recording file is saved in different formats.
   * - A WAV file is large with high quality
   * - An AAC file is small with low quality.
   * @note
   * - You must call the method after you call joinChannel.
   * - A client can only run a recording task. If you repeatedly call the startAudioRecordingWithConfig method, the current
   * recording task stops and a new recording task starts.
   * - If the current user leaves the room, audio recording automatically stops. You can call the stopAudioRecording method to
   * manually stop recording during calls.
   * @param filePath The file path where the recording file is stored. The file name and format are required. For example,
   * sdcard/xxx/audio.aac.
   *                   - Make sure that the path is valid and has the write permissions.
   *                   - Only WAV or AAC files are supported.
   * @param sampleRate The recording sample rate. Valid values: 16000, 32000, 44100, and 48000. The default value is 32000.
   * @param quality The audio quality. The parameter is valid only the recording file is in AAC format. For more information,
   * see {@link NERtcAudioRecordingQuality}.
   * @param position   The recording object. For more information, see {@link NERtcAudioRecordingPosition}。
   * @param cycleTime  The maximum number of seconds for loop caching. You can set the value to 0, 10, 60, 360, and 900. The
   * default value is 0. The write operation runs in real time.
   * @return
   * - 0: success
   * - Others: failure
   * @endif
   * @if Chinese
   * 开始客户端录音。
   * 调用该方法后，客户端会录制房间内所有用户混音后的音频流，并将其保存在本地一个录音文件中。录制开始或结束时，自动触发
   * onAudioRecording() 回调。 指定的录音音质不同，录音文件会保存为不同格式：
   * - WAV：音质保真度高，文件大。
   * - AAC：音质保真度低，文件小。
   * @note
   * - 请在加入房间后调用此方法。
   * - 客户端只能同时运行一个录音任务，正在录音时，如果重复调用
   * startAudioRecordingWithConfig，会结束当前录制任务，并重新开始新的录音任务。
   * - 当前用户离开房间时，自动停止录音。您也可以在通话中随时调用 stopAudioRecording 手动停止录音。
   * @since V4.6.0
   * @param filePath   录音文件在本地保存的绝对路径，需要精确到文件名及格式。例如：sdcard/xxx/audio.aac。
   *                   - 请确保指定的路径存在并且可写。
   *                   - 目前仅支持 WAV 或 AAC 文件格式。
   * @param sampleRate 录音采样率（Hz），可以设为 16000、32000（默认）、44100 或 48000。
   * @param quality    录音音质，只在 AAC 格式下有效。详细信息请参考 \ref nertc::NERtcAudioRecordingQuality
   * "NERtcAudioRecordingQuality" 。
   * @param position   录音对象。详细信息请参考 \ref nertc::NERtcAudioRecordingPosition "NERtcAudioRecordingPosition"。
   * @param cycleTime  循环缓存的最大时长跨度。该参数单位为秒，可以设为 0、10、60、360、900，默认值为 0，即实时写文件。
   * @return
   * - 0：方法调用成功。
   * - 其他：方法调用失败。
   * @endif
   */
  NERTC_API int NERTC_CALL nertc_engine_start_audio_recording_with_config(struct nertc_engine* self, const struct nertc_audio_recording_configuration* config);

  /**
 * @if English
 * Stops the audio recording on the client.
 * <br>If the local client leaves the room, audio recording automatically stops. You can call the stopAudioRecording method to
 * manually stop recording during calls at any time.
 * @note You must call this method before you call leaveChannel.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 停止客户端录音。
 * <br>本端离开房间时自动停止录音，您也可以在通话中随时调用 stopAudioRecording 手动停止录音。
 * @note 该接口需要在 leaveChannel 之前调用。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_stop_audio_recording(struct nertc_engine* self);

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
NERTC_API int NERTC_CALL nertc_engine_adjust_recording_signal_volume(struct nertc_engine* self, int volume);

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
NERTC_API int NERTC_CALL nertc_engine_adjust_playback_signal_volume(struct nertc_engine* self, int volume);


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
 * @param uid    远端用户 ID。
 * @param volume 播放音量，取值范围为 [0,100]。
                - 0：静音。
                - 100：原始音量。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_adjust_user_playback_signal_volume(struct nertc_engine* self, nertc_uid_t uid, int volume);

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
NERTC_API int NERTC_CALL nertc_engine_adjust_channel_playback_signal_volume(struct nertc_engine* self, uint32_t volume);

/**
 * @if English
 * Starts to relay media streams across rooms.
 * - The method can invite co-hosts across rooms. Media streams from up to four rooms can be relayed. A room can receive
 * multiple relayed media streams.
 * - After you call this method, the SDK triggers `onMediaRelayStateChange` and `onMediaRelayEvent`. The return reports the
 * status and events about the current relayed media streams across rooms.
 * @note - You can call this method after joining a room. Before you call the method, you must set the destination room in the
 * `NERtcChannelMediaRelayConfiguration` parameter in `dest_infos`.
 * - The method is applicable only to the host in live streaming.
 * - If you want to call the method again, you must first call the `stopChannelMediaRelay` method to exit the current relaying
 * status.
 * - If you succeed in relaying the media stream across rooms, and want to change the destination room, for example, add or
 * remove the destination room, you can call `updateChannelMediaRelay` to update the information about the destination room.
 * @since V4.3.0
 * @param config specifies the configuration for the media stream relay across rooms. For more information, see {@link
 * NERtcMediaRelayParam.ChannelMediaRelayConfiguration}。
 * @return {@code 0} A value of 0 returned indicates that the method call is successful. Otherwise, the method call fails.
 * @endif
 * @if Chinese
 * 开始跨房间媒体流转发。
 * - 该方法可用于实现跨房间连麦等场景。支持同时转发到 4 个房间，同一个房间可以有多个转发进来的媒体流。
 * - 成功调用该方法后，SDK 会触发 `onMediaRelayStateChange` 和 `onMediaRelayEvent`
 * 回调，并在回调中报告当前的跨房间媒体流转发状态和事件。
 * @note
 * - 请在成功加入房间后调用该方法。调用此方法前需要通过 `NERtcChannelMediaRelayConfiguration` 中的 `dest_infos` 设置目标房间。
 * - 该方法仅对直播场景下的主播角色有效。
 * - 成功调用该方法后，若您想再次调用该方法，必须先调用 `stopChannelMediaRelay` 方法退出当前的转发状态。
 * - 成功开始跨房间转发媒体流后，如果您需要修改目标房间，例如添加或删减目标房间等，可以调用方法 `updateChannelMediaRelay`
 * 更新目标房间信息。
 * @since V4.3.0
 * @param config 跨房间媒体流转发参数配置信息。
 * @return 成功返回0，其他则失败
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_start_channel_media_relay(struct nertc_engine* self, const struct nertc_channel_media_relay_config* config);

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
 * @since V4.3.0
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
 * @since V4.3.0
 * @param config 目标房间配置信息
 * @return 成功返回0，其他则失败
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_update_channel_media_relay(struct nertc_engine* self, const struct nertc_channel_media_relay_config* config);

/**
 * @if English
 * Stops relaying media streams.
 * <br>If the host leaves the room, media stream replay across rooms automatically stops. You can also call
 * stopChannelMediaRelay. In this case, the host exits all destination rooms.
 * - If you call this method, the SDK triggers the `onMediaRelayStateChange` callback. If `NERtcChannelMediaRelayStateIdle` is
 * returned, the media stream relay stops.
 * - If the method call failed, the SDK triggers the `onMediaRelayStateChange` callback that returns the status code
 * `NERtcChannelMediaRelayStateFailure`.
 * @since V4.3.0
 * @return A value of 0 returned indicates that the method call is successful. Otherwise, the method call fails.
 * @endif
 * @if Chinese
 * 停止跨房间媒体流转发。
 * <br>主播离开房间时，跨房间媒体流转发自动停止，您也可以在需要的时候随时调用 `stopChannelMediaRelay`
 * 方法，此时主播会退出所有目标房间。
 * - 成功调用该方法后，SDK 会触发 `onMediaRelayStateChange` 回调。如果报告
 * `NERtcChannelMediaRelayStateIdle`，则表示已停止转发媒体流。
 * - 如果该方法调用不成功，SDK 会触发 `onMediaRelayStateChange` 回调，并报告状态码 `NERtcChannelMediaRelayStateFailure`。
 * @since V4.3.0
 * @return 成功返回0，其他则失败
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_stop_channel_media_relay(struct nertc_engine* self);

/**
 * @if English
 * Sets the fallback option for the published local video stream based on the network conditions.
 * <br>The quality of the published local audio and video streams is degraded with poor quality network connections. After
 * calling this method and setting the option to #kNERtcStreamFallbackAudioOnly:
 * - With unreliable upstream network connections and the quality of audio and video streams is downgraded, the SDK
 * automatically disables video stream or stops receiving video streams. In this way, the communication quality is guaranteed.
 * - The SDK monitors the network performance and recover audio and video streams if the network quality improves.
 * - If the locally published audio and video stream falls back to audio stream, or recovers to audio and video stream, the
 * SDK triggers the onLocalPublishFallbackToAudioOnly callback.
 * @note You must call the method before you call joinChannel.
 * @since V4.3.0
 * @param option The fallback option of publishing audio and video streams. The fallback kNERtcStreamFallbackAudioOnly is
 * disabled by default. For more information, see nertc::NERTCStreamFallbackOption .
 * @return {@code 0} A value of 0 returned indicates that the method call is successful. Otherwise, the method call fails.
 * @endif
 * @if Chinese
 * 设置弱网条件下发布的音视频流回退选项。
 * <br>在网络不理想的环境下，发布的音视频质量都会下降。使用该接口并将 option 设置为 #kNERtcStreamFallbackAudioOnly 后：
 * - SDK 会在上行弱网且音视频质量严重受影响时，自动关断视频流，尽量保证音频质量。
 * - 同时 SDK 会持续监控网络质量，并在网络质量改善时恢复音视频流。
 * - 当本地发布的音视频流回退为音频流时，或由音频流恢复为音视频流时，SDK 会触发本地发布的媒体流已回退为音频流
 * onLocalPublishFallbackToAudioOnly 回调。
 * @note 请在加入房间（joinChannel）前调用此方法。
 * @since V4.3.0
 * @param option 发布音视频流的回退选项，默认为不开启回退 kNERtcStreamFallbackAudioOnly。详细信息请参考
 * nertc::NERTCStreamFallbackOption 。
 * @return {@code 0} 方法调用成功，其他调用失败
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_local_publish_fallback_option(struct nertc_engine* self, nertc_stream_fallback_option option);

/**
 * @if English
 * Sets the fallback option for the subscribed remote audio and video stream with poor network connections.
 * <br>The quality of the subscribed audio and video streams is degraded with unreliable network connections. You can use the
 * interface to set the option as #kNERtcStreamFallbackVideoStreamLow or #kNERtcStreamFallbackAudioOnly.
 * - In unreliable downstream network connections, the SDK switches to receive a low-quality video stream or stops receiving
 * video streams. In this way, the communication quality is maintained or improved.
 * - The SDK monitors the network quality and resumes the video stream when the network condition improves.
 * - If the subscribed remote video stream falls back to audio only, or the audio-only stream switches back to the video
 * stream, the SDK triggers the onRemoteSubscribeFallbackToAudioOnly callback.
 * @note You must call the method before you call joinChannel.
 * @since V4.3.0
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
 * onRemoteSubscribeFallbackToAudioOnly 回调。
 * @note 请在加入房间（joinChannel）前调用此方法。
 * @since V4.3.0
 * @param option    订阅音视频流的回退选项，默认为弱网时回退到视频小流 kNERtcStreamFallbackVideoStreamLow。详细信息请参考
 * nertc::NERTCStreamFallbackOption 。
 * @return {@code 0} 方法调用成功，其他调用失败
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_remote_subscribe_fallback_option(struct nertc_engine* self, nertc_stream_fallback_option option);

/**
 * @if English
 * Enables or disables AI super resolution.
 * @since V4.4.0
 * @note
 * - Please contact our technical support to enable AI super resolution before you perform the feature.
 * - AI super resolution is only valid when you enable the following types of video streams:
 * - Video streams that are received from local 360P.
 * - High stream video of mainstream that are captured by the camera. AI super resolution is currently unsupported to resume
 * low streams or substreams of screen sharing.
 * @param enable     Whether to enable AI super resolution. By default, the setting is disabled.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 启用或停止 AI 超分。
 * @since V4.4.0
 * @note
 * - 使用 AI 超分功能之前，请联系技术支持开通 AI 超分功能。
 * - AI 超分仅对以下类型的视频流有效：
 *      - 必须为本端接收到第一路 360P 的视频流。
 *      - 必须为摄像头采集到的主流大流视频。AI 超分功能暂不支持复原重建小流和屏幕共享辅流。
 * @param enable        是否启用 AI 超分。默认为关闭状态。
 * @return
 * - 0: 方法调用成功
 * - 其他: 调用失败
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_enable_super_resolution(struct nertc_engine* self, bool enable);

/**
 * @if English
 * Enables or disables media stream encryption.
 * @since V4.4.0
 * In scenes where high safety is required such as financial sectors, you can set encryption modes of media streams with the
 * method before joining the room.
 * @note
 * - Please calls the method before you join the room. The encryption mode and private key cannot be changed after you join
 * the room. The SDK will automatically disable encryption after users leave the room. If you need to enable encryption again,
 * users need to call the method before joining the room.
 * - In the same room, all users who enable media stream encryption must share the same encryption mode and private keys. If
 * not, members who use different private keys will report kNERtcErrEncryptNotSuitable (30113).
 * - For safety, we recommend that you use a new private key every time you enable media stream encryption.
 * @param enable    whether to enable media stream encryption.
 *                  - true: Enabled.
 *                  - false: Disabled. This is the default value.
 * @param config    specifies encryption plan for media streams. For more information, see nertc::NERtcEncryptionConfig.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 开启或关闭媒体流加密。
 * @since V4.4.0
 * 在金融行业等安全性要求较高的场景下，您可以在加入房间前通过此方法设置媒体流加密模式。
 * @note
 * - 请在加入房间前调用该方法，加入房间后无法修改加密模式与密钥。用户离开房间后，SDK
 * 会自动关闭加密。如需重新开启加密，需要在用户再次加入房间前调用此方法。
 * - 同一房间内，所有开启媒体流加密的用户必须使用相同的加密模式和密钥，否则使用不同密钥的成员加入房间时会报错
 * kNERtcErrEncryptNotSuitable（30113）。
 * - 安全起见，建议每次启用媒体流加密时都更换新的密钥。
 * @param enable    是否开启媒体流加密。
 *                  - true: 开启
 *                  - false:（默认）关闭
 * @param config    媒体流加密方案。详细信息请参考 nertc::NERtcEncryptionConfig 。
 * @return
 * - 0: 方法调用成功
 * - 其他: 调用失败
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_enable_encryption(struct nertc_engine* self, bool enable, struct nertc_encryption_config* config);

/**
 * @if English
 * Starts the last-mile network probe test.
 * <br>This method starts the last-mile network probe test before joining a channel to get the uplink and downlink last mile
 * network statistics, including the bandwidth, packet loss, jitter, and round-trip time (RTT).This method is used to detect
 * network quality before a call. Before a user joins a room, you can use this method to estimate the subjective experience
 * and objective network status of a local user during an audio and video call. Once this method is enabled, the SDK returns
 * the following callbacks:
 * - `onLastmileQuality`: the SDK triggers this callback within five seconds depending on the network conditions. This
 * callback rates the network conditions with a score and is more closely linked to the user experience.
 * - `onLastmileProbeResult`: the SDK triggers this callback within 30 seconds depending on the network conditions. This
 * callback returns the real-time statistics of the network conditions and is more objective.
 * @note
 * - You can call this method before joining a channel(joinChannel).
 * - Do not call other methods before receiving the onLastmileQuality and onLastmileProbeResult callbacks. Otherwise, the
 * callbacks may be interrupted.
 * @since V4.5.0
 * @param config    Sets the configurations of the last-mile network probe test.
 * @endif
 * @if Chinese
 * 开始通话前网络质量探测。
 * <br>启用该方法后，SDK
 * 会通过回调方式反馈上下行网络的质量状态与质量探测报告，包括带宽、丢包率、网络抖动和往返时延等数据。一般用于通话前的网络质量探测场景，用户加入房间之前可以通过该方法预估音视频通话中本地用户的主观体验和客观网络状态。
 * <br>相关回调如下：
 * - `onLastmileQuality`：网络质量状态回调，以打分形式描述上下行网络质量的主观体验。该回调视网络情况在约 5 秒内返回。
 * - `onLastmileProbeResult`：网络质量探测报告回调，报告中通过客观数据反馈上下行网络质量。该回调视网络情况在约 30 秒内返回。
 * @note
 * - 请在加入房间（joinChannel）前调用此方法。
 * - 调用该方法后，在收到 `onLastmileQuality` 和 `onLastmileProbeResult` 回调之前请不要调用其他方法，否则可能会由于 API
 * 操作过于频繁导致此方法无法执行。
 * @since V4.5.0
 * @param config    Last mile 网络探测配置。
 * @return
 * - 0: 方法调用成功
 * - 其他: 调用失败
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_start_lastmile_probe_test(struct nertc_engine* self, const struct nertc_lastmile_probe_config* config);

/**
 * @if English
 * Stops the last-mile network probe test.
 * @since V4.5.0
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 停止通话前网络质量探测。
 * @since V4.5.0
 * @return
 * - 0: 方法调用成功
 * - 其他: 调用失败
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_stop_lastmile_probe_test(struct nertc_engine* self);

/**
 * @if English
 * Sets a remote audio stream to high priority
 * Sets a remote audio streams to high priority during automatic stream subscription. Users can hear the audio stream with high priority.
 * @note
 * - The priority of a remote audio stream must be set during a call and automatic stream subscription must be enabled (by default)
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
NERTC_API int NERTC_CALL nertc_engine_set_remote_high_priority_audio_stream(struct nertc_engine* self, bool enabled, nertc_uid_t uid);

/**
 * @if English
 * Check audio driver plug-in insall success or not (only for Mac system)
 * This method will detect whether the computer has the latest version of the virtual sound card installed. If it is not installed, and the NERTCPrivilegedTask library has been integrated in the application, the interface will pop up the virtual sound card installation dialog box, which is convenient for users to install.
 * @since V4.6.0
 * @return
 * - 0: The computer does not have a NetEase virtual sound card installed or the virtual sound card is not the latest version
 * - 1: The computer has installed the latest version of NetEase virtual sound card
 * @endif
 * @if Chinese
 * 检测虚拟声卡是否安装（仅适用于 Mac 系统）。
 * 该接口会检测电脑是否安装最新版本的虚拟声卡。如果未安装，并且应用中已集成NERTCPrivilegedTask库，该接口会弹出安装虚拟声卡对话框，方便用户安装。
 * @since V4.6.0
 * @return
 * - 0:  电脑未安装网易虚拟声卡或虚拟声卡不是最新版本
 * - 1:  电脑已安装最新版本的网易虚拟声卡
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_check_necast_audio_driver(struct nertc_engine* self);
/**
 * @if English
 * Check if video correction is enabled
 * @since V4.6.0
 * @note
 * - If you use a camera to shoot an object, a mapping process from 3D to 2D images is implemented. the image of an object is
 * deformed when the position of the camera changes.
 * - If you enable video correction with appropriate parameters, video images can be restored by algorithms.
 * - To use video correction, the rendering mode of the local canvas must be set to fit. Video frames keeps aspect ratio
 * unchanged and are all displayed in the current view. Otherwise, video correction may not take effect.
 * - If the parameters of video correction are applied, the local and remote video frames are all corrected
 * @param enable Enables or disables local video correction.
 * - true：enabled
 * - false (default): disabled
 * @return
 * - 0: success.
 * - Others: failure
 * @endif
 * @if Chinese
 * 是否启用视频图像畸变矫正。
 * @since V4.6.0
 * @note
 * -
 * 当使用相机去拍摄物体时，存在着一个从三维世界到二维图像的映射过程，这个过程中由于相机位置的变化和移动，会对拍摄物体的成像产生一定的形变影响。
 * - 开启该功能时，根据合适的参数，可以通过算法把这个形变进行复原。
 * - 使用该功能时，本地画布的渲染模式需要为 fit（即视频帧保持自身比例不变全部显示在当前视图中），否则矫正功能可能不会正常生效。
 * - 矫正参数生效后，本地画面和对端看到的画面，均会是矫正以后的画面。
 * @param enable 是否开启视频图像矫正。
 * - true：开启视频图像矫正。
 * - false（默认）：关闭视频图像矫正。
 * @return
 * - 0：方法调用成功。
 * - 其他：方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_enable_video_correction(struct nertc_engine* self, bool enable);

/**
 * @if English
 * Sets the parameters for video correction.
 * @since V4.6.0
 * @note
 * - The first 4 parameters of the config schema represent coordinates of areas to be corrected on the screen. The x and y
 * coordinates of each point ranges from 0 to 1.
 * - The last 3 parameters are required only if external video rendering is used.
 * - You can pass nill in config. If config is set to nil, the SDK clears previous configurations for video correction. The
 * video graph will be restored to the state without correction.
 * @param config Correction parameters. For more information, see {@link NERtcVideoCorrectionConfiguration}.
 * @return
 * - 0: success.
 * - Others: failure
 * @endif
 * @if Chinese
 * 设置视频图像矫正参数。
 * @since V4.6.0
 * @note
 * - 矫正参数结构体的前 4 个参数，代表了待矫正区域相对于屏幕上视图的坐标，每个坐标点的 x 和 y 的取值范围均为 0 ~ 1 的浮点数。
 * - 矫正参数结构体的后 3 个参数只有在使用了外部视频渲染功能时才需要传入。
 * - config 可以传入 nil，清空之前设置过的矫正参数，将画面恢复至矫正之前的效果。
 * @param config 视频图像矫正相关参数。详细说明请参考 {@link NERtcVideoCorrectionConfiguration}。
 * @return
 * - 0：方法调用成功。
 * - 其他：方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_video_correction_config(struct nertc_engine* self, struct nertc_video_correction_configuration* config);

/**
 * @if English
 * Enables/Disables the virtual background.
 *
 * After enabling the virtual background feature, you can replace the original background image of the local user
 * with a custom background image. After the replacement, all users in the channel can see the custom background
 * image. You can find out from the
 * RtcEngineEventHandlerEx::onVirtualBackgroundSourceEnabled "onVirtualBackgroundSourceEnabled" callback
 * whether the virtual background is successfully enabled or the cause of any errors.
 * - macOS and Windows: Devices with an i5 CPU and better
 * -  Recommends that you use this function in scenarios that meet the following conditions:
 * - A high-definition camera device is used, and the environment is uniformly lit.
 * - The captured video image is uncluttered, the user's portrait is half-length and largely unobstructed, and the
 * background is a single color that differs from the color of the user's clothing.
 * - The virtual background feature does not support video in the Texture format or video obtained from custom video capture by the Push method.
 * @since V4.6.0
 * @param enabled Sets whether to enable the virtual background:
 * - true: Enable.
 * - false: Disable.
 * @param backgroundSource The custom background image. See VirtualBackgroundSource.
 * Note: To adapt the resolution of the custom background image to the resolution of the SDK capturing video,
 * the SDK scales and crops
 * the custom background image while ensuring that the content of the custom background image is not distorted.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 * @endif
 * @if Chinese
 * 启用/禁用虚拟背景。
 * 启用虚拟背景功能后，您可以使用自定义背景图片替换本地用户的原始背景图片。
 * 替换后，频道内所有用户都可以看到自定义背景图片。
 * @since V4.6.0
 * @note
 * - 您可以通过 \ref nertc::IRtcEngineEventHandlerEx::onVirtualBackgroundSourceEnabled "onVirtualBackgroundSourceEnabled" 回调查看虚拟背景是否开启成功或出错原因。
 * - 建议您使用配备 i5 CPU 及更高性能的设备。
 * - 建议您在满足以下条件的场景中使用该功能：
 * - 采用高清摄像设备，环境光线均匀。
 * - 捕获的视频图像整洁，用户肖像半长且基本无遮挡，并且背景是与用户衣服颜色不同的单一颜色。
 * - 虚拟背景功能不支持 Texture 格式的视频或通过 Push 方法从自定义视频捕获中获取的视频。
 * @param background_source 自定义背景图片。请参阅 {@link VirtualBackgroundSource}。
 * @return
 * - 0：方法调用成功。
 * - < 0: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_enable_virtual_background(struct nertc_engine* self, bool enabled, struct nertc_virtual_background_source* background_source);

/**
 * @if English
 * Sets the Agora cloud proxy service.
 * <br>When the user's firewall restricts the IP address and port, refer to Use Cloud Proxy to add the specific IP addresses and ports to the firewall whitelist; then, call this method to enable the cloud proxy and set the proxyType parameter as NERtcTransportTypeUDPProxy(1), which is the cloud proxy for the UDP protocol.
 * - After a successfully cloud proxy connection, the SDK triggers the `onNERtcEngineConnectionStateChangeWithState(kNERtcConnectionStateConnecting, kNERtcReasonConnectionChangedSettingProxyServer)` callback.
 * - To disable the cloud proxy that has been set, call setCloudProxy(NERtcTransportTypeNoneProxy).
 * @note We recommend that you call this method before joining the channel or after leaving the channel.
 * @param proxyType The cloud proxy type. For more information, see {@link NERtcTransportType}. This parameter is required, and the SDK reports an error if you do not pass in a value.
 * @return A value of 0 returned indicates that the method call is successful. Otherwise, the method call fails.
 * @endif
 * @if Chinese
 * 开启并设置云代理服务。
 * <br>在内网环境下，如果用户防火墙开启了网络限制，请参考《使用云代理》将指定 IP 地址和端口号加入防火墙白名单，然后调用此方法开启云代理，并将 proxyType 参数设置为 NERtcTransportTypeUDPProxy(1)，即指定使用 UDP 协议的云代理。
 * - 成功连接云代理后，SDK 会触发 `onNERtcEngineConnectionStateChangeWithState(kNERtcConnectionStateConnecting, kNERtcReasonConnectionChangedSettingProxyServer)` 回调。
 * - 如果需要关闭已设置的云代理，请调用 `setCloudProxy(NERtcTransportTypeNoneProxy)`。
 * @note 请在加入房间前调用此方法。
 * @param proxyType 云代理类型。详细信息请参考 {@link NERtcTransportType}。该参数为必填参数，若未赋值，SDK 会报错。
 * @return {@code 0} 方法调用成功，其他失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_cloud_proxy(struct nertc_engine* self, nertc_transport_type proxy_type);

/**
 * @if English
 * Enables or disables local data channel.
 * @note
 * - You can call this method after you join a room.
 * - After local data channel successfully enabled or disabled,  the onUserDataStop or onUserDataStart
 * @param[in] enabled Whether to enable local data channel.
 * - true: Enables local data channel.
 * - false: Disables local data channel
 * @since V5.0.0
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 开启或关闭本地数据通道。
 * @note
 * - 该方法加入房间后才可调用。
 * - 成功启用或禁用本地数据通道后，远端会触发 onUserDataStop 或 onUserDataStart  回调。
 * @param[in] enabled 是否启用本地数据通道:
 * - true: 开启本地数据通道；
 * - false: 关闭本地数据通道。
 * @since V5.0.0
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_enable_local_data(struct nertc_engine* self, bool enabled);

/**
 * @if English
 * Unsubscribes from or subscribes to data channel from specified remote users.
 * <br>After a user joins a channel, data channel streams from all remote users are subscribed by default. You can call this method to unsubscribe from or subscribe to data channel streams from all remote users.
 * @note  When the kNERtcKeyAutoSubscribeData is enabled by default, users cannot manually modify the state of data channel subscription.
 * @param[in] uid           The user ID.
 * @param[in] subscribe
 * - true: Subscribes to specified data channel streams (default).
 * - false: Unsubscribes from specified data channel streams.
 *  @since V5.0.0
 *  @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 取消或恢复订阅指定远端用户数据通道流。
 * <br>加入房间时，默认订阅所有远端用户的数据通道流，您可以通过此方法取消或恢复订阅指定远端用户的数据通道流。
 * @note 当kNERtcKeyAutoSubscribeData默认打开时，用户不能手动修改数据通道订阅状态
 * @param[in] uid           指定用户的 ID。
 * @param[in] subscribe     是否订阅远端用户数据通道流。
 * - true: 订阅指定数据通道流（默认）。
 * - false: 取消订阅指定数据通道流。
 * @since V5.0.0
 * @return
 * - 0: 方法调用成功。
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_subscribe_remote_data(struct nertc_engine* self, nertc_uid_t uid, bool subscribe);

/**
 * @if English
 * Send data by data channel.
 * @param[in] pData    The custom data channel frame data.。
 * @param[in] size      The custom data channel data size whose maximum value does not exceed 128k bytes.
 * @since V5.0.0
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 通过数据通道发送数据。
 * @param[in] data   自定义数据。
 * @param[in] size     自定义数据长度, 最大不超过128k。
 * @since V5.0.0
 * @return
 * - 0: 方法调用成功。
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_send_data(struct nertc_engine* self, void* data, uint64_t size);

/**
 * @if English
 * Enables the beauty module.
 * - The API starts the beauty engine. If beauty is not needed, you can call `stopBeauty` to end the beauty module, destroy the beauty engine and release resources.
 * - When the beauty module is enabled, no beauty effect is applied by default. You must set beauty effects or filters by calling `setBeautyEffect` or other filters and stickers methods.
 * @note
 * - The method must be called before `enableLocalVideo`.
 * - The method is only supported on Windows
 * @since V4.2.202
 * @param file_path the absolute path of a file. For example, xxx\data\beauty\nebeauty in the Windows operating system..
 * @return
 * - 0: success.
 * - 30001 (kNERtcErrFatal): failure.
 * - 30004 (kNERtcErrNotSupported): beauty is not supported.
 * @endif
 * @if Chinese
 * 开启美颜功能模块。
 * - 调用此接口后，开启美颜引擎。如果后续不再需要使用美颜功能，可以调用 `stopBeauty` 结束美颜功能模块，销毁美颜引擎并释放资源。
 * - 开启美颜功能模块后，默认无美颜效果，您需要通过 `setBeautyEffect` 或其他滤镜、贴纸相关接口设置美颜或滤镜效果。
 * @note
 * - 该方法需要在 `enableLocalVideo` 之前设置。
 * - 该方法仅适用于 Windows 平台。
 * @since V4.2.202
 * @param file_path 文件文件绝对路径。（例：windows环境下传入xxx\data\beauty\nebeauty）
 * @return
 * - 0: 方法调用成功。
 * - 30001（kNERtcErrFatal）：方法调用失败。
 * - 30004（kNERtcErrNotSupported）：不支持美颜功能。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_start_beauty(struct nertc_engine* self, const char* file_path);

/**
 * @if English
 * Stops the beauty module.
 * @note The method is only supported on Windows
 * <br>If the beauty module is not needed, you can call `stopBeauty` to stop the module. The SDK will automatically destroy the beauty engine and release the resources.
 * @since V4.2.202
 * @return
 * - 0: success
 * - Others: failure
 * @endif
 * @if Chinese
 * 结束美颜功能模块。
 * <br>如果后续不再需要使用美颜功能，可以调用 `stopBeauty` 结束美颜功能模块，SDK 会自动销毁美颜引擎并释放资源。
 * @note 该方法仅适用于 Windows 平台。
 * @since V4.2.202
 * @return
 * - 0：方法调用成功。
 * - 其他：方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_stop_beauty(struct nertc_engine* self);

/**
* @if English
* Pauses or resumes the beauty effect
* <br> The beauty effect is paused, including the global beauty effect, filters, stickers, and makeups, until the effect is resumed.
* @note
* - The method is only supported on Windows.
* - Beauty effect is enabled by default. If you want to temporarily disable the beauty effect, call this method after invoking {@link NERtcEx#startBeauty()}.
* @since V4.2.202
* @param enabled specifies whether to resume the beauty effect.
* - true (default): resumes the beauty effect.
* - false: pauses the beauty effect.
* @return
* - 0: success
* - Others: failure
* @endif
* @if Chinese
* 暂停或恢复美颜效果。
* <br> 暂停美颜效果后，包括全局美颜、滤镜、贴纸和美妆在内的所有美颜效果都会暂时关闭，直至重新恢复美颜效果。
* @note
* - 该方法仅适用于 Windows 平台。
* - 美颜效果默认开启。若您需要临时关闭美颜功能，需要在 `startBeauty` 之后调用该方法。
* @since V4.2.202
* @param enabled 是否恢复美颜效果。
* - true：恢复美颜效果。
* - false：暂停美颜效果。
* @return
* - 0：方法调用成功。
* - 其他：方法调用失败。
* @endif
*/
NERTC_API int NERTC_CALL nertc_engine_enable_beauty(struct nertc_engine* self, bool enabled);

/**
 * @if English
 * This method is deprecated.
 * @endif
 * @if Chinese
 * 启用美颜时，启用或关闭镜像模式。
 *
 * - 美颜功能启用时，此接口用于开启或关闭镜像模式。默认为关闭状态。美颜功能暂停或结束后，此接口不再生效。
 * - 启用镜像模式之后，本端画面会呈现为左右翻转的视觉效果。
 * - 该方法已废弃。
 *
 * @since V4.2.202
 * @param enabled 美颜时是否启用镜像模式。默认为 `true`，表示美颜时启用镜像模式。`false` 表示美颜时取消镜像模式。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_enable_beauty_mirror_mode(struct nertc_engine* self, bool enabled);

/**
 * @if English
 * Gets the intensity setting of a specified beauty type.
 * <br> The method is used to get the intensity setting of a specified beauty type after you set a beauty effect with intensity using `setBeautyEffect`.
 * @note The method is only supported on Windows.
 * @since V4.2.202
 * @param type Beauty type.
 * @return
 * - 0: success
 * - Others: failure
 * @endif
 * @if Chinese
 * 获取指定美颜类型的强度设置。
 * <br> 通过接口 `setBeautyEffect` 设置美颜效果及强度后，可以通过此接口查看指定美颜效果的强度设置。
 * @note 该方法仅适用于 Windows 平台。
 * @since V4.2.202
 * @param type 美颜类型。
 * @return
 * - 0：方法调用成功。
 * - 其他：方法调用失败。
 * @endif
 */
NERTC_API float NERTC_CALL nertc_engine_get_beauty_effect(struct nertc_engine* self, nertc_beauty_effect_type type);

/**
 * @if English
 * Sets the beauty type and intensity.
 * - The method can set various types of beauty effects, such as smoothing, whitening, and big eyes.
 * - Multiple method calls can apply multiple global effects. Filters, stickers, and makeups can be added in the same way.
 * @note The method is only supported on Windows.
 * @since V4.2.202
 * @param type  Beauty type. For more information, see {@link NERtcBeautyEffectType}.
 * @param value Beauty intensity. Value range: [0, 1]. The default values of effects are different.
 * @return
 * - 0: success
 * - Others: failure
 * @endif
 * @if Chinese
 * 设置指定美颜类型的强度。
 * - 此方法可用于设置磨皮、美白、大眼等多种全局美颜类型。
 * - 多次调用此接口可以叠加多种全局美颜效果，也可以通过相关方法叠加滤镜、贴纸、美妆等自定义效果。
 * @note 该方法仅适用于 Windows 平台。
 * @since V4.2.202
 * @param type     美颜类型。详细信息请参考 {@link NERtcBeautyEffectType}。
 * @param level    对应美颜类型的强度。取值范围为 [0, 1]，各种美颜效果的默认值不同。
 * @return
 * - 0: 方法调用成功。
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_beauty_effect(struct nertc_engine* self, nertc_beauty_effect_type type, float level);

/**
* @if English
* Add filters.
* <br>The API is used to load filter assets and add related filter effects. To change a filter, call this method for a new filter.
* @note
* - The method is only supported on Windows.
* - Before applying filters, stickers, and makeups, you must prepare beauty assets or models.
* - A filter effect can be applied together with global beauty effects, stickers, and makeups. However, multiple filters cannot be applied at the same time.
* @since V4.2.202
* @param file_path The path of the filter assets or models.
* @return
* - 0: success
* - Others: failure
* @endif
* @if Chinese
* 添加滤镜效果。
* <br>此接口用于加载滤镜资源，并添加对应的滤镜效果。需要更换滤镜时，重复调用此接口使用新的滤镜资源即可。
* @note
* - 该方法仅适用于 Windows 平台。
* - 使用滤镜、贴纸和美妆等自定义美颜效果之前，需要先准备好对应的美颜资源或模型。
* - 滤镜效果可以和全局美颜、贴纸、美妆等效果互相叠加，但是不支持叠加多个滤镜。
* @since V4.2.202
* @param file_path 滤镜资源或模型所在的绝对路径。
* @return
* - 0：方法调用成功。
* - 其他：方法调用失败。
* @endif
*/
NERTC_API int NERTC_CALL nertc_engine_add_beauty_filter(struct nertc_engine* self, const char* file_path);

/**
* @if English
* Removes a filter effect.
* @note The method is only supported on Windows.
* @since V4.2.202
* @return
* - 0: success
* - Others: failure
* @endif
* @if Chinese
* 取消滤镜效果。
* @note 该方法仅适用于 Windows 平台。
* @since V4.2.202
* @return
* - 0：方法调用成功。
* - 其他：方法调用失败。
* @endif
*/
NERTC_API int NERTC_CALL nertc_engine_remove_beauty_filter(struct nertc_engine* self);

/**
 * @if English
 * Sets the filter intensity
 * A larger value indicates more intensity. You can adjust a custom value based on business requirements.
 * @note
 * - The method is only supported on Windows
 * - The setting takes effect when it is applied. The intensity remains if a filter is changes. You can adjust the intensity by setting this property.
 * @since V4.2.202
 * @param level Filter intensity. Value range: 0 - 1. Default value: 0.5.
 * @return
 * - 0: success
 * - Others: failure
 * @endif
 * @if Chinese
 * 设置滤镜强度。
 * 取值越大，滤镜强度越大，开发者可以根据业务需求自定义设置滤镜强度。
 * @note
 * - 该方法仅适用于 Windows 平台。
 * - 滤镜强度设置实时生效，更换滤镜后需要重新设置滤镜强度，否则强度取默认值。
 * @since V4.2.202
 * @param level 滤镜强度。取值范围为 [0 - 1]，默认值为 0.5。
 * @return
 * - 0：方法调用成功。
 * - 其他：方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_beauty_filter_level(struct nertc_engine* self, float level);

/**
* @if English
* Adds a sticker (beta).
* <br>The API is used to load sticker assets and add related sticker effects. To change a sticker, call this method for a new sticker.
* @note
* - The method is only supported on Windows
* - Before applying filters, stickers, and makeups, you must prepare beauty assets or models.
* - A sticker effect can be applied together with global beauty effects, stickers, and makeups. However, multiple stickers cannot be applied at the same time.
* @since V4.2.202
* @param file_path The path of the sticker assets or models.
* @return
* - 0: success
* - Others: failure
* @endif
* @if Chinese
* （此接口为 beta 版本）添加贴纸效果。
* <br>此接口用于加载贴纸资源，添加对应的贴纸效果。需要更换贴纸时，重复调用此接口使用新的贴纸资源即可。
* @note
* - 该方法仅适用于 Windows 平台。
* - 使用滤镜、贴纸和美妆等自定义美颜效果之前，需要先准备好对应的美颜资源或模型。
* - 贴纸效果可以和全局美颜、滤镜、美妆等效果互相叠加，但是不支持叠加多个贴纸。
* @since V4.2.202
* @param file_path 贴纸资源或模型所在的绝对路径。
* @return
* - 0：方法调用成功。
* - 其他：方法调用失败。
* @endif
*/
NERTC_API int NERTC_CALL nertc_engine_add_beauty_sticker(struct nertc_engine* self, const char* file_path);

/**
* @if English
* Removes a sticker (beta).
* @note The method is only supported on Windows
* @since V4.2.202
* @return
* - 0: success
* - Others: failure
* @endif
* @if Chinese
* （此接口为 beta 版本）取消贴纸效果。
* @note 该方法仅适用于 Windows 平台。
* @since V4.2.202
* @return
* - 0：方法调用成功。
* - 其他：方法调用失败。
* @endif
*/
NERTC_API int NERTC_CALL nertc_engine_remove_beauty_sticker(struct nertc_engine* self);

/**
 * @if English
 * Adds a makeup effect (beta).
 * <br>The API is used to load makeup assets and add related sticker effects. To change a makeup effect, call this method for a new makeup effect.
 * @note
 * - The method is only supported on Windows
 * - Before applying filters, stickers, and makeups, you must prepare beauty assets or models.
 * - A makeup effect can be applied together with global beauty effects, stickers, and makeups. However, multiple makeup effects cannot be applied at the same time.
 * @since V4.2.202
 * @param path The path of the makeup assets or models.
 * @return
 * - 0: success
 * - Others: failure
 * @endif
 * @if Chinese
 * （此接口为 beta 版本）添加美妆效果。
 * 此接口用于加载美妆模型，添加对应的美妆效果。需要更换美妆效果时，重复调用此接口使用新的美妆模型即可。
 * @note
 * - 该方法仅适用于 Windows 平台。
 * - 使用滤镜、贴纸和美妆等自定义美颜效果之前，需要先准备好对应的美颜资源或模型。
 * - 美妆效果可以和全局美颜、滤镜、贴纸等效果互相叠加，但是不支持叠加多个美妆效果。
 * @since V4.2.202
 * @param file_path 美妆模型所在的绝对路径。
 * @return
 * - 0：方法调用成功。
 * - 其他：方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_add_beauty_makeup(struct nertc_engine* self, const char* file_path);

/**
 * @if English
 * Removes a makeup effect (beta).
 * @note The method is only supported on Windows
 * @since V4.2.202
 * @return
 * - 0: success
 * - Others: failure
 * @endif
 * @if Chinese
 * （此接口为 beta 版本）取消美妆效果。
 * @note 该方法仅适用于 Windows 平台。
 * @since V4.2.202
 * @return
 * - 0：方法调用成功。
 * - 其他：方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_remove_beauty_makeup(struct nertc_engine* self);

/**
 * @if English
 * Sets the reverb effect for the local audio stream.
 * @note The method can be called before or after a user joins a room. The setting will be reset to the default value after a call ends.
 * @since V4.6.10
 * @param param For more information, see {@link NERtcReverbParam}.
 * @return
 * - 0: success
 * - Others: failure
 * @endif
 * @if Chinese
 * 设置本地语音混响效果。
 * @note 该方法在加入房间前后都能调用，通话结束后重置为默认的关闭状态。
 * @since V4.6.10
 * @param param 详细信息请参考 {@link NERtcReverbParam}。
 * @return
 * - 0：方法调用成功。
 * - 其他：方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_set_local_voice_reverb_param(struct nertc_engine* self, const struct nertc_reverb_param* param);

/**
 * @if English
 * Publishes or unpublishes the local audio stream.
 * <br>When a user joins a room, the feature is enabled by default.
 * <br>The method does not affect receiving or playing the remote audio stream. The enableLocalAudio(false) method is suitable for scenarios where clients only receives remote media streams and does not publish any local streams.
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
 * - 成功调用该方法切换本地用户的发流状态后，房间内其他用户会收到 \ref IRtcEngineEventHandler::onUserAudioStart "onUserAudioStart"（开启发送音频）或 \ref IRtcChannelEventHandler::onUserAudioStop "onUserAudioStop"（停止发送音频）的回调。
 * @par 相关接口
 * - \ref IRtcEngineEx::muteLocalAudioStream "muteLocalAudioStream"：
 *         - 在需要开启本地音频采集（监测本地用户音量）但不发送音频流的情况下，您也可以调用 muteLocalAudioStream(true) 方法。
 *         - 两者的差异在于，muteLocalAudioStream(true) 仍然保持与服务器的音频通道连接，而 enableMediaPub(false) 表示断开此通道，因此若您的实际业务场景为多人并发的大房间，建议您调用 enableMediaPub 方法。
 * @param enabled 是否发布本地媒体流。
 * - true（默认）：发布本地媒体流。
 * - false：不发布本地媒体流。
 * @param media_type 媒体发布类型，暂时仅支持音频。
 * @return
 * - 0：方法调用成功。
 * - 其他：方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_enable_media_publish(struct nertc_engine* self, bool enabled, nertc_media_pub_type media_type);

/**
* @if English
* Update the permission key. It needs to be set during the call. See ref onUpdatePermissionKey for asynchronous results.
* @param key New Permission Key
* @return
* - 0: success
* - Others: failure
* @endif
* @if Chinese
* 更新权限密钥。
* - 通过本接口可以实现当用户权限被变更，或者收到权限密钥即将过期的回调 \ref IRtcEngineEventHandlerEx::onPermissionKeyWillExpire() "onPermissionKeyWillExpire" 时，更新权限密钥。
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
* std::string key;//向服务器请求得到的权限key，具体请参考<a href="https://doc.yunxin.163.com/jcyOTA0ODM/docs/TQwMTEwMjk?platform=windows" target="_blank">高级 Token 鉴权</a>
* rtc_engine_->updatePermissionKey(key.c_str()));    if (kNERtcNoError != res) {
* }
* @endcode
* @par 相关回调
* 调用此接口成功更新权限密钥后会触发 \ref IRtcEngineEventHandlerEx::onUpdatePermissionKey() "onUpdatePermissionKey" 回调。
* @return
* - 0（kNERtcNoError）：方法调用成功。
* - 其他：方法调用失败。
*         - 30003（kNERtcErrInvalidParam）：参数错误，比如 key 无效。
*         - 30005（kNERtcErrInvalidState)：当前状态不支持的操作，比如引擎尚未初始化。
* @endif
*/
NERTC_API int NERTC_CALL nertc_engine_update_permission_key(struct nertc_engine* self, const char* key);

/**
 * @if Chinese
 * 上报自定义事件
 * @param event_name      事件名 不能为空
 * @param custom_identify 自定义标识，比如产品或业务类型，如不需要填null
 * @param parameters          参数键值对 ，参数值支持String 及java基本类型(int 、bool....) ， 如不需要填null
 * @return 操作返回值，成功则返回 0
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_report_custom_event(struct nertc_engine* self, const char* event_name, const char* custom_identify, const char* parameters);

/**
 * 引擎3D音效算法距离范围设置
 * @note 依赖enableSpatializer接口开启，通话前调用
 * @param audible_distance 监听器能够听到扬声器并接收其文本消息的距离扬声器的最大距离。[0,1000] 默认值为 32。
 * @param conversational_distance 控制扬声器音频保持其原始音量的范围，超出该范围时，语音聊天的响度在被听到时开始淡出。
 * 默认值为 1。
 * @param roll_off:距离衰减模式 #NERtcDistanceRolloffModel ，默认值 #kNERtcDistanceRolloffNone
 * @return
 * - 0: 方法调用成功
 * - 其他: 调用失败
 */

/**
 * 设置范围语音模式
 * @note 此接口在加入房间前后均可调用。
 * @param mode 范围语音模式
 * @return 操作返回值，成功则返回 0
 */
NERTC_API int NERTC_CALL nertc_engine_set_range_audio_mode(struct nertc_engine* self, nertc_range_audio_mode mode);

/**
 * 设置范围语音小队
 * @note 此接口在加入房间前后均可调用。
 * @param team_id 小队ID
 * @return 操作返回值，成功则返回 0
 */
NERTC_API int NERTC_CALL nertc_engine_set_range_audio_team_id(struct nertc_engine* self, int32_t team_id);

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
NERTC_API int NERTC_CALL nertc_engine_set_audio_recv_range(struct nertc_engine* self, int audible_distance, int conversational_distance, nertc_distance_rolloff_model roll_off);

/**
 * 引擎3D音效算法中本人坐标方位更新接口
 * @param speaker_position 嘴巴位置信息，默认值{0,0,0}
 * @param speaker_quaternion 嘴巴方向信息，四元组格式，默认值{0,0,0,0}
 * @param head_position 耳朵位置信息，默认值{0,0,0}
 * @param head_quaternion 耳朵方向信息，四元组格式，默认值{0,0,0,0}
 * @return
 * - 0: 方法调用成功
 * - 其他: 调用失败
 */
NERTC_API int NERTC_CALL nertc_engine_update_self_position(struct nertc_engine* self, const struct nertc_position_info* info);

/**
 * 引擎3D音效算法中房间混响效果开关
 * @note 依赖enableSpatializer接口开启
 * @param enable 混响效果开关，默认值关闭
 * @return
 * - 0: 方法调用成功
 * - 其他: 调用失败
 */
NERTC_API int NERTC_CALL nertc_engine_enable_spatializer_room_effects(struct nertc_engine* self, bool enable);
/**
 * 引擎3D音效算法中房间混响属性
 * @note 依赖enableSpatializer接口开启
 * @param room_property 房间属性 #NERtcSpatializerRoomProperty
 * @return
 * - 0: 方法调用成功
 * - 其他: 调用失败
 */
NERTC_API int NERTC_CALL nertc_engine_set_spatializer_room_property(struct nertc_engine* self, const struct nertc_spatializer_room_property* room_property);

/**
 * 引擎3D音效算法中渲染模式
 * @note 依赖enableSpatializer接口开启
 * @param mode 渲染模式 #NERtcSpatializerRenderMode ，默认值 #kNERtcSpatializerRenderBinauralHighQuality
 * @return
 * - 0: 方法调用成功
 * - 其他: 调用失败
 */
NERTC_API int NERTC_CALL nertc_engine_set_spatializer_render_mode(struct nertc_engine* self, nertc_spatializer_render_mode mode);

/**
 * 初始化引擎3D音效算法
 * @note 此接口在加入房间前调用，退出房间后不重置
 * @return
 * - 0: 方法调用成功
 * - 其他: 调用失败
 */
NERTC_API int NERTC_CALL nertc_engine_init_spatializer(struct nertc_engine* self);

/**
 * 引擎3D音效算法开关
 * @note 通话前调用，通话结束后不重置
 * @param enable 是否打开3D音效算法功能
 * @return
 * - 0: 方法调用成功
 * - 其他: 调用失败
 */
NERTC_API int NERTC_CALL nertc_engine_enable_spatializer(struct nertc_engine* self, bool enable);
/**
 * @if English
 * Convert I420 to RGBA
 * @since V4.5.0
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 将I420格式转换为RGBA格式
 * @since V4.5.0
 * @return
 * - 0: 方法调用成功
 * - 其他: 调用失败
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_convert_i420_to_rgba(const uint8_t* src_y,
                                                           int src_stride_y,
                                                           const uint8_t* src_u,
                                                           int src_stride_u,
                                                           const uint8_t* src_v,
                                                           int src_stride_v,
                                                           uint8_t* dst_rgba,
                                                           int dst_stride_rgba,
                                                           int width,
                                                           int height);


/**
 @param enabled 麦克风是否打开
 @return
 - 0: 方法调用成功；
 - 其他: 方法调用失败。
 */
NERTC_API int NERTC_CALL nertc_engine_get_microphone_mode(struct nertc_engine* self, bool *enabled);  
/**
 @param volume 麦克风音量
 @return
 - 0: 方法调用成功；
 - 其他: 方法调用失败。
 */
NERTC_API int NERTC_CALL nertc_engine_get_recording_signal_volume(struct nertc_engine* self, int *volume);
/**
 @param volume 扬声器音量
 @return
 - 0: 方法调用成功；
 - 其他: 方法调用失败。
 */
NERTC_API int NERTC_CALL nertc_engine_get_playback_signal_volume(struct nertc_engine* self, int *volume);
/**
 * 检查平台麦克风权限（移动端）
 @param enabled 麦克风是否有权限
 @return
 - 0: 方法调用成功；
 - 其他: 方法调用失败。
 */
NERTC_API int NERTC_CALL nertc_engine_check_mic_permision(struct nertc_engine* self, bool *enabled);
/**
 * 暂停音频输入与输出
 @return
 - 0: 方法调用成功；
 - 其他: 方法调用失败。
 */
NERTC_API int NERTC_CALL nertc_engine_pause_audio(struct nertc_engine* self);
/**
 * 恢复音频输入与输出
 @return
 - 0: 方法调用成功；
 - 其他: 方法调用失败。
 */
NERTC_API int NERTC_CALL nertc_engine_resume_audio(struct nertc_engine* self);
/**
 * 检查是否已经在房间内
 @return
 - true: 在房间内；
 - false: 不在房间内。
 */
NERTC_API bool NERTC_CALL nertc_engine_is_in_channel(struct nertc_engine* self);

NERTC_END_DECLS

#endif  // NERTC_ENGINE_EX_H
