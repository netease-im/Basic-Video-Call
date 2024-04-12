
export enum ChatState {
  CHAT_IDLE = 0,
  CHAT_ING = 1,
  CHAT_ED = 2
}

export interface LoginInfo {
  cname: string;
  uid: string;
}

export class User {
  uid: bigint;
  width?: number = 150;
  height?: number = 150;
  local?: boolean = false;  // Is yourself?
}

export enum LiveStreamEvent {
  ADD,
  UPDATE,
  DEL
}

export enum ModelType {
  DEFAULT = -1,
  VIDEO_CALL = 0,
  LIVE_STREAM = 1,
  SNAPSHOT_WATERMARK = 2
}




