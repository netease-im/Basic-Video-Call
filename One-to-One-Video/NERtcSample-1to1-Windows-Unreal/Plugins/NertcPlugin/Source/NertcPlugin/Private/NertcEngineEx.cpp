// Copyright Epic Games, Inc. All Rights Reserved.

#include "NertcEngineEx.h"
#include "NertcAudioDeviceManager.h"
#include "NertcEngineUtil.h"
#include "Nertc/api/nertc_engine.h"
#include "Nertc/api/nertc_engine_ex.h"
#include <utility>

#if !WITH_EDITOR && PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#include "AndroidPermission/Classes/AndroidPermissionCallbackProxy.h"
#include "Android/AndroidJni.h"
#endif

namespace nertc {
  IRtcEngineEx* createNERtcEngine() {
    nertc_engine* csdk_nertc_engine = create_nertc_engine();
    if (csdk_nertc_engine) {
      return new NertcEngineEx(csdk_nertc_engine);
    }
    return nullptr;
  }
  
	NertcEngineEx::NertcEngineEx(const NertcEngineEx& other):m_nertc_engine(other.m_nertc_engine){
	
	}
	NertcEngineEx::NertcEngineEx(NertcEngineEx&& other)noexcept: m_nertc_engine(std::exchange(other.m_nertc_engine, nullptr)){
	
	}
	NertcEngineEx& NertcEngineEx::operator=(const NertcEngineEx& other) {
		return *this = NertcEngineEx(other);
	}
	NertcEngineEx& NertcEngineEx::operator=(NertcEngineEx&& other) noexcept {
		std::swap(m_nertc_engine, other.m_nertc_engine);
		return *this;
	}
	NertcEngineEx::~NertcEngineEx(){
		::destroy_nertc_engine(m_nertc_engine);
		m_nertc_engine = nullptr;
		if (m_nertc_audio_frame_observer) {
			delete m_nertc_audio_frame_observer;
			m_nertc_audio_frame_observer = nullptr;
		}
        if (m_nertc_media_stats_observer) {
            delete m_nertc_media_stats_observer;
            m_nertc_media_stats_observer = nullptr;
        }
        if (m_nertc_engine_event) {
            delete m_nertc_engine_event;
            m_nertc_engine_event = nullptr;
        }

        clearCsdkAudioFrameObserver();
        clearCsdkMediaStatsObserver();
        clearCsdkEventHandler();
	}
	NertcEngineEx::NertcEngineEx(nertc_engine* engine):m_nertc_engine(engine){

	}
  ///////////////////////////////////////////////////////////////

  int NertcEngineEx::initialize(const NERtcEngineContext& context) {
    nertc_engine_context csdk_context{};
    csdk_context.app_key = context.app_key;
    csdk_context.log_dir_path = context.log_dir_path;
    csdk_context.log_level = (nertc_log_level)context.log_level;
    csdk_context.log_file_max_size_kbytes = context.log_file_max_size_KBytes;
    memcpy(csdk_context.server_config.channel_server, context.server_config.channel_server, kNERtcMaxURILength);
    memcpy(csdk_context.server_config.statistics_server, context.server_config.statistics_server, kNERtcMaxURILength);
    memcpy(csdk_context.server_config.statistics_dispatch_server, context.server_config.statistics_dispatch_server, kNERtcMaxURILength);
    memcpy(csdk_context.server_config.statistics_backup_server, context.server_config.statistics_backup_server, kNERtcMaxURILength);
    memcpy(csdk_context.server_config.room_server, context.server_config.room_server, kNERtcMaxURILength);
    memcpy(csdk_context.server_config.compat_server, context.server_config.compat_server, kNERtcMaxURILength);
    memcpy(csdk_context.server_config.nos_lbs_server, context.server_config.nos_lbs_server, kNERtcMaxURILength);
    memcpy(csdk_context.server_config.nos_upload_sever, context.server_config.nos_upload_sever, kNERtcMaxURILength);
    memcpy(csdk_context.server_config.nos_token_server, context.server_config.nos_token_server, kNERtcMaxURILength);
    memcpy(csdk_context.server_config.cloud_proxy_server, context.server_config.cloud_proxy_server, kNERtcMaxURILength);
    memcpy(csdk_context.server_config.websocket_proxy_server, context.server_config.websocket_proxy_server, kNERtcMaxURILength);
    memcpy(csdk_context.server_config.quic_proxy_server, context.server_config.quic_proxy_server, kNERtcMaxURILength);
    memcpy(csdk_context.server_config.media_proxy_server, context.server_config.media_proxy_server, kNERtcMaxURILength);
    csdk_context.server_config.use_ipv6 = context.server_config.use_ipv6;
    if (!m_nertc_engine_event) {
      m_nertc_engine_event = new nertc_engine_events();
    }
    fillCsdkEventHandler(context.event_handler);
    csdk_context.events = *m_nertc_engine_event;

    auto ret = nertc_engine_init(m_nertc_engine, &csdk_context);
    nertc_engine_set_parameters(m_nertc_engine, "{\"sdk.business.scenario.type\":14}");
    return ret;
  }

  void NertcEngineEx::release(bool sync /*= false*/) {
    nertc_engine_release(m_nertc_engine, sync);
  }
  int NertcEngineEx::setClientRole(NERtcClientRole role) {
    return nertc_engine_set_client_role(m_nertc_engine, (nertc_client_role)role);
  }
  int NertcEngineEx::setChannelProfile(NERtcChannelProfileType profile) {
    return nertc_engine_set_channel_profile(m_nertc_engine, (nertc_channel_profile_type)profile);
  }
  int NertcEngineEx::joinChannel(const char* token, const char* channel_name, uid_t uid, const NERtcJoinChannelOptions& channel_options) {
    nertc_join_channel_options csdk_channel_options;
    convertToCsdkStruct(channel_options, csdk_channel_options);
    return nertc_engine_join_channel(m_nertc_engine, token, channel_name, uid, &csdk_channel_options);
  }
  int NertcEngineEx::switchChannel(const char* token, const char* channel_name, const NERtcJoinChannelOptions& channel_options) {
    nertc_join_channel_options csdk_channel_options;
    convertToCsdkStruct(channel_options, csdk_channel_options);
    return nertc_engine_switch_channel(m_nertc_engine, token, channel_name, &csdk_channel_options);
  }
  int NertcEngineEx::switchChannelEx(const char* token, const char* channel_name, uid_t uid, const NERtcJoinChannelOptionsEx& channel_options) {
    nertc_join_channel_options_ex csdk_channel_options;
    convertToCsdkStruct(channel_options, csdk_channel_options);
    return nertc_engine_switch_channel_ex(m_nertc_engine, token, channel_name, uid, &csdk_channel_options);
  }
  int NertcEngineEx::leaveChannel() {
    return nertc_engine_leave_channel(m_nertc_engine);
  }
  int NertcEngineEx::queryInterface(NERtcInterfaceIdType iid, void** inter) {
    void* csdk_manager_ptr{};
    csdk_manager_ptr = nertc_engine_query_interface(m_nertc_engine, (nertc_interface_id_type)iid);
    if (!csdk_manager_ptr) {
      *inter = nullptr;
      return kNERtcErrFatal;
    }
    if (iid == kNERtcIIDAudioDeviceManager) {
      *inter = new NertcAudioDeviceManager(static_cast<nertc_audio_device_manager*>(csdk_manager_ptr));
      return kNERtcNoError;
    }
    else {
      //TODO
    }
    return *inter == nullptr ? kNERtcErrInvalidState : kNERtcNoError;
  }

  int NertcEngineEx::enableLocalAudio(NERtcAudioStreamType type, bool enabled) {
    return nertc_engine_enable_local_audio(m_nertc_engine, (nertc_audio_stream_type)type, enabled);
  }

  ///////////////////////////////////////////////////////////////
	NERtcConnectionStateType NertcEngineEx::getConnectionState() {
		return (NERtcConnectionStateType)nertc_engine_get_connection_state(m_nertc_engine);
	}
	int NertcEngineEx::muteLocalAudioStream(NERtcAudioStreamType type, bool mute) {
		return nertc_engine_mute_local_audio_stream(m_nertc_engine, nertc_audio_stream_type(type), mute);
	}
	int NertcEngineEx::setAudioProfile(NERtcAudioProfileType profile, NERtcAudioScenarioType scenario) {
		return nertc_engine_set_audio_profile(m_nertc_engine, (nertc_audio_profile_type)profile, (nertc_audio_scenario_type)scenario);
	}
  int NertcEngineEx::setAudioEffectPreset(NERtcVoiceChangerType type) {
    return nertc_engine_set_audio_effect_preset(m_nertc_engine, (nertc_voice_changer_type)type);
  }
  int NertcEngineEx::setVoiceBeautifierPreset(NERtcVoiceBeautifierType type) {
    return nertc_engine_set_voice_beautifier_preset(m_nertc_engine, (nertc_voice_beautifier_type)type);
  }
  int NertcEngineEx::setLocalVoicePitch(double pitch) {
    return nertc_engine_set_local_voice_pitch(m_nertc_engine, pitch);
  }
  int NertcEngineEx::setLocalVoiceEqualization(NERtcVoiceEqualizationBand band_frequency, int band_gain) {
    return nertc_engine_set_local_voice_equalization(m_nertc_engine, (nertc_voice_equalization_band)band_frequency, band_gain);
  }
	int NertcEngineEx::subscribeRemoteAudioStream(NERtcAudioStreamType type, uid_t uid, bool subscribe) {
		return nertc_engine_subscribe_remote_audio_stream(m_nertc_engine, nertc_audio_stream_type(type), uid, subscribe);
	}
  int NertcEngineEx::subscribeAllRemoteAudioStream(bool subscribe) {
    return nertc_engine_subscribe_all_remote_audio_stream(m_nertc_engine, subscribe);
  }
  int NertcEngineEx::setPublishAudioAllowList(uid_t* uid_array, uint32_t size) {
      return nertc_engine_set_audio_subscribe_only_by(m_nertc_engine, uid_array, size);
  }

  int NertcEngineEx::setSubscribeAudioAllowList(uid_t* uid_array, uint32_t size) {
    return nertc_engine_set_subscribe_audio_allow_list(m_nertc_engine, uid_array, size);
  }
  int NertcEngineEx::setSubscribeAudioBlockList(uid_t* uid_array, uint32_t size) {
    return nertc_engine_set_subscribe_audio_block_list(m_nertc_engine, uid_array, size);
  }

  int NertcEngineEx::setAudioSessionOperationRestriction(NERtcAudioSessionOperationRestriction restriction)  {
    return nertc_engine_set_audio_session_operation_restriction(m_nertc_engine, (nertc_audio_session_operation_restriction)restriction);
  }

  int NertcEngineEx::setAudioFocusMode(NERtcAudioFocusMode focus_mode)  {
    return nertc_engine_set_audio_focus_mode(m_nertc_engine, (nertc_audio_focus_mode)focus_mode);
  }

  int NertcEngineEx::setPlayoutDeviceMute(bool muted) {
    return nertc_engine_set_playout_device_mute(m_nertc_engine, muted);
  }

  int NertcEngineEx::getPlayoutDeviceMute(bool* muted) {
    return nertc_engine_get_playout_device_mute(m_nertc_engine, muted);
  }

	int NertcEngineEx::setParameters(const char* parameters) {
		return nertc_engine_set_parameters(m_nertc_engine, parameters);
	}
	int NertcEngineEx::setAudioFrameObserver(INERtcAudioFrameObserver* observer) {
		fillCsdkAudioFrameObserver(observer);
		return nertc_engine_set_audio_frame_observer(m_nertc_engine, m_nertc_audio_frame_observer);
	}
	int NertcEngineEx::startAudioDump(NERtcAudioDumpType type) {
		return nertc_engine_start_audio_dump(m_nertc_engine, nertc_audio_dump_type(type));
	}
	int NertcEngineEx::stopAudioDump() {
		return nertc_engine_stop_audio_dump(m_nertc_engine);
	}
  int NertcEngineEx::setLoudspeakerMode(bool enable) {
    return nertc_engine_set_loudspeaker_mode(m_nertc_engine, enable);
  }

  int NertcEngineEx::getLoudspeakerMode(bool* enabled) { 
    return nertc_engine_get_loudspeaker_mode(m_nertc_engine, enabled);
  }
  
	int NertcEngineEx::setStatsObserver(IRtcMediaStatsObserver* observer) {
		fillCsdkMediaStatsObserver(observer);
		nertc_engine_set_stats_observer(m_nertc_engine, m_nertc_media_stats_observer);
		return kNERtcNoError;
	}
	int NertcEngineEx::enableAudioVolumeIndication(bool enable, uint64_t interval, bool enable_vad) {
		return nertc_engine_enable_audio_volume_indication(m_nertc_engine, enable, interval, enable_vad);
	}
	const char* NertcEngineEx::getVersion(int* build) {
		return nertc_engine_get_version(m_nertc_engine);
	}
	const char* NertcEngineEx::getErrorDescription(int error_code) {
		return nertc_engine_get_error_description(m_nertc_engine, error_code);
	}
	void NertcEngineEx::uploadSdkInfo() {
		nertc_engine_upload_sdk_info(m_nertc_engine);
	}
  int NertcEngineEx::adjustRecordingSignalVolume(int volume) { 
    return nertc_engine_adjust_recording_signal_volume(m_nertc_engine, volume);
  }
  int NertcEngineEx::adjustPlaybackSignalVolume(int volume) { 
    return nertc_engine_adjust_playback_signal_volume(m_nertc_engine, volume);
  }
  int NertcEngineEx::enableMediaPublish(bool enabled, NERtcMediaPubType media_type) {
    return nertc_engine_enable_media_publish(m_nertc_engine, enabled, (nertc_media_pub_type)media_type);
  }
  int NertcEngineEx::setRangeAudioMode(NERtcRangeAudioMode mode) {
    return nertc_engine_set_range_audio_mode(m_nertc_engine, (nertc_range_audio_mode)mode);
  }
  int NertcEngineEx::setRangeAudioTeamID(int32_t team_id) {
    return nertc_engine_set_range_audio_team_id(m_nertc_engine, team_id);
  }
  int NertcEngineEx::setAudioRecvRange(int audible_distance,
    int conversational_distance,
    NERtcDistanceRolloffModel roll_off) {
    return nertc_engine_set_audio_recv_range(m_nertc_engine, audible_distance, conversational_distance, (nertc_distance_rolloff_model)roll_off);
  }
  int NertcEngineEx::updateSelfPosition(const NERtcPositionInfo& info) {
    nertc_position_info csdk_info{};
    convertToCsdkStruct(info, csdk_info);
    return nertc_engine_update_self_position(m_nertc_engine, &csdk_info);
  }
  int NertcEngineEx::initSpatializer() {
    return nertc_engine_init_spatializer(m_nertc_engine);
  }
	int NertcEngineEx::enableSpatializer(bool enable) {
		return nertc_engine_enable_spatializer(m_nertc_engine, enable);
	}
  int NertcEngineEx::getMicrophoneMode(bool* enabled) {
    return nertc_engine_get_microphone_mode(m_nertc_engine,enabled);
  }
  int NertcEngineEx::getRecordingSignalVolume() {
    int volume = 0;
    nertc_engine_get_recording_signal_volume(m_nertc_engine, &volume);
    return volume;
  }
  int NertcEngineEx::getPlaybackSignalVolume() {
    int volume = 0;
    nertc_engine_get_playback_signal_volume(m_nertc_engine, &volume);
    return volume;
  }
  bool NertcEngineEx::checkMicPermision() {
    bool enabled = false;
    nertc_engine_check_mic_permision(m_nertc_engine,&enabled);
    return enabled;
  }
  int NertcEngineEx::pauseAudio() {
    return nertc_engine_pause_audio(m_nertc_engine);
  }
  int NertcEngineEx::resumeAudio() {
    return nertc_engine_resume_audio(m_nertc_engine);
  }
  bool NertcEngineEx::isInChannel() {
    return nertc_engine_is_in_channel(m_nertc_engine);
  }
  bool NertcEngineEx::acquireAndroidRecordingPermissions() {
#if PLATFORM_ANDROID
    auto hasPermission = UAndroidPermissionFunctionLibrary::CheckPermission(TEXT("android.permission.RECORD_AUDIO"));

    if (hasPermission) {
      return true;
    }

    TArray<FString> Permissions;
    Permissions.Add(TEXT("android.permission.RECORD_AUDIO"));
    Permissions.Add(TEXT("android.permission.BLUETOOTH"));
    Permissions.Add(TEXT("android.permission.BLUETOOTH_CONNECT"));
    Permissions.Add(TEXT("android.permission.BROADCAST_STICKY"));

    UAndroidPermissionCallbackProxy* proxy = UAndroidPermissionFunctionLibrary::AcquirePermissions(Permissions);
    if (!proxy) {
      return false;
    }

    proxy->OnPermissionsGrantedDelegate.BindLambda([this](const TArray<FString>& Permissions, const TArray<bool>& GrantResults) {
      std::unique_lock<std::recursive_mutex> lock(m_sleep_condition_mutex);
      m_sleep_condition.notify_one();
    });

    std::unique_lock<std::recursive_mutex> lock(m_sleep_condition_mutex);
    m_sleep_condition.wait(lock);
    return UAndroidPermissionFunctionLibrary::CheckPermission(TEXT("android.permission.RECORD_AUDIO"));
#endif
    return false;
  }
}
