# NERtcSample-GroupVideoCall-Android-Java

## 功能介绍

这个开源示例项目演示了如何快速集成 网易云信 新一代（G2）音视频 SDK，实现多人音视频通话。

- 支持多人加入通话和断开通话

## 环境准备

- Android SDK API Level Level ≥ 18
- Android Studio 3.0 或以上版本
- App 要求 Android 4.3 或以上设备

## 运行示例项目

这个段落主要讲解了如何编译和运行实例程序。

### 创建网易云信账号并获取App Key

在编译和启动实例程序前，您需要首先获取一个可用的`App Key`:

1. 若您已经与专属客户经理取得联系，可直接向他获取Appkey

2. 若您并未与专属客户经理取得联系那么请按后续步骤获取Appkey

3. 首先在 [网易云信](https://id.163yun.com/register?h=media&t=media&clueFrom=nim&from=bdjjnim0035&referrer=https://app.yunxin.163.com/?clueFrom=nim&from=bdjjnim0035) 注册账号

4. 然后在「应用」一栏中创建您的项目

5. 等待专属客户经理联系您，并向他获取Appkey

6. 将 AppID 填写进 "app/src/main/res/values/strings.xml"

```xml
<!-- 替换为你自己的AppKey -->
<string name="app_key">Your App Key</string>
```

### 集成SDK

集成方式有两种，通过Maven集成和通过SDK库文件集成

#### 通过Maven集成（**强烈推荐**）

在项目对应的模块的 `app/build.gradle` 文件的依赖属性中加入通过 Maven 自动集成 SDK 的地址：

```gradle
implementation 'com.netease.yunxin:nertc:' + versionName
```

#### 通过SDK库文件集成

Android [视频通话 SDK](https://dev.yunxin.163.com/docs/product/音视频通话G2/SDK下载)

下载的文件包括 libs 文件和 sample 文件，其中 libs 文件包括：

| 文件/文件夹名称     | 文件类型      |
| ------------------- | ------------- |
| nertc-sdk-x.x.x.jar | Java JAR 文件 |
| arm64-v8a           | 文件夹        |
| armeabi-v7a         | 文件夹        |
| x86                 | 文件夹        |

##### 添加 SDK

1. 设置 libs 存放路径。使用 Android Studio 打开你想要运行的项目，选择 *app/src/build.gradle* 文件，将预设的 libs 路径添加到 fileTree 代码行中。

   ![img](https://yx-web-nosdn.netease.im/quickhtml%2Fassets%2Fyunxin%2Fdefault%2FandroidStudioConfig.jpg)

**注意SDK依赖的JDK版本为Java 8**

1. 添加 libs 文件包。根据步骤 1 中预设的路径添加 libs 文件包。
2. 同步项目文件。点击 **Sync Project With Gradle Files** 按钮，直到同步完成。

## 功能实现

### 初始化

导入以下 NERTC API 包:

- `com.netease.lava.nertc.sdk.NERtcConstants`
- `com.netease.lava.nertc.sdk.NERtcCallback`
- `com.netease.lava.nertc.sdk.NERtcEx`
- `com.netease.lava.nertc.sdk.NERtcParameters`
- `com.netease.lava.nertc.sdk.video.NERtcVideoView`
- `com.netease.lava.nertc.sdk.video.NERtcRemoteVideoStreamType`

进入房间之前，调用 `init` 进行初始化。在该方法中:

- 填入后台应用注册的 **AppKey**。只有 **AppKey** 相同的应用程序才能进入同一个房间进行互通。
- 指定一个事件回调。SDK 通过指定的事件通知应用程序 SDK 的运行事件，如: 加入或离开房间，新用户加入房间等。

```java
import com.netease.lava.nertc.sdk.NERtcCallback;
import com.netease.lava.nertc.sdk.NERtcConstants;
import com.netease.lava.nertc.sdk.NERtcEx;
import com.netease.lava.nertc.sdk.NERtcParameters;
import com.netease.lava.nertc.sdk.video.NERtcRemoteVideoStreamType;
import com.netease.lava.nertc.sdk.video.NERtcVideoView;

...

private void setupNERtc() {
    NERtcParameters parameters = new NERtcParameters();
    parameters.set(NERtcParameters.KEY_AUTO_SUBSCRIBE_AUDIO, false);
    NERtcEx.getInstance().setParameters(parameters); //先设置参数，后初始化

    try {
        NERtcEx.getInstance().init(getApplicationContext(), getString(R.string.app_key), this, null);
        setAudioEnable(true);
        setVideoEnable(true);
    } catch (Exception e) {
        Toast.makeText(this, "SDK初始化失败", Toast.LENGTH_LONG).show();
        finish();
    }
}
```

### 加入房间

在加入房间前，请确保你已完成环境准备、安装包获取等步骤。

#### 加入通信房间

调用 `joinChannel` 方法加入房间。在该方法中:

在该方法中：

- 传入能标识用户角色和权限的 `Token`。如果安全要求不高，也可以将值设为 null。Token 需要在应用程序的服务器端生成，具体生成办法，详见 [密钥说明](https://dev.yunxin.163.com/docs/product/音视频通话G2/服务端API文档?pos=toc-2-15)。
- 传入能标识房间的房间名称。输入相同房间名称的用户会进入同一个房间。
- 房间内每个用户的 UID 必须是唯一的。

> 如果已在房间中，用户必须调用 `leaveChannel` 方法退出当前房间，才能进入下一个房间。

```java
NERtcEx.getInstance().joinChannel(null, roomID, userID);
```

### 发布和订阅音视频流

在发布和订阅音视频流前，请确保你已完成环境准备、安装包获取等步骤，并成功加入房间。

#### 打开视频模式

调用 `enableLocalVideo` 方法打开视频模式，调用 `enableLocalAudio` 方法打开音频模式。您也可以根据需要关闭默认，在加入房间后自行调用该方法进行打开。

- 如果在通话过程前和过程中都可以通过以下接口实现音视频的开关。

```java
NERtc.getInstance().enableLocalAudio(boolean enable);
NERtc.getInstance().enableLocalVideo(boolean enable);
```

#### 设置本地视频视图

本地视频视图，是指用户在本地设备上看到的本地视频流的视图。

在加入房间前，调用 `setupLocalVideoCanvas` 方法使应用程序绑定本地视频流的显示视窗，并设置本地看到的本地视频视图。`setupLocalVideoCanvas` 参数默认为 `NERtcVideoView`，`NERtcVideoView` 可以通过:

- 将 setZOrderMediaOverlay 设置为 true，用以覆盖父视图;
- 通过 setScalingType 设置 View 的缩放模式;

调用 `setupLocalVideoCanvas` 将新画布 对象传递给引擎，该引擎绑定本地视频流的视频窗口(视图) 并配置视频的显示设置;

```java
localUserVv.setZOrderMediaOverlay(true);
localUserVv.setScalingType(NERtcConstants.VideoScalingType.SCALE_ASPECT_FIT);
NERtcEx.getInstance().setupLocalVideoCanvas(localUserVv);
```

#### 订阅远端视频

订阅视频是指在通话中根据用户需要，选择是否查看远端某个用户的视频

在收到远端用户视频发布回调 `onUserVideoStart(long uid,int maxProfile)` 后，可以根据回调中的uid以及maxProfile选择合适的分辨率进行视频订阅 `subscribeRemoteVideoStream` 分辨率档位可参看 [视频档位](https://dev.yunxin.163.com/docs/product/音视频通话G2/SDK开发集成/Android开发集成/视频管理)

```java
NERtcEx.getInstance().subscribeRemoteVideoStream(uid, NERtcRemoteVideoStreamType.kNERtcRemoteVideoStreamTypeHigh, true);
```

#### 设置远端视频视图

远端视频视图，是指用户在本地设备上看到的远端视频流的视图。

调用 `setupRemoteVideoCanvas` 方法设置本地看到的远端用户的视频视图。

用户需要在该方法中指定想要看到的远端视图的用户 **UID**。 UID可以在收到其他用户发布视频的回调事件 `onUserVideoStart` 中获取。

```java
remoteUserVv.setScalingType(NERtcConstants.VideoScalingType.SCALE_ASPECT_FIT);
NERtcEx.getInstance().setupRemoteVideoCanvas(remoteUserVv, uid);
```

### 离开房间

通话或直播结束时，你可以调用 `leaveChannel` 方法离开房间，结束或退出通话或直播。

不论当前是否还在直播中，调用该方法会把直播相关的所有资源释放掉。`leaveChannel` 并不会直接让用户离开房间。调用该方法后 SDK 会触发 `onLeaveChannel` 回调。

```java
NERtcEx.getInstance().leaveChannel();
```

**如果在调用** `leaveChannel` **方法后立即使用** `release`**，则退出房间会被打断，SDK 也不会触发** `onLeaveChannel` **回调。**