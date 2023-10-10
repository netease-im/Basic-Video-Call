/** @file NertcEngineEx.h
 * @brief The interface header file of expansion NERTC UE SDK.
 * All parameter descriptions of the NERTC UE SDK. All string-related parameters (char *) are encoded in UTF-8.
 * @copyright (c) 2015-2022, NetEase Inc. All rights reserved.
 */

#pragma once

#include "INertcEngineEx.h"
#include "INertcMediaStatsObserver.h"
#include <string>
#include <condition_variable>
#include <mutex>

struct nertc_engine;
struct nertc_engine_events;
struct nertc_media_stats_observer;
struct nertc_audio_frame_observer;

namespace nertc {
  class NertcEngineEx :public IRtcEngineEx {
  public:
    NertcEngineEx() = delete;
    NertcEngineEx(const NertcEngineEx& other);
    NertcEngineEx(NertcEngineEx&& other) noexcept;
    NertcEngineEx& operator=(const NertcEngineEx& other);
    NertcEngineEx& operator=(NertcEngineEx&& other) noexcept;

    virtual ~NertcEngineEx();
    NertcEngineEx(nertc_engine*);
  public:
    ////////////////////////////////////////////////////////////////
    int initialize(const NERtcEngineContext& context) override;

    void release(bool sync = false) override;

    int setClientRole(NERtcClientRole role) override;

    int setChannelProfile(NERtcChannelProfileType profile) override;

    int joinChannel(const char* token, const char* channel_name, uid_t uid, const NERtcJoinChannelOptions& channel_options) override;

    int switchChannel(const char* token, const char* channel_name, const NERtcJoinChannelOptions& channel_options) override;

    int switchChannelEx(const char* token, const char* channel_name, uid_t uid, const NERtcJoinChannelOptionsEx& channel_options) override;

    int leaveChannel() override;

    int queryInterface(NERtcInterfaceIdType iid, void** inter) override;

    int enableLocalAudio(NERtcAudioStreamType type, bool enabled) override;

    //////////////////////////////////////////////////////////////
    NERtcConnectionStateType getConnectionState() override;

    int muteLocalAudioStream(NERtcAudioStreamType type, bool mute) override;

    int setAudioProfile(NERtcAudioProfileType profile, NERtcAudioScenarioType scenario) override;

    int setAudioEffectPreset(NERtcVoiceChangerType type) override;

    int setVoiceBeautifierPreset(NERtcVoiceBeautifierType type) override;

    int setLocalVoicePitch(double pitch) override;

    int setLocalVoiceEqualization(NERtcVoiceEqualizationBand band_frequency, int band_gain) override;
    
    int subscribeRemoteAudioStream(NERtcAudioStreamType stream_type, uid_t uid, bool subscribe) override;
    
    int subscribeAllRemoteAudioStream(bool subscribe) override;

    int setPublishAudioAllowList(uid_t* uid_array, uint32_t size) override;

    int setSubscribeAudioAllowList(uid_t* uid_array, uint32_t size) override;

    int setSubscribeAudioBlockList(uid_t* uid_array, uint32_t size) override;

    int setAudioSessionOperationRestriction(NERtcAudioSessionOperationRestriction restriction) override;

    int setAudioFocusMode(NERtcAudioFocusMode focus_mode) override;

    int setPlayoutDeviceMute(bool muted);

    int getPlayoutDeviceMute(bool* muted);

    int setParameters(const char* parameters) override;

    int setAudioFrameObserver(INERtcAudioFrameObserver* observer) override;

    int startAudioDump(NERtcAudioDumpType type) override;

    int stopAudioDump() override;

    int setLoudspeakerMode(bool enable) override;

    int getLoudspeakerMode(bool* enabled) override;
    
    int setStatsObserver(IRtcMediaStatsObserver* observer) override;

    int enableAudioVolumeIndication(bool enable, uint64_t interval, bool enable_vad) override;

    const char* getVersion(int* build) override;

    const char* getErrorDescription(int error_code) override;

    void uploadSdkInfo() override;

    int adjustRecordingSignalVolume(int volume) override;

    int adjustPlaybackSignalVolume(int volume) override;

    int enableMediaPublish(bool enabled, NERtcMediaPubType media_type) override;

    int setRangeAudioMode(NERtcRangeAudioMode mode) override;

    int setRangeAudioTeamID(int32_t team_id) override;

    int setAudioRecvRange(int audible_distance, int conversational_distance, NERtcDistanceRolloffModel roll_off) override;

    int updateSelfPosition(const NERtcPositionInfo& info) override;

    int initSpatializer() override;

    int enableSpatializer(bool enable) override;

    int getMicrophoneMode(bool* enabled) override;

    int getRecordingSignalVolume() override;

    int getPlaybackSignalVolume() override;

    bool checkMicPermision() override;

    int pauseAudio() override;

    int resumeAudio() override;

    bool isInChannel() override;

    bool acquireAndroidRecordingPermissions() override;
  private:
	  void fillCsdkEventHandler(IRtcEngineEventHandler* handler);
    void clearCsdkEventHandler();
    void fillCsdkAudioFrameObserver(INERtcAudioFrameObserver* observer);
    void clearCsdkAudioFrameObserver();
    void fillCsdkMediaStatsObserver(IRtcMediaStatsObserver* observer);
    void clearCsdkMediaStatsObserver();
    nertc_engine* m_nertc_engine{ nullptr };
    nertc_engine_events* m_nertc_engine_event{ nullptr };
    nertc_audio_frame_observer* m_nertc_audio_frame_observer{ nullptr };
    nertc_media_stats_observer* m_nertc_media_stats_observer{ nullptr };
    std::condition_variable_any m_sleep_condition;
    std::recursive_mutex m_sleep_condition_mutex;
  };
}