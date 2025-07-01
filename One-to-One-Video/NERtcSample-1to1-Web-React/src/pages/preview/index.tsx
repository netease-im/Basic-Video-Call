import { useEffect, useState, useRef } from "react";
import {
  AudioOutline,
  VideoOutline,
  SoundOutline,
  GlobalOutline,
} from "antd-mobile-icons";
import { Button, Space, Steps, Toast } from "antd-mobile";
import { Select } from "antd";
import { useNavigate } from "react-router-dom";
import "./index.css";
import RTCPreview from "@/features/rtcPreview";
import { appkey, secret } from "@/config";
import { useAppContext } from "@/store/index";
import type {
  NetworkInfo,
  DeviceCheckResult,
  NetworkStatus,
  NetworkStatusText,
} from "../../types/index";
import { getSystemInfo } from "@/utils";

const systemInfo = getSystemInfo();

const Preview: React.FC = () => {
  const navigate = useNavigate();
  const { meetingInfo, setMeetingInfo } = useAppContext();
  const { Step } = Steps;
  const [checking, setChecking] = useState(false);
  const [stepIndex, setStedIndex] = useState(-1);
  const [volume, setVolume] = useState(0);
  const [networkInfo, setNetworkInfo] = useState<NetworkInfo>({
    osType: systemInfo.os as string,
    userAgent: `${systemInfo.browser} ${systemInfo.browserVersion}`,
    supportRTC: false,
    uplinkNetworkQuality: "UNKNOWN",
    downlinkNetworkQuality: "UNKNOWN",
  });
  const [showReport, setShowReport] = useState(false);
  const [microphoneDeviceList, setMicrophoneDeviceList] = useState<
    { value: string; label: string }[]
  >([]);
  const [microphoneDefaultValue, setMicrophoneDefaultValue] = useState({
    label: "",
    deviceId: "",
  });
  const [cameraDeviceList, setCameraDeviceList] = useState<
    { value: string; label: string }[]
  >([]);
  const [cameraDefaultValue, setCameraDefaultValue] = useState({
    label: "",
    deviceId: "",
  });
  const [loading, setLoading] = useState(true);
  const videoRef = useRef<HTMLDivElement>(null);
  const rtcPreviewRef = useRef<RTCPreview | null>(null);
  const rtcPreviewResultRef = useRef<DeviceCheckResult>({
    microphone: {
      isOK: false,
    },
    speaker: {
      isOK: false,
    },
    camera: {
      isOK: false,
    },
    network: networkInfo,
  });

  const NETWORK_STATUS_MAP: Record<NetworkStatus, NetworkStatusText> = {
    0: "UNKNOWN",
    1: "EXCELLENT",
    2: "GOOD",
    3: "POOR",
    4: "BAD",
    5: "VERYBAD",
    6: "DOWN",
  };

  useEffect(() => {
    console.log("meetingInfo:", meetingInfo);
    if (!meetingInfo.channelName) {
      navigate("/");
    }
  }, []);
  useEffect(() => {
    if (!rtcPreviewRef.current || !rtcPreviewRef.current.stream) {
      return;
    }
    if (stepIndex === 0) {
      const timer = setInterval(() => {
        setVolume(rtcPreviewRef.current?.stream?.getAudioLevel() as number);
      }, 500);
      return () => clearInterval(timer);
    } else if (stepIndex === 2) {
      rtcPreviewRef.current.stream.play(videoRef.current as HTMLDivElement);
      rtcPreviewRef.current.stream.setLocalRenderMode({
        width: videoRef.current?.clientWidth as number,
        height: videoRef.current?.clientHeight as number,
        cut: false,
      });
    }
  }, [stepIndex, rtcPreviewRef.current]);

  const convertQuality = (quality: NetworkStatus): NetworkStatusText => {
    return NETWORK_STATUS_MAP[quality];
  };

  const repeat = () => {
    console.log("重新检测");
    setShowReport(false);
    startPreview();
  };

  const startPreview = () => {
    console.log("开始检测");
    setChecking(true);
    setStedIndex(0);
    rtcPreviewRef.current = new RTCPreview({
      appkey,
      secret: secret,
    });
    checkEnvironment();
  };

  const handleMicrophoneDeviceChange = (value: string, options: any) => {
    console.log(`麦克风选择selected ${value}`);
    console.log("options", options);
    setMicrophoneDefaultValue({
      label: options.label,
      deviceId: options.value,
    });
    setMeetingInfo({ ...meetingInfo, microphoneId: options.value });
    // 记录选择的麦克风设备，后续加入房间时使用
    rtcPreviewRef.current?.stream?.switchDevice("audio", value);
  };

  const handleCameraDeviceChange = (value: string, options: any) => {
    console.log(`摄像头选择selected ${value}`);
    setCameraDefaultValue({
      label: options.label,
      deviceId: options.value,
    });
    rtcPreviewRef.current?.stream?.switchDevice("video", value);
    // 记录选择的摄像头设备，后续加入房间时使用
    setMeetingInfo({ ...meetingInfo, cameraId: options.value });
  };

  const microphoneCallback = (isOK: boolean) => {
    console.log("反馈麦克风采集的音量 isOK:", isOK);
    console.log("反馈麦克风采集的音量 volume:", volume);
    // if (!volume) {
    //   Toast.show({
    //     content: '请检查选择的麦克风设备是否正常',
    //     icon: 'success'
    //   })
    //   return
    // }
    rtcPreviewResultRef.current.microphone.isOK = isOK;
    setStedIndex(1);
  };

  const speakerCallback = (isOK: boolean) => {
    console.log("反馈扬声器 isOK:", isOK);
    rtcPreviewResultRef.current.speaker.isOK = isOK;
    setStedIndex(2);
  };

  const cameraCallback = (isOK: boolean) => {
    console.log("反馈摄像头 isOK:", isOK);
    rtcPreviewResultRef.current.camera.isOK = isOK;
    setStedIndex(3);
    checkNetwork();
  };

  const checkNetwork = async () => {
    try {
      setLoading(true);
      const result = (await rtcPreviewRef.current?.checkNetwork()) as {
        uplinkNetworkQuality: NetworkStatus;
        downlinkNetworkQuality: NetworkStatus;
      };
      setLoading(false);
      console.log("检测网络结果: ", result);
      const transformedResult = {
        uplinkNetworkQuality: convertQuality(result.uplinkNetworkQuality),
        downlinkNetworkQuality: convertQuality(result.downlinkNetworkQuality),
      };
      setNetworkInfo((prevState) => ({ ...prevState, ...transformedResult }));
      //rtcPreviewResultRef.current.network = {...networkInfo, ...transformedResult}
      rtcPreviewRef.current?.destroy();
      rtcPreviewRef.current = null;
    } catch (error) {
      setLoading(false);
      const message = "检测网络错误: " + (error as Error).message;
      console.error(message);
      Toast.show({
        content: message,
        icon: "fail",
      });
    }
  };

  const enterMeetingRoom = () => {
    console.log("进入会议");
    navigate("/rtc");
  };

  const checkEnvironment = async () => {
    try {
      if (!rtcPreviewRef.current) {
        return;
      }
      rtcPreviewRef.current.on(
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
      rtcPreviewRef.current.on(
        "error",
        (result: { reason: string; message: string }) => {
          console.error(
            "检测流程内部异常: ",
            JSON.stringify(result, null, " "),
          );
          Toast.show({
            content: result.reason + result.message,
            icon: "fail",
          });
        },
      );
      //初始化
      await rtcPreviewRef.current.init();
      console.log("初始化完成");
      setLoading(false);
      // 检查是否支持NERTC
      const supportRTC = await rtcPreviewRef.current.supportRTC();
      setNetworkInfo((prevState) => ({ ...prevState, supportRTC }));
      //获取麦克风设备列表
      const microphones = await rtcPreviewRef.current.getMicrophones();
      setMicrophoneDeviceList(microphones);
      setMicrophoneDefaultValue({
        label: microphones[0].label,
        deviceId: microphones[0].value,
      });
      //获取摄像头设备列表
      const cameras = await rtcPreviewRef.current.getCameras();
      setCameraDeviceList(cameras);
      setCameraDefaultValue({
        label: microphones[0].label,
        deviceId: microphones[0].value,
      });
    } catch (error: unknown) {
      console.error("Error checking environment:", error);
      Toast.show({
        content: "设备检测错误: " + (error as Error).message,
        icon: "fail",
        afterClose: () => {
          console.log("after");
        },
      });
      setLoading(false);
    }
  };

  const skip = () => {
    if (checking) {
      rtcPreviewRef.current?.destroy();
      rtcPreviewRef.current = null;
      setChecking(false);
    }
    enterMeetingRoom();
  };

  // 渲染30个柱状图
  const renderVolumeBars = () => {
    const totalBars = 30;
    // 计算需要显示为绿色的柱子数量
    const activeBars = Math.round((volume / 100) * totalBars);
    return (
      <div
        style={{
          display: "flex",
          alignItems: "flex-end",
          justifyContent: "center",
          gap: "2px",
        }}
      >
        {Array.from({ length: totalBars }).map((_, index) => {
          const isActive = index < activeBars;
          return (
            <div
              key={index}
              style={{
                width: "6px",
                height: "30px",
                backgroundColor: isActive ? "#4CAF50" : "transparent",
                border: "1px solid #E0E0E0",
                borderRadius: "4px",
                transition: "background-color 0.1s ease",
              }}
            />
          );
        })}
      </div>
    );
  };

  return (
    <div className="preview-body">
      <div className="preview-body-header" onClick={skip}>
        跳过检测
      </div>
      {checking ? (
        <div className="checked-body">
          {!showReport ? (
            <div className="checked-body-steps">
              <Steps
                current={stepIndex}
                style={{
                  "--icon-size": "24px",
                  "--indicator-margin-right": "5px",
                }}
              >
                <Step title="麦克风" icon={<AudioOutline />} />
                <Step title="扬声器" icon={<SoundOutline />} />
                <Step title="摄像头" icon={<VideoOutline />} />
                <Step title="网络连接" icon={<GlobalOutline />} />
              </Steps>
            </div>
          ) : null}

          {/* 麦克风检测UI */}
          {stepIndex === 0 && !showReport ? (
            <div className="checked-body-steps-item">
              <div className="checked-body-steps-microphone-devices">
                <div className="checked-body-steps-microphone-devices-title">
                  选择麦克风
                </div>
                <Select
                  value={microphoneDefaultValue.label}
                  style={{ width: 200 }}
                  onChange={handleMicrophoneDeviceChange}
                  options={microphoneDeviceList}
                />
              </div>

              <div className="checked-body-steps-microphone-volume">
                <div className="checked-body-steps-microphone-volume-title">
                  对着麦克风说话
                </div>
                {/* <ProgressBar
                  percent={volume}
                  style={{
                    '--track-width': '2px',
                    '--fill-color': '#00B578', // 绿色填充
                    '--track-color': 'rgba(0, 181, 120, 0.1)', // 透明背景
                    width: 200,
                    height: 10,
                  }}
                /> */}
                {renderVolumeBars()}
              </div>

              <div className="checked-body-steps-microphone-callback">
                <div className="checked-body-steps-microphone-callback-title">
                  是否可以看到音量图标跳动？
                </div>
                <div className="checked-body-steps-microphone-callback-btn">
                  <Button
                    block
                    color="primary"
                    size="small"
                    loading={loading}
                    loadingText="检测中..."
                    style={{
                      width: 80,
                      borderRadius: 5,
                      background: "white",
                      color: "#1677ff",
                      overflow: "hidden",
                      textOverflow: "ellipsis",
                      whiteSpace: "nowrap",
                    }}
                    onClick={() => {
                      microphoneCallback(false);
                    }}
                  >
                    看不到
                  </Button>
                  <Button
                    block
                    color="primary"
                    size="small"
                    loading={loading}
                    loadingText="检测中..."
                    style={{
                      width: 80,
                      borderRadius: 5,
                      overflow: "hidden",
                      textOverflow: "ellipsis",
                      whiteSpace: "nowrap",
                    }}
                    onClick={() => {
                      microphoneCallback(true);
                    }}
                  >
                    看得到
                  </Button>
                </div>
              </div>
            </div>
          ) : null}

          {/* 扬声器检测UI */}
          {stepIndex === 1 ? (
            <div className="checked-body-steps-item">
              <div className="checked-body-steps-speaker">
                <div className="checked-body-steps-speaker-title">
                  请点击播放下面的音频
                </div>
                <audio
                  src="https://yx-web-nosdn.netease.im/common/95b8fba2b56c03532a24548d692a5091/BoyAndGirl.mp3"
                  controls
                ></audio>
              </div>

              <div className="checked-body-steps-microphone-callback">
                <div className="checked-body-steps-microphone-callback-title">
                  是否可以听到声音？
                </div>
                <div className="checked-body-steps-microphone-callback-btn">
                  <Button
                    block
                    color="primary"
                    size="small"
                    style={{
                      width: 80,
                      borderRadius: 5,
                      background: "white",
                      color: "#1677ff",
                    }}
                    onClick={() => {
                      speakerCallback(false);
                    }}
                  >
                    听不到
                  </Button>
                  <Button
                    block
                    color="primary"
                    size="small"
                    style={{ width: 80, borderRadius: 5 }}
                    onClick={() => {
                      speakerCallback(true);
                    }}
                  >
                    听得到
                  </Button>
                </div>
              </div>
            </div>
          ) : null}

          {/* 摄像头检测UI */}
          {stepIndex === 2 ? (
            <div className="checked-body-steps-item" style={{ marginTop: 50 }}>
              <div className="checked-body-steps-microphone-devices">
                <div className="checked-body-steps-microphone-devices-title">
                  选择摄像头
                </div>
                <Select
                  value={cameraDefaultValue.label}
                  style={{ width: 200 }}
                  onChange={handleCameraDeviceChange}
                  options={cameraDeviceList}
                />
              </div>
              <div style={{ maxWidth: "100%", margin: "0 auto" }}>
                <div
                  ref={videoRef}
                  style={{
                    width: "240px",
                    height: "180px",
                    background: "#000",
                  }}
                ></div>
              </div>
              <div className="checked-body-steps-camera-callback-btn">
                <div className="checked-body-steps-microphone-callback-title">
                  是否可以看到自己？
                </div>
                <div className="checked-body-steps-microphone-callback-btn">
                  <Button
                    block
                    color="primary"
                    size="small"
                    style={{
                      width: 80,
                      borderRadius: 5,
                      background: "white",
                      color: "#1677ff",
                    }}
                    onClick={() => {
                      cameraCallback(false);
                    }}
                  >
                    看不到
                  </Button>
                  <Button
                    block
                    color="primary"
                    size="small"
                    style={{ width: 80, borderRadius: 5 }}
                    onClick={() => {
                      cameraCallback(true);
                    }}
                  >
                    看得到
                  </Button>
                </div>
              </div>
            </div>
          ) : null}

          {/* 网络检测UI */}
          {stepIndex === 3 && !showReport ? (
            <div className="checked-body-steps-item">
              <div className="checked-body-steps-item-network">
                <div className="checked-body-steps-network">
                  <div className="checked-body-steps-network-title">
                    操作系统
                  </div>
                  <div className="checked-body-steps-network-description">
                    {networkInfo.osType}
                  </div>
                </div>
                <div className="checked-body-steps-network">
                  <div className="checked-body-steps-network-title">浏览器</div>
                  <div className="checked-body-steps-network-description">
                    {networkInfo.userAgent}
                  </div>
                </div>
                <div className="checked-body-steps-network">
                  <div className="checked-body-steps-network-title">
                    支持NERTC
                  </div>
                  <div className="checked-body-steps-network-description">
                    {networkInfo.supportRTC ? "支持" : "不支持"}
                  </div>
                </div>
                <div className="checked-body-steps-network">
                  <div className="checked-body-steps-network-title">
                    上行网络质量
                  </div>
                  <div className="checked-body-steps-network-description">
                    {networkInfo.uplinkNetworkQuality}
                  </div>
                </div>
                <div className="checked-body-steps-network">
                  <div className="checked-body-steps-network-title">
                    下行网络质量
                  </div>
                  <div className="checked-body-steps-network-description">
                    {networkInfo.downlinkNetworkQuality}
                  </div>
                </div>
              </div>

              <div className="checked-body-steps-microphone-callback">
                <div className="checked-body-steps-microphone-callback-btn">
                  <Button
                    block
                    color="primary"
                    size="small"
                    loading={loading}
                    loadingText="检测中..."
                    style={{
                      width: 120,
                      borderRadius: 5,
                      overflow: "hidden",
                      textOverflow: "ellipsis",
                      whiteSpace: "nowrap",
                    }}
                    onClick={enterMeetingRoom}
                  >
                    进入会议房间
                  </Button>
                  <Button
                    block
                    color="primary"
                    size="small"
                    loading={loading}
                    loadingText="检测中..."
                    style={{
                      width: 120,
                      borderRadius: 5,
                      overflow: "hidden",
                      textOverflow: "ellipsis",
                      whiteSpace: "nowrap",
                    }}
                    onClick={() => {
                      setShowReport(true);
                    }}
                  >
                    查看检查报告
                  </Button>
                </div>
              </div>
            </div>
          ) : null}

          {/* 检查报告UI */}
          {showReport ? (
            <div className="checked-body-steps-item">
              <div style={{ fontSize: 24 }}>检查报告</div>

              <div className="checked-body-steps-item-report">
                <div className="checked-body-steps-network">
                  <AudioOutline
                    color="#76c6b8"
                    style={{ width: 24, height: 24 }}
                  />
                  <div className="checked-body-steps-network-title-row">
                    <div className="checked-body-steps-network-title">
                      {microphoneDefaultValue.label}
                    </div>
                    <div className="checked-body-steps-network-description">
                      {rtcPreviewResultRef.current.microphone.isOK
                        ? "正常"
                        : "异常"}
                    </div>
                  </div>
                </div>
                <div className="checked-body-steps-network">
                  <SoundOutline
                    color="#76c6b8"
                    style={{ width: 24, height: 24 }}
                  />
                  <div className="checked-body-steps-network-title-row">
                    <div className="checked-body-steps-network-title">
                      系统扬声器
                    </div>
                    <div className="checked-body-steps-network-description">
                      {rtcPreviewResultRef.current.speaker.isOK
                        ? "正常"
                        : "异常"}
                    </div>
                  </div>
                </div>
                <div className="checked-body-steps-network">
                  <VideoOutline
                    color="#76c6b8"
                    style={{ width: 24, height: 24 }}
                  />
                  <div className="checked-body-steps-network-title-row">
                    <div className="checked-body-steps-network-title">
                      {cameraDefaultValue.label}
                    </div>
                    <div className="checked-body-steps-network-description">
                      {rtcPreviewResultRef.current.camera.isOK
                        ? "正常"
                        : "异常"}
                    </div>
                  </div>
                </div>
                <div className="checked-body-steps-network">
                  <GlobalOutline
                    color="#76c6b8"
                    style={{ width: 24, height: 24 }}
                  />
                  <div className="checked-body-steps-network-title-row">
                    <div className="checked-body-steps-network-title">
                      上行网络质量
                    </div>
                    <div className="checked-body-steps-network-description">
                      {networkInfo.uplinkNetworkQuality}
                    </div>
                  </div>
                </div>
                <div className="checked-body-steps-network">
                  <GlobalOutline
                    color="#76c6b8"
                    style={{ width: 24, height: 24 }}
                  />
                  <div className="checked-body-steps-network-title-row">
                    <div className="checked-body-steps-network-title">
                      下行网络质量
                    </div>
                    <div className="checked-body-steps-network-description">
                      {networkInfo.downlinkNetworkQuality}
                    </div>
                  </div>
                </div>
              </div>
              <div className="checked-body-steps-report-btn">
                <Button
                  block
                  color="primary"
                  size="small"
                  style={{ width: 120, borderRadius: 5 }}
                  onClick={repeat}
                >
                  重新检测
                </Button>
                <Button
                  block
                  color="primary"
                  size="small"
                  style={{ width: 120, borderRadius: 5 }}
                  onClick={enterMeetingRoom}
                >
                  完成检测
                </Button>
              </div>
            </div>
          ) : null}
        </div>
      ) : (
        <div className="checked-body">
          <div className="checked-body-title">环境监测</div>
          <div className="checked-body-text">
            检查前请确保网络通畅，摄像头和麦克风正常工作
          </div>
          <Space
            wrap
            style={{ marginTop: 20, fontSize: 36, "--gap-horizontal": "32px" }}
          >
            <AudioOutline color="#76c6b8" />
            <SoundOutline color="#76c6b8" />
            <VideoOutline color="#76c6b8" />
            <GlobalOutline color="#76c6b8" />
          </Space>
          <Button
            block
            color="primary"
            size="middle"
            style={{ width: 100, height: 44, marginTop: 20, borderRadius: 8 }}
            onClick={startPreview}
          >
            开始检测
          </Button>
        </div>
      )}
    </div>
  );
};

export default Preview;
