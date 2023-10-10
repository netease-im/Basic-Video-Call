/** @file nertc_engine_media_stats_observer.h
 * @brief The interface header file of expansion callback of the NERTC SDK.
 * All parameter descriptions of the NERTC SDK. All string-related parameters (char *) are encoded in UTF-8.
 * @copyright (c) 2021, NetEase Inc. All rights reserved.
 */
#pragma once
#include "NertcEngineDefines.h"

/**
 * @namespace nertc
 * @brief namespace nertc
 */
namespace nertc {
/**
 * @if English
 * The SDK reports stats to the application through IRtcMediaStatsObserver expansion callback interface class.
 * <br>All methods in this interface class have their (empty) default implementations, and the application can inherit only some
 * of the required events instead of all of them. When calling a callback method, the application must not implement
 * time-consuming operations or call blocking-triggered APIs. For example, if you want to enable audio and video, the SDK may be
 * affected in the runtime.
 * @endif
 * @if Chinese
 * IRtcMediaStatsObserver 回调扩展接口类用于 SDK 向 App 上报统计信息。
 * <br>接口类的所有方法都有缺省（空）实现，App 可以根据需要只继承关心的事件。在回调方法中，App
 * 不应该做耗时或者调用可能会引起阻塞的 API（如开启音频或视频等），否则可能影响 SDK 的运行。
 * @endif
 */
class IRtcMediaStatsObserver {
 public:
  virtual ~IRtcMediaStatsObserver() {}

    /**
     * 当前通话统计回调。
     * SDK 定期向 App 报告当前通话的统计信息，每 2 秒触发一次。
     *
     * @param stats NERTC 引擎统计数据: nertc_stats
     */
  virtual void onRtcStats(const NERtcStats& stats) { (void)stats; }

    /**
     * 本地音频流统计信息回调。
     * 该回调描述本地设备发送音频流的统计信息，每 2 秒触发一次。
     *
     * @param stats 本地音频流统计信息。详见 nertc_audio_send_stats.
     */
  virtual void onLocalAudioStats(const NERtcAudioSendStats& stats) { (void)stats; }

    /**
     * 通话中远端音频流的统计信息回调。
     * 该回调描述远端用户在通话中端到端的音频流统计信息，每 2 秒触发一次。
     *
     * @param stats 每个远端用户音频统计信息的数组。详见 nertc_audio_recv_stats.
     * @param user_count stats 数组的大小。
     */
  virtual void onRemoteAudioStats(const NERtcAudioRecvStats* stats, unsigned int user_count) {
    (void)stats;
    (void)user_count;
  }

    /**
     * 本地视频流统计信息回调。
     *
     * 该回调描述本地设备发送视频流的统计信息，每 2 秒触发一次。
     *
     * @param stats 本地视频流统计信息。详见 nertc_video_send_stats.
     */
  virtual void onLocalVideoStats(const NERtcVideoSendStats& stats) { (void)stats; }

    /**
     * 通话中远端视频流的统计信息回调。
     *
     * 该回调描述远端用户在通话中端到端的视频流统计信息，每 2 秒触发一次。
     *
     * @param stats 每个远端用户视频统计信息的数组。详见 nertc_video_recv_stats.
     * @param user_count stats 数组的大小。
     */
  virtual void onRemoteVideoStats(const NERtcVideoRecvStats* stats, unsigned int user_count) {
    (void)stats;
    (void)user_count;
  }

    /**
     * 通话中每个用户的网络上下行质量报告回调。
     *
     * 该回调描述每个用户在通话中的网络状态，每 2 秒触发一次，只上报状态有变更的成员。
     *
     * @param infos 每个用户 ID 和网络上下行质量信息的数组: nertc_network_quality_info
     * @param user_count infos 数组的大小，即用户数。
     */
  virtual void onNetworkQuality(const NERtcNetworkQualityInfo* infos, unsigned int user_count) {
    (void)infos;
    (void)user_count;
  }
};
}  // namespace nertc
