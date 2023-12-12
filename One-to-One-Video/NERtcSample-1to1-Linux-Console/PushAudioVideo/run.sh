#!/bin/sh
export LD_LIBRARY_PATH=../lib
chmod a+x ./nertc_demo

./nertc_demo \
--appkey "" \
--cname "test1111" \
--uid 1234 \
--logdir "$(pwd)/Log/" \
--pcm "$(pwd)/resource/music_16k_ch1.pcm" \
--samplerate 16000 \
--channels 1 \
--videotype 0 \
--yuv "$(pwd)/resource/640x360_20fps_I420.yuv" \
--h264 "$(pwd)/resource/960x540_f24_music.h264" \
--width 960 \
--height 540 \
--fps 24 \
--runtime 0 
