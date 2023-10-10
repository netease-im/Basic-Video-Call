// Copyright Epic Games, Inc. All Rights Reserved.

#include "NertcAudioDeviceManager.h"

#include "Nertc/api/nertc_engine.h"
#include "Nertc/api/nertc_engine_ex.h"
#include "Nertc/api/nertc_audio_device_manager.h"

#include <utility>

namespace nertc {
	NertcAudioDeviceManager::NertcAudioDeviceManager(nertc_audio_device_manager* manager) :m_nertc_audio_device_manager(manager){

	}
	IDeviceCollection* NertcAudioDeviceManager::enumerateRecordDevices() {
		auto csdk_collection = nertc_audio_device_manager_enumerate_record_devices(m_nertc_audio_device_manager);
    if (csdk_collection) {
      return new NertcDeviceCollection(csdk_collection);
    }
    return nullptr;
	}
	int NertcAudioDeviceManager::setRecordDevice(const char device_id[kNERtcMaxDeviceIDLength]) {
		return nertc_audio_device_manager_set_record_device(m_nertc_audio_device_manager, device_id);
	}
	int NertcAudioDeviceManager::getRecordDevice(char device_id[kNERtcMaxDeviceIDLength]) {
		return nertc_audio_device_manager_get_record_device(m_nertc_audio_device_manager, device_id);
	}
  IDeviceCollection* NertcAudioDeviceManager::enumeratePlayoutDevices() {
		auto csdk_collection = nertc_audio_device_manager_enumerate_playout_devices(m_nertc_audio_device_manager);
		return new NertcDeviceCollection(csdk_collection);
	}
	int NertcAudioDeviceManager::setPlayoutDevice(const char device_id[kNERtcMaxDeviceIDLength]) {
		return nertc_audio_device_manager_set_playout_device(m_nertc_audio_device_manager, device_id);
	}
	int NertcAudioDeviceManager::getPlayoutDevice(char device_id[kNERtcMaxDeviceIDLength]) {
		return nertc_audio_device_manager_get_playout_device(m_nertc_audio_device_manager, device_id);
	}
	// Device volume manager
	// The volume value: [0, 255]
	int NertcAudioDeviceManager::setRecordDeviceVolume(uint32_t volume) {
		return nertc_audio_device_manager_set_record_device_volume(m_nertc_audio_device_manager, volume);
	}
	int NertcAudioDeviceManager::getRecordDeviceVolume(uint32_t* volume) {
		return nertc_audio_device_manager_get_record_device_volume(m_nertc_audio_device_manager, volume);
	}
	int NertcAudioDeviceManager::setPlayoutDeviceVolume(uint32_t volume) {
		return nertc_audio_device_manager_set_playout_device_volume(m_nertc_audio_device_manager, volume);
	}
	int NertcAudioDeviceManager::getPlayoutDeviceVolume(uint32_t* volume) {
		return nertc_audio_device_manager_get_playout_device_volume(m_nertc_audio_device_manager, volume);
	}

	int NertcAudioDeviceManager::setPlayoutDeviceMute(bool mute) {
		return nertc_audio_device_manager_set_playout_device_mute(m_nertc_audio_device_manager, mute);
	}
	int NertcAudioDeviceManager::getPlayoutDeviceMute(bool* mute) {
		return nertc_audio_device_manager_get_playout_device_mute(m_nertc_audio_device_manager, mute);
	}
	int NertcAudioDeviceManager::setRecordDeviceMute(bool mute) {
		return nertc_audio_device_manager_set_record_device_mute(m_nertc_audio_device_manager, mute);
	}
	int NertcAudioDeviceManager::getRecordDeviceMute(bool* mute) {
		return nertc_audio_device_manager_get_record_device_mute(m_nertc_audio_device_manager, mute);
	}

	// Device test
	// NOTE: Recoding and loopback test can not being started at the same time
	int NertcAudioDeviceManager::startRecordDeviceTest(uint64_t indication_interval) {
		return nertc_audio_device_manager_start_record_device_test(m_nertc_audio_device_manager, indication_interval);
	}
	int NertcAudioDeviceManager::stopRecordDeviceTest() {
		return nertc_audio_device_manager_stop_record_device_test(m_nertc_audio_device_manager);
	}
	int NertcAudioDeviceManager::startPlayoutDeviceTest(const char* test_audio_file_path) {
		return nertc_audio_device_manager_start_playout_device_test(m_nertc_audio_device_manager, test_audio_file_path);
	}
	int NertcAudioDeviceManager::stopPlayoutDeviceTest() {
		return nertc_audio_device_manager_stop_playout_device_test(m_nertc_audio_device_manager);
	}
	int NertcAudioDeviceManager::startAudioDeviceLoopbackTest(uint64_t indication_interval) {
		return nertc_audio_device_manager_start_audio_device_loopback_test(m_nertc_audio_device_manager, indication_interval);
	}
	int NertcAudioDeviceManager::stopAudioDeviceLoopbackTest() {
		return nertc_audio_device_manager_stop_audio_device_loopback_test(m_nertc_audio_device_manager);
	}
}