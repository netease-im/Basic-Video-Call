import { NERtc } from 'sdk/src/main/ets/default/sdk/NERtc';

export enum ChatState {
  CHAT_IDLE = 0,
  CHAT_ING = 1,
  CHAT_ED = 2
}

export interface LoginInfo {
  cname: string;
  uid: string;
}

export interface ChatResult {
  result: ChatState;
  detail?: string;
}

export enum API {
  INIT = 'init',
  JOIN = 'join',
  SETUP = 'setup',
  ENABLE_VIDEO = 'enableVideo',
  LEAVE = 'leave',
  RELEASE = 'release',

  ON_JOIN = 'onJoin',
  ON_LEAVE = 'onLeave',
  ON_USER_JOIN = 'onUserJoin',
  ON_USER_LEAVE = 'onUserLeave'
}

export interface NERtcData {
  api: API
}

export interface Init extends  NERtcData {
  key: string
  level: number
}

export interface Join extends NERtcData {
  token: string
  cname: string
  uid: string
}

export interface SetUp extends NERtcData {
  uid: string
  xComponentId: string
  isMe: boolean
}

export interface EnableVideo extends NERtcData {
  enable: boolean
}


export interface Response extends NERtcData {
  ret: number
}

export interface SetUpResponse extends Response {
  uid: string
}

export interface CallbackResponse extends Response {
  object: any
}

