/** @file NertcEngineEx.h
 * @brief The interface header file of expansion NERTC UE SDK.
 * All parameter descriptions of the NERTC UE SDK. All string-related parameters (char *) are encoded in UTF-8.
 * @copyright (c) 2015-2022, NetEase Inc. All rights reserved.
 */

#pragma once
#include "NertcBase.h"
#include "INertcEngine.h"
#include "INertcMediaStatsObserver.h"
#include <string>

namespace nertc {

class IRtcEngineEx:public IRtcEngine {
public:
  virtual ~IRtcEngineEx(){}
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
virtual NERtcConnectionStateType getConnectionState() = 0;
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
virtual int muteLocalAudioStream(NERtcAudioStreamType type, bool mute) = 0;
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
virtual int setAudioProfile(NERtcAudioProfileType profile, NERtcAudioScenarioType scenario) = 0;

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
virtual int setAudioEffectPreset(NERtcVoiceChangerType type) = 0;

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
virtual int setVoiceBeautifierPreset(NERtcVoiceBeautifierType type) = 0;

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
virtual int setLocalVoicePitch(double pitch) = 0;

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
virtual int setLocalVoiceEqualization(NERtcVoiceEqualizationBand band_frequency, int band_gain) = 0;

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
virtual int subscribeRemoteAudioStream(NERtcAudioStreamType stream_type, uid_t uid, bool subscribe) = 0;

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
virtual int subscribeAllRemoteAudioStream(bool subscribe) = 0;

/**
 * @if Chinese
 * 你可以调用该方法指定音频流被谁订阅。
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
virtual int setPublishAudioAllowList(uid_t* uid_array, uint32_t size) = 0;

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
virtual int setSubscribeAudioAllowList(uid_t* uid_array, uint32_t size) = 0;

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
virtual int setSubscribeAudioBlockList(uid_t* uid_array, uint32_t size) = 0;

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
virtual int setAudioSessionOperationRestriction(NERtcAudioSessionOperationRestriction restriction) = 0;

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
virtual int setAudioFocusMode(NERtcAudioFocusMode focus_mode) = 0;
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
virtual int setPlayoutDeviceMute(bool muted) = 0;

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
virtual int getPlayoutDeviceMute(bool* muted) = 0;

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
virtual int setParameters(const char* parameters) = 0;

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
virtual int setAudioFrameObserver(INERtcAudioFrameObserver* observer) = 0;
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
virtual int startAudioDump(NERtcAudioDumpType type) = 0;
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
virtual int stopAudioDump() = 0;

/**
 设置音频播放扬声器模式（仅iOS/Android有效）

 @param enable 是否使用扬声器模式
 @return 操作返回值，成功则返回 0
 */
virtual int setLoudspeakerMode( bool enable) = 0;

/**
 获取目前是否使用扬声器模式（仅iOS/Android有效）

 @param enabled 是否正在使用扬声器模式
 @return
 - 0: 方法调用成功；
 - 其他: 方法调用失败。
 */
virtual int getLoudspeakerMode(bool* enabled) = 0;

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
virtual int setStatsObserver(IRtcMediaStatsObserver* observer) = 0;

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
virtual int enableAudioVolumeIndication(bool enable, uint64_t interval, bool enable_vad) = 0;

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
virtual const char* getVersion(int* build) = 0;
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
virtual const char* getErrorDescription(int error_code) = 0;
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
virtual void uploadSdkInfo() = 0;
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
virtual int adjustRecordingSignalVolume(int volume) = 0;
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
virtual int adjustPlaybackSignalVolume(int volume) = 0;


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
virtual int enableMediaPublish(bool enabled, NERtcMediaPubType media_type) = 0;

/**
 * 设置范围语音模式
 * @note 此接口在加入房间前后均可调用。
 * @param mode 范围语音模式
 * @return 操作返回值，成功则返回 0
 */
virtual int setRangeAudioMode(NERtcRangeAudioMode mode) = 0;

/**
 * 设置范围语音小队
 * @note 此接口在加入房间前后均可调用。
 * @param team_id 小队ID
 * @return 操作返回值，成功则返回 0
 */
virtual int setRangeAudioTeamID(int32_t team_id) = 0;

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
virtual int setAudioRecvRange(int audible_distance, int conversational_distance, NERtcDistanceRolloffModel roll_off) = 0;
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
virtual int updateSelfPosition(const NERtcPositionInfo& info) = 0;

/**
 * 初始化引擎3D音效算法
 * @note 此接口在加入房间前调用，退出房间后不重置
 * @return
 * - 0: 方法调用成功
 * - 其他: 调用失败
 */
virtual int initSpatializer() = 0;

/**
 * 引擎3D音效算法开关
 * @note 通话前调用，通话结束后不重置
 * @param enable 是否打开3D音效算法功能
 * @return
 * - 0: 方法调用成功
 * - 其他: 调用失败
 */
virtual int enableSpatializer(bool enable) = 0;

/**
 * 获取麦克风开关状态
 * @return 麦克风打开状态
 */
virtual int getMicrophoneMode(bool* enabled) = 0;

/**
 * 获取麦克风音量
 * @return 麦克风音量
 */
virtual int getRecordingSignalVolume() = 0;

/**
 * 获取扬声器音量
 * @return 扬声器音量
 */
virtual int getPlaybackSignalVolume() = 0;

/**
 * 检查平台麦克风权限（移动端）
 * @return 麦克风权限
 */
virtual bool checkMicPermision() = 0;

/**
 * 暂停音频输入与输出
 @return
 - 0: 方法调用成功；
 - 其他: 方法调用失败。
 */
virtual int pauseAudio() = 0;
/**
 * 暂停音频输入与输出
 @return
 - 0: 方法调用成功；
 - 其他: 方法调用失败。
 */
virtual int resumeAudio() = 0;
/**
 * 检查是否已经在房间内
 @param enabled 输出结果，true:在房间内 false:不在房间内
 @return
 - 0: 方法调用成功；
 - 其他: 方法调用失败。
 */
virtual bool isInChannel() = 0;
/**
 * 安卓平台下请求录音权限、蓝牙权限
 */
virtual bool acquireAndroidRecordingPermissions() = 0;
};

  NERTC_UE_API IRtcEngineEx* NERTC_UE_CALL createNERtcEngine();
}