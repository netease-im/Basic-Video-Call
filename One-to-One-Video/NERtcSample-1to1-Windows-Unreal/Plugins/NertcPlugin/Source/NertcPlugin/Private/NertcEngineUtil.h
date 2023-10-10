#pragma once
#include "NertcEngineDefines.h"
#include "Nertc/api/nertc_engine_defines.h"
#include <functional>
namespace nertc {
  using WindUpCallback = std::function<void(void)>;
  //////////////////////////////csdk struct to nertc struce//////////////////////////////
  void convertToCsdkStruct(const NERtcJoinChannelOptions& src, nertc_join_channel_options& dst);
  void convertToCsdkStruct(const NERtcJoinChannelOptionsEx& src, nertc_join_channel_options_ex& dst);
  void convertToCsdkStruct(const NERtcRectangle& src, nertc_rectangle& dst);
  void convertToCsdkStruct(const NERtcScreenCaptureParameters& src, nertc_screen_capture_parameters& dst);
  void convertToCsdkStruct(const NERtcVideoCanvas& src, nertc_video_canvas& dst);
  void convertToCsdkStruct(const NERtcCameraCaptureConfig& src, nertc_camera_capture_config& dst);
  void convertToCsdkStruct(const NERtcVideoConfig& src, nertc_video_config& dst);
  WindUpCallback convertToCsdkStruct(const NERtcLiveStreamTaskInfo& src, nertc_live_stream_task_info& dst);
  void convertToCsdkStruct(const NERtcVideoWatermarkConfig& src, nertc_video_watermark_config& dst);
  WindUpCallback convertToCsdkStruct(const NERtcChannelMediaRelayConfiguration& src, nertc_channel_media_relay_config& dst);
  void convertToCsdkStruct(const NERtcVideoFrame& src, nertc_video_frame& dst);
  void convertToCsdkStruct(const NERtcAudioFrameRequestFormat& src, nertc_audio_frame_request_format& dst);
  void convertToCsdkStruct(const NERtcCreateAudioMixingOption& src, nertc_create_audio_mixing_option& dst);
  void convertToCsdkStruct(const NERtcCreateAudioEffectOption& src, nertc_create_audio_effect_option& dst);
  void convertToCsdkStruct(const NERtcAudioFrame& src, nertc_audio_frame& dst);
  void convertToCsdkStruct(const NERtcEncryptionConfig& src, nertc_encryption_config& dst);
  void convertToCsdkStruct(const NERtcLastmileProbeConfig& src, nertc_lastmile_probe_config& dst);
  void convertToCsdkStruct(const NERtcPositionInfo& src, nertc_position_info& dst);
  void convertToCsdkStruct(const NERtcSpatializerRoomProperty& src, nertc_spatializer_room_property& dst);

  //////////////////////////////nertc struct to csdk struce//////////////////////////////
  void convertToNertcStruct(const nertc_device_info& src, NERtcDeviceInfo& dst);
  void convertToNertcStruct(const nertc_user_join_extra_info& src, NERtcUserJoinExtraInfo& dst);
  WindUpCallback convertToNertcStruct(const nertc_audio_volume_info* src, uint32_t speaker_number, NERtcAudioVolumeInfo*& dst);
  void convertToNertcStruct(const nertc_camera_focus_and_exposure_info& src, NERtcCameraFocusAndExposureInfo& dst);
  void convertToNertcStruct(const nertc_lastmile_probe_result& src, NERtcLastmileProbeResult& dst);
  void convertToNertcStruct(const nertc_audio_frame& src, NERtcAudioFrame& dst);
  void convertToNertcStruct(const nertc_stats& src, NERtcStats& dst);
  WindUpCallback convertToNertcStruct(const nertc_audio_send_stats& src, NERtcAudioSendStats& dst);
  WindUpCallback convertToNertcStruct(const nertc_audio_recv_stats* src, unsigned int user_count, NERtcAudioRecvStats*& dst);
  WindUpCallback convertToNertcStruct(const nertc_video_send_stats& src, NERtcVideoSendStats& dst);
  WindUpCallback  convertToNertcStruct(const nertc_video_recv_stats* src_list, unsigned int user_count, NERtcVideoRecvStats*& dst_list);
  void convertToNertcStruct(const nertc_network_quality_info& src, NERtcNetworkQualityInfo& dst);

}