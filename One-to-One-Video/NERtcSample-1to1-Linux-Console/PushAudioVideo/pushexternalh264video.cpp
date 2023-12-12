#include "pushexternalh264video.h"
#include "rtcengine.h"
#include "util.h"
#include <chrono>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace nertc;
using namespace std::chrono;

PushExternalH264Video::PushExternalH264Video(RtcEngine &_engine)
: m_engine(_engine)
, stopFlag(true)
{
   
}

PushExternalH264Video::~PushExternalH264Video()
{
   Stop();
}

void PushExternalH264Video::Release()
{
    if (buffer) {
        free(buffer);
        buffer = nullptr;
    }
}

int PushExternalH264Video::readFile(void)
{
    file = fopen(videoFile.c_str(), "rb+");
    if (file == nullptr) {
       std::cerr << "open " << videoFile << " error" << std::endl;
        return -1;
    }
    std::cout << "open " << videoFile << " successful" << std::endl;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    buffer = (unsigned char *)malloc(size);
    if (buffer == nullptr) {
        std::cerr << "malloc error" << std::endl;
        return - 1;
    }
    fseek(file, 0, SEEK_SET);
    size_t rsize = fread(buffer, 1, size, file);

    Nalu nalu;
    int cnt = 0;
    while (!complete) {
        getNalu(nalu);
        nalu_vec.push_back(nalu);
    }
    free(buffer);
    buffer = nullptr;

    return 0;
}

void PushExternalH264Video::setVideoConfig(std::string file, int fps, int width, int height)
{
    this->videoFile = file;
    this->fps = fps;
    this->width = width;
    this->height = height;

    if (!valid) {
        if (readFile() == 0) {
            valid = true;
        }
    } else {
        if (buffer) {
            free(buffer);
            buffer = nullptr;
        }
        if (readFile() != 0) {
            valid = false;
        }
    }
}

void PushExternalH264Video::Start()
{
    if (!valid) {
        std::cerr << "h264 video file is not valid" << std::endl;
        return;
    }
    std::cout << "pushing extern h264 video is starting..." << std::endl;
    if (stopFlag) {
        stopFlag.store(false);
    } else {
        std::cerr << "pushing extern h264 video is started, cannot start repeat" << std::endl;
        return;
    }
    worker = std::thread([this]() {
        int timediff = 1000000 / fps; //us
        steady_clock::time_point last = steady_clock::now();
        steady_clock::time_point now = steady_clock::now();
       
        while (!stopFlag) {
            now = steady_clock::now();
            long gap = duration_cast<microseconds>((now - last)).count();
            if ( gap >= timediff) {
                last = now - microseconds(gap - timediff);
                auto res = pushExternalH264VideoImpl();
                if ( res != 0) {
                    std::cerr << "push external H264 video error " <<  res << std::endl;
                }
            }
            std::this_thread::sleep_for(milliseconds(1)); //1ms
        }
    });
}

bool PushExternalH264Video::isStart() const
{
    return !stopFlag.load();
}

void PushExternalH264Video::Stop()
{
    stopFlag.store(true);

    if (worker.joinable()) {
        worker.join();
    }

    Release();
}


bool PushExternalH264Video::isStartCode3B (const unsigned char *buf){
	return (buf[0] == 0 && buf[1] == 0 && buf[2] == 1); //0x000001
}

bool PushExternalH264Video::isStartCode4B (const unsigned char *buf){
	return (buf[0] == 0 && buf[1] == 0 && buf[2] == 0 && buf[3] == 1); //0x00000001
}

int PushExternalH264Video::getNalu(Nalu &nalu)
{
    unsigned char *data = buffer + curPos;
    bool startCodeFound = isStartCode3B(data) || isStartCode4B(data);
    if (!startCodeFound) {
        std::cerr << "h264 file is invalid" << std::endl;
        return -1;
    }

    int startCodeLen = 0;
    if (isStartCode3B(data)) {
        startCodeLen = 3;
    } else {
        startCodeLen = 4;
    }

    //find next start code
    int tmpPos = curPos + startCodeLen;
    bool hasNextStartCode = false;
    int nextStartCodeLen = 0;
    while (!hasNextStartCode) {
        if (tmpPos + 3 > size) {
            break;
        } else {
            if (isStartCode3B(buffer + tmpPos)) {
                hasNextStartCode = true;
                nextStartCodeLen = 3;
                break;
            } else {
                if (tmpPos + 4 > size) {
                    break;
                } else {
                    if (isStartCode4B(buffer + tmpPos)) {
                        hasNextStartCode = true;
                        nextStartCodeLen = 4;
                        break;
                    }
                }
            }
        }
        tmpPos++;
    }
    if (hasNextStartCode) {
        nalu.start_code_len = startCodeLen;
        nalu.len = tmpPos - curPos; //include start code
        nalu.pos_start = curPos + startCodeLen;
        nalu.pos_end = tmpPos;
        nalu.head = buffer[nalu.pos_start];
        curPos = tmpPos;
    } else {
        nalu.start_code_len = startCodeLen;
        nalu.len = size - curPos;
        nalu.pos_start = curPos + startCodeLen;
        nalu.pos_end = size;
        nalu.head = buffer[nalu.pos_start];
        curPos = 0;
        complete = true;
    }

    return 0;
}

int PushExternalH264Video::pushExternalH264VideoImpl()
{
    NERtcVideoEncodedFrame frame;
    memset(&frame, 0, sizeof(frame));
    frame.frame_type = kNERtcNalFrameTypeP;
    int nalLen[40];
    memset(&nalLen, 0, sizeof(nalLen));
    unsigned char *data = nullptr;
    static int index = 0;
    while (true) {
        Nalu &nalu = nalu_vec[index++];
        nalLen[frame.nal_count++] = nalu.len;
        if (frame.nal_count >= 10) {
            std::cerr << "nalu num more than 10" << std::endl;
            return -1;
        }

        if ((nalu.head & 0x1f) == NALU_TYPE_SEI || 
                (nalu.head & 0x1f) == NALU_TYPE_SPS ||
                (nalu.head & 0x1f) == NALU_TYPE_PPS) {
            continue;
        }
        if ((nalu.head & 0x1f) == NALU_TYPE_IDR) {
            frame.frame_type = kNERtcNalFrameTypeIDR;
            break;
        } else {
            frame.frame_type = kNERtcNalFrameTypeP;
            break;
        }
    }
    frame.width = width;
    frame.height = height;
    frame.codec_type = kNERtcVideoCodecTypeH264;
    frame.timestamp_us = TimeMicros();
    static time_t last = frame.timestamp_us;
    last = frame.timestamp_us;
    frame.nal_length = nalLen;
    static uint64_t lens = 0;
    int len = 0;
    for (unsigned int i = 0; i < frame.nal_count; i++) {
        len += frame.nal_length[i];
    }
    lens += len;

    buffer = (unsigned char *)malloc(len);
    if (buffer == nullptr) {
        std::cerr << "malloc error" << std::endl;
        return - 1;
    }

    size_t rsize = fread(buffer, 1, len, file);
    fseek(file, lens, SEEK_SET);

    frame.nal_data = buffer;

    if (index >= nalu_vec.size()) {
        index = 0;
        lens = 0;
        fseek(file, 0, SEEK_SET);
    } 
    int ret = !stopFlag ? m_engine.pushExternalVideoEncodedFrame(kNERTCVideoStreamMain, &frame) : 0;
    free(buffer);
    buffer = nullptr;
    
    return ret;
}