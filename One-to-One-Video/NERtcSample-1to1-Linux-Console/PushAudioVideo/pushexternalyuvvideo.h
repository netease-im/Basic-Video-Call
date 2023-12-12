#ifndef PUSH_EXTERNAL_YUV_VIDEO_H
#define PUSH_EXTERNAL_YUV_VIDEO_H
#include <atomic>
#include <thread>

class RtcEngine;
class PushExternalYUVVideo
{
public:
    PushExternalYUVVideo(RtcEngine &_engine);
    ~PushExternalYUVVideo();

    void Start();
    bool isStart() const;
    void Stop();
    void setVideoConfig(std::string file, int fps, int width, int height);

private:
    void Release();

private:
    RtcEngine& m_engine;
    std::atomic_bool stopFlag;
    std::thread worker;
    char *buffer = nullptr;
    FILE *file = nullptr;
    size_t size = 0;
    int fps = 15;
    int width = 960;
    int height = 540;
};

#endif // PUSH_EXTERNAL_YUV_VIDEO_H
