#ifndef RTCENGINE_H
#define RTCENGINE_H
#include "nertc_engine_ex.h"
#include "nertc_engine_event_handler_ex.h"
#include "nertc_engine_defines.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <string>

#define APP_KEY "6acf024e190215b685905444b6e57dd7"

using namespace nertc;

class RtcEngine : public QObject, public IRtcEngineEventHandlerEx
{
    Q_OBJECT

    friend class MainWindow;

public:
    RtcEngine(QObject *parent = nullptr);
    ~RtcEngine();

    bool init(const std::string &app_key_, const std::string &log_dir_path_, NERtcLogLevel log_level_, uint32_t log_file_max_size_KBytes_);
    void joinRoom(const std::string &token, const std::string &roomName, uint32_t uid);
    void leaveRoom(void);
    int startScreenCaptureByScreenRect(const NERtcRectangle& screen_rect, const NERtcRectangle& region_rect, const NERtcScreenCaptureParameters& capture_params);
    int stopScreenCapture();
    std::string getSdkVersion();

    // IRtcEngineEventHandler
    virtual void onJoinChannel(channel_id_t cid, nertc::uid_t uid, NERtcErrorCode result, uint64_t elapsed) override;
    virtual void onLeaveChannel(NERtcErrorCode result) override;
    virtual void onUserJoined(nertc::uid_t uid, const char * user_name) override;
    virtual void onUserLeft(nertc::uid_t uid, NERtcSessionLeaveReason reason) override;

signals:
    void yuvDataComming(uint32_t uid, std::vector<unsigned char>, std::vector<unsigned char>, std::vector<unsigned char>, int, int);

private:
    IRtcEngineEx *rtc_engine_;
    std::string sdk_version_;

public:
    static void onYuvDataIncoming(
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
     );
};

#endif // RTCENGINE_H
