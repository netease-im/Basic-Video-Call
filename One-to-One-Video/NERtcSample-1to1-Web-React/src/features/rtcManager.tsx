import * as NERTC from "nertc-web-sdk";
import type { Client } from "nertc-web-sdk/types/client";
import type { Stream } from "nertc-web-sdk/types/stream";
import type { NetStatusItem } from "nertc-web-sdk/types/types";
import { EventEmitter } from "eventemitter3";
import { getRandomInt, getAppToken, getSystemInfo } from "@/utils";
import type { Timer } from "@/types";

interface RtcManagerOptions {
  appkey: string;
  secret?: string;
}

interface joinOptions {
  channelName: string;
  uid?: string | number;
  customData?: string;
  token?: string;
}

class RTCManager extends EventEmitter {
  public appkey: string = "";
  public secret: string | undefined = undefined;
  public channelName: string = "";
  public uid: string | number = 0;

  private client: Client | null = null;
  private localStream: Stream | null = null;
  private remoteStream: Stream | null = null;
  //本产品仅仅支持一个远端流，针对为点对点通话场景（这里仅仅是记录一下，并不会订阅或者渲染）
  private remoteStreamMap = new Map<string, Stream>();

  private localVideoView: HTMLElement | null = null;
  private remoteVideoView: HTMLElement | null = null;

  private mediaTimer: Timer | null = null;

  constructor(options: RtcManagerOptions) {
    super();
    this.appkey = options.appkey;
    this.secret = options.secret;
    this.initClient();
  }

  //暴露localStream，方便直接调用sdk的接口API
  get nertLocalStream() {
    return this.localStream;
  }

  //暴露client，方便直接调用sdk的接口API
  get nertClient() {
    return this.client;
  }

  get localView() {
    return this.localVideoView;
  }

  async getCameras() {
    return NERTC.getCameras();
  }

  interval() {
    if (this.mediaTimer) {
      clearInterval(this.mediaTimer);
    }
    this.mediaTimer = setInterval(async () => {
      const audioStats = await this.client?.getLocalAudioStats();
      const videoStats = await this.client?.getLocalVideoStats("video");
      // console.log('audioStats: ', audioStats);
      // console.log('videoStats: ', videoStats);
      this.emit("media-info", {
        audioLevel: this.localStream?.getAudioLevel() || 0,
        audioBitrate: audioStats[0]?.SendBitrate || 0,
        videoBitrate: videoStats[0]?.SendBitrate || 0,
        videoFrameRate: videoStats[0]?.SendFrameRate || 0,
        videoFrameWidth: videoStats[0]?.SendResolutionWidth || 0,
        videoFrameHeight: videoStats[0]?.SendResolutionHeight || 0,
      });
    }, 1000);
  }

  initClient() {
    this.client = NERTC.createClient({
      appkey: this.appkey,
      debug: true,
    });
    //开启日志上传
    NERTC.Logger.enableLogUpload();
    this.initRtcEvents();
  }

  async joinChannel(options: joinOptions) {
    let { channelName, uid, token, customData = "" } = options;
    console.log("joinChannel() options: ", JSON.stringify(options, null, " "));
    if (!channelName) {
      console.error("没有提供channelName, 无法加入房间");
      throw new Error("channelName is required");
    }
    if (!uid) {
      //自定义一个随机数
      uid = getRandomInt(100, 9999);
    }
    this.uid = uid as string | number;
    this.channelName = channelName;
    if (!token) {
      if (this.secret) {
        token = await getAppToken({
          appkey: this.appkey,
          secret: this.secret,
          uid: uid.toString(),
          channelName,
        });
      } else {
        console.error("没有提供secret 和 token，无法加入房间");
        throw new Error("secret or secret is required");
      }
    }
    const { isMobile } = getSystemInfo();
    if (isMobile) {
      console.log("移动端推荐使用VP8软编");
      this.client?.setCodecType("VP8");
    }

    return this.client?.join({
      channelName,
      uid: this.uid,
      token,
      customData: customData,
    });
  }

  async initLocalStream(config?: {
    audio: boolean;
    video: boolean;
    microphoneId: string;
    cameraId: string;
  }) {
    this.localStream = NERTC.createStream({
      video: config ? config.video : true,
      audio: config ? config.audio : true,
      microphoneId: config ? config.microphoneId : "",
      cameraId: config ? config.cameraId : "",
    }) as Stream;

    //音频默认即可
    this.localStream.setAudioProfile("speech_low_quality");
    //主流建议使用720p/30fps
    const videoProfile = {
      resolution: NERTC.VIDEO_QUALITY.VIDEO_QUALITY_720p,
      frameRate: NERTC.VIDEO_FRAME_RATE.CHAT_VIDEO_FRAME_RATE_30,
    };
    this.localStream.setVideoProfile(videoProfile);
    return this.localStream.init();
  }

  async playLocalStream(view: HTMLElement) {
    console.log("playLocalStream() view: ", view);
    if (!view) {
      throw new Error("playLocalStream(): view is required");
    }
    if (!this.localStream) {
      throw new Error("Local stream is not initialized");
    }
    try {
      this.localVideoView = view;
      await this.localStream.play(view, { video: true, muted: true });
      this.localStream.setLocalRenderMode({
        width: view.clientWidth - 2, // 减去边框宽度
        height: view.clientHeight - 2,
        cut: false,
      });
      this.interval();
    } catch (error) {
      console.error("playLocalStream error: ", (error as Error).message);
      throw error;
    }
  }

  async publish() {
    if (!this.localStream) {
      throw new Error("Local stream is not initialized");
    }
    return this.client?.publish(this.localStream);
  }

  //订阅远端流
  subscribeStream(stream: Stream) {
    console.log("subscribeStream() stream", stream);
    const subscribeConfig = {
      video: true,
      audio: true,
    };
    stream.setSubscribeConfig(subscribeConfig);
    this.client?.subscribe(stream).then(() => {
      console.log("subscribe success");
    });
  }

  //取消订阅远端流
  unsubscribeStream(stream: Stream) {
    console.log("unsubscribeStream() stream: ", stream);
    const unsubscribeConfig = {
      video: true,
      audio: false,
      screen: true,
    };
    return this.client?.unsubscribe(stream, unsubscribeConfig);
  }

  async playRemoteAudioStream(uid?: string | number) {
    console.log("playRemoteAudioStream() uid: ", uid);

    if (!this.remoteStream) {
      throw new Error("remoteStream is not initialized");
    }
    try {
      // 在UI窗口上显示静音图标，用户手动点击图标后在播放音频
      await this.remoteStream?.play(this.remoteVideoView as HTMLElement, {
        video: false,
        audio: true,
        muted: false,
      });
    } catch (error) {
      console.error("playRemoteAudioStream error: ", (error as Error).message);
      throw error;
    }
  }

  async playRemoteVideoStream(view: HTMLElement, uid?: string | number) {
    console.log("playRemoteVideoStream() view: ", view, uid);
    if (!view) {
      throw new Error("playRemoteVideoStream(): view is required");
    }
    if (!this.remoteStream) {
      throw new Error("remoteStream is not initialized");
    }
    try {
      this.remoteVideoView = view;
      //将音频mute后进行播放，保证规避浏览器的自动播发逻辑受限的限制，
      // 在UI窗口上显示静音图标，用户手动点击图标后在播放音频
      await this.remoteStream?.play(view, {
        video: true,
        audio: false,
        muted: true,
      });
      this.remoteStream.setRemoteRenderMode({
        width: view.clientWidth - 2, // 减去边框宽度
        height: view.clientHeight - 2,
        cut: false,
      });
    } catch (error) {
      console.error("playRemoteVideoStream error: ", (error as Error).message);
      throw error;
    }
  }

  resumeRemoteStream() {
    console.log("resumeRemoteStream()");
    if (this.remoteStream) {
      this.remoteStream?.resume();
    }
  }

  swapVideos() {
    //大小屏幕切换
    console.log("swapVideos() 大小屏幕切换");
    if (this.localVideoView && this.remoteVideoView) {
    } else {
      //console.warn('swapVideos() localVideoView or localVideoView is not initialized');
      return false;
    }
    try {
      this.localStream?.stop("video");
      this.remoteStream?.stop("video");
      const localVideoView = this.localVideoView;
      const remoteVideoView = this.remoteVideoView;
      this.playLocalStream(remoteVideoView as HTMLElement);
      this.playRemoteVideoStream(localVideoView as HTMLElement);
      return true;
    } catch (error) {
      console.error("swapVideos error: ", (error as Error).message);
      return false;
    }
  }

  getChannelInfo() {
    return this.client?.getChannelInfo();
  }

  leaveChannel() {
    if (this.mediaTimer) {
      clearInterval(this.mediaTimer);
      this.mediaTimer = null;
    }
    this.client?.leave();
    this.localStream?.destroy();
    this.client?.destroy();
  }

  //RTC事件监听
  initRtcEvents() {
    this.initMediaDeviceEvents();
    this.client?.on("peer-online", (evt) => {
      console.warn("[NERTC通知]: 收到新用户加入房间的通知: ", evt.uid);
      this.emit("peer-online", {
        uid: evt.uid.toString(),
      });
    });

    this.client?.on("peer-leave", (evt) => {
      //@ts-ignore
      const { uid, reason } = evt;
      console.warn(
        "[NERTC通知]: 收到用户离开房间的通知: ",
        uid,
        "reason: ",
        reason,
      );
      //删除对应的stream
      this.remoteStreamMap.delete(uid.toString());
      if (this.remoteStream?.getId()?.toString() === uid.toString()) {
        this.remoteStream = null;
      }

      this.emit("peer-leave", {
        uid: evt.uid.toString(),
        reason,
      });
    });
    this.client?.on("stream-added", (evt) => {
      const remoteStream = evt.stream;
      console.log(
        "[NERTC通知]: 收到别人的发布消息: ",
        remoteStream.getId(),
        "mediaType: ",
        evt.mediaType,
      );
      if (!this.remoteStream) {
        this.remoteStream = remoteStream;
        this.initSreamEvents(remoteStream);
      }
      const streamId = remoteStream.getId()?.toString() as string;
      //重复设置 streamId 对应的stream
      this.remoteStreamMap.set(streamId, remoteStream);
      //仅仅订阅第一次收到的remoteStream
      this.subscribeStream(this.remoteStream);
    });

    this.client?.on("stream-subscribed", (evt) => {
      console.warn("[NERTC通知]: 远端流订阅成功: ", evt);
      //订阅成功后，播放逻辑放到rtc外面去做
      this.emit("stream-need-play", {
        uid: evt.stream.getId()?.toString(),
        mediaType: evt.mediaType,
      });
    });

    this.client?.on("stream-removed", (evt) => {
      const remoteStream = evt.stream;
      console.warn(
        "[NERTC通知]: 收到别人停止发布的消息: ",
        remoteStream.getId(),
        "mediaType: ",
        evt.mediaType,
      );
      remoteStream.stop(evt.mediaType);
      this.emit("stream-removed", {
        uid: remoteStream.getId()?.toString(),
        mediaType: evt.mediaType,
      });
    });

    this.client?.on("network-quality", async (evt: NetStatusItem[]) => {
      // console.log(
      //   "[NERTC通知]: 网络质量network-quality: " + JSON.stringify(evt),
      // );
      const networkInfo = { local: 0, remote: 0 };
      evt.forEach((item) => {
        if (item.uid.toString() === this.uid.toString()) {
          networkInfo.local = item.uplinkNetworkQuality;
        }
        if (item.uid.toString() === this.remoteStream?.getId()?.toString()) {
          networkInfo.remote = item.uplinkNetworkQuality;
        }
      });
      this.emit("network-quality", networkInfo);
    });
  }

  //初始化stream事件
  initSreamEvents(stream: Stream) {
    stream.on("notAllowedError", (evt) => {
      //@ts-ignore
      const errorCode = evt.getCode();
      console.warn("收到音频自动播放受限的通知: ", stream.getId(), evt);
      if (errorCode === 41030) {
        console.warn("自动播放策略阻止：" + stream.getId());
      }
    });
  }

  initMediaDeviceEvents() {
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
        message: `${type} 设备不可用, 设备被占用或者系统驱动异常引起，请重启应用或者系统`,
      });
    });
    this.client?.on("deviceError", (type) => {
      this.emit("DeviceError", {
        mediaType: type,
        reason: "deviceError",
        message: `${type} 设备不支持设置的profile参数, 请换一个设备`,
      });
    });
    this.localStream?.on("device-error", (data) => {
      console.warn("设备异常:", data);
    });
  }

  destroy() {
    console.log("destroy()");
    this.leaveChannel();
    NERTC.destroy(this.client as Client);
  }
}

export default RTCManager;
