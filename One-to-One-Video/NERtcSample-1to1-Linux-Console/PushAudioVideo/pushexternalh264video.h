#ifndef PUSHEXTERNALH264VIDEO_H
#define PUSHEXTERNALH264VIDEO_H

#include <stdio.h>
#include <atomic>
#include <thread>
#include <string>
#include <vector>

typedef enum {
	NALU_TYPE_SLICE    = 1,
	NALU_TYPE_DPA      = 2,
	NALU_TYPE_DPB      = 3,
	NALU_TYPE_DPC      = 4,
	NALU_TYPE_IDR      = 5,
	NALU_TYPE_SEI      = 6,
	NALU_TYPE_SPS      = 7,
	NALU_TYPE_PPS      = 8,
	NALU_TYPE_AUD      = 9,
	NALU_TYPE_EOSEQ    = 10,
	NALU_TYPE_EOSTREAM = 11,
	NALU_TYPE_FILL     = 12,
} NaluType;
 
typedef enum {
	NALU_PRIORITY_DISPOSABLE = 0,
	NALU_PRIRITY_LOW         = 1,
	NALU_PRIORITY_HIGH       = 2,
	NALU_PRIORITY_HIGHEST    = 3
} NaluPriority;

// startcode | head | data || startcode | head | data || startcode | head | data ||...
struct Nalu
{
    uint8_t start_code_len;
    unsigned char head;
    size_t pos_start;
    size_t pos_end;
    size_t len;
};

class RtcEngine;
class PushExternalH264Video
{
public:
    PushExternalH264Video(RtcEngine &_engine);
    ~PushExternalH264Video();

    void Start();
    bool isStart() const;
    void Stop();
    void setVideoConfig(std::string file, int fps, int width, int height);

private:
    int getNalu(Nalu &nalu);
    int pushExternalH264VideoImpl(void);
    bool isStartCode3B(const unsigned char *buf);
    bool isStartCode4B(const unsigned char *buf);
    int findStartCode(const unsigned char *buf, size_t size);
    int readFile(void);
    void Release();

private:
    RtcEngine& m_engine;
    std::atomic_bool stopFlag;
    std::thread worker;
    bool valid = false;
    std::string videoFile;
    int fps = 15;
    int width = 960;
    int height = 540;
    unsigned char *buffer = nullptr;
    size_t size = 0;
    size_t curPos = 0;
    FILE *file = nullptr;
    std::vector<struct Nalu> nalu_vec;
    bool complete = false;
};



#endif //#ifndef PUSHEXTERNALH264VIDEO_H