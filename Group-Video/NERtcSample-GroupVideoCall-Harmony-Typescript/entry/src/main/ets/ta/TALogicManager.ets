import RtcTool from '../ta/RtcTool'
import { NERtcSDK, NERtcConstants } from 'sdk'

const TAG: string = '[Demo][Ta]';

export default class TALogicManager {

  isJSONString(str: string): boolean {
    try {
      JSON.parse(str);
      return true;
    } catch (e) {
      return false;
    }
  }

  public execCommand(jsonString: string): string {
    console.info(TAG, "command: " + jsonString)
    if (jsonString.length < 2) {
      console.error(TAG, "command error: jsonString is invalid")
      return RtcTool.respDataNumber(-1, "execCommand");
    }

    if (!this.isJSONString(jsonString)) {
      console.error(TAG, "command error: jsonString is not json string")
      return RtcTool.respDataNumber(-1, "execCommand");
    }

    interface Data {
      method: string;
    }
    let data: Data = JSON.parse(jsonString);
    let method: string = data.method
    console.info(TAG, "Method:" + method)
    if (method === "AdjustRecordingSignalVolume") {
      return this.execAdjustRecordingSignalVolume(jsonString);
    }
    else if (method === "EnableEarback") {
      return this.execEnableEarback(jsonString);
    }
    else if (method === "SetEarbackVolume") {
      return this.execSetEarbackVolume(jsonString);
    }
    else if (method === "SetStreamAlignmentProperty") {
      return this.execSetStreamAlignmentProperty(jsonString);
    }
    else if (method === "GetNtpTimeOffset") {
      return this.execGetNtpTimeOffset(jsonString);
    }
    else if (method === "StartAudioMixing") {
      return this.execStartAudioMixingWithOption(jsonString);
    }
    else if (method === "StopAudioMixing") {
      return this.execStopAudioMixing(jsonString);
    }
    else if (method === "PauseAudioMixing") {
      return this.execPauseAudioMixing(jsonString);
    }
    else if (method === "ResumeAudioMixing") {
      return this.execResumeAudioMixing(jsonString);
    }
    else if (method === "SetAudioMixingPlaybackVolume") {
      return this.execSetAudioMixingPlaybackVolume(jsonString);
    }
    else if (method === "SetAudioMixingSendVolume") {
      return this.execSetAudioMixingSendVolume(jsonString);
    }
    else if (method === "GetAudioMixingDuration") {
      return this.execGetAudioMixingDuration(jsonString);
    }
    else if (method === "GetAudioMixingCurrentPosition") {
      return this.execGetAudioMixingCurrentPosition(jsonString);
    }
    else if (method === "PlayEffect") {
      return this.execPlayEffect(jsonString);
    }
    else if (method === "StopEffect") {
      return this.execStopEffect(jsonString);
    }
    else if (method === "PauseEffect") {
      return this.execPauseEffect(jsonString);
    }
    else if (method === "ResumeEffect") {
      return this.execResumeEffect(jsonString);
    }
    else if (method === "StopAllEffects") {
      return this.execStopAllEffects(jsonString);
    }
    else if (method === "PauseAllEffects") {
      return this.execPauseAllEffects(jsonString);
    }
    else if (method === "ResumeAllEffects") {
      return this.execResumeAllEffects(jsonString);
    }
    else if (method === "AddLiveStreamTask") {
      return this.execAddLiveStreamTask(jsonString);
    }
    else if (method === "UpdateLiveStreamTask") {
      return this.execUpdateLiveStreamTask(jsonString);
    }
    else if (method === "RemoveLiveStreamTask") {
      return this.execRemoveLiveStreamTask(jsonString);
    }

    return RtcTool.respDataString("方法不存在", "execCommand");
  };

  private execAdjustRecordingSignalVolume(jsonString: string): string {
    interface Data {
      volume: number;
    }
    let data: Data = JSON.parse(jsonString);
    console.info(TAG, "execAdjustRecordingSignalVolume volume:" + data.volume)
    let ret = NERtcSDK.getInstance().adjustRecordingSignalVolume(data.volume);
    return RtcTool.respDataNumber(ret, "execAdjustRecordingSignalVolume");
  }

  private execEnableEarback(jsonString: string): string {
    interface Data {
      volume: number;
      enabled: boolean;
    }
    let data: Data = JSON.parse(jsonString);
    console.info(TAG, "execEnableEarback enabled:" + data.enabled)
    console.info(TAG, "execEnableEarback volume:" + data.volume)
    let ret = NERtcSDK.getInstance().enableEarback(data.enabled, data.volume);
    return RtcTool.respDataNumber(ret, "execEnableEarback");
  }

  private execSetEarbackVolume(jsonString: string): string {
    interface Data {
      volume: number;
    }
    let data: Data = JSON.parse(jsonString);
    console.info(TAG, "execSetEarbackVolume volume:" + data.volume)
    let ret = NERtcSDK.getInstance().setEarbackVolume(data.volume);
    return RtcTool.respDataNumber(ret, "execSetEarbackVolume");
  }

  private execSetStreamAlignmentProperty(jsonString: string): string {
    interface Data {
      enable: boolean;
    }
    let data: Data = JSON.parse(jsonString);
    NERtcSDK.getInstance().setStreamAlignmentProperty(data.enable);
    return RtcTool.respDataNumber(0, "execSetStreamAlignmentProperty");
  }

  private execGetNtpTimeOffset(jsonString: string): string {
    let ret = NERtcSDK.getInstance().getNtpTimeOffset();
    return RtcTool.respDataBigint(ret, "execGetNtpTimeOffset");
  }

  private execStartAudioMixingWithOption(jsonString: string): string {
    interface Data {
      path: string;
      loopCount: number;
      sendEnabled: boolean;
      playbackEnabled: boolean;
      sendVolume: number;
      playbackVolume: number;
      startTimeStamp: bigint;
      sendWithAudioType: NERtcConstants.NERtcAudioStreamType;
      progressInterval: bigint
    }
    let data: Data = JSON.parse(jsonString);
    let option: NERtcConstants.NERtcCreateAudioMixingOption = {
      path: data.path,
      loopCount: data.loopCount,
      sendEnabled: data.sendEnabled,
      playbackEnabled: data.playbackEnabled,
      sendVolume: data.sendVolume,
      playbackVolume: data.playbackVolume,
      startTimeStamp: data.startTimeStamp,
      sendWithAudioType: data.sendWithAudioType,
      progressInterval: data.progressInterval
    };
    let ret = NERtcSDK.getInstance().startAudioMixing(option);
    return RtcTool.respDataNumber(0, "execStartAudioMixingWithOption");
  }

  private execStopAudioMixing(jsonString: string): string {
    let ret = NERtcSDK.getInstance().stopAudioMixing();
    return RtcTool.respDataNumber(ret, "execStopAudioMixing");
  }

  private execPauseAudioMixing(jsonString: string): string {
    let ret = NERtcSDK.getInstance().pauseAudioMixing();
    return RtcTool.respDataNumber(ret, "execPauseAudioMixing");
  }

  private execResumeAudioMixing(jsonString: string): string {
    let ret = NERtcSDK.getInstance().resumeAudioMixing();
    return RtcTool.respDataNumber(ret, "execResumeAudioMixing");
  }

  private execSetAudioMixingPlaybackVolume(jsonString: string): string {
    interface Data {
      volume: number;
    }
    let data: Data = JSON.parse(jsonString);
    console.info(TAG, "execSetAudioMixingPlaybackVolume volume:" + data.volume)
    let ret = NERtcSDK.getInstance().setAudioMixingPlaybackVolume(data.volume)
    return RtcTool.respDataNumber(ret, "execSetAudioMixingPlaybackVolume")
  }

  private execSetAudioMixingSendVolume(jsonString: string): string {
    interface Data {
      volume: number;
    }
    let data: Data = JSON.parse(jsonString);
    console.info(TAG, "execSetAudioMixingSendVolume volume:" + data.volume)
    let ret = NERtcSDK.getInstance().setAudioMixingSendVolume(data.volume)
    return RtcTool.respDataNumber(ret, "execSetAudioMixingSendVolume")
  }

  private execGetAudioMixingDuration(jsonString: string): string {
    let duration: bigint = BigInt(0);
    let ret = NERtcSDK.getInstance().getAudioMixingDuration(duration)
    return RtcTool.respDataBigint(duration, "execGetAudioMixingDuration")
  }

  private execGetAudioMixingCurrentPosition(jsonString: string): string {
    let position: bigint = BigInt(0)
    let ret = NERtcSDK.getInstance().getAudioMixingCurrentPosition(position)
    return RtcTool.respDataBigint(position, "execGetAudioMixingCurrentPosition")
  }

  private execPlayEffect(jsonString: string): string {
    interface Data {
      effect_id: number;
      path: string;
      loopCount: number;
      sendEnabled: boolean;
      playbackEnabled: boolean;
      sendVolume: number;
      playbackVolume: number;
      startTimeStamp: bigint;
      sendWithAudioType: NERtcConstants.NERtcAudioStreamType;
      progressInterval: bigint
    }
    let data: Data = JSON.parse(jsonString);
    let option: NERtcConstants.NERtcCreateAudioEffectOption = {
      path: data.path,
      loopCount: data.loopCount,
      sendEnabled: data.sendEnabled,
      playbackEnabled: data.playbackEnabled,
      sendVolume: data.sendVolume,
      playbackVolume: data.playbackVolume,
      startTimeStamp: data.startTimeStamp,
      sendWithAudioType: data.sendWithAudioType,
      progressInterval: data.progressInterval
    };
    let ret = NERtcSDK.getInstance().playEffect(data.effect_id, option)
    return RtcTool.respDataNumber(0, "execPlayEffect")
  }

  private execStopEffect(jsonString: string): string {
    interface Data {
      effect_id: number;
    }
    let data: Data = JSON.parse(jsonString);
    console.info(TAG, "execStopEffect volume:" + data.effect_id)
    let ret = NERtcSDK.getInstance().stopEffect(data.effect_id)
    return RtcTool.respDataNumber(ret, "execStopEffect")
  }

  private execPauseEffect(jsonString: string): string {
    interface Data {
      effect_id: number;
    }
    let data: Data = JSON.parse(jsonString);
    console.info(TAG, "execPauseEffect volume:" + data.effect_id)
    let ret = NERtcSDK.getInstance().pauseEffect(data.effect_id)
    return RtcTool.respDataNumber(ret, "execPauseEffect");
  }

  private execResumeEffect(jsonString: string): string {
    interface Data {
      effect_id: number;
    }
    let data: Data = JSON.parse(jsonString);
    console.info(TAG, "execResumeEffect volume:" + data.effect_id)
    let ret = NERtcSDK.getInstance().resumeEffect(data.effect_id)
    return RtcTool.respDataNumber(ret, "execResumeEffect");
  }

  private execStopAllEffects(jsonString: string): string {
    let ret = NERtcSDK.getInstance().stopAllEffects();
    return RtcTool.respDataNumber(ret, "execStopAllEffects");
  }

  private execPauseAllEffects(jsonString: string): string {
    let ret = NERtcSDK.getInstance().pauseAllEffects();
    return RtcTool.respDataNumber(ret, "execPauseAllEffects");
  }

  private execResumeAllEffects(jsonString: string): string {
    let ret = NERtcSDK.getInstance().resumeAllEffects();
    return RtcTool.respDataNumber(ret, "execResumeAllEffects");
  }

  public  execAddLiveStreamTask(jsonString: string): string {
    interface Data {
      task_id: string
      task_stream_url: string
      uid: string
      uids: string
      extra_info: string
      server_record: boolean
      live_model: number
      config_singleVideoPassThrough: boolean
      config_audioBitrate: number
      config_channels: number
      config_sampleRate: number
      layout_width: number
      layout_height: number
      layout_backGroundColor: number
    }

    let data: Data = JSON.parse(jsonString)
    let info: NERtcConstants.NERtcLiveStreamTaskInfo = new NERtcConstants.NERtcLiveStreamTaskInfo
    info.taskID = data.task_id
    info.streamURL = data.task_stream_url
    info.extraInfo = data.extra_info
    info.serverRecordEnabled = data.server_record
    if (data.live_model == 0) {
      info.lsMode = NERtcConstants.NERtcLiveStreamMode.kNERtcLsModeVideo
    }
    else if (data.live_model == 1) {
      info.lsMode = NERtcConstants.NERtcLiveStreamMode.kNERtcLsModeAudio
    }

    let layout: NERtcConstants.NERtcLiveStreamLayout = new NERtcConstants.NERtcLiveStreamLayout
    info.layout = layout
    layout.width = data.layout_width
    layout.height = data.layout_height
    layout.backgroundColor = data.layout_backGroundColor
    
    const uidArray: string[] = data.uids.split(",")
    let length: number = uidArray.length
    if (length > 1) {
      layout.users = []
      for (let i = 0; i < length; i++) {
        let user: NERtcConstants.NERtcLiveStreamUserTranscoding = new NERtcConstants.NERtcLiveStreamUserTranscoding
        user.uid = BigInt(uidArray[i]);
        user.zOrder = i + 1
        user.x = i * (data.layout_width/length)
        user.width = (data.layout_width/length)
        user.height = data.layout_height
        layout.users.push(user)
      }
    }
    else {
      let user: NERtcConstants.NERtcLiveStreamUserTranscoding = new NERtcConstants.NERtcLiveStreamUserTranscoding
      user.uid = BigInt(data.uid);
      user.width = data.layout_width
      user.height = data.layout_height
      layout.users = [user]
    }

    let ret = NERtcSDK.getInstance().addLiveStreamTask(info)
    return RtcTool.respDataNumber(ret, "execAddLiveStreamTask");
  }

  public execUpdateLiveStreamTask(jsonString: string): string {
    interface Data {
      task_id: string
      task_stream_url: string
      uid: string
      uids: string
      extra_info: string
      server_record: boolean
      live_model: number
      config_singleVideoPassThrough: boolean
      config_audioBitrate: number
      config_channels: number
      config_sampleRate: number
      layout_width: number
      layout_height: number
      layout_backGroundColor: number
    }

    let data: Data = JSON.parse(jsonString)
    let info: NERtcConstants.NERtcLiveStreamTaskInfo = new NERtcConstants.NERtcLiveStreamTaskInfo
    info.taskID = data.task_id
    info.streamURL = data.task_stream_url
    info.extraInfo = data.extra_info
    info.serverRecordEnabled = data.server_record
    if (data.live_model == 0) {
      info.lsMode = NERtcConstants.NERtcLiveStreamMode.kNERtcLsModeVideo
    }
    else if (data.live_model == 1) {
      info.lsMode = NERtcConstants.NERtcLiveStreamMode.kNERtcLsModeAudio
    }

    let layout: NERtcConstants.NERtcLiveStreamLayout = new NERtcConstants.NERtcLiveStreamLayout
    info.layout = layout
    layout.width = data.layout_width
    layout.height = data.layout_height
    layout.backgroundColor = data.layout_backGroundColor

    const uidArray: string[] = data.uids.split(",")
    let length: number = uidArray.length
    if (length > 1) {
      layout.users = []
      for (let i = 0; i < length; i++) {
        let user: NERtcConstants.NERtcLiveStreamUserTranscoding = new NERtcConstants.NERtcLiveStreamUserTranscoding
        user.uid = BigInt(uidArray[i]);
        user.zOrder = i + 1
        user.x = i * (data.layout_width/length)
        user.width = (data.layout_width/length)
        user.height = data.layout_height
        layout.users.push(user)
      }
    }
    else {
      let user: NERtcConstants.NERtcLiveStreamUserTranscoding = new NERtcConstants.NERtcLiveStreamUserTranscoding
      user.uid = BigInt(data.uid);
      user.width = data.layout_width
      user.height = data.layout_height
      layout.users = [user]
    }
    let ret = NERtcSDK.getInstance().updateLiveStreamTask(info)
    return RtcTool.respDataNumber(ret, "execUpdateLiveStreamTask");
  }

  public execRemoveLiveStreamTask(jsonString: string): string {
    interface Data {
      task_id: string;
    }
    let data: Data = JSON.parse(jsonString);
    console.info(TAG, "execRemoveLiveStreamTask task_id:" + data.task_id)
    let ret = NERtcSDK.getInstance().removeLiveStreamTask(data.task_id)
    return RtcTool.respDataNumber(ret, "execRemoveLiveStreamTask");
  }
}