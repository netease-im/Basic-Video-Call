import router from '@ohos.router';
import Delegate from '../common/Delegate';
import ChatPresenter from '../common/Presenter'
import { NERtcVideoView, NERtcConstants} from 'sdk';
import * as model from '../common/Model';
import prompt from '@ohos.promptAction';

@Entry
@Component
struct VoiceBeauty {

  TAG: string = "VoiceBeauty"
  chat?: ChatPresenter
  @State cname: string = ""
  @State uid: string = ""
  @State useBackCamera: boolean = true
  @State closeCamera: boolean = false
  @State closeMic: boolean = false
  @State useEarpiece: boolean = false
  @State local?: model.User = undefined
  @State login: model.LoginInfo = {
    cname: "1392",
    uid: Math.floor(Math.random() * 10000).toString()
  };
  @State remoteUser1?: model.User = undefined
  @State remoteUser2?: model.User = undefined
  @State remoteUser3?: model.User = undefined
  @State remoteUser4?: model.User = undefined
  @State btnVoiceChange: boolean[] = [false, false, false, false, false]
  @State btnVoiceBeauty: boolean[] = [false, false, false, false, false]

  remoteUserList: bigint[] = []

  onPageShow() {
    console.info(this.TAG, '=== CallPage show ===')
    ChatPresenter.getInstance().setDelegate(this.delegate)
    this.local = { uid: BigInt(this.login?.uid ?? 0) }
    this.chat = ChatPresenter.getInstance()
    this.init(this.login)
    this.beforeJoin()
    this.joinRoom()
  }
  onPageHide(): void {
    ChatPresenter.getInstance().leave()
    ChatPresenter.getInstance().removeDelegate(this.delegate)
    ChatPresenter.getInstance().release()
  }
  init(login: model.LoginInfo) {
    ChatPresenter.getInstance().init(getContext())
  }
  beforeJoin() {
    ChatPresenter.getInstance().enableVideo(true)
    ChatPresenter.getInstance().enableAudio(true)
  }
  joinRoom() {
    ChatPresenter.getInstance().join(this.login)
  }
  delegate: Delegate = {
    onJoin: (result: number, channelId: bigint): void => {
      prompt.showToast({ message: 'Join channel async result:' + result, duration: 2000 })
    },
    onLeave: (result: number): void =>{

    },
    onUserJoin:(uid: bigint): void => {
      if(this.findFalseIndex(uid) != -1){
        return
      }
      this.remoteUserList.push(uid);
      if(this.remoteUser1 == undefined) {
        this.remoteUser1 = { uid: uid }
        console.info(this.TAG, 'Create Remote User1.')
      }else if(this.remoteUser2 == undefined) {
        this.remoteUser2 = { uid: uid }
        console.info(this.TAG, 'Create Remote User2.')
      }else if(this.remoteUser3 == undefined) {
        this.remoteUser3 = { uid: uid }
        console.info(this.TAG, 'Create Remote User3.')
      }else if(this.remoteUser4 == undefined){
        this.remoteUser4 = { uid: uid }
        console.info(this.TAG, 'Create Remote User4.')
      }
    },
    onUserLeave:(uid: bigint, reason: number): void => {
      if(this.findFalseIndex(uid) == -1){
        return
      }
      this.remoteUserList.splice(this.findFalseIndex(uid), 1);
      if(this.remoteUser1 && this.remoteUser1.uid === uid) {
        this.remoteUser1 = undefined
      }else if(this.remoteUser2 && this.remoteUser2.uid === uid) {
        this.remoteUser2 = undefined
      }else if(this.remoteUser3 && this.remoteUser3.uid === uid) {
        this.remoteUser3 = undefined
      }else if(this.remoteUser4 && this.remoteUser4.uid === uid){
        this.remoteUser4 = undefined
      }
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
    let index = -1
    for (let i = 0; i < this.remoteUserList.length; i++) {
      if (this.remoteUserList[i] == uid) {
        index = i
        break
      }
    }
    return index
  }
  changeVoiceBtnState(idx: number){
    for(let i = 0;i < this.btnVoiceChange.length;i++){
      if(i != idx){
        this.btnVoiceChange[i] = false;
      }
    }
    this.btnVoiceChange[idx] = true;
  }
  beautyVoiceBtnState(idx: number){
    for(let i = 0;i < this.btnVoiceBeauty.length;i++){
      if(i != idx){
        this.btnVoiceBeauty[i] = false;
      }
    }
    this.btnVoiceBeauty[idx] = true;
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
          if (this.local) {
            NERtcVideoView({
              canvasId: String(this.local.uid),
              onLoad: (() => {
                console.info(this.TAG, `User: ${this.local?.uid} surface create.`)
                if (this.local) this.chat?.attach(this.local)
              }),
              onDestroy: (() => {
                console.info(this.TAG, `User: ${this.local?.uid} surface release.`)
              })
            }).width('100%').height('40%')
          }
        }
        Row() {
          if (this.remoteUser1) {
            NERtcVideoView({
              canvasId: String(this.remoteUser1.uid),
              onLoad: (() => {
                if (this.remoteUser1) {
                  console.info(this.TAG, `User: ${String(this.remoteUser1?.uid)} surface create.`)
                  this.chat?.attach(this.remoteUser1)
                }
              }),
              onDestroy: (() => {
                if (this.remoteUser1) {
                  console.info(this.TAG, `User: ${String(this.remoteUser1?.uid)} surface release.`)
                }
              })
            }).width('25%').height('20%')
          }else{
            Image($r('app.media.common_user_portrait'))
              .width("25%")
              .objectFit(ImageFit.Contain).margin(15)
              .margin({ top: "10vp", bottom: "40vp" })
          }
          if (this.remoteUser2) {
            NERtcVideoView({
              canvasId: String(this.remoteUser2.uid),
              onLoad: (() => {
                if (this.remoteUser2) {
                  console.info(this.TAG, `User: ${String(this.remoteUser2?.uid)} surface create.`)
                  this.chat?.attach(this.remoteUser2)
                }
              }),
              onDestroy: (() => {
                if (this.remoteUser2) {
                  console.info(this.TAG, `User: ${String(this.remoteUser2?.uid)} surface release.`)
                }
              })
            }).width('25%').height('20%')
          }else{
            Image($r('app.media.common_user_portrait'))
              .width("25%")
              .objectFit(ImageFit.Contain).margin(15)
              .margin({ top: "10vp", bottom: "40vp" })
          }
          if (this.remoteUser3) {
            NERtcVideoView({
              canvasId: String(this.remoteUser3.uid),
              onLoad: (() => {
                if (this.remoteUser3) {
                  console.info(this.TAG, `User: ${String(this.remoteUser3?.uid)} surface create.`)
                  this.chat?.attach(this.remoteUser3)
                }
              }),
              onDestroy: (() => {
                if (this.remoteUser3) {
                  console.info(this.TAG, `User: ${String(this.remoteUser3?.uid)} surface release.`)
                }
              })
            }).width('25%').height('20%')
          }else{
            Image($r('app.media.common_user_portrait'))
              .width("25%")
              .objectFit(ImageFit.Contain).margin(15)
              .margin({ top: "10vp", bottom: "40vp" })
          }
          if (this.remoteUser4) {
            NERtcVideoView({
              canvasId: String(this.remoteUser4.uid),
              onLoad: (() => {
                if (this.remoteUser4) {
                  console.info(this.TAG, `User: ${String(this.remoteUser4?.uid)} surface create.`)
                  this.chat?.attach(this.remoteUser4)
                }
              }),
              onDestroy: (() => {
                if (this.remoteUser4) {
                  console.info(this.TAG, `User: ${String(this.remoteUser4?.uid)} surface release.`)
                }
              })
            }).width('25%').height('20%')
          }else{
            Image($r('app.media.common_user_portrait'))
              .width("25%")
              .objectFit(ImageFit.Contain).margin(15)
              .margin({ top: "10vp", bottom: "40vp" })
          }
        }
        .width('100%')
        .justifyContent(FlexAlign.SpaceBetween)
        Row() {
          Text('请选择变声效果： ')
            .width('100%')
            .fontSize(15)
            .textAlign(TextAlign.Start)
            .margin({ top: "5vp", bottom: "5vp" })
        }
        .justifyContent(FlexAlign.Start)
        Row() {
          Toggle({ type: ToggleType.Button, isOn: this.btnVoiceChange[0] }) {
            Text('默认')
              .fontColor('#182431')
              .fontSize(12)
          }.width("20%")
          .onChange((isOn: boolean) => {
            if(isOn) {
              this.changeVoiceBtnState(0);
              ChatPresenter.getInstance().setAudioEffectPreset(NERtcConstants.NERtcVoiceChangerType.kNERtcAudioEffectOFF)
            }
          })
          Toggle({ type: ToggleType.Button, isOn: this.btnVoiceChange[1] }) {
            Text('男变女')
              .fontColor('#182431')
              .fontSize(12)
          }.width("20%")
          .onChange((isOn: boolean) => {
            if(isOn) {
              this.changeVoiceBtnState(1);
              ChatPresenter.getInstance().setAudioEffectPreset(NERtcConstants.NERtcVoiceChangerType.kNERtcVoiceChangerEffectMantowoman)
            }
          })
          Toggle({ type: ToggleType.Button, isOn: this.btnVoiceChange[2] }) {
            Text('女变男')
              .fontColor('#182431')
              .fontSize(12)
          }.width("20%")
          .onChange((isOn: boolean) => {
            if(isOn) {
              this.changeVoiceBtnState(2);
              ChatPresenter.getInstance().setAudioEffectPreset(NERtcConstants.NERtcVoiceChangerType.kNERtcVoiceChangerEffectWomantoman)
            }
          })
          Toggle({ type: ToggleType.Button, isOn: this.btnVoiceChange[3] }) {
            Text('男变萝莉')
              .fontColor('#182431')
              .fontSize(12)
          }.width("20%")
          .onChange((isOn: boolean) => {
            if(isOn) {
              this.changeVoiceBtnState(3);
              ChatPresenter.getInstance().setAudioEffectPreset(NERtcConstants.NERtcVoiceChangerType.kNERtcVoiceChangerEffectMantololi)
            }
          })
          Toggle({ type: ToggleType.Button, isOn: this.btnVoiceChange[4] }) {
            Text('女变萝莉')
              .fontColor('#182431')
              .fontSize(12)
          }.width("20%")
          .onChange((isOn: boolean) => {
            if(isOn) {
              this.changeVoiceBtnState(4);
              ChatPresenter.getInstance().setAudioEffectPreset(NERtcConstants.NERtcVoiceChangerType.kNERtcVoiceChangerEffectWomanTololi)
            }
          })
        }
        .width('100%')
        .justifyContent(FlexAlign.Start)
        Row() {
          Text('请选择美声效果： ')
            .width('100%')
            .fontSize(15)
            .textAlign(TextAlign.Start)
            .margin({ top: "20vp", bottom: "5vp" })
        }
        .justifyContent(FlexAlign.Start)
        Row() {
          Toggle({ type: ToggleType.Button, isOn: this.btnVoiceBeauty[0] }) {
            Text('默认')
              .fontColor('#182431')
              .fontSize(12)
          }.width("20%")
          .onChange((isOn: boolean) => {
            if(isOn) {
              this.beautyVoiceBtnState(0);
              ChatPresenter.getInstance().setVoiceBeautifierPreset(NERtcConstants.NERtcVoiceBeautifierType.kNERtcVoiceBeautifierOFF)
            }
          })
          Toggle({ type: ToggleType.Button, isOn: this.btnVoiceBeauty[1] }) {
            Text('KTV')
              .fontColor('#182431')
              .fontSize(12)
          }.width("20%")
          .onChange((isOn: boolean) => {
            if(isOn) {
              this.beautyVoiceBtnState(1);
              ChatPresenter.getInstance().setVoiceBeautifierPreset(NERtcConstants.NERtcVoiceBeautifierType.kNERtcVoiceBeautifierKTV)
            }
          })
          Toggle({ type: ToggleType.Button, isOn: this.btnVoiceBeauty[2] }) {
            Text('卧室')
              .fontColor('#182431')
              .fontSize(12)
          }.width("20%")
          .onChange((isOn: boolean) => {
            if(isOn) {
              this.beautyVoiceBtnState(2);
              ChatPresenter.getInstance().setVoiceBeautifierPreset(NERtcConstants.NERtcVoiceBeautifierType.kNERtcVoiceBeautifierBedroom)
            }
          })
          Toggle({ type: ToggleType.Button, isOn: this.btnVoiceBeauty[3] }) {
            Text('磁性')
              .fontColor('#182431')
              .fontSize(12)
          }.width("20%")
          .onChange((isOn: boolean) => {
            if(isOn) {
              this.beautyVoiceBtnState(3);
              ChatPresenter.getInstance().setVoiceBeautifierPreset(NERtcConstants.NERtcVoiceBeautifierType.kNERtcVoiceBeautifierMagnetic)
            }
          })
          Toggle({ type: ToggleType.Button, isOn: this.btnVoiceBeauty[4] }) {
            Text('悠远')
              .fontColor('#182431')
              .fontSize(12)
          }.width("20%")
          .onChange((isOn: boolean) => {
            if(isOn) {
              this.beautyVoiceBtnState(4);
              ChatPresenter.getInstance().setVoiceBeautifierPreset(NERtcConstants.NERtcVoiceBeautifierType.kNERtcVoiceBeautifierRemote)
            }
          })
        }
        .width('100%')
        .justifyContent(FlexAlign.Start)

      }
      .width('100%')
      .height('100%')
      .justifyContent(FlexAlign.Start)
    }
    .width('100%')
    .height('100%')
  }

}