import { useAppContext } from "@/store/index";
import { useEffect, useState } from "react";
import { Image, Input, Button, Toast, WaterMark } from "antd-mobile";
import { useNavigate } from "react-router-dom";
import imgSrc from "@/assets/yunxinLogo1.png";
import { getSystemInfo } from "@/utils";
import WechatQrCode from "@/components/wechatQrCode";

import "./index.css";
const Home: React.FC = () => {
  const { meetingInfo, setMeetingInfo } = useAppContext();
  //全局变量保存房间信息
  const [nickName, setNickName] = useState("");
  const [channelName, setChannelName] = useState("");
  const [useWxChat, setUseWxChat] = useState(false);
  const [disabled, setDisabled] = useState(false);
  const navigate = useNavigate();

  useEffect(() => {
    const { os, osVersion, isMobile, isWeChat } = getSystemInfo();
    console.log("getSystemInfo() :", os, osVersion, isMobile, isWeChat);
    if (!isMobile) {
      console.warn("非移动端");
      setDisabled(true);
      Toast.show({
        content: "请使用移动端浏览器打开",
        icon: "fail",
        duration: 5000,
      });
      return;
    }
    // 安卓、鸿蒙系统推荐使用微信浏览器打开
    // ios系统推荐使用safari浏览器打开
    // ps: 使用URL Scheme或者App Links唤起微信都有各自的缺陷，所以这里推荐使用引导的方式
    if (!isWeChat && (os === "Android" || os === "Harmony")) {
      console.log("安卓系统推荐使用微信浏览器打开");
      setUseWxChat(true);
    }
    if (os === "iOS" && parseInt(osVersion as string) < 13) {
      setDisabled(true);
      Toast.show({
        content: "IOS推荐系统版本13+",
        icon: "fail",
        duration: 5000,
      });
    }
  }, []);
  useEffect(() => {
    console.log("meetingInfo:", meetingInfo);
    if (meetingInfo.channelName) {
      console.log("进入preview页面");
      navigate("/preview");
    }
  }, [meetingInfo]);

  const joinChannel = () => {
    console.log("joinChannel()");
    setMeetingInfo({ nickName, channelName });
  };

  return (
    <div className="home-body">
      <WaterMark content={"网易云信"} fullPage={true} />
      {useWxChat ? (
        //引导微信浏览器打开当前页面
        <WechatQrCode />
      ) : (
        <div className={"content"}>
          <Image src={imgSrc} width={300} height={55} fit="contain" />
          <Input
            placeholder="请输入房间名称"
            value={channelName}
            clearable={true}
            onChange={(val) => {
              setChannelName(val);
            }}
            style={{
              "--color": "#0a43e5",
              "--placeholder-color": "#000000ad",
              "--font-size": "18px",
              height: 44,
              width: 300,
              borderBottom: "1px solid #dcdfe5",
              marginTop: 20,
              fontSize: 18,
            }}
          />
          <Input
            placeholder="请输入昵称"
            value={nickName}
            onChange={(val) => {
              setNickName(val);
            }}
            style={{
              "--color": "#0a43e5",
              "--placeholder-color": "#000000ad",
              "--font-size": "18px",
              height: 44,
              width: 300,
              borderBottom: "1px solid #dcdfe5",
              fontSize: 18,
            }}
          />
          <Button
            block
            color="primary"
            size="large"
            disabled={!channelName || disabled}
            style={{ width: 300, marginTop: 20 }}
            onClick={joinChannel}
          >
            加入房间
          </Button>
        </div>
      )}
    </div>
  );
};

export default Home;
