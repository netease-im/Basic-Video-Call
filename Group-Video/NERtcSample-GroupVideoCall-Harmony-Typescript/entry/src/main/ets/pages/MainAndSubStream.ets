import Delegate from '../common/Delegate';
import prompt from '@ohos.promptAction';
import ChatPresenter from '../common/Presenter';
import AudioCapturerHelper from '../utils/AudioCapturerHelper';
import { LoginInfo } from '../common/Model'


let mCapturer: AudioCapturerHelper = new AudioCapturerHelper();

@Entry
@Component
export struct MainAndSubStream {
  @State remoteList: bigint[] = [BigInt(0), BigInt(0), BigInt(0), BigInt(0), BigInt(0), BigInt(0)]
  @State btnAudioCapturer: boolean[] = [false, false]
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

  async pushExternalCaptureAudioFrame(data: ArrayBuffer) {

    let sampleRate: number = 44100;
    let channels: number = 2;
    let samplesPerChannel :number = data.byteLength / channels / 2;
    let lastSyncTimestamp: bigint = BigInt(0);

    let uint8Array = new Uint8Array(data);
    ChatPresenter.getInstance().pushExternalAudioFrame(uint8Array, samplesPerChannel, sampleRate, channels, lastSyncTimestamp);
  }

  async pushExternalCaptureSubStreamAudioFrame(data: ArrayBuffer) {

    let sampleRate: number = 44100;
    let channels: number = 2;
    let samplesPerChannel :number = data.byteLength / channels / 2;
    let lastSyncTimestamp: bigint = BigInt(0);

    let uint8Array = new Uint8Array(data);
    ChatPresenter.getInstance().pushExternalSubAudioFrame(uint8Array, samplesPerChannel, sampleRate, channels, lastSyncTimestamp);
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
    for(let i = 0;i < this.btnAudioCapturer.length;i++){
        if(i != idx){
          this.btnAudioCapturer[i] = false;
        }
    }
    this.btnAudioCapturer[idx] = true;
  }

  async startAudioCapture(): Promise<void> {
    await mCapturer.init();
    await mCapturer.start((buffer: ArrayBuffer, size: number) => {
        this.pushExternalCaptureSubStreamAudioFrame(buffer)
    });
  }

  async stopAudioCapture(): Promise<void> {
    await mCapturer.stop();
    await mCapturer.release();
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
          Text('主副流切换')
            .width('100%')
            .fontSize(20)
            .textAlign(TextAlign.Start)
            .margin({ top: "20vp", bottom: "20vp" })
        }
        Row() {
          Toggle({ type: ToggleType.Button, isOn: this.btnAudioCapturer[0] }) {
            Text('打开主流')
              .fontColor('#182431')
              .fontSize(12)
          }.width("50%")
          .onChange((isOn: boolean) => {
            if(isOn) {
              this.changeProfileBtnState(0);
              ChatPresenter.getInstance().enableSubAudio(false);//关闭辅流
              ChatPresenter.getInstance().setExternalSubAudioSource(false, 44100, 2);
              ChatPresenter.getInstance().enableAudio(true);//打开主流
              this.stopAudioCapture();

            }
          })
          Toggle({ type: ToggleType.Button, isOn: this.btnAudioCapturer[1] }) {
            Text('打开辅流')
              .fontColor('#182431')
              .fontSize(12)
          }.width("50%")
          .onChange((isOn: boolean) => {
            if(isOn) {
              this.changeProfileBtnState(1);
              ChatPresenter.getInstance().enableAudio(false);//关闭主流
              ChatPresenter.getInstance().enableSubAudio(true);//打开辅流
              ChatPresenter.getInstance().setExternalSubAudioSource(true, 44100, 2);
              this.startAudioCapture();
            }
          })
        }
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