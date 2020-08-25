# NERtcSample-GroupVideoCall-iOS-Swift

这个开源示例项目演示了如何快速集成 网易云信 新一代（G2）音视频 SDK，实现多人音视频通话。

 在这个示例项目中包含了以下功能：

- 支持多人加入通话和断开通话

## 环境准备

- Xcode 10.0+
- iOS真机设备
- 支持模拟器运行，但是部分功能无法使用

## 运行示例项目

这个段落主要讲解了如何编译和运行实例程序。

#### 获取AppKey

在编译和启动实例程序前，您需要首先获取一个可用的App Key：

1. 若您已经与专属客户经理取得联系，可直接向他获取Appkey

2. 若您并未与专属客户经理取得联系那么请按后续步骤获取Appkey

3. 首先在 [网易云信](https://id.163yun.com/register?h=media&t=media&clueFrom=nim&from=bdjjnim0035&referrer=https://app.yunxin.163.com/?clueFrom=nim&from=bdjjnim0035) 注册账号

4. 然后在「应用」一栏中创建您的项目
5. 等待专属客户经理联系您，并向他获取Appkey

6. 将AppKey填写进Config.swift

```swift
let kAppKey: String = "<#请输入您的app key#>"
```

#### 集成实时音视频SDK

1. 进入Demo根路径，执行`pod install`
2. 使用Xcode打开NERtcSample-GroupVideoCall-iOS-Swift.xcworkspace，连接iPhone/iPad测试设备，设置有效的开发者签名后即可运行

## 功能实现

1. 引擎初始化。配置音视频相关参数。

   ```swift
   func setupRTCEngine() {
        let context = NERtcEngineContext()
        context.engineDelegate = self
        context.appKey = "<#请输入您的app key#>"
        let engine = NERtcEngine.shared()
        engine.setupEngine(with: context)
        engine.enableLocalAudio(true)
        engine.enableLocalVideo(true)
    }
   ```

2. 加入和离开房间。调用SDK接口加入和退出音视频房间

   ```swift
   /* ---- 加入房间 ---- */
   let channelName: String = "频道名称"
   let userId: UInt64 = '用户ID'
   NERtcEngine.shared().joinChannel(
            withToken: "",
            channelName: roomID,
            myUid: userId) { [weak self] (error, channelId, elapesd) in
                guard let self = self else { return }
                if let error = error {
                    // 加入失败
                    print(error.localizedDescription)
                } else {
                    // 加入成功，建立本地canvas，准备渲染本地视图
                    let canvas = NERtcVideoCanvas()
                    canvas.container = self.localUserView
                    NERtcEngine.shared().setupLocalVideoCanvas(canvas)
                }
            }
   
   /* ---- 离开房间 ---- */
   NERtcEngine.shared().leaveChannel()
   ```

3. 建立Canvas，渲染画面。针对每个用户需要单独建立Canvas用于渲染该用户的图像。

   ```swift
   /* ---- 本地用户渲染 ---- */
   func setupLocalCanvas() {
        let canvas = NERtcVideoCanvas()
        canvas.container = localRenderView  /* UIView，本地待渲染view */
        canvas.renderMode = .cropFill       /* 渲染模式 */
        NERtcEngine.shared().setupLocalVideoCanvas(canvas)
    }
   
   /* ---- 远端用户渲染 ----- */
   func setupRemoteCanvas(userId: UInt64) {
        let canvas = NERtcVideoCanvas()
        canvas.container = remoteRenderView  /* UIView，本地待渲染view */
        canvas.renderMode = .cropFill       /* 渲染模式 */
        NERtcEngine.shared().setupRemoteVideoCanvas(canvas, forUserID: userId)
    }
   ```

4. 订阅/取消订阅远端视频流

   ```swift
   /* ---- 引擎回调（NERtcEngineDelegateEx），有远端用户开启了视频 --- */
   func onNERtcEngineUserVideoDidStart(withUserID userID: UInt64, videoProfile profile: NERtcVideoProfileType) {
        NERtcEngine.shared().subscribeRemoteVideo(true, /* 参数如果为false，则为取消订阅 */
                                                  forUserID: userID,
                                                  streamType: .high)
    }
   ```

5. 音视频控制

   ```swift
   /* ---- 本地音频控制(开关) ---- */
   let enableLocalAudio = true /* YES:开启音频 NO:关闭音频 */
   NERtcEngine.shared().enableLocalAudio(enableLocalAudio)
   
   /* ---- 本地视频控制(开关) ---- */
   let enableLocalVideo = true /* YES:开启视频 NO:关闭视频 */
   NERtcEngine.shared().enableLocalVideo(enableLocalVideo)
   ```

   

   