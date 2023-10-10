/** @file NertcAudioDeviceManager.h
 * @brief The interface header file of audio device management of the NERTC UE SDK.
 * All parameter descriptions of the NERTC UE SDK. All string-related parameters (char *) are encoded in UTF-8.
 * @copyright (c) 2021 NetEase, Inc. All rights reserved.
 */

#pragma once
#include "INertcDeviceCollection.h"
#include <string>

namespace nertc {
class IAudioDeviceManager {
public:
  virtual ~IAudioDeviceManager() {}
 /**
 * @if English
 * Gets the list of all the audio capture devices in the system.
 * <br>The method returns an IDeviceCollection object that includes all the audio capture devices in the system. Enumerates
 * capturing devices with the App through the IDeviceCollection object.
 * @note After the method is used, the App needs to destroy the returned object by calling \ref IDeviceCollection::destroy
 * "destroy" method.
 * @return
 * - Failure: Null.
 * @endif
 * @if Chinese
 * 获取系统中所有的音频采集设备列表。
 * <br>该方法返回一个 IDeviceCollection 对象，包含系统中所有的音频采集设备。通过IDeviceCollection 对象，App
 * 可以枚举音频采集设备。
 * @note 在使用结束后，App 需调用  \ref IDeviceCollection::destroy "destroy"  方法销毁返回的对象。
 * @return
 * - 方法调用成功：一个 IDeviceCollection 对象，包含所有的音频采集设备。
 * - 方法调用失败：NULL。
 * @endif
 * */
virtual IDeviceCollection* enumerateRecordDevices() = 0;
/**
 * @if English
 * Specifies the audio capture device.
 * @param device_id The device ID of the audio capture devices. Gets the ID through enumerateRecordDevices. Device swapping or
 * plugging does not affect deviceId.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 指定音频采集设备。
 * @param device_id 音频采集设备的设备 ID。可通过 enumerateRecordDevices 获取。插拔设备不会影响 deviceId。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 * */
virtual int setRecordDevice(const char device_id[kNERtcMaxDeviceIDLength]) = 0;
/**
 * @if English
 * Gets the ID of the audio capture device that is currently used.
 * @param device_id The device ID of the audio capture devices.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 获取当前使用的音频采集设备 ID。
 * @param device_id 音频采集设备的设备 ID。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 * */
virtual int getRecordDevice(char device_id[kNERtcMaxDeviceIDLength]) = 0;
/**
 * @if English
 * Gets the list of all playback devices in the system.
 * <br>The method returns an IDeviceCollection object that includes all audio playback devices in the system. Enumerates
 * playback devices with the App through the IDeviceCollection object. After the method is used, the App needs to destroy the
 * returned object by calling the destroy method.
 * @note The system must destroy the returned value by calling \ref IDeviceCollection::destroy "destroy" method.
 * @return
 * - Success: Gets an IDeviceCollection object that includes all audio playback devices.
 * - Failure: Null.
 * @endif
 * @if Chinese
 * 获取系统中所有的播放设备列表。
 * <br>该方法返回一个 IDeviceCollection 对象，包含系统中所有的播放设备。通过 IDeviceCollection 对象，App
 * 可以枚举播放设备。在使用结束后，App 需调用 destroy 方法销毁返回的对象。
 * @note 程序必须调用 \ref IDeviceCollection::destroy "destroy" 方法销毁返回的值。
 * @return
 * - 方法调用成功：一个 IDeviceCollection 对象，包含所有的音频播放设备。
 * - 方法调用失败：NULL。
 * @endif
 * */
virtual IDeviceCollection* enumeratePlayoutDevices() = 0;
/**
 * @if English
 * Specifies the audio playback device.
 * @param device_id The device ID of audio playback devices. Gets the ID through \ref
 * IAudioDeviceManager::enumeratePlayoutDevices "enumeratePlayoutDevices". Device swapping or plugging does not affect
 * deviceId.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 指定播放设备。
 * @param device_id 音频播放设备的设备 ID。可以通过 \ref IAudioDeviceManager::enumeratePlayoutDevices
 * "enumeratePlayoutDevices" 获取。插拔设备不会影响 deviceId。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 * */
virtual int setPlayoutDevice(const char device_id[kNERtcMaxDeviceIDLength]) = 0;
/**
 * @if English
 * Gets the ID of the audio playback device that is currently used.
 * @param device_id The ID of audio playback devices.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 获取当前使用的音频播放设备 ID。
 * @param device_id 音频播放设备的设备 ID。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 * */
virtual int getPlayoutDevice(char device_id[kNERtcMaxDeviceIDLength]) = 0;

/**
 * @if English
 * Sets the volume of the audio capture device.
 * @param volume The volume of the audio capture device. Valid values: 0 to 255.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置音频采集设备音量。
 * @param volume 音频采集设备音量。取值范围为 0~255。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 * */
virtual int setRecordDeviceVolume(uint32_t volume) = 0;
/**
 * @if English
 * Gets the volume of the audio capture device.
 * @param volume The volume of the audio capture device.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 获取音频采集设备音量。
 * @param volume 音频采集设备音量。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 * */
virtual int getRecordDeviceVolume(uint32_t* volume) = 0;
/**
 * @if English
 * Sets the volume of audio playback device.
 * @param volume The volume of audio playback device. Valid values: 0 to 255.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置音频播放设备音量。
 * @param volume 音频播放设备音量。取值范围为 0~255。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 * */
virtual int setPlayoutDeviceVolume(uint32_t volume) = 0;
/**
 * @if English
 * Gets the volume of audio playback device.
 * @param volume The volume of audio playback device.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 获取音频播放设备音量。
 * @param volume 音频播放设备音量。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 * */
virtual int getPlayoutDeviceVolume(uint32_t* volume) = 0;

/**
 * @if English
 * Specifies to mute or unmute the audio playback device.
 * @param mute indicates whether to unmute the audio playback device.
 * - true: Specifies to mute the audio playback device.
 * - false: Specifies to unmute the audio playback device.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 静音或取消静音音频播放设备。
 * @param mute 是否静音音频播放设备。
 * - true：静音音频播放设备。
 * - false：取消静音音频播放设备。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 * */
virtual int setPlayoutDeviceMute(bool mute) = 0;

/**
 * @if English
 * Confirms whether the audio playback device is muted.
 * @param mute indicates the audio playback device is muted.
 * - true: The device is muted.
 * - false: The device is unmuted.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 获取音频播放设备静音状态。
 * @param mute 音频播放设备静音状态。
 * - true：静音状态。
 * - false：非静音状态。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 * */
virtual int getPlayoutDeviceMute(bool* mute) = 0;
/**
 * @if English
 * Specifies to mute or unmute the audio playback device.
 * @param mute indicates whether to unmute the audio playback device.
 * - true: Specifies to mute the audio playback device.
 * - false: Specifies to unmute the audio playback device.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 *  @endif
 *  @if Chinese
 * 静音或取消静音音频采集设备。
 * @param mute 是否静音音频采集设备。
 * - true：静音音频采集设备。
 * - false：取消静音音频采集设备。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 * */
virtual int setRecordDeviceMute(bool mute) = 0;

/**
 * @if English
 * Confirms whether the audio playback device is muted.
 * @param mute indicates the audio playback device is muted.
 * - true: The device is muted.
 * - false: The device is unmuted.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 获取音频采集设备静音状态。
 * @param mute 音频采集设备静音状态。
 * - true: 静音状态。
 * - false: 非静音状态。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 * */
virtual int getRecordDeviceMute(bool* mute) = 0;

/**
 * @if English
 * Starts the test of the audio capture device.
 * <br>The method tests whether the audio capture device can work properly.
 * <br>After calling the method, the SDK triggers \ref IRtcEngineEventHandlerEx::onLocalAudioVolumeIndication
 * "onLocalAudioVolumeIndication"  callback at the time interval set in this method, which reports the volume information of
 * the capturing device.
 * @note
 * - Calls the method before a user needs to join a room.
 * - The test of the audio capture device can automatically stop after a call starts. You can also manually stop the test by
 * calling stopRecordDeviceTest.
 * @param indication_interval indicates the time interval that SDK returns \ref
 * IRtcEngineEventHandlerEx::onLocalAudioVolumeIndication "onLocalAudioVolumeIndication" callback. Unit: milliseconds.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 启动音频采集设备测试。
 * <br>该方法测试音频采集设备是否能正常工作。
 * <br>调用该方法后，SDK 会按设置的时间间隔触发 \ref IRtcEngineEventHandlerEx::onLocalAudioVolumeIndication
 * "onLocalAudioVolumeIndication"  回调， 报告采集设备的音量信息。
 * @note
 * - 该方法需在加入房间前调用。
 * - 音频采集设备测试会在通话开始后自动结束，您也可以手动调用 stopRecordDeviceTest 停止音频采集设备测试。
 * @param indication_interval SDK 返回 \ref IRtcEngineEventHandlerEx::onLocalAudioVolumeIndication
 * "onLocalAudioVolumeIndication"  回调的时间间隔，单位为毫秒。
 * @return
 * - 0: Success.
 * - other: Failure.
 * @endif
 * */
virtual int startRecordDeviceTest(uint64_t indication_interval) = 0;
/**
 * @if English
 * Stops the test of the audio capture device.
 * <br>Uses the method to stop the test of the audio capture device.
 * @note
 * - Calls the method before a user needs to join a room.
 * - The test of the audio capture device can automatically stop after a call starts. You can also manually stop the test by
 * calling stopRecordDeviceTest.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 停止音频采集设备测试。
 * <br>该方法停止音频采集设备测试。
 * @note
 * - 该方法需在加入房间前调用。
 * - 音频采集设备测试会在通话开始后自动结束，您也可以手动调用 stopRecordDeviceTest 停止音频采集设备测试。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 * */
virtual int stopRecordDeviceTest() = 0;
/**
 * @if English
 * Starts the test of the audio capture device.
 * The method tests whether the audio capture device can work properly. After the test is started, SDK plays the specified
 * audio files. If the sound is successfully played, the playback device can work properly. After calling the method, the SDK
 * triggers \ref IRtcEngineEventHandlerEx::onLocalAudioVolumeIndication "onLocalAudioVolumeIndication"  callback per 100 ms,
 * which reports the volume information of the playback device.
 * @note
 * - Calls the method before a user needs to join a room.
 * - The test of the audio playback device can automatically stop after a call starts. You can also manually stop the test by
 * calling stopRecordDeviceTest.
 * - Supported file formats: wav, mp3, aac.
 * @param test_audio_file_path The absolute path of audio files. The path string is encoded in UTF-8.
 * @return
 * - 0: Success. You can hear the audio of the set files.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 启动音频播放设备测试。
 * 该方法测试音频播放设备是否能正常工作。启动测试后，SDK 播放指定的音频文件，测试者如果能听到声音，说明播放设备能正常工作。
 * 调用该方法后，SDK 会每隔 100 ms 触发一次 \ref IRtcEngineEventHandlerEx::onLocalAudioVolumeIndication
 * "onLocalAudioVolumeIndication" 回调，报告播放设备的音量信息。
 * @note
 * - 该方法需在加入房间前调用。
 * - 音频播放设备测试会在通话开始后自动结束，您也可以手动调用 stopPlayoutDeviceTest 停止音频播放设备测试。
 * - 支持文件格式包括 wav、mp3、aac。
 * @param test_audio_file_path 音频文件的绝对路径，路径字符串使用 UTF-8 编码格式。
 * @return
 * - 0: 成功，并且可以听到所设置文件的声音。
 * - 其他：失败。
 * @endif
 * */
virtual int startPlayoutDeviceTest(const char* test_audio_file_path) = 0;
/**
 * @if English
 * Stops the test of the audio capture device.
 * @note
 * - Calls the method before a user needs to join a room.
 * - The test of the audio playback device can automatically stop after a call starts. You can also manually stop the test by
 calling stopRecordDeviceTest.
 * @return
 * - 0: Success.
 * - Other values: Failure.

 * @endif
 * @if Chinese
 * 停止播放设备测试。
 * @note
 * - 该方法需在加入房间前调用。
 * - 播放设备测试会在通话开始后自动结束，您也可以手动调用 stopPlayoutDeviceTest 停止播放设备测试。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 * */
virtual int stopPlayoutDeviceTest() = 0;
/**
 * @if English
 * Starts the test of the audio device circuit.
 * <br>The method tests whether the audio capturing and playback device can work properly. Once the test starts, the audio
 capture device captures local audio, and then plays the local audio. The SDK triggers \ref
 IRtcEngineEventHandlerEx::onLocalAudioVolumeIndication "onLocalAudioVolumeIndication"  callback at the time interval set in
 this method,  which reports the volume information of the audio.
 * @note
 * - Calls the method before a user needs to join a room.
 * - The test of the audio device circuit can automatically stop after a call starts. You can also manually stop the test by
 calling stopRecordDeviceTest.
 * - You can use the method locally to test the audio device, which does not require an Internet connection.
 * @param indication_interval The time interval that SDK returns \ref IRtcEngineEventHandlerEx::onLocalAudioVolumeIndication
 "onLocalAudioVolumeIndication" callback. Unit: milliseconds.
 * @return
 * - 0: Success.
 * - Other values: Failure.

 * @endif
 * @if Chinese
 * 开始音频设备回路测试。
 * <br>该方法测试音频采集和播放设备是否能正常工作。一旦测试开始，音频采集设备会采集本地音频，然后使用音频播放设备播放出来。
 SDK 会按设置的时间间隔触发 \ref IRtcEngineEventHandlerEx::onLocalAudioVolumeIndication "onLocalAudioVolumeIndication"  回调，
 报告音量信息。
 * @note
 * - 该方法需在加入房间前调用。
 * - 音频设备回路测试会在通话开始后自动结束，您也可以手动调用 stopAudioDeviceLoopbackTest 停止音频设备回路测试。
 * - 该方法仅在本地进行音频设备测试，不涉及网络连接。
 * @param indication_interval SDK 返回  \ref IRtcEngineEventHandlerEx::onLocalAudioVolumeIndication
 "onLocalAudioVolumeIndication" 回调的 时间间隔，单位为毫秒。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 * */
virtual int startAudioDeviceLoopbackTest(uint64_t indication_interval) = 0;
/**
 * @if English
 * Stops the test of the audio device circuit.
 * @note
 * - Calls the method before a user needs to join a room.
 * - The test of the audio device circuit can automatically stop after a call starts. You can also manually stop the test by
 calling stopRecordDeviceTest.
 * @return
 * - 0: Success.
 * - Other values: Failure.

 * @endif
 * @if Chinese
 * 停止音频设备回路测试。
 * @note
 * - 该方法需在加入房间前调用。
 * - 音频设备回路测试会在通话开始后自动结束，您也可以手动调用 stopAudioDeviceLoopbackTest 停止音频设备回路测试。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 * */
virtual int stopAudioDeviceLoopbackTest() = 0;
};
}