#ifndef NERTC_ENGINE_H
#define NERTC_ENGINE_H

#include "nertc_engine_events.h"
#include "nertc_media_stats_observer.h"

NERTC_BEGIN_DECLS

/**
 * @if English
 * RtcEngineContext definition.
 * @endif
 * @if Chinese
 * RtcEngineContext 定义
 * @endif
 */
struct nertc_engine_context{
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
  nertc_log_level log_level;

   /**
   * @if English
   * The size of SDK-input log file. Unit: KB. If the value is set as 0, the size of log file is 20M by default.
   * @endif
   * @if Chinese
   * 指定 SDK 输出日志文件的大小上限，单位为 KB。如果设置为 0，则默认为 20 M。
   * @endif
   */
  uint32_t log_file_max_size_kbytes;

  /**
   * @if English
   * IRtcEngineEventHandler callback interface class is used to send callback event notifications to the app from SDK.
   * @endif
   * @if Chinese
   * 用于 SDK 向 App 发送回调事件通知。
   * @endif
   */
  struct nertc_engine_events events;

  /**
   * @if English
   * The private server address. You need to set the value as empty by default. ** To use a private server, contact technical
   * support for details.
   * @endif
   * @if Chinese
   * 私有化服务器地址，默认需要置空。如需启用私有化功能，请联系技术支持获取详情。
   * @endif
   */
  struct nertc_server_addresses server_config;
};

/**
 * @if English
 * Creates an RTC engine object and returns the pointer.
 * @note Only one nertc_engine object is supported at the same time. You must release an nertc_engine before creating a new
 * instance.
 * @return The pointer of the RTC engine object.
 * @endif
 * @if Chinese
 * 创建 RTC 引擎对象并返回指针。
 * @note 同时只支持一个nertc_engine对象，新创建前必须先释放前一个nertc_engine。
 * @return RTC 引擎对象的指针。
 * @endif
 */
NERTC_API struct nertc_engine* NERTC_CALL create_nertc_engine();

/**
 * @if English
 * Destroys RTC engine object.
 * @note Call \ref nertc_engine_release "release" first before releasing.
 * @endif
 * @if Chinese
 * 销毁 RTC 引擎对象。
 * @note 释放前需要先调用\ref nertc_engine_release "release"
 * @endif
 */
NERTC_API void NERTC_CALL destroy_nertc_engine(struct nertc_engine* engine);

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
NERTC_API int NERTC_CALL nertc_engine_init(struct nertc_engine* self, const struct nertc_engine_context* param);

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
NERTC_API void NERTC_CALL nertc_engine_release(struct nertc_engine* self, bool sync);

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
NERTC_API int NERTC_CALL nertc_engine_set_client_role(struct nertc_engine* self, nertc_client_role role);

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
NERTC_API int NERTC_CALL nertc_engine_set_channel_profile(struct nertc_engine* self, nertc_channel_profile_type profile);

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
NERTC_API int NERTC_CALL nertc_engine_join_channel(struct nertc_engine* self,
                                                   const char* token,
                                                   const char* channel_name,
                                                   nertc_uid_t uid,
                                                   struct nertc_join_channel_options* channel_options);

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
 * - 该方法仅适用于直播场景中，角色为观众的音视频房间成员。即已通过接口 setchannelprofile 设置房间场景为直播，通过
 setClientRole 设置房间成员的角色为观众。
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
NERTC_API int NERTC_CALL nertc_engine_switch_channel(struct nertc_engine* self,
                                                     const char* token,
                                                     const char* channel_name,
                                                     struct nertc_join_channel_options* channel_options);
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
NERTC_API int NERTC_CALL nertc_engine_switch_channel_ex(struct nertc_engine* self,
                                                     const char* token,
                                                     const char* channel_name,
                                                     nertc_uid_t uid,
                                                     struct nertc_join_channel_options_ex* channel_options_ex);

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
NERTC_API int NERTC_CALL nertc_engine_leave_channel(struct nertc_engine* self);

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
NERTC_API void* NERTC_CALL nertc_engine_query_interface(struct nertc_engine* self,nertc_interface_id_type iid);

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
NERTC_API int NERTC_CALL nertc_engine_enable_local_audio(struct nertc_engine* self, nertc_audio_stream_type stream_type, bool enabled);

/**
 * @if English
 * Sets local views.
 * <br>This method is used to set the display information about the local video. The method is applicable for only local
 * users. Remote users are not affected. <br>Apps can call this API operation to associate with the view that plays local
 * video streams. During application development, in most cases, before joining a room, you must first call this method to set
 * the local video view after the SDK is initialized.
 * @note  If you use external rendering on the Mac platform, you must set the rendering before the SDK is initialized.
 * @param[in] canvas The video canvas information.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置本地视图。
 * <br>该方法设置本地视频显示信息。只影响本地用户看到的视频画面，不影响远端。
 * <br>App 通过调用此接口绑定本地视频流的显示视窗(view)。 在 App
 * 开发中，通常在初始化后调用该方法进行本地视频设置，然后再加入房间。
 * @note mac端若使用外部渲染，必须在 SDK 初始化时设置。
 * @param[in] canvas 视频画布信息
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_setup_local_video_canvas(struct nertc_engine* self,
                                                               nertc_video_stream_type type,
                                                               struct nertc_video_canvas* canvas);

/**
 * @if English
 *  Sets views for remote users.
 * <br>This method is used to associate remote users with display views and configure the rendering mode and mirror mode for
 * remote views that are displayed locally. The method affects only video display viewed by local users.
 * @note
 * - You need to specify the uid of remote video when the interface is called. In general cases, the uid can be set before
 * users join the room.
 * - If the user ID is not retrieved, the App calls this method after the onUserJoined event is triggered. To disassociate a
 * specified user from a view, you can leave the canvas parameter empty.
 * - After a user leaves the room, the association between a remote user and the view is cleared.
 * @param[in] uid       The ID of a remote user.
 * @param[in] canvas    The video canvas information.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 设置远端用户视图。
 * <br>该方法绑定远端用户和显示视图，并设置远端用户视图在本地显示时的渲染模式和镜像模式，只影响本地用户看到的视频画面。
 * @note
 * - 调用该接口时需要指定远端视频的 uid，一般可以在用户加入后设置好。
 * - 如果 App 无法事先知道对方的用户 ID，可以在 APP 收到 onUserJoined 事件时设置。- 解除某个用户的绑定视图可以把 canvas
 * 设置为空。
 * - 退出房间后，SDK 会清除远程用户和视图的绑定关系。
 * @param[in] uid       远端用户 ID。
 * @param[in] canvas    视频画布信息
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_setup_remote_video_canvas(struct nertc_engine* self,
                                                                nertc_uid_t uid,
                                                                nertc_video_stream_type type,
                                                                struct nertc_video_canvas* canvas);

/**
 * @if English
 * Enables or disables local audio capture and rendering.
 * <br>The method enables local video capture.
 * @note
 * - You can call this method before or after you join a room.
 * - The method enables the internal engine, which is still valid after you call \ref IRtcEngine::leaveChannel "leaveChannel".
 * - After local video capture is successfully enabled or disabled,  the onUserVideoStop or onUserVideoStart callback is
 * remotely triggered.
 * @param[in] enabled Whether to enable local video capture and rendering.
 * - true: Enables the local video capture and rendering.
 * - false: Disables the local camera device. After local video capture is disabled, remote users cannot receive video streams
 * from local users. However, local users can still receive video streams from remote users. If the setting is false, the
 * local camera is not required to call the method.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 开启或关闭本地视频采集和渲染。
 * <br>该方法启用本地视频采集功能。
 * @note
 * - 该方法在加入房间前和加入房间后均可调用。
 * - 该方法设置内部引擎为启用状态，在 \ref IRtcEngine::leaveChannel "leaveChannel" 后仍然有效。
 * - 成功启用或禁用本地视频采集和渲染后，远端会触发 onUserVideoStop 或 onUserVideoStart  回调。
 * @param[in] enabled 是否启用本地视频采集和渲染:
 * - true: 开启本地视频采集和渲染 (默认)；
 * - false: 关闭使用本地摄像头设备。关闭后，远端用户会接收不到本地用户的视频流；但本地用户依然可以接收远端用户的视频流。设置为
 * false 时，该方法不需要本地有摄像头。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_enable_local_video(struct nertc_engine* self, nertc_video_stream_type stream_type, bool enabled);

/**
 * @if English
 * Subscribes or unsubscribes video streams from specified remote users.
 * - After a user joins a room, the video streams from remote users are not subscribed by default. If you want to view video
 * streams from specified remote users, you can call this method to subscribe to the video streams from the user when the user
 * joins the room or publishes the video streams.
 * - This method can be called only if a user joins a room.
 * @param[in] uid       The user ID.
 * @param[in] type      The type of the subscribed video streams. #NERtcRemoteVideoStreamType.
 * @param[in] subscribe
 * - true: Subscribes to specified video streams. This is the default value.
 * - false: Not subscribing to specified video streams.
 * @return
 * - 0: Success.
 * - Other values: Failure.
 * @endif
 * @if Chinese
 * 订阅或取消订阅指定远端用户的视频流。
 * -
 * 用户加入房间之后，默认不订阅远端用户的视频流，如果希望看到指定远端用户的视频，可以在监听到对方加入房间或发布视频流之后，通过此方法订阅该用户的视频流。
 * - 该方法需要在加入房间后调用。
 * @param[in] uid       指定用户的用户 ID。
 * @param[in] type      订阅的视频流类型。 #NERtcRemoteVideoStreamType
 * @param[in] subscribe
 * - true: （默认）订阅指定视频流。
 * - false: 不订阅指定视频流。
 * @return
 * - 0: 方法调用成功；
 * - 其他: 方法调用失败。
 * @endif
 */

NERTC_API int NERTC_CALL nertc_engine_subscribe_remote_video_stream(struct nertc_engine* self,
                                                                    nertc_uid_t uid,
                                                                    nertc_video_stream_type type,
                                                                    nertc_remote_video_stream_type stream_type,
                                                                    bool subscribe);

/**
 * @if English
 * Switches between the front and rear cameras.
 * <br>Make sure that you call this method after the camera starts. For example, you can call this method after you call
 * startPreview or joinChannel.
 * @note The audio-only SDK disables this API. If you need to use the API, you can download the standard SDK from the official
 * website of CommsEase and replace the audio-only SDK.
 * @return The value returned. A value of 0 indicates that the operation is successful.
 * @endif
 * @if Chinese
 * 切换前置/后置摄像头。
 * <br>该方法需要在相机启动后调用，例如调用 startPreview 或 joinChannel 后。
 * @note 纯音频 SDK 禁用该接口，如需使用请前往云信官网下载并替换成视频 SDK。
 * @return 操作返回值，成功则返回 0
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_switch_camera(struct nertc_engine* self);

/**
 * @if English
 * @endif
 * @if Chinese
 * 指定前置/后置摄像头。
 * <br>该方法需要在相机启动后调用，例如调用 StartPreview 或 joinChannel 后。
 * @note 纯音频 SDK 禁用该接口，如需使用请前往云信官网下载并替换成视频 SDK。
 * @since V4.6.10
 * @param position 摄像头类型。详细信息请参考 {@link RtcCameraPosition}。该参数为必填参数，若未赋值，SDK 会报错。
 * @return
 * - 0：方法调用成功。
 * - 其他：方法调用失败。
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_switch_camera_with_position(struct nertc_engine* self, nertc_camera_position position);
/**
 * @if English
 * Gets the current camera direction.
 * - This method is used to check whether the current camera is front-facing or rear.
 * - Call this method after enabling the local camera. That said, you can call this method before calling startVideoPreview or
 * joinChannel, depending on which method you use to turn on your local camera.（only for Android）
 * @since V4.5.0
 * @return
 * - {@code 0}：The rear camera.
 * - Others：The front camera.
 * @endif
 * @if Chinese
 * 查看当前摄像头配置。
 * - 该方法用于查看当前使用的摄像头为前置摄像头还是后置摄像头。
 * - 该方法需要在相机启动后调用，例如调用 startVideoPreview 或 joinChannel 后。（仅Android有效）
 * @since V4.5.0
 * @return
 * - {@code 0}：后置摄像头
 * - 其他值：前置摄像头
 * @endif
 */
NERTC_API int NERTC_CALL nertc_engine_get_current_camera(struct nertc_engine* self);

NERTC_END_DECLS

#endif  // NERTC_ENGINE_H
