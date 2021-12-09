/** @file nertc_warn_code.h
  * @brief The definition of error codes of NERtc SDK.
  * @copyright (c) 2021 NetEase, Inc.  All rights reserved.
  */

#ifndef NERTC_WARN_CODE_H
#define NERTC_WARN_CODE_H

 /**
 * @namespace nertc
 * @brief namespace nertc
 */
namespace nertc
{
/** 
 * @if English
 * Warning code.
 * If the warning code occurs, the SDK reports an error that is likely to be solved. The warning code just informs you of the SDK status. In most cases, the application programs can pass the warning code.
 * @endif
 * @if Chinese
 * 警告代码。
 * 警告代码意味着 SDK 遇到问题，但有可能恢复，警告代码仅起告知作用，一般情况下应用程序可以忽略警告代码。
 * @endif
 */
typedef enum
{
    /**
     * @if English
     * If the specified value of view is invalid, you must specify the value of view when you enable a video. If the view is still not specified, the SDK returns the warning code.
     * @endif
     * @if Chinese
     * 指定的 view 无效，使用视频功能时需要指定 view，如果 view 尚未指定，则返回该警告。
     * @endif
     */
    kNERtcWarnInvalidView               = 100,      
    /**
     * @if English
     * The value indicates that you fail to initialize the video feature. The reason for the failure is that video resources are occupied. Users cannot view  the video but the audio communication is not affected.
     * @endif
     * @if Chinese
     * 初始化视频功能失败。有可能是因视频资源被占用导致的。用户无法看到视频画面，但不影响语音通信。
     * @endif
     */
    kNERtcWarnInitVideo                 = 101,      
    /**
     * @if English
     * The value indicates the request is in the pending status. In most cases, the request is delayed to be met for a certain module is not well loaded.
     * @endif
     * @if Chinese
     * 请求处于待定状态。一般是由于某个模块还没准备好，请求被延迟处理。
     * @endif
     */
    kNERtcWarnPending                   = 102,      
    /**
     * @if English
     * The Client has no capability of device encoding and  decoding to match that of the channel. For example, the device cannot encode in VP8 and other formats. Therefore, you may cannot implement video encoding and decoding in the channel. The local side may cannot display some remote video screens and the remote side may cannot display local screens.
     * @endif
     * @if Chinese
     * 当前客户端设备视频编解码能力与房间不匹配，例如设备不支持 VP8 等编码类型。在此房间中可能无法成功进行视频编解码，即本端可能无法正常显示某些远端的视频画面，同样远端也可能无法显示本端画面。
     * @endif
     */
    kNERtcWarningChannelAbilityNotMatch = 406,      
    //ADM module.
    /**
     * @if English
     * Audio Device Module: A warning occurs in the playback device.
     * @endif
     * @if Chinese
     * 音频设备模块：运行时播放设备出现警告。
     * @endif
     */
    kNERtcWarnADMRuntimePlayoutWarning  = 1001,     
    /**
     * @if English
     * Device Module: A warning occurs in the recording device.
     * @endif
     * @if Chinese
     * 音频设备模块：运行时录音设备出现警告。
     * @endif
     */
    kNERtcWarnADMRuntimeRecordingWarning = 1002,    
    /**
     * @if English
     * Audio Device Module: No valid audio data is collected.
     * @endif
     * @if Chinese
     * 音频设备模块：没有采集到有效的声音数据。
     * @endif
     */
    kNERtcWarnADMRecordAudioSilence    = 1003,      
    /**
     * @if English
     * Audio Device Module: Malfunction occurs in the playback device.
     * @endif
     * @if Chinese
     * 音频设备模块：播放设备故障。
     * @endif
     */
    kNERtcWarnADMPlayoutMalfunction     = 1004,     
    /**
     * @if English
     * Audio Device Module: Malfunction occurs in the recording device.
     * @endif
     * @if Chinese
     * 音频设备模块：录音设备故障。
     * @endif
     */
    kNERtcWarnADMRecordMalfunction      = 1005,     
    /**
     * @if English
     * Audio Device Module: The volume of recorded audio is too low.
     * @endif
     * @if Chinese
     * 音频设备模块：录到的声音太低。
     * @endif
     */
    kNERtcWarnADMRecordAudioLowLevel    = 1006,     
    /**
     * @if English
     * Audio Device Module: The playback volume is too low.
     * @endif
     * @if Chinese
     * 音频设备模块：播放的声音太低。
     * @endif
     */
    kNERtcWarnADMPlayoutAudioLowLevel   = 1007,     
    /**
     * @if English
     * Audio Device Module: Howling is detected in the recording audio.
     * @endif
     * @if Chinese
     * 音频设备模块：录音声音监测到啸叫。
     * @endif
     */
    kNERtcWarnAPMHowling                = 1008,     
    /**
     * @if English
     * Audio Device Module: The freeze occurs in the audio playback.
     * @endif
     * @if Chinese
     * 音频设备模块：音频播放会卡顿。
     * @endif
     */
    kNERtcWarnADMGlitchState            = 1009,     
    /**
     * @if English
     * Audio Device Module: The setting of audio bottom layer is modified.
     * @endif
     * @if Chinese
     * 音频设备模块：音频底层设置被修改。
     * @endif
     */
    kNERtcWarnADMImproperSettings       = 1010,     
    /**
     * @if English
     * Audio Device Module: Error occurs in the audio drive. Solution: Disables and restarts audio device, enables the device, or updates the sound card drive.
     * @endif
     * @if Chinese
     * 音频设备模块：音频驱动异常。解决方案：禁用并重新使能音频设备，或者重启机器，或者更新声卡驱动。
     * @endif
     */
    //The definition of warning code on the Windows platform.
    kNERtcWarnADMWinCoreNoDataReadyEvent        = 2000,     
    /**
     * @if English
     * Audio Device Module: The audio capture device is not available.
     * @endif
     * @if Chinese
     * 音频设备模块：无可用音频采集设备。
     * @endif
     */
    kNERtcWarnADMWinCoreNoRecordingDevice       = 2001,     
    /**
     * @if English
     * Audio Device Module: Audio playback device is not available. Solution: Swap the audio device.
     * @endif
     * @if Chinese
     * 音频设备模块：无可用音频播放设备。解决方案：插入音频设备。
     * @endif
     */
    kNERtcWarnADMWinCoreNoPlayoutDevice         = 2002,     
    /**
     * @if English
     * Audio Device Module: Audio capturing and releasing are wrongly implemented. Solution: Disables and restarts audio device, enables the device, or updates the sound card drive.
     * @endif
     * @if Chinese
     * 音频设备模块：音频采集释放有误。解决方案：禁用并重新使能音频设备，或者重启机器，或者更新声卡驱动。
     * @endif
     */
    kNERtcWarnADMWinCoreImproperCaptureRelease  = 2003,     
    //The definition of warning code on the macOS platform. Starts from 30000.

    //The definition of warning code on the iOS platform. Starts from 40000.

    //The definition of warning code on theAndroid  platform. Starts from 50000.

} NERtcWarnCode;

} // namespace nertc

#endif