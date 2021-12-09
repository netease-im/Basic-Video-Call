#include "rtcengine.h"
#include "nertc_video_device_manager.h"
#include <QMessageBox>

RtcEngine::RtcEngine(QObject *parent) : QObject(parent)
{

}

RtcEngine::~RtcEngine()
{
    if (rtc_engine_) {
        destroyNERtcEngine((void *&)rtc_engine_);
    }
}

bool RtcEngine::init(const std::string &app_key_, const std::string &log_dir_path_, NERtcLogLevel log_level_, uint32_t log_file_max_size_KBytes_)
{
    // Create And Initialize Engine
    rtc_engine_ = (IRtcEngineEx *)createNERtcEngine();
    NERtcEngineContext rtc_engine_context_;
    rtc_engine_context_.app_key = app_key_.c_str();
    rtc_engine_context_.log_dir_path = log_dir_path_.c_str();
    rtc_engine_context_.log_level = log_level_;
    rtc_engine_context_.log_file_max_size_KBytes = log_file_max_size_KBytes_;
    rtc_engine_context_.event_handler = this;
    ::memset(&rtc_engine_context_.server_config, 0, sizeof(rtc_engine_context_.server_config)); //important
    auto ret = rtc_engine_->initialize(rtc_engine_context_);
    if (kNERtcNoError != ret) {
        qDebug("[ERROR] initialize failed! ERROR CODE: %d", ret);
        return false;
    }

    // SDK Version
    int build = 0;
    sdk_version_ = rtc_engine_->getVersion(&build);
    sdk_version_ += std::string(".") + std::to_string(build);

    // Setup Local Video Canvas
    NERtcVideoCanvas canvas;
    canvas.cb = &RtcEngine::onYuvDataIncoming;
    canvas.user_data = this;
    canvas.window = nullptr;
    canvas.scaling_mode = kNERtcVideoScaleFit;
    ret = rtc_engine_->setupLocalVideoCanvas(&canvas);
    if (kNERtcNoError != ret) {
        qDebug("[ERROR] setupLocalVideoCanvas failed! ERROR CODE: %d", ret);
        return false;
    }

    // Set Video Device
    IVideoDeviceManager *vdmPtr = nullptr;
    rtc_engine_->queryInterface(kNERtcIIDVideoDeviceManager, (void **)&vdmPtr);
    IDeviceCollection *vdmCapture = vdmPtr->enumerateCaptureDevices();
    NERtcDeviceInfo info;
    int count = vdmCapture->getCount();
    if (count > 0) {
        vdmCapture->getDeviceInfo(vdmCapture->getCount() - 1, &info);
    } else {
        QMessageBox::critical(nullptr, "Camera Error", "No Camera Available");
        qDebug("[ERROR] No Camera Available");
        return false;
    }
    ret = vdmPtr->setDevice(info.device_id);
    if (ret != kNERtcNoError) {
        QMessageBox::critical(nullptr, "Camera Error", "setDevice failed! ERROR CODE: " + QString::number(ret) + ", Camera Name: " + info.device_name);
        qDebug("[ERROR] setDevice failed! ERROR CODE: %d, Camera Name: %s", ret, info.device_name);
        return false;
    }

    // Enable Local Video
    ret = rtc_engine_->enableLocalVideo(true);
    if (kNERtcNoError != ret) {
        qDebug("[ERROR] enableLocalVideo failed! ERROR CODE: %d", ret);
        return false;
    }

    return true;
}

std::string RtcEngine::getSdkVersion()
{
    return sdk_version_;
}

void RtcEngine::joinRoom(const std::string &token, const std::string &roomName, uint32_t uid)
{
    auto ret = rtc_engine_->joinChannel(token.c_str(), roomName.c_str(), uid);
    if (kNERtcNoError != ret) {
        qDebug("[ERROR] joinChannel failed! ERROR CODE: %d", ret);
        QMessageBox::critical(nullptr, "Room Error", "joinChannel failed! ERROR CODE: " + QString::number(ret));
    }
}

void RtcEngine::leaveRoom(void)
{
    auto ret = rtc_engine_->leaveChannel();
    if (kNERtcNoError != ret) {
        qDebug("[ERROR] leaveChannel failed! ERROR CODE: %d", ret);
        QMessageBox::critical(nullptr, "Room Error", "leaveChannel failed! ERROR CODE: " + QString::number(ret));
    }
}

void RtcEngine::startPreview(void)
{
    auto ret = rtc_engine_->startVideoPreview();
    if (kNERtcNoError != ret) {
        qDebug("[ERROR] startVideoPreview failed! ERROR CODE: %d", ret);
        QMessageBox::critical(nullptr, "Preview Error", "startVideoPreview failed! ERROR CODE: " + QString::number(ret));
    }
}

void RtcEngine::stopPreview(void)
{
    auto ret = rtc_engine_->stopVideoPreview();
    if (kNERtcNoError != ret) {
        qDebug("[ERROR] stopVideoPreview failed! ERROR CODE: %d", ret);
        QMessageBox::critical(nullptr, "Preview Error", "stopVideoPreview failed! ERROR CODE: " + QString::number(ret));
    }
}

void RtcEngine::onJoinChannel(channel_id_t cid, nertc::uid_t uid, NERtcErrorCode result, uint64_t elapsed)
{
    qDebug("[onJoinChannel] cid: %lu uid: %lu result: %d elapsed: %lu(ms)", cid, uid, result, elapsed);
}

void RtcEngine::onLeaveChannel(NERtcErrorCode result)
{
    qDebug("[onLeaveChannel] result: %d", result);
}

void RtcEngine::onUserJoined(nertc::uid_t uid, const char * user_name)
{
    qDebug("[onUserJoined] uid: %lu, user_name: %s", uid, user_name);
    NERtcVideoCanvas canvas;
    canvas.cb = &RtcEngine::onYuvDataIncoming;
    canvas.user_data = this;
    canvas.window = nullptr;
    canvas.scaling_mode = kNERtcVideoScaleFit;
    rtc_engine_->setupRemoteVideoCanvas(uid, &canvas);
    rtc_engine_->subscribeRemoteVideoStream(uid, kNERtcRemoteVideoStreamTypeHigh, true);
}

void RtcEngine::onUserLeft(nertc::uid_t uid, NERtcSessionLeaveReason reason)
{
    qDebug("[onUserLeft] uid: %lu, reason: %d", uid, reason);
    rtc_engine_->subscribeRemoteVideoStream(uid, kNERtcRemoteVideoStreamTypeNone, false);
    NERtcVideoCanvas canvas;
    canvas.cb = nullptr;
    canvas.user_data = nullptr;
    canvas.window = nullptr;
    canvas.scaling_mode = kNERtcVideoScaleFit;
    rtc_engine_->setupRemoteVideoCanvas(uid, &canvas);
}

void RtcEngine::onYuvDataIncoming(
        nertc::uid_t uid,   /**< uid */
        void *data,         /**< 数据指针 */
        uint32_t type,      /**< NERtcVideoType */
        uint32_t width,     /**< 宽度 */
        uint32_t height,    /**< 高度 */
        uint32_t count,     /**< 数据类型个数，即offset及stride的数目 */
        uint32_t offset[4], /**< 每类数据偏移 */
        uint32_t stride[4], /**< 每类数据步进 */
        uint32_t rotation,  /**< NERtcVideoRotation */
        void *user_data     /**< 用户透传数据 */
)
{
    (void) type;
    (void) count;
    (void) rotation;
    if (user_data) {
        std::vector<unsigned char> data_y;
        unsigned char *src_y = (unsigned char *)data + offset[0];
        for (uint32_t i = 0; i < height; i++) {
            data_y.insert(data_y.end(), src_y, src_y + width);
            src_y += stride[0];
        }

        std::vector<unsigned char> data_u;
        unsigned char *src_u = (unsigned char *)data + offset[1];
        for (uint32_t i = 0; i < height / 2; i++) {
            data_u.insert(data_u.end(), src_u, src_u + width / 2);
            src_u += stride[1];
        }

        std::vector<unsigned char> data_v;
        unsigned char *src_v = (unsigned char *)data + offset[2];
        for (uint32_t i = 0; i < height / 2; i++) {
            data_v.insert(data_v.end(), src_v, src_v + width / 2);
            src_v += stride[2];
        }

        RtcEngine *rtc_engine = static_cast<RtcEngine *>(user_data);
        emit rtc_engine->yuvDataComming(uid, data_y, data_u, data_v, width, height);
    }
}
