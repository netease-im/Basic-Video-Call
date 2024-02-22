# 快速入门

本文介绍在鸿蒙平台下如何快速运行 NERtc DEMO 以及集成 NERtc SDK到项目中。

## 环境要求

- DevEco Studio 4.0 Release及以上。
- HarmonyOS SDK API 10 及以上。

## 操作步骤

### 步骤1: 创建应用
创建应用并获取 AppKey，详情见链接：[点这里](https://doc.yunxin.163.com/console/docs/TIzMDE4NTA?platform=console)

### 步骤2: 配置AppKey

在应用配置中获取到AppKey配置到DEMO中。

![WX20240222-101914.png](img%2FWX20240222-101914.png)

![WX20240222-102042.png](img%2FWX20240222-102042.png)


### 步骤3: 编译运行

1.打开 RTC DEMO 配置签名：

![WX20240222-102536.png](img%2FWX20240222-102536.png)

![WX20240222-102735.png](img%2FWX20240222-102735.png)

2.连接真机，编译运行:

![WX20240222-102948.png](img%2FWX20240222-102948.png)


## DEMO 运行流程

进入首页后，需要用户手动申请权限，否则入会后会导致音视频采集设备无法正常工作。
和 NERtcSDK 交互的代码在子线程 Worker.ets 文件中。

![process.png](img%2Fprocess.png)


## SDK 接入流程

1.拷贝 sdk.har 到项目文件夹中，例如： entry/src/main/libs

2.DEMO 工程下 oh-package.json5 配置 sdk.har 如下图所示：

![WX20240222-105552.png](img%2FWX20240222-105552.png)

3.安装第三方包，点击 Run 'ohpm install'

![WX20240222-105813.png](img%2FWX20240222-105813.png)

4.调用SDK接口，完成入会流程

```typescript

//伪代码

//从SDK中导入相关的interface或者class        
import { NERtcCallbackEx, NERtcConstants, NERtcSDK } from 'sdk';
        
//初始化引擎, 参数列表分别为: appkey, SDK回调callback, 初始化参数option(可选).
NERtcSDK.getInstance().init(key, new ChatCallback(), option)
        
//入会：参数列表：鉴权token, 频道名，用户id
NERtcSDK.getInstance().joinChannel(join.token, join.cname, BigInt(join.uid))      

//离会：
NERtcSDK.getInstance().leaveChannel()        
        
//打开视频：
NERtcSDK.getInstance().enableLocalVideo(true)
        
//设置本地和远端画布
NERtcSDK.getInstance().setupLocalVideoCanvas(canvas)
NERtcSDK.getInstance().setupRemoteVideoCanvas(canvas, BigInt(setUp.uid))


```

## 运行DEMO

1.下载 rtc_demo hap包 [rtc_demo.zip](output%2Frtc_demo.zip)

2.将华为设备ID交与云信技术支持，将您的设备ID添加到云信后台白名单中

3.执行安装命令来安装hap包
```
$ hdc uninstall com.netease.lava.nertc.demo
$ hdc shell mkdir data/local/tmp/6fb0eb90b6f94ae3b290619566d9b79c
$ hdc file send "/Users/zhangchenliang/Workspace/lava-stable/mobile-sdk/harmony/entry/build/default/outputs/default/demo-default-signed.hap" "data/local/tmp/6fb0eb90b6f94ae3b290619566d9b79c"
$ hdc shell bm install -p data/local/tmp/6fb0eb90b6f94ae3b290619566d9b79c 
$ hdc shell rm -rf data/local/tmp/6fb0eb90b6f94ae3b290619566d9b79c
$ hdc shell aa start -a EntryAbility -b com.netease.lava.nertc.demo
```