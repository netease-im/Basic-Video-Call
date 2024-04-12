import {NERtcConstants} from 'sdk';
import {LiveStreamEvent} from './Model'

export default interface Delegate {
  onJoin:(result: number, channelId: bigint) => void
  onLeave:(result: number) => void
  onUserJoin?:(uid: bigint) => void
  onUserLeave?:(uid: bigint, reason: number) => void
  onUserAudioStart?:(uid: bigint) => void
  onUserAudioStop?:(uid: bigint) => void
  onUserVideoStart?:(uid: bigint) => void
  onUserVideoStop?:(uid: bigint) => void
  onLastmileQuality?:(quality: number) =>void
  onLastmileProbeResult?:(result: NERtcConstants.LiteSDKProbeResult) =>void
  onLiveStreamEvent?:(state: LiveStreamEvent, taskId: string, url: string, errCode: number) => void;
}

