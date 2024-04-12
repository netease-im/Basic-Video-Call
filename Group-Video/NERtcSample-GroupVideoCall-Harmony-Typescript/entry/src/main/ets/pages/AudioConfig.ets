import Delegate from '../common/Delegate';
import prompt from '@ohos.promptAction';
import ChatPresenter, { remoteUsers } from '../common/Presenter';
import router from '@ohos.router';
import { LoginInfo } from '../common/Model'

@Entry
@Component
export struct AudioConfig {
  @State remoteList: bigint[] = [BigInt(0), BigInt(0), BigInt(0), BigInt(0), BigInt(0), BigInt(0)]
  @State btnProfile: boolean[] = [false, false, false, false, false, false]
  @State btnScene: boolean[] = [false, false, false]
  scenario: number = 0
  profile: number = 0
  TAG: string = "AudioConfig"
  @State login: LoginInfo = {
    cname: "1392",
    uid: Math.floor(Math.random() * 10000).toString()
  };
  @State cname: string = ""
  @State uid: string = ""
  onPageShow() {
    console.info(this.TAG, '=== CallPage show ===')
    ChatPresenter.getInstance().setDelegate(this.delegate)
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
    ChatPresenter.getInstance().enableAudio(true)
  }

  joinRoom() {
    ChatPresenter.getInstance().join(this.login)
  }

  public delegate: Delegate = {
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
  changeProfileBtnState(idx: number){
    for(let i = 0;i < this.btnProfile.length;i++){
        if(i != idx){
          this.btnProfile[i] = false;
        }
    }
    this.btnProfile[idx] = true;
  }
  changeSceneBtnState(idx: number){
    for(let i = 0;i < this.btnScene.length;i++){
      if(i != idx){
        this.btnScene[i] = false;
      }
    }
    this.btnScene[idx] = true;
  }
  build() {
    Row() {
      Column() {
        Text('音频质量')
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
        Row() {
          Text('音频质量')
            .width('100%')
            .fontSize(20)
            .textAlign(TextAlign.Start)
            .margin({ top: "20vp", bottom: "20vp" })
        }
        Row() {
          Toggle({ type: ToggleType.Button, isOn: this.btnProfile[0]}) {
            Text('默认')
              .fontColor('#182431')
              .fontSize(12)
          }.width(100)
          .onChange((isOn: boolean) => {
            if(isOn) {
              this.changeProfileBtnState(0);
              this.profile = 0
              ChatPresenter.getInstance().setAudioProfile(this.profile, this.scenario);
            }
          })
          Toggle({ type: ToggleType.Button, isOn: this.btnProfile[1] }) {
            Text('普通')
              .fontColor('#182431')
              .fontSize(12)
          }.width(100)
          .onChange((isOn: boolean) => {
            if(isOn) {
              this.changeProfileBtnState(1);
              this.profile = 1
              ChatPresenter.getInstance().setAudioProfile(this.profile, this.scenario);
            }
          })
          Toggle({ type: ToggleType.Button, isOn: this.btnProfile[2] }) {
            Text('中等')
              .fontColor('#182431')
              .fontSize(12)
          }.width(100)
          .onChange((isOn: boolean) => {
            if(isOn) {
              this.changeProfileBtnState(2);
              this.profile = 3
              ChatPresenter.getInstance().setAudioProfile(this.profile, this.scenario);
            }
          })
          Toggle({ type: ToggleType.Button, isOn: this.btnProfile[3] }) {
            Text('高质量')
              .fontColor('#182431')
              .fontSize(12)
          }.width(100)
          .onChange((isOn: boolean) => {
            if(isOn) {
              this.changeProfileBtnState(3);
              this.profile = 5
              ChatPresenter.getInstance().setAudioProfile(this.profile, this.scenario);
            }
          })
        }
        Row() {
          Toggle({ type: ToggleType.Button, isOn: this.btnProfile[4] }) {
            Text('中等质量立体音')
              .fontColor('#182431')
              .fontSize(12)
          }.width("50%")
          .onChange((isOn: boolean) => {
            if(isOn) {
              this.changeProfileBtnState(4);
              this.profile = 4
              ChatPresenter.getInstance().setAudioProfile(this.profile, this.scenario);
            }
          })
          Toggle({ type: ToggleType.Button, isOn: this.btnProfile[5] }) {
            Text('高质量立体音')
              .fontColor('#182431')
              .fontSize(12)
          }.width("50%")
          .onChange((isOn: boolean) => {
            if(isOn) {
              this.changeProfileBtnState(5);
              this.profile = 6
              ChatPresenter.getInstance().setAudioProfile(this.profile, this.scenario);
            }
          })
        }
        .justifyContent(FlexAlign.Start)
        Row() {
          Text('音频模式')
            .width('100%')
            .fontSize(20)
            .textAlign(TextAlign.Start)
            .margin({ top: "20vp", bottom: "20vp" })
        }
        Row() {
          Toggle({ type: ToggleType.Button, isOn: this.btnScene[0]}) {
            Text('默认')
              .fontColor('#182431')
              .fontSize(12)
          }.width(100)
          .onChange((isOn: boolean) => {
            if(isOn) {
              this.changeSceneBtnState(0);
              this.scenario = 0
              ChatPresenter.getInstance().setAudioProfile(this.profile, this.scenario);
            }
          })
          Toggle({ type: ToggleType.Button, isOn: this.btnScene[1]}) {
            Text('语音')
              .fontColor('#182431')
              .fontSize(12)
          }.width(100)
          .onChange((isOn: boolean) => {
            if(isOn) {
              this.changeSceneBtnState(1);
              this.scenario = 1
              ChatPresenter.getInstance().setAudioProfile(this.profile, this.scenario);
            }
          })
          Toggle({ type: ToggleType.Button, isOn: this.btnScene[2] }) {
            Text('音乐')
              .fontColor('#182431')
              .fontSize(12)
          }.width(100)
          .onChange((isOn: boolean) => {
            if(isOn) {
              this.changeSceneBtnState(2);
              this.scenario = 2
              ChatPresenter.getInstance().setAudioProfile(this.profile, this.scenario);
            }
          })
        }
        .margin({bottom: "40vp" })
        .width('100%')
        .justifyContent(FlexAlign.Start)
      }
      .width('100%')
      .height('100%')
      .justifyContent(FlexAlign.SpaceBetween)
    }
    .width('100%')
    .height('100%')
  }
}