# NEVideoCall-Linux

提供了 Linux 桌面端 `一对一视频通话` 案例，展示如何集成 网易云信新一代（G2）音视频 SDK， 包括一下基本功能:

* 加入通话和离开通话；
* 以安全模式和非安全模式加入通话和离开通话；
* 本地视频预览；

平台|操作系统 |编译器|依赖
---|---|---|---
`x86_64`|`Ubuntu18.04+`|`g++7.5+`|`glibc 2.19+`|

## Demo工程使用步骤

### 1. 打开工程 

* 使用 qtcreator 打开 NEScreenShare-Linux.pro

### 2. 配置项目

* Projects - Build & Run 选择 编译环境
* Projects - Build Settings 选择 编译目录(可选)

### 3. 修改 APP KEY

* 将 rtcengine.h 文件中的APP_KEY修改为从网易云信控制台创建应用得到的App Key

```cpp
#define APP_KEY ""
```

### 4. 编译运行

![demo](https://github.com/netease-im/Basic-Video-Call/blob/master/One-to-One-Video/NERtcSample-1to1-Linux-Qt/NEScreenShare-Linux/demo.png)


* 如果你遇到了困难，可以先参阅 [知识库](https://faq.yunxin.163.com/kb/main/#/)
* 完整的 API 文档见 [文档中心](https://dev.yunxin.163.com/?from=bdjjnim0035)
