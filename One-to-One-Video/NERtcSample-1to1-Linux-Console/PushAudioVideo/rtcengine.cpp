#include "rtcengine.h"

using namespace std::chrono;

void RtcEngine::onFrameDataCallback(
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
)
{
    static int64_t cnt = 0;
    if (cnt++ % 10 == 0) {
        std::cout << "uid = " << uid << " w*h = " << width << "*" << height << std::endl;
    }
}

RtcEngine::RtcEngine()
: stopFlag(false)
, pushExternalH264Video(*this)
, pushExternalYUVVideo(*this)
{
    m_engine = (IRtcEngineEx *)createNERtcEngine();
    if (m_engine == nullptr) {
        std::cerr << "createNERtcEngine error" << std::endl;
    }
}

int RtcEngine::initialize(const std::string &appkey, const std::string &logdir)
{

    if (m_engine == nullptr) {
        std::cerr << "initialize failed as m_engine is nullptr" << std::endl;
        return -1;
    }
    NERtcEngineContext context;
    if (appkey.empty()) {
        std::cerr << "APPKEY is null" << std::endl;
        return -1;
    }
    context.app_key = appkey.c_str();
    context.log_dir_path = logdir.c_str();
    context.log_level = kNERtcLogLevelInfo;
    context.event_handler = this;
    memset(&context.server_config, 0, sizeof(context.server_config));
    auto ret = m_engine->initialize(context);
    if (ret != kNERtcNoError) {
        std::cerr << "initialize error " << ret << std::endl;
        return ret;
    }

    NERtcVideoCanvas canvas;
    canvas.cb = RtcEngine::onFrameDataCallback;
    canvas.window = nullptr;
    canvas.user_data = this;

    ret = m_engine->setupLocalVideoCanvas(&canvas);
    if (ret != kNERtcNoError) {
        std::cerr << "setupLocalVideoCanvas error " << ret << std::endl;
        return ret;
    } else {
        std::cout << "setupLocalVideoCanvas successful" << std::endl;
    }

    return 0;
}

 void RtcEngine::setAVConfig(
        const std::string &audio_pcm_file_,
        int audio_sample_rate_,
        int audio_channels_,
        int videotype_,
        const std::string &video_h264_file_,
        const std::string &video_yuv_file_,
        int video_fps_,
        int video_width_, 
        int video_height_
    )
{
    audio_pcm_file = audio_pcm_file_;
    audio_sample_rate = audio_sample_rate_;
    audio_channels = audio_channels_;
    videotype = videotype_;

    if (videotype == 0) { //file
        pushExternalH264Video.setVideoConfig(video_h264_file_, video_fps_, video_width_, video_height_);
    } else if (videotype == 1) { //yuv
        pushExternalYUVVideo.setVideoConfig(video_yuv_file_, video_fps_, video_width_, video_height_);
    }
}

RtcEngine::~RtcEngine()
{
    if (m_engine) {
        destroyNERtcEngine((void *&)m_engine);
    }
}

// INERtcAudioFrameObserver
void RtcEngine::onAudioFrameDidRecord(NERtcAudioFrame *frame)
{
    // std::cout << "<>" << __func__ << " " << "sample_rate = " << frame->format.sample_rate << 
    //     " channels = " << frame->format.channels << ", samples_per_channel = " << frame->format.samples_per_channel << std::endl;
}

void RtcEngine::onSubStreamAudioFrameDidRecord(NERtcAudioFrame* frame)
{
    // std::cout << "<>" << __func__ << " " << "sample_rate = " << frame->format.sample_rate << 
    //     " channels = " << frame->format.channels << ", samples_per_channel = " << frame->format.samples_per_channel << std::endl;
}

void RtcEngine::onAudioFrameWillPlayback(NERtcAudioFrame *frame)
{
    // std::cout << "<>" << __func__ << " " << "sample_rate = " << frame->format.sample_rate << 
    //     " channels = " << frame->format.channels << ", samples_per_channel = " << frame->format.samples_per_channel << std::endl;
}

void RtcEngine::onMixedAudioFrame(NERtcAudioFrame * frame)
{
    // std::cout << "<>" << __func__ << " " << "sample_rate = " << frame->format.sample_rate << 
    //     " channels = " << frame->format.channels << ", samples_per_channel = " << frame->format.samples_per_channel << std::endl;
}

void RtcEngine::onPlaybackAudioFrameBeforeMixing(uint64_t userID, NERtcAudioFrame* frame)
{
    // std::cout << "<>" << __func__ << " " << "sample_rate = " << frame->format.sample_rate << 
    //     " channels = " << frame->format.channels << ", samples_per_channel = " << frame->format.samples_per_channel << ", uid = " << userID << std::endl;
}

// INERtcVideoEncoderQosObserver
void RtcEngine::onRequestSendKeyFrame(NERtcVideoStreamType video_stream_type)
{
    std::cout << "<>" << __func__ << " " << "video_stream_type = " << video_stream_type << std::endl;
}

void RtcEngine::onBitrateUpdated(uint32_t bitrate_bps, NERtcVideoStreamType video_stream_type)
{
    std::cout << "<>" << __func__ << " " << "bitrate_bps = " << bitrate_bps << " " << "video_stream_type = " << video_stream_type << std::endl;
}

void RtcEngine::onVideoCodecUpdated(NERtcVideoCodecType video_codec_type, NERtcVideoStreamType video_stream_type)
{
    std::cout << "<>" << __func__ << " " << "video_codec_type = " << video_codec_type << " " << "video_stream_type = " << video_stream_type << std::endl;
}

// IRtcEngineEventHandlerEx
void RtcEngine::onError(int error_code, const char* msg) {
    std::cout << "<>" << __func__ << " " << error_code << " " << msg << std::endl;
}

void RtcEngine::onWarning(int error_code, const char* msg) {
    std::cout << "<>" << __func__ << " " << error_code << " " << msg << std::endl;
}

void RtcEngine::onReleasedHwResources(NERtcErrorCode result) {
    std::cout << "<>" << __func__ << " " << result << std::endl;
}

void RtcEngine::onReconnectingStart(channel_id_t cid, nertc::uid_t uid) {
    std::cout << "<>" << __func__ << " " << cid << " " << uid << std::endl;
}

void RtcEngine::onConnectionStateChange(NERtcConnectionStateType state, NERtcReasonConnectionChangedType reason) {
    std::cout << "<>" << __func__ << " " << state << " " << reason << std::endl;
}

void RtcEngine::onJoinChannel(channel_id_t cid, nertc::uid_t uid, NERtcErrorCode result, uint64_t elapsed) {
    std::cout << "<>" << __func__ << " " << cid << " " << uid << " " << (int)result << " " << elapsed << std::endl;
    if (result == 0) {
        // pull audio
        std::thread audio_pull_thread = std::thread([this]() {
            int timediff = 20000; //20ms
            size_t size = audio_sample_rate / 1000 * 2 * audio_channels * 20;
            char * buffer = (char *)malloc(size);
            steady_clock::time_point last = steady_clock::now();
            steady_clock::time_point now = steady_clock::now();
            while (!stopFlag) {
                now = steady_clock::now();
                long gap = duration_cast<microseconds>((now - last)).count();
                if ( gap >= timediff) {
                    last = now - microseconds(gap - timediff);
                    auto res = pullExternalAudioFrame(buffer, size);
                    if (res != 0) {
                        std::cerr << "pull external audio error, "  << res << std::endl;
                    }
                }
                std::this_thread::sleep_for(milliseconds(1)); //1ms
            }
            free(buffer);
        });
        audio_pull_thread.detach();

        // push audio
        std::thread audio_push_thread = std::thread([this]() {
            FILE *fp = fopen(audio_pcm_file.c_str(), "rb");
            if (fp == nullptr) {
                std::cerr << "open " << audio_pcm_file << " faild" << std::endl;
                return;
            } else {
                std::cout << "open " << audio_pcm_file << " successful" << std::endl;
            }
            fseek(fp, 0, SEEK_END);
            size_t size = ftell(fp);
            char *buffer = (char *)malloc(size);
            if (buffer == nullptr) {
                std::cerr << "malloc " << audio_pcm_file << " error" << "\n";
                return;
            }
            fseek(fp, 0, SEEK_SET);
            size_t ret = fread(buffer, 1, size, fp);
            if (ret != size) {
                std::cerr << "read " << audio_pcm_file << " error" << std::endl;
                return;
            }

            size_t offset = 0;
            int timediff = 20000; //20ms
            NERtcAudioFrame audioFrame;
            audioFrame.format.bytes_per_sample = 2; //pcm16
            audioFrame.format.channels = audio_channels;
            audioFrame.format.sample_rate = audio_sample_rate;
            audioFrame.format.samples_per_channel = audio_sample_rate / 1000 * timediff / 1000; 
            audioFrame.format.type = kNERtcAudioTypePCM16;
            steady_clock::time_point last = steady_clock::now();
            steady_clock::time_point now = steady_clock::now();

            while (!stopFlag) {
                now = steady_clock::now();
                long gap = duration_cast<microseconds>((now - last)).count();
                if ( gap >= timediff) {
                    last = now - microseconds(gap - timediff);
                    audioFrame.data = buffer + offset;
                    if (offset > size) {
                        offset = 0;
                    } else {
                        auto res = pushExternalAudioFrame(&audioFrame);
                        if (res != 0) {
                            std::cerr << "push external audio error, "  << res << std::endl;
                        }
                        offset += audioFrame.format.samples_per_channel * audioFrame.format.channels * audioFrame.format.bytes_per_sample;
                    }
                }
                std::this_thread::sleep_for(milliseconds(1)); //1ms
            }
            free(buffer);
        });
        audio_push_thread.detach();

        // push video
        if (videotype == 0) { // h264 file
            pushExternalH264Video.Start();
        } else if (videotype == 1) { // yuv file
            pushExternalYUVVideo.Start();
        }
    }
}

void RtcEngine::onRejoinChannel(channel_id_t cid, nertc::uid_t uid, NERtcErrorCode result, uint64_t elapsed) {
    std::cout << "<>" << __func__ << " " << cid << " " << uid << " " << result << " " << elapsed << std::endl;
}

void RtcEngine::onLeaveChannel(NERtcErrorCode result) {
    std::cout << "<>" << __func__ << " " << result << std::endl;
}

void RtcEngine::onDisconnect(NERtcErrorCode reason) {
    std::cout << "<>" << __func__ << " " << reason << std::endl;
}

void RtcEngine::onClientRoleChanged(NERtcClientRole oldRole, NERtcClientRole newRole) {
    std::cout << "<>" << __func__ << " " << oldRole << " " << newRole << std::endl;
}

void RtcEngine::onUserJoined(nertc::uid_t uid, const char * user_name) {
    std::cout << "<>" << __func__ << " " << uid << " " << user_name << std::endl;
}

void RtcEngine::onUserLeft(nertc::uid_t uid, NERtcSessionLeaveReason reason) {
    std::cout << "<>" << __func__ << " " << uid << " " << reason << std::endl; 
}

void RtcEngine::onUserAudioStart(nertc::uid_t uid) {
    std::cout << "<>" << __func__ << " " << uid << std::endl;
}

void RtcEngine::onUserAudioStop(nertc::uid_t uid) {
    std::cout << "<>" << __func__ << " " << uid << std::endl;
}

void RtcEngine::onUserVideoStart(nertc::uid_t uid, NERtcVideoProfileType max_profile) {
    std::cout << "<>" << __func__ << " " << uid << " " << max_profile << std::endl;

    NERtcVideoCanvas canvas;
    canvas.cb = RtcEngine::onFrameDataCallback;
    canvas.window = nullptr;
    canvas.user_data = this;
    auto ret = m_engine->setupRemoteVideoCanvas(uid, &canvas);
    if (ret != kNERtcNoError) {
        std::cerr << "setupRemoteVideoCanvas error " << ret << " uid = " << uid << std::endl;
    } else {
        std::cout << "setupRemoteVideoCanvas successful, uid = " << uid << std::endl;
    }

    ret = m_engine->subscribeRemoteVideoStream(uid, kNERtcRemoteVideoStreamTypeHigh, true);
    if (ret != kNERtcNoError) {
        std::cerr << "subscribeRemoteVideoStream error " << ret << " uid = " << uid << std::endl;
    } else {
        std::cout  << "subscribeRemoteVideoStream successful, uid = " << uid << std::endl;
    }
}

void RtcEngine::onUserVideoStop(nertc::uid_t uid) {
    std::cout << "<>" << __func__ << " " << uid << std::endl;

    auto ret = m_engine->subscribeRemoteVideoStream(uid, kNERtcRemoteVideoStreamTypeNone, false);
    if (ret != kNERtcNoError) {
        std::cerr << "[un]subscribeRemoteVideoStream error " << ret << " uid = " << uid << std::endl;
    } else {
        std::cout << "[un]subscribeRemoteVideoStream successful, uid = " << uid << std::endl;
    }

    NERtcVideoCanvas canvas;
    canvas.cb = nullptr;
    canvas.window = nullptr;
    canvas.user_data = nullptr;
    ret = m_engine->setupRemoteVideoCanvas(uid, &canvas);
    if (ret != kNERtcNoError) {
        std::cerr << "[un]setupRemoteVideoCanvas error " << ret << " uid = " << uid << std::endl;
    } else {
        std::cout << "[un]setupRemoteVideoCanvas successful, uid = " << uid << std::endl;
    }
}

// API
std::string RtcEngine::getVersion()
{
    int build = 0;
    std::string ver = m_engine->getVersion(&build);
    return ver + "." + std::to_string(build);
}

int RtcEngine::setParameters(const char *parameters)
{
    return m_engine->setParameters(parameters);
}

int RtcEngine::queryInterface(NERtcInterfaceIdType iid, void ** inter )
{
    return m_engine->queryInterface(iid, inter);
}

int RtcEngine::joinChannel(std::string token, std::string channel_name, uint64_t uid)
{
    auto ret = m_engine->joinChannel(token.c_str(), channel_name.c_str(), uid);
    if (ret != kNERtcNoError) {
        std::cerr << "joinChannel error " << ret << std::endl;
    } else {
        std::cout << "joinChannel successful " << std::endl;
    }
    return ret;
}

void RtcEngine::leaveChannel()
{
    // push/pull audio stop
    stopFlag.store(true);

    // push video stop
    pushExternalH264Video.Stop();
    pushExternalYUVVideo.Stop();

    if (m_engine) {
        auto ret = m_engine->leaveChannel();
        if (ret != kNERtcNoError) {
            std::cerr << "leaveChannel error " << ret << std::endl;
        } else {
            std::cout << "leaveChannel successful " << std::endl;
        }
    }
}

void RtcEngine::release()
{
    if (m_engine) {
        m_engine->release(true);
    }
}

void RtcEngine::enableLocalVideo(bool enable)
{
    auto ret = m_engine->enableLocalVideo(enable);
    if (ret != kNERtcNoError) {
        std::cerr << "enableLocalVideo error " << ret << std::endl;
    } else {
        std::cout << "enableLocalVideo successful " << std::endl;
    }
}

void RtcEngine::enableLocalAudio(bool enable)
{
    auto ret = m_engine->enableLocalAudio(enable);
    if (ret != kNERtcNoError) {
        std::cerr << "enableLocalAudio error " << ret << std::endl;
    } else {
        std::cout << "enableLocalAudio successful " << std::endl;
    }
}

int RtcEngine::setAudioFrameObserver()
{
    return m_engine->setAudioFrameObserver(this);
}

int RtcEngine::setVideoEncoderQosObserver()
{
    return m_engine->setVideoEncoderQosObserver(this);
}

// push video
int RtcEngine::setExternalVideoSource(bool enabled)
{
    return m_engine->setExternalVideoSource(enabled);
}

int RtcEngine::pushExternalVideoFrame(NERtcVideoFrame* frame)
{
    return m_engine->pushExternalVideoFrame(frame);
}

int RtcEngine::pushExternalVideoEncodedFrame(NERtcVideoStreamType type, NERtcVideoEncodedFrame* frame)
{
    return m_engine->pushExternalVideoEncodedFrame(type, frame);
}

// push audio
int RtcEngine::setExternalAudioSource(bool enabled, int sample_rate, int channels)
{
    return m_engine->setExternalAudioSource(enabled, sample_rate, channels);
}

int RtcEngine::pushExternalAudioFrame(NERtcAudioFrame* frame)
{
    return m_engine->pushExternalAudioFrame(frame);
}

// pull audio - audio frame callback by INERtcAudioFrameObserver
int RtcEngine::setExternalAudioRender(bool enabled, int sample_rate, int channels)
{
    return m_engine->setExternalAudioRender(enabled, sample_rate, channels);
}

int RtcEngine::pullExternalAudioFrame(void* data, int len)
{
    return m_engine->pullExternalAudioFrame(data, len);
}

int RtcEngine::enableDualStreamMode(bool enable)
{
    return m_engine->enableDualStreamMode(enable);
}