//因为Typescript对不同平台的timer返回值类型处理不同：
export type Timer =
  | ReturnType<typeof setTimeout>
  | ReturnType<typeof setInterval>;
export interface LoginResponse {
  code: number;
  requestId: string;
  message: string;
  data: unknown;
  success: boolean;
}

export interface consultationResponse {}

export type NetworkStatus =
  | 0 // UNKNOWN
  | 1 // EXCELLENT
  | 2 // GOOD
  | 3 // POOR
  | 4 // BAD
  | 5 // VERYBAD
  | 6; // DOWN

export type NetworkStatusText =
  | "UNKNOWN"
  | "EXCELLENT"
  | "GOOD"
  | "POOR"
  | "BAD"
  | "VERYBAD"
  | "DOWN";

export interface NetworkInfo {
  osType: string;
  userAgent: string;
  supportRTC: boolean;
  uplinkNetworkQuality: NetworkStatusText;
  downlinkNetworkQuality: NetworkStatusText;
}

export interface DeviceCheckResult {
  microphone: { isOK: boolean };
  speaker: { isOK: boolean };
  camera: { isOK: boolean };
  network: NetworkInfo; // 或更具体的网络类型
}

export interface MediaInfo {
  audioLevel: number;
  audioBitrate: number;
  videoBitrate: number;
  videoFrameRate: number;
  videoFrameWidth: number;
  videoFrameHeight: number;
  uplinkNetworkQuality: NetworkStatus;
  downlinkNetworkQuality: NetworkStatus;
}
