#ifndef NERTC_DEVICE_COLLECTION_H
#define NERTC_DEVICE_COLLECTION_H

#include "nertc_engine_defines.h"

NERTC_BEGIN_DECLS
/**
 * @if English
 * Gets the number of devices.
 * @note You must call \ref IAudioDeviceManager::enumeratePlayoutDevices "enumeratePlayoutDevices" or \ref
 * IAudioDeviceManager::enumerateRecordDevices "enumerateRecordDevices" before calling the method to get the number of playing
 * and capturing devices.
 * @return The number of capturing and playback devices.
 *
 * @endif
 * @if Chinese
 * 获取设备数量。
 * @note 调用此方法之前，必须调用 \ref IAudioDeviceManager::enumeratePlayoutDevices "enumeratePlayoutDevices" 或 \ref
 * IAudioDeviceManager::enumerateRecordDevices "enumerateRecordDevices" 方法获取播放或采集设备数量。
 * @return 采集或播放设备数量。
 * @endif
 */
NERTC_API uint16_t NERTC_CALL nertc_device_collection_get_count(struct nertc_device_collection* self);

/**
 * @if English
 * Gets the device information of the specified index.
 * @param index specifies the device information that you want to check. The value must be lower than the value returned by
 * \ref IDeviceCollection::getCount "getCount".
 * @param device_name Device name.
 * @param device_id Device ID.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 *
 * @endif
 * @if Chinese
 * 获取指定 index 的设备信息。
 * @param index  指定想查询的设备信息。必须小于 \ref IDeviceCollection::getCount "getCount"返回的值。
 * @param device_name  设备名称。
 * @param device_id  设备 ID。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_device_collection_get_device(struct nertc_device_collection* self,uint16_t index,char* device_name,char* device_id);

/**
 * @if English
 * Searches specified information about index-related devices.
 * @note The link method of returnable devices and the non-useful status determined by the SDK.
 * @param index specifies the device information that you want to check.
 * @param device_info For information about device information, see \ref NERtcDeviceInfo "NERtcDeviceInfo".
 * @return
 * - 0: Success.
 * - Other values: Failure.
 *
 * @endif
 * @if Chinese
 * 检索有关索引设备的指定信息。
 * @note 可返回设备的链接方式，和SDK判定的疑似不可用状态。
 * @param index  指定想查询的设备信息。
 * @param device_info 设备信息，详细信息请参考 \ref NERtcDeviceInfo "NERtcDeviceInfo"。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_device_collection_get_device_info(struct nertc_device_collection* self,uint16_t index,struct nertc_device_info* device_info);

/**
 * @if English
 * Releases all IDeviceCollection resources.
 *
 * @endif
 * @if Chinese
 * 释放所有 IDeviceCollection 资源。
 * @endif
 */
NERTC_API void NERTC_CALL nertc_device_collection_destroy(struct nertc_device_collection* self);

NERTC_END_DECLS

#endif //NERTC_DEVICE_COLLECTION_H
