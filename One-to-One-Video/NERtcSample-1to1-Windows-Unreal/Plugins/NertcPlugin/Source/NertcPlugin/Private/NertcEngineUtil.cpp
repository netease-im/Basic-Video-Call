// Copyright Epic Games, Inc. All Rights Reserved.

#include "NertcEngineUtil.h"

namespace nertc {
    //////////////////////////////csdk struct to nertc struce//////////////////////////////
    void convertToCsdkStruct(const NERtcJoinChannelOptions& src, nertc_join_channel_options& dst) {
      memcpy(dst.custom_info, src.custom_info, kNERtcCustomInfoLength);
      dst.permission_key = src.permission_key;
      dst.team_id = src.team_id;
      dst.mode = (nertc_range_audio_mode)src.mode;
      dst.audible_distance = src.audible_distance;
    }
    void convertToCsdkStruct(const NERtcJoinChannelOptionsEx& src, nertc_join_channel_options_ex& dst) {
        memcpy(dst.custom_info, src.custom_info, kNERtcCustomInfoLength);
        dst.permission_key = src.permission_key;
        dst.team_id = src.team_id;
        dst.mode = (nertc_range_audio_mode)src.mode;
        dst.audible_distance = src.audible_distance;
    }
    void convertToCsdkStruct(const NERtcRectangle& src, nertc_rectangle& dst) {
        dst.x = src.x;
        dst.y = src.y;
        dst.width = src.width;
        dst.height = src.height;
    }
    void convertToCsdkStruct(const NERtcScreenCaptureParameters& src, nertc_screen_capture_parameters& dst){
        dst.profile = (nertc_screen_profile_type)src.profile;
        dst.dimensions.width = src.dimensions.width;
        dst.dimensions.height = src.dimensions.height;
        dst.frame_rate = src.frame_rate;
        dst.bitrate = src.bitrate;
        dst.capture_mouse_cursor = src.capture_mouse_cursor;
        dst.window_focus = src.window_focus;
        dst.excluded_window_count = src.excluded_window_count;
        dst.excluded_window_list = new source_id_t[src.excluded_window_count];
        for (int i = 0; i < src.excluded_window_count; i++) {
            dst.excluded_window_list[i] = src.excluded_window_list[i];
        }
        dst.prefer = (nertc_sub_stream_content_prefer)src.prefer;
        //warn: need delete excluded_window_list
    }
    void convertToCsdkStruct(const NERtcVideoCanvas& src, nertc_video_canvas& dst){
        dst.cb = src.cb;
        dst.user_data = src.user_data;
        dst.window = src.window;
        dst.scaling_mode = (nertc_video_scaling_mode)src.scaling_mode;
    }
    void convertToCsdkStruct(const NERtcCameraCaptureConfig& src, nertc_camera_capture_config& dst){
        //dst.preference = (nertc_camera_preference)src.preference;
        dst.capture_width = src.capture_width;
        dst.capture_height = src.capture_height;
    }
    void convertToCsdkStruct(const NERtcVideoConfig& src, nertc_video_config& dst){
        dst.max_profile = (nertc_video_profile_type)src.max_profile;
        dst.width = src.width;
        dst.height = src.height;
        dst.crop_mode_ = (nertc_video_crop_mode)src.crop_mode; //TODO rename csdk + nertc sdk
        dst.framerate = (nertc_video_framerate_type)src.framerate;
        dst.min_framerate = (nertc_video_framerate_type)src.min_framerate;
        dst.bitrate = src.bitrate;
        dst.min_bitrate = src.min_bitrate;
        dst.degradation_preference = (nertc_degradation_preference)src.degradation_preference;
        dst.mirror_mode = (nertc_video_mirror_mode)src.mirror_mode;
        dst.orientation_mode = (nertc_video_orientation_mode)src.orientation_mode;
    }
    void convertToCsdkStruct(const NERtcLiveStreamLayout& src, nertc_live_stream_layout& dst) {

        dst.width = src.width;
        dst.height = src.height;
        dst.background_color = src.background_color;
        dst.user_count = src.user_count;

        dst.users = new nertc_live_stream_user_transcoding[src.user_count];
        for (unsigned int i = 0; i < src.user_count; i++) {
            dst.users[i].uid = src.users[i].uid;
            dst.users[i].video_push = src.users[i].video_push;
            dst.users[i].adaption = (nertc_live_stream_video_scale_mode)src.users[i].adaption;
            dst.users[i].x = src.users[i].x;
            dst.users[i].y = src.users[i].y;
            dst.users[i].width = src.users[i].width;
            dst.users[i].height = src.users[i].height;
            dst.users[i].audio_push = src.users[i].audio_push;
            dst.users[i].z_order = src.users[i].z_order;
        }
    }
    void convertToCsdkStruct(const NERtcLiveConfig& src, nertc_live_stream_config& dst) {
      dst.audioCodecProfile = (nertc_live_stream_audio_sample_rate)src.audioCodecProfile;
      dst.audio_bitrate = src.audio_bitrate;
      dst.channels = src.channels;
      dst.sampleRate = (nertc_live_stream_audio_sample_rate)src.sampleRate;
      dst.single_video_passthrough = src.single_video_passthrough;
    }
    WindUpCallback convertToCsdkStruct(const NERtcLiveStreamTaskInfo& src, nertc_live_stream_task_info& dst){
        memcpy(dst.task_id, src.task_id, kNERtcMaxTaskIDLength);
        memcpy(dst.stream_url, src.stream_url, kNERtcMaxURILength);
        dst.server_record_enabled = src.server_record_enabled;
        dst.ls_mode = (nertc_live_stream_mode)src.ls_mode;
        convertToCsdkStruct(src.layout, dst.layout);
        convertToCsdkStruct(src.config, dst.config);
        memcpy(dst.extra_info, src.extra_info, kNERtcMaxSEIBufferLength);
        
        return [dst]() {
          delete[] dst.layout.users;
        };
    }
    void convertToCsdkStruct(const NERtcVideoWatermarkConfig& src, nertc_video_watermark_config& dst){
        //TODO 后面升级到编码水印
    }
    WindUpCallback convertToCsdkStruct(const NERtcChannelMediaRelayConfiguration& src, nertc_channel_media_relay_config& dst){
      auto convert_relay_info = [](const NERtcChannelMediaRelayInfo& src, nertc_channel_media_relay_info& dst) {
        memcpy((void*)dst.channel_name, src.channel_name, kNERtcMaxChannelNameLength);
        memcpy((void*)dst.channel_token, src.channel_token, kNERtcMaxChannelNameLength);
        dst.uid = src.uid;
      };
      dst.dest_count = src.dest_count;

      dst.dest_infos = new nertc_channel_media_relay_info[dst.dest_count]{};
      for(int i = 0; i < dst.dest_count; i++){
        convert_relay_info(src.dest_infos[i], dst.dest_infos[i]);
      }

      dst.src_infos = new nertc_channel_media_relay_info{};
      convert_relay_info(*src.src_infos, *dst.src_infos);

      return [dst]() {
        delete[] dst.dest_infos;
        delete dst.src_infos;
      };
    }
    void convertToCsdkStruct(const NERtcVideoFrame& src, nertc_video_frame& dst){
      dst.buffer = src.buffer;
      dst.format = (nertc_video_type)src.format;
      dst.height = src.height;
      dst.rotation = (nertc_video_rotation)src.rotation;
      dst.timestamp = src.timestamp;
    }
    void convertToCsdkStruct(const NERtcAudioFrameRequestFormat& src, nertc_audio_frame_request_format& dst){
      dst.channels = src.channels;
      dst.mode = (nertc_raw_audio_frame_op_mode_type)src.mode;
      dst.sample_rate = src.sample_rate;
    }
    void convertToCsdkStruct(const NERtcCreateAudioMixingOption& src, nertc_create_audio_mixing_option& dst){
      memcpy(dst.path, src.path, kNERtcMaxURILength);
      dst.loop_count = src.loop_count;
      dst.playback_enabled = src.playback_enabled;
      dst.playback_volume = src.playback_volume;
      dst.send_enabled = src.send_enabled;
      dst.send_volume = src.send_volume;
    }
    void convertToCsdkStruct(const NERtcCreateAudioEffectOption& src, nertc_create_audio_effect_option& dst){
      memcpy(dst.path, src.path, kNERtcMaxURILength);
      dst.loop_count = src.loop_count;
      dst.playback_enabled = src.playback_enabled;
      dst.playback_volume = src.playback_volume;
      dst.send_enabled = src.send_enabled;
      dst.send_volume = src.send_volume;
    }
    void convertToCsdkStruct(const NERtcAudioFrame& src, nertc_audio_frame& dst){
      dst.data = src.data;
      dst.format.type = (nertc_audio_type)src.format.type;
      dst.format.channels = src.format.channels;
      dst.format.sample_rate = src.format.sample_rate;
      dst.format.bytes_per_sample = src.format.bytes_per_sample;
      dst.format.samples_per_channel = src.format.samples_per_channel;
    }
    void convertToCsdkStruct(const NERtcEncryptionConfig& src, nertc_encryption_config& dst){
      memcpy(dst.key, src.key, kNERtcEncryptByteLength);
      dst.mode = (nertc_encryption_mode)src.mode;
    }
    void convertToCsdkStruct(const NERtcLastmileProbeConfig& src, nertc_lastmile_probe_config& dst){
      dst.expected_downlink_bitratebps = src.expected_downlink_bitratebps;
      dst.expected_uplink_bitratebps = src.expected_uplink_bitratebps;
      dst.probe_downlink = src.probe_downlink;
      dst.probe_uplink = src.probe_uplink;
    }
    void convertToCsdkStruct(const NERtcPositionInfo& src, nertc_position_info& dst){
      memcpy(dst.speaker_position, src.speaker_position, sizeof(src.speaker_position));
      memcpy(dst.speaker_quaternion, src.speaker_quaternion, sizeof(src.speaker_quaternion));
      memcpy(dst.head_position, src.head_position, sizeof(src.head_position));
      memcpy(dst.head_quaternion, src.head_quaternion, sizeof(src.head_quaternion));
    }
    void convertToCsdkStruct(const NERtcSpatializerRoomProperty& src, nertc_spatializer_room_property& dst){
      dst.material = (nertc_spatializer_material_name)src.material;
      dst.reflection_scalar = src.reflection_scalar;
      dst.reverb_brightness = src.reverb_brightness;
      dst.reverb_gain = src.reverb_gain;
      dst.reverb_time = src.reverb_time;
      dst.room_capacity = (nertc_spatializer_room_capacity)src.room_capacity;
    }


    //////////////////////////////nertc struct to csdk struce//////////////////////////////
    void convertToNertcStruct(const nertc_device_info& src, NERtcDeviceInfo& dst) {
      memcpy(dst.device_id, src.device_id, kNERtcMaxDeviceIDLength);
      memcpy(dst.device_name, src.device_name, kNERtcMaxDeviceNameLength);
      dst.transport_type = src.transport_type;
      dst.suspected_unavailable = src.suspected_unavailable;
      dst.system_default_device = src.system_default_device;
    }
    void convertToNertcStruct(const nertc_user_join_extra_info& src, NERtcUserJoinExtraInfo& dst) {
      memcpy(dst.custom_info, src.custom_info, kNERtcCustomInfoLength);
    }
    WindUpCallback convertToNertcStruct(const nertc_audio_volume_info* src, uint32_t speaker_number, NERtcAudioVolumeInfo*& dst) {
      if (!src) {
        return []() {};
      }
      dst = new NERtcAudioVolumeInfo[speaker_number];
      for (uint32_t i = 0; i < speaker_number; i++) {
        dst[i].uid = src[i].uid;
        dst[i].volume = src[i].volume;
        dst[i].sub_stream_volume = src[i].sub_stream_volume;
      }
      return [dst]() {
        delete[] dst;
      };
    }
    void convertToNertcStruct(const nertc_camera_focus_and_exposure_info& src, NERtcCameraFocusAndExposureInfo& dst) {
      dst.center_x = src.center_x;
      dst.center_y = src.center_y;
      dst.left = src.left;
      dst.top = src.top;
      dst.right = src.right;
      dst.bottom = src.bottom;
    }
    void convertToNertcStruct(const nertc_lastmile_probe_result& src, NERtcLastmileProbeResult& dst) {
      dst.downlink_report.available_band_width = src.downlink_report.available_band_width;
      dst.downlink_report.jitter = src.downlink_report.jitter;
      dst.downlink_report.packet_loss_rate = src.downlink_report.packet_loss_rate;

      dst.rtt = src.rtt;
      dst.state = (NERtcLastmileProbeResultState)src.state;

      dst.uplink_report.available_band_width = src.uplink_report.available_band_width;
      dst.uplink_report.jitter = src.uplink_report.jitter;
      dst.uplink_report.packet_loss_rate = src.uplink_report.packet_loss_rate;
    }
    void convertToNertcStruct(const nertc_audio_frame& src, NERtcAudioFrame& dst) {
      dst.data = src.data;
      dst.format.type = (NERtcAudioType)src.format.type;
      dst.format.channels = src.format.channels;
      dst.format.sample_rate = src.format.sample_rate;
      dst.format.bytes_per_sample = src.format.bytes_per_sample;
      dst.format.samples_per_channel = src.format.samples_per_channel;
    }
    void convertToNertcStruct(const nertc_stats& src, NERtcStats& dst) {
      dst.cpu_app_usage = src.cpu_app_usage;
      dst.cpu_idle_usage = src.cpu_idle_usage;
      dst.cpu_total_usage = src.cpu_total_usage;
      dst.memory_app_usage = src.memory_app_usage;
      dst.memory_total_usage = src.memory_total_usage;
      dst.memory_app_kbytes = src.memory_app_kbytes;
      dst.total_duration = src.total_duration;
      dst.tx_bytes = src.tx_bytes;
      dst.rx_bytes = src.rx_bytes;
      dst.tx_audio_bytes = src.tx_audio_bytes;
      dst.tx_video_bytes = src.tx_video_bytes;
      dst.rx_audio_bytes = src.rx_audio_bytes;
      dst.rx_video_bytes = src.rx_video_bytes;
      dst.tx_audio_kbitrate = src.tx_audio_kbitrate;
      dst.rx_audio_kbitrate = src.rx_audio_kbitrate;
      dst.tx_video_kbitrate = src.tx_video_kbitrate;
      dst.rx_video_kbitrate = src.rx_video_kbitrate;
      dst.up_rtt = src.up_rtt;
      dst.down_rtt = src.down_rtt;
      dst.tx_audio_packet_loss_rate = src.tx_audio_packet_loss_rate;
      dst.tx_video_packet_loss_rate = src.tx_video_packet_loss_rate;
      dst.tx_audio_packet_loss_sum = src.tx_audio_packet_loss_sum;
      dst.tx_video_packet_loss_sum = src.tx_video_packet_loss_sum;
      dst.tx_audio_jitter = src.tx_audio_jitter;
      dst.tx_video_jitter = src.tx_video_jitter;
      dst.rx_audio_packet_loss_rate = src.rx_audio_packet_loss_rate;
      dst.rx_video_packet_loss_rate = src.rx_video_packet_loss_rate;
      dst.rx_audio_packet_loss_sum = src.rx_audio_packet_loss_sum;
      dst.rx_video_packet_loss_sum = src.rx_video_packet_loss_sum;
      dst.rx_audio_jitter = src.rx_audio_jitter;
      dst.rx_video_jitter = src.rx_video_jitter;
    }
    WindUpCallback convertToNertcStruct(const nertc_audio_send_stats& src, NERtcAudioSendStats& dst) {
      dst.audio_layers_list = new NERtcAudioLayerSendStats[src.audio_layers_count];
      dst.audio_layers_count = src.audio_layers_count;
      for (size_t i = 0; i < src.audio_layers_count; i++) {
        dst.audio_layers_list[i].stream_type = (NERtcAudioStreamType)src.audio_layers_list[i].stream_type;
        dst.audio_layers_list[i].num_channels = src.audio_layers_list[i].num_channels;
        dst.audio_layers_list[i].sent_sample_rate = src.audio_layers_list[i].sent_sample_rate;
        dst.audio_layers_list[i].sent_bitrate = src.audio_layers_list[i].sent_bitrate;
        dst.audio_layers_list[i].audio_loss_rate = src.audio_layers_list[i].audio_loss_rate;
        dst.audio_layers_list[i].rtt = src.audio_layers_list[i].rtt;
        dst.audio_layers_list[i].volume = src.audio_layers_list[i].volume;
        dst.audio_layers_list[i].cap_volume = src.audio_layers_list[i].cap_volume;
      }
      return [dst]() {
        delete[] dst.audio_layers_list;
      };
    }
    WindUpCallback convertToNertcStruct(const nertc_audio_recv_stats* src, unsigned int user_count, NERtcAudioRecvStats*& dst) {
      dst = new NERtcAudioRecvStats[user_count];
      for (size_t i = 0; i < user_count; i++) {
        dst[i].uid = src[i].uid;
        dst[i].audio_layers_list = new NERtcAudioLayerRecvStats[src[i].audio_layers_count];
        dst[i].audio_layers_count = src[i].audio_layers_count;
        for (size_t j = 0; j < src[i].audio_layers_count; j++) {
          dst[i].audio_layers_list[j].stream_type = (NERtcAudioStreamType)src[i].audio_layers_list[j].stream_type;
          dst[i].audio_layers_list[j].received_bitrate = src[i].audio_layers_list[j].received_bitrate;
          dst[i].audio_layers_list[j].total_frozen_time = src[i].audio_layers_list[j].total_frozen_time;
          dst[i].audio_layers_list[j].frozen_rate = src[i].audio_layers_list[j].frozen_rate;
          dst[i].audio_layers_list[j].audio_loss_rate = src[i].audio_layers_list[j].audio_loss_rate;
          dst[i].audio_layers_list[j].volume = src[i].audio_layers_list[j].volume;
        }
      }
      return [dst, user_count]() {
        for (size_t i = 0; i < user_count; i++) {
          delete[] dst[i].audio_layers_list;
        }
        delete[] dst;
      };
    }
    WindUpCallback convertToNertcStruct(const nertc_video_send_stats& src, NERtcVideoSendStats& dst) {
      auto convertVideoLayerSendStats = [](const nertc_video_layer_send_stats& src, NERtcVideoLayerSendStats& dst) {
        dst.layer_type = src.layer_type;
        dst.width = src.width;
        dst.height = src.height;
        dst.capture_width = src.capture_width;
        dst.capture_height = src.capture_height;
        dst.capture_frame_rate = src.capture_frame_rate;
        dst.render_frame_rate = src.render_frame_rate;
        dst.encoder_frame_rate = src.encoder_frame_rate;
        dst.sent_frame_rate = src.sent_frame_rate;
        dst.sent_bitrate = src.sent_bitrate;
        dst.target_bitrate = src.target_bitrate;
        dst.encoder_bitrate = src.encoder_bitrate;
        memcpy(dst.codec_name, src.codec_name, kNERtcMaxDeviceNameLength);
      };
      dst.video_layers_count = src.video_layers_count;
      dst.video_layers_list = new NERtcVideoLayerSendStats[dst.video_layers_count]{};
      for (int i = 0; i < dst.video_layers_count; i++) {
        convertVideoLayerSendStats(src.video_layers_list[i], dst.video_layers_list[i]);
      }

      return [dst]() {
        delete[] dst.video_layers_list;
      };
    }
    WindUpCallback convertToNertcStruct(const nertc_video_recv_stats* src_list, unsigned int user_count, NERtcVideoRecvStats*& dst_list) {
      auto convertVideoLayerRecvStats = [](const nertc_video_layer_recv_stats& src, NERtcVideoLayerRecvStats& dst) {
        dst.layer_type = src.layer_type;
        dst.width = src.width;
        dst.height = src.height;
        dst.received_bitrate = src.received_bitrate;
        dst.received_frame_rate = src.received_frame_rate;
        dst.decoder_frame_rate = src.decoder_frame_rate;
        dst.render_frame_rate = src.render_frame_rate;
        dst.packet_loss_rate = src.packet_loss_rate;
        dst.total_frozen_time = src.total_frozen_time;
        dst.frozen_rate = src.frozen_rate;
        memcpy(dst.codec_name, src.codec_name, kNERtcMaxDeviceNameLength);
      };
      dst_list = new NERtcVideoRecvStats[user_count]{};
      for (unsigned int i = 0; i < user_count; i++) {
        dst_list[i].uid = src_list[i].uid;
        dst_list[i].video_layers_count = src_list[i].video_layers_count;
        dst_list[i].video_layers_list = new NERtcVideoLayerRecvStats[dst_list[i].video_layers_count]{};
        for (int j = 0; j < dst_list[j].video_layers_count; j++) {
          convertVideoLayerRecvStats(src_list[i].video_layers_list[j], dst_list[i].video_layers_list[j]);
        }
      }
      
      return [dst_list, user_count]() {
        for (unsigned int i = 0; i < user_count; i++) {
          delete[] dst_list[i].video_layers_list;
        }
        delete[] dst_list;
      };
    }
    void convertToNertcStruct(const nertc_network_quality_info& src, NERtcNetworkQualityInfo& dst) {
      dst.rx_quality = (NERtcNetworkQualityType)src.rx_quality;
      dst.tx_quality = (NERtcNetworkQualityType)src.tx_quality;
      dst.uid = src.uid;
    }
}