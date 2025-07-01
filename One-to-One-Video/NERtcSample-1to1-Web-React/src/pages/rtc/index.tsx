import React, { useState, useEffect, useRef, useCallback } from "react";
import "./index.css";
import type { MediaInfo } from "@/types";
import { Toast } from "antd-mobile";
import { useNavigate } from "react-router-dom";
import { SoundMuteOutline } from "antd-mobile-icons";
import muteIcon from "@/assets/mute.png";
import unmuteIcon from "@/assets/unmute.png";
import closeCameraIcon from "@/assets/camera-opned.png";
import openCameraIcon from "@/assets/camera-closed.png";
import flipCameraIcon from "@/assets/camera-flip.png";
import overIcon from "@/assets/over.png";
import { appkey, secret } from "@/config";
import Pip from "@/components/Pip";
import type { PipHandle } from "@/components/Pip";
import NetworkSignal from "@/components/networkSignal";
import type { SignalLevel } from "@/components/networkSignal";
import RTCManager from "@/features/rtcManager";
import { useAppContext } from "@/store/index";
import useVisibility from "@/hooks/useVisibility";
import { throttle } from "lodash-es";
import type { PEER_LEAVE_REASON_CODE } from "nertc-web-sdk/types/types";

const RTC: React.FC = () => {
  const navigate = useNavigate();
  const visibility = useVisibility();
  const { meetingInfo, setMeetingInfo } = useAppContext();
  const [isMuted, setIsMuted] = useState(false);
  const remoteUid = useRef<string>("");
  const rtcManagerRef = useRef<RTCManager | null>(null);
  const largeVideoRef = useRef<HTMLDivElement>(null);
  const smallVideoRef = useRef<PipHandle>(null);
  const [meidaInfo, setMediaInfo] = useState<MediaInfo>({
    audioLevel: 0,
    audioBitrate: 0,
    videoBitrate: 0,
    videoFrameRate: 0,
    videoFrameWidth: 0,
    videoFrameHeight: 0,
    uplinkNetworkQuality: 0,
    downlinkNetworkQuality: 0,
  });

  const [localSignalLevel, setLocalSignalLevel] = useState<SignalLevel>(3); // 初始强信号
  const [remoteSignalLevel, setRemoteSignalLevel] = useState<SignalLevel>(3); // 初始强信号
  const [muted, setMuted] = useState(false);
  const [cameraOpened, setCameraOpened] = useState(true);
  const [facingMode, setFacingMode] = useState<"user" | "environment">("user"); // 默认前置摄像头
  const [isLocalVideoLarge, setIsLocalVideoLarge] = useState(false);

  useEffect(() => {
    //这一段是示例代码，业务方需要自己实现
    const sendFinalRequest = () => {
      console.log("页面离开主动通知服务器，广播给房间中的其他人");
      return;
      //下面是示例代码，本Demo没有业务服务器所以没有实现这部分逻辑
      // 客户自己可以实现自己的业务服务器，然后调用下面的接口
      const analyticsData = {
        page: window.location.pathname,
        content: "本人主动离开了页面，需要服务器感知",
        // 其他需要上报的数据
      };

      // 使用Blob可以发送更复杂的数据结构
      const blob = new Blob([JSON.stringify(analyticsData)], {
        type: "application/json; charset=UTF-8",
      });

      /**
       * navigator.sendBeacon() 是一个专门为在页面卸载时可靠地发送数据到服务器而设计的API。
       * - 页面卸载时仍能可靠发送
       * - 异步不阻塞页面卸载
       * - 自动处理网络问题
       */
      //发送给你的业务服务器
      navigator.sendBeacon("your-api-endpoint", blob);
    };

    // 同时监听多个事件确保覆盖各种情况
    const events = ["pagehide", "beforeunload", "unload"];
    events.forEach((event) => {
      window.addEventListener(event, sendFinalRequest);
    });

    return () => {
      events.forEach((event) => {
        window.removeEventListener(event, sendFinalRequest);
      });
    };
  }, []);

  React.useEffect(() => {
    //这里可以监听页面可见性变化，当页面不可见时mute视频
    //PS: visibility目前判断的不够准确，先忽略
    console.log(`当前可见性状态: ${visibility}`);
    return;
    if (visibility === "hidden") {
      // 页面进入后台时的逻辑
      console.log("页面进入后台，mute视频");
      rtcManagerRef.current?.nertLocalStream?.muteVideo();
    } else {
      // 页面回到前台时的逻辑
      console.log("页面回到前台，unmute视频");
      rtcManagerRef.current?.nertLocalStream?.unmuteVideo();
    }
  }, [visibility]);

  useEffect(() => {
    console.log("meetingInfo:", meetingInfo);
    const catchMeetingInfo = localStorage.getItem("meetingInfo");
    console.log("catchMeetingInfo:", catchMeetingInfo);
    let channelName = meetingInfo.channelName;
    if (catchMeetingInfo && !channelName) {
      channelName = JSON.parse(catchMeetingInfo).channelName;
      setMeetingInfo(JSON.parse(catchMeetingInfo));
    }
    if (!channelName) {
      navigate("/");
    }
    if (channelName && !rtcManagerRef.current) {
      createNERTCEngine(channelName);
    }
    return () => {
      if (rtcManagerRef.current) {
        rtcManagerRef.current.destroy();
        rtcManagerRef.current = null;
      }
    };
  }, []);

  useEffect(() => {
    if (!rtcManagerRef.current?.localView) {
      return;
    }
    if (
      rtcManagerRef.current.localView === smallVideoRef.current?.getElement()
    ) {
      setIsLocalVideoLarge(false);
    } else {
      //此时进行了大小屏切换，右上角展示的是远端视频画面
      setIsLocalVideoLarge(true);
    }
  }, [rtcManagerRef.current?.localView]);

  const createNERTCEngine = async (channelName: string) => {
    console.warn("开始创建NERTC引擎");
    rtcManagerRef.current = new RTCManager({
      appkey,
      secret,
    });
    //@ts-ignore
    window.rtc = rtcManagerRef.current;
    initRTCManagerEvents();
    initNERTCEvents();
    await join(channelName);
  };

  const join = async (channelName: string) => {
    try {
      console.log("开始加入房间");
      await rtcManagerRef.current?.joinChannel({
        channelName,
      });
      console.log("加入房间成功, 开始初始化本地流");
      //保存到本地，用于刷新当前页面进入房间的场景
      localStorage.setItem("meetingInfo", JSON.stringify(meetingInfo));
      await initLocalStream();
    } catch (error) {
      const message = "加入房间失败: " + (error as Error).message;
      console.error(message);
      Toast.show({
        content: message,
        icon: "fail",
        duration: 5000,
      });
    }
  };

  const initLocalStream = async () => {
    console.log("开始初始化本地流");
    //使用检测页面选择的摄像头
    await rtcManagerRef.current?.initLocalStream({
      audio: true,
      video: true,
      microphoneId: meetingInfo.microphoneId || "",
      cameraId: "", //移动端使用前置后置摄像头选择
    });
    console.log("开始播放本地流");
    //默认小窗口渲染本端视频
    const view = smallVideoRef.current?.getElement() as HTMLDivElement;
    await rtcManagerRef.current?.playLocalStream(view);
    //业务上实现本地镜像
    const videoElement = view.querySelector("video");
    if (videoElement) {
      videoElement.style.transform += "scaleX(-1)";
      console.log("开始发布本地流");
    }
    await rtcManagerRef.current?.publish();
  };

  const initRTCManagerEvents = () => {
    if (!rtcManagerRef.current) {
      return;
    }
    rtcManagerRef.current.on(
      "DeviceError",
      (result: {
        mediaType: "audio" | "video";
        reason: string;
        message: string;
      }) => {
        console.error("检测到设备异常: ", JSON.stringify(result, null, " "));
        Toast.show({
          content: result.message,
          icon: "fail",
        });
      },
    );

    rtcManagerRef.current.on("peer-online", (result: { uid: string }) => {
      console.warn("[RTCManager通知]: 有人加入房间 ", result.uid);
      Toast.show({
        content: `${result.uid}加入房间`,
      });
    });

    rtcManagerRef.current.on(
      "peer-leave",
      (result: { uid: string; reason: PEER_LEAVE_REASON_CODE }) => {
        console.warn(
          "[RTCManager通知]: 有人离开房间 ",
          result.uid,
          "原因: ",
          result.reason,
        );
        Toast.show({
          content: `${result.uid}离开房间，原因: ${result.reason}`,
        });
      },
    );

    rtcManagerRef.current.on(
      "stream-removed",
      (result: { uid: string; mediaType: string }) => {
        console.warn(
          "[RTCManager通知]: ",
          result.uid,
          "停止发布: ",
          result.mediaType,
        );
        Toast.show({
          content: `${result.uid}关闭了${result.mediaType}`,
        });
      },
    );

    rtcManagerRef.current?.on(
      "stream-need-play",
      (evt: { uid: string; mediaType: "audio" | "video" }) => {
        console.log(
          "[RTCManager通知]: 收到媒体需要播放的通知: ",
          JSON.stringify(evt, null, " "),
        );
        remoteUid.current = evt.uid;
        if (evt.mediaType === "audio") {
          setIsMuted(true);
          Toast.show({
            content: "请点击对端窗口的静音图标播放对方声音",
            duration: 5000,
          });
        }
        rtcManagerRef.current?.playRemoteVideoStream(
          largeVideoRef.current as HTMLDivElement,
          evt.uid,
        );
      },
    );
    rtcManagerRef.current?.on("media-info", (evt: Partial<MediaInfo>) => {
      // console.log(
      //   "[RTCManager通知]: media-info: ",
      //   JSON.stringify(evt, null, " "),
      // );
      setMediaInfo((prevState: MediaInfo) => ({ ...prevState, ...evt }));
    });
    rtcManagerRef.current?.on("network-quality", handleNetworkQuality);
  };

  const initNERTCEvents = () => {
    const nertClient = rtcManagerRef.current?.nertClient;
    //用于注册NERTC的原生事件

    nertClient?.on("error", (type: string) => {
      console.error("[NERTC通知]: ERROR: ", type);
      if (type === "SOCKET_ERROR") {
        console.error("[NERTC通知]: 网络断开已经退出房间");
        Toast.show({
          content: "网络断开，请检查网络",
          icon: "fail",
          duration: 5000,
        });
        rtcManagerRef.current?.destroy();
      }
    });
    //@ts-ignore
    nertClient?.on("mute-audio", (result: { uid: string }) => {
      console.warn(`${result.uid} mute自己的音频`);
      Toast.show({
        content: `${result.uid}禁音了`,
      });
    });
    //@ts-ignore
    nertClient?.on("unmute-audio", (result: { uid: string }) => {
      console.warn(`${result.uid} unmute自己的音频`);
      Toast.show({
        content: `${result.uid}恢复声音了`,
      });
    });

    nertClient?.on(
      "connection-state-change",
      (data: { prevState: string; curState: string; reconnect: boolean }) => {
        console.log("[NERTC通知]: change: ", data);
        if (data.reconnect) {
          let content = "网络异常，正在重连";
          if (data.curState === "CONNECTED") {
            content = "网络恢复，重连成功";
          }
          Toast.show({
            content,
          });
        }
      },
    );

    nertClient?.on("TrackEnded", (mediaType: string) => {
      console.log("[NERTC通知]: TrackEnded: ", mediaType);
      resume(mediaType);
      Toast.show({
        content: `检测到${mediaType}异常，正在恢复`,
      });
    });

    nertClient?.on("TrackMuted", (mediaType: string) => {
      console.log("[NERTC通知]: TrackMuted: ", mediaType);
      resume(mediaType);
      Toast.show({
        content: `检测到${mediaType}异常，正在恢复`,
      });
    });

    nertClient?.on("local-track-state", (trackStates: any) => {
      console.log("[NERTC通知]: local-track-state: ", trackStates);
      for (let mediaType in trackStates) {
        const trackState = trackStates[mediaType];
        console.warn(`${mediaType} state: ${trackState.muted}`);
        if (trackState.muted) {
          console.warn("尝试恢复播放", mediaType);
          resume(mediaType);
          Toast.show({
            content: `检测到${mediaType}异常，正在恢复`,
          });
        }
      }
    });

    nertClient?.on("recording-device-changed", (evt: any) => {
      console.log(
        `[NERTC通知]:麦克风设备变化 【${evt.state}】recording-device-changed ${evt.device.label}`,
        evt,
      );
      if (evt.state === "ACTIVE") {
        Toast.show({
          content: `检测到麦克风新设备: ${evt.device.label}`,
        });
      } else if (evt.state === "INACTIVE") {
        Toast.show({
          content: `检测到麦克风拔出: ${evt.device.label}`,
        });
      }
    });

    nertClient?.on("playout-device-changed", (evt: any) => {
      console.log(
        `[NERTC通知]:扬声器设备变化 【${evt.state}playout-device-changed ${evt.device.label}`,
        evt,
      );
      if (evt.state === "ACTIVE") {
        Toast.show({
          content: `检测到扬声器新设备: ${evt.device.label}`,
        });
      } else if (evt.state === "INACTIVE") {
        Toast.show({
          content: `检测到扬声器拔出: ${evt.device.label}`,
        });
      }
    });

    nertClient?.on(
      "mute-video",
      (evt: {
        /**
         * 远端用户 ID。
         */
        uid: number | string;
      }) => {
        console.warn(`[NERTC通知]: ${evt.uid} mute自己的视频`);
        if (evt.uid.toString() === remoteUid.current) {
          console.log("[NERTC通知]: 对端mute自己的视频");
          Toast.show({
            content: "对端推到后台, mute自己的视频",
            duration: 1500,
          });
        }
      },
    );
    nertClient?.on(
      "unmute-video",
      (evt: {
        /**
         * 远端用户 ID。
         */
        uid: number | string;
      }) => {
        console.warn(`[NERTC通知]: ${evt.uid} resume自己的视频`);
        if (evt.uid.toString() === remoteUid.current) {
          console.log("对端resume自己的视频");
          Toast.show({
            content: "对端回到前台, resume自己的视频",
            duration: 1500,
          });
        }
      },
    );
  };

  const resume = (mediaType: string) => {
    console.log("[NERTC通知]: 尝试恢复本地流: ", mediaType);
    if (mediaType === "audio") {
      openTheMicrophone(true);
      openTheMicrophone(true);
    } else if (mediaType === "video") {
      openTheCamera();
      openTheCamera();
    }
  };
  const openTheMicrophone = async (realClose = false) => {
    try {
      console.log("麦克风 muted: ", muted);
      if (muted) {
        console.log("开始打开麦克风");
        //直接调用NERTC SDK的接口
        if (realClose) {
          await rtcManagerRef.current?.nertLocalStream?.open({ type: "audio" });
        } else {
          await rtcManagerRef.current?.nertLocalStream?.unmuteAudio();
        }
        setMuted(false);
      } else {
        console.log("开始关闭麦克风");
        if (realClose) {
          await rtcManagerRef.current?.nertLocalStream?.close({
            type: "audio",
          });
        } else {
          //mute并非真的关闭设备，仅仅发送静音包
          await rtcManagerRef.current?.nertLocalStream?.muteAudio();
        }
        setMuted(true);
      }
    } catch (error) {
      const message = "操作麦克风失败: " + (error as Error).message;
      console.error(message);
      Toast.show({
        content: message,
        icon: "fail",
      });
    }
  };

  const openTheCamera = async () => {
    try {
      console.log("摄像头 cameraOpened: ", cameraOpened);
      if (cameraOpened) {
        console.log("开始关闭摄像头");
        //直接调用NERTC SDK的接口
        await rtcManagerRef.current?.nertLocalStream?.close({ type: "video" });
        setCameraOpened(false);
      } else {
        console.log("开始打开摄像头 facingMode: ", facingMode);
        await rtcManagerRef.current?.nertLocalStream?.open({
          type: "video",
          facingMode,
        });
        console.log("开始播放本地流");
        await rtcManagerRef.current?.playLocalStream(
          rtcManagerRef.current.localView as HTMLElement,
        );
        //业务上实现本地镜像
        const videoElement =
          rtcManagerRef.current?.localView?.querySelector("video");
        videoElement && (videoElement.style.transform += " scaleX(-1)");
        setCameraOpened(true);
      }
    } catch (error) {
      const message = "操作摄像头失败: " + (error as Error).message;
      console.error(message);
      Toast.show({
        content: message,
        icon: "fail",
      });
    }
  };

  const flipCamera = async () => {
    try {
      console.log("切换摄像头 facingMode: ", facingMode);
      const newFacingMode = facingMode === "user" ? "environment" : "user";
      const localStream = rtcManagerRef.current?.nertLocalStream;
      if (!localStream) {
        return;
      }
      await localStream.close({
        type: "video",
      });
      const USER_AGENT = (window.navigator && window.navigator.userAgent) || "";
      const IS_IPAD = /iPad/i.test(USER_AGENT);
      const IS_IPHONE = /iPhone/i.test(USER_AGENT) && !IS_IPAD;
      const IS_IPOD = /iPod/i.test(USER_AGENT);
      const IS_IOS = IS_IPHONE || IS_IPAD || IS_IPOD;
      if (IS_IOS) {
        //苹果手机直接遵守facingMode的设置，所以直接利用该属性完成切换，无需对deviceId进行处理
        await localStream.open({
          type: "video",
          facingMode: newFacingMode,
        });
        console.log("打开摄像头 sucess");
        //考虑到有可能大小屏切换了，所以建议使用rtcManager中记录的localView
        await rtcManagerRef.current?.playLocalStream(
          rtcManagerRef.current.localView as HTMLElement,
        );
        setFacingMode(newFacingMode);
      } else {
        //facingMode参数目前实际测试看，安卓手机前置支持情况还可以，后置表现却是各有千秋，表现诸如选错摄像头、黑屏等问题
        if (newFacingMode === "user") {
          await localStream.open({
            type: "video",
            facingMode: "user",
          });
          console.log("打开摄像头 sucess");
          await rtcManagerRef.current?.playLocalStream(
            rtcManagerRef.current.localView as HTMLElement,
          );
        } else {
          //安卓手机利用deviceId来指定单一的后置摄像头
          const cameraList = (await rtcManagerRef.current?.getCameras()) || [];
          //NERTC.getCameras经根据排列组合，帮你处理好每个厂商暴露出来给我们使用的设备序列。有的像华为它会把闪光灯也包括在内，并暴露多个前后置给你使用，后置我们取最后一个设备
          const cameraDevice = cameraList[cameraList.length - 1];
          if (
            cameraDevice &&
            cameraDevice.label &&
            cameraDevice.label.includes("back")
          ) {
            console.log(
              "摄像头列表中的最后一位确认是后置摄像头，且当前已经有了摄像头权限",
            );
          } else {
            console.warn(
              "当前环境不是H5，或者当前环境还没有摄像头权限, 打印cameraDevice: ",
              JSON.stringify(cameraDevice, null, ""),
            );
          }
          await localStream.open({
            type: "video",
            deviceId: cameraDevice.deviceId, //使用deviceId指定后置摄像头
          });
          console.log("打开摄像头 sucess");
          await rtcManagerRef.current?.playLocalStream(
            rtcManagerRef.current.localView as HTMLElement,
          );
        }
        setFacingMode(newFacingMode);
      }
    } catch (error) {
      const message = "切换摄像头失败: " + (error as Error).message;
      console.error(message);
      Toast.show({
        content: message,
        icon: "fail",
      });
    }
  };

  const swapVideos = () => {
    console.log("swapVideos() 点击大小屏幕切换");
    const result = rtcManagerRef.current?.swapVideos();
    if (result) {
      // 大小屏幕切换后，记得刷新下网络状态图标
      // 前置比较:只有值变化时才更新状态
      let tempLocalSignalLevel = localSignalLevel;
      setLocalSignalLevel((prev: SignalLevel) =>
        prev !== remoteSignalLevel ? remoteSignalLevel : prev,
      );
      setRemoteSignalLevel((prev: SignalLevel) =>
        prev !== tempLocalSignalLevel ? tempLocalSignalLevel : prev,
      );
    }
  };
  const leave = async () => {
    console.log("开始离开房间");
    setMeetingInfo({ nickName: "", channelName: "" });
    rtcManagerRef.current?.leaveChannel();
    rtcManagerRef.current?.destroy();
    rtcManagerRef.current = null;
    navigate("/");
  };

  // 转换NERTC SDK信号值为组件信号值
  const convertNetworkLevel = (sdkLevel: number): SignalLevel => {
    switch (sdkLevel) {
      case 0:
        return 0; // SDK 0 → 组件1（unkonwn）
      case 1:
      case 2:
        return 3; // SDK 1-2 → 组件3（很好）
      case 3:
        return 2; // SDK 3 → 组件2（一般）
      case 4:
      case 5:
      case 6:
        return 1; // SDK 4-6 → 组件1（极差）
    }
    return 0; // 默认unkonwn
  };

  // 防抖处理（1000ms间隔）
  const handleNetworkQuality = useCallback(
    throttle((evt: { local: number; remote: number }) => {
      //console.log("[RTCManager通知]: 网络质量: ", evt);
      let { local, remote } = evt;
      if (isLocalVideoLarge) {
        //此时进行了大小屏切换，右上角展示的是远端视频画面
        local = remote;
        remote = evt.local;
      }
      const newLocal = convertNetworkLevel(local);
      const newRemote = convertNetworkLevel(remote);

      // 前置比较:只有值变化时才更新状态
      setLocalSignalLevel((prev: SignalLevel) =>
        prev !== newLocal ? newLocal : prev,
      );
      setRemoteSignalLevel((prev: SignalLevel) =>
        prev !== newRemote ? newRemote : prev,
      );
    }, 1000),
    [],
  );

  return (
    <div className="rtc-body">
      {/*右上角小视频窗口，支持拖拽*/}
      <Pip
        ref={smallVideoRef}
        initialPosition={{ x: 10, y: 10 }}
        width="25vw"
        aspectRatio="3/4"
        content="等待视频流"
        onClick={swapVideos}
      >
        <div
          style={{
            position: "absolute",
            bottom: "10px",
            left: "10px",
            display: "flex",
            alignItems: "flex-start",
            gap: "10px",
            zIndex: 100, // 确保按钮在视频之上，否则点击事件会被视频遮挡
          }}
        >
          <NetworkSignal level={localSignalLevel} />
          {isMuted && isLocalVideoLarge && (
            <SoundMuteOutline
              color="red"
              fontSize={20}
              style={{ marginTop: 3 }}
              onClick={(e) => {
                e.stopPropagation(); // 阻止事件冒泡
                console.log("点击播放声音");
                rtcManagerRef.current?.playRemoteAudioStream(remoteUid.current);
                setIsMuted(false);
              }}
            />
          )}
        </div>
      </Pip>
      {/** 视频渲染大窗口UI */}
      <div className="rtc-main-window" ref={largeVideoRef}>
        <div
          style={{
            position: "absolute",
            bottom: "10px",
            left: "10px",
            display: "flex",
            alignItems: "flex-start",
            gap: "10px",
            zIndex: 100, // 确保按钮在视频之上，否则点击事件会被视频遮挡
          }}
        >
          <NetworkSignal level={remoteSignalLevel} />
          {isMuted && !isLocalVideoLarge && (
            <SoundMuteOutline
              color="red"
              fontSize={20}
              style={{ marginTop: 3 }}
              onClick={(e) => {
                e.stopPropagation(); // 阻止事件冒泡
                console.log("点击播放声音");
                rtcManagerRef.current?.playRemoteAudioStream(remoteUid.current);
                setIsMuted(false);
              }}
            />
          )}
        </div>
        <div className="rtc-main-window-statistics-box">
          <div>{`房间名称： ${meetingInfo.channelName}`}</div>
          <div>{`音频音量： ${meidaInfo.audioLevel}`}</div>
          <div>{`音频码率： ${meidaInfo.audioBitrate} Kbps`}</div>
          <div>{`视频码率： ${meidaInfo.videoBitrate} Kbps`}</div>
          <div>{`视频帧率： ${meidaInfo.videoFrameRate} fps`}</div>
          <div>
            {`视频分辨率： ${meidaInfo.videoFrameWidth} * ${meidaInfo.videoFrameHeight}`}
          </div>
        </div>
        {/* <div className='rtc-main-window-small-video-wrapper'>
          <div className='rtc-main-window-small-video' ref={smallVideoRef}>
          </div>
        </div> */}
        {!largeVideoRef.current?.querySelector("video") && "等待视频流"}
      </div>
      {/** 按钮UI */}
      <div className="rtc-tab-bar">
        <img
          src={muted ? unmuteIcon : muteIcon}
          style={{ width: "38px" }}
          onClick={() => openTheMicrophone()}
        />
        <img
          src={cameraOpened ? closeCameraIcon : openCameraIcon}
          style={{ width: "38px" }}
          onClick={() => openTheCamera()}
        />
        <img
          src={flipCameraIcon}
          style={{ width: "38px" }}
          onClick={() => flipCamera()}
        />
        <img
          src={overIcon}
          style={{ width: "38px", height: "34px" }}
          onClick={() => leave()}
        />
      </div>
    </div>
  );
};
export default RTC;
