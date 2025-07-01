import { createContext, useState, useContext, type ReactNode } from "react";
import type { Client } from "nertc-web-sdk/types/client";
import type { Stream } from "nertc-web-sdk/types/stream";

type MeetingInfo = {
  nickName?: string;
  channelName?: string;
  microphoneId?: string;
  cameraId?: string;
};

// 定义Context的类型
type AppContextType = {
  meetingInfo: MeetingInfo;
  setMeetingInfo: (info: MeetingInfo) => void;
};

// 创建Context并设置默认值（可选）
const AppContext = createContext<AppContextType | undefined>(undefined);

// 封装Provider组件
export function AppProvider({ children }: { children: ReactNode }) {
  const [meetingInfo, setMeetingInfo] = useState<MeetingInfo>({
    nickName: "",
    channelName: "",
    microphoneId: "",
    cameraId: "",
  });

  return (
    <AppContext.Provider value={{ meetingInfo, setMeetingInfo }}>
      {children}
    </AppContext.Provider>
  );
}

// 自定义Hook（方便在组件中使用）
export function useAppContext() {
  const context = useContext(AppContext);
  if (context === undefined) {
    throw new Error("useAppContext must be used within an AppProvider");
  }
  return context;
}

type RTCInfo = {
  client?: Client | undefined;
  localStream?: Stream | undefined;
};

type RTCContextType = {
  rtcInfo: RTCInfo;
  setRTCInfo: (info: RTCInfo) => void;
};

const RTCContext = createContext<RTCContextType | undefined>(undefined);

export function RTCProvider({ children }: { children: ReactNode }) {
  const [rtcInfo, setRTCInfo] = useState<RTCInfo>({
    client: undefined,
    localStream: undefined,
  });

  return (
    <RTCContext.Provider value={{ rtcInfo, setRTCInfo }}>
      {children}
    </RTCContext.Provider>
  );
}

// 自定义Hook（方便在组件中使用）
export function useRTCContext() {
  const context = useContext(RTCContext);
  if (context === undefined) {
    throw new Error("useRTCContext must be used within an useRTCContext");
  }
  return context;
}
