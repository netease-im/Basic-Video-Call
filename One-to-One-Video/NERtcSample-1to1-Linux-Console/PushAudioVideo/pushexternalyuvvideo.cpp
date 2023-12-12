#include "pushexternalyuvvideo.h"
#include "rtcengine.h"
#include <chrono>

using namespace nertc;
using namespace std::chrono;

PushExternalYUVVideo::PushExternalYUVVideo(RtcEngine &_engine)
: m_engine(_engine)
, stopFlag(true)
{

}

PushExternalYUVVideo::~PushExternalYUVVideo()
{
    Stop();
}

void PushExternalYUVVideo::Release()
{
    if (buffer) {
        free(buffer);
        buffer = nullptr;
    }
}

void PushExternalYUVVideo::Start()
{
    if (stopFlag) {
        stopFlag.store(false);
    } else {
        std::cout << "pushing extern video is started, cannot start repeat" << std::endl;
        return;
    }
    worker = std::thread([this]() {
        uint32_t offset = 0;
        int timediff = 1000000 / fps;

        NERtcVideoFrame videoFrame;
        videoFrame.format = kNERtcVideoTypeI420;
        videoFrame.width = width;
        videoFrame.height = height;
        videoFrame.timestamp = 0;

        steady_clock::time_point last = steady_clock::now();
        steady_clock::time_point now = steady_clock::now();
        while (!stopFlag) {
            now = steady_clock::now();
            long gap = duration_cast<microseconds>((now - last)).count();
            if (gap > timediff) {
                last = now - microseconds(gap - timediff);
                videoFrame.timestamp += timediff / 1000;
                videoFrame.rotation = kNERtcVideoRotation_0;
                int len =  videoFrame.width * videoFrame.height * 3 / 2;
                if (offset + len > size) {
                    offset = 0;
                    videoFrame.timestamp = 0;
                    fseek(file, 0, SEEK_SET);
                }

                buffer = (char *)malloc(len);
                if (buffer == nullptr) {
                    std::cout << "malloc error\n";
                    stopFlag.store(true);
                    return;
                }
                fread(buffer, 1, len, file);
                offset += len;
                fseek(file, offset, SEEK_SET);

                videoFrame.buffer = buffer;
                m_engine.pushExternalVideoFrame(&videoFrame);
                free(buffer);
                buffer = nullptr;
            }
            std::this_thread::sleep_for(milliseconds(1)); //1ms
        }
    });
}

bool PushExternalYUVVideo::isStart() const
{
    return !stopFlag.load();
}

void PushExternalYUVVideo::Stop()
{
    stopFlag.store(true);

    if (worker.joinable()) {
        worker.join();
    }

    Release();
}

void PushExternalYUVVideo::setVideoConfig(std::string yuv_file, int fps, int width, int height)
{
    this->fps = fps;
    this->width = width;
    this->height = height;

    if (file) {
        fclose(file);
        file = nullptr;
    }
    file = fopen(yuv_file.c_str(), "rb+");
    if (file == nullptr) {
        std::cerr << "open" << yuv_file.c_str() << "error" << std::endl;
        return;
    }
    std::cout << "open" << yuv_file.c_str() << "successful" << std::endl;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);
}
