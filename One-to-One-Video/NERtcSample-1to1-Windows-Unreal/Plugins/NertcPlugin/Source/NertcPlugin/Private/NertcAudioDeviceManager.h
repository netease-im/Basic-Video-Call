/** @file NertcAudioDeviceManager.h
 * @brief The interface header file of audio device management of the NERTC UE SDK.
 * All parameter descriptions of the NERTC UE SDK. All string-related parameters (char *) are encoded in UTF-8.
 * @copyright (c) 2021 NetEase, Inc. All rights reserved.
 */

#pragma once
#include "NertcDeviceCollection.h"
#include "INertcAudioDeviceManager.h"
#include <string>
//#include "Nertc/include/nertc_engine_ex.h"

struct nertc_audio_device_manager;
namespace nertc {
class NertcEngine;

class NertcAudioDeviceManager:public IAudioDeviceManager {
public:
  NertcAudioDeviceManager() = default;
  NertcAudioDeviceManager(const NertcAudioDeviceManager& other) = delete;
  NertcAudioDeviceManager(NertcAudioDeviceManager&& other) noexcept = delete;
  NertcAudioDeviceManager& operator=(const NertcAudioDeviceManager& other) = delete;
  NertcAudioDeviceManager& operator=(NertcAudioDeviceManager&& other) noexcept = delete;
  virtual ~NertcAudioDeviceManager() = default;
private:
  friend class NertcEngineEx;
  NertcAudioDeviceManager(nertc_audio_device_manager* manager);
public:
 
IDeviceCollection* enumerateRecordDevices() override;

int setRecordDevice(const char device_id[kNERtcMaxDeviceIDLength]) override;

int getRecordDevice(char device_id[kNERtcMaxDeviceIDLength]) override;

IDeviceCollection* enumeratePlayoutDevices() override;

int setPlayoutDevice(const char device_id[kNERtcMaxDeviceIDLength]) override;

int getPlayoutDevice(char device_id[kNERtcMaxDeviceIDLength]) override;

int setRecordDeviceVolume(uint32_t volume) override;

int getRecordDeviceVolume(uint32_t* volume) override;

int setPlayoutDeviceVolume(uint32_t volume) override;

int getPlayoutDeviceVolume(uint32_t* volume) override;

int setPlayoutDeviceMute(bool mute) override;

int getPlayoutDeviceMute(bool* mute) override;

int setRecordDeviceMute(bool mute) override;

int getRecordDeviceMute(bool* mute) override;

int startRecordDeviceTest(uint64_t indication_interval) override;

int stopRecordDeviceTest() override;

int startPlayoutDeviceTest(const char* test_audio_file_path) override;

int stopPlayoutDeviceTest() override;

int startAudioDeviceLoopbackTest(uint64_t indication_interval) override;

int stopAudioDeviceLoopbackTest() override;
private:
nertc_audio_device_manager* m_nertc_audio_device_manager{ nullptr };
};
}