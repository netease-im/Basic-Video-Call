import worker, { ThreadWorkerGlobalScope, MessageEvents, ErrorEvent } from '@ohos.worker';
import { NERtcCallbackEx, NERtcConstants, NERtcSDK } from 'sdk';
import { Init, Join, NERtcData, Response, SetUp, SetUpResponse, API, CallbackResponse, EnableVideo } from './ChatModel'

const TAG: string = 'ChatWorker'
const workerPort: ThreadWorkerGlobalScope = worker.workerPort;

function __call_ui__(response: Response): void {
  workerPort.postMessage(response)
}

workerPort.onmessage = (e: MessageEvents) => {
  let data = e.data as NERtcData
  switch(data.api) {
    case API.INIT:
      {
        let init = data as Init
        console.info(TAG, `key:${init.key}, level:${init.level}`)
        let option: NERtcConstants.NERtcOption = {logLevel: init.level}
        NERtcSDK.getInstance().init(init.key, new ChatCallback(), option)
      }
      break;
    case API.JOIN:
      {
        let join = data as Join
        let ret: number = NERtcSDK.getInstance().joinChannel(join.token, join.cname, BigInt(join.uid))
        console.info(TAG, `token:${join.token}, cname:${join.cname}, uid:${join.uid}, ret:${ret}`)
        __call_ui__({ api: API.JOIN, ret: ret })
      }
      break;
    case API.SETUP:
      {
        let setUp = data as SetUp
        let canvas: NERtcConstants.NERtcVideoCanvas = { xComponentId: setUp.xComponentId}
        let ret: number;
        if(setUp.isMe) {
          ret = NERtcSDK.getInstance().setupLocalVideoCanvas(canvas)
        } else {
          ret = NERtcSDK.getInstance().setupRemoteVideoCanvas(canvas, BigInt(setUp.uid))
        }
        let response: SetUpResponse = { api: API.SETUP, uid: setUp.uid, ret: ret }
        __call_ui__(response)
      }
      break;
    case API.ENABLE_VIDEO:
      {
        let enableVideo = data as EnableVideo
        let ret: number = NERtcSDK.getInstance().enableLocalVideo(enableVideo.enable)
        console.info(TAG, `Enable local video ret:${ret}`)
      }
      break;
    case API.LEAVE:
      {
        let ret: number = NERtcSDK.getInstance().leaveChannel()
        __call_ui__({ api: API.LEAVE, ret: ret })
      }
      break;
    case API.RELEASE:
      {
        NERtcSDK.getInstance().release()
        console.info(TAG, 'CALL release done.')
      }
      break;
    default: break;
  }
}

workerPort.onmessageerror = (e: MessageEvents) => {
  console.info(TAG, `onmessageerror: ${e}`);
}

workerPort.onerror = (e: ErrorEvent) => {
  console.info(TAG, `onerror: ${e}`);
}


export class ChatCallback extends NERtcCallbackEx {

  onJoinChannel(result: number, channelId: bigint, elapsed: bigint, uid: bigint): void {
    let callback: CallbackResponse = {api: API.ON_JOIN, ret: result, object: {result: result, channelId: BigInt(channelId).toString(), elapsed: BigInt(elapsed).toString(), uid: BigInt(uid).toString()}}
    __call_ui__(callback)
  }

  onLeaveChannel(result: number): void {
    __call_ui__({ api: API.ON_LEAVE, ret: result })
  }

  onUserJoined(uid: bigint, extraInfo?: NERtcConstants.NERtcUserJoinExtraInfo): void {
    let callback: CallbackResponse = { api: API.ON_USER_JOIN, ret: 0, object: {uid: BigInt(uid).toString(), extraInfo: extraInfo} }
    __call_ui__(callback)
  }

  onUserLeave(uid: bigint, reason: number, extraInfo?: NERtcConstants.NERtcUserLeaveExtraInfo): void {
    let callback: CallbackResponse = { api: API.ON_USER_LEAVE, ret: 0, object: {uid: BigInt(uid).toString(), reason: reason, extraInfo: extraInfo}}
    __call_ui__(callback)
  }

  onUserAudioStart(uid: bigint): void {
    console.info(TAG, `User:${uid} audio start.`)
  }

  onUserAudioStop(uid: bigint): void {
    console.info(TAG, `User:${uid} audio stop.`)
  }

  onUserVideoStart(uid: bigint, maxProfile: number): void {
    console.info(TAG, `User:${uid} video start.`)
  }

  onUserVideoStop(uid: bigint): void {
    console.info(TAG, `User:${uid} video stop.`)
  }

  onDisconnect(reason: number): void {
    console.info(TAG, `Disconnect reason:${reason}`)
  }

  onClientRoleChange(oldRole: number, newRole: number): void {
    console.info(TAG, `Role change to ${newRole}`)
  }

  onReceiveSEIMessage(userId: bigint, data: Uint8Array, dataSize: number): void{
    console.info(TAG, `Receive SEI message: ${userId}, dataSize:${dataSize}`)
  }
}