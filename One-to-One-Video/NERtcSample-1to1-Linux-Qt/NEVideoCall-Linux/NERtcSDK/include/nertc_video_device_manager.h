/** @file nertc_video_device_manager.h
* @brief The interface header file of video device management of the NERTC SDK. 
* The interface header file of video device management of the NERTC SDK. 
* @copyright (c) 2021, NetEase Inc. All rights reserved.
*/

#ifndef NERTC_VIDEO_DEVICE_MANAGER_H
#define NERTC_VIDEO_DEVICE_MANAGER_H

#include "nertc_base_types.h"
#include "nertc_engine_defines.h"
#include "nertc_device_collection.h"

 /**
 * @namespace nertc
 * @brief namespace nertc
 */
namespace nertc
{
/** 
 * @if English
 * Video device management method.
 * <br>IVideoDeviceManager interface class provides related interfaces for video device management. Gets IVideoDeviceManager interface through instantiating the IVideoDeviceManager class.
 * @endif
 * @if Chinese
 * 视频设备管理方法。
 * <br>IVideoDeviceManager 接口类提供用于管理视频设备的相关接口。 可通过实例化 IVideoDeviceManager 类来获取 IVideoDeviceManager 接口。
* @endif
*/
class IVideoDeviceManager
{
protected:
    virtual ~IVideoDeviceManager() {}

public:
    /** 
     * @if English
     * Gets the list of all video capturing devices in the system.
     * <br>The method returns an IDeviceCollection object that includes all Video capturing devices in the system. Enumerates capturing devices with the App through the IDeviceCollection object.  
     * @note
     * After the method is used, the App needs to destroy the returned object. 
     * @return
     * - Success: An IDeviceCollection object includes all Video capturing devices.
     * - Failure: Null. 
     * @endif
     * @if Chinese
     * 获取系统中所有的视频采集设备列表。
     * <br>该方法返回一个 IDeviceCollection 对象，包含系统中所有的音频采集设备。通过IDeviceCollection 对象，App 可以枚举视频采集设备。
     * @note
     * 在使用结束后，App 需调用 destroy 方法销毁返回的对象。
     * @return
     * - 方法调用成功：一个 IDeviceCollection 对象，包含所有的视频采集设备。
     * - 方法调用失败：NULL 。
     * @endif
     */
    virtual IDeviceCollection * enumerateCaptureDevices() = 0;
    /** 
     * @if English
     * Specifies the video capturing device.
     * @param device_id     The ID of video capturing devices. You can get the ID through the enumerateCaptureDevices method.
     * @return
     * - 0: Success.
     * - Other values: Failure. 
     * @endif
     * @if Chinese
     * 指定视频采集设备。
     * @param device_id     视频采集设备的设备 ID。可以通过 enumerateCaptureDevices 获取。
     * @return
     * - 0：方法调用成功；
     * - 其他： 方法调用失败。
     * @endif
     */
    virtual int setDevice(const char device_id[kNERtcMaxDeviceIDLength]) = 0;
    /** 
     * @if English
     * Gets the ID of the Video capturing device that is currently used.
     * @param device_id     The audio capture device.
     * @return
     * - 0: Success.
     * - Other values: Failure. 
     * @endif
     * @if Chinese
     * 获取当前使用的视频采集设备信息。
     * @param device_id     视频采集设备的设备 ID。
     * @return
     * - 0：方法调用成功；
     * - 其他： 方法调用失败。
     * @endif
     */
    virtual int getDevice(char device_id[kNERtcMaxDeviceIDLength]) = 0;
};
} //namespace nertc

#endif
