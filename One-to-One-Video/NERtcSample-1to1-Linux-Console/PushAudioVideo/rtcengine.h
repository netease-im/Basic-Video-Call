#ifndef RTCENGINE_H
#define RTCENGINE_H

#include "nertc_engine_defines.h"
#include "nertc_engine_event_handler_ex.h"
#include "nertc_engine_ex.h"
#include "nertc_video_device_manager.h"
#include "nertc_engine_video_encoder_qos_observer.h"
#include "pushexternalh264video.h"
#include "pushexternalyuvvideo.h"
#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>


using namespace nertc;

class RtcEngine 
: IRtcEngineEventHandlerEx
, INERtcAudioFrameObserver
, INERtcVideoEncoderQosObserver
{
public:
    static void onFrameDataCallback(
        nertc::uid_t uid,               /**< The user ID. */
        void *data,              /**< The data pointer. */
        uint32_t type,           /**< NERtcVideoType. */
        uint32_t width,          /**< The width. */
        uint32_t height,         /**< The height. */
        uint32_t count,          /**< The number of data types, including the number of offset and stride. */
        uint32_t offset[4],      /**< The data offset. */
        uint32_t stride[4],      /**< The data step. */
        uint32_t rotation,       /**< NERtcVideoRotation. */
        void *user_data          /**< User transparent transmission data. */
    );

    RtcEngine();

    ~RtcEngine();

    int initialize(const std::string &appkey, const std::string &logdir);

public:
    // INERtcAudioFrameObserver
    virtual void onAudioFrameDidRecord(NERtcAudioFrame *frame) override;
    virtual void onSubStreamAudioFrameDidRecord(NERtcAudioFrame* frame) override;
    virtual void onAudioFrameWillPlayback(NERtcAudioFrame *frame) override;
    virtual void onMixedAudioFrame(NERtcAudioFrame * frame) override;
    virtual void onPlaybackAudioFrameBeforeMixing(uint64_t userID, NERtcAudioFrame* frame) override;
    virtual void onPlaybackAudioFrameBeforeMixing(uint64_t userID, NERtcAudioFrame* frame, channel_id_t cid) override {}
    virtual void onPlaybackSubStreamAudioFrameBeforeMixing(uint64_t userID, NERtcAudioFrame* frame,
                                                           channel_id_t cid) override {}

    // INERtcVideoEncoderQosObserver
    virtual void onRequestSendKeyFrame(NERtcVideoStreamType video_stream_type) override;
    virtual void onBitrateUpdated(uint32_t bitrate_bps, NERtcVideoStreamType video_stream_type) override;
    virtual void onVideoCodecUpdated(NERtcVideoCodecType video_codec_type, NERtcVideoStreamType video_stream_type) override;

    // IRtcEngineEventHandlerEx
    virtual void onError(int error_code, const char* msg) override;
    virtual void onWarning(int error_code, const char* msg) override;
    virtual void onReleasedHwResources(NERtcErrorCode result) override;
    virtual void onReconnectingStart(channel_id_t cid, nertc::uid_t uid) override;
    virtual void onConnectionStateChange(NERtcConnectionStateType state, NERtcReasonConnectionChangedType reason) override;
    virtual void onJoinChannel(channel_id_t cid, nertc::uid_t uid, NERtcErrorCode result, uint64_t elapsed) override;
    virtual void onRejoinChannel(channel_id_t cid, nertc::uid_t uid, NERtcErrorCode result, uint64_t elapsed) override;
    virtual void onLeaveChannel(NERtcErrorCode result) override;
    virtual void onDisconnect(NERtcErrorCode reason) override;
    virtual void onClientRoleChanged(NERtcClientRole oldRole, NERtcClientRole newRole) override;
    virtual void onUserJoined(nertc::uid_t uid, const char * user_name) override;
    virtual void onUserLeft(nertc::uid_t uid, NERtcSessionLeaveReason reason) override;
    virtual void onUserAudioStart(nertc::uid_t uid) override;
    virtual void onUserAudioStop(nertc::uid_t uid) override;
    virtual void onUserVideoStart(nertc::uid_t uid, NERtcVideoProfileType max_profile) override;
    virtual void onUserVideoStop(nertc::uid_t uid) override;

    // API
    std::string getVersion();
    int setParameters(const char *parameters);
    int queryInterface(NERtcInterfaceIdType iid, void ** inter );
    int joinChannel(std::string token, std::string channel_name, uint64_t uid);
    void leaveChannel();
    void release();
    void enableLocalVideo(bool enable);
    void enableLocalAudio(bool enable);
    int setAudioFrameObserver();
    int setVideoEncoderQosObserver();

    // push video
    int setExternalVideoSource(bool enabled);
    int pushExternalVideoFrame(NERtcVideoFrame* frame);
    int pushExternalVideoEncodedFrame(NERtcVideoStreamType type, NERtcVideoEncodedFrame* frame);

    // push audio
    int setExternalAudioSource(bool enabled, int sample_rate, int channels);
    int pushExternalAudioFrame(NERtcAudioFrame* frame);
    
    // pull audio - audio frame callback by INERtcAudioFrameObserver
    int setExternalAudioRender(bool enabled, int sample_rate, int channels);
    int pullExternalAudioFrame(void* data, int len);

    // simucast
    int enableDualStreamMode(bool enable);

private:
    IRtcEngineEx *m_engine = nullptr;
    std::atomic_bool stopFlag;
    PushExternalH264Video pushExternalH264Video;
    PushExternalYUVVideo pushExternalYUVVideo;

public:
    void setAVConfig(
        const std::string &audio_pcm_file_,
        int audio_sample_rate_,
        int audio_channels_,
        int videotype_,
        const std::string &video_h264_file_,
        const std::string &video_yuv_file_,
        int video_fps_,
        int video_width_, 
        int video_height_
    );

private:
    int         videotype;
    std::string audio_pcm_file;
    int         audio_sample_rate;
    int         audio_channels;
};

#endif