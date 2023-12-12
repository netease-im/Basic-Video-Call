# README

---

提供了 Linux 端音视频通话案例，展示如何集成网易云信新一代（G2）音视频 SDK， 包括以下基本功能:

* 加入通话和离开通话；
* Linux 音频拉流
* Linux 音频推流 （`PCM格式`）
* Linux 视频推流 （`YUV、H264格式`）

应用场景：`服务端虚拟人音视频推流场景`

平台|操作系统 |编译器|依赖
---|---|---|---
`x86_64`|`Linux`|`gnu`|`glibc 2.19+`|
`arm64`|`Linux`|`gnu`|`glibc 2.23+`|


## 1. 工程构建及编译

### 1.1 构建

---

* 进入工程根目录
* 执行cmake命令进行工程构建
  
```sh
  cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=[安装路径] -DTARGET_ARCH=[x86_64|arm64]

  比如：
  cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$(pwd)/install -DTARGET_ARCH=x86_64
```

### 1.2 编译

---

```sh
  cmake --build build --config Release
```

### 1.3 安装

---

```sh
  cmake --install build --config Release
```

## 2. demo 运行

### 2.1 目录结构

---

```sh
install/
├── bin
│   ├── nertc_demo
│   ├── resource
│   │   ├── 640x360_20fps_I420.yuv
│   │   ├── 960x540_f24_music.h264
│   │   └── music_16k_ch1.pcm
│   └── run.sh
├── lib
│   ├── libNERtcAiDenoise.so
│   ├── libnertc_sdk.so
│   └── libprotoopp.so
└── README.md

3 directories, 9 files
```

## 2.2 demo 启动方式

---

* 直接运行bin目录中的run.sh即可
> 必须提供 appkey
> appkey获取请参考 https://doc.yunxin.163.com/console/docs/TIzMDE4NTA?platform=console

```sh
sh run.sh
```

* 可手动修改run.sh中的启动参数, 启动参数如下:

```sh
usage: ./nertc_demo --appkey=string [options] ...
options:
  -a, --appkey        appkey (string)
  -n, --cname         channel name (string)
  -u, --uid           user id (long)
  -l, --logdir        log absolute dir (string [=/tmp/Log/])
  -p, --pcm           pcm file dir (string [=resource/music_16k_ch1.pcm])
  -s, --samplerate    samplerate(16k, 48k, ...) (int [=16000])
  -c, --channels      channels(1, 2) (int [=1])
  -v, --videotype     videotype(0-h264, 1-yuv) (int [=0])
  -x, --h264          h264 file dir (string [=resource/960x540_f24_music.h264])
  -y, --yuv           h264 file dir (string [=resource/640x360_20fps.yuv])
  -f, --fps           fps(15, 20, 25, ...) (int [=24])
  -w, --width         video width (int [=960])
  -h, --height        video height (int [=540])
  -t, --runtime       demo run time, minutes, 0 represent run forever (unsigned long [=0])
  -?, --help          print this message
```

## 2.3 互通验证

---

可以加入其他端 demo 进行验证，可以在其它端 demo 上看到 Linux 端的推流画面和听到 Linux 端的推流声音。

> 要保证互通的两个 demo Appkey 和 cname （房间名）一样