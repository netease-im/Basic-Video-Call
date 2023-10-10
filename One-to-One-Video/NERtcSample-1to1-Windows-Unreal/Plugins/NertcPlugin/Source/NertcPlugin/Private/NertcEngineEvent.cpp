// Copyright Epic Games, Inc. All Rights Reserved.

#include "NertcEngineEx.h"
#include "NertcEngineUtil.h"

#include "Nertc/api/nertc_engine_defines.h"
#include "Nertc/api/nertc_engine.h"
#include "Nertc/api/nertc_engine_events.h"

#include <map>
//#include <mutex>
static std::map<void*, nertc::IRtcEngineEventHandler*> g_engine_handler_map;
namespace engine_sink {
  ////////////////////////////////IRtcEngineEventHandler////////////////////////////////////
  void on_error(void* self, int error_code, const char* msg) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onError(error_code, msg);
  }

  void on_warning(void* self, int warn_code, const char* msg) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onWarning(warn_code, msg);
  }
  void on_join_channel(void* self, channel_id_t cid, nertc_uid_t uid, nertc_error_code result, uint64_t elapsed) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onJoinChannel(cid, uid, (nertc::NERtcErrorCode)result, elapsed);
  }
  void on_reconnecting_start(void* self, channel_id_t cid, nertc_uid_t uid) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onReconnectingStart(cid, uid);
  }
  void on_connection_state_change(void* self, nertc_connection_state_type state, nertc_reason_connection_changed_type reason) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onConnectionStateChange((nertc::NERtcConnectionStateType)state, (nertc::NERtcReasonConnectionChangedType)reason);
  }
  void on_rejoin_channel(void* self, channel_id_t cid, nertc_uid_t uid, nertc_error_code result, uint64_t elapsed) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onRejoinChannel(cid, uid, (nertc::NERtcErrorCode)result, elapsed);
  }
  void on_leave_channel(void* self, nertc_error_code result, uint64_t channel_id) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onLeaveChannel((nertc::NERtcErrorCode)result, channel_id);
  }
  void on_disconnect(void* self, nertc_error_code reason) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onDisconnect((nertc::NERtcErrorCode)reason);
  }
  void on_client_role_changed(void* self, nertc_client_role old_role, nertc_client_role new_role) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onClientRoleChanged((nertc::NERtcClientRole)old_role, (nertc::NERtcClientRole)new_role);
  }
  void on_user_joined(void* self, nertc_uid_t uid, const char* user_name, const struct nertc_user_join_extra_info* custom_info) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    nertc::NERtcUserJoinExtraInfo extra_info;
    if (custom_info) {
      convertToNertcStruct(*custom_info, extra_info);
    }
    g_engine_handler_map[self]->onUserJoined(uid, user_name, extra_info);
  }
  void on_user_left(void* self, nertc_uid_t uid, nertc_session_leave_reason reason, const struct nertc_user_join_extra_info* custom_info) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    nertc::NERtcUserJoinExtraInfo extra_info;
    if (custom_info) {
      convertToNertcStruct(*custom_info, extra_info);
    }
    g_engine_handler_map[self]->onUserLeft(uid, (nertc::NERtcSessionLeaveReason)reason, extra_info);
  }
  void on_user_audio_start(void* self, nertc_audio_stream_type type, nertc_uid_t uid) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onUserAudioStart(nertc::NERtcAudioStreamType(type), uid);
  }
  void on_user_audio_stop(void* self, nertc_audio_stream_type type, nertc_uid_t uid) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onUserAudioStop(nertc::NERtcAudioStreamType(type), uid);
  }
  void on_user_video_start(void* self, nertc_video_stream_type type, nertc_uid_t uid, nertc_video_profile_type max_profile) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onUserVideoStart(nertc::NERtcVideoStreamType(type), uid, (nertc::NERtcVideoProfileType)max_profile);
  }
  void on_user_video_stop(void* self, nertc_video_stream_type type, nertc_uid_t uid) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onUserVideoStop(nertc::NERtcVideoStreamType(type), uid);
  }

  ////////////////////////////////IRtcEngineEventHandlerEx////////////////////////////////////

  void on_screen_capture_state_changed(void* self, nertc_screen_capture_status status) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onScreenCaptureStatusChanged((nertc::NERtcScreenCaptureStatus)status);
  }
  void on_user_video_profile_update(void* self, nertc_uid_t uid, nertc_video_profile_type max_profile) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onUserVideoProfileUpdate(uid, (nertc::NERtcVideoProfileType)max_profile);
  }
  void on_user_audio_mute(void* self, nertc_audio_stream_type type, nertc_uid_t uid, bool mute) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onUserAudioMute(nertc::NERtcAudioStreamType(type), uid, mute);
  }
  void on_user_video_mute(void* self, nertc_video_stream_type type, nertc_uid_t uid, bool mute) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onUserVideoMute(nertc::NERtcVideoStreamType(type), uid, mute);
  }
  void on_audio_device_state_changed(void* self, const char* device_id, nertc_audio_device_type device_type, nertc_audio_device_state device_state) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onAudioDeviceStateChanged(device_id, (nertc::NERtcAudioDeviceType)device_type, (nertc::NERtcAudioDeviceState)device_state);
  }
  void on_audio_default_device_changed(void* self, const char* device_id, nertc_audio_device_type device_type) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onAudioDefaultDeviceChanged(device_id, (nertc::NERtcAudioDeviceType)device_type);
  }
  void on_video_device_state_changed(void* self, const char* device_id, nertc_video_device_type device_type, nertc_video_device_state device_state) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onVideoDeviceStateChanged(device_id, (nertc::NERtcVideoDeviceType)device_type, (nertc::NERtcVideoDeviceState)device_state);
  }
  void on_camera_focus_changed(void* self, const struct nertc_camera_focus_and_exposure_info* info) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    nertc::NERtcCameraFocusAndExposureInfo nertc_info{};
    if (info) {
      convertToNertcStruct(*info, nertc_info);
    }
    g_engine_handler_map[self]->onCameraFocusChanged(nertc_info);
  }
  void on_camera_exposure_changed(void* self, const struct nertc_camera_focus_and_exposure_info* info) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    nertc::NERtcCameraFocusAndExposureInfo nertc_info{};
    if (info) {
      convertToNertcStruct(*info, nertc_info);
    }
    g_engine_handler_map[self]->onCameraExposureChanged(nertc_info);
  }
  void on_first_audio_data_received(void* self, nertc_audio_stream_type type, nertc_uid_t uid) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onFirstAudioDataReceived(nertc::NERtcAudioStreamType(type), uid);
  }
  void on_first_video_data_received(void* self, nertc_video_stream_type type, nertc_uid_t uid) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onFirstVideoDataReceived(nertc::NERtcVideoStreamType(type), uid);
  }
  void on_first_audio_frame_decoded(void* self, nertc_audio_stream_type type, nertc_uid_t uid) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onFirstAudioFrameDecoded(nertc::NERtcAudioStreamType(type), uid);
  }
  void on_first_video_frame_decoded(void* self, nertc_video_stream_type type, nertc_uid_t uid, uint32_t width, uint32_t height) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onFirstVideoFrameDecoded(nertc::NERtcVideoStreamType(type), uid, width, height);
  }

  void on_capture_video_frame(void* self,
    void* data,
    nertc_video_type type,
    uint32_t width,
    uint32_t height,
    uint32_t count,
    uint32_t* offset,
    uint32_t* stride,
    nertc_video_rotation rotation) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onCaptureVideoFrame(data, (nertc::NERtcVideoType)type, width, height, count, offset, stride, (nertc::NERtcVideoRotation)rotation);
  }
  void on_audio_mixing_state_changed(void* self, nertc_audio_mixing_state state, nertc_audio_mixing_error_code error_code) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onAudioMixingStateChanged((nertc::NERtcAudioMixingState)state, (nertc::NERtcAudioMixingErrorCode)error_code);
  }
  void on_audio_mixing_timestamp_update(void* self, uint64_t timestamp_ms) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onAudioMixingTimestampUpdate(timestamp_ms);
  }
  void on_audio_effect_finished(void* self, uint32_t effect_id) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onAudioEffectFinished(effect_id);
  }
  void on_local_audio_volume_indication(void* self, int volume, bool enable_vad) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onLocalAudioVolumeIndication(volume, enable_vad);
  }
  void on_remote_audio_volume_indication(void* self, const struct nertc_audio_volume_info* speakers, uint32_t speaker_number, int total_volume) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    nertc::NERtcAudioVolumeInfo* nertc_speakers = nullptr;
    auto windup_cb = convertToNertcStruct(speakers, speaker_number, nertc_speakers);
    g_engine_handler_map[self]->onRemoteAudioVolumeIndication(nertc_speakers, speaker_number, total_volume);
    windup_cb();
  }
  void on_add_live_stream_task(void* self, const char* task_id, const char* url, int error_code) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onAddLiveStreamTask(task_id, url, error_code);
  }
  void on_update_live_stream_task(void* self, const char* task_id, const char* url, int error_code) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onUpdateLiveStreamTask(task_id, url, error_code);
  }
  void on_remove_live_stream_task(void* self, const char* task_id, int error_code) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onRemoveLiveStreamTask(task_id, error_code);
  }
  void on_live_stream_state_changed(void* self, const char* task_id, const char* url, nertc_live_stream_state_code state) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onLiveStreamStateChanged(task_id, url, (nertc::NERtcLiveStreamStateCode)state);
  }
  void on_audio_howling(void* self, bool howling) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onAudioHowling(howling);
  }
  void on_receive_sei_message(void* self, nertc_uid_t uid, const uint8_t* data, uint32_t dataSize) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onRecvSEIMsg(uid, data, dataSize);
  }
  void on_audio_recording(void* self, nertc_audio_recording_code code, const char* file_path) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onAudioRecording((nertc::NERtcAudioRecordingCode)code, file_path);
  }
  void on_media_relay_state_changed(void* self, nertc_channel_media_relay_state state, const char* channel_name) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onMediaRelayStateChanged((nertc::NERtcChannelMediaRelayState)state, channel_name);
  }
  void on_media_relay_event(void* self, nertc_channel_media_relay_event event, const char* channel_name, nertc_error_code error) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onMediaRelayEvent((nertc::NERtcChannelMediaRelayEvent)event, channel_name, (nertc::NERtcErrorCode)error);
  }
  void on_publish_fallback_to_audio_only(void* self, bool is_fallback, nertc_video_stream_type stream_type) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onPublishFallbackToAudioOnly(is_fallback, (nertc::NERtcVideoStreamType)stream_type);
  }
  void on_subscribe_fallback_to_audio_only(void* self, nertc_uid_t uid, bool is_fallback, nertc_video_stream_type stream_type) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onSubscribeFallbackToAudioOnly(uid, is_fallback, (nertc::NERtcVideoStreamType)stream_type);
  }
  void on_lastmile_quality(void* self, nertc_network_quality_type quality) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    g_engine_handler_map[self]->onLastmileQuality((nertc::NERtcNetworkQualityType)quality);
  }
  void on_lastmile_probe_result(void* self, const struct nertc_lastmile_probe_result* result) {
    if (g_engine_handler_map.find(self) == g_engine_handler_map.end())
      return;
    nertc::NERtcLastmileProbeResult nertc_result{};
    convertToNertcStruct(*result, nertc_result);
    g_engine_handler_map[self]->onLastmileProbeResult(nertc_result);
  }
  /*
  void on_client_virtual_human_data(void* self, nertc_uid_t uid, const uint8_t* data, uint32_t dataSize) {
  }
  void on_user_virtual_human_start(void* self, nertc_uid_t uid) {
  }
  void on_user_virtual_human_stop(void* self, nertc_uid_t uid) {
  }
  */

}
namespace nertc {
    
    void NertcEngineEx::fillCsdkEventHandler(IRtcEngineEventHandler* handler) {
        g_engine_handler_map[m_nertc_engine] = handler;
        if (!m_nertc_engine_event) {
            m_nertc_engine_event = new nertc_engine_events{0};
        }

        if (!handler) {
            //clear callback
            *m_nertc_engine_event = nertc_engine_events{0};
            return;
        }
        m_nertc_engine_event->self = m_nertc_engine;

        m_nertc_engine_event->on_error = engine_sink::on_error;
        m_nertc_engine_event->on_warning = engine_sink::on_warning;
        m_nertc_engine_event->on_join_channel = engine_sink::on_join_channel;
        m_nertc_engine_event->on_reconnecting_start = engine_sink::on_reconnecting_start;
        m_nertc_engine_event->on_connection_state_change = engine_sink::on_connection_state_change;
        m_nertc_engine_event->on_rejoin_channel = engine_sink::on_rejoin_channel;
        m_nertc_engine_event->on_leave_channel = engine_sink::on_leave_channel;
        m_nertc_engine_event->on_disconnect = engine_sink::on_disconnect;
        m_nertc_engine_event->on_client_role_changed = engine_sink::on_client_role_changed;
        m_nertc_engine_event->on_user_joined = engine_sink::on_user_joined;
        m_nertc_engine_event->on_user_left = engine_sink::on_user_left;
        m_nertc_engine_event->on_user_audio_start = engine_sink::on_user_audio_start;
        m_nertc_engine_event->on_user_audio_stop = engine_sink::on_user_audio_stop;
        //m_nertc_engine_event->on_user_video_start = engine_sink::on_user_video_start;
        //m_nertc_engine_event->on_user_video_stop = engine_sink::on_user_video_stop;

        //m_nertc_engine_event->on_screen_capture_state_changed = engine_sink::on_screen_capture_state_changed;
        //m_nertc_engine_event->on_user_video_profile_update = engine_sink::on_user_video_profile_update;
        m_nertc_engine_event->on_user_audio_mute = engine_sink::on_user_audio_mute;
        m_nertc_engine_event->on_audio_device_state_changed = engine_sink::on_audio_device_state_changed;
        m_nertc_engine_event->on_audio_default_device_changed = engine_sink::on_audio_default_device_changed;
        //m_nertc_engine_event->on_video_device_state_changed = engine_sink::on_video_device_state_changed;
        //m_nertc_engine_event->on_camera_focus_changed = engine_sink::on_camera_focus_changed;
        //m_nertc_engine_event->on_camera_exposure_changed = engine_sink::on_camera_exposure_changed;
        m_nertc_engine_event->on_first_audio_data_received = engine_sink::on_first_audio_data_received;
        //m_nertc_engine_event->on_first_video_data_received = engine_sink::on_first_video_data_received;
        m_nertc_engine_event->on_first_audio_frame_decoded = engine_sink::on_first_audio_frame_decoded;
        //m_nertc_engine_event->on_first_video_frame_decoded = engine_sink::on_first_video_frame_decoded;
        //m_nertc_engine_event->on_capture_video_frame = engine_sink::on_capture_video_frame;
        //m_nertc_engine_event->on_audio_mixing_state_changed = engine_sink::on_audio_mixing_state_changed;
        //m_nertc_engine_event->on_audio_mixing_timestamp_update = engine_sink::on_audio_mixing_timestamp_update;
        //m_nertc_engine_event->on_audio_effect_finished = engine_sink::on_audio_effect_finished;
        m_nertc_engine_event->on_local_audio_volume_indication = engine_sink::on_local_audio_volume_indication;
        m_nertc_engine_event->on_remote_audio_volume_indication = engine_sink::on_remote_audio_volume_indication;
        //m_nertc_engine_event->on_add_live_stream_task = engine_sink::on_add_live_stream_task;
        //m_nertc_engine_event->on_update_live_stream_task = engine_sink::on_update_live_stream_task;
        //m_nertc_engine_event->on_remove_live_stream_task = engine_sink::on_remove_live_stream_task;
        //m_nertc_engine_event->on_live_stream_state_changed = engine_sink::on_live_stream_state_changed;
        m_nertc_engine_event->on_audio_howling = engine_sink::on_audio_howling;
        //m_nertc_engine_event->on_receive_sei_message = engine_sink::on_receive_sei_message;
        m_nertc_engine_event->on_audio_recording = engine_sink::on_audio_recording;
        //m_nertc_engine_event->on_media_relay_state_changed = engine_sink::on_media_relay_state_changed;
        //m_nertc_engine_event->on_media_relay_event = engine_sink::on_media_relay_event;
        //m_nertc_engine_event->on_publish_fallback_to_audio_only = engine_sink::on_publish_fallback_to_audio_only;
        //m_nertc_engine_event->on_subscribe_fallback_to_audio_only = engine_sink::on_subscribe_fallback_to_audio_only;
        //m_nertc_engine_event->on_lastmile_quality = engine_sink::on_lastmile_quality;
        //m_nertc_engine_event->on_lastmile_probe_result = engine_sink::on_lastmile_probe_result;

        //m_nertc_engine_event->on_client_virtual_human_data = engine_sink::on_client_virtual_human_data;
        //m_nertc_engine_event->on_user_virtual_human_start = engine_sink::on_user_virtual_human_start;
        //m_nertc_engine_event->on_user_virtual_human_stop = engine_sink::on_user_virtual_human_stop;
    }

    void NertcEngineEx::clearCsdkEventHandler() {
        g_engine_handler_map.clear();
    }
}