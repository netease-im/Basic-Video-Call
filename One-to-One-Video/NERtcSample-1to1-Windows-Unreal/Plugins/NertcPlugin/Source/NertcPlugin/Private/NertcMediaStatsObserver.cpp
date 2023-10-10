// Copyright Epic Games, Inc. All Rights Reserved.

#include "NertcEngineEx.h"
#include "NertcEngineUtil.h"
#include "Nertc/api/nertc_media_stats_observer.h"
#include <map>

namespace nertc {
    static std::map<void*, IRtcMediaStatsObserver*> g_engine_media_stats_map;
    namespace {
        void on_rtc_stats(void* self, const struct nertc_stats* stats){
            if (g_engine_media_stats_map.find(self) == g_engine_media_stats_map.end())
                return;
            NERtcStats nertc_stats{};
            convertToNertcStruct(*stats, nertc_stats);
            g_engine_media_stats_map[self]->onRtcStats(nertc_stats);
        }
        void on_local_audio_stats(void* self, const struct nertc_audio_send_stats* stats) {
            if (g_engine_media_stats_map.find(self) == g_engine_media_stats_map.end())
                return;
            NERtcAudioSendStats nertc_stats{};
            auto wind_cb = convertToNertcStruct(*stats, nertc_stats);
            g_engine_media_stats_map[self]->onLocalAudioStats(nertc_stats);
            wind_cb();
        }
        void on_remote_audio_stats(void* self, const struct nertc_audio_recv_stats* stats, unsigned int user_count) {
            if (g_engine_media_stats_map.find(self) == g_engine_media_stats_map.end())
                return;
            NERtcAudioRecvStats* nertc_stats;
            auto wind_cb = convertToNertcStruct(stats, user_count, nertc_stats);
            
            g_engine_media_stats_map[self]->onRemoteAudioStats(nertc_stats, user_count);
            wind_cb();
        }
        void on_local_video_stats(void* self, const struct nertc_video_send_stats* stats) {
            if (g_engine_media_stats_map.find(self) == g_engine_media_stats_map.end())
                return;
            NERtcVideoSendStats nertc_stats{};
            auto wind_up_cb = convertToNertcStruct(*stats, nertc_stats);
            g_engine_media_stats_map[self]->onLocalVideoStats(nertc_stats);
            wind_up_cb();
        }
        void on_remote_video_stats(void* self, const struct nertc_video_recv_stats* stats, unsigned int user_count) {
            if (g_engine_media_stats_map.find(self) == g_engine_media_stats_map.end())
                return;

            NERtcVideoRecvStats* nertc_stats{};
            auto wind_up_cb = convertToNertcStruct(stats, user_count, nertc_stats);
            g_engine_media_stats_map[self]->onRemoteVideoStats(nertc_stats, user_count);
            wind_up_cb();
        }
        void on_network_quality(void* self, const struct nertc_network_quality_info* infos, unsigned int user_count) {
            if (g_engine_media_stats_map.find(self) == g_engine_media_stats_map.end())
                return;
            NERtcNetworkQualityInfo* nertc_infos = new NERtcNetworkQualityInfo[user_count];
            for (unsigned int i = 0; i < user_count; i++) {
                convertToNertcStruct(infos[i], nertc_infos[i]);
            }
            g_engine_media_stats_map[self]->onNetworkQuality(nertc_infos, user_count);
            delete[] nertc_infos;
        }

    }
    void NertcEngineEx::fillCsdkMediaStatsObserver(IRtcMediaStatsObserver* observer) {
        g_engine_media_stats_map[m_nertc_engine] = observer;
        if (!m_nertc_media_stats_observer) {
            m_nertc_media_stats_observer = new nertc_media_stats_observer();
        }
        if (!observer) {
            *m_nertc_media_stats_observer = nertc_media_stats_observer{};
        }
        m_nertc_media_stats_observer->self = m_nertc_engine;

        m_nertc_media_stats_observer->on_rtc_stats = on_rtc_stats;
        m_nertc_media_stats_observer->on_local_audio_stats = on_local_audio_stats;
        m_nertc_media_stats_observer->on_remote_audio_stats = on_remote_audio_stats;
        m_nertc_media_stats_observer->on_local_video_stats = on_local_video_stats;
        m_nertc_media_stats_observer->on_remote_video_stats = on_remote_video_stats;
        m_nertc_media_stats_observer->on_network_quality = on_network_quality;

    }
    void NertcEngineEx::clearCsdkMediaStatsObserver() {
        //g_engine_media_stats_map.erase(m_nertc_engine);
        g_engine_media_stats_map.clear();
    }

}