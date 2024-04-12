import { NERtcCallbackEx, NERtcChannelCallback, NERtcConstants, NERtcSDK , NERtcStatsObserver} from 'sdk/Index';
import Config from './Config';
import * as model from './Model';
import Delegate from './Delegate';

let TAG: string = 'Presenter'
let delegates: Array<Delegate> = []
export let remoteUsers: Array<bigint> = []

export default class ChatPresenter {

  private static instance: ChatPresenter = new ChatPresenter()
  private login?: model.LoginInfo

  private constructor() {
    delegates = []
  }

  static getInstance(): ChatPresenter {
    return ChatPresenter.instance;
  }

  setDelegate(delegate: Delegate) {

    if(delegates.indexOf(delegate) !== -1) {
      console.info(TAG, 'delegate is exits')
    } else {
      delegates?.push(delegate)
      console.info(TAG, 'setDelegate size: ' + delegates.length)
    }
  }

  removeDelegate(delegate: Delegate) {

    let index = delegates.indexOf(delegate)
    if(index !== -1) {
      delegates.splice(index, 1)
    } else {
      console.info(TAG, 'delegate not found.')
    }
  }

  init(context: Context) {
    NERtcSDK.getInstance().setParameters({test_env: true})
    let option: NERtcConstants.NERtcOption = { logLevel: NERtcConstants.LogLevel.INFO }
    NERtcSDK.getInstance().init(context, Config.APP_KEY, new ChatCallback(), option)
  }

  join(login: model.LoginInfo): number {

    this.login = login
    let ret = NERtcConstants.ErrorCode.NO_ERROR
    if(login) {
      ret = NERtcSDK.getInstance().joinChannel('', login?.cname, BigInt(login?.uid))
      console.info(TAG, 'Join channel ret: ' + ret)
    } else {
      console.error(TAG, 'LoginInfo is empty.')
      ret = NERtcConstants.ErrorCode.ENGINE_ERROR_FATAL
    }
    return ret 
  }
  setExternalAudioSource(enable: boolean, sampleRate: number, channel: number){
    NERtcSDK.getInstance().setExternalAudioSource(enable,sampleRate, channel)
  }
  setExternalSubAudioSource(enable: boolean, sampleRate: number, channel: number){
    NERtcSDK.getInstance().setExternalSubStreamAudioSource(enable,sampleRate, channel)
  }
  pushExternalSubAudioFrame(uint8Array: Uint8Array, samplesPerChannel: number, sampleRate: number, channels: number, lastSyncTimestamp: bigint) {
    let frame = new NERtcConstants.NERtcAudioExternalFrame()
    frame.data = uint8Array
    frame.sampleRate = sampleRate
    frame.samplesPerChannel = samplesPerChannel
    frame.channels = channels
    frame.syncTimestamp = lastSyncTimestamp
    NERtcSDK.getInstance().pushExternalSubStreamAudioFrame(frame)
  }
  pushExternalAudioFrame(uint8Array: Uint8Array, samplesPerChannel: number, sampleRate: number, channels: number, lastSyncTimestamp: bigint) {
    let frame = new NERtcConstants.NERtcAudioExternalFrame()
    frame.data = uint8Array
    frame.sampleRate = sampleRate
    frame.samplesPerChannel = samplesPerChannel
    frame.channels = channels
    frame.syncTimestamp = lastSyncTimestamp
    NERtcSDK.getInstance().pushExternalAudioFrame(frame)
  }
  attach(user: model.User) {
    let canvas: NERtcConstants.NERtcVideoCanvas = { canvasId: String(user.uid) }
    let local = String(user.uid) === this.login?.uid
    if(local) {
      let ret = NERtcSDK.getInstance().setupLocalVideoCanvas(canvas)
      console.info(TAG, 'setLocalVideoCanvas ret:' + ret)
    } else {
      let ret = NERtcSDK.getInstance().setupRemoteVideoCanvas(canvas, user.uid)
      console.info(TAG, 'setupRemoteVideoCanvas ret:' + ret)
      NERtcSDK.getInstance().subscribeRemoteVideo(user.uid, true, NERtcConstants.NERtcVideoStreamType.kNERtcVideoStreamTypeMain, NERtcConstants.NERtcRemoteVideoSubscribeType.kNERtcRemoteVideoSubscribeTypeHigh)
    }
  }

  attachSub(user: model.User) {
    let canvas: NERtcConstants.NERtcVideoCanvas = { canvasId: String(user.uid + 'sub') }
    let local = String(user.uid) === this.login?.uid
    if(local) {
      let ret = NERtcSDK.getInstance().setupLocalSubStreamVideoCanvas(canvas)
      console.info(TAG, 'setupLocalSubStreamVideoCanvas ret:' + ret)
    } else {
      let ret = NERtcSDK.getInstance().setupRemoteSubStreamVideoCanvas(canvas, user.uid)
      console.info(TAG, 'setupRemoteSubStreamVideoCanvas ret:' + ret)
      NERtcSDK.getInstance().subscribeRemoteSubStreamVideo(user.uid, true)
    }
  }

  switchCamera() {
    NERtcSDK.getInstance().switchCamera()
  }
  enableVideo(enable: boolean) {
    let ret = NERtcSDK.getInstance().enableLocalVideo(enable, NERtcConstants.NERtcVideoStreamType.kNERtcVideoStreamTypeMain)
    console.info(TAG, 'enableLocalVideo result:' + ret)
  }
  enableSubVideo(enable: boolean) {
    let ret = NERtcSDK.getInstance().enableLocalVideo(enable, NERtcConstants.NERtcVideoStreamType.kNERtcVideoStreamTypeSub)
    console.info(TAG, 'enableLocalSubVideo result:' + ret)
  }
  setExternalVideoSouce(enable:boolean, streamType:NERtcConstants.NERtcVideoStreamType){
    let ret = NERtcSDK.getInstance().setExternalVideoSource(enable,streamType)
    console.info(TAG, 'setExternalVideoSouce result:' + ret)
  }

  pushExternalVideoFrame(frame: NERtcConstants.NERtcVideoFrame, streamType: NERtcConstants.NERtcVideoStreamType){
    let ret = NERtcSDK.getInstance().pushExternalVideoFrame(frame, streamType)
  }

  setStatsObserver(statsObserver: NERtcStatsObserver) {
    NERtcSDK.getInstance().setStatsObserver(statsObserver)
  }
  enableAudio(enable: boolean) {
    let ret = NERtcSDK.getInstance().enableLocalAudio(enable)
    console.info(TAG, 'enableLocalAudio result:' + ret)
  }
  startLastmileProbeTest(config: NERtcConstants.LastmileProbeConfig) {
    let ret: number = NERtcSDK.getInstance().startLastmileProbeTest(config)
    console.info(TAG, 'startLastmileProbeTest result:' + ret)
  }
  enableSubAudio(enable: boolean) {
    let ret = NERtcSDK.getInstance().enableLocalSubStreamAudio(enable)
    console.info(TAG, 'enableLocalAudio result:' + ret)
  }
  setAudioProfile(profile: number, scenario: number) {
    NERtcSDK.getInstance().setAudioProfile(profile, scenario);
  }
  setSpeakPhoneOn(enable: boolean) {
    let ret = NERtcSDK.getInstance().setSpeakerphoneOn(enable)
    console.info(TAG, 'setSpeakPhoneOn result:' + ret)
  }
  leave() {
    let ret: number = NERtcSDK.getInstance().leaveChannel()
    console.info(TAG, `LeaveChannel ret:${ret}`)
  }
  setVoiceBeautifierPreset(preset: number) {
    let ret: number = NERtcSDK.getInstance().setVoiceBeautifierPreset(preset)
    console.info(TAG, `setVoiceBeautifierPreset ret:${ret}`)
  }
  setAudioEffectPreset(preset: number) {
    let ret: number = NERtcSDK.getInstance().setAudioEffectPreset(preset)
    console.info(TAG, `setAudioEffectPreset ret:${ret}`)
  }
  setCameraCaptureConfig(config: NERtcConstants.NERtcCameraCaptureConfiguration) {
    let ret: number = NERtcSDK.getInstance().setCameraCaptureConfig(config, NERtcConstants.NERtcVideoStreamType.kNERtcVideoStreamTypeMain);
    console.info(TAG, `setCameraCaptureConfig ret:${ret}`);
  }
  setLocalVideoConfig(config: NERtcConstants.NERtcVideoEncodeConfiguration) {
    let ret: number = NERtcSDK.getInstance().setLocalVideoConfig(config, NERtcConstants.NERtcVideoStreamType.kNERtcVideoStreamTypeMain);
    console.info(TAG, `setLocalVideoEncodeConfig ret:${ret}`);
  }
  addLiveStreamTask(info: NERtcConstants.NERtcLiveStreamTaskInfo) {
    let ret: number = NERtcSDK.getInstance().addLiveStreamTask(info)
    console.info(TAG, 'addLiveStreamTask ret: ' + ret)
  }
  removeLiveStreamTask(taskId: string): void {
    let ret: number = NERtcSDK.getInstance().removeLiveStreamTask(taskId)
    console.info(TAG, 'removeLiveStreamTask ret: ' + ret)
  }
  startAudioMixing(option: NERtcConstants.NERtcCreateAudioMixingOption) : number {
    let ret: number = NERtcSDK.getInstance().startAudioMixing(option)
    console.info(TAG, `startAudioMixing ret:${ret}`)
    return ret
  }
  pauseAudioMixing() : number  {
    let ret: number = NERtcSDK.getInstance().pauseAudioMixing()
    console.info(TAG, `pauseAudioMixing ret:${ret}`)
    return ret
  }
  resumeAudioMixing() : number {
    let ret: number = NERtcSDK.getInstance().resumeAudioMixing()
    console.info(TAG, `resumeAudioMixing ret:${ret}`)
    return ret
  }
  stopAudioMixing() : number {
    let ret: number = NERtcSDK.getInstance().stopAudioMixing()
    console.info(TAG, `stopAudioMixing ret:${ret}`)
    return ret
  }
  playEffect(effectId: number, option: NERtcConstants.NERtcCreateAudioEffectOption) : number {
    let ret: number = NERtcSDK.getInstance().playEffect(effectId, option)
    console.info(TAG, `playEffect ret:${ret}`)
    return ret
  }
  pauseEffect(effectId: number) : number {
    let ret: number = NERtcSDK.getInstance().pauseEffect(effectId)
    console.info(TAG, `pauseEffect ret:${ret}`)
    return ret
  }
  resumeEffect(effectId: number) : number {
    let ret: number = NERtcSDK.getInstance().resumeEffect(effectId)
    console.info(TAG, `resumeEffect ret:${ret}`)
    return ret
  }
  stopEffect(effectId: number) : number {
    let ret: number = NERtcSDK.getInstance().stopEffect(effectId)
    console.info(TAG, `stopEffect ret:${ret}`)
    return ret
  }
  pauseAllEffects() : number {
    let ret: number = NERtcSDK.getInstance().pauseAllEffects()
    console.info(TAG, `pauseAllEffects ret:${ret}`)
    return ret
  }
  resumeAllEffects() : number {
    let ret: number = NERtcSDK.getInstance().resumeAllEffects()
    console.info(TAG, `resumeAllEffects ret:${ret}`)
    return ret
  }
  stopAllEffects() : number {
    let ret: number = NERtcSDK.getInstance().stopAllEffects()
    console.info(TAG, `stopAllEffects ret:${ret}`)
    return ret
  }
  release() {
    NERtcSDK.getInstance().release()
    console.info(TAG, 'Call release done.')
  }
}

class ChatCallback extends NERtcCallbackEx {

  onJoinChannel(result: number, channelId: bigint, elapsed: bigint, uid: bigint): void {
    delegates?.forEach(delegate => {
      delegate.onJoin(result, channelId)
    })
  }

  onLeaveChannel(result: number): void {
    delegates?.forEach(delegate => {
      delegate.onLeave(result)
    })
  }

  onUserJoined(uid: bigint, extraInfo?: NERtcConstants.NERtcUserJoinExtraInfo): void {

    if(remoteUsers.indexOf(uid, 0) === -1) {
      remoteUsers.push(uid)
    }

    delegates?.forEach((delegate, index) => {
      if(delegate.onUserJoin) {
        delegate.onUserJoin(uid)
      }
    })
  }

  onUserLeave(uid: bigint, reason: number, extraInfo?: NERtcConstants.NERtcUserLeaveExtraInfo): void {

    let index = remoteUsers.indexOf(uid, 0)
    if(index !== -1) {
      remoteUsers.splice(index, 1)
    }

    console.info(TAG, 'remoteUsers size:' + remoteUsers.length)
    delegates?.forEach(delegate => {
      if(delegate.onUserLeave) {
        delegate.onUserLeave(uid, reason)
      }
    })
  }

  onUserAudioStart(uid: bigint): void {
    delegates?.forEach(delegate => {
      if(delegate.onUserAudioStart)
       delegate.onUserAudioStart(uid)
    })
  }

  onUserAudioStop(uid: bigint): void {
    delegates?.forEach(delegate => {
      if(delegate.onUserAudioStop)
        delegate.onUserAudioStop(uid)
    })
  }

  onUserVideoStart(uid: bigint, maxProfile: number): void {
    delegates?.forEach(delegate => {
      if(delegate.onUserVideoStart)
        delegate.onUserVideoStart(uid)
    })
  }

  onUserVideoStop(uid: bigint): void {
    delegates?.forEach(delegate => {
      if(delegate.onUserVideoStop)
        delegate.onUserVideoStop(uid)
    })
  }
  onLastmileQuality(quality: number):void {
    delegates?.forEach(delegate => {
      if(delegate.onLastmileQuality)
        delegate.onLastmileQuality(quality)
    })
  }
  onLastmileProbeResult(result: NERtcConstants.LiteSDKProbeResult):void {
    delegates?.forEach(delegate => {
      if(delegate.onLastmileProbeResult)
        delegate.onLastmileProbeResult(result)
    })
  }
  onDisconnect(reason: number): void {
    console.info(TAG, 'onDisconnect reason: ' + reason)
  }

  onClientRoleChange(oldRole: number, newRole: number): void {
    console.info(TAG, 'onClientRoleChange oldRole: ' + oldRole + ', newRole: ' + newRole)
  }

  onRecvSEIMsg(userId: bigint, data: Uint8Array, dataSize: number): void {
    console.info(TAG, 'onReceiveSEIMessage userId: ' + userId + ', data:' + String(data) + ", dataSize: " + dataSize)
  }

  onAddLiveStreamTask(taskId: string, url: string, errorCode: number): void {
    delegates?.forEach(delegate => {
      if(delegate.onLiveStreamEvent) {
        delegate.onLiveStreamEvent(model.LiveStreamEvent.ADD, taskId, url, errorCode)
      }
    })
  }

  onUpdateLiveStreamTask(taskId: string, url: string, errorCode: number): void {
    delegates?.forEach(delegate => {
      if(delegate.onLiveStreamEvent) {
        delegate.onLiveStreamEvent(model.LiveStreamEvent.UPDATE, taskId, url, errorCode)
      }
    })
  }

  onRemoveLiveStreamTask(taskId: string, errorCode: number): void {
    delegates?.forEach(delegate => {
      if(delegate.onLiveStreamEvent) {
        delegate.onLiveStreamEvent(model.LiveStreamEvent.DEL, taskId, '', errorCode)
      }
    })
  }

}
