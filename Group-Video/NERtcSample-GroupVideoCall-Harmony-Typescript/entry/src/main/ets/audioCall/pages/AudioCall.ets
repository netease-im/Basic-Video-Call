import router from '@ohos.router';
import Delegate from '../../common/Delegate';
import { LoginInfo } from '../../common/Model'
import ChatPresenter from '../../common/Presenter'
import { NERtcStatsObserver, NERtcConstants} from '@nertc/nertc_sdk';
import prompt from '@ohos.promptAction';
let TAG: string = 'audioCall'

@Entry
@Component
struct audioCall {

  TAG: string = "audioCall"

  @State cname: string = ""
  @State uid: string = ""
  @State volumeInfo: string = ""
  @State networkInfo: string = ""
  @State useSpeaker: boolean = false
  @State useMic: boolean = false
  @State login: LoginInfo = {
    cname: "",
    uid: ""
  };
  @State remoteList: bigint[] = [BigInt(0), BigInt(0), BigInt(0), BigInt(0), BigInt(0), BigInt(0)]
  networkList: string[] = ["未知", "非常好", "好", "一般", "差", "非常差", "无网络"]
  onPageShow() {
    console.info(this.TAG, '=== CallPage show ===')
    ChatPresenter.getInstance().setDelegate(this.delegate)
    this.login = router.getParams() as LoginInfo
    this.cname = this.login.cname
    this.uid = this.login.uid
    this.init()
    this.beforeJoin()
    this.joinRoom()
  }
  onPageHide(): void {
    ChatPresenter.getInstance().leave()
    ChatPresenter.getInstance().removeDelegate(this.delegate)
    ChatPresenter.getInstance().release()
  }
  init() {
    ChatPresenter.getInstance().init(getContext())
  }
  beforeJoin() {
    ChatPresenter.getInstance().setStatsObserver(this.observer)
    ChatPresenter.getInstance().enableAudio(true)
  }
  joinRoom() {
    ChatPresenter.getInstance().join(this.login)
  }
  observer: NERtcStatsObserver = {

    onRtcStats: (stats: NERtcConstants.NERtcStats): void => {

    },

    onLocalAudioStats: (stats: NERtcConstants.NERtcAudioSendStats): void => {

    },

    onRemoteAudioStats: (statsArray: Array<NERtcConstants.NERtcAudioRecvStats>): void => {

      let volumeInfoTmp = ""
      for(let i = 0;i < statsArray.length;i++){
        let layers = statsArray[i].layers
        let volume: number = 0;
        if(layers) {
          volume = layers[0].volume
        }
        volumeInfoTmp += "uid: " + statsArray[i].uid + "  音量: " + volume + "\n"
      }
      this.volumeInfo = volumeInfoTmp;
    },

    onLocalVideoStats: (stats: NERtcConstants.NERtcVideoSendStats): void => {

    },

    onRemoteVideoStats: (statsArray: Array<NERtcConstants.NERtcVideoRecvStats>): void => {

    },

    onNetworkQuality: (statsArray: Array<NERtcConstants.NERtcNetworkQualityInfo>): void => {
      let networkInfoTmp = ""
      for(let i = 0;i < statsArray.length;i++){
        if (statsArray[i].uid.toString() == this.uid)
            continue
        networkInfoTmp += "uid: " + statsArray[i].uid + "  网络状态: " + this.networkList[statsArray[i].downStatus] + "\n"
      }
      this.networkInfo = networkInfoTmp;
    }

  }
  delegate: Delegate = {
    onJoin: (result: number, channelId: bigint): void => {
      prompt.showToast({ message: 'Join channel async result:' + result, duration: 2000 })
    },
    onLeave: (result: number): void =>{

    },
    onUserJoin:(uid: bigint): void => {
      let idx = this.findFalseIndex(uid)
      if(idx != -1)
        return
      idx = this.findFalseIndex(BigInt(0))
      this.remoteList[idx] = uid
    },
    onUserLeave:(uid: bigint, reason: number): void => {
      let idx = this.findFalseIndex(uid)
      if (idx == -1)
        return
      this.remoteList[idx] = BigInt(0)
    },
    onUserAudioStart:(uid: bigint): void =>{

    },
    onUserAudioStop:(uid: bigint): void =>{

    },
    onUserVideoStart:(uid: bigint): void =>{

    },
    onUserVideoStop:(uid: bigint): void =>{

    }
  };
  findFalseIndex(uid: bigint) {
    let Index = -1;
    for (let i = 0; i < this.remoteList.length; i++) {
      if (this.remoteList[i] == uid) {
        Index = i;
        break;
      }
    }
    return Index;
  }
  build() {
    Row() {
      Column() {
          Text('房间号: ' + this.cname)
            .width('100%')
            .fontSize(20)
            .textAlign(TextAlign.Center)
            .margin({ top: "20vp", bottom: "20vp" })
          Row() {
              Column() {
                Image(this.remoteList[0] == BigInt(0) ? $r('app.media.common_user_portrait') : $r('app.media.common_user_live'))
                  .width("60vp")
                  .objectFit(ImageFit.Contain).margin(15)
                  .margin({ top: "10vp", bottom: "40vp" })
                Text(this.remoteList[0] == BigInt(0) ? '': 'uid:' + this.remoteList[0])
                  .fontSize(10)
              }
              .justifyContent(FlexAlign.Start)
              Column() {
                Image(this.remoteList[1] == BigInt(0) ? $r('app.media.common_user_portrait') : $r('app.media.common_user_live'))
                  .width("60vp")
                  .objectFit(ImageFit.Contain).margin(15)
                  .margin({ top: "10vp", bottom: "40vp" })
                Text(this.remoteList[1] == BigInt(0) ? '': 'uid:' + this.remoteList[1])
                  .fontSize(10)
              }
              .justifyContent(FlexAlign.Start)
              Column() {
                Image(this.remoteList[2] == BigInt(0) ? $r('app.media.common_user_portrait') : $r('app.media.common_user_live'))
                  .width("60vp")
                  .objectFit(ImageFit.Contain).margin(15)
                  .margin({ top: "10vp", bottom: "40vp" })
                Text(this.remoteList[2] == BigInt(0) ? '': 'uid:' + this.remoteList[2])
                  .fontSize(10)
              }
              .justifyContent(FlexAlign.Start)
          }
          .width('100%')
          .justifyContent(FlexAlign.SpaceAround)
          Row() {
            Column() {
              Image(this.remoteList[3] == BigInt(0) ? $r('app.media.common_user_portrait') : $r('app.media.common_user_live'))
                .width("60vp")
                .objectFit(ImageFit.Contain).margin(15)
                .margin({ top: "10vp", bottom: "40vp" })
              Text(this.remoteList[3] == BigInt(0) ? '': 'uid:' + this.remoteList[3])
                .fontSize(10)
            }
            .justifyContent(FlexAlign.Start)
            Column() {
              Image(this.remoteList[4] == BigInt(0) ? $r('app.media.common_user_portrait') : $r('app.media.common_user_live'))
                .width("60vp")
                .objectFit(ImageFit.Contain).margin(15)
                .margin({ top: "10vp", bottom: "40vp" })
              Text(this.remoteList[4] == BigInt(0) ? '': 'uid:' + this.remoteList[4])
                .fontSize(10)
            }
            .justifyContent(FlexAlign.Start)
            Column() {
              Image(this.remoteList[5] == BigInt(0) ? $r('app.media.common_user_portrait') : $r('app.media.common_user_live'))
                .width("60vp")
                .objectFit(ImageFit.Contain).margin(15)
                .margin({ top: "10vp", bottom: "40vp" })
              Text(this.remoteList[5] == BigInt(0) ? '': 'uid:' + this.remoteList[5])
                .fontSize(10)
            }
            .justifyContent(FlexAlign.Start)
          }
          .width('100%')
          .justifyContent(FlexAlign.SpaceAround)

          Row({ space: 25}) {
            Text('用户音量: \n' + this.volumeInfo)
              .width('100%')
              .fontSize(15)
              .textAlign(TextAlign.Start)
              .margin({ top: "20vp", bottom: "20vp" })
          }.justifyContent(FlexAlign.Start).width('100%').margin({ top: 20 })

          Row({ space: 25}) {
            Text('网络状态: \n' + this.networkInfo)
              .width('100%')
              .fontSize(15)
              .textAlign(TextAlign.Start)
              .margin({ top: "20vp", bottom: "20vp" })
          }.justifyContent(FlexAlign.Start).width('100%').margin({ top: 20 })

        Row() {
          Button(this.useSpeaker ? "使用扬声器" : "使用听筒", { type: ButtonType.Normal, stateEffect: true})
            .onClick(() => {
              ChatPresenter.getInstance().setSpeakPhoneOn(this.useSpeaker);
              this.useSpeaker = !this.useSpeaker
            })
            .width('130vp')
            .height(60)
            .fontSize(17)
            .borderRadius(10)
          Button(this.useMic ? "打开麦克风" : "关闭麦克风", { type: ButtonType.Normal, stateEffect: true})
            .onClick(() => {
              ChatPresenter.getInstance().enableAudio(this.useMic);
              this.useMic = !this.useMic
            })
            .width('130vp')
            .height(60)
            .fontSize(17)
            .borderRadius(10)
          Button("挂断", { type: ButtonType.Normal, stateEffect: true})
            .onClick(() => {
              ChatPresenter.getInstance().leave()
              ChatPresenter.getInstance().removeDelegate(this.delegate)
              ChatPresenter.getInstance().release()
              router.back()
            })
            .width('130vp')
            .height(60)
            .fontSize(17)
            .borderRadius(10)
        }
        .width('100%')
        .justifyContent(FlexAlign.SpaceAround)
      }
      .width('100%')
      .height('100%')
      .justifyContent(FlexAlign.SpaceBetween)
    }
    .width('100%')
    .height('100%')
  }

}