/** @file nertc_engine_video_encoder_qos_observer.h
* @brief The interface header file of expansion callback of the NERTC SDK.
* All parameter descriptions of the NERTC SDK. All string-related parameters (char *) are encoded in UTF-8.
* @copyright (c) 2022, NetEase Inc. All rights reserved.
*/

#ifndef NERTC_ENGINE_VIDEO_ENCODER_QOS_OBSERVER_H
#define NERTC_ENGINE_VIDEO_ENCODER_QOS_OBSERVER_H

#include "nertc_engine_defines.h"

/** 
 * @if English
 * The SDK reports video encoder qos to the application through INERtcVideoEncoderQosObserver expansion callback interface class.
 * @endif
 * @if Chinese
 * INERtcVideoEncoderQosObserver 回调扩展接口类用于 SDK 向 App 上报视频编码qos信息。
 * @endif
 */
struct nertc_video_encoder_qos_observer { 
    void* self;
    /** 
    * @if English
    * The video I frame request callback.
    * @param frame The video stream type.
    * @endif
    * @if Chinese
    * I 帧请求事件回调。
    * - 调用 \ref IRtcEngineEx::setVideoEncoderQosObserver "setVideoEncoderQosObserver" 方法注册解码前媒体数据观测器后，SDK 可能会在推送外部视频编码帧后触发该回调，此时请及时发送相应的 IDR 帧，否则对端无法渲染视频画面。
    * @since V4.6.29
    * @par 使用前提
    * 请在 INERtcVideoEncoderQosObserver 接口类中通过 \ref IRtcEngineEx::setVideoEncoderQosObserver "setVideoEncoderQosObserver" 接口设置回调监听。
    * @par 参数说明
    * <table>
    *  <tr>
    *      <th>**参数名称**</th>
    *      <th>**类型**</th>
    *      <th>**描述**</th>
    *  </tr>
    *  <tr>
    *      <td>video_stream_type</td>
    *      <td> \ref nertc::NERtcVideoStreamType "NERtcVideoStreamType"</td>
    *      <td>视频通道类型：<ul><li>kNERtcVideoStreamMain：主流。<li>kNERtcVideoStreamSub：辅流。</td>
    *  </tr>
    * </table>  
    * @endif
    */
    void (NERTC_CALL *on_request_send_key_frame)(void* self, nertc_video_stream_type stream_type);

    /** 
    * @if English
    * The video bitrate info.
    * @param bitrate_bps The video bitrate. Unit: bps。
    * @param video_stream_type The video stream type.
    * @endif
    * @if Chinese
    * 视频码率信息回调。
    * - 调用 \ref IRtcEngineEx::setVideoEncoderQosObserver "setVideoEncoderQosObserver" 方法注册解码前媒体数据观测器后，SDK 可能会在推送外部视频编码帧后触发该回调，此时可以调整对应的码率，防止出现超编，引发视频异常。
    * @since V4.6.29
    * @par 使用前提
    * 请在 INERtcVideoEncoderQosObserver 接口类中通过 \ref IRtcEngineEx::setVideoEncoderQosObserver "setVideoEncoderQosObserver" 接口设置回调监听。
    * @par 参数说明
    * <table>
    *  <tr>
    *      <th>**参数名称**</th>
    *      <th>**类型**</th>
    *      <th>**描述**</th>
    *  </tr>
    *  <tr>
    *      <td>bitrate_bps</td>
    *      <td> uint32_t</td>
    *      <td>码率。单位为 kbps。</td>
    *  </tr>
    *  <tr>
    *      <td>video_stream_type</td>
    *      <td> \ref nertc::NERtcVideoStreamType "NERtcVideoStreamType"</td>
    *      <td>视频通道类型：<ul><li>kNERtcVideoStreamMain：主流。<li>kNERtcVideoStreamSub：辅流。</td>
    *  </tr>
    * </table>  
    * @endif
    */
    void (NERTC_CALL *on_bitrate_updated)(void* self, uint32_t bps, nertc_video_stream_type stream_type);

    /** 
    * @if English
    * The video codec info callback.
    * @param video_codec_type The video codec type.
    * @param video_stream_type The video stream type.
    * @endif
    * @if Chinese
    * 视频编码器类型信息回调。
    * - 调用 \ref IRtcEngineEx::setVideoEncoderQosObserver "setVideoEncoderQosObserver" 方法注册解码前媒体数据观测器后，SDK 默认会在推送外部视频编码帧后触发一次该回调；后续若编码器类型发生变更时会再次触发此回调，此时请重置您的编码器。
    * @since V4.6.29
    * @par 使用前提
    * 请在 INERtcVideoEncoderQosObserver 接口类中通过 \ref IRtcEngineEx::setVideoEncoderQosObserver "setVideoEncoderQosObserver" 接口设置回调监听。
    * @par 参数说明
    * <table>
    *  <tr>
    *      <th>**参数名称**</th>
    *      <th>**类型**</th>
    *      <th>**描述**</th>
    *  </tr>
    *  <tr>
    *      <td>video_codec_type</td>
    *      <td> \ref nertc::NERtcVideoCodecType "NERtcVideoCodecType"</td>
    *      <td>视频编码器类型：<ul><li>kNERtcVideoCodecTypeH264(3)：H.264 编码器。</td>
    *  </tr>
    *  <tr>
    *      <td>video_stream_type</td>
    *      <td> \ref nertc::NERtcVideoStreamType "NERtcVideoStreamType"</td>
    *      <td>视频通道类型：<ul><li>kNERtcVideoStreamMain：主流。<li>kNERtcVideoStreamSub：辅流。</td>
    *  </tr>
    * </table>  
    * @endif
    */
    void (NERTC_CALL *on_video_codec_updated)(void* self, nertc_video_codec_type codec_type, nertc_video_stream_type stream_type);
};

#endif
