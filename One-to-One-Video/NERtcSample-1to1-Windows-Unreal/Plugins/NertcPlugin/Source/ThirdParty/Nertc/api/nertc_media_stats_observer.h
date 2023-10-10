#ifndef NERTC_MEDIA_STATS_OBSERVER_H
#define NERTC_MEDIA_STATS_OBSERVER_H

#include "nertc_engine_defines.h"

struct nertc_media_stats_observer {
    void *self;

    /**
     * 当前通话统计回调。
     * SDK 定期向 App 报告当前通话的统计信息，每 2 秒触发一次。
     *
     * @param stats NERTC 引擎统计数据: nertc_stats
     */
    void (NERTC_CALL *on_rtc_stats)(void *self, const struct nertc_stats *stats);

    /**
     * 本地音频流统计信息回调。
     * 该回调描述本地设备发送音频流的统计信息，每 2 秒触发一次。
     *
     * @param stats 本地音频流统计信息。详见 nertc_audio_send_stats.
     */
    void (NERTC_CALL *on_local_audio_stats)(void *self, const struct nertc_audio_send_stats *stats);

    /**
     * 通话中远端音频流的统计信息回调。
     * 该回调描述远端用户在通话中端到端的音频流统计信息，每 2 秒触发一次。
     *
     * @param stats 每个远端用户音频统计信息的数组。详见 nertc_audio_recv_stats.
     * @param user_count stats 数组的大小。
     */
    void (NERTC_CALL *on_remote_audio_stats)(void *self, const struct nertc_audio_recv_stats *stats, unsigned int user_count);

    /**
     * 本地视频流统计信息回调。
     *
     * 该回调描述本地设备发送视频流的统计信息，每 2 秒触发一次。
     *
     * @param stats 本地视频流统计信息。详见 nertc_video_send_stats.
     */
    void (NERTC_CALL *on_local_video_stats)(void *self, const struct nertc_video_send_stats *stats);

    /**
     * 通话中远端视频流的统计信息回调。
     *
     * 该回调描述远端用户在通话中端到端的视频流统计信息，每 2 秒触发一次。
     *
     * @param stats 每个远端用户视频统计信息的数组。详见 nertc_video_recv_stats.
     * @param user_count stats 数组的大小。
     */
    void (NERTC_CALL *on_remote_video_stats)(void *self, const struct nertc_video_recv_stats *stats, unsigned int user_count);

    /**
     * 通话中每个用户的网络上下行质量报告回调。
     *
     * 该回调描述每个用户在通话中的网络状态，每 2 秒触发一次，只上报状态有变更的成员。
     *
     * @param infos 每个用户 ID 和网络上下行质量信息的数组: nertc_network_quality_info
     * @param user_count infos 数组的大小，即用户数。
     */
    void (NERTC_CALL *on_network_quality)(void *self, const struct nertc_network_quality_info *infos, unsigned int user_count);
};

#endif //NERTC_MEDIA_STATS_OBSERVER_H
