// Copyright Epic Games, Inc. All Rights Reserved.

#include "NertcEngineEx.h"
#include "NertcEngineUtil.h"
#include <map>
namespace nertc {
    static std::map<void*, INERtcAudioFrameObserver*> g_engine_audio_observer_map;
    namespace {
        void on_audio_frame_did_record(void* self, struct nertc_audio_frame* frame) {
            if (g_engine_audio_observer_map.find(self) == g_engine_audio_observer_map.end())
                return;
            NERtcAudioFrame nertc_frame{};
            convertToNertcStruct(*frame, nertc_frame);
            g_engine_audio_observer_map[self]->onAudioFrameDidRecord(&nertc_frame);
        }
        void on_audio_frame_will_playback(void* self, struct nertc_audio_frame* frame) {
            if (g_engine_audio_observer_map.find(self) == g_engine_audio_observer_map.end())
                return;
            NERtcAudioFrame nertc_frame{};
            convertToNertcStruct(*frame, nertc_frame);
            g_engine_audio_observer_map[self]->onAudioFrameWillPlayback(&nertc_frame);
        }
        void on_mixed_audio_frame(void* self, struct nertc_audio_frame* frame) {
            if (g_engine_audio_observer_map.find(self) == g_engine_audio_observer_map.end())
                return;
            NERtcAudioFrame nertc_frame{};
            convertToNertcStruct(*frame, nertc_frame);
            g_engine_audio_observer_map[self]->onMixedAudioFrame(&nertc_frame);
        }
        void on_playback_audio_frame_before_mixing(void* self, uint64_t user_id, struct nertc_audio_frame* frame, channel_id_t cid) {
            if (g_engine_audio_observer_map.find(self) == g_engine_audio_observer_map.end())
                return;
            NERtcAudioFrame nertc_frame{};
            convertToNertcStruct(*frame, nertc_frame);
            g_engine_audio_observer_map[self]->onPlaybackAudioFrameBeforeMixing(user_id, &nertc_frame, cid);
        }
    }
    void NertcEngineEx::clearCsdkAudioFrameObserver() {
        //g_engine_audio_observer_map.erase(m_nertc_engine);
        g_engine_audio_observer_map.clear();
    }
    void NertcEngineEx::fillCsdkAudioFrameObserver(INERtcAudioFrameObserver* observer) {
        g_engine_audio_observer_map[m_nertc_engine] = observer;
        if (!m_nertc_audio_frame_observer) {
            m_nertc_audio_frame_observer = new nertc_audio_frame_observer();
        }
        if (!observer) {
            *m_nertc_audio_frame_observer = nertc_audio_frame_observer{};
        }
        m_nertc_audio_frame_observer->self = m_nertc_engine;

        m_nertc_audio_frame_observer->on_audio_frame_did_record = on_audio_frame_did_record;
        m_nertc_audio_frame_observer->on_audio_frame_will_playback = on_audio_frame_will_playback;
        m_nertc_audio_frame_observer->on_mixed_audio_frame = on_mixed_audio_frame;
        m_nertc_audio_frame_observer->on_playback_audio_frame_before_mixing = on_playback_audio_frame_before_mixing;
    }


}