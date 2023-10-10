#ifndef NERTC_DEFINES_H
#define NERTC_DEFINES_H

#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif

#ifdef  __cplusplus
#define NERTC_BEGIN_DECLS  extern "C" {
#define NERTC_END_DECLS    }
#else
#define NERTC_BEGIN_DECLS
#define NERTC_END_DECLS
#endif

#ifdef WIN32
#define NERTC_API __declspec(dllexport)
#define NERTC_CALL __cdecl
#else
#define NERTC_API __attribute__ ((visibility ("default")))
#define NERTC_CALL
#endif
/**
 * @if English
 * Video max plane count.
 * @endif
 * @if Chinese
 * Video max plane count.
 * @endif
 */
#define kNERtcMaxPlaneCount 4
/**
 * @if English
 * The length of the encryption key.
 * @endif
 * @if Chinese
 * 加密key的长度
 * @endif
 */
#define kNERtcEncryptByteLength 128
/**
 * @if Chinese
 * 自定义信息的长度
 * @endif
 */
#define kNERtcCustomInfoLength 128
/**
 * @if English
 * Maximum length of a room ID.
 * @endif
 * @if Chinese
 * 房间ID最大长度
 * @endif
 */
#define kNERtcMaxChannelNameLength 128
/**
 * @if English
 * maximum token length.
 * @endif
 * @if Chinese
 * token最大长度
 * @endif
 */
#define kNERtcMaxTokenLength 256
/**
 * @if English
 * Maximum length of a device ID.
 * @endif
 * @if Chinese
 * 设备ID最大长度。
 * @endif
 */
#define kNERtcMaxDeviceIDLength 256
/**
 * @if English
 * Maximum length of a device name.
 * @endif
 * @if Chinese
 * 设备名最大长度。
 * @endif
 */
#define kNERtcMaxDeviceNameLength 256
/**
 * @if English
 * Maximum length of the URI.
 * @endif
 * @if Chinese
 * URI最大长度。
 * @endif
 */
#define kNERtcMaxURILength 256
/**
 * @if English
 * Maximum length of the task ID.
 * @endif
 * @if Chinese
 * 任务ID最大长度。
 * @endif
 */
#define kNERtcMaxTaskIDLength 64
/**
 * @if English
 * Maximum length of the string buffer.
 * @endif
 * @if Chinese
 * 字符串缓存区最大长度。
 * @endif
 */
#define kNERtcMaxBuffLength 1024
/**
 * @if English
 * Maximum length of SEI information used in live streaming. Unit: bytes.
 * @endif
 * @if Chinese
 * 直播推流中用到的SEI信息最大长度，单位：字节
 * @endif
 */
#define kNERtcMaxSEIBufferLength 4096
/**
 * @if English
 * Device ID of an external video input source. After you enable external input, you must set this device ID using setDevice.
 * @endif
 * @if Chinese
 * 外部视频输入源设备ID，开启外部输入之后，需要通过setDevice设置此设备ID。
 * @endif
 */
#define kNERtcExternalVideoDeviceID "nertc-video-external-device"
/**
 * @if English
 * The audio device automatically selects the ID. When the ID is set as the device, the SDK will automatically select the
 * appropriate audio device based on the device management system settings.
 * @endif
 * @if Chinese
 * 音频设备自动选择ID，设置该ID为设备时，SDK会根据设备插拔系统设置等自动选择合适音频设备。
 * @endif
 */
#define kNERtcAudioDeviceAutoID "nertc-audio-device-auto"

/**
 * @if English
 * 64-bit unsigned integer. Recommended setting range: 1 to 2 <sup>63</sup> -1, and make sure the number is unique.
 * @endif
 * @if Chinese
 * 64位无符号整数。建议设置范围：1到 2<sup>63</sup>-1，并保证唯一性。
 * @endif
 */
typedef uint64_t nertc_uid_t;
/**
 * @if English
 * 64-bit unsigned integer. Recommended setting range: 1 to 2 <sup>63</sup> -1, and make sure the number is unique.
 * @endif
 * @if Chinese
 * 64位无符号整数。建议设置范围：1到 2<sup>63</sup>-1，并保证唯一性。
 * @endif
 */
typedef uint64_t channel_id_t;
/**
 * @if English
 * Identify the source of the screen capture from a window or screen. If the source is a window, the type will be converted to
 * HWND on Windows, and it will be converted to the INT data type on macOS. If the source is screen, the source type will be
 * converted to the INT data type.
 * @endif
 * @if Chinese
 * 用于标识屏幕捕捉的源，代表某个窗口或屏幕。源为窗口时, Windows上该类型会转换为HWND, MAC上转换为整形。源为屏幕时会转换为整形。
 * @endif
 */
typedef void* source_id_t;


/**
 * @if English
 * Interface ID type.
 *
 * @endif
 * @if Chinese
 * 接口ID类型。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * Get the interface ID of the audio device manager.
   * @endif
   * @if Chinese
   * 获取音频设备管理器的接口ID
   * @endif
   */
  kNERtcIIDAudioDeviceManager = 1,
  /**
   * @if English
   * Get the interface ID of the video device manager.
   * @endif
   * @if Chinese
   * 获取视频设备管理器的接口ID
   * @endif
   */
  kNERtcIIDVideoDeviceManager = 2,
} nertc_interface_id_type;

/**
 * @if English
 * Participant role type.
 * @endif
 * @if Chinese
 * 参会者角色类型
 * @endif
 */
typedef enum {
  /**
   * @if English
   * The host role in live streaming. The host has the permissions to open or close audio and video devices, such as a camera,
   * publish streams, and configure streaming tasks in interactive live streaming. The status of the host is visible to the
   * users in the room when the host joins or leaves the room.
   * @endif
   * @if Chinese
   * （默认）直播模式中的主播，可以操作摄像头等音视频设备、发布流、配置互动直播推流任务、上下线对房间内其他用户可见。
   * @endif
   */
  kNERtcClientRoleBroadcaster = 0,
  /**
   * @if English
   * The audience role in live streaming. The audience can only receive audio and video streams, and cannot manage audio and
   * video devices, and configure streaming tasks in interactive live streaming. The status of an audience is invisible to the
   * users in the room when the audience joins or leaves the room.
   * @endif
   * @if Chinese
   * 直播模式中的观众，观众只能接收音视频流，不支持操作音视频设备、配置互动直播推流任务、上下线不通知其他用户。
   * @endif
   */
  kNERtcClientRoleAudience = 1,
} nertc_client_role;

/**
 * @if English
 * Scenario types.
 * @endif
 * @if Chinese
 * 场景模式。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * Communication mode。
   * @endif
   * @if Chinese
   * 通话场景
   * @endif
   */
  kNERtcChannelProfileCommunication = 0,
  /**
   * @if English
   * Live streaming mode.
   * @endif
   * @if Chinese
   * 直播推流场景
   * @endif
   */
  kNERtcChannelProfileLiveBroadcasting = 1,
} nertc_channel_profile_type;


/**
 * @if English
 * Media priority type.
 * @endif
 * @if Chinese
 * 媒体优先级类型。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * High priority
   * @endif
   * @if Chinese
   * 高优先级
   * @endif
   */
  kNERtcMediaPriorityHigh = 50,
  /**
   * @if English
   * Normal priority (default)
   * @endif
   * @if Chinese
   * （默认）普通优先级
   * @endif
   */
  kNERtcMediaPriorityNormal = 100,
} nertc_media_priority_type;

/**
 * @if English
 * Co-hosting method.
 * @endif
 * @if Chinese
 * 连麦方式。
 * @endif
 */
typedef enum {
  kNERtcLayoutFloatingRightVertical = 0,
  kNERtcLayoutFloatingLeftVertical,
  kNERtcLayoutSplitScreen,
  kNERtcLayoutSplitScreenScaling,
  kNERtcLayoutCustom,
  kNERtcLayoutAudioOnly,
} nertc_live_stream_layout_mode;

/**
 * @if English
 * Configuration of streaming tasks.
 * @endif
 * @if Chinese
 * 直播推流任务的配置项。
 * @endif
 */
struct nertc_live_stream_task_option {
  /**
   * @if English
   * Streaming task ID, which is the unique identifier of a streaming task. You can use the ID to create and delete streaming
   * tasks.
   * @endif
   * @if Chinese
   * 推流任务ID，为推流任务的唯一标识，用于过程中增删任务操作。
   * @endif
   */
  char task_id[kNERtcMaxTaskIDLength];
  /**
   * @if English
   * Live streaming URL address.
   * @endif
   * @if Chinese
   * 直播推流地址。
   * @endif
   */
  char stream_url[kNERtcMaxURILength];
  /**
   * @if English
   * Enable or disable server recording. The default value is false.
   * @endif
   * @if Chinese
   * 服务器录制功能是否开启，默认值为 false。
   * @endif
   */
  bool server_record_enabled;
  /**
   * @if English
   * Co-hosting method. The default value is kNERtcLayoutFloatingRightVertical.
   * @endif
   * @if Chinese
   * 连麦方式，默认值为 kNERtcLayoutFloatingRightVertical。
   * @endif
   */
  nertc_live_stream_layout_mode layout_mode;
  /**
   * @if English
   * Specify the main picture uid (optional).
   * @endif
   * @if Chinese
   * 指定大画面uid（选填）。
   * @endif
   */
  nertc_uid_t main_picture_account_id;
  /**
   * @if English
   * Custom layout parameters in JSON format (optional). You need to set the layout parameters only when layout_mode is set to
   * kNERtcLayoutCustom or kNERtcLayoutAudioOnly.
   * @endif
   * @if Chinese
   * 自定义布局参数（选填），JSON 字符串格式, 只有当layout_mode为 kNERtcLayoutCustom 或 kNERtcLayoutAudioOnly时才需要设置。
   * @endif
   */
  char layout_parameters[kNERtcMaxBuffLength];
};

/**
 * @if English
 * Streaming mode in live streaming.
 * @endif
 * @if Chinese
 * 直播推流模式
 * @endif
 */
typedef enum {
  /**
   * @if English
   * Publish the video stream.
   * @endif
   * @if Chinese
   * 推流带视频
   * @endif
   */
  kNERtcLsModeVideo = 0,
  /**
   * @if English
   * Publish audio-only stream.
   * @endif
   * @if Chinese
   * 推流纯音频
   * @endif
   */
  kNERtcLsModeAudio = 1,
} nertc_live_stream_mode;

/**
 * @if English
 * Video cropping mode in live streaming
 * @endif
 * @if Chinese
 * 直播推流视频裁剪模式
 * @endif
 */
typedef enum {
  /**
   * @if English
   * 0: Video dimensions are scaled proportionally. All video content is prioritized for display. If the video dimensions do not
   * match the display window, the unfilled area of the window will be filled with the background color.
   * @endif
   * @if Chinese
   * 0: 视频尺寸等比缩放。优先保证视频内容全部显示。因视频尺寸与显示视窗尺寸不一致造成的视窗未被填满的区域填充背景色。
   * @endif
   */
  kNERtcLsModeVideoScaleFit = 0,
  /**
   * @if English
   * 1: Video dimensions are scaled proportionally. The window is prioritized to be filled. The extra video due to the
   * inconsistency between the video size and the display window size will be cropped off.
   * @endif
   * @if Chinese
   * 1: 视频尺寸等比缩放。优先保证视窗被填满。因视频尺寸与显示视窗尺寸不一致而多出的视频将被截掉。
   * @endif
   */
  kNERtcLsModeVideoScaleCropFill = 1,
} nertc_live_stream_video_scale_mode;

/**
 * @if English
 * The member layout in live streaming.
 * @endif
 * @if Chinese
 * 直播成员布局
 * @endif
 */
struct nertc_live_stream_user_transcoding {
  /**
   * @if English
   * Pulls the video stream of the user with the specified uid into the live event. If you add multiple users, the uid must be
   * unique.
   * @endif
   * @if Chinese
   * 将指定uid对应用户的视频流拉入直播。如果添加多个 users，则 uid 不能重复。
   * @endif
   */
  nertc_uid_t uid;
  /**
   * @if English
   * Specifies whether to play back the specific video stream from the user to viewers in the live event. Valid values:
   * - true: plays the video stream.
   * - false: does not play the video stream.
   * The setting becomes invalid when the streaming mode is set to kNERtcLsModeAudio.
   * @endif
   * @if Chinese
   * 是否在直播中向观看者播放该用户的对应视频流。可设置为：
   * - true：在直播中播放该用户的视频流。
   * - false：在直播中不播放该用户的视频流。
   * 推流模式为 kNERtcLsModeAudio 时无效。
   * @endif
   */
  bool video_push;
  /**
   * @if English
   * Adjustment between the video and the canvas in live streaming. For more information, see NERtcLiveStreamVideoScaleMode.
   * @endif
   * @if Chinese
   * 直播推流视频和画布的调节属性。详细信息请参考 NERtcLiveStreamVideoScaleMode。
   * @endif
   */
  nertc_live_stream_video_scale_mode adaption;
  /**
   * @if English
   * The X parameter is used to set the horizontal coordinate value of the user image. You can specify a point in the canvas
   * with X and Y coordinates. This point is used as the anchor of the upper left corner of the user image.
   * - Value range: 0 to 1920. If the specified value is set to an odd value, the value is automatically rounded down to an even
   * number.
   * - If the user image exceeds the canvas, an error occurs when you call the method.
   * @endif
   * @if Chinese
   * x 参数用于设置用户图像的横轴坐标值。通过 x 和 y 指定画布坐标中的一个点，该点将作为用户图像的左上角。
   * - 取值范围为 0~1920，若设置为奇数值，会自动向下取偶。
   * - 用户图像范围如果超出超出画布，调用方法时会报错。
   * @endif
   */
  int x;
  /**
   * @if English
   * The Y parameter is used to set the vertical coordinate value of the user image. You can specify a point in the canvas with
   * X and Y coordinates. This point is used as the anchor of the upper left corner of the user image.
   * - Value range: 0 to 1920. If the specified value is set to an odd value, the value is automatically rounded down to an even
   * number.
   * - If the user image exceeds the canvas, an error occurs when you call the method.
   * @endif
   * @if Chinese
   * y参数用于设置用户图像的纵轴坐标值。通过 x 和 y 指定画布坐标中的一个点，该点将作为用户图像的左上角。
   * - 取值范围为 0~1920，若设置为奇数值，会自动向下取偶。
   * - 用户图像范围如果超出超出画布，调用方法时会报错。
   * @endif
   */
  int y;
  /**
   * @if English
   * The width of the user image in the canvas.
   * - Value range: 0 to 1920. The default value is 0. If the specified value is set to an odd value, the value is automatically
   * rounded down to an even number.
   * - If the user image exceeds the canvas, an error occurs when you call the method.
   * @endif
   * @if Chinese
   * 该用户图像在画布中的宽度。
   * - 取值范围为 0~1920，默认为0。若设置为奇数值，会自动向下取偶。
   * - 用户图像范围如果超出超出画布，调用方法时会报错。
   *
   * @endif
   */
  int width;
  /**
   * @if English
   * The height of the user image in the canvas.
   * - The X parameter is used to set the horizontal coordinate value of the user image. You can specify a point in the canvas
   * with X and Y coordinates. This point is used as the anchor of the upper left corner of the user image. 0 to 1920. The
   * default value is 0. If the specified value is set to an odd value, the value is automatically rounded down to an even
   * number.
   * - Value range: 0 to 1920. If the specified value is set to an odd value, the value is automatically rounded down to an even
   * number.
   * @endif
   * @if Chinese
   * 该用户图像在画布中的高度。
   * - 取值范围为 0~1920，默认为0。若设置为奇数值，会自动向下取偶。
   * - 用户图像范围如果超出超出画布，调用方法时会报错。
   * @endif
   */
  int height;
  /**
   * @if English
   * Specifies whether to mix the audio stream from the user in the live event. Valid values:
   * - true: mixes the audio streams from users in a live event.
   * - false: mutes the audio streams from users in a live event.
   * @endif
   * @if Chinese
   * 是否在直播中混流该用户的对应音频流。可设置为：
   * - true：在直播中混流该用户的对应音频流。
   * - false：在直播中将该用户设置为静音。
   * @endif
   */
  bool audio_push;
  /**
   * @if English
   * The layer number that is used to determine the rendering level. Value range: 0 to 100. A value of 0 indicates the bottom
   * layer and 100 indicates the top layer. <br>The rendering area at the same level is overwritten based on the existing
   * overlay strategy. Rendering is performed in the order of the array, and the index increases in ascending order.
   * @endif
   * @if Chinese
   * 图层编号，用来决定渲染层级, 取值0-100，0位于最底层，100位于最顶层。
   * 相同层级的渲染区域按照现有的覆盖逻辑实现，即按照数组中顺序进行渲染，index 递增依次往上叠加。
   * @endif
   */
  int z_order;
};

/**
 * @if English
 * Picture layout.
 * @endif
 * @if Chinese
 * 图片布局
 * @endif
 */
struct nertc_live_stream_image_info {
  /**
   * @if English
   * The URL of the placeholder image.
   * @endif
   * @if Chinese
   * 占位图片的URL。
   * @endif
   */
  char url[kNERtcMaxURILength];
  /**
   * @if English
   * The X parameter is used to set the horizontal coordinate value of the canvas.
   * You can specify a point in the canvas with X and Y coordinates. This point is used as the anchor of the upper left corner
   * of the placeholder image. Value range: 0 to 1920. If the specified value is set to an odd value, the value is automatically
   * rounded down to an even number.
   * @endif
   * @if Chinese
   * x 参数用于设置画布的横轴坐标值。
   * 通过 x 和 y 指定画布坐标中的一个点，该点将作为占位图片的左上角。
   * 取值范围为 0~1920，若设置为奇数值，会自动向下取偶。
   * @endif
   */
  int x;
  /**
   * @if English
   * The Y parameter is used to set the vertical coordinate value of the canvas.
   * - You can specify a point in the canvas with X and Y coordinates. This point is used as the anchor of the upper left corner
   * of the placeholder image.
   * - Value range: 0 to 1920. If the specified value is set to an odd value, the value is automatically rounded down to an even
   * number.
   * @endif
   * @if Chinese
   * y 参数用于设置画布的纵轴坐标值。
   * - 通过 x 和 y 指定画布坐标中的一个点，该点将作为占位图片的左上角。
   * - 取值范围为 0~1920，若设置为奇数值，会自动向下取偶。
   * @endif
   */
  int y;
  /**
   * @if English
   * The width of the placeholder image in the canvas.
   * <br>Value range: 0 to 1920. If the specified value is set to an odd value, the value is automatically rounded down to an
   * even number.
   * @endif
   * @if Chinese
   * 该占位图片在画布中的宽度。
   * <br>取值范围为 0~1920，若设置为奇数值，会自动向下取偶。
   * @endif
   */
  int width;
  /**
   * @if English
   * The height of the placeholder image in the canvas.
   * <br>Value range: 0 to 1920. If the specified value is set to an odd value, the value is automatically rounded down to an
   * even number.
   * @endif
   * @if Chinese
   * 该占位图片在画布中的高度。
   * <br>取值范围为 0~1920，若设置为奇数值，会自动向下取偶。
   * @endif
   */
  int height;
  /**
   * @if Chinese
   * 占位图的图层编号，用来决定渲染层级。
   * <br>取值范围为 0~100，默认为 0。
   * - 最小值为 0（默认值），表示该区域图像位于最底层。
   * - 最大值为 100，表示该区域图像位于最顶层。
   * <br><b>注意</b>：相同层级的渲染区域会按照数组中顺序进行渲染，随着 index 递增，依次往上叠加。
   * @endif
   */
  int z_order;
};


/**
 * @if English
 * The live streaming layout.
 * @endif
 * @if Chinese
 * 直播布局
 * @endif
 */
struct nertc_live_stream_layout {
  /**
   * @if English
   * The width of the overall canvas. Unit: px. Value range: 0 to 1920. If the specified value is set to an odd value, the value
   * is automatically rounded down to an even number.
   * @endif
   * @if Chinese
   * 整体画布的宽度，单位为 px。取值范围为 0~1920，若设置为奇数值，会自动向下取偶。
   * @endif
   */
  int width;
  /**
   * @if English
   * The height of the overall canvas. Unit: - true: 0 to 1920. If the specified value is set to an odd value, the value is
   * automatically rounded down to an even number.
   * @endif
   * @if Chinese
   * 整体画布的高度，单位为 px。取值范围为 0~1920，若设置为奇数值，会自动向下取偶。
   * @endif
   */
  int height;
  /**
   * @if English
   * The background color of the canvas. The value of the background color is the sum of 256 x 256 x R + 256 x G + B. Enter the
   * corresponding RGB values into this formula to calculate the value. If the value is unspecified, the default value is 0.
   * @endif
   * @if Chinese
   * 画面背景颜色，格式为 256 x 256 x R + 256 x G + B的和。请将对应 RGB 的值分别带入此公式计算即可。若未设置，则默认为0。
   * @endif
   */
  unsigned int background_color;
  /**
   * @if English
   * The member layout in live streaming.
   * @endif
   * @if Chinese
   * 成员布局个数。
   * @endif
   */
  unsigned int user_count;
  /**
   * @if English
   * The member layout array. For more information, see NERtcLiveStreamUserTranscoding.
   * @endif
   * @if Chinese
   * 成员布局数组，详细信息请参考 NERtcLiveStreamUserTranscoding。
   * @endif
   */
  nertc_live_stream_user_transcoding* users;
  /**
   * @if English
   * For more information, see NERtcLiveStreamImageInfo.
   * @endif
   * @if Chinese
   * 详细信息请参考 NERtcLiveStreamImageInfo。
   * @endif
   */
  nertc_live_stream_image_info* bg_image;

  /**
   * @if English
   * The member of picture layout.
   * @endif
   * @if Chinese
   * 图片布局个数。
   * @endif
   */
   int bg_image_count;
};

/**
 * @if English
 * Live streaming audio sample rate
 * @endif
 * @if Chinese
 * 直播推流音频采样率
 * @endif
 */
typedef enum {
  /**
   * @if English
   * The sample rate is 32 kHz.
   * @endif
   * @if Chinese
   * 采样率为 32 kHz。
   * @endif
   */
  kNERtcLiveStreamAudioSampleRate32000 = 32000,
  /**
   * @if English
   * The sample rate is 44.1 kHz.
   * @endif
   * @if Chinese
   * 采样率为 44.1 kHz。
   * @endif
   */
  kNERtcLiveStreamAudioSampleRate44100 = 44100,
  /**
   * @if English
   * (Default) The sample rate is 48 kHz.
   * @endif
   * @if Chinese
   * （默认）采样率为 48 kHz。
   * @endif
   */
  kNERtcLiveStreamAudioSampleRate48000 = 48000,
} nertc_live_stream_audio_sample_rate;


/**
 * @if English
 * Live streaming audio codec profile
 * @endif
 * @if Chinese
 * 直播推流音频编码规格
 * @endif
 */
typedef enum {
  /**
   * @if English
   * (Default) LC- AAC, the basic audio encoding profile.
   * @endif
   * @if Chinese
   * （默认）LC-AAC 规格，表示基本音频编码规格。
   * @endif
   */
  kNERtcLiveStreamAudioCodecProfileLCAAC = 0,
  /**
   * @if English
   * HE-AAC, high-efficiency audio encoding profile.
   * @endif
   * @if Chinese
   * HE-AAC 规格，表示高效音频编码规格。
   * @endif
   */
  kNERtcLiveStreamAudioCodecProfileHEAAC = 1,
} nertc_live_stream_audio_codec_profile;

/**
 * @if English
 * Streaming configuration.
 * @endif
 * @if Chinese
 * 直播流配置
 * @endif
 */
struct nertc_live_stream_config {
  /**
   * @if English
   * Enables or disables single video pass-through. By default, the setting is disabled.
   * - If you enable video pass-through, and the room ingests only one video stream, then, the stream is not transcoded and does
   * not follow the transcoding flow. The video stream is directly published to a CDN.
   * - If multiple video streams from different room members are mixed into one video stream, this setting becomes invalid, and
   * will not be restored when the stream is restored to the single stream.
   * @endif
   * @if Chinese
   * 单路视频透传开关，默认为关闭状态。
   * - 开启后，如果房间中只有一路视频流输入， 则不对输入视频流进行转码，不遵循转码布局，直接推流 CDN。
   * - 如果有多个房间成员视频流混合为一路流，则该设置失效，并在恢复为一个成员画面（单路流）时也不会恢复。
   * @endif
   */
  bool single_video_passthrough;
  /**
   * @if English
   * The bitrate of the audio stream.
   * - Unit: kbps. Valid values: 10 to 192.
   * - We recommend that you set the bitrate to 64 or higher for voice scenarios and set 128 or higher for music scenarios.
   * @endif
   * @if Chinese
   * 音频推流码率。
   * - 单位为 kbps，取值范围为 10~192。
   * - 语音场景建议设置为 64 及以上码率，音乐场景建议设置为 128 及以上码率。
   * @endif
   */
  int audio_bitrate;

  /**
   * @if English
   * The sample rate of the audio stream. Unit: Hz. The default value is kNERtcLiveStreamAudioSampleRate48000, which indicates
   * the sample rate of 48 kHz.
   * @endif
   * @if Chinese
   * 音频推流采样率。单位为Hz。默认为 kNERtcLiveStreamAudioSampleRate48000，即采样率为 48 kHz。
   * @endif
   */
  nertc_live_stream_audio_sample_rate sampleRate;

  /**
   * @if English
   * The number of audio channels for publishing streams. The default value is 2, which represents the stereo sound.
   * @endif
   * @if Chinese
   * 音频推流声道数，默认值为 2 双声道。
   * @endif
   */
  int channels;

  /**
   * @if English
   * The audio encoding profile. The default value is NERtcLiveStreamAudioCodecProfileLCAAC, which is the basic encoding
   * profile.
   * - 0: LC-AAC, the basic encoding profile.
   * - 1: HE-AAC, the high-efficiency audio encoding profile.
   * @endif
   * @if Chinese
   * 音频编码规格。默认值 NERtcLiveStreamAudioCodecProfileLCAAC，普通编码规格。
   * - 0: LC-AAC 规格，表示基本音频编码规格
   * - 1: HE-AAC 规格，表示高效音频编码规格。
   * @endif
   */
  nertc_live_stream_audio_sample_rate audioCodecProfile;
};

/**
 * @if English
 * Configuration of streaming tasks.
 * @endif
 * @if Chinese
 * 直播推流任务的配置项。
 * @endif
 */
struct nertc_live_stream_task_info {
  /**
   * @if English
   * The ID of a custom streaming task. The ID must be up to 64 characters in length and can contain letters, numbers, and
   * underscores. The ID must be unique.
   * @endif
   * @if Chinese
   * 自定义的推流任务 ID。字母、数字、下划线组成的 64 位以内的字符串。请保证此 ID 唯一。
   * @endif
   */
  char task_id[kNERtcMaxTaskIDLength];
  /**
   * @if English
   * The streaming URL, such as rtmp://test.url.
   * <br>The URL can be set to the value of the pushUrl response parameter of the server API used to create a room in NetEase
   * CommsEase live streaming.
   * @endif
   * @if Chinese
   * 推流地址，例如 rtmp://test.url。
   * <br>此处的推流地址可设置为网易云信直播产品中服务端 API创建房间的返回参数pushUrl。
   * @endif
   */
  char stream_url[kNERtcMaxURILength];
  /**
   * @if English
   * Specifies whether to enable audio and video recording in the CDN relayed streaming. By default, the setting is disabled.
   * @endif
   * @if Chinese
   * 旁路推流是否需要进行音视频录制。默认为关闭状态。
   * @endif
   */
  bool server_record_enabled;
  /**
   * @if English
   * The live streaming mode. For more information, see NERtcLiveStreamMode.
   * @endif
   * @if Chinese
   * 直播推流模式。详细信息请参考 NERtcLiveStreamMode。
   * @endif
   */
  nertc_live_stream_mode ls_mode;
  /**
   * @if English
   * Set the canvas layout of Interactive Live Streaming. For more information, see NERtcLiveStreamLayout.
   * @endif
   * @if Chinese
   * 设置互动直播的画面布局。详细信息请参考 NERtcLiveStreamLayout。
   * @endif
   */
  nertc_live_stream_layout layout;
  /**
   * @if English
   * Settings such as encoding parameters of the audio and video streams. For more information, see NERtcLiveConfig.
   * @endif
   * @if Chinese
   * 音视频流编码参数等设置。详细信息请参考 NERtcLiveConfig。
   * @endif
   */
  nertc_live_stream_config config;
  /**
   * @if English
   * SEI message
   * @endif
   * @if Chinese
   * SEI信息
   * @endif
   */
  char extra_info[kNERtcMaxSEIBufferLength];
};

/**
 * @if English
 * Live streaming status code.
 * @endif
 * @if Chinese
 * 直播推流状态。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * Publishing.
   * @endif
   * @if Chinese
   * 推流中
   * @endif
   */
  kNERtcLsStatePushing = 505,
  /**
   * @if English
   * Publishing fails.
   * @endif
   * @if Chinese
   * 互动直播推流失败
   * @endif
   */
  kNERtcLsStatePushFail = 506,
  /**
   * @if English
   * Publishing ends.
   * @endif
   * @if Chinese
   * 推流结束
   * @endif
   */
  kNERtcLsStatePushStopped = 511,
  /**
   * @if English
   * Background image setting error.
   * @endif
   * @if Chinese
   * 背景图片设置出错
   * @endif
   */
  kNERtcLsStateImageError = 512,
} nertc_live_stream_state_code;

/**
 * @if English
 * System ategory.
 * @endif
 * @if Chinese
 * 系统分类。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * iOS universal device.
   * @endif
   * @if Chinese
   * iOS 通用设备
   * @endif
   */
  kNERtcOSiOS = 1,
  /**
   * @if English
   * Android universal device.
   * @endif
   * @if Chinese
   * Android 通用设备
   * @endif
   */
  kNERtcOSAndroid = 2,
  /**
   * @if English
   * PC设备
   * @endif
   * @if Chinese
   * PC device.
   * @endif
   */
  kNERtcOSPC = 3,
  /**
   * @if English
   * WebRTC.
   * @endif
   * @if Chinese
   * WebRTC
   * @endif
   */
  kNERtcOSWebRTC = 4,
} nertc_os_category;

/**
 * @if English
 * Audio profile. Audio sample rate, bitrate, encoding mode, and the number of channels.
 * @endif
 * @if Chinese
 * 音频属性。设置采样率，码率，编码模式和声道数。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * Default settings. kNERtcAudioProfileStandard in the speech scenarios. kNERtcAudioProfileHighQuality in the music scenarios.
   * @endif
   * @if Chinese
   * 0: 默认设置。Speech 场景下为 kNERtcAudioProfileStandardExtend，Music 场景下为 kNERtcAudioProfileHighQuality。
   * @endif
   */
  kNERtcAudioProfileDefault = 0,
  /**
   * @if English
   * 1: Standard-quality audio encoding, 16000Hz, 20kbps.
   * @endif
   * @if Chinese
   * 1: 普通质量的音频编码，16000Hz，20Kbps
   * @endif
   */
  kNERtcAudioProfileStandard = 1,
  /**
   * @if English
   * 2: Standard-quality audio encoding, 16000Hz, 32kbps.
   * @endif
   * @if Chinese
   * 2: 普通质量的音频编码，16000Hz，32Kbps
   * @endif
   */
  kNERtcAudioProfileStandardExtend = 2,
  /**
   * @if English
   * 3: Medium-quality audio encoding, 48000Hz, 32kbps.
   * @endif
   * @if Chinese
   * 3: 中等质量的音频编码，48000Hz，32Kbps
   * @endif
   */
  kNERtcAudioProfileMiddleQuality = 3,
  /**
   * @if English
   * 4: Medium-quality stereo encoding, 48000Hz * 2, 64kbps.
   * @endif
   * @if Chinese
   * 4: 中等质量的立体声编码，48000Hz * 2，64Kbps
   * @endif
   */
  kNERtcAudioProfileMiddleQualityStereo = 4,
  /**
   * @if English
   * 5: High-quality audio encoding, 48000Hz, 64kbps.
   * @endif
   * @if Chinese
   * 5: 高质量的音频编码，48000Hz，64Kbps
   * @endif
   */
  kNERtcAudioProfileHighQuality = 5,
  /**
   * @if English
   * 6: High-quality stereo encoding, 48000Hz * 2, 128kbps.
   * @endif
   * @if Chinese
   * 6: 高质量的立体声编码，48000Hz * 2，128Kbps
   * @endif
   */
  kNERtcAudioProfileHighQualityStereo = 6,
} nertc_audio_profile_type;


/**
 * @if English
 * Audio application scenarios. Different audio scenarios use different audio capture modes and playback modes.
 * @endif
 * @if Chinese
 *  音频应用场景。不同的场景设置对应不同的音频采集模式、播放模式。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * 0: Default settings.
   * - kNERtcAudioScenarioSpeech in kNERtcChannelProfileCommunication.
   * - kNERtcAudioScenarioMusic in kNERtcChannelProfileLiveBroadcasting.
   * @endif
   * @if Chinese
   * 0: 默认设置
   * - kNERtcChannelProfileCommunication下为kNERtcAudioScenarioSpeech，
   * - kNERtcChannelProfileLiveBroadcasting下为kNERtcAudioScenarioMusic。
   * @endif
   */
  kNERtcAudioScenarioDefault = 0,
  /**
   * @if English
   * 1: Voice scenarios. Set NERtcAudioProfileType to kNERtcAudioProfileMiddleQuality or lower.
   * @endif
   * @if Chinese
   * 1: 语音场景. NERtcAudioProfileType 推荐使用 kNERtcAudioProfileMiddleQuality 及以下
   * @endif
   */
  kNERtcAudioScenarioSpeech = 1,
  /**
   * @if English
   * 2: Music scenarios. Set NERtcAudioProfileType to kNERtcAudioProfileMiddleQualityStereo or above.
   * @endif
   * @if Chinese
   * 2: 音乐场景。NERtcAudioProfileType 推荐使用 kNERtcAudioProfileMiddleQualityStereo 及以上
   * @endif
   */
  kNERtcAudioScenarioMusic = 2,
  /**
 * @if English
 * 3: Chatroom scenario. Set NERtcAudioProfileType to kNERtcAudioProfileHighQuality or above.
 * @endif
 * @if Chinese
 * 3: 语聊房场景 (只适用于移动端）。NERtcAudioProfileType 推荐使用 kNERtcAudioProfileHighQuality 及以上
 * @endif
 */
  kNERtcAudioScenarioChatroom = 3,
} nertc_audio_scenario_type;

/**
 * @if English
 * The preset value of the voice changer.
 * @endif
 * @if Chinese
 * 变声 预设值
 * @endif
 */
typedef enum {
  /**
   * @if English
   * By default, the setting is disabled.
   * @endif
   * @if Chinese
   * 默认关闭
   * @endif
   */
  kNERtcVoiceChangerOff = 0,
  /**
   * @if English
   * A robot voice.
   * @endif
   * @if Chinese
   * 机器人
   * @endif
   */
  kNERtcVoiceChangerRobot = 1,
  /**
   * @if English
   * A giant voice.
   * @endif
   * @if Chinese
   * 巨人
   * @endif
   */
  kNERtcVoiceChangerGaint = 2,
  /**
   * @if English
   * A horror voice.
   * @endif
   * @if Chinese
   * 恐怖
   * @endif
   */
  kNERtcVoiceChangerHorror = 3,
  /**
   * @if English
   * A maturity voice.
   * @endif
   * @if Chinese
   * 成熟
   * @endif
   */
  kNERtcVoiceChangerMature = 4,
  /**
   * @if English
   * From a male voice to a female voice.
   * @endif
   * @if Chinese
   * 男变女
   * @endif
   */
  kNERtcVoiceChangerManToWoman = 5,
  /**
   * @if English
   * From a female voice to a male voice.
   * @endif
   * @if Chinese
   * 女变男
   * @endif
   */
  kNERtcVoiceChangerWomanToMan = 6,
  /**
   * @if English
   * From a male voice to a loli voice.
   * @endif
   * @if Chinese
   * 男变萝莉
   * @endif
   */
  kNERtcVoiceChangerManToLoli = 7,
  /**
   * @if English
   * From a female voice to a loli voice.
   * @endif
   * @if Chinese
   * 女变萝莉
   * @endif
   */
  kNERtcVoiceChangerWomanToLoli = 8,
} nertc_voice_changer_type;

/**
 * @if English
 * Preset voice beautifier effect.
 * @endif
 * @if Chinese
 * 预设的美声效果
 * @endif
 */
typedef enum {
  /**
   * @if English
   * By default, the setting is disabled.
   * @endif
   * @if Chinese
   * 默认关闭
   * @endif
   */
  kNERtcVoiceBeautifierOff = 0,
  /**
   * @if English
   * A muffled effect.
   * @endif
   * @if Chinese
   * 低沉
   * @endif
   */
  kNERtcVoiceBeautifierMuffled = 1,
  /**
   * @if English
   * A mellow effect.
   * @endif
   * @if Chinese
   * 圆润
   * @endif
   */
  kNERtcVoiceBeautifierMellow = 2,
  /**
   * @if English
   * A clear effect.
   * @endif
   * @if Chinese
   * 清澈
   * @endif
   */
  kNERtcVoiceBeautifierClear = 3,
  /**
   * @if English
   * A magnetic effect.
   * @endif
   * @if Chinese
   * 磁性
   * @endif
   */
  kNERtcVoiceBeautifierMagnetic = 4,
  /**
   * @if English
   * A recording studio effect.
   * @endif
   * @if Chinese
   * 录音棚
   * @endif
   */
  kNERtcVoiceBeautifierRecordingstudio = 5,
  /**
   * @if English
   * A nature effect.
   * @endif
   * @if Chinese
   * 天籁
   * @endif
   */
  kNERtcVoiceBeautifierNature = 6,
  /**
   * @if English
   * A KTV effect.
   * @endif
   * @if Chinese
   * KTV
   * @endif
   */
  kNERtcVoiceBeautifierKTV = 7,
  /**
   * @if English
   * A remote effect.
   * @endif
   * @if Chinese
   * 悠远
   * @endif
   */
  kNERtcVoiceBeautifierRemote = 8,
  /**
   * @if English
   * A church effect.
   * @endif
   * @if Chinese
   * 教堂
   * @endif
   */
  kNERtcVoiceBeautifierChurch = 9,
  /**
   * @if English
   * A bedroom effect.
   * @endif
   * @if Chinese
   * 卧室
   * @endif
   */
  kNERtcVoiceBeautifierBedroom = 10,
  /**
   * @if English
   * A live effect.
   * @endif
   * @if Chinese
   * Live
   * @endif
   */
  kNERtcVoiceBeautifierLive = 11,
} nertc_voice_beautifier_type;

/**
 * @if English
 * The center frequency of the sound equalization band.
 * @endif
 * @if Chinese
 * 音效均衡波段的中心频率
 * @endif
 */
typedef enum {
  /**
   * @if English
   * 31 Hz
   * @endif
   * @if Chinese
   * 31 Hz
   * @endif
   */
  kNERtcVoiceEqualizationBand_31 = 0,
  /**
   * @if English
   * 62 Hz.
   * @endif
   * @if Chinese
   * 62 Hz
   * @endif
   */
  kNERtcVoiceEqualizationBand_62 = 1,
  /**
   * @if English
   * 125 Hz.
   * @endif
   * @if Chinese
   * 125 Hz
   * @endif
   */
  kNERtcVoiceEqualizationBand_125 = 2,
  /**
   * @if English
   * 250 Hz.
   * @endif
   * @if Chinese
   * 250 Hz
   * @endif
   */
  kNERtcVoiceEqualizationBand_250 = 3,
  /**
   * @if English
   * 500 Hz.
   * @endif
   * @if Chinese
   * 500 Hz
   * @endif
   */
  kNERtcVoiceEqualizationBand_500 = 4,
  /**
   * @if English
   * 1 kHz.
   * @endif
   * @if Chinese
   * 1 kHz
   * @endif
   */
  kNERtcVoiceEqualizationBand_1K = 5,
  /**
   * @if English
   * 2 kHz.
   * @endif
   * @if Chinese
   * 2 kHz
   * @endif
   */
  kNERtcVoiceEqualizationBand_2K = 6,
  /**
   * @if English
   * 4 kHz.
   * @endif
   * @if Chinese
   * 4 kHz
   * @endif
   */
  kNERtcVoiceEqualizationBand_4K = 7,
  /**
   * @if English
   * 8 kHz.
   * @endif
   * @if Chinese
   * 8 kHz
   * @endif
   */
  kNERtcVoiceEqualizationBand_8K = 8,
  /**
   * @if English
   * 16 kHz.
   * @endif
   * @if Chinese
   * 16 kHz
   * @endif
   */
  kNERtcVoiceEqualizationBand_16K = 9,
} nertc_voice_equalization_band;

/**
 * @if English
 * The camera capturer configuration.
 * @endif
 * @if Chinese
 * 摄像头采集配置。
 * @endif
 */
struct nertc_camera_capture_config {
  /**
   * @if English
   * The width (px) of the video image captured by the local camera.
   * <br>The video encoding resolution is expressed in width x height. It is used to set the video encoding resolution and
   * measure the encoding quality.
   * - capture_width: the pixels of the video frame on the horizontal axis, that is, the custom width.
   * - capture_height： the pixels of the video frame on the horizontal axis, that is, the custom height.
   * @note
   * - To customize the width of the video image, set preference as kNERtcCameraOutputManual first, and then use captureWidth
   * and captureHeight.
   * - In manual mode, if the specified collection size is smaller than the encoding size, the encoding parameters will be
   * aligned down to the collection size range.
   * @endif
   * @if Chinese
   * 本地采集的视频宽度，单位为 px。
   * <br>视频编码分辨率以宽 x 高表示，用于设置视频编码分辨率，以衡量编码质量。
   * - captureWidth 表示视频帧在横轴上的像素，即自定义宽。
   * - captureHeight 表示视频帧在横轴上的像素，即自定义高。
   * @note
   * - 如果您需要自定义本地采集的视频尺寸，请先将 preference 设为 kNERtcCameraOutputManual，再通过 captureWidth 和 captureHeight
   * 设置采集的视频宽度。
   * - 手动模式下，如果指定的采集宽高小于编码宽高，编码参数会被下调对齐到采集的尺寸范围内。
   * @endif
   */
  int capture_width;
  /**
   * @if English
   * The height (px) of the video image captured by the local camera.
   * <br>The video encoding resolution is expressed in width x height. It is used to set the video encoding resolution and
   * measure the encoding quality.
   * - capture_width: the pixels of the video frame on the horizontal axis, that is, the custom width.
   * - capture_height： the pixels of the video frame on the horizontal axis, that is, the custom height.
   * @note
   * - To customize the width of the video image, set preference as CAPTURE_PREFERENCE_MANUAL first, and then use captureWidth
   * and captureHeight.
   * - In manual mode, if the specified collection size is smaller than the encoding size, the encoding parameters will be
   * aligned down to the collection size range.
   * @endif
   * @if Chinese
   * 本地采集的视频高度，单位为 px。
   * <br>视频编码分辨率以宽 x 高表示，用于设置视频编码分辨率，以衡量编码质量。
   * - captureWidth 表示视频帧在横轴上的像素，即自定义宽。
   * - captureHeight 表示视频帧在横轴上的像素，即自定义高。
   * @note
   * - 如果您需要自定义本地采集的视频尺寸，请先将 preference 设为 kNERtcCameraOutputManual，再通过 captureWidth 和 captureHeight
   * 设置采集的视频宽度。
   * - 手动模式下，如果指定的采集宽高小于编码宽高，编码参数会被下调对齐到采集的尺寸范围内。
   * @endif
   */
  int capture_height;
};

/**
 * @if English
 * Video encoding configuration. The resolution used to measure encoding quality.
 * @note kNERtcVideoProfileFake:
 * - The peer sends a 16*16 fakeVideo (SEI delivered in audio-only streams), which is an internal behavior of the SDK. The view
 * is not displayed at this time (the client receives only black frames).
 * - Therefore, this setting is not actively applied. If you select the setting, the SDK applies the setting to the standard.
 * @endif
 * @if Chinese
 * 视频编码配置。用于衡量编码质量。
 * @note
 * kNERtcVideoProfileFake:
 * - 表示对端发送 16*16 的 fakeVideo，即纯音频下发送 SEI，属于 SDK 内部行为，此时收到的是黑色帧，不需要显示 view。
 * - 因此这个档位不主动使用，属于被动接受，如果主动使用，SDK 内部会按 standard 处理。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * LD160x90/120, 15fps
   * @endif
   * @if Chinese
   * 普清（160x90/120, 15fps）
   * @endif
   */
  kNERtcVideoProfileLowest = 0,
  /**
   * @if English
   * LD 320x180/240, 15fps
   * @endif
   * @if Chinese
   * 标清（320x180/240, 15fps）
   * @endif
   */
  kNERtcVideoProfileLow = 1,
  /**
   * @if English
   * SD 640x360/480, 30fps
   * @endif
   * @if Chinese
   * 高清（640x360/480, 30fps）
   * @endif
   */
  kNERtcVideoProfileStandard = 2,
  /**
   * @if English
   * HD (1280 x 720, 30 fps)
   * @endif
   * @if Chinese
   * 超清（1280x720, 30fps）
   * @endif
   */
  kNERtcVideoProfileHD720P = 3,
  /**
   * @if English
   * 1080p (1920x1080, 30fps)
   * @endif
   * @if Chinese
   * 1080P（1920x1080, 30fps）
   * @endif
   */
  kNERtcVideoProfileHD1080P = 4,
  /**
   * @if English
   * None
   * @endif
   * @if Chinese
   * 无效果。
   * @endif
   */
  kNERtcVideoProfileNone = 5,
  kNERtcVideoProfileMAX = kNERtcVideoProfileHD1080P,
  /**
   * @if English
   * FakeVideo logo, only displayed in the callback. Do not use the setting. Otherwise, the SDK applies the logo based on
   * kNERtcVideoProfileStandard. <br>When the remote client sends the SEI in the audio-only state, the local client receives the
   * message returned by the onUserVideoStart callback from the remote client. The maxProfile parameter is
   * kNERtcVideoProfileFake, which indicates that the remote client sends a 16*16 FakeVideo. At this time, if the local client
   * needs to receive the remote SEI, you only need to subscribe to the remote video, without setting the remote canvas.
   * @endif
   * @if Chinese
   * FakeVideo标识，仅在回调中显示。请勿主动设置，否则 SDK 会按照 STANDARD 处理。
   * <br>当远端在纯音频状态发送 SEI 时，本端将会收到远端的onUserVideoStart回调，其中 max_profile 参数为 kNERtcVideoProfileFake
   * ， 表示对端发送 16*16 的 FakeVideo，此时如果本端需要接收远端的SEI信息，只需要订阅一下远端的视频即可，无须设置远端画布。
   * @endif
   */
  kNERtcVideoProfileFake = 6,
} nertc_video_profile_type;

/**
 * @if English
 * The video stream type.
 * @endif
 * @if Chinese
 * 视频流类型。
 * @note 大流的分辨率及参数配置高，小流的分辨率及参数配置低。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * The default high-resolution stream.
   * @endif
   * @if Chinese
   *  默认大流
   * @endif
   */
  kNERtcRemoteVideoStreamTypeHigh = 0,
  /**
   * @if English
   * The low-resolution stream
   * @endif
   * @if Chinese
   * 小流
   * @endif
   */
  kNERtcRemoteVideoStreamTypeLow = 1,
  /**
   * @if English
   * Unsubscribed.
   * @endif
   * @if Chinese
   * 不订阅
   * @endif
   */
  kNERtcRemoteVideoStreamTypeNone = 2,
} nertc_remote_video_stream_type;

/**
 * @if English
 * Audio device type.
 * @endif
 * @if Chinese
 * 音频设备类型。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * Unknown audio device.
   * @endif
   * @if Chinese
   * 未知音频设备
   * @endif
   */
  kNERtcAudioDeviceUnknown = 0,
  /**
   * @if English
   * Audio capture device.
   * @endif
   * @if Chinese
   * 音频采集设备
   * @endif
   */
  kNERtcAudioDeviceRecord,
  /**
   * @if English
   * Audio playback device.
   * @endif
   * @if Chinese
   * 音频播放设备
   * @endif
   */
  kNERtcAudioDevicePlayout,
} nertc_audio_device_type;

/**
 * @if English
 * Audio device status types.
 * @endif
 * @if Chinese
 * 音频设备类型状态。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * The audio device is activated.
   * @endif
   * @if Chinese
   * 音频设备已激活
   * @endif
   */
  kNERtcAudioDeviceActive = 0,
  /**
   * @if English
   * The audio device is not activated.
   * @endif
   * @if Chinese
   * 音频设备未激活
   * @endif
   */
  kNERtcAudioDeviceUnactive,
} nertc_audio_device_state;

/**
 * @if English
 * Audio device types.
 *@endif
 *@if Chinese
 * 音频设备连接类型。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * Unknown device.
   * @endif
   * @if Chinese
   * 未知设备
   * @endif
   */
  kNERtcAudioDeviceTransportTypeUnknown = 0,
  /**
   * @if English
   * Bluetooth device.
   * @endif
   * @if Chinese
   * 蓝牙设备
   * @endif
   */
  kNERtcAudioDeviceTransportTypeBluetooth = 1,
  /**
   * @if English
   * Bluetooth stereo device.
   * @endif
   * @if Chinese
   * 蓝牙立体声设备
   * @endif
   */
  kNERtcAudioDeviceTransportTypeBluetoothA2DP = 2,
  /**
   * @if English
   * Bluetooth low energy device.
   * @endif
   * @if Chinese
   * 蓝牙低功耗设备
   * @endif
   */
  kNERtcAudioDeviceTransportTypeBluetoothLE = 3,
  /**
   * @if English
   * USB device.
   * @endif
   * @if Chinese
   * USB设备
   * @endif
   */
  kNERtcAudioDeviceTransportTypeUSB = 4,
  /**
   * @if English
   * HDMI device.
   * @endif
   * @if Chinese
   * HDMI设备
   * @endif
   */
  kNERtcAudioDeviceTransportTypeHDMI = 5,
  /**
   * @if English
   * Built-in device.
   * @endif
   * @if Chinese
   * 内置设备
   * @endif
   */
  kNERtcAudioDeviceTransportTypeBuiltIn = 6,
  /**
   * @if English
   * Thunderbolt interface device.
   * @endif
   * @if Chinese
   * 雷电接口设备
   * @endif
   */
  kNERtcAudioDeviceTransportTypeThunderbolt = 7,
  /**
   * @if English
   * AirPlay device.
   * @endif
   * @if Chinese
   * AirPlay设备
   * @endif
   */
  kNERtcAudioDeviceTransportTypeAirPlay = 8,
  /**
   * @if English
   * Virtual device.
   * @endif
   * @if Chinese
   * 虚拟设备
   * @endif
   */
  kNERtcAudioDeviceTransportTypeVirtual = 9,
  /**
   * @if English
   * Other devices.
   * @endif
   * @if Chinese
   * 其他设备
   * @endif
   */
  kNERtcAudioDeviceTransportTypeOther = 10,
} nertc_audio_device_transport_type;

/**
 * @if English
 * Camera device type.
 * @endif
 * @if Chinese
 * 摄像头设备链接类型。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * Unknown device.
   * @endif
   * @if Chinese
   * 未知设备
   * @endif
   */
  kNERtcVideoDeviceTransportTypeUnknown = 0,
  /**
   * @if English
   * USB设备
   * @endif
   * @if Chinese
   * USB device.
   * @endif
   */
  kNERtcVideoDeviceTransportTypeUSB = 1,
  /**
   * @if English
   * Virtual device.
   * @endif
   * @if Chinese
   * 虚拟设备
   * @endif
   */
  kNERtcVideoDeviceTransportTypeVirtual = 2,
  /**
   * @if English
   * Other device.
   * @endif
   * @if Chinese
   * 其他设备
   * @endif
   */
  kNERtcVideoDeviceTransportTypeOther = 3,
} nertc_video_device_transport_type;

/**
 * @if English
 * Device details.
 * @endif
 * @if Chinese
 * 设备详细信息。
 * @endif
 */
struct nertc_device_info {
  /**
   * @if English
   * Device ID
   * @endif
   * @if Chinese
   * 设备ID
   * @endif
   */
  char device_id[kNERtcMaxDeviceIDLength];
  /**
   * @if English
   * Device name
   * @endif
   * @if Chinese
   * 设备名称
   * @endif
   */
  char device_name[kNERtcMaxDeviceNameLength];
  /**
   * @if English
   * Device types, including NERtcAudioDeviceTransportType and NERtcVideoDeviceTransportType
   * @endif
   * @if Chinese
   * 设备链接类型，分别指向NERtcAudioDeviceTransportType及NERtcVideoDeviceTransportType
   * @endif
   */
  int transport_type;
  /**
   * @if English
   * Determines whether it is a non-recommended device
   * @endif
   * @if Chinese
   * 是否是不推荐设备
   * @endif
   */
  bool suspected_unavailable;
  /**
   * @if English
   * Determines whether it is the system default device
   * @endif
   * @if Chinese
   * 是否是系统默认设备
   * @endif
   */
  bool system_default_device;
};

/**
 * @if English
 * Video device types.
 * @endif
 * @if Chinese
 * 视频设备类型。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * Unknown video device.
   * @endif
   * @if Chinese
   * Video capture device.
   * @endif
   */
  kNERtcVideoDeviceUnknown = 0,
  /**
   * @if English
   * Video capture device.
   * @endif
   * @if Chinese
   * 视频采集设备
   * @endif
   */
  kNERtcVideoDeviceCapture,
} nertc_video_device_type;

/**
 * @if English
 * Video device status types.
 * @endif
 * @if Chinese
 * 视频设备类型状态。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * The video device is added.
   * @endif
   * @if Chinese
   * 视频设备已添加
   * @endif
   */
  kNERtcVideoDeviceAdded = 0,
  /**
   * @if English
   * The video device is removed.
   * @endif
   * @if Chinese
   * 视频设备已拔除
   * @endif
   */
  kNERtcVideoDeviceRemoved,
} nertc_video_device_state;

/**
 * @if English
 * @enum NERtcVideoScalingMode Set the video scaling mode.
 * @endif
 * @if Chinese
 * @enum NERtcVideoScalingMode 设置视频缩放模式。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * 0: adaptive to the video. The video size is scaled proportionally. All video content is prioritized for display. If the
   * video size does not match the display window size, the unfilled area of the window is be filled with the background color.
   * @endif
   * @if Chinese
   * 0：适应视频，视频尺寸等比缩放。优先保证视频内容全部显示。若视频尺寸与显示视窗尺寸不一致，视窗未被填满的区域填充背景色。
   * @endif
   */
  kNERtcVideoScaleFit = 0,
  /**
   * @if English
   * 1: The video size is scaled non-proportionally. Ensure that all video content is displayed and the window is filled.
   * @endif
   * @if Chinese
   * 1：视频尺寸非等比缩放。保证视频内容全部显示，且填满视窗。
   * @endif
   */
  kNERtcVideoScaleFullFill = 1,
  /**
   * @if English
   * 2: adaptive to the area. The video size is scaled proportionally. Ensure that all areas are filled, and the extra part of
   * the video will be cropped.
   * @endif
   * @if Chinese
   * 2：适应区域，视频尺寸等比缩放。保证所有区域被填满，视频超出部分会被裁剪。
   * @endif
   */
  kNERtcVideoScaleCropFill = 2,
} nertc_video_scaling_mode;

/**
 * @if English
 * @enum NERtcVideoMirrorMode Video mirror mode.
 * @endif
 * @if Chinese
 * @enum NERtcVideoMirrorMode 视频镜像模式。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * 0: The mirror mode is enabled in Windows and macOS SDKs.
   * @endif
   * @if Chinese
   * 0: Windows/macOS SDK 启用镜像模式。
   * @endif
   */
  kNERtcVideoMirrorModeAuto = 0,
  /**
   * @if English
   * 1: Enables mirror mode.
   * @endif
   * @if Chinese
   * 1: 启用镜像模式。
   * @endif
   */
  kNERtcVideoMirrorModeEnabled = 1,
  /**
   * @if English
   * 2: Disables mirroring mode (default).
   * @endif
   * @if Chinese
   * 2: （默认）关闭镜像模式。
   * @endif
   */
  kNERtcVideoMirrorModeDisabled = 2,
} nertc_video_mirror_mode;

/**
 *  @if English
 * @enum NERtcVideoOutputOrientationMode The video orientation mode.
 * @endif
 * @if Chinese
 * @enum NERtcVideoOutputOrientationMode 视频旋转的方向模式。
 * @endif
 */
typedef enum {

  /**
   * @if English
   * (default) The direction of the video output by the SDK in this mode is consistent with the direction of the captured video.
   * The receiver rotates the video based on the received video rotation information. <br>This mode is suitable for scenarios
   * where the receiver can adjust the video direction.
   * - If the captured video is in landscape mode, the output video is also in landscape mode.
   * - If the captured video is in portrait mode, the output video is also in portrait mode.
   * @endif
   * @if Chinese
   * （默认）该模式下 SDK 输出的视频方向与采集到的视频方向一致。接收端会根据收到的视频旋转信息对视频进行旋转。
   * <br>该模式适用于接收端可以调整视频方向的场景。
   * - 如果采集的视频是横屏模式，则输出的视频也是横屏模式。
   * - 如果采集的视频是竖屏模式，则输出的视频也是竖屏模式。
   * @endif
   */
  kNERtcVideoOutputOrientationModeAdaptative = 0,

  /**
   * @if English
   * In this mode, the SDK always outputs videos in landscape mode. If the captured video is in portrait mode, the video encoder
   * crops the video. <br>This mode is suitable for scenes where the receiver cannot adjust the video direction, such as CDN
   * relayed streaming.
   * @endif
   * @if Chinese
   * 该模式下 SDK 固定输出横屏模式的视频。如果采集到的视频是竖屏模式，则视频编码器会对其进行裁剪。
   * <br>该模式适用于接收端无法调整视频方向的场景，例如旁路推流。
   * @endif
   */
  kNERtcVideoOutputOrientationModeFixedLandscape = 1,

  /**
   * @if English
   * In this mode, the SDK always outputs videos in portrait mode. If the captured video is in landscape mode, the video encoder
   * crops the video. <br>This mode is suitable for scenes where the receiver cannot adjust the video direction, such as CDN
   * relayed streaming.
   * @endif
   * @if Chinese
   * 该模式下 SDK 固定输出竖屏模式的视频，如果采集到的视频是横屏模式，则视频编码器会对其进行裁剪。
   * <br>该模式适用于接收端无法调整视频方向的场景，例如旁路推流。
   * @endif
   */
  kNERtcVideoOutputOrientationModeFixedPortrait = 2,

} nertc_video_orientation_mode;
/**
 * @if English
 * The state of network connection
 * @endif
 * @if Chinese
 * 连接状态
 * @endif
 */
typedef enum {
  /**
   * @if English
   * The client is disconnected.
   * @endif
   * @if Chinese
   * 未加入房间。
   * @endif
   */
  kNERtcConnectionStateDisconnected = 1,
  /**
   * @if English
   * The client is connecting to the room server.
   * @endif
   * @if Chinese
   * 正在加入房间。
   * @endif
   */
  kNERtcConnectionStateConnecting = 2,
  /**
   * @if English
   * The client is connected to the room server.
   * @endif
   * @if Chinese
   * 加入房间成功。
   * @endif
   */
  kNERtcConnectionStateConnected = 3,
  /**
   * @if English
   * The client is reconnecting to the room server.
   * @endif
   * @if Chinese
   * 正在尝试重新加入房间。
   * @endif
   */
  kNERtcConnectionStateReconnecting = 4,
  /**
   * @if English
   * The client fails to connect to the room server.
   * @endif
   * @if Chinese
   * 加入房间失败。
   * @endif
   */
  kNERtcConnectionStateFailed = 5,
} nertc_connection_state_type;

/**
 * @if English
 * The reason for the connection state change.
 * @endif
 * @if Chinese
 * 连接状态变更原因
 * @endif
 */
typedef enum {
  /**
   * @if English
   * kNERtcConnectionStateDisconnected The client leaves the room.
   * @endif
   * @if Chinese
   * kNERtcConnectionStateDisconnected 离开房间
   * @endif
   */
  kNERtcReasonConnectionChangedLeaveChannel = 1,
  /**
   * @if English
   * kNERtcConnectionStateDisconnected The room is closed.
   * @endif
   * @if Chinese
   * kNERtcConnectionStateDisconnected 房间被关闭
   * @endif
   */
  kNERtcReasonConnectionChangedChannelClosed = 2,
  /**
   * @if English
   * kNERtcConnectionStateDisconnected The user is removed from the room.
   * @endif
   * @if Chinese
   * kNERtcConnectionStateDisconnected 用户被踢
   * @endif
   */
  kNERtcReasonConnectionChangedBeKicked = 3,
  /**
   * @if English
   * kNERtcConnectionStateDisconnected The service times out.
   * @endif
   * @if Chinese
   * kNERtcConnectionStateDisconnected	服务超时
   * @endif
   */
  kNERtcReasonConnectionChangedTimeOut = 4,
  /**
   * @if English
   * kNERtcConnectionStateConnecting The user joins the room.
   * @endif
   * @if Chinese
   * kNERtcConnectionStateConnected 加入房间
   * @endif
   */
  kNERtcReasonConnectionChangedJoinChannel = 5,
  /**
   * @if English
   * kNERtcConnectionStateConnected The user has joined the room.
   * @endif
   * @if Chinese
   * kNERtcConnectionStateConnected 加入房间成功
   * @endif
   */
  kNERtcReasonConnectionChangedJoinSucceed = 6,
  /**
   * @if English
   * kNERtcConnectionStateConnected The user rejoins the room successfully (reconnection).
   * @endif
   * @if Chinese
   * kNERtcConnectionStateConnected 重新加入房间成功（重连）
   * @endif
   */
  kNERtcReasonConnectionChangedReJoinSucceed = 7,
  /**
   * @if English
   * kNERtcConnectionStateReconnecting The media stream gets disconnected.
   * @endif
   * @if Chinese
   *  kNERtcConnectionStateReconnecting 媒体连接断开
   * @endif
   */
  kNERtcReasonConnectionChangedMediaConnectionDisconnected = 8,
  /**
   * @if English
   * kNERtcConnectionStateReconnecting The signaling channel gets disconnected.
   * @endif
   * @if Chinese
   *  kNERtcConnectionStateReconnecting 信令连接断开
   * @endif
   */
  kNERtcReasonConnectionChangedSignalDisconnected = 9,
  /**
   * @if English
   * kNERtcConnectionStateFailed The request to join the room fails.
   * @endif
   * @if Chinese
   * kNERtcConnectionStateFailed 请求房间失败
   * @endif
   */
  kNERtcReasonConnectionChangedRequestChannelFailed = 10,
  /**
   * @if English
   * kNERtcConnectionStateFailed The user fails to join the room.
   * @endif
   * @if Chinese
   * kNERtcConnectionStateFailed 加入房间失败
   * @endif
   */
  kNERtcReasonConnectionChangedJoinChannelFailed = 11,
  /**
   * @if English
   * kNERtcConnectionStateReconnecting The server IP is reallocated.
   * @endif
   * @if Chinese
   * kNERtcConnectionStateReconnecting 重新分配了服务端IP
   * @endif
   */
  kNERtcReasonConnectionChangedReDispatch = 12,
  /**
   * @if English
   * Start connecting to server using the cloud proxy.
   * @endif
   * @if Chinese
   * 开始使用云代理进行连接。
   * @endif
   */
  kNERtcReasonConnectionChangedSettingProxyServer = 13
} nertc_reason_connection_changed_type;

/**
 * @if English
 * Audio volume information. An array that contains the user ID and volume information of each speaker.
 * @endif
 * @if Chinese
 * 声音音量信息。一个数组，包含每个说话者的用户 ID 和音量信息。
 * @endif
 */
struct nertc_audio_volume_info {
  /**
   * @if English
   * The user ID of the speaker. If the returned uid is 0, the user refers to the local user by default.
   * @endif
   * @if Chinese
   * 说话者的用户 ID。如果返回的 uid 为 0，则默认为本地用户。
   * @endif
   */
  nertc_uid_t uid;
  /**
   * @if English
   * The speaker's volume, the value range is from 0 (lowest) to 100 (highest).
   * @endif
   * @if Chinese
   * 说话者的音量，范围为 0（最低）- 100（最高）。
   * @endif
   */
  unsigned int volume;
  /**
   * @if Chinese
   * 远端用户音频辅流的音量，取值范围为 [0,100] 。
   * <br>如果 sub_stream_volume 为 0，表示该用户未发布音频辅流或音频辅流没有音量。
   * @endif
   */
  unsigned int sub_stream_volume;
};

/**
 * @if English
 * Stats related to calls.
 * @endif
 * @if Chinese
 * 通话相关的统计信息。
 * @endif
 */
struct nertc_stats {
  /**
   * @if English
   * The CPU usage occupied by the app (%).
   * @endif
   * @if Chinese
   * 当前 App 的 CPU 使用率 (%)。
   * @endif
   */
  uint32_t cpu_app_usage;
  /**
   * @if English
   * The CPU idle rate of the current system (%).
   * @endif
   * @if Chinese
   * 当前系统的 CPU 空闲率 (%)。
   * @endif
   */
  uint32_t cpu_idle_usage;
  /**
   * @if English
   * The current system CPU usage (%).
   * @endif
   * @if Chinese
   * 当前系统的 CPU 使用率 (%)。
   * @endif
   */
  uint32_t cpu_total_usage;
  /**
   * @if English
   * The current memory usage occupied by the app (%).
   * @endif
   * @if Chinese
   * 当前App的内存使用率 (%)。
   * @endif
   */
  uint32_t memory_app_usage;
  /**
   * @if English
   * The current system memory usage (%).
   * @endif
   * @if Chinese
   * 当前系统的内存使用率 (%)。
   * @endif
   */
  uint32_t memory_total_usage;
  /**
   * @if English
   * The current memory used by the app (KB).
   * @endif
   * @if Chinese
   * 当前App的内存使用量 (KB)。
   * @endif
   */
  uint32_t memory_app_kbytes;
  /**
   * @if English
   * Call duration in seconds.
   * @endif
   * @if Chinese
   * 通话时长（秒）。
   * @endif
   */
  int total_duration;
  /**
   * @if English
   * The number of bytes sent. This is the cumulative value. (bytes)
   * @endif
   * @if Chinese
   * 发送字节数，累计值。(bytes)
   * @endif
   */
  uint64_t tx_bytes;
  /**
   * @if English
   * The number of bytes received. This is the cumulative value. (bytes)
   * @endif
   * @if Chinese
   * 接收字节数，累计值。(bytes)
   * @endif
   */
  uint64_t rx_bytes;
  /**
   * @if English
   * The number of audio bytes sent. This is the cumulative value. (bytes)
   * @endif
   * @if Chinese
   * 音频发送字节数，累计值。(bytes)
   * @endif
   */
  uint64_t tx_audio_bytes;
  /**
   * @if English
   * The number of video bytes sent. This is the cumulative value. (bytes)
   * @endif
   * @if Chinese
   * 视频发送字节数，累计值。(bytes)
   * @endif
   */
  uint64_t tx_video_bytes;
  /**
   * @if English
   * The number of audio bytes received. This is the cumulative value. (bytes)
   * @endif
   * @if Chinese
   * 音频接收字节数，累计值。(bytes)
   * @endif
   */
  uint64_t rx_audio_bytes;
  /**
   * @if English
   * The number of video bytes received. This is the cumulative value. (bytes)
   * @endif
   * @if Chinese
   * 视频接收字节数，累计值。(bytes)
   * @endif
   */
  uint64_t rx_video_bytes;
  /**
   * @if English
   * Audio bitrate for publishing. (kbps)
   * @endif
   * @if Chinese
   * 音频发送码率。(kbps)
   * @endif
   */
  int tx_audio_kbitrate;
  /**
   * @if English
   * Audio bitrate for subscribed streams. (kbps)
   * @endif
   * @if Chinese
   * 音频接收码率。(kbps)
   * @endif
   */
  int rx_audio_kbitrate;
  /**
   * @if English
   * Video bitrate for publishing. (kbps)
   * @endif
   * @if Chinese
   * 视频发送码率。(kbps)
   * @endif
   */
  int tx_video_kbitrate;
  /**
   * @if English
   * Video bitrate for subscribed streams. (kbps)
   * @endif
   * @if Chinese
   * 视频接收码率。(kbps)
   * @endif
   */
  int rx_video_kbitrate;
  /**
   * @if English
   * Average uplink round trip time. (ms)
   * @endif
   * @if Chinese
   * 上行平均往返时延rtt(ms)
   * @endif
   */
  int up_rtt;
  /**
   * @if English
   * Average downlink round-trip time. (ms)
   * @endif
   * @if Chinese
   * 下行平均往返时延rtt(ms)
   * @endif
   */
  int down_rtt;
  /**
   * @if English
   * The actual uplink packet loss rate of the local audio stream. (%)
   * @endif
   * @if Chinese
   * 本地上行音频实际丢包率。(%)
   * @endif
   */
  int tx_audio_packet_loss_rate;
  /**
   * @if English
   * The actual uplink packet loss rate of the local video stream. (%)
   * @endif
   * @if Chinese
   * 本地上行视频实际丢包率。(%)
   * @endif
   */
  int tx_video_packet_loss_rate;
  /**
   * @if English
   * The actual number of lost packets for local upstream audio.
   * @endif
   * @if Chinese
   * 本地上行音频实际丢包数。
   * @endif
   */
  int tx_audio_packet_loss_sum;
  /**
   * @if English
   * Actual number of lost packets for local upstream video.
   * @endif
   * @if Chinese
   * 本地上行视频实际丢包数。
   * @endif
   */
  int tx_video_packet_loss_sum;
  /**
   * @if English
   * Local upstream audio jitter calculation. (ms)
   * @endif
   * @if Chinese
   * 本地上行音频抖动计算。(ms)
   * @endif
   */
  int tx_audio_jitter;
  /**
   * @if English
   * Local uplink video jitter calculation. (ms)
   * @endif
   * @if Chinese
   * 本地上行视频抖动计算。(ms)
   * @endif
   */
  int tx_video_jitter;
  /**
   * @if English
   * Actual packet loss of local downlink audio stream. (%)
   * @endif
   * @if Chinese
   * 本地下行音频实际丢包率。(%)
   * @endif
   */
  int rx_audio_packet_loss_rate;
  /**
   * @if English
   * Actual local downstream video packet loss rate. (%)
   * @endif
   * @if Chinese
   * 本地下行视频实际丢包率。(%)
   * @endif
   */
  int rx_video_packet_loss_rate;
  /**
   * @if English
   * Actual number of lost packets for local downstream audio.
   * @endif
   * @if Chinese
   * 本地下行音频实际丢包数。
   * @endif
   */
  int rx_audio_packet_loss_sum;
  /**
   * @if English
   * Actual number of lost packets for local downstream video.
   * @endif
   * @if Chinese
   * 本地下行视频实际丢包数。
   * @endif
   */
  int rx_video_packet_loss_sum;
  /**
   * @if English
   * Local downstream audio jitter calculation. (ms)
   * @endif
   * @if Chinese
   * 本地下行音频抖动计算。(ms)
   * @endif
   */
  int rx_audio_jitter;
  /**
   * @if English
   *  Local downstream video jitter calculation. (ms)
   * @endif
   * @if Chinese
   * 本地下行视频抖动计算。(ms)
   * @endif
   */
  int rx_video_jitter;
};

/**
 * @if English
 * Stats of each local video stream.
 * @endif
 * @if Chinese
 * 本地视频单条流上传统计信息。
 * @endif
 */
struct nertc_video_layer_send_stats {
  /**
   * @if English
   * Stream type: 1. mainstream. 2. substream.
   * @endif
   * @if Chinese
   * 流类型： 1、主流，2、辅流。
   * @endif
   */
  int layer_type;
  /**
   * @if English
   * Video stream width (pixels).
   * @endif
   * @if Chinese
   * 视频流宽（像素）。
   * @endif
   */
  int width;
  /**
   * @if English
   * Video stream height (pixels).
   * @endif
   * @if Chinese
   * 视频流高（像素）。
   * @endif
   */
  int height;
  /**
   * @if English
   * @endif
   * @if Chinese
   * 视频采集宽（像素）。
   * @endif
   */
  int capture_width;
  /**
   * @if English
   * @endif
   * @if Chinese
   * 视频采集高（像素）。
   * @endif
   */
  int capture_height;
  /**
   * @if English
   * Video capture frame rate.
   * @endif
   * @if Chinese
   * 视频采集帧率。
   * @endif
   */
  int capture_frame_rate;
  /**
   * @if English
   * Video rendering frame rate.
   * @endif
   * @if Chinese
   * 视频渲染帧率。
   * @endif
   */
  int render_frame_rate;
  /**
   * @if English
   * Encoding frame rate.
   * @endif
   * @if Chinese
   * 编码帧率。
   * @endif
   */
  int encoder_frame_rate;
  /**
   * @if English
   * Publishing frame rate.
   * @endif
   * @if Chinese
   * 发送帧率。
   * @endif
   */
  int sent_frame_rate;
  /**
   * @if English
   * Publishing bitrate(kbps).
   * @endif
   * @if Chinese
   * 发送码率(Kbps)。
   * @endif
   */
  int sent_bitrate;
  /**
   * @if English
   * Encoder expected bitrate (kbps).
   * @endif
   * @if Chinese
   * 编码器目标码率(Kbps)。
   * @endif
   */
  int target_bitrate;
  /**
   * @if English
   * Encoder actual bitrate (kbps).
   * @endif
   * @if Chinese
   * 编码器实际编码码率(Kbps)。
   * @endif
   */
  int encoder_bitrate;
  /**
   * @if English
   * The name of the video encoder.
   * @endif
   * @if Chinese
   * 视频编码器名字。
   * @endif
   */
  char codec_name[kNERtcMaxDeviceNameLength];
};

/**
 * @if English
 * The stats of the uplink local video stream.
 * @endif
 * @if Chinese
 * 本地视频流上传统计信息。
 * @endif
 */
struct nertc_video_send_stats {
  /**
   * @if English
   * Video stream information array.
   * @endif
   * @if Chinese
   * 视频流信息数组。
   * @endif
   */
  nertc_video_layer_send_stats* video_layers_list;
  /**
   * @if English
   * The number of video streams.
   * @endif
   * @if Chinese
   * 视频流条数。
   * @endif
   */
  int video_layers_count;
};

/**
 * @if English
 * The stats of each remote video stream.
 * @endif
 * @if Chinese
 * 远端视频单条流的统计信息。
 * @endif
 */
struct nertc_video_layer_recv_stats {
  /**
   * @if English
   * Stream type: 1. mainstream. 2. substream.
   * @endif
   * @if Chinese
   * 流类型： 1、主流，2、辅流。
   * @endif
   */
  int layer_type;
  /**
   * @if English
   * Video stream width (pixels).
   * @endif
   * @if Chinese
   * 视频流宽（像素）。
   * @endif
   */
  int width;
  /**
   * @if English
   * Video stream height (pixels).
   * @endif
   * @if Chinese
   * 视频流高（像素）。
   * @endif
   */
  int height;
  /**
   * @if English
   * The bitrate of the received stream (kbps).
   * @endif
   * @if Chinese
   * 接收到的码率(Kbps)。
   * @endif
   */
  int received_bitrate;
  /**
   * @if English
   * The frame rate of the received stream (fps).
   * @endif
   * @if Chinese
   * 接收到的帧率 (fps)。
   * @endif
   */
  int received_frame_rate;
  /**
   * @if English
   * Decoding frame rate (fps).
   * @endif
   * @if Chinese
   * 解码帧率 (fps)。
   * @endif
   */
  int decoder_frame_rate;
  /**
   * @if English
   * Rendering frame rate (fps).
   * @endif
   * @if Chinese
   * 渲染帧率 (fps)。
   * @endif
   */
  int render_frame_rate;
  /**
   * @if English
   * Downlink packet loss rate (%).
   * @endif
   * @if Chinese
   * 下行丢包率(%)。
   * @endif
   */
  int packet_loss_rate;
  /**
   * @if English
   * The downlink video freeze cumulative time (ms).
   * @endif
   * @if Chinese
   * 用户的下行视频卡顿累计时长(ms)。
   * @endif
   */
  int total_frozen_time;
  /**
   * @if English
   * The average freeze rate of the user's downlink video stream (%).
   * @endif
   * @if Chinese
   * 用户的下行视频平均卡顿率(%)。
   * @endif
   */
  int frozen_rate;
  /**
   * @if English
   * The codec name.
   * @endif
   * @if Chinese
   * 视频解码器名字。
   * @endif
   */
  char codec_name[kNERtcMaxDeviceNameLength];
};

/**
 * @if English
 * Remote video stream stats.
 * @endif
 * @if Chinese
 * 远端视频流的统计信息。
 * @endif
 */
struct nertc_video_recv_stats {
  /**
   * @if English
   * The user ID used to identify the video stream.
   * @endif
   * @if Chinese
   * 用户 ID，指定是哪个用户的视频流。
   * @endif
   */
  nertc_uid_t uid;
  /**
   * @if English
   * Video stream information array.
   * @endif
   * @if Chinese
   * 视频流信息数组。
   * @endif
   */
  nertc_video_layer_recv_stats* video_layers_list;
  /**
   * @if English
   * The number of video streams.
   * @endif
   * @if Chinese
   * 视频流条数。
   * @endif
   */
  int video_layers_count;
};

/**
 * @if English
 * Audio stream type.
 * @endif
 * @if Chinese
 * 音频流类型。
 * @endif
 */
enum nertc_audio_stream_type{
    /**
     * @if English
     * Main stream.
     * @endif
     * @if Chinese
     * 主流。
     * @endif
     */
    kNERtcAudioStreamTypeMain = 0,

    /**
     * @if English
     * Substream.
     * @endif
     * @if Chinese
     * 辅流。
     * @endif
     */
    kNERtcAudioStreamTypeSub = 1,
};
struct nertc_audio_layer_send_stats {
  /**
   * @if English
   * Audio stream tyepe.
   * @endif
   * @if Chinese
   * 音频流通道类型。
   * @endif
   */
  nertc_audio_stream_type stream_type;
  /**
   * @if English
   * The number of channels currently collected.
   * @endif
   * @if Chinese
   * 当前采集声道数。
   * @endif
   */
  int num_channels;
  /**
   * @if English
   * The sample rate of local uplink audio stream.
   * @endif
   * @if Chinese
   * 本地上行音频采样率。
   * @endif
   */
  int sent_sample_rate;
  /**
   * @if English
   * Publishing bitrate after last report (kbps).
   * @endif
   * @if Chinese
   * （上次统计后）发送码率(Kbps)。
   * @endif
   */
  int sent_bitrate;
  /**
   * @if English
   * Audio packet loss rate in a specific time (%).
   * @endif
   * @if Chinese
   * 特定时间内的音频丢包率 (%)。
   * @endif
   */
  int audio_loss_rate;
  /**
   * @if English
   * Round trip time.
   * @endif
   * @if Chinese
   * RTT。
   * @endif
   */
  int64_t rtt;
  /**
   * @if English
   * Volume range: 0 (lowest) to 100 (highest).
   * @endif
   * @if Chinese
   * 音量，范围为 0（最低）- 100（最高）。
   * @endif
   */
  unsigned int volume;
  /**
   * @if English
   * @endif
   * @if Chinese
   * 采集音量，范围为 0（最低）- 100（最高）。
   * @endif
   */
  unsigned int cap_volume;
};
/**
 * @if English
 * The local audio stream stats.
 * @endif
 * @if Chinese
 * 本地音频流上传统计信息。
 * @endif
 */
struct nertc_audio_send_stats {
  /**
   * @if English
   * Audio stream information array.
   * @endif
   * @if Chinese
   * 音频流信息数组。
   * @endif
   */
  nertc_audio_layer_send_stats* audio_layers_list;
  /**
   * @if English
   * The number of audio streams.
   * @endif
   * @if Chinese
   * 音频流条数。
   * @endif
   */
  int audio_layers_count;
};

/**
 * @if English
 * The stats of each remote audio stream.
 * @endif
 * @if Chinese
 * 远端用户单条音频流统计。
 * @endif
 */
struct nertc_audio_layer_recv_stats {
  /**
   * @if English
   * Audio stream type.
   * @endif
   * @if Chinese
   * 音频频流通道类型。
   * @endif
   */
  nertc_audio_stream_type stream_type;
  /**
   * @if English
   * The bitrate of the received audio stream after the last report (kbps).
   * @endif
   * @if Chinese
   * （上次统计后）接收到的码率(Kbps)。
   * @endif
   */
  int received_bitrate;
  /**
   * @if English
   * The user's downlink audio freeze cumulative time (ms).
   * @endif
   * @if Chinese
   * 用户的下行音频卡顿累计时长(ms)。
   * @endif
   */
  int total_frozen_time;
  /**
   * @if English
   * The user's downstream audio average freeze rate (%).
   * @endif
   * @if Chinese
   * 用户的下行音频平均卡顿率(%)。
   * @endif
   */
  int frozen_rate;
  /**
   * @if English
   * Audio packet loss rate in a specific time (%).
   * @endif
   * @if Chinese
   * 特定时间内的音频丢包率 (%)。
   * @endif
   */
  int audio_loss_rate;
  /**
   * @if English
   * Volume range: 0 (lowest) to 100 (highest).
   * @endif
   * @if Chinese
   * 音量，范围为 0（最低）- 100（最高）。
   * @endif
   */
  unsigned int volume;
};
/**
 * @if English
 * The stats of the audio stream from a remote user.
 * @endif
 * @if Chinese
 * 远端用户的音频统计。
 * @endif
 */
struct nertc_audio_recv_stats {
  /**
   * @if English
   * The user ID used to identify the audio stream.
   * @endif
   * @if Chinese
   * 用户 ID，指定是哪个用户的音频流。
   * @endif
   */
  nertc_uid_t uid;
  /**
   * @if English
   * Audio stream information array.
   * @endif
   * @if Chinese
   * 音频流信息数组。
   * @endif
   */
  nertc_audio_layer_recv_stats* audio_layers_list;
  /**
   * @if English
   * The number of audio streams.
   * @endif
   * @if Chinese
   * 音频流条数。
   * @endif
   */
  int audio_layers_count;
};

/**
 * @if English
 * @enum NERtcNetworkQualityType Network quality type.
 * @endif
 * @if Chinese
 * @enum NERtcNetworkQualityType 网络质量类型。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * 0: Unknown network quality.
   * @endif
   * @if Chinese
   * 0: 网络质量未知。
   * @endif
   */
  kNERtcNetworkQualityUnknown = 0,
  /**
   * @if English
   * 1: Excellent network quality.
   * @endif
   * @if Chinese
   * 1: 网络质量极好。
   * @endif
   */
  kNERtcNetworkQualityExcellent = 1,
  /**
   * @if English
   * 2: Good network quality is close to the excellent level but has the bitrate is lower an excellent network.
   * @endif
   * @if Chinese
   * 2: 用户主观感觉和 `kNERtcNetworkQualityExcellent` 类似，但码率可能略低于 `kNERtcNetworkQualityExcellent`。
   * @endif
   */
  kNERtcNetworkQualityGood = 2,
  /**
   * @if English
   * 3: Poor network does not affect communication.
   * @endif
   * @if Chinese
   * 3: 用户主观感受有瑕疵但不影响沟通。
   * @endif
   */
  kNERtcNetworkQualityPoor = 3,
  /**
   * @if English
   * 4: Users can communicate with each other without smoothness.
   * @endif
   * @if Chinese
   * 4: 勉强能沟通但不顺畅。
   * @endif
   */
  kNERtcNetworkQualityBad = 4,
  /**
   * @if English
   * 5: The network quality is very poor. Basically users are unable to communicate.
   * @endif
   * @if Chinese
   * 5: 网络质量非常差，基本不能沟通。
   * @endif
   */
  kNERtcNetworkQualityVeryBad = 5,
  /**
   * @if English
   * 6: Users are unable to communicate with each other.
   * @endif
   * @if Chinese
   * 6: 完全无法沟通。
   * @endif
   */
  kNERtcNetworkQualityDown = 6,
} nertc_network_quality_type;

/**
 * @if English
 * Network quality stats.
 * @endif
 * @if Chinese
 * 网络质量统计信息。
 * @endif
 */
struct nertc_network_quality_info {
  /**
   * @if English
   * The user ID used to identify the network quality stats.
   * @endif
   * @if Chinese
   * 用户 ID，指定是哪个用户的网络质量统计。
   * @endif
   */
  nertc_uid_t uid;
  /**
   * @if English
   * The uplink network quality. For more information, see #NERtcNetworkQualityType.
   * @endif
   * @if Chinese
   * 该用户的上行网络质量，详见 #NERtcNetworkQualityType.
   * @endif
   */
  nertc_network_quality_type tx_quality;
  /**
   * @if English
   * The downlink network quality. For more information, see #NERtcNetworkQualityType.
   * @endif
   * @if Chinese
   * 该用户的下行网络质量，详见 #NERtcNetworkQualityType.
   * @endif
   */
  nertc_network_quality_type rx_quality;
};

/**
 * @if English
 * @enum NERtcVideoCropMode Video cropping mode.
 * @endif
 * @if Chinese
 * @enum NERtcVideoCropMode 视频画面裁剪模式。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * Device Default
   * @endif
   * @if Chinese
   * 设备默认裁剪模式。
   * @endif
   */
  kNERtcVideoCropModeDefault = 0,
  /**
   * @if English
   * 16:9
   * @endif
   * @if Chinese
   * 16:9
   * @endif
   */
  kNERtcVideoCropMode16x9 = 1,
  /**
   * @if English
   * 4:3
   * @endif
   * @if Chinese
   * 4:3
   * @endif
   */
  kNERtcVideoCropMode4x3 = 2,
  /**
   * @if English
   * 1:1
   * @endif
   * @if Chinese
   * 1:1
   * @endif
   */
  kNERtcVideoCropMode1x1 = 3,
} nertc_video_crop_mode;

/**
 * @if English
 * @enum NERtcVideoFramerateType Video frame rate.
 * @endif
 * @if Chinese
 * @enum NERtcVideoFramerateType 视频帧率。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * default frame rate
   * @endif
   * @if Chinese
   * 默认帧率
   * @endif
   */
  kNERtcVideoFramerateFpsDefault = 0,
  /**
   * @if English
   * 7 frames per second
   * @endif
   * @if Chinese
   * 7帧每秒
   * @endif
   */
  kNERtcVideoFramerateFps_7 = 7,
  /**
   * @if English
   * 10 frames per second
   * @endif
   * @if Chinese
   * 10帧每秒
   * @endif
   */
  kNERtcVideoFramerateFps_10 = 10,
  /**
   * @if English
   * 15 frames per second
   * @endif
   * @if Chinese
   * 15帧每秒
   * @endif
   */
  kNERtcVideoFramerateFps_15 = 15,
  /**
   * @if English
   * 24 frames per second
   * @endif
   * @if Chinese
   * 24帧每秒
   * @endif
   */
  kNERtcVideoFramerateFps_24 = 24,
  /**
   * @if English
   * 30 frames per second
   * @endif
   * @if Chinese
   * 30帧每秒
   * @endif
   */
  kNERtcVideoFramerateFps_30 = 30,
  /**
   * @if English
   * 60 frames per second
   * @endif
   * @if Chinese
   * 60帧每秒
   * @endif
   */
  kNERtcVideoFramerateFps_60 = 60,
} nertc_video_framerate_type;

/**
 * @if English
 * @enum NERtcDegradationPreference Video encoding strategy.
 * @endif
 * @if Chinese
 * NERtcDegradationPreference 视频编码策略。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * - By default, adjust the adaptation preference based on scenarios.
   * - In communication scenes, select kNERtcDegradationBalanced mode to maintain a balance between the frame rate and video
   * quality.
   * - In live streaming scenes, select kNERtcDegradationMaintainQuality mode and reduce the frame rate to ensure video quality.
   * @endif
   * @if Chinese
   * - （默认）根据场景模式调整适应性偏好。
   * - 通信场景中，选择kNERtcDegradationBalanced 模式，在编码帧率和视频质量之间保持平衡。
   * - 直播场景中，选择kNERtcDegradationMaintainQuality 模式，降低编码帧率以保证视频质量。
   * @endif
   */
  kNERtcDegradationDefault = 0,
  /**
   * @if English
   * Smooth streams come first. Reduce video quality to ensure the frame rate. In a weak network environment, you can reduce the
   * video quality to ensure a smooth video playback. In this case, the image quality is reduced and the pictures become
   * blurred, but the video can be kept smooth.
   * @endif
   * @if Chinese
   * 流畅优先，降低视频质量以保证编码帧率。在弱网环境下，降低视频清晰度以保证视频流畅，此时画质降低，画面会变得模糊，但可以保持视频流畅。
   * @endif
   */
  kNERtcDegradationMaintainFramerate = 1,
  /**
   * @if English
   * Clarity is prioritized. Reduce the frame rate to ensure video quality. In a weak network environment, you can reduce the
   * video frame rate to ensure that the video is clear. In this case, a certain amount of freezes may occur at this time.
   * @endif
   * @if Chinese
   * 清晰优先，降低编码帧率以保证视频质量。在弱网环境下，降低视频帧率以保证视频清晰，此时可能会出现一定卡顿。
   * @endif
   */
  kNERtcDegradationMaintainQuality = 2,
  /**
   * @if English
   * Maintain a balance between the frame rate and video quality.
   * @endif
   * @if Chinese
   * 在编码帧率和视频质量之间保持平衡。
   * @endif
   */
  kNERtcDegradationBalanced = 3,
} nertc_degradation_preference;

/**
 * @if English
 * The video encoding profile configuration.
 * @endif
 * @if Chinese
 * 视频编码属性配置。
 * @endif
 */
struct nertc_video_config {
  /**
   * @if English
   * The resolution of video encoding used to measure encoding quality. For more information, see NERtcVideoProfileType
   * @endif
   * @if Chinese
   * 视频编码的分辨率，用于衡量编码质量。详细信息请参考 NERtcVideoProfileType。
   * @endif
   */
  nertc_video_profile_type max_profile;
  /**
   * @if English
   * Video encoding resolution, an indicator of encoding quality, is represented by width x height. You can select this profile
   * or maxProfile. <br>The width represents the pixels of the video frame on the horizontal axis. You can enter a custom width.
   * - If you set the value to a negative number, the maxProfile setting is used.
   * - If you need to customize the resolution, set this profile, and maxProfile becomes invalid.
   * If the width and height of the custom video input are invalid, the width and height are automatically scaled based on
   * maxProfile.
   * @endif
   * @if Chinese
   * 视频编码分辨率，衡量编码质量，以宽x高表示。与maxProfile属性二选一。
   * <br>width表示视频帧在横轴上的像素，即自定义宽。
   * - 设置为负数时表示采用 max_profile 档位。
   * - 如果需要自定义分辨率场景，则设置此属性，maxProfile属性失效。
   * 自定义视频输入width和height无效，会自动根据 maxProfile 缩放。
   * @endif
   */
  uint32_t width;
  /**
   * @if English
   * Video encoding resolution, an indicator of encoding quality, is represented by width x height. You can select this profile
   * or maxProfile. <br>The height represents the pixels of the video frame on the vertical axis. You can enter a custom height.
   * - If you set the value to a negative number, the maxProfile setting is used.
   * - If you need to customize the resolution, set this profile, and maxProfile becomes invalid.
   * If the width and height of the custom video input are invalid, the width and height are automatically scaled based on
   * maxProfile.
   * @endif
   * @if Chinese
   * 视频编码分辨率，衡量编码质量，以宽x高表示。与maxProfile属性二选一。
   * <br>height表示视频帧在纵轴上的像素，即自定义高。
   * - 设置为负数时表示采用 max_profile 档位。
   * - 如果需要自定义分辨率场景，则设置此属性，maxProfile属性失效。
   * <br>自定义视频输入width和height无效，会自动根据 maxProfile 缩放。
   * @endif
   */
  uint32_t height;
  /**
   * @if English
   * Video crop mode, aspect ratio. The default value is kNERtcVideoCropModeDefault. For more information, see
   * NERtcVideoCropMode.
   * @endif
   * @if Chinese
   * 视频裁剪模式，宽高比。默认为 kNERtcVideoCropModeDefault。详细信息请参考 NERtcVideoCropMode。
   * @endif
   */
  nertc_video_crop_mode crop_mode_;
  /**
   * @if English
   * The frame rate of the mainstream video encoding. For more information, see NERtcVideoFramerateType. By default, the frame
   * rate is determined based on maxProfile.
   * - max_profile >= STANDARD. frameRate = FRAME_RATE_FPS_30.
   * - max_profile < STANDARD. frameRate = FRAME_RATE_FPS_15.
   * @endif
   * @if Chinese
   * 主流的视频编码的帧率。详细信息请参考 NERtcVideoFramerateType。默认根据设置的maxProfile决定帧率。
   * - max_profile >= STANDARD，frameRate = FRAME_RATE_FPS_30。
   * - max_profile < STANDARD，frameRate = FRAME_RATE_FPS_15。
   * @endif
   */
  nertc_video_framerate_type framerate;
  /**
   * @if English
   * The minimum frame rate for video encoding. The default value is 0, which indicates that the minimum frame rate is used by
   * default
   * @endif
   * @if Chinese
   * 视频编码的最小帧率。默认为 0，表示使用默认最小帧率
   * @endif
   */
  nertc_video_framerate_type min_framerate;
  /**
   * @if English
   * Video encoding bitrate (kbps), use the default value if the setting is set to 0.
   * @endif
   * @if Chinese
   * 视频编码码率kbps，取0时使用默认值
   * @endif
   */
  uint32_t bitrate;
  /**
   * @if English
   * The minimum bitrate of video encoding in kbps. You can manually set the required minimum bitrate based on your business
   * requirements. If the bitrate is set to 0, the SDK computes and processes automatically.
   * @endif
   * @if Chinese
   * 视频编码的最小码率，单位为 Kbps。您可以根据场景需要，手动设置想要的最小码率，若设置为0，SDK 将会自行计算处理。
   * @endif
   */
  uint32_t min_bitrate;
  /**
   * @if English
   * Video encoding degradation preference when the bandwidth is limited. For more information, see NERtcDegradationPreference.
   * @endif
   * @if Chinese
   * 带宽受限时的视频编码降级偏好。详细信息请参考 NERtcDegradationPreference。
   * @endif
   */
  nertc_degradation_preference degradation_preference;
  /**
   * @if English
   * Set the mirror mode for the local video encoding. The mirror mode is used for publishing the local video stream. The
   * setting only affects the video picture seen by remote users.
   * @endif
   * @if Chinese
   * 设置本地视频编码的镜像模式，即本地发送视频的镜像模式，只影响远端用户看到的视频画面。
   * @endif
   */
  nertc_video_mirror_mode mirror_mode;
  /**
   * @if English
   * Set the orientation mode of the local video encoding, The orientation mode is used for publishing the local video stream,
   * which only affects the video picture seen by remote users.
   * @endif
   * @if Chinese
   * 设置本地视频编码的方向模式，即本地发送视频的方向模式，只影响远端用户看到的视频画面。
   * @endif
   */
  nertc_video_orientation_mode orientation_mode;
};

/**
 * @if English
 * Video frame rate callback.
 * @param uid         The user ID
 * @param data        The data pointer
 * @param type        The data type NERtcVideoType
 * @param  width      The width
 * @param  height     The height
 * @param count       The number of data types, including the number of offset and stride.
 * @param offset      The data offset of each type
 * @param stride      The data step of each type
 * @param rotation    Screen rotation angle NERtcVideoRotation
 * @param user_data   User transparent transmission data
 *
 * @endif
 * @if Chinese
 * 视频帧数据回调
 * @param  uid          用户id
 * @param  data         数据指针
 * @param  type         数据类型NERtcVideoType
 * @param  width        宽度
 * @param  height       高度
 * @param  count        数据类型个数，即offset及stride的数目
 * @param  offset       每类数据偏移
 * @param  stride       每类数据步进
 * @param  rotation     画面旋转角度NERtcVideoRotation
 * @param  user_data    用户透传数据
 * @endif
 */
typedef void (NERTC_CALL *on_frame_data_callback)(nertc_uid_t uid,
                                    void* data,
                                    uint32_t type,
                                    uint32_t width,
                                    uint32_t height,
                                    uint32_t count,
                                    uint32_t offset[4],
                                    uint32_t stride[4],
                                    uint32_t rotation,
                                    void* user_data);

/**
 * @if English
 * Configuration parameters for screen sharing encoding.
 * @endif
 * @if Chinese
 * 屏幕共享编码参数配置。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * 640x480, 5fps.
   * @endif
   * @if Chinese
   * 640x480, 5fps
   * @endif
   */
  kNERtcScreenProfile480P = 0,
  /**
   * @if English
   * 1280x720, 5fps.
   * @endif
   * @if Chinese
   * 1280x720, 5fps
   * @endif
   */
  kNERtcScreenProfileHD720P = 1,
  /**
   * @if English
   * 1920x1080, 5fps. This is the default value.
   * @endif
   * @if Chinese
   * 1920x1080, 5fps。默认
   * @endif
   */
  kNERtcScreenProfileHD1080P = 2,
  /**
   * @if English
   * Custom.
   * @endif
   * @if Chinese
   * 自定义
   * @endif
   */
  kNERtcScreenProfileCustom = 3,
  /**
   * @if English
   * None
   * @endif
   * @if Chinese
   * 无效果。
   * @endif
   */
  kNERtcScreenProfileNone = 4,
  /**
   * @if English
   * 1920x1080, 5fps. This is the default value.
   * @endif
   * @if Chinese
   * 1920x1080, 5fps。
   * @endif
   */
  kNERtcScreenProfileMAX = kNERtcScreenProfileHD1080P,
} nertc_screen_profile_type;


/**
 * @if English
 * Screen sharing status.
 * @endif
 * @if Chinese
 * 屏幕分享状态
 * @endif
 */
typedef enum {
  /**
   * @if English
   * Starts screen sharing.
   * @endif
   * @if Chinese
   * 开始屏幕共享。
   * @endif
   */
  kNERtcScreenCaptureStatusStart = 1,

  /**
   * @if English
   * Pauses screen sharing.
   * @endif
   * @if Chinese
   * 暂停屏幕共享。
   * @endif
   */
  kNERtcScreenCaptureStatusPause = 2,

  /**
   * @if English
   * Resumes screen sharing.
   * @endif
   * @if Chinese
   * 恢复屏幕共享。
   * @endif
   */
  kNERtcScreenCaptureStatusResume = 3,

  /**
   * @if English
   * Stops screen sharing.
   * @endif
   * @if Chinese
   * 停止屏幕共享。
   * @endif
   */
  kNERtcScreenCaptureStatusStop = 4,

  /**
   * @if English
   * The target window for screen sharing is covered.
   * @endif
   * @if Chinese
   * 屏幕分享的目标窗口被覆盖。
   * @note 在 Windows 平台中，某些窗口在被屏蔽之后，如果被置于图层最上层，此窗口图像可能会黑屏。此时会触发
   * onScreenCaptureStatus.kScreenCaptureStatusCovered 回调，建议应用层在触发此回调时提醒用户将待分享的窗口置于最上层。
   * @endif
   */
  kNERtcScreenCaptureStatusCovered = 5
} nertc_screen_capture_status;

/**
 * @if English
 * The position of the area to be shared with respect to the entire screen or window. If you leave the setting empty, the entire
 * screen or window is shared.
 * @endif
 * @if Chinese
 * 待共享区域相对于整个屏幕或窗口的位置，如不填，则表示共享整个屏幕或窗口。
 * @endif
 */
struct nertc_rectangle {
  /**
   * @if English
   * The horizontal offset of the upper left corner.
   * @endif
   * @if Chinese
   * 左上角的横向偏移。
   * @endif
   */
  int x;
  /**
   * @if English
   * The vertical offset of the upper left corner.
   * @endif
   * @if Chinese
   * 左上角的纵向偏移。
   * @endif
   */
  int y;
  /**
   * @if English
   * The width of the area to be shared.
   * @endif
   * @if Chinese
   * 待共享区域的宽。
   * @endif
   */
  int width;
  /**
   * @if English
   * The height of the area to be shared.
   * @endif
   * @if Chinese
   * 待共享区域的高。
   * @endif
   */
  int height;
};

/**
 * @if English
 * Video dimensions.
 * @endif
 * @if Chinese
 * 视频尺寸。
 * @endif
 */
struct nertc_video_dimensions {
  /**
   * @if English
   * The width
   * @endif
   * @if Chinese
   * 宽度
   * @endif
   */
  int width;
  /**
   * @if English
   * The height
   * @endif
   * @if Chinese
   * 高度
   * @endif
   */
  int height;
};

/**
 * @if English
 * Encoding strategy preference for screen sharing.
 * - kNERtcSubStreamContentPreferMotion: The content type is animation. When the shared content is a video, movie, or game, We
 * recommend that you select this content type.If a user sets the content type to animation, the user-defined frame rate is
 * applied.
 * - kNERtcSubStreamContentPreferDetails: The content type is details. When the shared content is an image or text, We recommend
 * that you select this content type. When the user sets the content type to details, the user is allowed to set up to 10
 * frames. If the setting exceeds 10 frames, 10 frames are applied.
 * @endif
 * @if Chinese
 * 屏幕共享功能的编码策略倾向。
 * - kNERtcSubStreamContentPreferMotion:
 * 内容类型为动画。当共享的内容是视频、电影或游戏时，推荐选择该内容类型。当用户设置内容类型为动画时，按用户设置的帧率处理。
 * - kNERtcSubStreamContentPreferDetails:
 * 内容类型为细节。当共享的内容是图片或文字时，推荐选择该内容类型。当用户设置内容类型为细节时，最高允许用户设置到10帧，设置超过
 * 10 帧时，不生效，按 10 帧处理。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * The animation mode.
   * @endif
   * @if Chinese
   * 动画模式。
   * @endif
   */
  kNERtcSubStreamContentPreferMotion = 0,
  /**
   * @if English
   * The details mode.
   * @endif
   * @if Chinese
   * 细节模式。
   * @endif
   */
  kNERtcSubStreamContentPreferDetails = 1,
} nertc_sub_stream_content_prefer;

/**
 * @if English
 * Configuration parameters for screen sharing encoding. The setting is used to measure encoding quality.
 * @endif
 * @if Chinese
 * 屏幕共享编码参数配置。用于衡量编码质量。
 * @endif
 */
struct nertc_screen_capture_parameters {
  /**
   * @if English
   * Configuration parameters for screen sharing encoding.
   * @endif
   * @if Chinese
   * 屏幕共享编码参数配置。
   * @endif
   */
  nertc_screen_profile_type profile;
  /**
   * @if English
   * The maximum pixel value sent by screen sharing video. The value is valid in kNERtcScreenProfileCustom.
   * @endif
   * @if Chinese
   * 屏幕共享视频发送的最大像素值，kNERtcScreenProfileCustom下生效。
   * @endif
   */
  nertc_video_dimensions dimensions;
  /**
   * @if English
   * The frame rate of the shared video.The value is valid in kNERtcScreenProfileCustom, and the unit is fps. The default value
   * is 5. A value more than 15 is not recommended.
   * @endif
   * @if Chinese
   * 共享视频的帧率，kNERtcScreenProfileCustom下生效，单位为 fps；默认值为 5，建议不要超过 15。
   * @endif
   */
  int frame_rate;
  /**
   * @if English
   * The bitrate of the shared video in kbps. The default value is 0, which indicates that the SDK calculates a reasonable value
   * based on the resolution of the current shared screen.
   * @endif
   * @if Chinese
   * 共享视频的码率，单位为 kbps；默认值为 0，表示 SDK 根据当前共享屏幕的分辨率计算出一个合理的值。
   * @endif
   */
  int bitrate;
  /**
   * @if English
   * Determines whether to capture the mouse during screen sharing.
   * @endif
   * @if Chinese
   * 是否采集鼠标用于屏幕共享。
   * @endif
   */
  bool capture_mouse_cursor;
  /**
   * @if English
   * Determing whether to bing the window to the front when you call the startScreenCaptureByWindowId method to share a window.
   * @endif
   * @if Chinese
   * 调用 startScreenCaptureByWindowId 方法共享窗口时，是否将该窗口前置。
   * @endif
   */
  bool window_focus;
  /**
   * @if English
   * ID list of windows to be blocked.
   * @endif
   * @if Chinese
   * 待屏蔽窗口的 ID 列表。
   * @endif
   */
  source_id_t* excluded_window_list;
  /**
   * @if English
   * The number of windows to be blocked.
   * @endif
   * @if Chinese
   * 待屏蔽窗口的数量。
   * @endif
   */
  int excluded_window_count;
  /**
   * @if English
   * Encoding strategy preference.
   * @endif
   * @if Chinese
   * 编码策略倾向。
   * @endif
   */
  nertc_sub_stream_content_prefer prefer;

  /**
   * @if English
   * Video encoding degradation preference when the bandwidth is limited. For more information, see
   * nertc_degradation_preference.
   * @endif
   * @if Chinese
   * 带宽受限时的视频编码降级偏好。详细信息请参考 NERtcDegradationPreference。
   * @endif
   */
  nertc_degradation_preference degradation_preference;
};

/**
 * @if English
 * Configuration of the video display.
 * @endif
 * @if Chinese
 * 视频显示设置
 * @endif
 */
struct nertc_video_canvas {
  /**
   * @if English
   * Specifies whether to use an external renderer. The default value is NO. If you want to use an external renderer, you can
   * associate the renderer by calling externalVideoRender with the SDK. if not, you can associate the renderer based on the
   * container with the SDK. Switching between the internal rendering and external rendering during a call is not supported.
   * @endif
   * @if Chinese
   * 是否使用外部渲染器，默认 NO
   * 不使用，若使用SDK内部会根据externalVideoRender来进行绑定，若不使用SDK内部根据container来进行绑定。暂不支持在通话中切换内部渲染与外部渲染。
   * @endif
   */
  bool use_external_render;
  /**
   * @if English
   * Data callbacks. For more information, see onFrameDataCallback.
   * <br>In macosx, you must set video_use_exnternal_render in NERtcEngineContext to true.
   * @endif
   * @if Chinese
   * 数据回调。详细信息请参考 onFrameDataCallback。
   * <br>在 macosx中，需要设置 NERtcEngineContex t的 video_use_exnternal_render 为 true 才有效。
   * @endif
   */
  on_frame_data_callback cb;
  /**
   * @if English
   * The user data returned by the callback for the data transparent transmission.
   * In macosx, you must set video_use_exnternal_render in NERtcEngineContext to true.
   * @endif
   * @if Chinese
   * 数据回调的用户透传数据。
   * <br>在 macosx中，需要设置 NERtcEngineContex t的 video_use_exnternal_render 为 true 才有效。
   * @endif
   */
  void* user_data;
  /**
   * @if English
   * Rendering window handle.
   * In macosx, you must set video_use_exnternal_render in NERtcEngineContext to false.
   * @endif
   * @if Chinese
   * 渲染窗口句柄。
   * <br>在 macosx中，需要设置 NERtcEngineContex t的 video_use_exnternal_render 为 false 才有效。
   *
   * @endif
   */
  void* window;
  /**
   * @if English
   * Video display mode. For more information, see NERtcVideoCropMode.
   * @endif
   * @if Chinese
   * 视频显示模式，详细信息请参考 NERtcVideoScalingMode。
   * @endif
   */
  nertc_video_scaling_mode scaling_mode;
  
  /**
   * @if Chinese
   * 背景颜色，格式为 0xRRGGBB，默认为黑色即 0x000000
   * @endif
   */
  uint32_t background_color;
};

/**
 * @if English
 * Recording type.
 * @endif
 * @if Chinese
 * 录制类型。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * Composite and individual stream recording.
   * @endif
   * @if Chinese
   * 参与合流+单流录制。
   * @endif
   */
  kNERtcRecordTypeAll = 0,
  /**
   * @if English
   * Composite recording mode.
   * @endif
   * @if Chinese
   * 参与合流录制模式。
   * @endif
   */
  kNERtcRecordTypeMix = 1,
  /**
   * @if English
   * individual recording mode.
   * @endif
   * @if Chinese
   * 参与单流录制模式。
   * @endif
   */
  kNERtcRecordTypeSingle = 2,

} nertc_record_type;

/**
 * @if English
 * Audio type.
 * @endif
 * @if Chinese
 * 音频类型。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * PCM audio format.
   * @endif
   * @if Chinese
   * PCM 音频格式。
   * @endif
   */
  kNERtcAudioTypePCM16 = 0,
} nertc_audio_type;

/**
 * @if English
 * Audio frame request data read and write mode.
 * @endif
 * @if Chinese
 * 音频帧请求数据的读写模式。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * Read-only mode
   * @endif
   * @if Chinese
   * 返回数据只读模式
   * @endif
   */
  kNERtcRawAudioFrameOpModeReadOnly = 0,
  /**
   * @if English
   * Read and write mode
   * @endif
   * @if Chinese
   * 返回数据可读写
   * @endif
   */
  kNERtcRawAudioFrameOpModeReadWrite,
} nertc_raw_audio_frame_op_mode_type;

/**
 * @if English
 * The audio frame request format.
 * @endif
 * @if Chinese
 *  音频帧请求格式。
 * @endif
 */
struct nertc_audio_frame_request_format {
  /**
   * @if English
   * the number of channels. If the audio is a stereo sound, the data is interleaved. mono: 1. stereo: 2.
   * @endif
   * @if Chinese
   * 音频声道数量。如果是立体声，数据是交叉的。单声道: 1；双声道 : 2。
   * @endif
   */
  uint32_t channels;
  /**
   * @if English
   * The sample rate.
   * @endif
   * @if Chinese
   * 采样率。
   * @endif
   */
  uint32_t sample_rate;
  /**
   * @if English
   * Read and write mode.
   * @endif
   * @if Chinese
   * 读写模式
   * @endif
   */
  nertc_raw_audio_frame_op_mode_type mode;
};

/**
 * @if English
 * The audio format.
 * @endif
 * @if Chinese
 * 音频格式。
 * @endif
 */
struct nertc_audio_format {
  /**
   * @if English
   * Audio type.
   * @endif
   * @if Chinese
   * 音频类型。
   * @endif
   */
  nertc_audio_type type;
  /**
   * @if English
   * the number of channels. If the audio is a stereo sound, the data interleaved. mono: 1. stereo: 2.
   * @endif
   * @if Chinese
   * 音频声道数量。如果是立体声，数据是交叉的。单声道: 1；双声道 : 2。
   * @endif
   */
  uint32_t channels;
  /**
   * @if English
   * The sample rate.
   * @endif
   * @if Chinese
   * 采样率。
   * @endif
   */
  uint32_t sample_rate;
  /**
   * @if English
   * The number of bytes per sample. For PCM, 16 bits are used, which means 2 bytes.
   * @endif
   * @if Chinese
   * 每个采样点的字节数。对于 PCM 来说，一般使用 16 bit，即两个字节。
   * @endif
   */
  uint32_t bytes_per_sample;
  /**
   * @if English
   * The number of samples per room.
   * @endif
   * @if Chinese
   * 每个房间的样本数量。
   * @endif
   */
  uint32_t samples_per_channel;
};

/**
 * @if English
 * The audio frame.
 * @endif
 * @if Chinese
 * 音频帧。
 * @endif
 */
struct nertc_audio_frame {
  /**
   * @if English
   * Audio format.
   * @endif
   * @if Chinese
   * 音频格式。
   * @endif
   */
  nertc_audio_format format;
  /**
   * @if English
   * Data buffer. The valid data length: samples_per_channel * channels * bytes_per_sample.
   * @endif
   * @if Chinese
   * 数据缓冲区。有效数据长度为：samples_per_channel * channels * bytes_per_sample。
   * @endif
   */
  void* data;
};

/**
 * @if English
 * Audio payload type.
 * @endif
 * @if Chinese
 * 音频payload类型。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * OPUS audio payload type.
   * @endif
   * @if Chinese
   * OPUS音频格式。
   * @endif
   */
  kNERtcAudioPayloadTypeOPUS = 111,
} nertc_audio_payload_type;

/**
 * @if English
 * Audio encoded frame of external input.
 * @endif
 * @if Chinese
 * 外部输入的编码后音频帧。
 * @endif
 */
struct nertc_audio_encoded_frame {
  /**
   * @if English
   * The audio encoded frame data.
   * @endif
   * @if Chinese
   * 编码后音频帧数据。
   * @endif
   */
  unsigned char* data;
  /**
   * @if English
   * The audio encoded frame timestamp. Unit: microseconds.
   * @endif
   * @if Chinese
   * 时间戳, 单位为微妙。
   * @endif
   */
  int64_t timestamp_us;
  /**
   * @if English
   * The audio encoded frame samplerate.
   * @endif
   * @if Chinese
   * 音频采样率。
   * @endif
   */
  int sample_rate;
  /**
   * @if English
   * The audio encoded frame channels.
   * @endif
   * @if Chinese
   * 音频声道数。
   * @endif
   */
  int channels;
  /**
   * @if English
   * The audio encoded frame samples per channel.
   * @endif
   * @if Chinese
   * 该编码片段中每个声道的样本数。
   * @endif
   */
  int samples_per_channel;
  /**
   * @if English
   * The audio encoded frame data length.
   * @endif
   * @if Chinese
   * 编码后音频帧数据长度。
   * @endif
   */
  int encoded_len;
  /**
   * @if English
   * The audio encoded timestmap, Unit: number of samples, such as 0, 960, 1920 ... increase.
   * @endif
   * @if Chinese
   * 编码时间, 单位为样本数, 如0、960、1920...递增。
   * @endif
   */
  int encoded_timestamp;
  /**
   * @if English
   * The audio encoded frame payload type. For more information, see NERtcAudioPayloadType.
   * @endif
   * @if Chinese
   * 编码后音频帧payload类型，详细信息请参考 NERtcAudioPayloadType。
   * @endif
   */
  nertc_audio_payload_type payload_type;

  /**
   * @if Chinese
   * 音频数据音量标记，有效值[0,100]，用于后台ASL选路时参考。默认100。
   * @endif
   */
  uint8_t rms_level;
};

struct nertc_audio_frame_observer {
	void *self;

    /**
     * @if English
     * Occurs when the audio data is captured. The callback is used to process the audio data.
     * @note
     * - The returned audio data has read and write permissions.
     * - The callback is triggered when an operation is driven by the local audio data.
     * @param frame The audio frame.
     * @endif
     * @if Chinese
     * 采集音频数据回调，用于声音处理等操作。
     * @note
     * - 返回音频数据支持读/写。
     * - 有本地音频数据驱动就会回调。
     * @param frame 音频帧。
     * @endif
     */
    void (NERTC_CALL *on_audio_frame_did_record)(void *self, struct nertc_audio_frame *frame);

    /**
     * @if English
     * Occurs when the audio substream data is captured. The callback is used to process the audio data.
     * @note
     * - The returned audio data has read and write permissions.
     * - The callback is triggered when an operation is driven by the local audio data.
     * @param frame The audio frame.
     * @endif
     * @if Chinese
     * 辅流采集音频数据回调。
     * <br>通过 \ref IRtcEngineEx::setAudioFrameObserver "setAudioFrameObserver" 接口设置回调监听，当辅流设备工作时，会触发该回调。此外您可以通过 \ref IRtcEngineEx::setRecordingAudioFrameParameters "setRecordingAudioFrameParameters" 接口设置回调数据格式。
     * @par 业务场景
     * 通过该回调数据可以获取辅流采集数据，也可以通过回调数据做音频前处理（变声、音效处理等）。
     * @since V4.6.20
     * @note
     * - 有本地音频辅流据驱动就会返回该回调。     
     * - 返回音频数据支持读/写。
     * - 该接口返回的数据格式，需要以返回数据 NERtcAudioFrame 中的 NERtcAudioFormat 为准。
     * @par 参数说明
     * <table>
     *  <tr>
     *      <th>**参数名称**</th>
     *      <th>**类型**</th>
     *      <th>**描述**</th>
     *  </tr>
     *  <tr>
     *      <td>frame</td>
     *      <td> \ref nertc::NERtcAudioFrame "NERtcAudioFrame"</td>
     *      <td>音频帧。包含数据格式及数据内容。</td>
     *  </tr>
     * </table>
     * @endif
     */
    void (NERTC_CALL *on_substream_audio_frame_did_record)(void *self, struct nertc_audio_frame *frame);

    /**
     * @if English
     * Occurs when the audio data is played back. The callback is used to process the audio data.
     * @note
     * - The returned audio data has read and write permissions.
     * - The callback is triggered when an operation is driven by the local audio data.
     * @param frame The audio frame.
     * @endif
     * @if Chinese
     * 播放音频数据回调，用于声音处理等操作。
     * @note
     * - 返回音频数据支持读/写。
     * - 有本地音频数据驱动就会回调。
     * @param frame 音频帧。
     * @endif
     */
    void (NERTC_CALL *on_audio_frame_will_playback)(void *self, struct nertc_audio_frame *frame);

    /**
     * @if English
     * Gets the raw audio data of the local user and all remote users after mixing.
     * @note
     * - The returned audio data is read-only.
     * - The callback is triggered when an operation is driven by the local audio data.
     * @param frame The audio frame.
     * @endif
     * @if Chinese
     * 获取本地用户和所有远端用户混音后的原始音频数据。
     * @note
     * - 返回音频数据只读。
     * - 有本地音频数据驱动就会回调。
     * @param frame 音频帧。
     * @endif
     */
    void (NERTC_CALL *on_mixed_audio_frame)(void *self, struct nertc_audio_frame *frame);

    /**
     * @if English
     * Gets the raw audio data of a specified remote user before audio mixing.
     * <br>After the audio observer is registered, if the remote audio is subscribed by default and the remote user
     * enables the audio, the SDK triggers this callback when the audio data before audio mixing is captured, and the
     * audio data is returned to the user.
     * @note The returned audio data is read-only.
     * @deprecated This API is about to be deprecated. Use \ref
     * nertc::INERtcAudioFrameObserver::onPlaybackAudioFrameBeforeMixing(uint64_t userID, NERtcAudioFrame* frame,
     * channel_id_t cid) "onPlaybackAudioFrameBeforeMixing"[2/2] instead. In multi-channel scenarios, channelId is used
     * to identify different channels.
     * @param userID The ID of a remote user.
     * @param frame The audio frame.
     * @endif
     * @if Chinese
     * 获取单个远端用户混音前的音频数据。
     * <br>成功注册音频观测器后，如果订阅了远端音频（默认订阅）且远端用户开启音频后，SDK
     * 会在捕捉到混音前的音频数据时，触发该回调，将音频数据回调给用户。
     * @note 返回音频数据只读。
     * @deprecated 即将废弃，请改用接口 \ref nertc::INERtcAudioFrameObserver::onPlaybackAudioFrameBeforeMixing(uint64_t
     * userID, NERtcAudioFrame* frame, channel_id_t cid)
     * "onPlaybackAudioFrameBeforeMixing"[2/2]。在多房间场景下，此接口可通过 cid 识别不同房间。
     * @param userID 用户 ID。
     * @param frame  音频帧。
     * @endif
     */
    void (NERTC_CALL *on_playback_audio_frame_before_mixing)(void *self, uint64_t user_id, struct nertc_audio_frame *frame, channel_id_t cid);

    /**
     * @if English
     * Gets the audio substream data from a specified remote user before mixing audio.
     * <br>After the audio observer is registered, the SDK will get the audio data from a specified remote user before
     * mixing if the remote audio substream is subscribed to and the remote user publishes the audio substream.
     * @note The returned audio data can only be read.
     * @param userID     A remote user ID.
     * @param frame      audio frame data.
     * @param cid        Room ID. For multiple rooms, channelId is used to identify the rooms.
     * @endif
     * @if Chinese
     * 获取指定远端用户混音前的辅流音频数据。
     * <br>成功注册音频观测器后，如果订阅了远端辅流音频（默认订阅）且远端用户开启辅流音频后，SDK
     * 会在捕捉到混音前的辅流音频数据时，触发该回调，将辅流音频数据回调给用户。
     * @note 返回音频数据只读。
     * @param userID 用户ID。
     * @param frame  音频帧。
     * @param cid    房间 ID。在多房间场景下，cid 用于识别不同的房间。
     * @endif
     */
    void (NERTC_CALL *on_playback_substream_audio_frame_before_mixing)(void *self, uint64_t user_id, struct nertc_audio_frame *frame, channel_id_t cid);
};

/**
 * @if English
 * The video type.
 * @endif
 * @if Chinese
 * 视频类型。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * I420 video format.
   * @endif
   * @if Chinese
   * I420 视频格式。
   * @endif
   */
  kNERtcVideoTypeI420 = 0,
  /**
   * @if English
   * NV12 video format.
   * @endif
   * @if Chinese
   * NV12 视频格式。
   * @endif
   */
  kNERtcVideoTypeNV12 = 1,
  /**
   * @if English
   * NV21 video format.
   * @endif
   * @if Chinese
   * NV21 视频格式。
   * @endif
   */
  kNERtcVideoTypeNV21 = 2,
  /**
   * @if English
   * BGRA video format.
   * @endif
   * @if Chinese
   * BGRA 视频格式。
   * @endif
   */
  kNERtcVideoTypeBGRA = 3,
  /**
   * @if English
   * ARGB video format.
   * @endif
   * @if Chinese
   * BGRA 视频格式。
   * @endif
   */
  kNERtcVideoTypeARGB = 4,
  /**
   * @if English
   * oc capture native video format. External video input is not allowed.
   * @endif
   * @if Chinese
   * oc capture native视频格式。不支持外部视频输入
   * @endif
   */
  kNERtcVideoTypeCVPixelBuffer = 5,
} nertc_video_type;

/**
 * @if English
 * The angle to which the video rotates.
 * @endif
 * @if Chinese
 * 视频旋转角度。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * 0 度。
   * @endif
   * @if Chinese
   * 0°
   * @endif
   */
  kNERtcVideoRotation_0 = 0,
  /**
   * @if English
   * 90°
   * @endif
   * @if Chinese
   * 90 度。
   * @endif
   */
  kNERtcVideoRotation_90 = 90,
  /**
   * @if English
   * 180°
   * @endif
   * @if Chinese
   * 180 度。
   * @endif
   */
  kNERtcVideoRotation_180 = 180,
  /**
   * @if English
   * 270°
   * @endif
   * @if Chinese
   * 270 度。
   * @endif
   */
  kNERtcVideoRotation_270 = 270,
} nertc_video_rotation;

/**
 * @if English
 * Video frame of external input.
 * @endif
 * @if Chinese
 * 外部输入的视频桢。
 * @endif
 */
struct nertc_video_frame {
  /**
   * @if English
   * The video frame format. For more information, see NERtcVideoType.
   * @endif
   * @if Chinese
   * 视频帧格式，详细信息请参考 NERtcVideoType。
   * @endif
   */
  nertc_video_type format;
  /**
   * @if English
   * The video timestamp. Unit: milliseconds.
   * @endif
   * @if Chinese
   * 视频时间戳，单位为毫秒。
   * @endif
   */
  uint64_t timestamp;
  /**
   * @if English
   * Video frame width.
   * @endif
   * @if Chinese
   * 视频桢宽度
   * @endif
   */
  uint32_t width;
  /**
   * @if English
   * Video frame height.
   * @endif
   * @if Chinese
   * 视频桢宽高
   * @endif
   */
  uint32_t height;
  /**
   * @if Chinese
   * 数据类型个数，即offset及stride的数目
   * @endif
   */
  int count;
  /**
   * @if English
   * offset of Video frame data .
   * @endif
   * @if Chinese
   * 每类数据偏移
   * @endif
   */
    uint32_t offset[4];
  /**
   * @if English
   * stride of Video frame data .
   * @endif
   * @if Chinese
   * 每类数据步进
   * @endif
   */
  uint32_t stride[4];
  /**
   * @if English
   * For more information about video rotation angle, see #NERtcVideoRotation.
   * @endif
   * @if Chinese
   * 视频旋转角度 详见: #NERtcVideoRotation
   * @endif
   */
  nertc_video_rotation rotation;
  /**
   * @if English
   * Video frame data.
   * @endif
   * @if Chinese
   * 视频桢数据
   * @endif
   */
  void* buffer;
  /**
   * @if English
   * The length of Video frame data.
   * @endif
   * @if Chinese
   * 视频桢数据长度
   * @endif
   */
  int64_t buffer_length;
};

/**
 * @if English
 * The video codec type.
 * @endif
 * @if Chinese
 * 视频编解码器类型。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * The H264 codec
   * @endif
   * @if Chinese
   * H264 编解码器。
   * @endif
   */
  kNERtcVideoCodecTypeH264 = 3,
} nertc_video_codec_type;

/**
 * @if English
 * The video encoded frame type.
 * @endif
 * @if Chinese
 * 视频编码帧类型。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * The IDR frame
   * @endif
   * @if Chinese
   * IDR 帧。
   * @endif
   */
  kNERtcNalFrameTypeIDR = 1,
  /**
   * @if English
   * I frame.
   * @endif
   * @if Chinese
   * I 帧。
   * @endif
   */
  kNERtcNalFrameTypeI = 2,
  /**
   * @if English
   * P frame.
   * @endif
   * @if Chinese
   * P 帧。
   * @endif
   */
  kNERtcNalFrameTypeP = 3,
} nertc_nal_frame_type;

/**
 * @if English
 * Video encoded frame of external input.
 * @endif
 * @if Chinese
 * 外部输入的编码后视频帧。
 * @endif
 */
struct nertc_video_encoded_frame {
  /**
   * @if English
   * The video codec type. For more information, see NERtcVideoCodecType.
   * @endif
   * @if Chinese
   * 视频编解码器类型，详细信息请参考 NERtcVideoCodecType。
   * @endif
   */
  nertc_video_codec_type codec_type;
  /**
   * @if English
   * The video encoded frame type. For more information, see NERtcNalFrameType.
   * @endif
   * @if Chinese
   * 编码后视频帧类型，详细信息请参考 NERtcNalFrameType。
   * @endif
   */
  nertc_nal_frame_type frame_type;
  /**
   * @if English
   * The nal count of video encoded frame.
   * @endif
   * @if Chinese
   * 编码后视频帧nal个数。
   * @endif
   */
  int nal_count;
  /**
   * @if English
   * The nal length of video encoded frame
   * @endif
   * @if Chinese
   * 编码后视频帧nal的长度。
   * @endif
   */
  int* nal_length;
  /**
   * @if English
   * The nal length of video encoded frame
   * @endif
   * @if Chinese
   * 编码后视频帧数据，包括所有nal的数据。
   * @endif
   */
  unsigned char* nal_data;
  /**
   * @if English
   * The video encoded frame timestamp. Unit: microseconds.
   * @endif
   * @if Chinese
   * 时间戳，机器时间，单位为微秒。
   * @endif
   */
  int64_t timestamp_us;
  /**
   * @if English
   * The video encoded frame width.
   * @endif
   * @if Chinese
   * 视频宽。
   * @endif
   */
  int width;
  /**
   * @if English
   * The video encoded frame height.
   * @endif
   * @if Chinese
   * 视频高。
   * @endif
   */
  int height;
};

/**
 * @if English
 * The reasons why the user leaves.
 * @endif
 * @if Chinese
 * 用户离开原因。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * A user leaves the room normally.
   * @endif
   * @if Chinese
   * 正常离开。
   * @endif
   */
  kNERtcSessionLeaveNormal = 0,
  /**
   * @if English
   * The user is disconnected and leaves the room.
   * @endif
   * @if Chinese
   * 用户断线导致离开。
   * @endif
   */
  kNERtcSessionLeaveForFailOver = 1,
  /**
   * @if English
   * The user leaves the room because the session fails over.
   * @endif
   * @if Chinese
   * 用户 Failover 过程中产生的 leave。
   * @endif
   */
  kNERtcSessionLeaveUpdate = 2,
  /**
   * @if English
   * The user is removed from the room.
   * @endif
   * @if Chinese
   * 用户被踢导致离开。
   * @endif
   */
  kNERtcSessionLeaveForKick = 3,
  /**
   * @if English
   * The user is disconnected due to connection timeout.
   * @endif
   * @if Chinese
   * 用户超时导致离开。
   * @endif
   */
  kNERtcSessionLeaveTimeOut = 4,
} nertc_session_leave_reason;

/**
 * @if English
 * The playback state of the music file.
 * @endif
 * @if Chinese
 * 音乐文件播放状态。
 *
 * @endif
 */
typedef enum {
  /**
   * @if English
   * The playback ends.
   * @endif
   * @if Chinese
   * 音乐文件播放结束。
   * @endif
   */
  kNERtcAudioMixingStateFinished = 0,
  /**
   * @if English
   * The playback fails because an error occurs. For more information, see #NERtcAudioMixingErrorCode.
   * @endif
   * @if Chinese
   * 音乐文件报错。详见: #NERtcAudioMixingErrorCode
   * @endif
   */
  kNERtcAudioMixingStateFailed = 1,
} nertc_audio_mixing_state;

/**
 * @if English
 * Configuration items for audio mixing.
 * @endif
 * @if Chinese
 * 创建混音的配置项
 * @endif
 */
struct nertc_create_audio_mixing_option {
    /**
    * @if English
    * The path of the audio file. The local absolute paths or URL addresses are supported.
    * - The path must include the file name and extension, such as "D:\\audio_files\\test.mp3".
    * - Supported audio formats: MP3, M4A, AAC, 3GP, WMA, and WAV.
    * @endif
    * @if Chinese
    * 待播放的音乐文件路径，支持本地绝对路径或 URL 地址。
    * - 需精确到文件名及后缀，例如 “D:\\audio_files\\test.mp3”。
    * - 支持的音乐文件类型包括 MP3、M4A、AAC、3GP、WMA 和 WAV 格式。
    * @endif
    */
    char path[kNERtcMaxURILength];
    /**
    * @if English
    * The number of loops for mixing audio playback:
    * -1: (Default) plays the audio effect for one time.
    * -≤ 0: plays in an infinite loop, until stops by calling pauseAudioMixing or stopAudioMixing.
    * @endif
    * @if Chinese
    * 伴音循环播放的次数：
    * - 1：（默认）播放音效一次。
    * - ≤ 0：无限循环播放，直至调用 pauseAudioMixing 后暂停，或调用 stopAudioMixing 后停止。
    * @endif
    */
    int loop_count;
    /**
    * @if English
    * Specifies whether to send the mixing audio to the remote client. The default value is true. The remote user can hear the
    * mixing audio after the remote user subscribes to the local audio stream.
    * @endif
    * @if Chinese
    * 是否将伴音发送远端，默认为 true，即远端用户订阅本端音频流后可听到该伴音。
    * @endif
    */
    bool send_enabled;
    /**
    * @if English
    * Indicates the publishing volume of a music file. Valid values: 0 to 100. The default value is 100, which indicates that the
    * original volume of the file is used.
    * @note If you modify the volume setting during a call, this setting will be used by default when you call the method again
    * during the current call.
    * @endif
    * @if Chinese
    * 乐文件的发送音量，取值范围为 0~100。默认为 100，表示使用文件的原始音量。
    * @note 若您在通话中途修改了音量设置，则当前通话中再次调用时默认沿用此设置。
    * @endif
    */
    uint32_t send_volume;
    /**
    * @if English
    * Specifies whether to play back the mixing audio on the local client. The default value is true. The local users can hear
    * the mixing audio.
    * @endif
    * @if Chinese
    * 是否本地播放伴音。默认为 true，即本地用户可以听到该伴音。
    * @endif
    */
    bool playback_enabled;
    /**
    * @if English
    * Indicates the playback volume of a music file. Valid values: 0 to 100. The default value is 100, which indicates that the
    * original volume of the file is used.
    * @note If you modify the volume setting during a call, this setting will be used by default when you call the method again
    * during the current call.
    * @endif
    * @if Chinese
    * 音乐文件的播放音量，取值范围为 0~100。默认为 100，表示使用文件的原始音量。
    * @note 若您在通话中途修改了音量设置，则当前通话中再次调用时默认沿用此设置。
    * @endif
    */
    uint32_t playback_volume;
    /**
    * @if English
    * The start of a playback position. Unit: milliseconds. Default value: 0.
    * @endif
    * @if Chinese
    * 音乐文件开始播放的时间，UTC 时间戳，即从1970 年 1 月 1 日 0 点 0 分 0 秒开始到事件发生时的毫秒数。默认值为
    * 0，表示立即播放。
    * @endif
    */
    uint64_t start_timestamp;

    /**
    * @if English
    * Specifies if a mixing audio uses a mainstream or substream. The default value is mainstream.
    * @endif
    * @if Chinese
    * 伴音跟随音频主流还是辅流，默认跟随主流。
    * @endif
    */
    nertc_audio_stream_type send_with_audio_type;

    /**
    * @if English
    * Audio playback progress callback interval, unit: ms, value range: 100~10000, default: 1000ms
    * @endif
    * @if Chinese
    * 伴音播放进度回调间隔，单位ms，取值范围为 100~10000, 默认1000ms
    * @endif
    */
    uint32_t progress_interval;
};

/**
 * @if English
 * Configuration items for audio effects.
 * @endif
 * @if Chinese
 * 创建音效的配置项
 * @endif
 */
struct nertc_create_audio_effect_option {
    /**
    * @if English
    * The path of the audio effect file. The local absolute paths or URL addresses are supported.
    * - The path must include the file name and extension, such as "D:\\audio_files\\test.mp3".
    * - Supported audio formats: MP3, M4A、AAC, 3GP, WMA, and WAV.
    * @endif
    * @if Chinese
    * 待播放的音效文件路径，支持本地绝对路径或 URL 地址。
    * - 需精确到文件名及后缀，例如 “D:\\audio_files\\test.mp3”。
    * - 支持的音效文件类型包括 MP3、M4A、AAC、3GP、WMA 和 WAV 格式。
    * @endif
    */
    char path[kNERtcMaxURILength];
    /**
    * @if English
    * The number of loops the audio effect is played:
    * -1: (Default) plays the audio effect for one time.
    * -≤ 0: Play sound effects in an infinite loop until you stop the playback by calling stopEffect or stopAllEffects.
    * @endif
    * @if Chinese
    * 音效循环播放的次数：
    * - 1：（默认）播放音效一次。
    * - ≤ 0：无限循环播放音效，直至调用 stopEffect 或 stopAllEffects 后停止。
    * @endif
    */
    int loop_count;
    /**
    * @if English
    * Specifies whether to send the mixing audio to the remote client. The default value is true. The remote user can hear the
    * mixing audio after the remote user subscribes to the local audio stream.
    * @endif
    * @if Chinese
    * 是否将伴音发送远端，默认为 true，即远端用户订阅本端音频流后可听到该伴音。
    * @endif
    */
    bool send_enabled;
    /**
    * @if English
    * Indicates the publishing volume of a music file. Valid values: 0 to 100. The default value is 100, which indicates that the
    * original volume of the file is used.
    * @note If you modify the volume setting during a call, this setting will be used by default when you call the method again
    * during the current call.
    * @endif
    * @if Chinese
    * 音乐文件的发送音量，取值范围为 0~100。默认为 100，表示使用文件的原始音量。
    * @note 若您在通话中途修改了音量设置，则当前通话中再次调用时默认沿用此设置。
    * @endif
    */
    uint32_t send_volume;
    /**
    * @if English
    * Specifies whether to play back. The default value is true. You can play back the local audio file.
    * @endif
    * @if Chinese
    * 是否可播放。默认为 true，即可在本地播放该音效。
    * @endif
    */
    bool playback_enabled;
    /**
    * @if English
    * Indicates the playback volume of a music file. Valid values: 0 to 100. The default value is 100, which indicates that the
    * original volume of the file is used.
    * @note If you modify the volume setting during a call, this setting will be used by default when you call the method again
    * during the current call.
    * @endif
    * @if Chinese
    * 音乐文件的播放音量，取值范围为 0~100。默认为 100，表示使用文件的原始音量。
    * @note 若您在通话中途修改了音量设置，则当前通话中再次调用时默认沿用此设置。
    * @endif
    */
    uint32_t playback_volume;
    /**
    * @if English
    * The start of a playback position. Unit: milliseconds. Default value: 0.
    * @endif
    * @if Chinese
    * 音乐文件开始播放的时间，UTC 时间戳，即从1970 年 1 月 1 日 0 点 0 分 0 秒开始到事件发生时的毫秒数。默认值为
    * 0，表示立即播放。
    * @endif
    */
    uint64_t start_timestamp;

    /**
    * @if English
    * Specifies if a mixing audio uses a mainstream or substream. The default value is mainstream.
    * @endif
    * @if Chinese
    * 伴音跟随音频主流还是辅流，默认跟随主流。
    * @endif
    */
    nertc_audio_stream_type send_with_audio_type;

    /**
    * @if English
    * Audio playback progress callback interval, unit: ms, value range: 100~10000, default: 1000ms
    * @endif
    * @if Chinese
    * 伴音播放进度回调间隔，单位ms，取值范围为 100~10000, 默认1000ms
    * @endif
    */
    uint32_t progress_interval;
};

/**
 * @if English
 * The video stream type.
 * @endif
 * @if Chinese
 * 视频流类型
 * @endif
 */
typedef enum {
  /**
   * @if English
   * mainstream.
   * @endif
   * @if Chinese
   * 主流
   * @endif
   */
  kNERTCVideoStreamMain = 0,
  /**
   * @if English
   * Substream.
   * @endif
   * @if Chinese
   * 辅流
   * @endif
   */
  kNERTCVideoStreamSub = 1,
  /**
   * @if English
   * Reserved parameter. Ignore this parameter.
   * @endif
   * @if Chinese
   * 预留参数，无需关注。
   * @endif
   */
  kNERTCVideoStreamCount,
} nertc_video_stream_type;

/**
 * @if English
 * Status during media stream relay.
 * @endif
 * @if Chinese
 * 媒体流转发状态
 * @endif
 */
typedef enum {
  /**
   * @if English
   * Initial state. After a successful call of stopChannelMediaRelay method to stop cross-room media streaming.
   * @endif
   * @if Chinese
   * 初始状态。在成功调用 stopChannelMediaRelay 停止跨房间媒体流转发后， onMediaRelayStateChanged 会回调该状态。
   * @endif
   */
  kNERtcChannelMediaRelayStateIdle = 0,
  /**
   * @if English
   * The SDK tries to relay cross-room media streams.
   * @endif
   * @if Chinese
   * SDK 尝试跨房间转发媒体流。
   * @endif
   */
  kNERtcChannelMediaRelayStateConnecting = 1,
  /**
   * @if English
   * Sets the host role of source channel into the target room.
   * @endif
   * @if Chinese
   * 源房间主播角色成功加入目标房间。
   * @endif
   */
  kNERtcChannelMediaRelayStateRunning = 2,
  /**
   * @if English
   * Failure occurs. See the error messages prompted by error of onMediaRelayEvent.
   * @endif
   * @if Chinese
   * 发生异常，详见 onMediaRelayEvent 的 error 中提示的错误信息。
   * @endif
   */
  kNERtcChannelMediaRelayStateFailure = 3,
} nertc_channel_media_relay_state;

/**
 * @if English
 * Events related to the media stream relay.
 * @endif
 * @if Chinese
 * 媒体流转发回调事件。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * Current media stream relay gets disconnected.
   * @endif
   * @if Chinese
   * 媒体流转发停止。
   * @endif
   */
  kNERtcChannelMediaRelayEventDisconnect = 0,
  /**
   * @if English
   * Starts to relay media streams.
   * @endif
   * @if Chinese
   * SDK 正在连接服务器，开始尝试转发媒体流。
   * @endif
   */
  kNERtcChannelMediaRelayEventConnecting = 1,
  /**
   * @if English
   * The media stream relay gets connected to the server.
   * @endif
   * @if Chinese
   * 连接服务器成功。
   * @endif
   */
  kNERtcChannelMediaRelayEventConnected = 2,
  /**
   * @if English
   * The video stream is relayed to the destination room.
   * @endif
   * @if Chinese
   * 视频音频媒体流成功转发到目标房间。
   * @endif
   */
  kNERtcChannelMediaRelayEventVideoSentToDestChannelSuccess = 3,
  /**
   * @if English
   * The audio stream is relayed to the destination room.
   * @endif
   * @if Chinese
   * 音频媒体流成功转发到目标房间。
   * @endif
   */
  kNERtcChannelMediaRelayEventAudioSentToDestChannelSuccess = 4,
  /**
   * @if English
   * Other streams such as screen sharing stream are relayed to the destination room.
   * @endif
   * @if Chinese
   * 媒体流屏幕共享等其他流成功转发到目标房间。
   * @endif
   */
  kNERtcChannelMediaRelayEventOtherStreamSentToDestChannelSuccess = 5,
  /**
   * @if English
   * Fails to relay media streams. Possible reasons：
   * - kNERtcErrChannelReserveErrorParam(414)
   * - kNERtcErrChannelMediaRelayInvalidState(30110)
   * - kNERtcErrChannelMediaRelayPermissionDenied(30111)
   * - kNERtcErrChannelMediaRelayStopFailed(30112)
   * @endif
   * @if Chinese
   * 媒体流转发失败。原因包括：
   * - kNERtcErrChannelReserveErrorParam(414)：请求参数错误。
   * - kNERtcErrChannelMediaRelayInvalidState(30110)：重复调用 startChannelMediaRelay。
   * - kNERtcErrChannelMediaRelayPermissionDenied(30111)：媒体流转发权限不足。例如调用 startChannelMediaRelay
   * 的房间成员为主播角色、或房间为双人通话房间，不支持转发媒体流。
   * - kNERtcErrChannelMediaRelayStopFailed(30112)：调用 stopChannelMediaRelay 前，未调用 startChannelMediaRelay。
   * @endif
   */
  kNERtcChannelMediaRelayEventFailure = 100,
} nertc_channel_media_relay_event;

/**
 * @if English
 * Data structure related to media stream relay.
 * @endif
 * @if Chinese
 * 媒体流转发相关的数据结构。
 * @endif
 */
struct nertc_channel_media_relay_info {
  /**
   * @if English
   * The name of the destination room to which the media stream is relayed.
   * @endif
   * @if Chinese
   * 房间名。
   * @endif
   */
  char channel_name[kNERtcMaxChannelNameLength];
  /**
   * @if English
   * The token used to connect to the destination room.
   * @endif
   * @if Chinese
   * 能加入房间的 Token。
   * @endif
   */
  char channel_token[kNERtcMaxTokenLength];
  /**
   * @if English
   * The user ID used in the destination room. This ID can be different from the ID used in the current room.
   * @endif
   * @if Chinese
   * 用户 ID。
   * @endif
   */
  nertc_uid_t uid;
};

/**
 * @if English
 * Configurations for media stream relay.
 * @endif
 * @if Chinese
 * 跨房间媒体流转发相关参数配置。
 * @endif
 */
struct nertc_channel_media_relay_config {
  /**
   * @if English
   * The information about the current room.
   * - `channelName`: Source channel name.
   * - `channel_token`: Token with access to source channel.
   * - `uid`: Identifies the UID of relaying media streams in the source channel.
   * @endif
   * @if Chinese
   * 源房间信息，包括：
   * - `channel_name`：源房间名。默认值为 nil，表示 SDK 填充当前的房间名。
   * - `channel_token`：能加入源房间的 Token。
   * - `uid`：标识源房间中的转发媒体流的 UID。
   * @endif
   */
  nertc_channel_media_relay_info* src_infos;
  /**
   * @if English
   * The configuration of the destination room.
   * - `channelName`：Destination channel names.
   * - `channel_token`：Token with access to target channels.
   * - `uid`：Identifies the UID of relaying media stream in the target channel. Do not set this parameter as the UID of the
   * host in the destination room. The parameter is different from all UIDs in the target channel.
   * @endif
   * @if Chinese
   * 目标房间信息，包括：
   * - `channelName`：目标房间的房间名。
   * - `channel_token`：可以加入目标房间的 Token。
   * - `uid`：标识目标房间中的转发媒体流的 UID。请确保不要将该参数设为目标房间的主播的 UID，并与目标房间中的 所有 UID 都不同。
   * @endif
   */
  nertc_channel_media_relay_info* dest_infos;
  /**
   * @if English
   * The number of destination rooms. The default value is 0.
   * @endif
   * @if Chinese
   * 目标房间数量。默认为 0。
   * @endif
   */
  int dest_count;
};

/**
 * @if English
 * Video watermark status.
 * @endif
 * @if Chinese
 * 视频水印状态。
 * @endif
 */
typedef enum {
  /**
   * @if Chinese
   * 水印设置成功。
   * @endif
   */
  kNERtcLocalWatermarkStateSetSuccess,
  /**
   * @if English
   * The device does not support video watermarks.
   * @endif
   * @if Chinese
   * 设备不支持。
   * @endif
   */
  kNERtcLocalWatermarkStateDeviceNotSupported,
  /**
   * @if English
   * The image format is not supported.
   * @endif
   * @if Chinese
   * 图片格式不支持。
   * @endif
   */
  kNERtcLocalWatermarkStateImgFormatNotSupported,
  /**
   * @if English
   * Image number error.
   * @endif
   * @if Chinese
   * 图片数量设置错误。
   * @endif
   */
  kNERtcLocalWatermarkStateImgNumError,
  /**
   * @if English
   * Image resolution error.
   * @endif
   * @if Chinese
   * 图片分辨率设置错误。
   * @endif
   */
  kNERtcLocalWatermarkStateImgSizeError,
  /**
   * @if Chinese
   * 播放帧率设置错误。
   * @endif
   */
  kNERtcLocalWatermarkStateFPSError,
  /**
   * @if English
   * Font error.
   * @endif
   * @if Chinese
   * 字体设置错误。
   * @endif
   */
  kNERtcLocalWatermarkStateFontError,
  /**
   * @if Chinese
   * 整体水印透明度设置错误。
   * @endif
   */
  kNERtcLocalWatermarkStateWmAlphaError,
  /**
   * @if Chinese
   * 文本内容为空。
   * @endif
   */
  kNERtcLocalWatermarkStateTextContentEmptyError,
  /**
   * @if English
   * Watermark canceled.
   * @endif
   * @if Chinese
   * 取消水印。
   * @endif
   */
  kNERtcLocalWatermarkStateCancel = 20
} nertc_local_video_watermark_state;

/**
 * @if English
 * Sets the parameters for image watermarks.
 * <br>You can add up to 4 picture watermarks.
 * @endif
 * @if Chinese
 * 图片水印设置参数。
 * <br>最多可以添加 4 个图片水印。
 * @endif
 */
struct nertc_video_watermark_image_config {
  /**
   * @if English
   * Watermark image path. The setting is invalid if left empty.
   * @endif
   * @if Chinese
   * 水印图片路径。空时无效。
   * @endif
   */
  char* image_paths[10];
  /**
   * @if English
   * The alpha channel of the watermark background color.
   * @endif
   * @if Chinese
   * 水印框内背景颜色透明度
   * @endif
   */
  int wm_alpha;
  /**
   * @if English
   * The width of the watermark frame. Unit: pixels. The default value is 0, which indicates no watermark frame.
   * @endif
   * @if Chinese
   * 水印框的宽度。单位为像素（pixel），默认值为 0，表示没有水印框。
   * @endif
   */
  int wm_width;
  /**
   * @if English
   * The height of the watermark frame. Unit: pixels. The default value is 0, which indicates no watermark frame.
   * @endif
   * @if Chinese
   * 水印框的高度。单位为像素（pixel），默认值为 0，表示没有水印框。
   * @endif
   */
  int wm_height;
  /**
   * @if English
   * The horizontal distance between the upper left corner of the watermark and the upper left corner of the video canvas. Unit:
   * pixels. The default value is 0.
   * @endif
   * @if Chinese
   * 水印图片左上角与视频画布左上角的水平距离。单位为像素（pixel），默认值为 0。
   * @endif
   */
  int offset_x;
  /**
   * @if English
   * The vertical distance between the upper left corner of the watermark and the upper left corner of the video canvas. Unit:
   * pixels. The default value is 0.
   * @endif
   * @if Chinese
   * 水印图片左上角与视频画布左上角的垂直距离。单位为像素（pixel），默认值为 0。
   * @endif
   */
  int offset_y;
  /**
   * @if English
   * The frame rate. The default value is 0 fps, which indicates that the images are not flipped automatically. Images are
   * displayed in static single frames. Note: The frame rate for clients on Windows does not exceed 20 fps.
   * @endif
   * @if Chinese
   * 播放帧率。默认 0 帧/秒，即不自动切换图片，图片单帧静态显示。注意：Windows端帧率不超过 20 fps。
   * @endif
   */
  int fps;
  /**
   * @if English
   * Specifies whether to loop. By default, loop is enabled. If the value is set to false, the watermarks disappear when the
   * playback is complete.
   * @endif
   * @if Chinese
   * 是否设置循环。默认循环，设置为 false 后水印数组播放完毕后消失。
   * @endif
   */
  bool loop;
};

/**
 * @if English
 * Parameters for text watermarks.
 * <br>You can add up to 10 text watermarks.
 * @endif
 * @if Chinese
 * 文字水印设置参数。
 * <br>最多可添加 10 个文字水印。
 * @endif
 */
struct nertc_video_watermark_text_config {
  /**
   * @if English
   * The text content.
   * @note
   * - The length of the string is unlimited. The final display is affected by the font size and the size of the watermark
   * frame. The part beyond the watermark frame is not displayed.
   * - If the width of the watermark frame is set, when the length of the text content exceeds the width of the watermark frame,
   * the text automatically wraps. If the text exceeds the height of the watermark frame, the excess part is not displayed.
   * - When the width and height of the watermark frame are not set, the text does not wrap, and the part beyond the watermark
   * frame is not be displayed.
   * @endif
   * @if Chinese
   * 文字内容。
   * @note
   * - 字符串长度无限制。最终显示受字体大小和水印框大小的影响。超出水印框的部分不显示。
   * - 如果设置了水印框宽度，当文字内容长度超过水印框宽度时，会自动换行，如果超出水印框高度，超出部分不显示。
   * - 未设置水印框宽度和高度时，文字不换行，超出水印框的部分不显示。
   * @endif
   */
  char content[kNERtcMaxBuffLength];
  /**
   * @if Chinese
   * 字体名称。
   * @endif
   */
  char font_name[kNERtcMaxURILength];
  /**
   * @if English
   * The font color. ARGB format.
   * @endif
   * @if Chinese
   * 字体颜色。ARGB 格式。
   * @endif
   */
  int font_color;
  /**
   * @if English
   * The font size. The default value is 10, equivalent to 10 x 15 lb on a 144 dpi device.
   * @endif
   * @if Chinese
   * 字体大小。默认值为 10，相当于 144 dpi 设备上的 10 x 15 磅。
   * @endif
   */
  int font_size;
  /**
   * @if English
   * The background color in the watermark frame. ARGB format. Transparency setting is supported.
   * @endif
   * @if Chinese
   * 水印框内背景颜色。ARGB格式，支持透明度设置。
   * @endif
   */
  int wm_color;
  /**
   * @if English
   * The alpha channel of the watermark background color.
   * @endif
   * @if Chinese
   * 水印框内背景颜色透明度
   * @endif
   */
  int wm_alpha;
  /**
   * @if English
   * The width of the watermark frame. Unit: pixels. The default value is 0, which indicates no watermark frame.
   * @endif
   * @if Chinese
   * 水印框的宽度。单位为像素（pixel），默认值为 0，表示没有水印框。
   * @endif
   */
  int wm_width;
  /**
   * @if English
   * The height of the watermark frame. Unit: pixels. The default value is 0, which indicates no watermark frame.
   * @endif
   * @if Chinese
   * 水印框的高度。单位为像素（pixel），默认值为 0，表示没有水印框。
   * @endif
   */
  int wm_height;
  /**
   * @if English
   * The horizontal distance between the upper left corner of the watermark and the upper left corner of the video canvas. Unit:
   * pixels.
   * @endif
   * @if Chinese
   * 水印左上角与视频画布左上角的水平距离。单位为像素（pixel）。
   * @endif
   */
  int offset_x;
  /**
   * @if English
   * The vertical distance between the upper left corner of the watermark and the upper left corner of the video canvas. Unit:
   * pixels.
   * @endif
   * @if Chinese
   * 水印左上角与视频画布左上角的垂直距离。单位为像素（pixel）。
   * @endif
   */
  int offset_y;
};

/**
 * @if English
 * Sets a timestamp watermark.
 * - You can add only 1 timestamp watermark.
 * - The time of the timestamp watermark is the same as the current time and changes in real time.
 * @endif
 * @if Chinese
 * 时间戳水印设置。
 * - 只能添加 1 个时间戳水印。
 * - 时间戳水印的时间和当前时间相同，且实时变化。
 * @endif
 */
struct nertc_video_watermark_timestamp_config {
  /**
   * @if Chinese
   * 字体名称。
   * @endif
   */
  char font_name[kNERtcMaxURILength];
  /**
   * @if English
   * The font color. ARGB format.
   * @endif
   * @if Chinese
   * 水印左上角与视频画布左上角的水平距离。单位为像素（pixel）。
   * @endif
   */
  int font_color;
  /**
   * @if English
   * The font size. The default value is 10, equivalent to 10 x 15 lb on a 144 dpi device.
   * @endif
   * @if Chinese
   * 字体颜色。ARGB 格式。
   * @endif
   */
  int font_size;
  /**
   * @if English
   * The background color in the watermark frame. ARGB format. Transparency setting is supported.
   * @endif
   * @if Chinese
   * 水印框内背景颜色。ARGB格式，支持透明度设置。
   * @endif
   */
  int wm_color;
  /**
   * @if English
   * The alpha channel of the watermark background color.
   * @endif
   * @if Chinese
   * 水印框内背景颜色透明度
   * @endif
   */
  int wm_alpha;
  /**
   * @if English
   * The width of the watermark frame. Unit: pixels. The default value is 0, which indicates no watermark frame.
   * @endif
   * @if Chinese
   * 水印框的宽度。单位为像素（pixel），默认值为 0，表示没有水印框。
   * @endif
   */
  int wm_width;
  /**
   * @if English
   * The height of the watermark frame. Unit: pixels. The default value is 0, which indicates no watermark frame.
   * @endif
   * @if Chinese
   * 水印框的高度。单位为像素（pixel），默认值为 0，表示没有水印框。
   * @endif
   */
  int wm_height;
  /**
   * @if English
   * The horizontal distance between the upper left corner of the watermark and the upper left corner of the video canvas. Unit:
   * pixels.
   * @endif
   * @if Chinese
   * 水印左上角与视频画布左上角的水平距离。单位为像素（pixel）。
   * @endif
   */
  int offset_x;
  /**
   * @if English
   * The vertical distance between the upper left corner of the watermark and the upper left corner of the video canvas. Unit:
   * pixels.
   * @endif
   * @if Chinese
   * 水印左上角与视频画布左上角的垂直距离。单位为像素（pixel）。
   * @endif
   */
  int offset_y;
};

/**
 * @if English
 * Video watermark settings. Three types of watermarks are supported. You can select one of the three types.
 * @endif
 * @if Chinese
 * 视频水印设置，目前支持三种类型的水印，但只能其中选择一种水印生效。
 * @endif
 */
struct nertc_video_watermark_config {
    /**
     * @if English
     * Video watermark type enumerations
     * @endif
     * @if Chinese
     * 视频水印类型枚举。
     * @endif
     */
    typedef enum {
        /**
         * @if English
         * Image watermark.
         * @endif
         * @if Chinese
         * 图片水印。
         * @endif
         */
        kNERtcWatermarkTypeImage = 0,
        /**
         * @if English
         * Text watermark.
         * @endif
         * @if Chinese
         * 文字水印。
         * @endif
         */
        kNERtcWatermarkTypeText,
        /**
         * @if English
         * Timestamp watermark.
         * @endif
         * @if Chinese
         * 时间戳水印。
         * @endif
         */
        kNERtcWatermarkTypeTimestamp
    }nertc_watermark_type;

    nertc_watermark_type watermark_type;
    nertc_video_watermark_image_config image_watermarks;
    nertc_video_watermark_text_config text_watermarks;
    nertc_video_watermark_timestamp_config timestamp_watermark;
};

/*
 * Returns the screenshot result.
 * @param errorCode The error code. For more information, see {@link NERtcErrorCode}.
 * @param image The screenshot. Images on macOS are in CGImageRef format.
 * @endif
 * @if Chinese
 * 截图结果回调。
 * @param errorCode 错误码。详细信息请参考 {@link NERtcErrorCode}。
 * @param image 截图图片。默认为图片文件所在路径。
 * @endif
 */
typedef void (NERTC_CALL *on_take_snapshot_callback)(void* self, nertc_uid_t uid, nertc_video_stream_type stream_type, int error_code, void* image);

/**
 * @if English
 * Log levels.
 * @endif
 * @if Chinese
 * 日志级别。
 * @endif
 * */
typedef enum {
  /**
   * @if English
   * Fatal.
   * @endif
   * @if Chinese
   * Fatal 级别日志信息。
   * @endif
   */
  kNERtcLogLevelFatal = 0,
  /**
   * @if English
   * Error.
   * @endif
   * @if Chinese
   * Error 级别日志信息。
   * @endif
   */
  kNERtcLogLevelError = 1,
  /**
   * @if English
   * Warning. The default log level.
   * @endif
   * @if Chinese
   * Warning 级别日志信息。默认级别
   * @endif
   */
  kNERtcLogLevelWarning = 2,
  /**
   * @if English
   * Info.
   * @endif
   * @if Chinese
   * Info 级别日志信息。
   * @endif
   */
  kNERtcLogLevelInfo = 3,
  /**
   * @if English
   * Detail Info.
   * @endif
   * @if Chinese
   * Detail Info 级别日志信息。
   * @endif
   */
  kNERtcLogLevelDetailInfo = 4,
  /**
   * @if English
   * Verbos.
   * @endif
   * @if Chinese
   * Verbos 级别日志信息。
   * @endif
   */
  kNERtcLogLevelVerbos = 5,
  /**
   * @if English
   * Debug. To get the complete log file, set the log level to this option.
   * @endif
   * @if Chinese
   * Debug 级别日志信息。如果你想获取最完整的日志，可以将日志级别设为该等级。
   * @endif
   */
  kNERtcLogLevelDebug = 6,
  /**
   * @if English
   * No logs.
   * @endif
   * @if Chinese
   * 不输出日志信息。
   * @endif
   */
  kNERtcLogLevelOff = 7,
} nertc_log_level;

/**
 * @if English
 * Video delivery strategy after publishing.
 * @endif
 * @if Chinese
 * 视频推流后发送策略。
 * @endif
 * */
typedef enum {
  /**
   * @if English
   * The client does not actively send the data stream. The stream is sent if the stream is subscribed.
   * @endif
   * @if Chinese
   * 不主动发送数据流，被订阅后发送。
   * @endif
   */
  kNERtcSendOnPubNone = 0,
  /**
   * @if English
   * The client actively sends the mainstream.
   * @endif
   * @if Chinese
   * 主动发送大流。
   * @endif
   */
  kNERtcSendOnPubHigh = 1,
  /**
   * @if English
   * The client actively sends the substream.
   * @endif
   * @if Chinese
   * 主动发送小流。
   * @endif
   */
  kNERtcSendOnPubLow = 1 << 1,
  /**
   * @if English
   * The client actively sends the mainstream and the substream.
   * @endif
   * @if Chinese
   * 主动发送大小流。
   * @endif
   */
  kNERtcSendOnPubAll = kNERtcSendOnPubLow | kNERtcSendOnPubHigh,
} nertc_send_on_pub_type;

/**
 * @if English
 * Configures private servers.
 * @note To use private servers, contact technical support for help.
 * @endif
 * @if Chinese
 * 私有化服务器配置项
 * @note 如需启用私有化功能，请联系技术支持获取详情。
 * @endif
 */
struct nertc_server_addresses {
  /**
   * @if English
   * 获取通道信息服务器
   * @endif
   * @if Chinese
   * The channel server.
   * @endif
   */
  char channel_server[kNERtcMaxURILength];
  /**
   * @if English
   * The stats server.
   * @endif
   * @if Chinese
   * 统计上报服务器
   * @endif
   */
  char statistics_server[kNERtcMaxURILength];
  /**
   * @if English
   * The stats dispatch server.
   * @endif
   * @if Chinese
   * 统计调度服务器
   * @endif
   */
  char statistics_dispatch_server[kNERtcMaxURILength];
  /**
   * @if English
   * The stats backup server.
   * @endif
   * @if Chinese
   * 统计备份服务器
   * @endif
   */
  char statistics_backup_server[kNERtcMaxURILength];
  /**
   * @if English
   * The roomServer server.
   * @endif
   * @if Chinese
   * roomServer服务器
   * @endif
   */
  char room_server[kNERtcMaxURILength];
  /**
   * @if English
   * The compatibility configuration server.
   * @endif
   * @if Chinese
   * 兼容性配置服务器
   * @endif
   */
  char compat_server[kNERtcMaxURILength];
  /**
   * @if English
   * The NOS domain name resolution server.
   * @endif
   * @if Chinese
   * nos 域名解析服务器
   * @endif
   */
  char nos_lbs_server[kNERtcMaxURILength];
  /**
   * @if English
   * The default NOS upload server.
   * @endif
   * @if Chinese
   * 默认nos 上传服务器
   * @endif
   */
  char nos_upload_sever[kNERtcMaxURILength];
  /**
   * @if English
   * The NOS token server.
   * @endif
   * @if Chinese
   * 获取NOS token 服务器
   * @endif
   */
  char nos_token_server[kNERtcMaxURILength];
  /**
   * @if English
   * The cloud proxy server.
   * @endif
   */
  char cloud_proxy_server[kNERtcMaxURILength];
  /**
   * @if English
   * The websocket proxy server.
   * @endif
   */
  char websocket_proxy_server[kNERtcMaxURILength];
  /**
   * @if English
   * The quic proxy server.
   * @endif
   */
  char quic_proxy_server[kNERtcMaxURILength];
  /**
   * @if English
   * The media proxy server.
   * @endif
   */
  char media_proxy_server[kNERtcMaxURILength];
  /**
   * @if English
   * Specifies whether to use Ipv6. The default value is false.
   * @endif
   * @if Chinese
   * 是否使用IPv6（默认false)
   * @endif
   */
  bool use_ipv6;
};

/**
 * @if English
 * Recording audio quality.
 * @endif
 * @if Chinese
 * 录音音质
 * @endif
 */
typedef enum {
  /**
   * @if English
   * Low quality
   * @endif
   * @if Chinese
   * 低音质
   * @endif
   */
  kNERtcAudioRecordingQualityLow = 0,
  /**
   * @if English
   * medium quality
   * @endif
   * @if Chinese
   * 中音质
   * @endif
   */
  kNERtcAudioRecordingQualityMedium = 1,
  /**
   * @if English
   * High quality
   * @endif
   * @if Chinese
   * 高音质
   * @endif
   */
  kNERtcAudioRecordingQualityHigh = 2,
} nertc_audio_recording_quality;

typedef enum {
  // 录制本地和所有远端用户混音后的音频（默认）
  kNERtcAudioRecordingPositionMixedRecordingAndPlayback = 0,
  // 仅录制本地用户的音频
  kNERtcAudioRecordingPositionRecording = 1,
  // 仅录制所有远端用户的音频
  kNERtcAudioRecordingPositionMixedPlayback = 2
} nertc_audio_recording_position;

typedef enum {
  // 音频录制缓存时间为0，实时写文件（默认）
  kNERtcAudioRecordingCycleTime0 = 0,
  // 音频录制缓存时间为10s，StopAudioRectording()后，将缓存都写到文件，文件数据时间跨度为: [0,10s]
  kNERtcAudioRecordingCycleTime10 = 10,
  // 音频录制缓存时间为60s，StopAudioRectording()后，将缓存都写到文件，文件数据时间跨度为: [0,60s]
  kNERtcAudioRecordingCycleTime60 = 60,
  // 音频录制缓存时间为360s，StopAudioRectording()后，将缓存都写到文件，文件数据时间跨度为: [0,360s]
  kNERtcAudioRecordingCycleTime360 = 360,
  // 音频录制缓存时间为900s，StopAudioRectording()后，将缓存都写到文件，文件数据时间跨度为: [0,900s]
  kNERtcAudioRecordingCycleTime900 = 900
} nertc_audio_recording_cycle_time;

struct nertc_audio_recording_configuration {
  // 录音文件在本地保存的绝对路径，需要精确到文件名及格式。例如：sdcard/xxx/audio.aac。请确保指定的路径存在并且可写。目前仅支持
  // WAV 或 AAC 文件格式。
  char file_path[kNERtcMaxURILength];

  // 录音采样率（Hz），可以设为 16000、32000（默认）、44100 或 48000。
  int sample_rate;

  // 录音音质，只在 AAC 格式下有效。详细信息请参考 {@link NERtcAudioRecordingQuality}。
  nertc_audio_recording_quality quality;

  // 录音文件所包含的内容。详细信息请参考 {@link NERtcAudioRecordingPosition}。
  nertc_audio_recording_position position;

  // 录制过程中，循环缓存的最大时间长度，单位(s)。详细信息请参考 {@link NERtcAudioRecordingCycleTime}。
  nertc_audio_recording_cycle_time cycle_time;
};

/**
 * @if English
 * The error code of recording callbacks.
 * @endif
 * @if Chinese
 * 录音回调事件错误码
 * @endif
 */
typedef enum {
  /**
   * @if English
   * Unsupported recording file format.
   * @endif
   * @if Chinese
   * 不支持的录音文件格式。
   * @endif
   */
  kNERtcAudioRecordErrorSuffix = 1,
  /**
   * @if English
   * fails to create a recording file. Reasons:
   * - The application does not have the write permissions.
   * - The file path does not exist.
   * @endif
   * @if Chinese
   * 无法创建录音文件，原因通常包括：
   * - 应用没有磁盘写入权限。
   * - 文件路径不存在。
   * @endif
   */
  kNERtcAudioRecordOpenFileFailed = 2,
  /**
   * @if English
   * Starts recording.
   * @endif
   * @if Chinese
   * 开始录制。
   * @endif
   */
  kNERtcAudioRecordStart = 3,
  /**
   * @if English
   * An error occurs during recording. The typical reason is that the disk space is full and cannot be written.
   * @endif
   * @if Chinese
   * 录制错误。原因通常为磁盘空间已满，无法写入。
   * @endif
   */
  kNERtcAudioRecordError = 4,
  /**
   * @if English
   * Recording is complete.
   * @endif
   * @if Chinese
   * 完成录制。
   * @endif
   */
  kNERtcAudioRecordFinish = 5,
} nertc_audio_recording_code;

/**
 * @if English
 * Fallback options when the uplink and downlink connections are weak.
 * @endif
 * @if Chinese
 * 上行、下行弱网时的回退选项。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * If the uplink or downlink network is unstable, the audio and video streams will not fall back, but the quality of the audio
   * and video streams cannot be guaranteed.
   * @note This option is only valid for the setLocalPublishFallbackOption method, and invalid for the
   * setRemoteSubscribeFallbackOption method.
   * @endif
   * @if Chinese
   * 上行或下行网络较弱时，不对音视频流作回退处理，但不能保证音视频流的质量。
   * @note 该选项只对 setLocalPublishFallbackOption 方法有效，对 setRemoteSubscribeFallbackOption 方法无效。
   * @endif
   */
  kNERtcStreamFallbackDisabled = 0,

  /**
   * @if English
   * In an unstable downlink network, the SDK only receives low-definition streams that have low resolution and bitrate.
   * @note This option is only valid for the setRemoteSubscribeFallbackOption method, and invalid for the
   * setLocalPublishFallbackOption method.
   * @endif
   * @if Chinese
   * 在下行网络条件较差的情况下，SDK 将只接收视频小流，即低分辨率、低码率视频流。
   * @note 该选项只对 setRemoteSubscribeFallbackOption 方法有效，对 setLocalPublishFallbackOption 方法无效。
   * @endif
   */
  kNERtcStreamFallbackVideoStreamLow = 1,

  /**
   * @if English
   * - In an unstable uplink network, only the audio stream is published.
   * - In an unstable downlink network, first try to receive only low-definition streams, which have low resolution and bitrate.
   * If the video stream cannot be displayed due to network quality, then the stream falls back to the audio stream.
   * @endif
   * @if Chinese
   * - 上行网络较弱时，只发布音频流。
   * - 下行网络较弱时，先尝试只接收视频小流，即低分辨率、低码率视频流。如果网络环境无法显示视频，则再回退到只接收音频流。
   * @endif
   */
  kNERtcStreamFallbackAudioOnly = 2,
} nertc_stream_fallback_option;

/**
 * @if English
 * Media stream encryption mode.
 * @endif
 * @if Chinese
 * 媒体流加密模式。
 * @endif
 * */
typedef enum {
  /**
   * @if English
   * 128-bit SM4 encryption, ECB mode.
   * @endif
   * @if Chinese
   * 128 位 SM4 加密，ECB 模式。
   * @endif
   */
  kNERtcGMCryptoSM4ECB = 0,
} nertc_encryption_mode;

/**
 * @if English
 * Media stream encryption scheme.
 * @endif
 * @if Chinese
 * 媒体流加密方案。
 * @endif
 */
struct nertc_encryption_config {
  /**
   * @if English
   * Media stream encryption mode. For more information, see NERtcEncryptionMode.
   * @endif
   * @if Chinese
   * 媒体流加密模式。详细信息请参考 NERtcEncryptionMode。
   * @endif
   */
  nertc_encryption_mode mode;
  /**
   * @if English
   * Media stream encryption key. The key is of string type. We recommend that you set the key to a string that contains only
   * letters.
   * @endif
   * @if Chinese
   * 媒体流加密密钥。字符串类型，推荐设置为英文字符串。
   * @endif
   */
  char key[kNERtcEncryptByteLength];
};

/**
 * @if English
 * Configurations of the last-mile network probe test.
 * @endif
 * @if Chinese
 * Last mile 网络探测配置。
 * @endif
 */
struct nertc_lastmile_probe_config {
  /**
   * @if English
   * Sets whether to test the uplink network.
   * <br>Some users, for example, the audience in a kNERtcChannelProfileLiveBroadcasting channel, do not need such a test。
   * - true: test.
   * - false: do not test.
   * @endif
   * @if Chinese
   * 是否探测上行网络。
   * <br>不发流的用户，例如直播房间中的普通观众，无需进行上行网络探测。
   * - true: 探测。
   * - false: 不探测。
   * @endif
   */
  bool probe_uplink;
  /**
   * @if English
   * Sets whether to test the downlink network:
   * - true: test.
   * - false: do not test.
   * @endif
   * @if Chinese
   * 是否探测下行网络。
   * - true: 探测。
   * - false: 不探测。
   * @endif
   */
  bool probe_downlink;
  /**
   * @if English
   * The expected maximum sending bitrate (bps) of the local user.
   * <br>The value ranges between 100000 and 5000000.
   * <br>We recommend setting this parameter according to the bitrate value set by setVideoConfig.
   * @endif
   * @if Chinese
   * 本端期望的最高发送码率。
   * <br>单位为 bps，范围为 [100000, 5000000]。
   * <br>推荐参考 setVideoConfig 中的码率值设置该参数的值。
   * @endif
   */
  uint32_t expected_uplink_bitratebps;
  /**
   * @if English
   * The expected maximum receiving bitrate (bps) of the local user. The value ranges between 100000 and 5000000.
   * @endif
   * @if Chinese
   * 本端期望的最高接收码率。
   * <br>单位为 bps，范围为 [100000, 5000000]。
   * @endif
   */
  uint32_t expected_downlink_bitratebps;
};

/**
 * @if English
 * States of the last-mile network probe test.
 * @endif
 * @if Chinese
 * Last mile 质量探测结果的状态。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * The last-mile network probe test is complete.
   * @endif
   * @if Chinese
   * 表示本次 last mile 质量探测的结果是完整的。
   * @endif
   */
  kNERtcLastmileProbeResultComplete = 1,
  /**
   * @if English
   * The last-mile network probe test is incomplete and the bandwidth estimation is not available, probably due to limited test
   * resources.
   * @endif
   * @if Chinese
   * 表示本次 last mile 质量探测未进行带宽预测，因此结果不完整。通常原因为测试资源暂时受限。
   * @endif
   */
  kNERtcLastmileProbeResultIncompleteNoBwe = 2,
  /**
   * @if English
   * The last-mile network probe test is not carried out, probably due to poor network conditions.
   * @endif
   * @if Chinese
   * 未进行 last mile 质量探测。通常原因为网络连接中断。
   * @endif
   */
  kNERtcLastmileProbeResultUnavailable = 3,
} nertc_lastmile_probe_result_state;

/**
 * @if English
 * The uplink or downlink last-mile network probe test result.
 * @endif
 * @if Chinese
 * 单向 Last mile 网络质量探测结果报告。
 * @endif
 */
struct nertc_lastmile_probe_one_way_result {
  /**
   * @if English
   * The network jitter (ms).
   * @endif
   * @if Chinese
   * 网络抖动，单位为毫秒 (ms)。
   * @endif
   */
  uint32_t jitter;
  /**
   * @if English
   * The packet loss rate (%).
   * @endif
   * @if Chinese
   * 丢包率（%）。
   * @endif
   */
  uint32_t packet_loss_rate;
  /**
   * @if English
   * The available band width (bps).
   * @endif
   * @if Chinese
   * 可用网络带宽预估，单位为 bps。
   * @endif
   */
  uint32_t available_band_width;
};

/**
 * @if English
 * The uplink and downlink last-mile network probe test result.
 * @endif
 * @if Chinese
 * 上下行 Last mile 网络质量探测结果。
 * @endif
 */
struct nertc_lastmile_probe_result {
  /**
   * @if English
   * The round-trip delay time (ms).
   * @endif
   * @if Chinese
   * 往返时延，单位为毫秒（ms）。
   * @endif
   */
  uint32_t rtt;
  /**
   * @if English
   * The state of the probe test.
   * @endif
   * @if Chinese
   * Last mile 质量探测结果的状态。
   * @endif
   */
  nertc_lastmile_probe_result_state state;
  /**
   * @if English
   * The uplink last-mile network probe test result.
   * @endif
   * @if Chinese
   * 上行网络质量报告。
   * @endif
   */
  nertc_lastmile_probe_one_way_result uplink_report;
  /**
   * @if English
   * The downlink last-mile network probe test result.
   * @endif
   * @if Chinese
   * 下行网络质量报告。
   * @endif
   */
  nertc_lastmile_probe_one_way_result downlink_report;
};
typedef enum {
    /**
     * @if English
     * 0: Do not use the cloud proxy.
     * @endif
     * @if Chinese
     * 0：关闭已设置的云代理。
     * @endif
     */
    kNERtcTransportTypeNoneProxy = 0,
    /**
     * @if English
     * 1: Sets the cloud proxy for the UDP protocol.
     * @endif
     * @if Chinese
     * 1: 开启 UDP 协议的云代理。
     * @endif
     */
    kNERtcTransportTypeUDPProxy = 1,
} nertc_transport_type;

/**
 * @if English
 * Install audio driver plug-in result (only for Mac system)
 * @endif
 * @if Chinese
 * 安装音频驱动插件结果（仅适用于 Mac 系统）
 * @endif
 */
typedef enum {
    /**
     * @if English
     * Install audio driver plug-in success.
     * @endif
     * @if Chinese
     * 安装音频驱动插件成功
     * @endif
     */
    kNERtcInstallCastAudioDriverSuccess = 0,
    /**
     * @if English
     * Install audio driver plug-in because unauthorized.
     * @endif
     * @if Chinese
     * 安装音频驱动插件未授
     * @endif
     */
    kNERtcInstallCastAudioDriverNotAuthorized = 1,
    /**
     * @if English
     * Install audio driver plug-in fail.
     * @endif
     * @if Chinese
     * 安装音频驱动插件失败
     * @endif
     */
    kNERtcInstallCastAudioDriverFailed = 2,
} nertc_install_cast_audio_driver_result;
/**
 * @if English
 * The reason why the virtual background is not successfully enabled or the message that confirms success.
 * @since v4.6.0
 * @endif
 * @if Chinese
 * 虚拟背景未成功启用的原因或确认成功的信息。
 * @since v4.6.0
 * @endif
 */
typedef enum{
    /**
     * @if English
     * 0: The virtual background is successfully enabled.
     * @endif
     * @if Chinese
     * 0:  虚拟背景开启成功。
     * @endif
     */
    kNERtcVirtualBackgroundSourceStateReasonSuccess = 0,
    /**
     * @if English
     * 1: The custom background image does not exist. Please check the value of `source` in VirtualBackgroundSource.
     * @endif
     * @if Chinese
     * 1：自定义背景图片不存在。 请检查 VirtualBackgroundSource 中 `source` 的值。
     * @endif
     */
    kNERtcVirtualBackgroundSourceStateReasonImageNotExist = 1,
    /**
     * @if English
     * 2: The image format of the custom background image is invalid. Please check the value of `source` in
     * VirtualBackgroundSource.
     * @endif
     * @if Chinese
     * 2：自定义背景图片的图片格式无效。 请检查 VirtualBackgroundSource 中 `source` 的值。
     * @endif
     */
    kNERtcVirtualBackgroundSourceStateReasonImageFormatNotSupported = 2,
    /**
     * @if English
     * 3: The color format of the custom background image is invalid. Please check the value of `color` in
     * VirtualBackgroundSource.
     * @endif
     * @if Chinese
     * 3：自定义背景图片的颜色格式无效。 请检查 VirtualBackgroundSource 中 `color` 的值。
     * @endif
     */
    kNERtcVirtualBackgroundSourceStateReasonColorFormatNotSupported = 3,
    /**
     * @if English
     * 4: The device does not support using the virtual background.
     * @endif
     * @if Chinese
     * 4：该设备不支持使用虚拟背景。
     * @endif
     */
    kNERtcVirtualBackgroundSourceStateReasonDeviceNotSupported = 4
} nertc_virtual_background_source_state_reason;

/**
 * @if English
 * The custom background image.
 * @since v4.6.0
 * @endif
 * @if Chinese
 * 自定义背景图像。
 * @since v4.6.0
 * @endif
 */
struct nertc_virtual_background_source {
    /**
     * @if English
     * The type of the custom background image.
     * @since v4.6.0
     * @endif
     * @if Chinese
     * 自定义背景图片的类型。
     * @since v4.6.0
     * @endif
     */
    typedef enum {
        /**
         * @if English
         * 1: (Default) The background image is a solid color.
         * @endif
         * @if Chinese
         * 1：（默认）背景图像为纯色。
         * @endif
         */
        kNERtcBackgroundColor = 1,

        /**
         * @if English
         * The background image is a file in PNG or JPG format.
         * @endif
         * @if Chinese
         * 背景图像只支持 PNG 或 JPG 格式的文件。
         * @endif
         */
        kNERtcBackgroundImage,
    }nertc_background_source_type;

    /**
     * @if English
     * The type of the custom background image. See #NERtcBackgroundSourceType.
     * @endif
     * @if Chinese
     * 自定义背景图片的类型。 请参阅#NERtcBackgroundSourceType。
     * @endif
     */
    nertc_background_source_type background_source_type;

    /**
     * @if English
     * The color of the custom background image. The format is a hexadecimal integer defined by RGB, without the # sign,
     * such as 0xFFB6C1 for light pink. The default value is 0xFFFFFF, which signifies white. The value range
     * is [0x000000,0xFFFFFF]. If the value is invalid, the SDK replaces the original background image with a white
     * background image.
     * @note This parameter takes effect only when the type of the custom background image is `kNERtcBackgroundColor`.
     * @endif
     * @if Chinese
     * 自定义背景图像的颜色。格式为RGB定义的十六进制整数，不带#号，
     * 例如 0xFFB6C1 代表浅粉色。默认值为 0xFFFFFF，表示白色。取值范围是 [0x000000,0xFFFFFF]。如果该值无效，
     * SDK 将原始背景图片替换为白色的图片
     * @note 该参数仅在自定义背景图片类型为`kNERtcBackgroundColor`时生效。
     * @endif
     */
    unsigned int color;

    /**
     * @if English
     * The local absolute path of the custom background image. PNG and JPG formats are supported.
     * @note This parameter takes effect only when the type of the custom background image is `kNERtcBackgroundImage`.
     * @endif
     * @if Chinese
     * 自定义背景图片的本地绝对路径。支持 PNG 和 JPG 格式。
     * @note 该参数仅在自定义背景图片类型为`kNERtcBackgroundImage`时生效。
     * @endif
     */
    char source[kNERtcMaxURILength];
};

/**
 音频dump类型
 */
typedef enum {
  /**
   * @if Chinese
   * 仅输出.dump文件（默认）
   * @since v4.6.0
   * @endif
   */
  kNERtcAudioDumpTypePCM = 0,
  /**
   * @if Chinese
   * 输出.dump和.wav文件
   * @since v4.6.0
   * @endif
   */
  kNERtcAudioDumpTypeAll = 1,
  /**
   * @if Chinese
   * 仅输出.wav文件
   * @since v4.6.0
   * @endif
   */
  kNERtcAudioDumpTypeWAV = 2
} nertc_audio_dump_type;

/** 混响参数 */
struct nertc_reverb_param {
    /**
     * @if English
     * Wet sound signal. Value range: 0 ~ 1. The default value is 0.0f.
     * @endif
     * @if Chinese
     * 湿信号，取值范围为 0 ~ 1，默认值为 0.0f。
     * @endif
     */
    float wet_gain;
    /**
     * @if English
     * Dry sound signal. Value range: 0 ~ 1. The default value is 1.0f.
     * @endif
     * @if Chinese
     * 干信号，取值范围为 0 ~ 1，默认值为 1.0f。
     * @endif
     */
    float dry_gain;
    /**
     * @if English
     * Reverb damping. Value range: 0 ~ 1. The default value is 1.0f.
     * @endif
     * @if Chinese
     * 混响阻尼，取值范围为 0 ~ 1，默认值为 1.0f。
     * @endif
     */
    float damping;
    /**
     * @if English
     * Room size. Value range: 0.1 ~ 2. The default value is 0.1f.
     * @endif
     * @if Chinese
     * 房间大小，取值范围为 0.1 ~ 2，默认值为 0.1f。
     * @endif
     */
    float room_size;
    /**
     * @if English
     * Decay time. Value range: 0.1 ~ 20. The default value is 0.1f.
     * @endif
     * @if Chinese
     * 持续强度（余响），取值范围为 0.1 ~ 20，默认值为 0.1f。
     * @endif
     */
    float decay_time;
    /**
     * @if English
     * Pre-delay. Value range: 0 ~ 1. The default value is 0.0f.
     * @endif
     * @if Chinese
     * 延迟长度，取值范围为 0 ~ 1，默认值为 0.0f。
     * @endif
     */
    float predelay;
};

typedef enum {
    /**
     * 默认模式
     */
    kNERtcRangeAudioModeDefault = 0,
    /**
     * 小组模式
     */
    kNERtcRangeAudioModeTeam = 1,
} nertc_range_audio_mode;

/** 
 * @if Chinese
 * 加入音视频房间时的一些可选信息。
 * @endif
 */
struct nertc_join_channel_options {
    /**
     * @if Chinese
     * 自定义信息，最长支持 127 个字符。
     * @endif
     */
    char custom_info[kNERtcCustomInfoLength];
    /**
     * @if Chinese
     * 权限密钥。能控制通话时长及媒体权限能力。
     * @endif
     */
    char* permission_key;
    
    /**
    * @if Chinese
    * 小队号
    * @endif
    */
    int32_t team_id;
    /**
    * @if Chinese
    * 语音模式。
    * @endif
    */
    nertc_range_audio_mode mode;
    /**
    * @if Chinese
    * 语音接收范围。
    * @endif
    */
    int audible_distance;
};

struct nertc_join_channel_options_ex {
    /**
     * @if Chinese
     * 自定义信息，最长支持 127 个字符。
     * @endif
     */
    char custom_info[kNERtcCustomInfoLength];
    /**
     * @if Chinese
     * 权限密钥。能控制通话时长及媒体权限能力。
     * @endif
     */
    char* permission_key;
     /**
     * @if Chinese
     * 小队号
     * @endif
     */
    int32_t team_id;
    /**
     * @if Chinese
     * 语音模式。
     * @endif
     */
    nertc_range_audio_mode mode;
    /**
     * @if Chinese
     * 语音接收范围。
     * @endif
     */
    int audible_distance;
};

/** onUserJoined 回调的一些可选信息 */
struct nertc_user_join_extra_info {
    /**
     * 自定义信息， 来源于远端用户joinChannel时填的 {@link NERtcJoinChannelOptions#custom_info}参数，默认为空字符串。
     */
    char custom_info[kNERtcCustomInfoLength];
};

/**
 * @if English
 * @since v4.6.10
 * Media pub type.
 * @endif
 * @if Chinese
 * @since v4.6.10
 * 媒体 pub 类型。
 * @endif
 */
typedef enum {
    /**
     * @if English
     * Audio pub type.
     * @endif
     * @if Chinese
     * 音频 pub 类型。
     * @endif
     */
    NERtcMediaPubTypeAudio
} nertc_media_pub_type;

/**
 * @if English
 * Beauty types
 * @endif
 * @if Chinese
 * 美颜类型。
 * @endif
 */
typedef enum {
    /**
     * @if English
     * Applies bright teeth. The default value of intensity is 0.0.
     * @endif
     * @if Chinese
     * 美牙。强度默认值为 0.0。
     * @endif
     */
    kNERtcBeautyWhiteTeeth = 0,

    /**
     * @if English
     * Applies bright eyes. The default value of intensity is 0.0.
     * @endif
     * @if Chinese
     * 亮眼。强度默认值为 0.0。
     * @endif
     */
    kNERtcBeautyLightEye,

    /**
     * @if English
     * Whitening. The default value of intensity is 0.0.
     * @endif
     * @if Chinese
     * 美白。强度默认值为 0.0。
     * @endif
     */
    kNERtcBeautyWhiten,

    /**
     * @if English
     * Smoothing. The default value of intensity is 0.0.
     * @endif
     * @if Chinese
     * 磨皮。强度默认值为 0.0。
     * @endif
     */
    kNERtcBeautySmooth,

    /**
     * @if English
     * Applies a small nose. The default value of intensity is 0.0.
     * @endif
     * @if Chinese
     * 小鼻。强度默认值为 0.0。
     * @endif
     */
    kNERtcBeautySmallNose,

    /**
     * @if English
     * Adjusts the eye distance. The default value of intensity is 0.5.
     * @endif
     * @if Chinese
     * 眼距调整。强度默认值为 0.5。
     * @endif
     */
    kNERtcBeautyEyeDis,

    /**
     * @if English
     * Adjusts the eye angle. The default value of intensity is 0.5.
     * @endif
     * @if Chinese
     * 眼角调整。强度默认值为 0.5。
     * @endif
     */
    kNERtcBeautyEyeAngle,

    /**
     * @if English
     * Adjusts the mouth shape. The default value of intensity is 0.5.
     * @endif
     * @if Chinese
     * 嘴型调整。强度默认值为 0.5。
     * @endif
     */
    kNERtcBeautyMouth,

    /**
     * @if English
     * Applies big eyes. The default value of intensity is 0.0.
     * @endif
     * @if Chinese
     * 大眼。强度默认值为 0.0。
     * @endif
     */
    kNERtcBeautyBigEye,

    /**
     * @if English
     * Applies a small face. The default value of intensity is 0.0.
     * @endif
     * @if Chinese
     * 小脸。强度默认值为 0.0。
     * @endif
     */
    kNERtcBeautySmallFace,

    /**
     * @if English
     * Adjusts the jaw. The default value of intensity is 0.0.
     * @endif
     * @if Chinese
     * 下巴调整。强度默认值为 0.0。
     * @endif
     */
    kNERtcBeautyJaw,

    /**
     * @if English
     * Applies a thin face. The default value of intensity is 0.0.
     * @endif
     * @if Chinese
     * 瘦脸。强度默认值为 0.0。
     * @endif
     */
    kNERtcBeautyThinFace,

    /**
     * @if English
     * Applies a ruddy face. The default value of intensity is 0.0.
     * @endif
     * @if Chinese
     * 红润。强度默认值为 0.0。
     * @endif
     */
    kNERtcBeautyFaceRuddy,

    /**
     * @if English
     * Applies a long nose. The default value of intensity is 0.5.
     * @endif
     * @if Chinese
     * 长鼻。强度默认值为 0.5。
     * @endif
     */
    kNERtcBeautyLongNose,

    /**
     * @if English
     * Adjusts the philtrum. The default value of intensity is 0.5.
     * @endif
     * @if Chinese
     * 人中。强度默认值为 0.5。
     * @endif
     */
    kNERtcBeautyRenZhong,

    /**
     * @if English
     * Adjusts the mouth angle. The default value of intensity is 0.5.
     * @endif
     * @if Chinese
     * 嘴角。强度默认值为 0.5。
     * @endif
     */
    kNERtcBeautyMouthAngle,

    /**
     * @if English
     * Applies round eyes. The default value of intensity is 0.0.
     * @endif
     * @if Chinese
     * 圆眼。强度默认值为 0.0。
     * @endif
     */
    kNERtcBeautyRoundEye,

    /**
     * @if English
     * Adjusts the eye corners. The default value of intensity is 0.0.
     * @endif
     * @if Chinese
     * 开眼角。强度默认值为 0.0。
     * @endif
     */
    kNERtcBeautyOpenEyeAngle,

    /**
     * @if English
     * Applies a V-shaped face. The default value of intensity is 0.0.
     * @endif
     * @if Chinese
     * V 脸。强度默认值为 0.0。
     * @endif
     */
    kNERtcBeautyVFace,

    /**
     * @if English
     * Applies a thin jaw. The default value of intensity is 0.0.
     * @endif
     * @if Chinese
     * 瘦下颚。强度默认值为 0.0。
     * @endif
     */
    kNERtcBeautyThinUnderjaw,

    /**
     * @if English
     * Applies a narrow face. The default value of intensity is 0.0.
     * @endif
     * @if Chinese
     * 窄脸。强度默认值为 0.0。
     * @endif
     */
    kNERtcBeautyNarrowFace,

    /**
     * @if English
     * Adjusts the cheekbone. The default value of intensity is 0.0.
     * @endif
     * @if Chinese
     * 瘦颧骨。强度默认值为 0.0。
     * @endif
     */
    kNERtcBeautyCheekBone,

    /**
     * @if English
     * Sharpens the face. The default value of intensity is 0.0.
     * @endif
     * @if Chinese
     * 锐化。强度默认值为 0.0。
     * @endif
     */
    kNERtcBeautyFaceSharpen,

    /** 
     * @if English
     * @endif
     * @if Chinese
     * 调整嘴巴宽度。强度默认值为 0.5。
     * @endif
     */
    kNERtcBeautyMouthWider,
    
    /** 
     * @if English
     * @endif
     * @if Chinese
     * 祛抬头纹。强度默认值为 0.0。
     * @endif
     */
    kNERtcBeautyForeheadWrinkles,
    
    /** 
     * @if English
     * @endif
     * @if Chinese
     * 祛黑眼圈。强度默认值为 0.0。
     * @endif
     */
    kNERtcBeautyDarkCircles,
    
    /** 
     * @if English
     * @endif
     * @if Chinese
     * 祛法令纹。强度默认值为 0.0。
     * @endif
     */
    kNERtcBeautySmileLines,
    
    /** 
     * @if English
     * @endif
     * @if Chinese
     * 短脸。强度默认值为 0.0。
     * @endif
     */
    kNERtcBeautyShortFace
} nertc_beauty_effect_type;
/**
 * 空间音效房间大小
 */
typedef enum {
  /**
   * 小房间
   */
  kNERtcSpatializerRoomCapacitySmall = 0,

  /**
   * 中等大小房间
   */
  kNERtcSpatializerRoomCapacityMedium = 1,

  /**
   * 大房间
   */
  kNERtcSpatializerRoomCapacityLarge = 2,

  /**
   * 巨大房间
   */
  kNERtcSpatializerRoomCapacityHuge = 3,

  /**
   * 无房间效果
   */
   kNERtcSpatializerRoomCapacityNone = 4
} nertc_spatializer_room_capacity;
/**
 * 空间音效中房间材质名称
 */
typedef enum {
  /**
   * 透明的
   */
  kNERtcSpatializerMaterialTransparent = 0,
  /**
   * 声学天花板，未开放
   */
  kNERtcSpatializerMaterialAcousticCeilingTiles,
  /**
   * 砖块，未开放
   */
  kNERtcSpatializerMaterialBrickBare,
  /**
   * 涂漆的砖块，未开放
   */
  kNERtcSpatializerMaterialBrickPainted,
  /**
   * 粗糙的混凝土块，未开放
   */
  kNERtcSpatializerMaterialConcreteBlockCoarse,
  /**
   * 涂漆的混凝土块，未开放
   */
  kNERtcSpatializerMaterialConcreteBlockPainted,
  /**
   * 厚重的窗帘
   */
  kNERtcSpatializerMaterialCurtainHeavy,
  /**
   * 隔音的玻璃纤维，未开放
   */
  kNERtcSpatializerMaterialFiberGlassInsulation,
  /**
   * 薄的的玻璃，未开放
   */
  kNERtcSpatializerMaterialGlassThin,
  /**
   * 茂密的草地，未开放
   */
  kNERtcSpatializerMaterialGlassThick,
  /**
   * 草地
   */
  kNERtcSpatializerMaterialGrass,
  /**
   * 铺装了油毡的混凝土，未开放
   */
  kNERtcSpatializerMaterialLinoleumOnConcrete,
  /**
   * 大理石
   */
  kNERtcSpatializerMaterialMarble,
  /**
   * 金属，未开放
   */
  kNERtcSpatializerMaterialMetal,
  /**
   * 镶嵌木板的混凝土，未开放
   */
  kNERtcSpatializerMaterialParquetOnConcrete,
  /**
   * 石膏，未开放
   */
  kNERtcSpatializerMaterialPlasterRough,
  /**
   * 粗糙石膏，未开放
   */
  kNERtcSpatializerMaterialPlasterSmooth,
  /**
   * 光滑石膏，未开放
   */
  kNERtcSpatializerMaterialPlywoodPanel,
  /**
   * 木板，未开放
   */
  kNERtcSpatializerMaterialPolishedConcreteOrTile,
  /**
   * 石膏灰胶纸板，未开放
   */
  kNERtcSpatializerMaterialSheetrock,
  /**
   * 水面或者冰面，未开放
   */
  kNERtcSpatializerMaterialWaterOrIceSurface,
  /**
   * 木头天花板，未开放
   */
  kNERtcSpatializerMaterialWoodCeiling,
  /**
   * 木头枪板，未开放
   */
  kNERtcSpatializerMaterialWoodPanel,
  /**
   * 均匀分布，未开放
   */
  kNERtcSpatializerMaterialUniform
} nertc_spatializer_material_name;

/**
 * 空间音效渲染模式
 */
typedef enum {
  /**
   * 立体声 panning
   */
  kNERtcSpatializerRenderStereoPanning = 0,
  /**
   * 低复杂度双耳渲染(Binaural)
   */
  kNERtcSpatializerRenderBinauralLowQuality,
  /**
   * 中复杂度双耳渲染(Binaural)
   */
  kNERtcSpatializerRenderBinauralMediumQuality,
  /**
   * 高复杂度双耳渲染(Binaural)
   */
  kNERtcSpatializerRenderBinauralHighQuality,
  /**
   * 仅房间音效
   */
  kNERtcSpatializerRenderRoomEffectsOnly
} nertc_spatializer_render_mode;

/**
 * 空间音效衰减模式
 */
typedef enum {
  /**
   * 指数衰减模式
   */
  kNERtcDistanceRolloffLogarithmic = 0,
  /**
   * 线性衰减模式
   */
  kNERtcDistanceRolloffLinear,
  /**
   * 无衰减
   */
  kNERtcDistanceRolloffNone,
} nertc_distance_rolloff_model;

/** 3D音效算法中坐标信息。*/
struct nertc_position_info {
  /**
   发声坐标，三个值分别表示x-左右，y-上下，z-前后
   */
  float speaker_position[3];
  /**
   发声旋转角度四元数,设置为0
   */
  float speaker_quaternion[4];
  /**
   头部听觉坐标，三个值分别表示x-左右，y-上下，z-前后
   */
  float head_position[3];
  /**
   头部听觉旋转方向，表示头部的朝向，四元组格式
   */
  float head_quaternion[4];
};

/** 3D音效房间属性设置。*/
struct nertc_spatializer_room_property {
  /**
   * 房间大小 #NERtcSpatializerRoomCapacity ，默认值 #kNERtcSpatializerRoomCapacitySmall
   */
  nertc_spatializer_room_capacity room_capacity;
  /**
   * 房间材质 #NERtcSpatializerMaterialName ，默认值 #kNERtcSpatializerMaterialTransparent
   */
  nertc_spatializer_material_name material;
  /**
   * 反射系数的比例因子，默认值1.0, 取值范围[1.0 30]
   */
  float reflection_scalar;
  /**
   * 混响增益比例因子，默认值1.0, 取值范围[1.0 10]
   */
  float reverb_gain;
  /**
   * 混响时间比例因子，RT60会和该值相乘，默认值1.0(无效果), 取值范围[1.0 30]
   */
  float reverb_time;
  /**
   * 混响亮度，该值为正且增加时，增加高频成分，该值为负数时衰减高频成分，默认值0.0(无效果), 取值范围[-30 30]
   */
  float reverb_brightness;
};


/**
 * @if English
 * Configure the SDK using a JSON file to provide technical preview or special custom functionalities. Standardize JSON options.
 * For more information, see setParameters. *
 * @endif
 * @if Chinese
 * 通过 JSON 配置 SDK 提供技术预览或特别定制功能。以标准化方式公开 JSON 选项。详见 API setParameters。
 * @endif
 */
/**
 * @if English
 * bool value. True: Record the presenter. False: Do not record the presenter. The setting is valid before the call.
 * @endif
 * @if Chinese
 * bool value. true: 录制主讲人, false: 不是录制主讲人。通话前设置有效。
 * @endif
 */
#define kNERtcKeyRecordHostEnabled "record_host_enabled"
/**
 * @if English
 * bool value, which determines whether to enable server audio recording. The default value is false. The setting is valid
 * before the call.
 * @endif
 * @if Chinese
 * bool value，启用服务器音频录制。默认值 false。通话前设置有效。
 * @endif
 */
#define kNERtcKeyRecordAudioEnabled "record_audio_enabled"
/**
 * @if English
 * bool value, which determines whether to enable server video recording. The default value is false. The setting is valid
 * before the call.
 * @endif
 * @if Chinese
 * bool value，启用服务器视频录制。默认值 false。通话前设置有效。
 * @endif
 */
#define kNERtcKeyRecordVideoEnabled "record_video_enabled"
/**
 * @if English
 * int value, NERtcRecordType. The setting is valid before the call.
 * @endif
 * @if Chinese
 * int value, NERtcRecordType。通话前设置有效。
 * @endif
 */
#define kNERtcKeyRecordType "record_type"
/**
 * @if English
 * bool value, which determines whether to automatically subscribe to the audio stream when other users open the audio. The
 * default value is true. The setting is valid before the call.
 * @endif
 * @if Chinese
 * bool value，其他用户打开音频时，自动订阅。默认值 true。通话前设置有效。
 * @endif
 */
#define kNERtcKeyAutoSubscribeAudio "auto_subscribe_audio"
/**
 * @if English
 * bool value, which determines whether to manually subscribe to the audio stream when other users open the audio on ASL mode. The
 * default value is false. The setting is valid before the call.
 * @endif
 * @if Chinese
 * bool value，在ASL模式下手动订阅音频。默认值 false。通话前设置有效。
 * @endif
 */
#define kNERtcKeyEnableAudioASLManualSubscribe "enable_audio_asl_manual_subscribe"
/**
 * @if English
 * bool value, which determines whether to enable CDN relayed streaming. The default value is true. The setting is valid before
 * the call.
 * @endif
 * @if Chinese
 * bool value，开启旁路直播。默认值 false。通话前设置有效。
 * @endif
 */
#define kNERtcKeyPublishSelfStreamEnabled "publish_self_stream_enabled"
/**
 * @if English
 * int value, NERtcLogLevel, SDK outputs logs that are of less than or equal to this level. The default is kNERtcLogLevelInfo.
 * @endif
 * @if Chinese
 * int value, NERtcLogLevel，SDK 输出小于或等于该级别的 log，默认为 kNERtcLogLevelInfo。
 * @endif
 */
#define kNERtcKeyLogLevel "log_level"
/**
 * @if English
 * bool value. Disable or enable AEC. The default value is true.
 * @endif
 * @if Chinese
 * bool value. AEC 开关，默认值 true。
 * @endif
 */
#define kNERtcKeyAudioProcessingAECEnable "audio_processing_aec_enable"
/**
 * @if English
 * bool value. Enable or disable low level AEC. The default value is false, The option takes effect only of
 * kNERtcKeyAudioProcessingAECEnable is enabled.
 * @endif
 * @if Chinese
 * bool value. low level AEC 开关，默认值 false，需要 kNERtcKeyAudioProcessingAECEnable 打开才生效。
 * @endif
 */
#define kNERtcKeyAudioAECLowLevelEnable "audio_aec_low_level_enable"
/**
 * @if English
 * bool value. Enable or disable AGC. The default value is true.
 * @endif
 * @if Chinese
 * bool value. AGC 开关，默认值 true。
 * @endif
 */
#define kNERtcKeyAudioProcessingAGCEnable "audio_processing_agc_enable"
/**
 * @if English
 * bool value. Enable or disable NS. The default value is true.
 * @endif
 * @if Chinese
 * bool value. NS 开关，默认值 true。
 * @endif
 */
#define kNERtcKeyAudioProcessingNSEnable "audio_processing_ns_enable"
/**
 * @if English
 * bool value. Enable or disable AI NS. We recommend that you modify this option before calls. The default value is false.
 * @endif
 * @if Chinese
 * bool value. AI NS 开关，建议通话前修改，默认值 false。
 * @endif
 */
#define kNERtcKeyAudioProcessingAINSEnable "audio_processing_ai_ns_enable"
/**
 * @if English
 * bool value. Enable or disable the audio mixing. The default value is false.
 * @endif
 * @if Chinese
 * bool value. 输入混音开关，默认值 false。
 * @endif
 */
#define kNERtcKeyAudioProcessingExternalAudioMixEnable "audio_processing_external_audiomix_enable"
/**
 * @if English
 * bool value, which determines whether to use an earphone. true: uses an earphone. false: does not use an earphone. The default
 * value is false.
 * @endif
 * @if Chinese
 * bool value. 通知 SDK 是否使用耳机， true: 使用耳机, false: 不使用耳机，默认值 false。
 * @endif
 */
#define kNERtcKeyAudioProcessingEarphone "audio_processing_earphone"
/**
 * @if English
 * int value. NERtcSendOnPubType. Sets the video sending strategy, and sends the mainstream by calling kNERtcSendOnPubHigh by
 * default. The setting is valid before the call.
 * @endif
 * @if Chinese
 * int value. NERtcSendOnPubType；设置视频发送策略，默认发送大流 kNERtcSendOnPubHigh。通话前设置有效。
 * @endif
 */
#define kNERtcKeyVideoSendOnPubType "video_sendonpub_type"
/**
 * @if English
 * bool value. Enable or disable the 1v1 mode. The default value is disabled. The setting is valid before the call.
 * @endif
 * @if Chinese
 * bool value. 1v1 模式开关，默认关闭。通话前设置有效。
 * @endif
 */
#define kNERtcKeyChannel1V1ModeEnabled "channel_1v1_mode_enabled"
/**
 * @if English
 * string value. APP identification, used to identify the user's product name.
 * @endif
 * @if Chinese
 * string value. APP 标识，用于后台识别用户产品名称。
 * @endif
 */
#define kNERtcKeyExtraInfo "extra_info"
/**
 * @if English
 * int value. Automatic audio device selection policy. The default value is 0.
 * - 0: Default device priority
 * - 1: Available device priority
 * @endif
 * @if Chinese
 * 音频设备自动选择策略。int 类型。默认值为 0。
 * - 0：优先选择默认设备。
 * - 1：优先选择可用设备。
 * @endif
 */
#define kNERtcKeyAudioDeviceAutoSelectType "audio_device_auto_select_type"
/**
 * @if English
 * Whether to return original volume when the local user is muted.  Boolean value, default: false.
 * - true：Return the original volume in `onLocalAudioVolumeIndication`.
 * - false：Return the recording volume(0) in `onLocalAudioVolumeIndication`.
 * @endif
 * @if Chinese
 * 本地用户静音时是否返回原始音量。 布尔值，默认值为 false。
 * - true：返回 `onLocalAudioVolumeIndication` 中的原始音量。
 * - false：返回 `onLocalAudioVolumeIndication` 中的录音音量，静音时为 0。
 * @endif
 */
#define kNERtcKeyEnableReportVolumeWhenMute "enable_report_volume_when_mute"
/**
 * @if English
 *  BOOL - Specifies whether to enable the callback to return captured video data. This enables developers to get the raw video
 * data. You can clear the video data by calling destroyEngine. The default value is NO.
 * @endif
 * @if Chinese
 * 是否需要开启视频数据采集回调，开启后开发者可以获取到原始视频数据。
 * <br>布尔值，默认值 NO。
 * <br>开启后如果需要关闭，需要通过调用 destroyEngine 来清除。
 * @endif
 */
#define kNERtcKeyEnableVideoCaptureObserver "enable_video_capture_observer"
/**
 * @if English
 *  BOOL - Specifies whether to prefer using hardware to encode video data. The default value is YES. We recommend that you set
 * this value before you call setupEngineWithContext to initialize the INERtcEngine instance. Otherwise, the setting is applied
 * the next time.
 * @endif
 * @if Chinese
 * 是否优先使用硬件编码视频数据。
 * <br>布尔值，默认值 YES。
 * <br>请在初始化（setupEngineWithContext）之前设置该参数，否则该参数会在下次初始化之后生效。
 * @endif
 */
#define kNERtcKeyVideoPreferHWEncode "video_prefer_hw_encode"
/**
 * @if English
 *  BOOL - Specifies whether to prefer using hardware to decode video data. The default value is true. We recommend that you set
 * this value before you call setupEngineWithContext to initialize the INERtcEngine instance. Otherwise, the setting is applied
 * the next time.
 * @endif
 * @if Chinese
 * 是否优先使用硬件解码视频数据。
 * <br>布尔值，默认值 true。
 * <br>请在初始化（setupEngineWithContext）之前设置该参数，否则该参数会在下次初始化之后生效。
 * @endif
 */
#define kNERtcKeyVideoPreferHWDecode "video_prefer_hw_decode"

/**
 * 是否使用动态token加入通话。 布尔值，默认值为 false。
 * @note 默认不使用动态token，该功能需要在通话前调用
 * - true：使用动态token。
 * - false：不使用动态token。
 */
#define kNERtcKeyEnableDynamicToken "enable_dynamic_token"
/**
 * @if English
 *  BOOL - Specifies whether to turn on the rear camera if the camera is enabled for the first time. The default value is false.
 * It's available only on iOS platform.
 * @endif
 * @if Chinese
 * 第一次开启摄像头时，是否使用后摄像头。仅iOS平台有效。
 * <br>布尔值，默认值 false，即不使用后置摄像头。
 * @endif
 */
#define kNERtcKeyVideoStartWithBackCamera "video_start_with_back_camera"
/**
 * @if English
 *  BOOL - Specifies whether to use metal rendering first. Otherwise, OpenGL rendering is applied. The default value is
 * false. It's available only on iOS platform.
 * @endif
 * @if Chinese
 * 是否优先使用 Metal 渲染。
 * <br>布尔值，默认值 false，即使用OpenGL 渲染。仅iOS平台有效。
 * @endif
 */
#define kNERtcKeyVideoPreferMetalRender "video_prefer_metal_render"
/**
 * @if English
 * BOOL -- Specifies whether to disable switching to the speakerphone when the system switches to the earpieces. The
 * default value is false. If the value is set to true, the SDK is not allowed to switch to the speakerphone when the system
 * switches to earpieces. Users need to handle the earpieces switching event.It's available only on iOS platform.
 * @endif
 * @if Chinese
 * 当系统切换听筒或扬声器时，SDK 是否以系统设置为准。仅iOS平台有效。
 * <br>布尔值，默认为 false。
 * - true： 以系统设置为准。例如当系统切换为听筒时，应用的音频播放则自动转为听筒，开发者需要自行处理该切换事件。
 * - false： 以 SDK 设置为准，SDK 不允许用户通过系统变更音频播放路由为听筒或扬声器。例如当 SDK
 * 设置为扬声器时，即使系统切换为听筒模式，SDK 也会自动将系统修改回扬声器模式。
 * @endif
 */
#define kNERtcKeyDisableOverrideSpeakerOnReceiver "disable_override_speaker_on_receiver"
/**
 * @if English
 * BOOL - Specifies whether to use echo reduction when the system sets the headset. The default value is false. If the value is
 * set to YES, the SDK does not use the echo reduction in headset mode. The setting affects the audio quality of the headset
 * in some mobile models.It's available only on iOS platform.
 * @endif
 * @if Chinese
 * 设置耳机时不使用软件回声消除功能，默认值 false。如设置YES 则SDK在耳机模式下不使用软件回声消除功能，会对某些机型下
 * 耳机的音质效果有影响。仅iOS平台有效。
 * @endif
 */
#define kNERtcKeyDisableSWAECOnHeadset "disable_sw_aec_on_headset"
/**
 * @if English
 * Whether to enable bluetooth SCO.The default value is true.It's available only on Android platform.
 * @endif
 * @if Chinese
 * 是否关闭蓝牙SCO.默认打开。仅Android平台有效。
 * @endif
 */
#define kNERtcKeyEnableAudioBluetoothSCO "enable_audio_bluetooth_sco"
/**
 * @if English
 * Whether to preview the front camera with mirror mode. Default: true. The setting enables the mirror mode.It's available only
 * on Android platform.
 * @endif
 * @if Chinese
 * 前置摄像头预览是否采用镜像模式。默认为 true，开启镜像模式。仅Android平台有效。
 * @endif
 */
#define kNERtcKeyEnableVideoMirrorWithFrontCamera "enable_video_mirror_with_front_camera"
/**
 * @if English
 * Video camera type.The default value is 1.It's available only on Android platform.
 * @endif
 * @if Chinese
 * 摄像头类型。默认值为1.取值范围为0(unknown), 1, 2.仅Android平台有效。
 * @endif
 */
#define kNERtcKeyVideoCameraType "video_camera_type"

/**
 * @if English
 * Returns a bitmap file path when you take snapshot.The default value is false.
 * @endif
 * @if Chinese
 * 调用TakeSnapshot截图时返回图片文件路径。默认值为false。
 * @endif
 */
#define kNERtcKeyEnableSnapshotWithFile "enable_snapshot_with_file"

/**
* @if English
* Specifies whether to automatically subscribe to video streams when other users turn on video.
* The default value is NO.
* @note
* You can change the subscription stautus. Local subscription status will not be affected if remote users resume
sending the video stream; but local settings will resume to be default if remote users rejoin the room.
* This method is only valid for windows.
* The setting is applied before you make a call. The setting is invalid if you specify the value during the call.
* @endif
* @if Chinese
* 是否订阅其他用户的视频流。
* <br>布尔值，默认值为 false。
* @note
- 订阅状态可以更改。远端用户重新发布推流视频，不影响本地用户的订阅状态；但远端用户退出房间重进后，本地恢复默认设置。
- 该接口仅 windows 下有效。
- 请在加入房间前设置该参数，通话中设置无效。
* @endif
*/
#define kNERtcKeyAutoSubscribeVideo "auto_subscribe_video"

/**
* @if English
*  BOOL - Specifies whether to automatically subscribe to data channel when other users turn on data channel. The setting is
* applied before you make a call. The setting is invalid If you specify the value during the call. The default value is NO.
* Note: The key of subscribeRemoteData must be set to NO if you use the method to control the data in your business.
* @endif
* @if Chinese
* 是否自动订阅其他用户的数据通道。
* <br>布尔值，默认为 NO，即非自动订阅。
* @note
* - 请在加入房间前设置该参数，通话中设置无效。
* - 如果业务场景中使用 subscribeData 控制数据订阅，则该 Key 必须设置为 NO。
* @endif
*/
#define kNERtcKeyAutoSubscribeData "auto_subscribe_data"

/**
* @if English
* Specifies whether to disable video decoder, the default value is false.
* When disable video decoder (true), the SDK will not decode the remote video and therefore will not render the received remote
* video. This parameter must be set before IRtcEngine::initialize and becomes invalid after the SDK is released. Usually used
* with IRtcEngineEx::setPreDecodeObserver.
* @since 4.6.25
* @endif
* @if Chinese
* 指定是否关闭视频解码器，默认不关闭（false）。
* 关闭（true）后 SDK 将不会解码远端视频，因此也不会渲染接收到的远端视频。
* 需要在初始化 IRtcEngine::initialize 前设置，释放 SDK 后失效。
* 一般配合 IRtcEngineEx::setPreDecodeObserver 使用。
* @since 4.6.25
* @endif
*/
#define kNERtcKeyDisableVideoDecoder "disable_video_decoder"

/**
* @if Chinese
* 切换SDK内部渲染模式
* <br>int，默认值0。
* - 0：选择默认渲染(win:d3d,Mac:metal)。
* - 1：Mac下使用OpenGL。
* - 2：Mac下使用Metal。
* - 3：windows下使用SDL2。
* @endif
*/
#define kNERtcKeyVideoRenderType "sdk.prefer.video.render"

/** 音频设备错误码。*/
typedef enum{
  kNERtcAudioDeviceNoError = 0, 
  kNERtcAudioDeviceErrorInitRecording, 
  kNERtcAudioDeviceErrorStartRecording,
  kNERtcAudioDeviceErrorStopRecording,
  kNERtcAudioDeviceErrorInitPlayout,
  kNERtcAudioDeviceErrorStartPlayout,
  kNERtcAudioDeviceErrorStopplayout,
  kNERtcAudioDeviceErrorCaptureThreadStop,
  kNERtcAudioDeviceErrorPlayoutThreadStop,
  kNERtcAudioDeviceErrorCaptureSampleRate,
  kNERtcAudioDeviceErrorPlayoutSampleRate,
  kNERtcAudioDeviceErrorConfigSession,
  kNERtcAudioDeviceErrorCodeReporter
}nertc_audio_device_error;

/** 视频设备错误码。*/
typedef enum {
  kNERtcVideoDeviceErrorNoFrame = 0,
  kNERtcVideoDeviceErrorNotAvailableInBackground,
  kNERtcVideoDeviceErrorUsingByAnotherClient,
  kNERtcVideoDeviceErrorNotAvailableWithMultipleForegroundApps,
} nertc_video_device_error;

/** 音频路由 仅iOS和Android有效*/
typedef enum {
  /**
   * @if English
   * Default
   * @endif
   * @if Chinese
   * 系统默认
   * @endif
   */
  kNERtcAudioOutputRoutingDefault = 0,
  /**
   * @if English
   * Headset
   * @endif
   * @if Chinese
   * 耳机
   * @endif
   */
  kNERtcAudioOutputRoutingHeadset,
  /**
   * @if English
   * Earpiece
   * @endif
   * @if Chinese
   * 听筒
   * @endif
   */
  kNERtcAudioOutputRoutingEarpiece,
  /**
   * @if English
   * Loudspeaker
   * @endif
   * @if Chinese
   * 扬声器
   * @endif
   */
  kNERtcAudioOutputRoutingLoudspeaker,
  /**
   * @if English
   * Bluetooth
   * @endif
   * @if Chinese
   * 蓝牙外设
   * @endif
   */
  kNERtcAudioOutputRoutingBluetooth,
} nertc_audio_output_routing;

/** 网络类型 */
typedef enum {
  kNERtcNetworkTypeUnknown = 0,
  kNERtcNetworkTypeEthernet,
  kNERtcNetworkTypeWifi,
  kNERtcNetworkType2G,
  kNERtcNetworkType3G,
  kNERtcNetworkType4G,
  kNERtcNetworkType5G,
  kNERtcNetworkTypeWWAN,
  kNERtcNetworkTypeBluetooth,
  kNERtcNetworkTypeNone
} nertc_network_type;

struct nertc_camera_focus_and_exposure_info {
  float center_x;
  float center_y;
  int32_t left;
  int32_t top;
  int32_t right;
  int32_t bottom;
};
/**
 * @if English
 * Audio session control permissions
 * <br>The SDK has the permissions of Audio Session.
 * @endif
 * @if Chinese
 * 音频会话控制权限。
 * <br>SDK 对 Audio Session 的控制权限。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * The SDK has full permissions and can control the Audio Session
   * @endif
   * @if Chinese
   * 没有限制，SDK 可以完全控制 Audio Session 操作。
   * @endif
   */
  kNERtcAudioSessionOperationRestrictionNone = 0,
  /**
   * @if English
   * If you restrict the SDK to perform operations on the Audio Session, the SDK cannot configure the Audio Session
   * @endif
   * @if Chinese
   * 限制 SDK 对 Audio Session 进行任何操作，SDK 将不能再对 Audio Session 进行任何配置。
   * @endif
   */
  kNERtcAudioSessionOperationRestrictionAll,
  /**
   * @if English
   * When a user leaves the room, the SDK will keep the Audio Session active.
   * @endif
   * @if Chinese
   * 离开房间时，SDK 会保持 Audio Session 处于活动状态。
   * @endif
   */
  kNERtcAudioSessionOperationRestrictionDeactivateSession,
} nertc_audio_session_operation_restriction;

/**
 * @if English
 * Audio focus mode（Android only）.
 * @endif
 * @if Chinese
 * 音频焦点模式（Android only）。
 * @endif
 */
typedef enum {
  /**
   * @if English
   * No request for audio focus.
   * @endif
   * @if Chinese
   * 不请求音频焦点。
   * @endif
   */
  kNERtcAudioFocusOff = 0,
  /**
   * @if English
   * Gains the audio focus in a long period.
   * @endif
   * @if Chinese
   * 长时间获得焦点。
   * @endif
   */
  kNERtcAudioFocusGain = 1,

  /**
   * @if English
   * Gains transient audio focus. Release the focus after losing it. Such as notification sounds.
   * @endif
   * @if Chinese
   * 短暂性获得焦点，用完应立即释放，比如notification sounds。
   * @endif
   */
  kNERtcAudioFocusGainTransient = 2,

  /**
   * @if English
   * Temporary requests for lowering the volume of other audio applications. Mixable playback is supportable.
   * @endif
   * @if Chinese
   * 临时请求, 降低其他音频应用的声音，可混音播放。
   * @endif
   */
  kNERtcAudioFocusGainTransientMayDuck = 3,

  /**
   * @if English
   * Gains transient audio focus to enable recording or audio recognition.
   * @endif
   * @if Chinese
   * 短暂性获得焦点，录音或者语音识别。
   * @endif
   */
  kNERtcAudioFocusGainTransientExclisive = 4,
}nertc_audio_focus_mode;

/**
* @if English
* Position of a specified camera.
* @endif
* @if Chinese
* 指定的摄像头位置。
* @endif
*/
typedef enum {
  /**
   * @if English
   * Front camera.
   * @endif
   * @if Chinese
   * 前置摄像头。
   * @endif
   */
  kNERtcCameraPositionBack = 0,

  /**
   * @if English
   * Rear camera.
   * @endif
   * @if Chinese
   * 后置摄像头。
   * @endif
   */
  kNERtcCameraPositionFront
}nertc_camera_position;

/**
 * @if Chinese
 * 二维坐标点。
 * @endif
 */
struct nertc_point {
  /**
   * @if Chinese
   * x 轴坐标。
   * @endif
   */
  float x;
  /**
   * @if Chinese
   * y轴坐标值。
   * @endif
   */
  float y;
};
/**
 * @if English
 * Video correction configuration
 * @endif
 * @if Chinese
 * 视频图像畸变矫正相关设置。
 * @endif
 */
struct nertc_video_correction_configuration {
  /**
   * @if Chinese
   * 矫正区域的左上顶点（x 和 y 的取值范围为 0 ~ 1 的浮点数）
   * @endif
   */
  nertc_point top_left;
  /**
   * @if Chinese
   * 矫正区域的右上顶点（x 和 y 的取值范围为 0 ~ 1 的浮点数）
   * @endif
   */
  nertc_point top_right;
  /**
   * @if Chinese
   * 矫正区域的左下顶点（x 和 y 的取值范围为 0 ~ 1 的浮点数）
   * @endif
   */
  nertc_point bottom_left;
  /**
   * @if Chinese
   * 矫正区域的右下顶点（x 和 y 的取值范围为 0 ~ 1 的浮点数）
   * @endif
   */
  nertc_point bottom_right;
  /**
   * @if Chinese
   * 画布宽度（单位 px，使用外部视频渲染时需要传递）
   * @endif
   */
  float canvas_width;
  /**
   * @if Chinese
   * 画布高度（单位 px，使用外部视频渲染时需要传递）
   * @endif
   */
  float canvas_height;
  /**
   * @if Chinese
   * 是否镜像显示（使用外部视频渲染时需要传递）
   * @endif
   */
  bool enable_mirror;
};
#endif  // NERTC_DEFINES_H
