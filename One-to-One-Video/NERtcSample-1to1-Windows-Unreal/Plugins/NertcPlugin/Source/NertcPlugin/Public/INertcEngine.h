/** @file NertcEngine.h
 * @brief The interface header file of NERTC UE SDK.
 * All parameter descriptions of the NERTC UE SDK. All string-related parameters (char *) are encoded in UTF-8.
 * @copyright (c) 2021, NetEase Inc. All rights reserved.
 */
#pragma once
#include "NertcBase.h"
#include "NertcBaseTypes.h"
#include "NertcEngineDefines.h"
#include "NertcErrorCode.h"
#include "NertcWarnCode.h"
#include "INertcEngineEventHandler.h"

#include <string>
#include <map>

namespace nertc {

/**
 * @if English
 * RtcEngineContext definition.
 * @endif
 * @if Chinese
 * RtcEngineContext 定义
 * @endif
 */
struct NERtcEngineContext {
  /**
   * @if English
   * Users register the APP key of CommsEase. If you have no APP key in your developer kit, please apply to register a new APP
   * key.
   * @endif
   * @if Chinese
   * 用户注册云信的APP Key。如果你的开发包里面缺少 APP Key，请申请注册一个新的 APP Key。
   * @endif
   */
const char* app_key;

  /**
   * @if English
   * The full path of log content are encoded in UTF-8.
   * @endif
   * @if Chinese
   * 日志目录的完整路径，采用 UTF-8 编码。
   * @endif
   */
  const char* log_dir_path;
  /**
   * @if English
   * The log level. The level is kNERtcLogLevelInfo by default.
   * @endif
   * @if Chinese
   * 日志级别，默认级别为 kNERtcLogLevelInfo。
   * @endif
   */
  NERtcLogLevel log_level;

   /**
   * @if English
   * The size of SDK-input log file. Unit: KB. If the value is set as 0, the size of log file is 20M by default.
   * @endif
   * @if Chinese
   * 指定 SDK 输出日志文件的大小上限，单位为 KB。如果设置为 0，则默认为 20 M。
   * @endif
   */
  uint32_t log_file_max_size_KBytes;

  /**
   * @if English
   * IRtcEngineEventHandler callback interface class is used to send callback event notifications to the app from SDK.
   * @endif
   * @if Chinese
   * 用于 SDK 向 App 发送回调事件通知。
   * @endif
   */
  IRtcEngineEventHandler* event_handler;


  /**
   * @if English
   * The private server address. You need to set the value as empty by default. ** To use a private server, contact technical
   * support for details.
   * @endif
   * @if Chinese
   * 私有化服务器地址，默认需要置空。如需启用私有化功能，请联系技术支持获取详情。
   * @endif
   */
  NERtcServerAddresses server_config;

NERtcEngineContext() {
app_key = nullptr;
event_handler = nullptr;
log_dir_path = nullptr;
log_level = kNERtcLogLevelWarning;
log_file_max_size_KBytes = 0;
}
};
class IRtcEngine {
public:
  virtual ~IRtcEngine() {}
 /**
 * @if English
 * Initializes the NERTC SDK service.
 * <br>After calling the createNERtcEngine to create IRtcEngine object, you must call the method to initialize before calling
 * other methods. After successfully initializing, the audio and video call mode is enabled by default.
 * @warning
 * - Callers must use the same AppKey to make audio or video calls.
 * - One IRtcEngine instance object must share the same App Key. If you need to change the AppKey, you must first call \ref
 * IRtcEngine::release "release" to destroy the current instance, and then call the method to create a new instance.
 * @param[in] context The passed RTC engine context object. NERtcEngineContext.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 初始化 NERTC SDK 服务。
 * <br>在调用 createNERtcEngine() 方法创建 IRtcEngine
 * 对象后，必须先调用该方法进行初始化，才能使用其他方法。初始化成功后，默认处于音视频通话模式。
 * @warning
 * - 必须使用同一个 App Key 才能进行通话。
 * - 一个 IRtcEngine 实例对象只能使用一个 App Key。如需更换 App Key，必须先调用 \ref IRtcEngine::release "release"
 * 方法销毁当前实例，再调用本方法重新创建实例。
 * @param[in] context 传入的RTC engine context对象: NERtcEngineContext.
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
virtual int initialize(const NERtcEngineContext& context) = 0;
/**
 * @if English
 *  Destroys an NERtc instance to release resources.
 * <br>This method releases all resources used by the NERTC SDK. In some cases, real-time audio and video communication is
 * only needed upon your demands. If no RTC calls are required, you can call this method to release resources. <br>After you
 * call the release method, other methods and callbacks supported by the SDK become unavailable. If you want to use RTC calls,
 * you must create a new NERtc instance.
 * @note If you need to use IRtcEngine instance again that cannot be initialized after release, you need to createNERtcEngine
 * after destroyNERtcEngine.
 * @param[in] sync The value is true by default, which can only be set to true. The default setting indicates synchronization
 * call of the instance. You must return before you release the resources and return the IRtcEngine object resources. <br>App
 * cannot call the interface in the callbacks returned by the SDK. If not, deadlock occurs and the SDK can only retrieve
 * related object resources before the callback is returned.  The SDK automatically detects the deadlock, and changes the
 * deadlock to asynchronous call. However, the asynchronous call consumes extra time.
 * @endif
 * @if Chinese
 * 销毁 NERtc 实例，释放资源。
 * <br>该方法释放 NERTC SDK 使用的所有资源。有些 App
 * 只在用户需要时才进行实时音视频通信，不需要时则将资源释放出来用于其他操作，该方法适用于此类情况。 <br>调用 release
 * 方法后，您将无法再使用 SDK 的其它方法和回调。如需再次使用实时音视频通话功能，您必须重新创建一个新的 NERtc 实例。
 * @note 如果需要重新使用IRtcEngine，release 后不能再 initialize，需要 destroyNERtcEngine 后重新 createNERtcEngine。
 * @param[in] sync 默认为 true 且只能设置为 true，表示同步调用，等待 IRtcEngine 对象资源释放后再返回。<br>App 不应该在 SDK
 * 产生的回调中调用该接口，否则由于 SDK 要等待回调返回才能回收相关的对象资源，会造成死锁。SDK
 * 会自动检测这种死锁并转为异步调用，但是检测本身会消耗额外的时间。
 * @endif
 */
virtual void release(bool sync = false) = 0;
/**
 * @if English
 * Sets the role of a user in live streaming.
 * <br>The method sets the role to host or audience. The permissions of a host and a viewer are different.
 * - A host has the permissions to open or close a camera, publish streams, call methods related to publishing streams in
 * interactive live streaming. The status of the host is visible to the users in the room when the host joins or leaves the
 * room.
 * - The audience has no permissions to open or close a camera, call methods related to publishing streams in interactive live
 * streaming, and is invisible to other users in the room when the user that has the audience role joins or leaves the room.
 * @note
 * - By default, a user joins a room as a host.
 * - Before a user joins a room, the user can call this method to change the client role to audience. Users can switch the
 * role of a user through the interface after joining the room.
 * - If the user switches the role to audience, the SDK automatically closes the audio and video devices.
 * @param[in] role The role of a user. NERtcClientRole.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 在直播场景中设置用户角色。
 * <br>用户角色支持设置为主播或观众，主播和观众的权限不同。
 * - 主播：可以开关摄像头等设备、可以发布流、可以操作互动直播推流相关接口、上下线对其他房间内用户可见。
 * - 观众：不可以开关摄像头等设备、不可以发布流、不可以操作互动直播推流相关接口、上下线对其他房间内用户不可见。
 * @note
 * - 默认情况下用户以主播角色加入房间。
 * - 在加入房间前，用户可以调用本接口切换本端角色为观众。在加入房间后，用户也可以通过本接口切换用户角色。
 * - 用户切换为观众角色时，SDK 会自动关闭音视频设备。
 * @param[in] role 用户角色。 NERtcClientRole
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
virtual int setClientRole(NERtcClientRole role) = 0;
/**
 * @if English
 * Sets a room scene.
 * <br>You can set a room scene for a call or live event. Different QoS policies are applied to different scenes.
 * @note You must set the profile after joining a call. The setting is invalid after the call ends.
 * @param[in] profile Sets the room scene. For more information, see NERtcChannelProfileType.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置房间场景。
 * <br>房间场景可设置为通话或直播场景，不同的场景中 QoS 策略不同。
 * @note 必须在加入通话前设置，开始通话后设置无效，结束通话后保留之前的设置。
 * @param[in] profile 设置房间场景。详细信息请参考 NERtcChannelProfileType。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
virtual int setChannelProfile(NERtcChannelProfileType profile) = 0;
/**
 * @if English
 *  Joins a channel of audio and video call.
 * <br>If the specified room does not exist when you join the room, a room with the specified name is automatically created in
the server provided by CommsEase.
 * - After you join a room by calling the relevant method supported by the SDK, users in the same room can make audio or video
calls. Users that join the same room can start a group chat. Apps that use different AppKeys cannot communicate with each
other.
 * - After the method is called successfully, the onJoinChannel callback is locally triggered, and the onUserJoined callback
is remotely triggered.
 * - If you join a room, you subscribe to the audio streams from other users in the same room by default. In this case, the
data usage is billed. To unsubscribe, you can call the setParameters method.
 * - In live streaming, audiences can switch channels by calling switchChannel.
 * @note The ID of each user must be unique.
 * @param[in] token The certification signature used in authentication (NERTC Token). Valid values:
                    - Null. You can set the value to null in the debugging mode. This poses a security risk. We recommend that
you contact your business manager to change to the default safe mode before your product is officially launched.
                    - NERTC Token acquired. In safe mode, the acquired token must be specified. If the specified token is
invalid, users are unable to join a room. We recommend that you use the safe mode.
 * @param[in] channel_name The name of the room. Users that use the same name can join the same room. The name must be of
STRING type and must be 1 to 64 characters in length. The following 89 characters are supported: a-z, A-Z, 0-9, space,
!#$%&()+-:;≤.,>? @[]^_{|}~”.
 * @param[in] uid  The unique identifier of a user. The uid of each user in a room must be unique.
                <br> uid is optional. The default value is 0. If the uid is not specified (set to 0), the SDK automatically
assigns a random uid and returns the uid in the callback of onJoinChannel. The application layer must keep and maintain the
return value. The SDK does not maintain the return value.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 加入音视频房间。
 * <br>加入音视频房间时，如果指定房间尚未创建，云信服务器内部会自动创建一个同名房间。
 * - SDK 加入房间后，同一个房间内的用户可以互相通话，多个用户加入同一个房间，可以群聊。使用不同 App Key 的 App 之间不能互通。
 * - 成功调用该方加入房间后，本地会触发onJoinChannel回调，远端会触发onUserJoined回调。
 * -
用户成功加入房间后，默认订阅房间内所有其他用户的音频流，可能会因此产生用量并影响计费。如果想取消自动订阅，可以在通话前通过调用setParameters方法实现。
 * - 直播场景中的观众角色可以通过 switchChannel 快速切换房间。
 * @note 房间内每个用户的用户 ID 必须是唯一的。
 * @param[in] token         安全认证签名（NERTC Token）。可设置为：
                            - null。调试模式下可设置为
null。安全性不高，建议在产品正式上线前在云信控制台中将鉴权方式恢复为默认的安全模式。
                            - 已获取的NERTC Token。安全模式下必须设置为获取到的 Token 。若未传入正确的 Token
将无法进入房间。推荐使用安全模式。
 * @param[in] channel_name 房间名称，设置相同房间名称的用户会进入同一个通话房间。字符串格式，长度为1~ 64
字节。支持以下89个字符：a-z, A-Z, 0-9, space, !#$%&()+-:;≤.,>? @[]^_{|}~”
 * @param[in] uid           用户的唯一标识 id，房间内每个用户的 uid 必须是唯一的。
                            <br>uid 可选，默认为 0。如果不指定（即设为 0），SDK 会自动分配一个随机 uid，并在 onJoinChannel
回调方法中返回，App 层必须记住该返回值并维护，SDK 不对该返回值进行维护。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
* @endif
*/
virtual int joinChannel(const char* token, const char* channel_name, uid_t uid, const NERtcJoinChannelOptions& channel_options) = 0;
/**
 * @if English
 * Switches to a room of audio and video call.
 * <br>In live streaming, the audience can call this method to switch from the current room to another room.
 * <br>After you switch to another room by calling the method, the local first receive the onLeaveChannel callback that the
 user leaves the room, and then receives the
 * <br>onJoinChanne callback that the user joins the new room. Remote clients receive the return from onUserLeave and
 onUserJoined.
 * @note
 * - The method applies to only the live streaming. The role is the audience in the RTC room. The room scene is set to live
 streaming by calling the setchannelprofile method, and the role of room members is set to audience by calling the
 setClientRole method.
 * - By default, after a room member switches to another room, the room member subscribes to audio streams from other members
 of the new room. In this case, data usage is charged and billing is updated. If you want to unsubscribe to the previous audio
 stream, you can call the subscribeRemoteAudio method with a value of false passed in.
 * @param[in] token The certification signature used in authentication (NERTC Token). Valid values:
                    - Null. You can set the value to null in the debugging mode. We recommend you change to the default safe
 mode before your product is officially launched.
                    - NERTC Token acquired. In safe mode, the acquired token must be specified. If the specified token is
 invalid, users are unable to join a channel. We recommend that you use the safe mode.
 * @param[in] channel_name  The room name that a user wants to switch to.

 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 快速切换音视频房间。
 * <br>房间场景为直播场景时，房间中角色为观众的成员可以调用该方法从当前房间快速切换至另一个房间。
 * <br>成功调用该方切换房间后，本端会先收到离开房间的回调 onLeaveChannel，再收到成功加入新房间的回调
 onJoinChannel。远端用户会收到 onUserLeave 和 onUserJoined 的回调。
 * @note
 * - 房间成员成功切换房间后，默认订阅房间内所有其他成员的音频流，因此产生用量并影响计费。如果想取消订阅，可以通过调用相应的
 subscribeRemoteAudio 方法传入 false 实现。
 * @param[in] token 安全认证签名（NERTC Token）。可设置为：
                    - null。调试模式下可设置为 null。建议在产品正式上线前在云信控制台中将鉴权方式恢复为默认的安全模式。
                    - 已获取的NERTC Token。安全模式下必须设置为获取到的 Token 。若未传入正确的 Token
 将无法进入房间。推荐使用安全模式。
 * @param[in] channel_name 期望切换到的目标房间名称。

 * @return
 * -0: 方法调用成功
 * -其他：方法调用失败
 * @endif
 */
virtual int switchChannel(const char* token, const char* channel_name, const NERtcJoinChannelOptions& channel_options) = 0;
/**
 * @if English
 * Switches to a room of audio and video call.
 * <br>In live streaming, the audience can call this method to switch from the current room to another room.
 * <br>After you switch to another room by calling the method, the local first receive the onLeaveChannel callback that the
 user leaves the room, and then receives the
 * <br>onJoinChanne callback that the user joins the new room. Remote clients receive the return from onUserLeave and
 onUserJoined.
 * @note
 * - Call this method to leave from the current room, and then join another room.
 * - By default, after a room member switches to another room, the room member subscribes to audio streams from other members
 of the new room. In this case, data usage is charged and billing is updated. If you want to unsubscribe to the previous audio
 stream, you can call the subscribeRemoteAudio method with a value of false passed in.
 * @param[in] token The certification signature used in authentication (NERTC Token). Valid values:
                    - Null. You can set the value to null in the debugging mode. We recommend you change to the default safe
 mode before your product is officially launched.
                    - NERTC Token acquired. In safe mode, the acquired token must be specified. If the specified token is
 invalid, users are unable to join a channel. We recommend that you use the safe mode.
 * @param[in] channel_name  The room name that a user wants to switch to.
 * @param[in] uid  The ID of user.

 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 快速切换音视频房间。
 * <br>调用该方法从当前房间leave，然后加入至另一个房间。
 * <br>成功调用该方切换房间后，本端会先收到离开房间的回调 onLeaveChannel，再收到成功加入新房间的回调
 onJoinChannel。远端用户会收到 onUserLeave 和 onUserJoined 的回调。
 * - 房间成员成功切换房间后，默认订阅房间内所有其他成员的音频流，因此产生用量并影响计费。如果想取消订阅，可以通过调用相应的
 subscribeRemoteAudio 方法传入 false 实现。
 * @param[in] token 安全认证签名（NERTC Token）。可设置为：
                    - null。调试模式下可设置为 null。建议在产品正式上线前在云信控制台中将鉴权方式恢复为默认的安全模式。
                    - 已获取的NERTC Token。安全模式下必须设置为获取到的 Token 。若未传入正确的 Token
 将无法进入房间。推荐使用安全模式。
 * @param[in] channel_name 期望切换到的目标房间名称。
 * @param[in] uid 用户ID。

 * @return
 * -0: 方法调用成功
 * -其他：方法调用失败
 * @endif
 */
virtual int switchChannelEx(const char* token, const char* channel_name, uid_t uid, const NERtcJoinChannelOptionsEx& channel_options) = 0;
/**
 * @if English
 * Leaves the room.
 * <br>Leaves a room for hang up or calls ended.
 * <br>A user can call the leaveChannel method to end the call before the user makes another call.
 * <br>After the method is called successfully, the onLeaveChannel callback is locally triggered, and the onUserLeave callback
 * is remotely triggered.
 * @note
 * - The method is asynchronous call. Users cannot exit the room when the method is called and returned. After users exit the
 * room, the SDK triggers the onLeaveChannel callback.
 * - If you call leaveChannel method and instantly call release method, the SDK cannot trigger onLeaveChannel callback.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 离开房间。
 * <br>离开房间，即挂断或退出通话。
 * <br>结束通话时，必须调用leaveChannel结束通话，否则无法开始下一次通话。
 * <br>成功调用该方法离开房间后，本地会触发onLeaveChannel回调，远端会触发onUserLeave回调。
 * @note
 * - 该方法是异步操作，调用返回时并没有真正退出房间。在真正退出房间后，SDK 会触发onLeaveChannel回调。
 * - 如果您调用了leaveChannel后立即调用release，SDK 将无法触发onLeaveChannel回调。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
virtual int leaveChannel() = 0;
/**
 * @if English
 * Gets the pointer of device administrators object.
 * @param[in] iid       The iid of interface preferred.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 获取设备管理员对象的指针。
 * @param[in] iid       想要获取的接口的iid.
 * @param[in] inter     指向 DeviceManager 对象的指针。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
virtual int queryInterface(NERtcInterfaceIdType iid, void** inter) = 0;
/**
 * @if English
 * Enables or disables local audio capture.
 * <br>The method can enable the local audio again to start local audio capture and processing.
 * <br>The method does not affect receiving or playing remote audio and audio streams.
 * @note The method is different from \ref IRtcEngineEx::muteLocalAudioStream "muteLocalAudioStream" in:.
 * - \ref IRtcEngine::enableLocalAudio "enableLocalAudio": Enables local audio capture and processing.
 * - \ref IRtcEngineEx::muteLocalAudioStream "muteLocalAudioStream": Stops or continues publishing local audio streams.
 * @note The method enables the internal engine, which is still valid after you call \ref IRtcEngine::leaveChannel
 * "leaveChannel".
 * @param[in] enabled
 * - true: Enables local audio feature again. You can enable local audio capture or processing by default.
 * - false: Disables local audio feature again. You can stop local audio capture or processing.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 开启/关闭本地音频采集
 * <br>该方法可以重新开启本地语音功能，重新开始本地音频采集及处理。
 * <br>该方法不影响接收或播放远端音频流。
 * @note 该方法与 \ref IRtcEngineEx::muteLocalAudioStream "muteLocalAudioStream" 的区别在于:
 * - \ref IRtcEngine::enableLocalAudio "enableLocalAudio": 开启本地语音采集及处理
 * - \ref IRtcEngineEx::muteLocalAudioStream "muteLocalAudioStream": 停止或继续发送本地音频流
 * @note 该方法设置内部引擎为启用状态，在 \ref IRtcEngine::leaveChannel "leaveChannel" 后仍然有效。
 * @param[in] type      音频流类型:
 * @param[in] enabled
 * - true: 重新开启本地语音功能，即开启本地语音采集或处理（默认）
 * - false: 关闭本地语音功能，即停止本地语音采集或处理
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
virtual int enableLocalAudio(NERtcAudioStreamType type, bool enabled) = 0;
};
}