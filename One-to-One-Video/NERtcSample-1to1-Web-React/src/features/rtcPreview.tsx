import * as NERTC from "nertc-web-sdk";
import type { Client } from "nertc-web-sdk/types/client";
import type { Stream } from "nertc-web-sdk/types/stream";
import { EventEmitter } from "eventemitter3";
import { getRandomInt, getAppToken } from "@/utils";

interface RTCPreviewOptions {
  appkey: string;
  secret: string;
}
class RTCPreview extends EventEmitter {
  public client: Client | null = null;
  public localStream: Stream | null = null;
  public appkey: string = "";
  public secret: string = "";
  public networkInfo = {
    uplinkNetworkQuality: 0,
    downlinkNetworkQuality: 0,
  };

  constructor(options: RTCPreviewOptions) {
    super();
    console.log("RTCPreview constructor", options);
    this.appkey = options.appkey;
    this.secret = options.secret;
    this.client = NERTC.createClient({
      appkey: this.appkey,
      debug: true,
    });
    this.localStream = NERTC.createStream({
      audio: true,
      video: true,
      client: this.client,
    }) as Stream;
  }

  //暴露localStream，方便直接调用sdk的接口API
  get stream() {
    return this.localStream;
  }

  async init() {
    try {
      this.initEvents();
      // 检查麦克风、摄像头权限
      await this.localStream?.init();
      //获取麦克风设备列表
      const microphoneDevices = await NERTC.getMicrophones();
      let options = microphoneDevices.map((item) => ({
        label: item.label, // 显示文本
        value: item.deviceId, // 实际值
      }));
      this.emit("microphoneDevices", options);
      //获取摄像头设备列表
      const cameras = await NERTC.getCameras();
      options = cameras.map((item) => ({
        label: item.label, // 显示文本
        value: item.deviceId, // 实际值
      }));
      this.emit("cameraDevices", options);
    } catch (error: unknown) {
      console.error("Error checking environment:", error);
      this.emit("error", {
        reason: "initError",
        message: (error as Error).message,
      });
    }
  }

  initEvents() {
    //@ts-ignore
    //this.client?.removeAllListeners();
    this.client?.on("accessDenied", (type) => {
      console.warn(`${type} 设备权限被禁止了`);
      this.emit("DeviceError", {
        mediaType: type,
        reason: "accessDenied",
        message: `${type} 设备权限被禁止了，请检查系统设置或者浏览器设置`,
      });
    });
    this.client?.on("notFound", (type) => {
      console.warn(`${type} 设备没有找到`);
      this.emit("DeviceError", {
        mediaType: type,
        reason: "notFound",
        message: `${type} 设备没有找到`,
      });
    });
    this.client?.on("beOccupied", (type) => {
      console.warn(`${type} 设备不可用, 系统或者设备驱动异常引起`);
      this.emit("DeviceError", {
        mediaType: type,
        reason: "beOccupied",
        message: `${type} 设备被占用或者系统驱动异常引起，请重启应用或者系统`,
      });
    });
    this.client?.on("deviceError", (type) => {
      this.emit("DeviceError", {
        mediaType: type,
        reason: "deviceError",
        message: `${type} 设备不支持设置的profile参数, 请换一个设备`,
      });
    });
    //@ts-ignore
    this.localStream?.removeAllListeners();
    this.localStream?.on("device-error", (data) => {
      console.warn("设备异常:", data);
    });
  }

  async supportRTC() {
    // 检查是否支持NERTC
    const checkResult = await NERTC.checkBrowserCompatibility();
    let supportRTC = false;
    if (
      checkResult &&
      checkResult.isPushStreamSupport &&
      checkResult.isPushStreamSupport
    ) {
      supportRTC = true;
    }
    return supportRTC;
  }

  async getMicrophones() {
    const microphoneDevices = await NERTC.getMicrophones();
    let options = microphoneDevices.map((item) => ({
      label: item.label, // 显示文本
      value: item.deviceId, // 实际值
    }));
    return options;
  }

  async getCameras() {
    const cameras = await NERTC.getCameras();
    const options = cameras.map((item) => ({
      label: item.label, // 显示文本
      value: item.deviceId, // 实际值
    }));
    return options;
  }

  async checkNetwork() {
    //实现逻辑为，使用client作为推流端，然后使用downClient作为拉流端
    return new Promise(async (resolve, reject) => {
      try {
        console.warn("开始检测网络质量");
        const upUid = getRandomInt(100, 10000); //随机用户Id
        const downUid = getRandomInt(100, 10000); //随机用户Id
        const channelName = "TEST_" + Date.now(); //RTC房间名，加上时间戳防止干扰
        const upClient = this.client as Client;
        const downClient = NERTC.createClient({
          appkey: this.appkey,
          debug: true,
        });
        //监听上行推流用户实际网络质量
        upClient.on("network-quality", (evt) => {
          console.log("upClient network-quality: " + JSON.stringify(evt)); //检测用户上行的网络质量
        });
        //监听下行拉流用户实际网络质量
        downClient.on("network-quality", async (evt) => {
          console.log("downClient network-quality: " + JSON.stringify(evt)); //检测用户下行的网络质量
          let result = evt.find((item) => item.uid === upUid);
          this.networkInfo.uplinkNetworkQuality =
            result?.uplinkNetworkQuality as number;
          result = evt.find((item) => item.uid === downUid);
          this.networkInfo.downlinkNetworkQuality =
            result?.downlinkNetworkQuality as number;
        });
        await this.upClientPub(upUid, channelName, upClient);
        await this.downClientSub(downUid, channelName, downClient);
        //服务器检查网络质量需要时间，这里限制5秒
        setTimeout(async () => {
          console.warn(
            "检测网络质量结束: ",
            JSON.stringify(this.networkInfo, null, " "),
          );
          resolve(this.networkInfo);
          //清除资源
          await downClient.leave();
          downClient.destroy();
          NERTC.destroy(downClient);
          upClient.leave();
        }, 5 * 1000);
      } catch (error) {
        console.error("checkNetwork error: ", (error as Error).message);
        reject({
          reason: "initError",
          message: (error as Error).message,
        });
      }
    });
  }

  async upClientPub(uid: number, channelName: string, upClient: Client) {
    try {
      console.log("upClientPub... " + uid + " channelName: " + channelName);
      const token = await getAppToken({
        appkey: this.appkey,
        secret: this.secret,
        uid: uid.toString(),
        channelName,
      });
      await upClient.join({
        channelName,
        uid,
        token,
      });
      console.log("upClient加入房间成功..." + uid);
      if (!this.localStream) {
        return;
      }
      await upClient.publish(this.localStream);
      console.log("本地 publish 成功");
    } catch (error) {
      console.error("upClientPub error: ", (error as Error).message);
    }
  }

  async downClientSub(uid: number, channelName: string, downClient: Client) {
    try {
      //回调事件-远端用户已发流
      downClient.on("stream-added", (evt) => {
        console.log("远端有流来: " + evt.mediaType);
        const remoteStream = evt.stream;
        remoteStream.setSubscribeConfig({
          audio: true,
          video: true,
        });
        downClient.subscribe(remoteStream);
      });
      //回调事件-远程音视频流已订阅
      downClient.on("stream-subscribed", (evt) => {
        console.log("订阅远端流成功: ", evt);
        //此处仅仅是坚持网络连接，不需要渲染订视频流
      });
      const token = await getAppToken({
        appkey: this.appkey,
        secret: this.secret,
        uid: uid.toString(),
        channelName,
      });
      await downClient.join({
        channelName,
        uid,
        token,
      });
      console.log("接收方加入房间成功...");
    } catch (error) {
      console.error("downClientSub error: ", (error as Error).message);
    }
  }

  destroy() {
    console.log("RTCPreview destroy()");
    this.localStream?.destroy();
    this.client?.destroy();
    NERTC.destroy(this.client as Client);
  }
}
export default RTCPreview;
