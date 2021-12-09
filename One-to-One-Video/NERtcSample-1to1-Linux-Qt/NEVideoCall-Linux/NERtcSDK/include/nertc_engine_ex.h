/** @file nertc_engine_ex.h
* @brief The interface header file of expansion NERTC SDK.
* All parameter descriptions of the NERTC SDK. All string-related parameters (char *) are encoded in UTF-8.
* @copyright (c) 2015-2022, NetEase Inc. All rights reserved.
*/

#ifndef NERTC_ENGINE_EX_H
#define NERTC_ENGINE_EX_H

#include "nertc_base.h"
#include "nertc_base_types.h"
#include "nertc_engine_defines.h"
#include "nertc_engine_event_handler.h"
#include "nertc_engine_media_stats_observer.h"
#include "nertc_engine.h"

 /**
 * @namespace nertc
 * @brief namespace nertc
 */
namespace nertc
{
/** 
 * @if English
 * RtcEngine class provides main interface-related methods for applications to call. 
 * <br>IRtcEngineEx is the expansion interface of the NERTC SDK. Creates an IRtcEngine object and calls the methods of this object, and you can activate the communication feature the NERTC SDK provides. 
 * @endif
 * @if Chinese
 * RtcEngine 类提供了供 App 调用的主要接口方法。
 * <br>IRtcEngineEx 是 NERTC SDK 的扩展接口类。创建一个 IRtcEngine 对象并调用这个对象的方法可以激活 NERTC SDK 的通信功能。
 * @endif
 */
class IRtcEngineEx : public IRtcEngine
{
public:
    virtual ~IRtcEngineEx() {}

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
     * Enables or disabling publishing the local audio stream. The method is used to enable or disable publishing the local audio stream. 
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
     * @param[in] mute      静音/取消静音:
     * - true: 静音本地音频
     * - false: 取消静音本地音频（默认）
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int muteLocalAudioStream(bool mute) = 0;

    /** 
     * @if English
     * Sets the audio encoding profile.
     * @note
     * - Sets the method before calling the \ref IRtcEngine::joinChannel "joinChannel". Otherwise, the setting is invalid after \ref IRtcEngine::joinChannel "joinChannel".
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
     * - 该方法需要在 \ref IRtcEngine::joinChannel "joinChannel" 之前设置好， \ref IRtcEngine::joinChannel "joinChannel" 之后设置不生效。
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
     * - You can call this method either before or after joining a room. By default, the audio effect is disabled after the call ends.
     * - The method conflicts with setLocalVoicePitch. After you call this method, the voice pitch is reset to the default value 1.0.
     * @param[in] type      The preset voice changer effect. By default, the audio effect is disabled. For more information, see nertc::NERtcVoiceChangerType.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
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
     * @param[in] type      The present voice beautifier effect. By default, the voice beautifier effect is disabled. For more information, see nertc::NERtcVoiceBeautifierType.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
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
     * - The method conflicts with setAudioEffectPreset. After you call this method, the preset voice beautifier effect will be removed.
     * @param[in] pitch         The voice frequency. Valid values: 0.5 to 2.0. Smaller values have lower pitches. The default value is 1, which That the pitch is not changed.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
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
     * @note You can call this method either before or after joining a room. By default, the audio effect is disabled after the call ends.
     * @param[in] band_frequency    Sets the band frequency. Value range: 0 to 9. Those numbers represent the respective 10-band center frequencies of the voice effects, including 31, 62, 125, 250, 500, 1k, 2k, 4k, 8k, and 16k Hz.
     * @param[in] band_gain         Sets the gain of each band (dB). Value range: -15 to 15. The default value is 0.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 设置本地语音音效均衡，即自定义设置本地人声均衡波段的中心频率。
     * @note 该方法在加入房间前后都能调用，通话结束后重置为默认关闭状态。
     * @param[in] band_frequency    频谱子带索引，取值范围是 [0-9]，分别代表 10 个频带，对应的中心频率是 [31，62，125，250，500，1k，2k，4k，8k，16k] Hz。
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
     * <br>After a user joins a channel, audio streams from all remote users are subscribed by default. You can call this method to unsubscribe from or subscribe to audio streams from all remote users.
     * @note  When the kNERtcKeyAutoSubscribeAudio is enabled by default, users cannot manually modify the state of audio subscription.
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
    virtual int subscribeRemoteAudioStream(uid_t uid, bool subscribe) = 0;

    /** 
     * @if English
     * Sets local video parameters.
     * @note
     * - You can call this method before or after you join the room.
     * - After the setting is configured, the setting takes effect the next time local video is enabled. 
     * - Each profile has a set of video parameters, such as resolution, frame rate, and bitrate. All the specified values of the parameters are the maximum values in optimal conditions. If the video engine cannot use the maximum value of resolution, due to poor network performance, the value closest to the maximum value is taken.
     * @param[in] config        Sets the video encoding parameters. For more information, see {@link NERtcVideoConfig}.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * 设置本地视频的编码属性。
     * 可以在加入房间前或加入房间后调用。设置成功后，下一次开启本端视频时生效。
     * @note
     * - 每个属性对应一套视频参数，例如分辨率、帧率、码率等。 所有设置的参数均为理想情况下的最大值。当视频引擎因网络环境等原因无法达到设置的分辨率的最大值时，会取最接近最大值的那个值。
     * - setVideoConfig 为全量参数配置接口，重复调用此接口时，SDK 会刷新此前的所有参数配置，以最新的传参为准。所以每次修改配置时都需要设置所有参数，未设置的参数将取默认值。
     * @param[in] config        视频编码属性配置，详细信息请参考 {@link NERtcVideoConfig}。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
     * @endif
     */
    virtual int setVideoConfig(const NERtcVideoConfig& config) = 0;

    /** 
     * @if English
     * Specifies whether to enable or disable the dual stream mode.
     * <br>The method sets the single-stream mode or dual-stream mode. If the dual-stream mode is enabled, the receiver can choose to receive the high-quality stream or low-quality stream video. The high-quality stream has a high resolution and high bitrate. The low-quality stream has a low resolution and low bitrate.
     * @note
     * - The method applies to camera data only. Video streams from external input and screen sharing are not affected.
     * - You can call this method before or after you join a room. After the method is set, it can take effect after restarting the camera.
     * @param[in] enable        Whether to enable dual-stream mode.
     * - true: Enables the dual-stream mode. This is the default value.
     * - false: Disables the dual-stream mode. 
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
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
    virtual int enableDualStreamMode(bool enable) = 0;

    /** 
     * @if English
     * Sets a remote substream canvas.
     * - This method is used to set the display information about the local secondary stream video. The app associates with the video view of local secondary stream by calling this method. 
     * - During application development, in most cases, before joining a room, you must first call this method to set the local video view after the SDK is initialized.
     * @param[in] canvas        The video canvas information.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * 
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 设置本地辅流视频画布。
     * - 该方法设置本地辅流视频显示信息。App 通过调用此接口绑定本地辅流的显示视窗（view）。 
     * - 在 App 开发中，通常在初始化后调用该方法进行本地视频设置，然后再加入房间。
     * @param[in] canvas        视频画布信息。
     * @return
     * - 0: 方法调用成功。
     * - 其他: 方法调用失败。
     * @endif
     */
    virtual int setupLocalSubStreamVideoCanvas(NERtcVideoCanvas* canvas) = 0;

    /** 
     * @if English
     * Sets the local view display mode.  
     * <br>This method is used to set the display mode about the local view. The application can repeatedly call the method to change the display mode.
     * @note You must set local secondary canvas before enabling screen shariing.
     * @param[in] scaling_mode  The video display mode. #NERtcVideoScalingMode.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * 
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 设置本端的屏幕共享辅流视频显示模式。
     * <br>该方法设置本地视图显示模式。 App 可以多次调用此方法更改显示模式。
     * @note 调用此方法前，必须先通过 setupLocalSubStreamVideoCanvas 设置本地辅流画布。
     * @param[in] scaling_mode  视频显示模式。
     * @return
     * - 0: 方法调用成功。
     * - 其他: 方法调用失败。
     * @endif
     */
    virtual int setLocalSubStreamRenderMode(NERtcVideoScalingMode scaling_mode) = 0;

    /** 
     * @if English
     * Sets the display mode for local substreams video of screen sharing.
     * This method is used to set the display mode about the local view. The application can repeatedly call the method to change the display mode.
     * @note You must set the local canvas for local substreams through setupLocalSubStreamVideoCanvas. 
     * @param[in] scaling_mode      The video display mode. #NERtcVideoScalingMode.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 设置本地视图显示模式。
     * 该方法设置本地视图显示模式。 App 可以多次调用此方法更改显示模式。
     * @note 在打开屏幕共享前必须设置本地辅流画布。
     * @param[in] scaling_mode      视频显示模式: #NERtcVideoScalingMode
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int setLocalRenderMode(NERtcVideoScalingMode scaling_mode) = 0;

    
    /** 
     * @if English
     * Sets the mirror mode of the local video. 
     * The method is used to set whether to enable the mirror mode for the local video. The mirror code determines whether to flip the screen view right or left. 
     * Mirror mode for local videos only affects what local users view. The views of remote users are not affected. App can repeatedly call this method to modify the mirror mode.
     * @param[in] mirror_mode       The video mirror mode. For more information, see {@link NERtcVideoMirrorMode}.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 设置本地视频镜像模式。
     * 该方法用于设置本地视频是否开启镜像模式，即画面是否左右翻转。
     * 本地的视频镜像模式仅影响本地用户所见，不影响远端用户所见。App 可以多次调用此方法更改镜像模式。
     *  @param[in] mirror_mode      视频镜像模式。详细信息请参考 {@link NERtcVideoMirrorMode}。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int setLocalVideoMirrorMode(NERtcVideoMirrorMode mirror_mode) = 0;

    /** 
     * @if English
     * Sets display mode for remote views. 
     * This method is used to set the display mode for the remote view. App can repeatedly call this method to modify the display mode.
     * @param[in] uid           The ID of a remote user.
     * @param[in] scaling_mode  The video display mode. #NERtcVideoScalingMode.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 设置远端视图显示模式。
     * 该方法设置远端视图显示模式。App 可以多次调用此方法更改显示模式。
     * @param[in] uid           远端用户 ID。
     * @param[in] scaling_mode  视频显示模式: #NERtcVideoScalingMode
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
     * @endif
     */
    virtual int setRemoteRenderMode(uid_t uid, NERtcVideoScalingMode scaling_mode) = 0;

    /** 
     * @if English
     * Sets a remote substream video canvas.
     * <br>The method associates a remote user with a substream view. You can assign a specified uid to use a corresponding canvas.
     * @note 
     * - If the uid is not retrieved, you can set the user ID after the app receives a message delivered when the \ref IRtcEngineEventHandler::onUserJoined "onUserJoined"  is triggered.
     * - After a user leaves the room, the association between a remote user and the view is cleared.
     * - After a user leaves the room, the association between a remote user and the canvas is cleared. The setting is automatically invalid. 
     * @param[in] uid       The ID of a remote user.
     * @param[in] canvas    The video canvas settings.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * 
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 设置远端的辅流视频画布。
     * <br>该方法绑定远端用户和辅流显示视图，即指定某个 uid 使用对应的画布显示。
     * @note
     * - 如果 App 无法事先知道对方的 uid，可以在 APP 收到 \ref IRtcEngineEventHandler::onUserJoined "onUserJoined" 事件时设置。
     * - 退出房间后，SDK 会清除远端用户和画布的的绑定关系，该设置自动失效。
     * @param[in] uid       远端用户 ID。
     * @param[in] canvas    视频画布设置
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
     * @endif
     */
    virtual int setupRemoteSubStreamVideoCanvas(uid_t uid, NERtcVideoCanvas* canvas) = 0;

    /** 
     * @if English
     * Subscribes to or unsubscribes from remote substream video from screen sharing. You can receive the substream video data only after you subscribe to remote substream video stream.
     * @note 
     * - You must call the method after joining a room.
     * - You must first set a remote substream canvas.
     * @param[in] uid           The user ID.
     * @param[in] subscribe
     * - true: Subscribes to or unsubscribes from video streams from specified remote users.
     * - false: Unsubscribes from video streams of specified remote users.  
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * 
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 订阅或取消订阅远端的屏幕共享辅流视频，订阅之后才能接收远端的辅流视频数据。
     * @note 
     * - 必须在远端加入房间后调用。
     * - 调用此接口前，必须先通过 setupRemoteSubStreamVideoCanvas 设置远端辅流画布。
     * @param[in] uid           指定用户的用户 ID。
     * @param[in] subscribe
     * - true: 订阅指定远端用户的视频流。
     * - false: 取消订阅指定远端用户的视频流。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
     * @endif
     */
    virtual int subscribeRemoteVideoSubStream(uid_t uid, bool subscribe) = 0;

    /** 
     * @if English
     * Sets substream video display modes for remote screen sharing.
     * <br>You can use the method when screen sharing is enabled in substreams on the remote side. The application can repeatedly call the method to change the display mode.
     * @param[in] uid           The ID of a remote user.
     * @param[in] scaling_mode  The video display mode. #NERtcVideoScalingMode.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * 
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 设置远端的屏幕共享辅流视频显示模式。
     * <br>在远端开启辅流形式的屏幕共享时使用。App 可以多次调用此方法更改显示模式。
     * @param[in] uid           远端用户 ID。
     * @param[in] scaling_mode  视频显示模式。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
     * @endif
     */
    virtual int setRemoteSubSteamRenderMode(uid_t uid, NERtcVideoScalingMode scaling_mode) = 0;

    /** 
     * @if English
     * Enables video preview.
     * <br>The method is used to enable local video preview before you join a room. Prerequisites for calling the API: 
     * - Calls \ref IRtcEngine::setupLocalVideoCanvas "setupLocalVideoCanvas" to set preview window.
     * @note After the local video preview is enabled, you must first disable the local preview and call \ref IRtcEngineEx::stopVideoPreview "stopVideoPreview" before joining the room. 
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * 开启视频预览。
     * <br>该方法用于在进入房间前启动本地视频预览。调用该 API 前，必须:
     * - 调用 \ref IRtcEngine::setupLocalVideoCanvas "setupLocalVideoCanvas" 设置预览窗口；
     * @note 启用了本地视频预览后，在进入房间前，本地预览必须先关闭，需要先调用 \ref IRtcEngineEx::stopVideoPreview "stopVideoPreview" 。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
     * @endif
     */
    virtual int startVideoPreview() = 0;

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
    virtual int stopVideoPreview() = 0;

    /** 
     * @if English
     * Enables or disables publishing the local video stream.
     * <br>If the method is called Successfully, onUserVideoMute is triggered remotely. 
     * @note
     * - When you call the method to disable video streams,  the SDK doesn’t send local video streams but the camera is still working. 
     * - The method can be called before or after a user joins a room.
     * - If you stop publishing the local video stream by calling this method, the option is reset to the default state that allows the app to publish the local video stream. 
     * - \ref nertc::IRtcEngine::enableLocalVideo "enableLocalVideo" (false) is different from \ref nertc::IRtcEngine::enableLocalVideo "enableLocalVideo" (false). The enableLocalVideo(false) method turns off local camera devices. The muteLocalVideoStreamvideo method does not affect local video capture, or disable cameras, and responds faster.
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
     * - 该方法与 \ref nertc::IRtcEngine::enableLocalVideo "enableLocalVideo" (false) 的区别在于， \ref nertc::IRtcEngine::enableLocalVideo "enableLocalVideo" (false) 会关闭本地摄像头设备，muteLocalVideoStream不影响本地视频流采集，不禁用摄像头，且响应速度更快。
     * @param[in] mute
     * - true: 不发送本地视频流
     * - false: 发送本地视频流（默认）
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int muteLocalVideoStream(bool mute) = 0;

    /** 
     * @if English
     * Sets the priority of media streams from a local user.
     * <br>If a user has a high priority, the media stream from the user also has a high priority. In unreliable network connections, the SDK guarantees the quality the media stream from users with a high priority.
     * @note
     * - You must call the method before you call joinChannel.
     * - After switching channels, media priority changes to the default value of normal priority.
     * - An RTC room has only one user that has a high priority. We recommend that only one user in a room call the setLocalMediaPriority method to set the local media stream a high priority. Otherwise, you need to enable the preempt mode to ensure the high priority of the local media stream.
     * @param priority      The priority of the local media stream. The default value is #kNERtcMediaPriorityNormal. For more information, see #NERtcMediaPriorityType.
     * @param is_preemptive specifies whether to enable the preempt mode. The default value is false, which indicates that the preempt mode is disabled.
                            - If the preempt mode is enabled, the local media stream preempts the high priority over other users. The priority of the media stream whose priority is taken becomes normal. After the user whose priority is taken leaves the room, other users still keep the normal priority.
                            - If the preempt mode is disabled, and a user in the room has a high priority. After that, the high priority of the local client remains invalid and is still normal.
     * @return
            - 0: Success.
            - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 设置本地用户的媒体流优先级。
     * <br>如果某个用户的优先级为高，那么该用户媒体流的优先级就会高于其他用户，弱网环境下 SDK 会优先保证其他用户收到的、高优先级用户的媒体流的质量。
     * @note
     * - 请在加入房间（joinChannel）前调用此方法。
     * - 快速切换房间 （switchChannel） 后，媒体优先级会恢复为默认值，即普通优先级。
     * - 一个音视频房间中只有一个高优先级的用户。建议房间中只有一位用户调用 setLocalMediaPriority 将本端媒体流设为高优先级，否则需要开启抢占模式，保证本地用户的高优先级设置生效。
     * @param priority      本地用户的媒体流优先级，默认为 #kNERtcMediaPriorityNormal 。详细信息请参考 #NERtcMediaPriorityType 。
     * @param is_preemptive 是否开启抢占模式。默认为 false，即不开启。
                            - 抢占模式开启后，本地用户可以抢占其他用户的高优先级，被抢占的用户的媒体优先级变为普通优先级，在抢占者退出房间后，其他用户的优先级仍旧维持普通优先级。
                            - 抢占模式关闭时，如果房间中已有高优先级用户，则本地用户的高优先级设置不生效，仍旧为普通优先级。
     * @return
            - 0: 方法调用成功；
            - 其他: 方法调用失败。
     * @endif
     */
    virtual int setLocalMediaPriority(NERtcMediaPriorityType priority, bool is_preemptive) = 0;

    /** 
     * @if English
     * Sets parameters for audio and video calls. You can configure the SDK through JSON to provide features like technology review and special customization. Publicizes JSON options in a standardized way. 
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
     * Sets the audio recording format. 
     * <br>The method is used to set audio recording format of \ref nertc::INERtcAudioFrameObserver::onAudioFrameDidRecord "onAudioFrameDidRecord" callback.
     * @note 
     * - The method can be called before or after a user joins a room.
     * - Stops listening and sets the value as empty. 
     * @param format The sample rate and channels of data returned in the  *onAudioFrameDidRecord*. A value of NULL is allowed. The default value is NULL.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
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
    virtual int setRecordingAudioFrameParameters(NERtcAudioFrameRequestFormat *format) = 0;

    /** 
     * @if English
     * Sets the audio playback format.
     * <br>The method is used to set audio recording format of \ref nertc::INERtcAudioFrameObserver::onAudioFrameDidRecord "onAudioFrameDidRecord" callback. 
     * @note
     * - The method can be called or modified before or after a user joins a room.
     * - Stops listening and sets the value as empty.
     * @param format The sample rate and channels of data returned in the  *onAudioFrameWillPlayback*. A value of NULL is allowed. The default value is NULL.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 设置播放的声音格式。
     * <br>该方法设置 \ref nertc::INERtcAudioFrameObserver::onAudioFrameWillPlayback "onAudioFrameWillPlayback" 回调的播放声音格式。
     * @note
     * - 该方法在加入房间前后均可设置或修改。
     * - 取消监听，重置为空。
     * @param format 指定 *onAudioFrameWillPlayback* 中返回数据的采样率和数据的通道数。允许传入 NULL，默认为 NULL。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
     * @endif
     */
    virtual int setPlaybackAudioFrameParameters(NERtcAudioFrameRequestFormat *format) = 0;


    /** 
     * @if English
     * Sets the sample rate of audio mixing stream after the audio is recording and playback.
     * <br>The method is used to set audio recording format of \ref nertc::INERtcAudioFrameObserver::onMixedAudioFrame "onMixedAudioFrame" .
     * @note
     * - The method can be called before or after a user joins a room.
     * - Currently supports setting the sample rate only.
     * - If you do not call the interface to set the data format, the sample rate in the callback return the default value set by the SDK. 
     * @param sample_rate   The sample rate of data returned in  *onMixedAudioFrame*. Only 8000, 16000, 32000, 44100, and 48000 are supported. 
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
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
	virtual int setMixedAudioFrameParameters(int sample_rate) = 0;

    /** 
     * @if English
     * Registers the audio observer object.
     * <br>The method is used to set audio capture or play PCM data callbacks. You can use the method to process audios. You need to register callbacks with this method when engine needs to trigger callbacks of \ref nertc::INERtcAudioFrameObserver::onAudioFrameDidRecord "onAudioFrameDidRecord" or \ref nertc::INERtcAudioFrameObserver::onAudioFrameWillPlayback "onAudioFrameWillPlayback". 
     * @param observer  The object instance. If you pass in NULL, you cancel the registration and clear the settings of NERtcAudioFrameRequestFormat.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 注册语音观测器对象。
     * <br>该方法用于设置音频采集和播放PCM回调，可用于声音处理等操作。当需要引擎给出 \ref nertc::INERtcAudioFrameObserver::onAudioFrameDidRecord "onAudioFrameDidRecord" 或 \ref nertc::INERtcAudioFrameObserver::onAudioFrameWillPlayback "onAudioFrameWillPlayback" 回调时，需要使用该方法注册回调。
     * @param observer  接口对象实例。如果传入 NULL，则取消注册，同时会清理NERtcAudioFrameRequestFormat相关设置。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
     * @endif
     */
    virtual int setAudioFrameObserver(INERtcAudioFrameObserver *observer) = 0;

    /** 
     * @if English
     * Starts recording an audio dump file. Audio dump files can be used to analyze audio issues.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * 开始记录音频 dump。 音频 dump 可用于分析音频问题。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
     * @endif
     */
    virtual int startAudioDump() = 0;
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
     * @if English
     * Starts playing a music file. 
     * <br>This method mixes the specified local or online audio file with the audio stream captured by the audio devices.
     * - Supported audio formats: MP3, M4A, AAC, 3GP, WMA, and WAV. Files that are stored in local or online URLs are supported.
     * - After you successfully call the method, if the playback status is changed, the local triggers \ref nertc::IRtcEngineEventHandlerEx::onAudioMixingStateChanged "onAudioMixingStateChanged"  callbacks. 
     * @note 
     * - You can call this method after joining a room.
     * - Since V4.3.0, if you call this method to play a music file during a call, and manually set the playback volume of the audio mixing and the sent volume, the setting is used when you call the method again during the current call.
     * @param[in] option        Options of creating audio mixing configurations that include types, full path or URL. For more information, see {@link NERtcCreateAudioMixingOption}.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 开始播放音乐文件。
     * <br>该方法指定本地或在线音频文件来和录音设备采集的音频流进行混音。
     * - 支持的音乐文件类型包括 MP3、M4A、AAC、3GP、WMA 和 WAV 格式，支持本地文件或在线 URL。
     * - 成功调用该方法后，如果播放状态改变，本地会触发  \ref nertc::IRtcEngineEventHandlerEx::onAudioMixingStateChanged "onAudioMixingStateChanged"  回调。
     * @note 
     * - 请在加入房间后调用该方法。
     * - 从 V4.3.0 版本开始， 若您在通话中途调用此接口播放音乐文件时，手动设置了伴音播放音量或发送音量，则当前通话中再次调用时默认沿用此设置。
     * - 在 V4.4.0 版本中，开启或关闭本地音频采集的操作不影响音乐文件在远端的播放，即 enableLocalAudio(false) 后仍旧可以发送伴音。在其他版本中，必须开启音频采集才能发送伴音。
     * @param[in] option        创建混音任务配置的选项，包括混音任务类型、混音文件全路径或URL等。详细信息请参考 {@link NERtcCreateAudioMixingOption}。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int startAudioMixing(NERtcCreateAudioMixingOption *option) = 0;

    /** 
     * @if English
     * Stops playing music files or audio mixing.
     * <br>The method stops playing the audio mixing. You can call the method when you are in a room.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 停止播放音乐文件及混音。
     * <br>该方法停止播放伴奏。请在房间内调用该方法。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int stopAudioMixing() = 0;

    /** 
     * @if English
     * Stops playing music files or audio mixing.
     * <br>The method pauses playing audio mixing. You can call the method when you are in a room.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 暂停播放音乐文件及混音。
     * <br>该方法暂停播放伴奏。请在房间内调用该方法。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int pauseAudioMixing() = 0;

    /** 
     * @if English
     * Resumes playing the audio mixing. 
     * <br>The method resumes audio mixing, and continues playing the audio mixing. You can call the method when you are in a room.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 恢复播放伴奏。
     * <br>该方法恢复混音，继续播放伴奏。请在房间内调用该方法。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int resumeAudioMixing() = 0;

    /** 
     * @if English
     * Adjusts the audio mixing volume for publishing.
     * <br>The method adjusts the volume for publishing of the audio mixing in the audio mixing. You can call the method when you are in a room.
     * @param[in] volume    The audio mixing volume for publishing. Valid values: 0 to 100. The default value of 100 represents the original volume.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 调节伴奏发送音量。
     * <br>该方法调节混音里伴奏的发送音量大小。请在房间内调用该方法。
     * @param[in] volume    伴奏发送音量。取值范围为 0~100。默认 100 为原始文件音量。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int setAudioMixingSendVolume(uint32_t volume) = 0;

    /** 
     * @if English
     * Gets the volume for publishing of audio mixing.
     * <br>The method gets the volume for publishing of the audio mixing in the audio mixing. You can call the method when you are in a room.
     * @param[out] volume   The volume for publishing of the audio mixing. 
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 获取伴奏发送音量。
     * <br>该方法获取混音里伴奏的发送音量大小。请在房间内调用该方法。
     * @param[out] volume   伴奏发送音量。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int getAudioMixingSendVolume(uint32_t *volume) = 0;

    /** 
     * @if English
     * Adjusts the playback volume of the audio mixing.
     * <br>The method adjusts the playback volume of the audio mixing in the audio mixing. You can call the method when you are in a room.
     * @param[in] volume    The volume range of the audio mixing is 0 to 100. The default value of 100 represents the original volume.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 调节伴奏播放音量。
     * <br>该方法调节混音里伴奏的播放音量大小。请在房间内调用该方法。
     * @param[in] volume    伴奏音量范围为 0~100。默认 100 为原始文件音量。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int setAudioMixingPlaybackVolume(uint32_t volume) = 0;

    /** 
     * @if English
     * Gets the playback volume of the audio mixing. 
     * <br>The method gets the playback volume of the audio mixing in the audio mixing. You can call the method when you are in a room.
     * @param[out] volume   The volume of the audio mixing. 
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 获取伴奏播放音量。
     * <br>该方法获取混音里伴奏的播放音量大小。请在房间内调用该方法。
     * @param[out] volume   伴奏播放音量。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int getAudioMixingPlaybackVolume(uint32_t *volume) = 0;

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
     * @note Linux 暂不支持
     * 
     * 获取伴奏时长。
     * <br>该方法获取伴奏时长，单位为毫秒。请在房间内调用该方法。
     * @param[out] duration     伴奏时长，单位为毫秒。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int getAudioMixingDuration(uint64_t *duration) = 0;

    /** 
     * @if English
     * Gets the playback position of the music file.
     * <br>The method gets the playback position of the music file. Unit: milliseconds. You can call the method when you are in a room.
     * @param[out] position     The playback position of the audio mixing file. Unit: milliseconds.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 获取音乐文件的播放进度。
     * <br>该方法获取当前伴奏播放进度，单位为毫秒。请在房间内调用该方法。
     * @param[out] position     伴奏播放进度，单位为毫秒。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int getAudioMixingCurrentPosition(uint64_t *position) = 0;

    /** 
     * @if English
     * Sets the playback position of the music file to a different starting position.
     * <br>The method sets the playback position of the music file to a different starting position. The method allows you to play the music file from the position based on your requirements rather than from the beginning of the music file.
     * @param[in] seek_position     The playback position of the music file. Unit: milliseconds.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 设置音乐文件的播放位置。
     * <br>该方法可以设置音频文件的播放位置，这样你可以根据实际情况播放文件，而非从头到尾播放整个文件。
     * @param[in] seek_position     进度条位置，单位为毫秒。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int setAudioMixingPosition(uint64_t seek_position) = 0;

    /** 
     * @if English
     * Plays a specified audio effect file.
     * - After the method is successfully called, if the playback ends, the onAudioEffectFinished callback is triggered.
     * - Supported audio formats: MP3, M4A, AAC, 3GP, WMA, and WAV. Files that are stored in local or online URLs are supported.
     * @note
     * - You can call this method after joining a room.
     * - You can call the method for multiple times. You can play multiple audio effect files simultaneously by passing in different effect_ids and options. Various audio effects are mixed. To gain optimal user experience, we recommend you to play no more than three audio effect files at the same time.
     * @param[in] effect_id         The ID of the specified audio effect. Each audio effect has a unique ID.
     * @param[in] option            The options of creating audio effect files configurations including types, full path or URL of audio mixing files. For more information, see {@link NERtcCreateAudioEffectOption}.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 播放指定音效文件。
     * - 成功调用该方法后，如果播放结束，本地会触发 onAudioEffectFinished 回调。
     * - 支持的音效文件类型包括 MP3、M4A、AAC、3GP、WMA 和 WAV 格式，支持本地文件和在线 URL。
     * @note
     * - 请在加入房间后调用该方法。
     * - 您可以多次调用该方法，通过传入不同的音效文件的effect_id 和 option ，同时播放多个音效文件，实现音效叠加。为获得最佳用户体验，建议同时播放的音效文件不超过 3 个。
     * @param[in] effect_id         指定音效的 ID。每个音效均有唯一的 ID。
     * @param[in] option            创建音效任务配置的选项，包括混音任务类型、混音文件全路径或 URL 等。详细说明请参考 {@link NERtcCreateAudioEffectOption}。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int playEffect(uint32_t effect_id, NERtcCreateAudioEffectOption *option) = 0;

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
     * @note Linux 暂不支持
     * 
     * 停止播放指定音效文件。
     * <br>请在房间内调用该方法。
     * @param[in] effect_id         指定音效的 ID。每个音效均有唯一的 ID。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int stopEffect(uint32_t effect_id) = 0;

    /** 
     * @if English
     * Stops playing all audio effects.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 停止播放所有音效文件。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int stopAllEffects() = 0;

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
     * @note Linux 暂不支持
     * 
     * 暂停音效文件播放。
     * <br>请在房间内调用该方法。
     * @param[in] effect_id     指定音效的 ID。每个音效均有唯一的 ID。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int pauseEffect(uint32_t effect_id) = 0;

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
     * @note Linux 暂不支持
     * 
     * 恢复播放指定音效文件。
     * <br>请在房间内调用该方法。
     * @param[in] effect_id     指定音效的 ID。每个音效均有唯一的 ID。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int resumeEffect(uint32_t effect_id) = 0;

    /** 
     * @if English
     * Pauses all audio effect files.
     * <br>You can call the method when you are in a room.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 暂停所有音效文件播放。
     * <br>请在房间内调用该方法。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int pauseAllEffects() = 0;

    /** 
     * @if English
     * Resumes playing all audio effects files. 
     * <br>You can call the method when you are in a room.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 恢复播放所有音效文件。
     * <br>请在房间内调用该方法。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int resumeAllEffects() = 0;

    /** 
     * @if English
     * Adjusts the audio effect volume for publishing.
     * The method adjusts the audio effect volume for publishing. You can call the method when you are in a room.
     * @param[in] effect_id         The ID of the specified audio effect. Each audio effect has a unique ID.
     * @param[in] volume            The audio effect volume. Value range: 0 to 100. The default value of 100 represents the original volume.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 调节音效发送音量。
     * 该方法调节音效的发送音量大小。请在房间内调用该方法。
     * @param[in] effect_id         指定音效的 ID。每个音效均有唯一的 ID。
     * @param[in] volume            音效音量范围为 0~100。默认 100 为原始文件音量。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int setEffectSendVolume(uint32_t effect_id, uint32_t volume) = 0;
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
     * @note Linux 暂不支持
     * 
     * 获取音效发送音量。
     * 该方法获取音效的发送音量大小。请在房间内调用该方法。
     * @param[in] effect_id         指定音效的 ID。每个音效均有唯一的 ID。
     * @param[out] volume           音效发送音量。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int getEffectSendVolume(uint32_t effect_id, uint32_t *volume) = 0;

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
     * @note Linux 暂不支持
     * 
     * 设置音效文件播放音量。
     * 请在加入房间后调用该方法。
     * @param[in] effect_id         指定音效的 ID。每个音效均有唯一的 ID。
     * @param[in] volume            音效播放音量。范围为0~100，默认为100。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int setEffectPlaybackVolume(uint32_t effect_id, uint32_t volume) = 0;

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
     * @note Linux 暂不支持
     * 
     * 获取音效文件播放音量。
     * <br>请在加入房间后调用该方法。
     * @param[in] effect_id         指定音效的 ID。每个音效均有唯一的 ID。
     * @param[out] volume           音效播放音量。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int getEffectPlaybackVolume(uint32_t effect_id, uint32_t *volume) = 0;

    /** 
     * @if English
     * Enables or disables local audio capture through the sound card. 
     * @since V4.4.0
     * After the feature is enabled, the audio played by the sound card is integrated into local video streams. In this way, you can publish the audio to the remote side.
     * @note
     * - The method applies to only macOS and Windows.
     * - The capture feature is not supported on the macOS by default. If you need to enable the feature, the app needs to enable a virtual sound card and name the sound card as device_name to pass in the SDK. We recommend that you can use Soundflower as virtual sound card to deliver better audio effect.
     * - You can call this method before or after you join a room.
     * @param[in] enabled       Specifies whether to enable the capture feature through the sound card.
                                - true: Enables audio capture through the sound card.
                                - false: Disables audio capture through the sound card (default). 
     * @param[in] device_name   The device name of the sound card. The name is set as NULL by default, which indicates capturing through the current sound card. <br>The parameter applies to macOS platform only. <br>If users use virtual sound cards such as “Soundflower”, you can set the sound card name of virtual card as parameter. In this way, the SDK finds the corresponding device of virtual sound cards and starts capturing.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 开启或关闭声卡采集。
     * @since V4.4.0
     * 启用声卡采集功能后，声卡播放的声音会被合到本地音频流中，从而可以发送到远端。
     * @note
     * - 该方法仅适用于 macOS 和 Windows 平台。
     * - macOS 系统默认声卡不支持采集功能，如需开启此功能需要 App 自己启用一个虚拟声卡，并将该虚拟声卡的名字作为 device_name 传入 SDK。 网易云信建议使用 Soundflower 作为虚拟声卡，以获得更好的音频效果。
     * - 该方法在加入房间前后都能调用。
     * @param[in] enabled       是否开启声卡采集功能。
                                - true: 开启声卡采集。
                                - false: （默认）关闭声卡采集。
     * @param[in] device_name   声卡的设备名。默认设为 NULL，即使用当前声卡采集。<br>该参数仅适用于 macOS 平台。<br>如果用户使用虚拟声卡，如 “Soundflower”，可以将虚拟声卡名称 “Soundflower” 作为参数，SDK 会找到对应的虚拟声卡设备，并开始采集。
     * @return
     * - 0: 方法调用成功
     * - 其他: 方法调用失败
     * @endif
     */
    virtual int enableLoopbackRecording(bool enabled, const char *device_name) = 0;

    /** 
     * @if English
     * Adjusts the volume of captured signals of sound cards.
     * @since V4.4.0
     * After calling sound card capturing by calling \ref nertc::IRtcEngineEx::enableLoopbackRecording "enableLoopbackRecording", you can call the method to adjust the volume of captured signals of sound cards.
     * @param[in] volume        The captured signals volume through sound cards. Value range: 0 to 100. The default value of 100 represents the original volume.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 调节声卡采集信号音量。
     * @since V4.4.0
     * 调用 \ref nertc::IRtcEngineEx::enableLoopbackRecording "enableLoopbackRecording" 开启声卡采集后，你可以调用该方法调节声卡采集的信号音量。
     * @param[in] volume        声卡采集信号音量。取值范围为 [0,100]。默认值为 100，表示原始音量。
     * @return
     * - 0: 方法调用成功
     * - 其他: 方法调用失败
     * @endif
     */
    virtual int adjustLoopbackRecordingSignalVolume(int volume) = 0;

    /** 
     * @if English
     * Enables or disables in-ear monitoring.
     * @note
     * - You can call the method when you are in a room.
     * - After in-ear monitoring is enabled, you must wear a headset or earpieces to use the in-ear monitoring feature. We recommend that you listen for changes of playback devices through  \ref IRtcEngineEventHandlerEx::onAudioDeviceStateChanged  "onAudioDeviceStateChanged" and  \ref IRtcEngineEventHandlerEx::onAudioDefaultDeviceChanged  "onAudioDefaultDeviceChanged". Only when the device changes to headset, you can enable in-ear monitoring.
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
     * - 开启耳返功能后，必须连接上耳机或耳麦，才能正常使用耳返功能。建议通过 \ref IRtcEngineEventHandlerEx::onAudioDeviceStateChanged  "onAudioDeviceStateChanged" 及 \ref    IRtcEngineEventHandlerEx::onAudioDefaultDeviceChanged  "onAudioDefaultDeviceChanged" 监听播放设备的变化，当监听到播放设备切换为耳机时才开启耳返。
     * @param[in] enabled   开启或关闭。
     * @param[in] volume    耳返音量。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int enableEarback(bool enabled, uint32_t volume) = 0;

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
    virtual int setEarbackVolume(uint32_t volume) = 0;

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
    virtual int setStatsObserver(IRtcMediaStatsObserver *observer) = 0;

    /** 
     * @if English
     * Enables volume indication for the speaker.
     * <br>The method allows the SDK to report to the app the information about the volume of the user that pushes local streams and the remote user (up to three users) that has the highest instantaneous volume. The information about the current speaker and the volume is reported.
     * <br>If this method is enabled, when a user joins a room and pushes streams, the SDK triggers \ref IRtcEngineEventHandlerEx::onRemoteAudioVolumeIndication "onRemoteAudioVolumeIndication" based on the preset time intervals. 
     * @param enable        Whether to prompt the speaker volume.
     * @param interval      The time interval at which volume prompt is displayed. Unit: milliseconds. The value must be the multiples of 100 milliseconds. 
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * 启用说话者音量提示。
     * <br>该方法允许 SDK 定期向 App 反馈本地发流用户和瞬时音量最高的远端用户（最多 3 位）的音量相关信息，即当前谁在说话以及说话者的音量。
     * <br>启用该方法后，只要房间内有发流用户，无论是否有人说话，SDK 都会在加入房间后根据预设的时间间隔触发\ref IRtcEngineEventHandlerEx::onRemoteAudioVolumeIndication  "onRemoteAudioVolumeIndication"回调。
     * @param enable        是否启用说话者音量提示。
     * @param interval      指定音量提示的时间间隔，单位为毫秒。必须设置为 100 毫秒的整数倍值。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
     * @endif
     */
    virtual int enableAudioVolumeIndication(bool enable, uint64_t interval) = 0; 

    /** 
     * @if English
     * Shares screens through specifying regions. Shares a certain screen or part of region of a screen. Users need to specify the screen region they wants to share in the method.
     * <br>When calling the method, you need to specify the screen region to be shared, and share the overall frame of the screen or designated regions. 
     * <br>If you join a room and successfully call this method to enable the substream, the onUserSubStreamVideoStart and setExcludeWindowList callback is remotely triggered.
     * @note
     * - The method applies to Windows only.
     * - The method enables video substreams.
     * @param  screen_rect      The relative position of the screen to virtual screens that is shared. 
     * @param  region_rect      The relative position of shared screen to the full screen. If you set the shared region beyond the frame of the screen, only content within the screen is shared. If you set the value of width or height as 0, the full screen is shared. 
     * @param  capture_params   The configurations of screen sharing. 
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * 
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 开启屏幕共享，共享范围为指定屏幕的指定区域。
     * <br>调用该方法时，可以选择共享整个虚拟屏、指定屏幕，或虚拟屏、整个屏幕的某些区域范围。
     * <br>此方法调用成功后，远端触发 onUserSubStreamVideoStart 和 setExcludeWindowList 回调。
     *  @note
     * - 该方法仅适用于 Windows。macOS 平台请使用方法 startScreenCaptureByDisplayId。
     * - 该方法需要在加入房间后调用。
     * @param  screen_rect      指定待共享的屏幕相对于虚拟屏的位置。
     * @param  region_rect      指定待共享区域相对于整个屏幕屏幕的位置。如果设置的共享区域超出了屏幕的边界，则只共享屏幕内的内容；如果将 width 或 height 设为 0, 则共享整个屏幕。
     * @param  capture_params   屏幕共享的编码参数配置。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
     * @endif
     */
    virtual int startScreenCaptureByScreenRect(const NERtcRectangle& screen_rect, const NERtcRectangle& region_rect, const NERtcScreenCaptureParameters& capture_params) = 0;

    /**
     * @if English
     * Enables screen sharing by specifying the ID of the screen. The content of screen sharing is sent by substreams.
     * <br>If you join a room and call this method to enable the substream, the onUserSubStreamVideoStart and onScreenCaptureStatus callback is remotely triggered.
     * @note 
     * - The method applies to only macOS. 
     * - The method enables video substreams.
     * @param  display_id       The ID of the screen to be shared. Developers need to specify the screen they share through the parameters.
     * @param  region_rect      The relative position of shared screen to the full screen.
     * @param  capture_params   The configurations of screen sharing.
     * @return
     * - 0: Success.
     * - Other values: Failure.

     *  @endif
     *  @if Chinese
     * @note Linux 暂不支持
     * 
     * 通过指定屏幕 ID 开启屏幕共享，屏幕共享内容以辅流形式发送。
     * <br>此方法调用成功后，远端触发 onUserSubStreamVideoStart 回调。
     * @note
     * - 该方法仅适用于 macOS。Windows 平台请使用方法 startScreenCaptureByScreenRect。
     * - 该方法需要在加入房间后设置。
     * @param  display_id       指定待共享的屏幕 ID。开发者需要自行实现枚举屏幕 ID 的方法，并通过该参数指定需要共享的屏幕。
     * @param  region_rect      指定待共享的区域相对于整个窗口的位置。如果设置的共享区域超出了窗口的边界，则只共享窗口内的内容；如果宽或高为 0，则共享整个窗口。
     * @param  capture_params   屏幕共享的参数配置，包括码率、帧率、编码策略、屏蔽窗口列表等。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
     * @endif
     */
    virtual int startScreenCaptureByDisplayId(unsigned int display_id, const NERtcRectangle& region_rect, const NERtcScreenCaptureParameters& capture_params) = 0;

    /** 
     * @if English
     * Enables screen sharing by specifying the ID of the window. The content of screen sharing is sent by substreams.
     * <br>If you join a room and call this method to enable the substream, the onUserSubStreamVideoStart and setExcludeWindowList callback is remotely triggered.
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
     * @note Linux 暂不支持
     * 
     * 通过指定窗口 ID 开启屏幕共享，屏幕共享内容以辅流形式发送。
     * <br>调用该方法时需要指定待共享的屏幕 ID，共享该屏幕的整体画面或指定区域。
     * <br>此方法调用成功后：
     * - Windows 平台远端触发 onUserSubStreamVideoStop 和 onScreenCaptureStatus 回调。
     * - macOS 平台远端触发 onUserSubStreamVideoStop 回调。
     * @note
     * - 该方法适用于 Windows 和 macOS。
     * - 该方法需要在加入房间后调用。
     * @param  window_id        指定待共享的窗口 ID。
     * @param  region_rect      指定待共享的区域相对于整个窗口的位置。如果设置的共享区域超出了窗口的边界，则只共享指定区域中窗口内的内容；如果宽或高为 0，则共享整个窗口。
     * @param  capture_params   屏幕共享的参数配置，包括码率、帧率、编码策略、屏蔽窗口列表等。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
     * @endif
     */
    virtual int startScreenCaptureByWindowId(source_id_t window_id, const NERtcRectangle& region_rect, const NERtcScreenCaptureParameters& capture_params) = 0;

    /** 
     * @if English
     * When sharing a screen or window, updates the shared region.
     * @param  region_rect      The relative position of shared screen to the full screen. If you set the shared region beyond the frame of the screen, only content within the screen is shared. If you set width or height as 0, the full screen is shared.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * 
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 在共享屏幕或窗口时，更新共享的区域。
     * <br>在 Windows 平台中，远端会触发 onScreenCaptureStatus 回调。
     * @param  region_rect      指定待共享的区域相对于整个窗口或屏幕的位置。如果设置的共享区域超出了边界，则只共享指定区域中，窗口或屏幕内的内容；如果宽或高为 0，则共享整个窗口或屏幕。
     * @return
     * - 0: 方法调用成功。
     * - 其他: 方法调用失败。
     * @endif
     */
    virtual int updateScreenCaptureRegion(const NERtcRectangle& region_rect) = 0;

    /** 
     * @if English
     * Stops screen sharing.
     * <br>If you use the method to disable the substream after joining a room, the onUserSubStreamVideoStop callback is remotely triggered.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * 
     * @endif
     * @if Chinese 
     * @note Linux 暂不支持
     * 
     * 停止屏幕共享。
     * <br>此方法调用成功后：
     * - Windows 平台远端触发 onUserSubStreamVideoStop 和 onScreenCaptureStatus 回调。
     * - macOS 平台远端触发 onUserSubStreamVideoStop 回调。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
     * @endif
     */
    virtual int stopScreenCapture() = 0;

    /** 
     * @if English
     * Pauses screen sharing.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * 
     * @endif
     * @if Chinese 
     * @note Linux 暂不支持
     * 
     * 暂停屏幕共享。
     * - 暂停屏幕共享后，共享区域内会持续显示暂停前的最后一帧画面，直至通过 resumeScreenCapture 恢复屏幕共享。
     * - 在 Windows 平台中，远端会触发 onScreenCaptureStatus 回调。
     * @return
     * - 0: 方法调用成功
     * - 其他: 方法调用失败
     * @endif
     */
    virtual int pauseScreenCapture() = 0;

    /** 
     * @if English
     * Resumes screen sharing. 
     * @return
     * - 0: Success.
     * - Other values: Failure. 
     * @endif
     * @if Chinese 
     * @note Linux 暂不支持
     * 
     * 恢复屏幕共享。
     * <br>在 Windows 平台中，远端会触发 onScreenCaptureStatus 回调。
     * @return
     * - 0: 方法调用成功
     * - 其他: 方法调用失败
     * @endif
     */
    virtual int resumeScreenCapture() = 0;


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
     * @note Linux 暂不支持
     * 
     * 设置共享整个屏幕或屏幕指定区域时，需要屏蔽的窗口列表。
     * <br>开启屏幕共享时，可以通过 NERtcScreenCaptureParameters 设置需要屏蔽的窗口列表；在 Windows 平台中，开发者可以在开启屏幕共享后，通过此方法动态调整需要屏蔽的窗口列表。被屏蔽的窗口不会显示在屏幕共享区域中。
     * @note 
     * - 在 Windows 平台中，该接口在屏幕共享过程中可动态调用；在 macOS 平台中，该接口需要在开启屏幕共享之前，即 startScreenCaptureByDisplayId 之前调用。
     * - 在 Windows 平台中，某些窗口在被屏蔽之后，如果被置于图层最上层，此窗口图像可能会黑屏。此时会触发 onScreenCaptureStatus.kScreenCaptureStatusCovered 回调，建议应用层在触发此回调时提醒用户将待分享的窗口置于最上层。
     * @since V4.2.0
     * @param  window_list      需要屏蔽的窗口 ID 列表。
     * @param  count            需屏蔽的窗口的数量。
     * @return
     * - 0: 方法调用成功
     * - 其他: 方法调用失败
     * @endif
     */
    virtual int setExcludeWindowList(source_id_t* window_list, int count) = 0;

    /** 
     * @if English
     * Enables or disables the external video source.
     * <br>When you enable the external video source through the method, you need to set kNERtcExternalVideoDeviceID as the ID of external video source with IVideoDeviceManager::setDevice kNERtcExternalVideoDeviceID method.
     * @note The method enables the internal engine, which is still valid after you call \ref IRtcEngine::leaveChannel "leaveChannel".
     * @param[in] enabled       Specifies whether input external video source data. 
     * - true: Enables external video source. 
     * - false: Disables the external video source (default).
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * 开启或关闭外部视频源数据输入。
     * <br>通过该方法启用外部视频数据输入功能时，需要通过 IVideoDeviceManager::setDevice 设置 kNERtcExternalVideoDeviceID 为外部视频输入源 ID。
     * @note 该方法设置内部引擎为启用状态，在 \ref IRtcEngine::leaveChannel "leaveChannel" 后仍然有效。
     * @param[in] enabled       是否外部视频源数据输入:
     * - true: 开启外部视频源数据输入；
     * - false: 关闭外部视频源数据输入 (默认)。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int setExternalVideoSource(bool enabled) = 0;

    /** 
     * @if English
     * Pushes the external video frames.
     * <br>The method actively pushes the data of video frames that are encapsulated with the NERtcVideoFrame class to the SDK. Make sure that you have already called setExternalVideoSource with a value of true before you call this method. Otherwise, an error message is repeatedly prompted if you call the method.
     * @note The method enables the internal engine, which is invalid after you call \ref IRtcEngine::leaveChannel "leaveChannel".
     * @param[in] frame         The video frame data.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * 推送外部视频帧。
     * <br>该方法主动将视频帧数据用 NERtcVideoFrame 类封装后传递给 SDK。 请确保在你调用本方法前已调用 setExternalVideoSource，并将参数设为 true，否则调用本方法后会一直报错。
     * @note 该方法设置内部引擎为启用状态，在 \ref IRtcEngine::leaveChannel "leaveChannel" 后不再有效。
     * @param[in] frame         视频帧数据。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int pushExternalVideoFrame(NERtcVideoFrame* frame) = 0;


    /** 
     * @if English
     * Enables or disables the external audio stream source.
     * <br>After you call the method, the setting becomes invalid if you choose audio input device or a sudden restart occurs. After the method is called, you can call pushExternalAudioFrame to send the pulse-code modulation (PCM) data.
     * @note 
     * - You can call this method before joining a room.
     * - The method enables the internal engine. After enabled, the virtual component works instead of the physical microphones. The setting remains unchanged after the leaveChannel method is called. If you want to disable the feature, you must disable the setting before next call starts.
     * - After you enable the external audio data input, some functionalities of the speakerphone supported by the SDK are replaced by the external audio source. Settings that are applied to the microphones become invalid or do not take effect in calls. For example, you can hear the external data input when you use loopback for testing.
     * @param[in] enabled       Specifies whether to input external data.
     * - true: Enables external data input.
     * - false: Disables the external data input(default).
     * @param[in] sample_rate   The sample rate of data. You need to input following data in the same sample rate.  Note: If you call the method to disable the functionality, you can pass in a random valid value. In this case, the setting does not take effect.
     * @param[in] channels      The number of channels. You need to input following data in the same number of channels. Note: If you call the method to disable the functionality, you can pass in a random valid value. In this case, the setting does not take effect.
     * Valid values:
     * - 1: Mono sound.
     * - 2: Stereo sound.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 开启或关闭外部音频源数据输入。
     * <br>当该方法调用成功后，音频输入设备选择和异常重启会失效。调用成功后可以使用 pushExternalAudioFrame 接口发送音频 PCM 数据。
     * @note 
     * - 请在加入房间前调用该方法。
     * - 该方法设置内部引擎为启用状态，启动时将用虚拟设备代替麦克风工作，在leaveChannel后仍然有效。如果需要关闭该功能，需要在下次通话前调用接口关闭外部音频数据输入功能。
     * - 启用外部音频数据输入功能后，SDK 内部实现部分麦克风由外部输入数据代替，麦克风相关的设置会失败或不在通话中生效。例如进行 loopback 检测时，会听到输入的外部数据。
     * @param[in] enabled       是否外部数据输入:
     * - true: 开启外部数据输入；
     * - false: 关闭外部数据输入 (默认)。
     * @param[in] sample_rate   数据采样率，后续数据传入需要按该格式传入。 注意：调用接口关闭功能时可传入任意合法值，此时设置不会生效。
     * @param[in] channels      数据声道数，后续数据传入需要按该格式传入。注意：调用接口关闭功能时可传入任意合法值，此时设置不会生效。
     * 可设置为：
     * - 1：单声道。
     *  2：双声道。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int setExternalAudioSource(bool enabled, int sample_rate, int channels) = 0;

    /** 
     * @if English
     * Pushes the external audio data input.
     * <br>Pushes the audio frame data captured from the external audio source to the internal audio engine. If you enable the external audio data source by calling setExternalAudioSource, you can use pushExternalAudioFrame to send audio PCM data.
     * @note 
     * - This method can be called only if a user joins a room.
     * - We recommend that you set the duration of data frames to match a cycle of 10 ms. 
     * - External input data frame consists of the data duration and call duration. 
     * - The method becomes invalid if the audio input device is turned off. For example, disable local audio, end calls, and shut off the microphone test before calls.
     * @param[in] frame         The data of frame cannot exceed 7680 bytes in length.
     * - External input data frame consists of the data duration and call duration. 
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 推送外部音频数据输入。
     * <br>将外部音频数据帧推送给内部引擎。 通过 setExternalAudioSource 启用外部音频数据输入功能成功后，可以使用 pushExternalAudioFrame 接口发送音频 PCM 数据。
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
    virtual int pushExternalAudioFrame(NERtcAudioFrame* frame) = 0;

    /** 
     * @if English
     * Sets external audio rendering. 
     * <br>The method is suitable for scenarios that require personalized audio rendering. By default, the setting is disabled. If you choose an audio playback device or a sudden restart occurs, the setting becomes invalid. After you call the method, you can use pullExternalAudioFrame to get audio PCM data.
     * @note
     * - You can call this method before joining a room.
     * - The method enables the internal engine. The virtual component works instead of the physical speaker. The setting remains valid after you call the leaveChannel method. If you want to disable the functionality, you must disable the functionality before the next call starts.
     * - After you enable the external audio rendering, some functionalities of the speakerphone supported by the SDK are replaced by the external audio source. Settings that are applied to the speakerphone become invalid or do not take effect in calls. For example, external rendering is required to play the external audio when you use loopback for testing.
     * @param[in] enabled       Specifies whether to output external data.
     * - true: Enables external data rendering.
     * - false: Disables the external data rendering (default).
     * @param[in] sample_rate    The sample rate of data. You need to input following data in the same sample rate. 
     * Note: If you call the method to disable the functionality, you can pass in a random valid value. In this case, the setting does not take effect. 
     * @param[in] channels       The number of data channels. You need to return following data in the same number of channels. 
     * Note: If you call the method to disable the functionality, you can pass in a random valid value. In this case, the setting does not take effect.
     * Valid values:
     * - 1: Mono sound.
     * - 2: Stereo sound.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 设置外部音频渲染。
     * <br>该方法适用于需要自行渲染音频的场景。默认为关闭状态。当该方法调用成功后，音频播放设备选择和异常重启失效。 调用成功后可以使用 pullExternalAudioFrame 接口获取音频 PCM 数据。
     * @note
     * - 请在加入房间前调用该方法。
     * - 该方法设置内部引擎为启用状态，启动时将用虚拟设备代替扬声器工作，在leaveChannel后仍然有效。如果需要关闭该功能，需要在下次通话前调用接口关闭外部音频数据渲染功能。
     * - 启用外部音频渲染功能后，SDK 内部实现部分扬声器由外部输入数据代替，扬声器相关的设置会失败或不在通话中生效。例如进行 loopback 检测时，需要由外部渲染播放。
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
    virtual int setExternalAudioRender(bool enabled, int sample_rate, int channels) = 0;

    /** 
     * @if English
     * Pulls the external audio data.
     * <br>The method pulls the audio data from the internal audio engine. After you enable the external audio data rendering functionality by calling setExternalAudioRender, you can use pullExternalAudioFrame to get the audio PCM data.
     * @note
     * - This method can be called only if a user joins a room.
     * - We recommend that you set the duration of data frames to match a cycle of 10 ms.
     * - The method becomes invalid if the audio rendering device is turned off. In this case, no data is returned. For example, calls end, and the speakerphone is shut off before calls.
     * @param[out] data         Data pointer. The SDK internally copies data into data. 
     * @param[in] len           The size of the audio data that are pulled. Unit: bytes.
     * - We recommend that the duration of the audio data at least last 10 ms, and the data size cannot exceed 7,680 bytes.
     * - Formula: len = sampleRate/1000 × 2 × channels × duration of the audio data in milliseconds.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 拉取外部音频数据。
     * <br>该方法将从内部引擎拉取音频数据。 通过 setExternalAudioRender 启用外部音频数据渲染功能成功后，可以使用 pullExternalAudioFrame 接口获取音频 PCM 数据。
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
    virtual int pullExternalAudioFrame(void* data, int len) = 0;

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
     * @param[out] build        编译号。
     * @return 当前的 SDK 版本号，格式为字符串，如1.0.0.
     * @endif
     */
    virtual const char* getVersion(int* build) = 0;

    /** 
     * @if English
     * Check the error description of specified error codes.
     * @note The method is currently invalid. Returns the value of empty only. Please check returned error codes and specific error descriptions in the \ref IRtcEngineEventHandler::onError "onError" .
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
     * After the method is successfully called, the current user can receive the notification about the status of the live stream.
     * @note
     * - The method is applicable to only live streaming.
     * - You can call the method in a room. The method is valid in calls.
     * - Only one address for the relayed stream is added in each call. You need to call the method for multiple times if you want to push many streams. An RTC room with the same channelid can create three different streaming tasks.
     * - After the method is successfully called, the current user will receive related-status notifications of the live stream. 
     * @param[in] info indicates information of live task. For more information, see \ref NERtcLiveStreamTaskInfo "NERtcLiveStreamTaskInfo". 
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 添加房间推流任务，成功添加后当前用户可以收到该直播流的状态通知。
     * @note
     * - 该方法仅适用直播场景。
     * - 请在房间内调用该方法，该方法在通话中有效。
     * - 该方法每次只能增加一路旁路推流地址。如需推送多路流，则需多次调用该方法。同一个音视频房间（即同一个 channelid）可以创建 3 个不同的推流任务。
     * - 成功添加推流任务后，当前用户会收到该直播流的相关状态通知。
     * @param[in] info 直播任务信息。详细信息请参考 \ref NERtcLiveStreamTaskInfo "NERtcLiveStreamTaskInfo"
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
     * @endif
     */
    virtual int addLiveStreamTask(const NERtcLiveStreamTaskInfo& info) = 0;

    /** 
     * @if English
     * Updates and modifies a push task in a room. 
     * @note
     * - The method is applicable to only live streaming.
     * - You can call the method in a room. The method is valid in calls.
     * @param[in] info indicates information of live task. For more information, see \ref NERtcLiveStreamTaskInfo "NERtcLiveStreamTaskInfo".
     * @return 
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
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
    virtual int updateLiveStreamTask(const NERtcLiveStreamTaskInfo& info) = 0;

    /** 
     * @if English
     * Deletes a push task.
     * @note
     * - The method is applicable to only live streaming.
     * - You can call the method in a room. The method is valid in calls.
     * - When calls stop and all members in the room leave the room, the SDK automatically deletes the streaming task. If some users are still in the room, users who create the streaming task need to delete the streaming task. 
     * @param[in] task_id  The ID of a live streaming task.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
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
    virtual int removeLiveStreamTask(const char* task_id) = 0;

	/** 
     * @if English
     * Sends SEI messages.
     * <br>While the local video stream is pushed, SEI data is also sent to sync some additional information. After SEI data is sent, the receiver can retrieve the content by listening on \ref IRtcEngineEventHandlerEx::onRecvSEIMsg callback.  
     * - Condition: After the video stream (mainstream) is enabled, the function can be invoked.
     * - Data size limits: The SEI data can contain a maximum of 4,096 bytes in size. Sending an SEI message fails if the data exceeds the size limit. If a large amount of data is sent, the video bitrate rises. This degrades the video quality or causes broken video frames.
     * - Frequency limit: we recommend that the maximum video frame rate does not exceed 10 fps.  
     * - Time to take effect: After the method is called, the SEI data is sent from the next frame in the fastest fashion or after the next 5 frames at the slowest pace.
     * @note
     * - The SEI data is transmitted together with the video stream. Frame loss may occur in poor network connection. The SEI data will also get lost. We recommend that you send the data many times within the transmission frequency limits. In this way, the receiver can get the data.
     * - By default, the SEI is transmitted by using the mainstream channel. 
     * @param data      The custom SEI frame data.
     * @param length    The custom SEI data size whose maximum value does not exceed 4096 bytes. 
     * @param type      The type of the stream channel with which the SEI data is transmitted. For more information, see #NERtcVideoStreamType. 
     * @return The value returned. A value of 0 That the operation is successful.
     * - Success: Successfully joins the queue to be sent. The data are sent after the closest video frame. 
     * - failure: Date are limitedly sent for the high sent frequency and the overloaded queue. Or, the maximum data size exceeds 4k.
     * @endif
     * @if Chinese
     * 发送媒体补充增强信息（SEI）。
     * <br>在本端推流传输视频流数据同时，发送流媒体补充增强信息来同步一些其他附加信息。当推流方发送 SEI 后，拉流方可通过监听 \ref IRtcEngineEventHandlerEx::onRecvSEIMsg 的回调获取 SEI 内容。
     * - 调用时机：视频流（主流）开启后，可调用此函数。
     * - 数据长度限制： SEI 最大数据长度为 4096 字节，超限会发送失败。如果频繁发送大量数据会导致视频码率增大，可能会导致视频画质下降甚至卡顿。
     * - 发送频率限制：最高为视频发送的帧率，建议不超过 10 次/秒。
     * - 生效时间：调用本接口之后，最快在下一帧视频数据帧之后发送 SEI 数据，最慢在接下来的 5 帧视频之后发送。
     * @note
     * - SEI 数据跟随视频帧发送，由于在弱网环境下可能丢帧，SEI 数据也可能随之丢失，所以建议在发送频率限制之内多次发送，保证接收端收到的概率。
     * - 调用本接口时，默认使用主流通道发送 SEI。
     * @param data      自定义 SEI 数据。
     * @param length    自定义 SEI 数据长度，最大不超过 4096 字节。
     * @param type      发送 SEI 时，使用的流通道类型。详细信息请参考 #NERtcVideoStreamType 。
     * @return 操作返回值，成功则返回 0
     * - 成功:  成功进入待发送队列，会在最近的视频帧之后发送该数据
     * - 失败:  数据被限制发送，可能发送的频率太高，队列已经满了，或者数据大小超过最大值 4k
	 * @endif
	 */
    virtual int sendSEIMsg(const char* data, int length, NERtcVideoStreamType type) = 0;

	/** 
     * @if English
     * Sends SEI messages.
     * <br>While the local video stream is pushed, SEI data is also sent to sync some additional information. After SEI data is sent, the receiver can retrieve the content by listening on \ref IRtcEngineEventHandlerEx::onRecvSEIMsg callback.
     * - Condition: After the video stream (mainstream) is enabled, the function can be invoked.
     * - Data size limits: The SEI data can contain a maximum of 4,096 bytes in size. Sending an SEI message fails if the data exceeds the size limit. If a large amount of data is sent, the video bitrate rises. This degrades the video quality or causes video frames freezes.
     * - Frequency limit: we recommend that the maximum video frame rate does not exceed 10 fps. 
     * - Time to take effect: After the method is called, the SEI data is sent from the next frame in the fastest fashion or after the next 5 frames at the slowest pace.
     * @note
     * - The SEI data is transmitted together with the video stream. Frame loss may occur in poor network connection. The SEI data will also get lost. We recommend that you send the data many times within the transmission frequency limits. In this way, the receiver can get the data.
     * - By default, the SEI is transmitted by using the mainstream channel.
     * @param data      The custom SEI frame data.
     * @param length    The custom SEI data size whose maximum value does not exceed 4096 bytes.
     * @note            The API is disabled in the audio-only SDK. If you need to use the API, you can download the standard SDK from the official website of CommsEase and replace the audio-only SDK.
     * @return The value returned. A value of 0 That the operation is successful.
     * - Success: Successfully joins the queue to be sent. The data are sent after the closest video frame.
     * - Failure: Date are limitedly sent for the high sent frequency, the overloaded queue and the maximum data size exceeding 4k.
     * @endif
     * @if Chinese
     * 发送媒体补充增强信息（SEI）。
     * 在本端推流传输视频流数据同时，发送流媒体补充增强信息来同步一些其他附加信息。当推流方发送 SEI 后，拉流方可通过监听 \ref IRtcEngineEventHandlerEx::onRecvSEIMsg 的回调获取 SEI 内容。
     * - 调用时机：视频流（主流）开启后，可调用此函数。
     * - 数据长度限制： SEI 最大数据长度为 4096 字节，超限会发送失败。如果频繁发送大量数据会导致视频码率增大，可能会导致视频画质下降甚至卡顿。
     * - 发送频率限制：最高为视频发送的帧率，建议不超过 10 次/秒。
     * - 生效时间：调用本接口之后，最快在下一帧视频数据帧之后发送 SEI 数据，最慢在接下来的 5 帧视频之后发送。
     * @note
     * - SEI 数据跟随视频帧发送，由于在弱网环境下可能丢帧，SEI 数据也可能随之丢失，所以建议在发送频率限制之内多次发送，保证接收端收到的概率。
     * - 调用本接口时，默认使用主流通道发送 SEI。
     * @param data      自定义 SEI 数据。
     * @param length    自定义 SEI 数据长度，最大不超过 4096 字节。
     * @note 纯音频SDK禁用该接口，如需使用请前往云信官网下载并替换成视频SDK
     * @return 操作返回值，成功则返回 0
     * - 成功:  成功进入待发送队列，会在最近的视频帧之后发送该数据
     * - 失败:  数据被限制发送，可能发送的频率太高，队列已经满了，或者数据大小超过最大值 4k
	 * @endif
	 */
	virtual int sendSEIMsg(const char* data, int length) = 0;

	/** 
     * @if English
     * Adds a watermark image to the local video.
     * @note
     * - The setLocalCanvasWatermarkConfigs method applies to the local video canvas and does not affect the video stream. If the canvas is removed, the watermark will be automatically deleted.
     * - Before you set a watermark, you must first set the canvas by calling related methods.
     * - Watermark-related methods are currently unsupported on the macOS platform.
     * @param type      The type of video streams. You can set the value to mainstream or substream. For more information, see #NERtcVideoStreamType.
     * @param config    The configuration of the watermark for the canvas. You can set text watermark, image watermark, and timestamp watermark. A value of null is set to remove the watermark. For more information, see \ref NERtcCanvasWatermarkConfig.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 添加本地视频画布水印。
     * @note
     * - setLocalCanvasWatermarkConfigs 方法作用于本地视频画布，不影响视频流。画布被移除时，水印也会自动移除。
     * - 设置水印之前，需要先通过画布相关方法设置画布。
     * - macOS 暂不支持水印相关方法。
     * @param type      视频流类型。支持设置为主流或辅流。详细信息请参考 #NERtcVideoStreamType 。
     * @param config    画布水印设置。支持设置文字水印、图片水印和时间戳水印，设置为 null 表示清除水印。
     * 详细信息请参考 \ref NERtcCanvasWatermarkConfig 。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
	 * @endif
	 */
	virtual int setLocalCanvasWatermarkConfigs(NERtcVideoStreamType type, NERtcCanvasWatermarkConfig &config) = 0;

	/** 
     * @if English
     * Adds a watermark to the remote video canvas.
     * @note
     * - setRemoteCanvasWatermarkConfigs method applies to the local video canvas and does not affect the video stream. If the canvas is removed, the watermark will be automatically deleted.
     * - Before you set a watermark, you must first set the canvas by calling related methods.
     * - Watermark-related methods are currently unsupported on the macOS platform.
     * @param uid       The ID of a remote user.
	 * @param type      The type of video streams. You can set the value to mainstream or substream. For more information, see #NERtcVideoStreamType.
	 * @param config    The configuration of the watermark for the canvas. You can set text watermark, image watermark, and timestamp watermark. A value of null is set to remove the watermark.
     * For more information, see \ref NERtcCanvasWatermarkConfig.  
     * @return
     - 0: Success.
     - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 添加远端视频画布水印。
     * @note
     * - setRemoteCanvasWatermarkConfigs 方法作用于远端视频画布，不影响视频流。画布被移除时，水印也会自动移除。
     * - 设置水印之前，需要先通过画布相关方法设置画布。
     * - macOS 暂不支持水印相关方法。
     * @param uid       远端用户 ID。
	 * @param type      视频流类型。支持设置为主流或辅流。详细信息请参考 #NERtcVideoStreamType 。
	 * @param config    画布水印设置。支持设置文字水印、图片水印和时间戳水印，设置为 null 表示清除水印。
     * 详细信息请参考 \ref NERtcCanvasWatermarkConfig 。 
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
	 * @endif
	 */
	virtual int setRemoteCanvasWatermarkConfigs(uid_t uid, NERtcVideoStreamType type, NERtcCanvasWatermarkConfig &config) = 0;

	/** 
     * @if English
     * Takes a local video snapshot.
     * <br>The takeLocalSnapshot method takes a local video snapshot on the local substream or local mainstream, and call \ref NERtcTakeSnapshotCallback "NERtcTakeSnapshotCallback::onTakeSnapshotResult" callback to return data of snapshot screen.
     * @note
     * - Before you call the method to capture the snapshot from the mainstream, you must first call startVideoPreview or enableLocalVideo, and joinChannel.
     * - Before you call the method to capture the snapshot from the substream, you must first call startScreenCapture, and joinChannel. 
     * - You can set text, timestamp, and image watermarks at the same time. If different types of watermarks overlap, the layers override previous layers following image, text, and timestamp.
     * @param stream_type       The video stream type of the snapshot. You can set the value to mainstream or substream. For more information, see #NERtcVideoStreamType.
     * @param callback          The snapshot callback. For information, see \ref NERtcTakeSnapshotCallback.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 本地视频画面截图。
     * <br>调用 takeLocalSnapshot 截取本地主流或本地辅流的视频画面，并通过 \ref NERtcTakeSnapshotCallback "NERtcTakeSnapshotCallback::onTakeSnapshotResult" 回调返回截图画面的数据。
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
	virtual int takeLocalSnapshot(NERtcVideoStreamType stream_type, NERtcTakeSnapshotCallback *callback) = 0;

	/** 
     * @if English
     * Takes a snapshot of a remote video.
     * <br>You can call takeRemoteSnapshot to specify the uid of video screen of remote mainstreams and substreams, and returns screenshot data of \ref NERtcTakeSnapshotCallback "NERtcTakeSnapshotCallback::onTakeSnapshotResult" callback.
     * @note
     * - You need to call takeRemoteSnapshot after receiving callbacks of onUserVideoStart and onUserSubStreamVideoStart.
     * - You can set text, timestamp, and image watermarks at the same time. If different types of watermarks overlap, the layers override previous layers following image, text, and timestamp.
     * @param uid           The ID of a remote user.
     * @param stream_type   The video stream type of the snapshot. You can set the value to mainstream or substream. For more information, see #NERtcVideoStreamType.
     * @param callback      The snapshot callback. For information, see \ref NERtcTakeSnapshotCallback.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 远端视频画面截图。
     * <br>调用 takeRemoteSnapshot 截取指定 uid 远端主流和远端辅流的视频画面，并通过 \ref NERtcTakeSnapshotCallback "NERtcTakeSnapshotCallback::onTakeSnapshotResult" 回调返回截图画面的数据。
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
	virtual int takeRemoteSnapshot(uid_t uid, NERtcVideoStreamType stream_type, NERtcTakeSnapshotCallback *callback) = 0;

    
    /** 
     * @if English
     * Starts an audio recording on a client.
     * <br>After calling the method, the client records the audio streams that are mixed by all users, and stores the streams in a local file. The onAudioRecording() callback is triggered when the recording starts or ends.
     * <br>If you specify a type of audio quality, the recording file is saved in different formats.
     * - WAV file is large with high quality.
     * - AAC file is small with low quality.
     * @note 
     * - You must call the method after calling the method after joining a room.
     * - A client can only run a recording task. If you repeatedly call the startAudioRecording method, the current recording task stops and a new recording task starts.
     * - If the current user leaves the room, the audio recording automatically stops. You can call the stopAudioRecording method to manually stop recording during calls.
     * @param file_path The absolute path where the recording file is saved. The file name and format must be accurate. For example, sdcard/xxx/audio.aac.
                        - Make sure that the specified path is valid and has the write permission.
                        - Only WAV or AAC files are supported.
     * @param sample_rate The audio sample rate (Hz). Valid values: 16000, 32000, 44100, and 48000. The default value is 32000.
     * @param quality     The audio quality. The parameter is valid only the audio file is in AAC format. For more information, see NERtcAudioRecordingQuality.    
     *  @return
     *  - 0: Success.
     *  - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 开始客户端录音。
     * <br>调用该方法后，客户端会录制房间内所有用户混音后的音频流，并将其保存在本地一个录音文件中。录制开始或结束时，自动触发 onAudioRecording() 回调。
     * <br>指定的录音音质不同，录音文件会保存为不同格式：
     * - WAV：音质保真度高，文件大。
     * - AAC：音质保真度低，文件小。
     * @note 
     * - 请在加入房间后调用此方法。
     * - 客户端只能同时运行一个录音任务，正在录音时，如果重复调用 startAudioRecording，会结束当前录制任务，并重新开始新的录音任务。
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
    virtual int startAudioRecording(const char* file_path, int sample_rate, NERtcAudioRecordingQuality quality) = 0;

    /** 
     * @if English
     * Stops the audio recording on the client.
     * <br>If the local client leaves the room, audio recording automatically stops. You can call the stopAudioRecording method to manually stop recording during calls at any time.
     * @note You must call this method before you call leaveChannel.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 停止客户端录音。
     * <br>本端离开房间时自动停止录音，您也可以在通话中随时调用 stopAudioRecording 手动停止录音。
     * @note 该接口需要在 leaveChannel 之前调用。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
    * @endif
    */
    virtual int stopAudioRecording() = 0;

    /** 
     * @if English
     * Adjusts the volume of local signal playback from a specified remote user.
     * <br>After you join the room, you can call the method to adjust the volume of local audio playback from different remote users or repeatedly adjust the volume of audio playback from a specified remote user.  
     * @note 
     * - You can call this method after joining a room.
     * - The method is valid in the current call. If a remote user exits the room and rejoins the room again, the setting is still valid until the call ends.
     * - The method adjusts the volume of the mixing audio published by a specified remote user. The volume of one remote user can be adjusted. If you want to adjust multiple remote users, you need to call the method for the required times.
     * @param uid    The ID of a remote user.
     * @param volume Playback volume: 0 to 100. 
                    - 0: Mute.
                    - 100: The original volume.
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 调节本地播放的指定远端用户的信号音量。
     * <br>加入房间后，您可以多次调用该方法设置本地播放的不同远端用户的音量；也可以反复调节本地播放的某个远端用户的音量。 
     *  @note 
     * - 请在成功加入房间后调用该方法。
     * - 该方法在本次通话中有效。如果远端用户中途退出房间，则再次加入此房间时仍旧维持该设置，通话结束后设置失效。
     * - 该方法调节的是本地播放的指定远端用户混音后的音量，且每次只能调整一位远端用户。若需调整多位远端用户在本地播放的音量，则需多次调用该方法。
     * @param uid    远端用户 ID。
     * @param volume 播放音量，取值范围为 [0,100]。
                    - 0：静音。
                    - 100：原始音量。
     * @return
     * - 0: 方法调用成功；
     * - 其他: 方法调用失败。
     * @endif
     */
    virtual int adjustUserPlaybackSignalVolume(uid_t uid, int volume) = 0;

    /** 
     * @if English
     * Starts to relay media streams across rooms.
     * - The method can invite co-hosts across rooms. Media streams from up to four rooms can be relayed. A room can receive multiple relayed media streams.
     * - After you call this method, the SDK triggers `onMediaRelayStateChange` and `onMediaRelayEvent`. The return reports the status and events about the current relayed media streams across rooms.
     * @note - You can call this method after joining a room. Before you call the method, you must set the destination room in the `NERtcChannelMediaRelayConfiguration` parameter in `dest_infos`.
     * - The method is applicable only to the host in live streaming.
     * - If you want to call the method again, you must first call the `stopChannelMediaRelay` method to exit the current relaying status.
     * - If you succeed in relaying the media stream across rooms, and want to change the destination room, for example, add or remove the destination room, you can call `updateChannelMediaRelay` to update the information about the destination room.
     * @since V4.3.0
     * @param config specifies the configuration for the media stream relay across rooms. For more information, see {@link NERtcMediaRelayParam.ChannelMediaRelayConfiguration}。
     * @return {@code 0} A value of 0 returned indicates that the method call is successful. Otherwise, the method call fails.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 开始跨房间媒体流转发。
     * - 该方法可用于实现跨房间连麦等场景。支持同时转发到 4 个房间，同一个房间可以有多个转发进来的媒体流。
     * - 成功调用该方法后，SDK 会触发 `onMediaRelayStateChange` 和 `onMediaRelayEvent` 回调，并在回调中报告当前的跨房间媒体流转发状态和事件。
     * @note
     * - 请在成功加入房间后调用该方法。调用此方法前需要通过 `NERtcChannelMediaRelayConfiguration` 中的 `dest_infos` 设置目标房间。
     * - 该方法仅对直播场景下的主播角色有效。
     * - 成功调用该方法后，若您想再次调用该方法，必须先调用 `stopChannelMediaRelay` 方法退出当前的转发状态。
     * - 成功开始跨房间转发媒体流后，如果您需要修改目标房间，例如添加或删减目标房间等，可以调用方法 `updateChannelMediaRelay` 更新目标房间信息。
     * @since V4.3.0
     * @param config 跨房间媒体流转发参数配置信息。
     * @return 成功返回0，其他则失败
     * @endif
     */
    virtual int startChannelMediaRelay(NERtcChannelMediaRelayConfiguration *config) = 0;

    /** 
     * @if English
     * Updates the information of the destination room for the media stream relay.
     * <br>You can call this method to relay the media stream to multiple rooms or exit the current room.
     * - You can call this method to change the destination room, for example, add or remove the destination room.
     * - After you call this method, the SDK triggers `onMediaRelayStateChange` and `onMediaRelayEvent`. The return reports the status and events about the current relayed media streams across rooms.
     * @note Before you call the method, you must join the room and call `startChannelMediaRelay` to relay the media stream across rooms. Before you call the method, you must set the destination room in the `NERtcChannelMediaRelayConfiguration` parameter in `dest_infos`.
     * @since V4.3.0
     * @param config The configuration for destination rooms.
     * @return A value of 0 returned indicates that the method call is successful. Otherwise, the method call fails.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 更新媒体流转发的目标房间。
     * <br>成功开始跨房间转发媒体流后，如果你希望将流转发到多个目标房间，或退出当前的转发房间，可以调用该方法。
     * - 成功开始跨房间转发媒体流后，如果您需要修改目标房间，例如添加或删减目标房间等，可以调用此方法。
     * - 成功调用该方法后，SDK 会触发 `onMediaRelayStateChange` 和 `onMediaRelayEvent` 回调，并在回调中报告当前的跨房间媒体流转发状态和事件。
     * @note 请在加入房间并成功调用 `startChannelMediaRelay` 开始跨房间媒体流转发后，调用此方法。调用此方法前需要通过 `NERtcChannelMediaRelayConfiguration` 中的 `dest_infos` 设置目标房间。
     * @since V4.3.0
     * @param config 目标房间配置信息
     * @return 成功返回0，其他则失败
     * @endif
     */
    virtual int updateChannelMediaRelay(NERtcChannelMediaRelayConfiguration *config) = 0;

    /** 
     * @if English
     * Stops relaying media streams.
     * <br>If the host leaves the room, media stream replay across rooms automatically stops. You can also call stopChannelMediaRelay. In this case, the host exits all destination rooms.
     * - If you call this method, the SDK triggers the `onMediaRelayStateChange` callback. If `NERtcChannelMediaRelayStateIdle` is returned, the media stream relay stops.
     * - If the method call failed, the SDK triggers the `onMediaRelayStateChange` callback that returns the status code `NERtcChannelMediaRelayStateFailure`.
     * @since V4.3.0
     * @return A value of 0 returned indicates that the method call is successful. Otherwise, the method call fails.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 停止跨房间媒体流转发。
     * <br>主播离开房间时，跨房间媒体流转发自动停止，您也可以在需要的时候随时调用 `stopChannelMediaRelay` 方法，此时主播会退出所有目标房间。
     * - 成功调用该方法后，SDK 会触发 `onMediaRelayStateChange` 回调。如果报告 `NERtcChannelMediaRelayStateIdle`，则表示已停止转发媒体流。
     * - 如果该方法调用不成功，SDK 会触发 `onMediaRelayStateChange` 回调，并报告状态码 `NERtcChannelMediaRelayStateFailure`。
     * @since V4.3.0
     * @return 成功返回0，其他则失败
     * @endif
     */
    virtual int stopChannelMediaRelay() = 0;
    

    /** 
     * @if English
     * Sets the fallback option for the published local video stream based on the network conditions.
     * <br>The quality of the published local audio and video streams is degraded with poor quality network connections. After calling this method and setting the option to #kNERtcStreamFallbackAudioOnly:
     * - With unreliable upstream network connections and the quality of audio and video streams is downgraded, the SDK automatically disables video stream or stops receiving video streams. In this way, the communication quality is guaranteed.
     * - The SDK monitors the network performance and recover audio and video streams if the network quality improves.
     * - If the locally published audio and video stream falls back to audio stream, or recovers to audio and video stream, the SDK triggers the onLocalPublishFallbackToAudioOnly callback.
     * @note You must call the method before you call joinChannel.
     * @since V4.3.0
     * @param option The fallback option of publishing audio and video streams. The fallback kNERtcStreamFallbackAudioOnly is disabled by default. For more information, see nertc::NERTCStreamFallbackOption .
     * @return {@code 0} A value of 0 returned indicates that the method call is successful. Otherwise, the method call fails.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 设置弱网条件下发布的音视频流回退选项。
     * <br>在网络不理想的环境下，发布的音视频质量都会下降。使用该接口并将 option 设置为 #kNERtcStreamFallbackAudioOnly 后：
     * - SDK 会在上行弱网且音视频质量严重受影响时，自动关断视频流，尽量保证音频质量。
     * - 同时 SDK 会持续监控网络质量，并在网络质量改善时恢复音视频流。
     * - 当本地发布的音视频流回退为音频流时，或由音频流恢复为音视频流时，SDK 会触发本地发布的媒体流已回退为音频流 onLocalPublishFallbackToAudioOnly 回调。
     * @note 请在加入房间（joinChannel）前调用此方法。
     * @since V4.3.0
     * @param option 发布音视频流的回退选项，默认为不开启回退 kNERtcStreamFallbackAudioOnly。详细信息请参考 nertc::NERTCStreamFallbackOption 。
     * @return {@code 0} 方法调用成功，其他调用失败
     * @endif
     */
    virtual int setLocalPublishFallbackOption(NERtcStreamFallbackOption option) = 0;

    /** 
     * @if English
     * Sets the fallback option for the subscribed remote audio and video stream with poor network connections.
     * <br>The quality of the subscribed audio and video streams is degraded with unreliable network connections. You can use the interface to set the option as #kNERtcStreamFallbackVideoStreamLow or #kNERtcStreamFallbackAudioOnly. 
     * - In unreliable downstream network connections, the SDK switches to receive a low-quality video stream or stops receiving video streams. In this way, the communication quality is maintained or improved.
     * - The SDK monitors the network quality and resumes the video stream when the network condition improves.
     * - If the subscribed remote video stream falls back to audio only, or the audio-only stream switches back to the video stream, the SDK triggers the onRemoteSubscribeFallbackToAudioOnly callback.
     * @note You must call the method before you call joinChannel.
     * @since V4.3.0
     * @param option    The fallback option for the subscribed remote audio and video stream. With unreliable network connections, the stream falls back to a low-quality video stream of kNERtcStreamFallbackVideoStreamLow. For more information, see nertc::NERTCStreamFallbackOption .
     * @return {@code 0} A value of 0 returned indicates that the method call is successful. Otherwise, the method call fails.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
     * 设置弱网条件下订阅的音视频流回退选项。
     * <br>弱网环境下，订阅的音视频质量会下降。使用该接口并将 option 设置为  #kNERtcStreamFallbackVideoStreamLow 或者 #kNERtcStreamFallbackAudioOnly 后：
     * - SDK 会在下行弱网且音视频质量严重受影响时，将视频流切换为小流，或关断视频流，从而保证或提高通信质量。
     * - SDK 会持续监控网络质量，并在网络质量改善时自动恢复音视频流。
     * - 当远端订阅流回退为音频流时，或由音频流恢复为音视频流时，SDK 会触发远端订阅流已回退为音频流 onRemoteSubscribeFallbackToAudioOnly 回调。
     * @note 请在加入房间（joinChannel）前调用此方法。
     * @since V4.3.0
     * @param option    订阅音视频流的回退选项，默认为弱网时回退到视频小流 kNERtcStreamFallbackVideoStreamLow。详细信息请参考 nertc::NERTCStreamFallbackOption 。
     * @return {@code 0} 方法调用成功，其他调用失败
     * @endif
     */
    virtual int setRemoteSubscribeFallbackOption(NERtcStreamFallbackOption option) = 0;

    /** 
     * @if English
     * Enables or disables AI super resolution.
     * @since V4.4.0
     * @note 
     * - Please contact our technical support to enable AI super resolution before you perform the feature. 
     * - AI super resolution is only valid when you enable the following types of video streams: 
     * - Video streams that are received from local 360P.
     * - High stream video of mainstream that are captured by the camera. AI super resolution is currently unsupported to resume low streams or substreams of screen sharing. 
     * @param enable     Whether to enable AI super resolution. By default, the setting is disabled. 
     * @return
     * - 0: Success.
     * - Other values: Failure.
     * @endif
     * @if Chinese
     * @note Linux 暂不支持
     * 
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
    virtual int enableSuperResolution(bool enable) = 0;

    /** 
     * @if English
     * Enables or disables media stream encryption.
     * @since V4.4.0
     * In scenes where high safety is required such as financial sectors, you can set encryption modes of media streams with the method before joining the room. 
     * @note 
     * - Please calls the method before you join the room. The encryption mode and private key cannot be changed after you join the room. The SDK will automatically disable encryption after users leave the room. If you need to enable encryption again, users need to call the method before joining the room. 
     * - In the same room, all users who enable media stream encryption must share the same encryption mode and private keys. If not, members who use different private keys will report kNERtcErrEncryptNotSuitable (30113). 
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
     * @note Linux 暂不支持
     * 
     * 开启或关闭媒体流加密。
     * @since V4.4.0
     * 在金融行业等安全性要求较高的场景下，您可以在加入房间前通过此方法设置媒体流加密模式。
     * @note 
     * - 请在加入房间前调用该方法，加入房间后无法修改加密模式与密钥。用户离开房间后，SDK 会自动关闭加密。如需重新开启加密，需要在用户再次加入房间前调用此方法。
     * - 同一房间内，所有开启媒体流加密的用户必须使用相同的加密模式和密钥，否则使用不同密钥的成员加入房间时会报错 kNERtcErrEncryptNotSuitable（30113）。 
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
    virtual int enableEncryption(bool enable, NERtcEncryptionConfig config) = 0;
};

} //namespace nertc

#endif
