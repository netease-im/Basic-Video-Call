# NERtcSample-GroupVideoCall-Windows_Mac

## 功能介绍

这个开源示例项目演示了如何基于QWidget 快速集成网易云信 新一代(G2) 音视频SDK，实现1对1视频通话

- 加入频道/离开频道
- 实现多人音视频聊天
- 开启/关闭本地视频/音频

QWidget

- UI界面



## 前提条件

1. 若您已经与专属客户经理取得联系，可直接向他获取Appkey
2. 若您并未与专属客户经理取得联系那么请按后续步骤获取Appkey
3. 首先在 [网易云信](https://id.163yun.com/register?h=media&t=media&clueFrom=nim&from=bdjjnim0035&referrer=https://app.yunxin.163.com/?clueFrom=nim&from=bdjjnim0035) 注册账号
4. 然后在「应用」一栏中创建您的项目
5. 等待专属客户经理联系您，并向他获取Appkey

#### Windows

1. 在当前文件夹下新建一个名为"nertc_sdk_win"的文件夹
2. 在官网下载[音视频通话G2 Windows端SDK](https://dev.yunxin.163.com/docs/product/%E9%9F%B3%E8%A7%86%E9%A2%91%E9%80%9A%E8%AF%9DG2/SDK%E4%B8%8B%E8%BD%BD)，解压后将"api/", "dll/", "lib/"三个文件夹拷贝到新建的"nertc_sdk_win"文件夹下


#### Mac

1. 在当前文件夹下新建一个名为"nertc_sdk_mac"的文件夹
2. 在官网下载[音视频通话G2 Mac端SDK](https://dev.yunxin.163.com/docs/product/%E9%9F%B3%E8%A7%86%E9%A2%91%E9%80%9A%E8%AF%9DG2/SDK%E4%B8%8B%E8%BD%BD)，解压后将"NEFundation_Mac.framework", "nertc_sdk_Mac.framework"，拷贝到新建的"nertc_sdk_mac"文件夹下
3. 在当前文件夹下开启一个终端，运行"qmake -spec macx-xcode NERtcSample-1to1-Windows_Mac.pro"生成Xcode工程
4. 使用Xcode打开刚生成好的工程，在"Build Phases"选项中新建"Copy Files Phase"
5. 在"Copy Files"中将Destination设置为"Frameworks", 并添加"NEFundation_Mac.framework"与"nertc_sdk_Mac.framework"



## 环境准备

- Windows 10及以上版本/ Mac OS
- IDE
  - Windows环境下 Qt Creator/Microsoft Visual Stuido
  - Mac环境下 Xcode 
- 编译器
  - Windows环境下 MSVC 2015 64bit
  - Mac环境下 clang 64bit



## 运行示例项目

将上面获取到的Appkey填入nrtc_engine.h

```c++
#define APP_KEY ""              // put your app key here, testing
```

#### Windows

使用Qt creator 打开 nertc_with_Qt.pro文件，重新构建后即可运行程序

#### Mac

使用Xcode打开上述建立好的工程，在Info.plist中添加访问摄像头及麦克风设备的权限，单机运行即可运行程序

## 功能实现

### 创建NERtcEngine 实例并初始化

进入频道之前，调用 createNERtcEngine 方法创建一个 NERtcEngine 实例，并调用initialize 方法完成初始化。

填入获取到的 Appkey 。只有 Appkey 相同的应用程序才能进入同一个频道进行互通。

```c++
//创建NERtcEngine实例
rtc_engine_ = static_cast<IRtcEngineEx*>(createNERtcEngine());

//对初始化需要的参数进行配置
rtc_engine_context_.app_key = app_key;
rtc_engine_context_.log_dir_path = log_dir_path;
rtc_engine_context_.log_level = kNERtcLogLevelInfo;
rtc_engine_context_.log_file_max_size_KBytes = log_file_max_size_KBytes;
rtc_engine_context_.event_handler = rtc_engine_handler_.get();
rtc_engine_context_.video_prefer_hw_codec = false;
rtc_engine_context_.video_use_exnternal_render = true;

//初始化引擎
if (kNERtcNoError != rtc_engine_->initialize(rtc_engine_context_)) {
    qDebug("[ERROR] Failed to initialize NERtc Engine\n");
    return false;
}
```



### 加入频道

调用joinChannel 方法加入频道

- 传入能标识用户角色和权限的 Token。如果安全要求不高，也可以将值设为 空字符串。Token 需要在应用程序的服务器端生成，具体生成办法，详见 [密钥说明](https://dev.yunxin.163.com/docs/product/音视频通话G2/服务端API文档?pos=toc-2-15)。
- 传入能标识频道的频道名称。输入相同频道名称的用户会进入同一个频道。
- 传入能标识用户身份的用户 UID。请确保频道内每个用户的 UID 必须是独一无二的

```c++
//加入频道，token置为空
ret = rtc_engine_->joinChannel("", roomid.toUtf8().data(), user_id_);
```



### 发布订阅音视频流

调用enalbeLocalAudio/enableLocalVideo 方法开启本地音/视频。开启本地视频之前，需要调用setupLocalVideoCanvas 方法设置好本地视频视图。

```c++
//设置本地视图参数
NERtcVideoCanvas canvas;
canvas.cb = view == nullptr ? nullptr : NRTCEngine::onReceiveVideoFrame;
canvas.user_data = view == nullptr ? nullptr : reinterpret_cast<void*>(params);
canvas.scaling_mode = kNERtcVideoScaleFit;

//设置本地视图
int ret = rtc_engine_->setupLocalVideoCanvas(&canvas);
if (ret) {
    qDebug("ERROR: Can not setup local video canvas! ERROR CODE: %d", ret);
}

//开启本地视频
if (view != nullptr) {
    rtc_engine_->enableLocalVideo(true);
}
else {
    rtc_engine_->enableLocalVideo(false);
}
```

调用subscribeRemoteAudioStream/subscribeRemoteVideoStream 方法来订阅远端音/视频流，需指定远端用户id，订阅远端视频前，需调用setupRemoteVideoCanvas设置远端视图

```c++
//设置远端视图参数
NERtcVideoCanvas canvas;
canvas.cb = view == nullptr ? nullptr : NRTCEngine::onReceiveVideoFrame;
canvas.user_data = view == nullptr ? nullptr : reinterpret_cast<void*>(params);
canvas.scaling_mode = kNERtcVideoScaleFit;

//设置远端视图
int ret = rtc_engine_->setupRemoteVideoCanvas(uid, &canvas);
if (ret) {
	qDebug("[ERROR] Can not setup remote video canvas! ERROR CODE: %d", ret);
}

//设置远端视图的画布后，订阅加入频道的用户
if (view != nullptr) {
	rtc_engine_->subscribeRemoteUserVideoStream(uid,
        kNERtcRemoteVideoStreamTypeHigh, true);
	rtc_engine_->subscribeRemoteAudioStream(uid, true);
}
```



### 离开频道

通话结束时，调用leaveChannel方法离开频道

```c++
int ret = rtc_engine_->leaveChannel();
```

