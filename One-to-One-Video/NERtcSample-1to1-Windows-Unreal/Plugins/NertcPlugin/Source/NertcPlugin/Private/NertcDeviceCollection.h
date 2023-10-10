/**
 * @file NertcDeviceCollection.h
 * @brief The interface header file of NERTC UE SDK device NERTC UE SDK device collection.
 * All parameter descriptions of the NERTC SDK. All string-related parameters (char *) are encoded in UTF-8.
 * @copyright (c) 2021, NetEase Inc. All rights reserved.
 */
#pragma once
#include "INertcDeviceCollection.h"
#include "Nertc/api/nertc_engine.h"
#include "Nertc/api/nertc_engine_ex.h"
#include <string>

struct nertc_device_collection;
namespace nertc {
class NertcAudioDeviceManager;
class NertcDeviceCollection:public IDeviceCollection {
public:
NertcDeviceCollection() = delete;
NertcDeviceCollection(const NertcDeviceCollection& other);
NertcDeviceCollection(NertcDeviceCollection&& other) noexcept;
NertcDeviceCollection& operator=(const NertcDeviceCollection& other);
NertcDeviceCollection& operator=(NertcDeviceCollection&& other) noexcept;
virtual ~NertcDeviceCollection();
private:
  friend class NertcAudioDeviceManager;
  NertcDeviceCollection(nertc_device_collection* collection);
public:

uint16_t getCount() override;

int getDevice(uint16_t index, char device_name[kNERtcMaxDeviceNameLength], char device_id[kNERtcMaxDeviceIDLength]) override;

int getDeviceInfo(uint16_t index, NERtcDeviceInfo* device_info) override;

private:
nertc_device_collection* m_nertc_collection{ nullptr };
};
}