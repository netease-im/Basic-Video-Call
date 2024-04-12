import router from '@ohos.router';
import Delegate from '../../common/Delegate';
import ChatPresenter from '../../common/Presenter'
import { NERtcVideoView } from 'sdk';
import * as model from '../../common/Model';
import prompt from '@ohos.promptAction';

@Entry
@Component
struct videoCall {

  TAG: string = "videoCall"
  chat?: ChatPresenter
  @State cname: string = ""
  @State uid: string = ""
  @State useBackCamera: boolean = true
  @State closeCamera: boolean = false
  @State closeMic: boolean = false
  @State useEarpiece: boolean = false
  @State local?: model.User = undefined
  @State login: model.LoginInfo = {
    cname: "",
    uid: ""
  };
  @State remoteUser1?: model.User = undefined
  @State remoteUser2?: model.User = undefined
  @State remoteUser3?: model.User = undefined
  @State remoteUser4?: model.User = undefined
  remoteUserList: bigint[] = []

  onPageShow() {
    console.info(this.TAG, '=== CallPage show ===')
    ChatPresenter.getInstance().setDelegate(this.delegate)
    this.login = router.getParams() as model.LoginInfo
    this.cname = this.login.cname
    this.uid = this.login.uid
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
          Text('视频选项: ')
            .width('100%')
            .fontSize(15)
            .textAlign(TextAlign.Start)
            .margin({ top: "5vp", bottom: "5vp" })
        }
        .justifyContent(FlexAlign.Start)
        Row() {
          Button(this.useBackCamera ? "使用后置摄像头" : "使用前置摄像头", { type: ButtonType.Normal, stateEffect: true})
            .onClick(() => {
              ChatPresenter.getInstance().switchCamera();
              this.useBackCamera = !this.useBackCamera
            })
            .width('160vp')
            .height(30)
            .fontSize(17)
            .borderRadius(10)
          Button(this.closeCamera ? "打开摄像头" : "关闭摄像头", { type: ButtonType.Normal, stateEffect: true})
            .onClick(() => {
              ChatPresenter.getInstance().enableVideo(this.closeCamera);
              this.closeCamera = !this.closeCamera
            })
            .width('130vp')
            .height(30)
            .fontSize(17)
            .borderRadius(10)
        }
        .width('100%')
        .justifyContent(FlexAlign.Start)
        Row() {
          Text('音频选项: ')
            .width('100%')
            .fontSize(15)
            .textAlign(TextAlign.Start)
            .margin({ top: "20vp", bottom: "5vp" })
        }
        .justifyContent(FlexAlign.Start)
        Row() {
          Button(this.closeMic ? "打开麦克风" : "关闭麦克风", { type: ButtonType.Normal, stateEffect: true})
            .onClick(() => {
              ChatPresenter.getInstance().enableAudio(this.closeMic);
              this.closeMic = !this.closeMic
            })
            .width('130vp')
            .height(30)
            .fontSize(17)
            .borderRadius(10)
          Button(this.useEarpiece ? "使用扬声器" : "使用听筒", { type: ButtonType.Normal, stateEffect: true})
            .onClick(() => {
              ChatPresenter.getInstance().setSpeakPhoneOn(this.useEarpiece);
              this.useEarpiece = !this.useEarpiece
            })
            .width('130vp')
            .height(30)
            .fontSize(17)
            .borderRadius(10)
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