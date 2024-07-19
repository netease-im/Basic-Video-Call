import Delegate from '../common/Delegate';
import Presenter from '../common/Presenter';
import prompt from '@ohos.promptAction';
import AbilityAccessCtrl from '@ohos.abilityAccessCtrl';
import { LoadingDialog } from '@ohos.arkui.advanced.Dialog'
import Utils from '../common/Utils';
import config from '../common/Config'
import ChatPresenter from '../common/Presenter';
import { NERtcConstants } from '@nertc/nertc_sdk';
import router from '@ohos.router';
import * as model from '../common/Model'

@Entry
@Component
struct Index {

  @State message: string = 'NERtcSDK Sample';
  TAG: string = 'Sample_Index'
  login?: model.LoginInfo
  type: model.ModelType = model.ModelType.DEFAULT


  delegate: Delegate = {

    onJoin:(result: number, channelId: bigint): void => {
      console.info(this.TAG, 'onJoin result:' + result + ', channelId:' + channelId)
      prompt.showToast({ message: 'Join channel async result:' + result, duration: 2000 })
      this.joinRoomDialog.close()
      if(result === NERtcConstants.ErrorCode.NO_ERROR) {
        if(this.type === model.ModelType.VIDEO_CALL) {
          this.turnToOtherPages('pages/VideoCall', this.login)
        } else if(this.type === model.ModelType.LIVE_STREAM) {
          this.turnToOtherPages('pages/LiveStream', this.login)
        } else if(this.type == model.ModelType.SNAPSHOT_WATERMARK) {
          this.turnToOtherPages('pages/SnapshotWaterMark', this.login)
        }
      }
      this.type = model.ModelType.DEFAULT
    },

    onLeave:(result: number): void => {
      console.info(this.TAG, 'onLeave result:' + result)
      prompt.showToast({ message: 'Leave channel async result:' + result, duration: 2000 })
    }

  }

  joinRoomDialog: CustomDialogController = new CustomDialogController({
    builder: LoadingDialog({
      content: '正在加入房间'
    }),
    autoCancel: false,
    customStyle: true,
    alignment: DialogAlignment.Center
  })

  @Builder itemHead(text: string) {
    Text(text)
      .fontSize(30)
      .backgroundColor('#fff1f3f5')
      .width('100%')
      .padding(5)
  }

  aboutToAppear(): void {
    Presenter.getInstance().init(getContext(this))
  }

  onPageShow(): void {
    this.RequestPermission()
  }

  onPageHide(): void {
    Presenter.getInstance().removeDelegate(this.delegate)
  }

  aboutToDisappear(): void {
   Presenter.getInstance().release()
  }

  build() {
    Row() {
      Column() {

        Flex({ direction: FlexDirection.Column }) {

          Text(this.message)
            .fontSize(25)
            .fontWeight(FontWeight.Bold)
            .width('100%')
            .margin({ top: 22 , bottom: 10})
            .textAlign(TextAlign.Start)
            .padding(5)


          List({ space: 5 }) {

            ListItem() {
              Button('1v1音视频通话', { type: ButtonType.Normal, stateEffect: true})
                .onClick(()=> {
                  console.info(this.TAG, 'User click 1v1 chat.')
                  Presenter.getInstance().setDelegate(this.delegate)
                  this.type = model.ModelType.VIDEO_CALL
                  this.JoinRoom()
                })
                .width('80%').height(50).borderRadius(10)
            }

            ListItemGroup({ header: this.itemHead('基础功能') }) {
              ListItem() {
                Button('音频通话', { type: ButtonType.Normal, stateEffect: true})
                  .onClick(() => {
                    router.pushUrl({ url: 'audioCall/pages/AudioCallEntry',  params: null }, (err)=> {
                      if(err) {
                        console.error(`Invoke pushUrl failed, code is ${err.code}, message is ${err.message}`)
                        return
                      }
                      console.info("Invoke pushUrl success.")
                    })
                  }).width('80%').height(50).borderRadius(10)
              }
              ListItem() {
                Button('视频通话', { type: ButtonType.Normal, stateEffect: true})
                  .onClick(() => {
                    router.pushUrl({ url: 'videoCall/pages/VideoCallEntry',  params: null }, (err)=> {
                      if(err) {
                        console.error(`Invoke pushUrl failed, code is ${err.code}, message is ${err.message}`)
                        return
                      }
                      console.info("Invoke pushUrl success.")
                    })
                  }).width('80%').height(50).borderRadius(10)
              }
            }.divider({strokeWidth: 1, startMargin: 60, endMargin: 10, color: '#ffe9f0f0'})

            ListItemGroup({ header: this.itemHead('进阶功能') }) {

              ListItem() {
                Button('通话前网络检测', { type: ButtonType.Normal, stateEffect: true})
                  .onClick(() => {
                    router.pushUrl({ url: 'pages/NetworkProbe',  params: null }, (err)=> {
                      if(err) {
                        console.error(`Invoke pushUrl failed, code is ${err.code}, message is ${err.message}`)
                        return
                      }
                      console.info("Invoke pushUrl success.")
                    })
                  }).width('80%').height(50).borderRadius(10)
              }

              ListItem() {
                Button('旁路推流', { type: ButtonType.Normal, stateEffect: true})
                  .onClick(() => {
                    console.info(this.TAG, 'User click live stream.')
                    Presenter.getInstance().setDelegate(this.delegate)
                    this.type = model.ModelType.LIVE_STREAM
                    this.JoinRoom()
                  }).width('80%').height(50).borderRadius(10)
              }

              ListItem() {
                Button('设备管理', { type: ButtonType.Normal, stateEffect: true})
                  .onClick(() => {
                  }).width('80%').height(50).borderRadius(10)
              }

              ListItem() {
                Button('媒体流加密', { type: ButtonType.Normal, stateEffect: true})
                  .onClick(() => {
                  }).width('80%').height(50).borderRadius(10)
              }

              ListItem() {
                Button('截图和水印', { type: ButtonType.Normal, stateEffect: true})
                  .onClick(() => {
                    console.info(this.TAG, 'User click snapshot and water mark.')
                    Presenter.getInstance().setDelegate(this.delegate)
                    this.type = model.ModelType.SNAPSHOT_WATERMARK
                    this.JoinRoom()
                  }).width('80%').height(50).borderRadius(10)
              }

              ListItem() {
                Button('快速切换房间', { type: ButtonType.Normal, stateEffect: true})
                  .onClick(() => {
                  }).width('80%').height(50).borderRadius(10)
              }
            }.divider({strokeWidth: 1, startMargin: 60, endMargin: 10, color: '#ffe9f0f0'})


            ListItemGroup({ header: this.itemHead('音频') }) {

              ListItem() {
                Button('设置音质', { type: ButtonType.Normal, stateEffect: true})
                  .onClick(() => {
                    router.pushUrl({ url: 'pages/AudioConfig',  params: null }, (err)=> {
                      if(err) {
                        console.error(`Invoke pushUrl failed, code is ${err.code}, message is ${err.message}`)
                        return
                      }
                      console.info("Invoke pushUrl success.")
                    })
                  }).width('80%').height(50).borderRadius(10)
              }

              ListItem() {
                Button('伴音', { type: ButtonType.Normal, stateEffect: true})
                  .onClick(() => {
                    router.pushUrl({ url: 'pages/AudioMixing',  params: null }, (err)=> {
                      if(err) {
                        console.error(`Invoke pushUrl failed, code is ${err.code}, message is ${err.message}`)
                        return
                      }
                      console.info("Invoke pushUrl success.")
                    })
                  }).width('80%').height(50).borderRadius(10)
              }

              ListItem() {
                Button('音效', { type: ButtonType.Normal, stateEffect: true})
                  .onClick(() => {
                    router.pushUrl({ url: 'pages/AudioEffect',  params: null }, (err)=> {
                      if(err) {
                        console.error(`Invoke pushUrl failed, code is ${err.code}, message is ${err.message}`)
                        return
                      }
                      console.info("Invoke pushUrl success.")
                    })
                  }).width('80%').height(50).borderRadius(10)
              }

              ListItem() {
                Button('美声变声', { type: ButtonType.Normal, stateEffect: true})
                  .onClick(() => {
                    router.pushUrl({ url: 'pages/VoiceBeauty',  params: null }, (err)=> {
                      if(err) {
                        console.error(`Invoke pushUrl failed, code is ${err.code}, message is ${err.message}`)
                        return
                      }
                      console.info("Invoke pushUrl success.")
                    })
                  }).width('80%').height(50).borderRadius(10)
              }

              ListItem() {
                Button('自定义音频采集', { type: ButtonType.Normal, stateEffect: true})
                  .onClick(() => {
                    router.pushUrl({ url: 'pages/ExternalAudioInput',  params: null }, (err)=> {
                      if(err) {
                        console.error(`Invoke pushUrl failed, code is ${err.code}, message is ${err.message}`)
                        return
                      }
                      console.info("Invoke pushUrl success.")
                    })
                  }).width('80%').height(50).borderRadius(10)
              }

              ListItem() {
                Button('原始音频回调', { type: ButtonType.Normal, stateEffect: true})
                  .onClick(() => {
                  }).width('80%').height(50).borderRadius(10)
              }

              ListItem() {
                Button('音频主辅流', { type: ButtonType.Normal, stateEffect: true})
                  .onClick(() => {
                    router.pushUrl({ url: 'pages/MainAndSubStream',  params: null }, (err)=> {
                      if(err) {
                        console.error(`Invoke pushUrl failed, code is ${err.code}, message is ${err.message}`)
                        return
                      }
                      console.info("Invoke pushUrl success.")
                    })
                  }).width('80%').height(50).borderRadius(10)
              }

              ListItem() {
                Button('本地音频录制', { type: ButtonType.Normal, stateEffect: true})
                  .onClick(() => {
                  }).width('80%').height(50).borderRadius(10)
              }
            }.divider({strokeWidth: 1, startMargin: 60, endMargin: 10, color: '#ffe9f0f0'})


            ListItemGroup({ header: this.itemHead('视频') }) {

              ListItem() {
                Button('设置画质', { type: ButtonType.Normal, stateEffect: true })
                  .onClick(() => {
                    router.pushUrl({ url: "videoconfig/pages/VideoProfileConfig" });
                  }).width('80%').height(50).borderRadius(10)
              }

              ListItem() {
                Button('自定义视频采集', { type: ButtonType.Normal, stateEffect: true})
                  .onClick(() => {
                    router.pushUrl({
                      url: "externalsource/pages/ExternalVideoSource"
                    });
                  }).width('80%').height(50).borderRadius(10)
              }

              ListItem() {
                Button('云信美颜', { type: ButtonType.Normal, stateEffect: true})
                  .onClick(() => {
                  }).width('80%').height(50).borderRadius(10)
              }

              ListItem() {
                Button('屏幕共享主辅流', { type: ButtonType.Normal, stateEffect: true})
                  .onClick(() => {
                  }).width('80%').height(50).borderRadius(10)
              }

              ListItem() {
                Button('虚拟背景', { type: ButtonType.Normal, stateEffect: true})
                  .onClick(() => {
                  }).width('80%').height(50).borderRadius(10)
              }

              ListItem() {
                Button('原始视频回调', { type: ButtonType.Normal, stateEffect: true})
                  .onClick(() => {
                  }).width('80%').height(50).borderRadius(10)
              }

              ListItem() {
                Button('超分', { type: ButtonType.Normal, stateEffect: true})
                  .onClick(() => {
                  }).width('80%').height(50).borderRadius(10)
              }

              ListItem() {
                Button('视频主辅流', { type: ButtonType.Normal, stateEffect: true})
                  .onClick(() => {
                    router.pushUrl({ url: 'pages/MainAndSubStreamVideo',  params: null }, (err)=> {
                      if(err) {
                        console.error(`Invoke pushUrl failed, code is ${err.code}, message is ${err.message}`)
                        return
                      }
                      console.info("Invoke pushUrl success.")
                    })
                  }).width('80%').height(50).borderRadius(10)
              }

              ListItem() {
                Button('SEI', { type: ButtonType.Normal, stateEffect: true})
                  .onClick(() => {
                  }).width('80%').height(50).borderRadius(10)
              }

              ListItem() {
                Button('常用视频配置', { type: ButtonType.Normal, stateEffect: true})
                  .onClick(() => {
                    router.pushUrl({ url: 'videoSettings/pages/VideoSettingsEntry',  params: null }, (err)=> {
                      if(err) {
                        console.error(`Invoke pushUrl failed, code is ${err.code}, message is ${err.message}`)
                        return
                      }
                      console.info("Invoke pushUrl success.")
                    });
                  }).width('80%').height(50).borderRadius(10)
              }

              ListItem() {
                Button('外部适配分享', { type: ButtonType.Normal, stateEffect: true})
                  .onClick(() => {
                  }).width('80%').height(50).borderRadius(10)
              }
            }.divider({strokeWidth: 1, startMargin: 60, endMargin: 10, color: '#ffe9f0f0'})

          }.scrollBar(BarState.Auto).alignListItem(ListItemAlign.Center).margin({ top: 10 }).width('100%').height('100%')

        }
      }
      .width('100%')
    }
    .height('100%')
  }


  async JoinRoom() {

    this.joinRoomDialog.open()
    let uid = Utils.getRandomNumber(1, 100000)
    console.info(this.TAG, 'uid: ' + uid)

    let login: model.LoginInfo = { cname: config.CHANNEL_NAME, uid: String(uid) }
    this.login = login

    let result = ChatPresenter.getInstance().join(login)
    if(result !== NERtcConstants.ErrorCode.NO_ERROR) {
      this.joinRoomDialog.close()
      prompt.showToast({ message: 'Join Channel failed, result: ' + result, duration: 2000 })
    }
  }

  async RequestPermission() {
    let atManager = AbilityAccessCtrl.createAtManager();
    let context = getContext(this);
    try {
      atManager.requestPermissionsFromUser(
        context,
        ["ohos.permission.MICROPHONE", "ohos.permission.CAMERA"],
        (err, data) =>
        {
          if(err) {
            prompt.showToast({message: `请求权限失败: ${err}`})
            return
          }
          let micGrant: boolean = data.authResults[0] === AbilityAccessCtrl.GrantStatus.PERMISSION_GRANTED;
          let cameraGrant: boolean = data.authResults[1] === AbilityAccessCtrl.GrantStatus.PERMISSION_GRANTED;

          if(!micGrant) {
            prompt.showToast({ message: `麦克风权限未授予` })
          }
          if(!cameraGrant) {
            prompt.showToast( {message: `摄像头权限未授予` })
          }
        })
    } catch(err) {
      prompt.showToast({ message: `请求权限失败: ${JSON.stringify(err)}`})
    }
  }

  turnToOtherPages(page: string, param?: object): void {

    router.pushUrl(
      { url: page, params: param },
      (err)=> {
        if(err)
          console.error(`Turn page:${page} failed, code is ${err.code}, message is ${err.message}`)
      })
  }

}