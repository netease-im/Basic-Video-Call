#include "rtcengine.h"
#include "cmdline.h"
#include "signal.h"

RtcEngine engine;

void SignalHandler(int signum) {
  if (signum == SIGINT) {
    std::cout << "receive SIGINT (Ctrl + C), exit" << std::endl;
    engine.leaveChannel();
    engine.release();
    exit(signum);
  }
}

int main(int argc, char* argv[])
{
    signal(SIGINT, SignalHandler);

    // arg parser
    cmdline::parser arg_parser;
    arg_parser.add<std::string>("appkey", 'a', "appkey", true, "");
    arg_parser.add<std::string>("cname", 'n', "channel name", false, "test1111");
    arg_parser.add<int64_t>("uid", 'u', "user id", false, 1234);
    arg_parser.add<std::string>("logdir", 'l', "log absolute dir", false, "/tmp/Log/");
    arg_parser.add<std::string>("pcm", 'p', "pcm file dir", false, "resource/music_16k_ch1.pcm");
    arg_parser.add<int>("samplerate", 's', "samplerate(16k, 48k, ...)", false, 16000);
    arg_parser.add<int>("channels", 'c', "channels(1, 2)", false, 1);
    arg_parser.add<int>("videotype", 'v', "videotype(0-h264, 1-yuv)", false, 0);
    arg_parser.add<std::string>("h264", 'x', "h264 file dir", false, "resource/960x540_f24_music.h264");
    arg_parser.add<std::string>("yuv", 'y', "h264 file dir", false, "resource/640x360_20fps.yuv");
    arg_parser.add<int>("fps", 'f', "fps(15, 20, 25, ...)", false, 24);
    arg_parser.add<int>("width", 'w', "video width", false, 960);
    arg_parser.add<int>("height", 'h', "video height", false, 540);
    arg_parser.add<uint64_t>("runtime", 't', "demo run time, minutes, 0 represent run forever", false, 0);

    arg_parser.parse_check(argc, argv);

    std::string appkey = arg_parser.get<std::string>("appkey");
    std::string cname = arg_parser.get<std::string>("cname");
    int64_t uid = arg_parser.get<int64_t>("uid");
    std::string logdir = arg_parser.get<std::string>("logdir");
    std::string pcm = arg_parser.get<std::string>("pcm");
    int samplerate = arg_parser.get<int>("samplerate");
    int channels = arg_parser.get<int>("channels");
    int videotype = arg_parser.get<int>("videotype");
    std::string h264 = arg_parser.get<std::string>("h264");
    std::string yuv = arg_parser.get<std::string>("yuv");
    int fps = arg_parser.get<int>("fps");
    int width = arg_parser.get<int>("width");
    int height = arg_parser.get<int>("height");
    uint64_t runtime = arg_parser.get<uint64_t>("runtime");

    std::cout << "*******************parameters******************" << std::endl;
    std::cout << "appkey: " << appkey << std::endl;
    std::cout << "cname: " << cname << std::endl;
    std::cout << "uid: " << uid << std::endl;
    std::cout << "logdir: " << logdir << std::endl;;
    std::cout << "pcm: " << pcm << std::endl;
    std::cout << "samplerate: " << samplerate << std::endl;
    std::cout << "channels: " << channels << std::endl;
    std::cout << "videotype:" << videotype << std::endl;
    std::cout << "h264: " << h264 << std::endl;
    std::cout << "yuv: " << yuv << std::endl;
    std::cout << "fps: " << fps << std::endl;
    std::cout << "width: " << width << std::endl;
    std::cout << "height: " << height << std::endl;
    std::cout << "runtime: " << runtime << " mins" << std::endl;
    std::cout << "**********************************************" << std::endl;

    // engine init
    auto ret = engine.initialize(appkey, logdir);
    if (ret != 0) {
        std::cerr << "initialize error, " << ret << std::endl;
        return -1;
    } else {
        std::cout << "initialize successful" << std::endl;
    }
    engine.setAVConfig(pcm, samplerate, channels, videotype, h264, yuv, fps, width, height);
    
    // print sdk version
    std::cout << "sdk version: " << engine.getVersion() << std::endl;

    // enable video and audio
    engine.enableLocalVideo(true);
    engine.enableLocalAudio(true);

    // disable simucast 
    engine.enableDualStreamMode(false);

    // set audio frame observer
    ret = engine.setAudioFrameObserver();
    if (ret != 0) {
        std::cerr << "setAudioFrameObserver error, " << ret << std::endl;
        return -1;
    } else {
        std::cout << "setAudioFrameObserver successful" << std::endl;
    }

    // set audio external render
    ret = engine.setExternalAudioRender(true, samplerate, channels);
    if (ret != 0) {
        std::cerr << "setExternalAudioRender error, " << ret << std::endl;
        return -1;
    } else {
        std::cout << "setExternalAudioRender successful" << std::endl;
    }

    // set audio external source
    ret = engine.setExternalAudioSource(true, samplerate, channels);
    if (ret != 0) {
        std::cerr << "setExternalAudioSource error, " << ret << std::endl;
        return -1;
    } else {
        std::cout << "setExternalAudioSource successful" << std::endl;
    }

    // set video external source and external video device
    ret = engine.setExternalVideoSource(true);
    if (ret != 0) {
        std::cerr << "setExternalVideoSource error, " << ret << std::endl;
        return -1;
    } else {
        std::cout << "setExternalVideoSource successful" << std::endl;
    }

    IVideoDeviceManager *vdmPtr;
    ret = engine.queryInterface(kNERtcIIDVideoDeviceManager, (void **)&vdmPtr);
    if (ret != 0) {
        std::cerr << "queryInterface video error, " << ret << std::endl;
        return -1;
    } else {
        std::cout << "queryInterface video successful" << std::endl;
        ret = vdmPtr->setDevice(kNERtcExternalVideoDeviceID);
        if (ret != 0) {
            std::cerr << "setDevice video error, " << ret << std::endl;
            return -1;
        } else {
            std::cout << "setDevice video successful" << std::endl;
        }
    }

    // set video encoder observer
    ret = engine.setVideoEncoderQosObserver();
    if (ret != 0) {
        std::cerr << "setVideoEncoderQosObserver error, " << ret << std::endl;
        return -1;
    } else {
        std::cout << "setVideoEncoderQosObserver successful" << std::endl;
    }

    // non-security mode, token = ""
    if (engine.joinChannel("", cname.c_str(), uid) != 0) {
        return -1;
    }

    if (runtime == 0) {
        sleep(60 * 60 * 24); // one day
    } else {
        sleep(60 * runtime);
    }

    // leave room
    engine.leaveChannel();

    // release
    engine.release();

    return 0;
}
