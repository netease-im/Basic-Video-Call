// Copyright Epic Games, Inc. All Rights Reserved.

#include "NertcDeviceCollection.h"
#include "Nertc/api/nertc_device_collection.h"
#include "NertcEngineUtil.h"
#include <utility>

namespace nertc {
	NertcDeviceCollection::NertcDeviceCollection(const NertcDeviceCollection& other):m_nertc_collection(other.m_nertc_collection) {

	}
	NertcDeviceCollection::NertcDeviceCollection(nertc_device_collection* collection) :m_nertc_collection(collection) {

	}
	NertcDeviceCollection::NertcDeviceCollection(NertcDeviceCollection&& other) noexcept :m_nertc_collection(std::exchange(other.m_nertc_collection, nullptr)) {

	}
	NertcDeviceCollection& NertcDeviceCollection::operator=(const NertcDeviceCollection& other) {
		return *this = NertcDeviceCollection(other);
	}
	NertcDeviceCollection& NertcDeviceCollection::operator=(NertcDeviceCollection&& other) noexcept {
		std::swap(m_nertc_collection, other.m_nertc_collection);
		return *this;
	}
	NertcDeviceCollection::~NertcDeviceCollection() {
		if (!m_nertc_collection) {
			nertc_device_collection_destroy(m_nertc_collection);
      m_nertc_collection = nullptr;
		}
	};
	uint16_t NertcDeviceCollection::getCount() {
		return nertc_device_collection_get_count(m_nertc_collection);
	}
	int NertcDeviceCollection::getDevice(uint16_t index,
		char device_name[kNERtcMaxDeviceNameLength],
		char device_id[kNERtcMaxDeviceIDLength]) {
		return nertc_device_collection_get_device(m_nertc_collection, index, device_name, device_id);
	}
	int NertcDeviceCollection::getDeviceInfo(uint16_t index, NERtcDeviceInfo* device_info) {
    nertc_device_info info{};

		auto ret = nertc_device_collection_get_device_info(m_nertc_collection, index, &info);
    if (device_info) {
      convertToNertcStruct(info, *device_info);
    }
    return ret;
	}
}