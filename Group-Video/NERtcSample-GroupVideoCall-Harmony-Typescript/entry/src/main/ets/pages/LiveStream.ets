import Delegate from '../common/Delegate';
import { LiveStreamEvent } from '../common/Model';
import ChatPresenter from '../common/Presenter';
import Prompt from '@system.prompt';
import { NERtcConstants } from 'sdk';
import router from '@ohos.router';
import * as model from '../common/Model';

@Entry
@Component
struct LiveStream {
  @State message: string = '旁路推流';

  TAG: string = 'LiveStream'
  scroller: Scroller = new Scroller()
  chat?: ChatPresenter

  delegate: Delegate = {
    onJoin:(result: number, channelId: bigint): void => {},
    onLeave:(result: number): void => {},
    onLiveStreamEvent:(state: LiveStreamEvent, taskId: string, url: string, errCode: number): void => {
      console.info(this.TAG, 'onLiveStreamEvent, state: ' + state + ", taskId: " + taskId + ", url: " + url + ", errCode: " + errCode)
    }
  }

  //推流基本信息, 这里为了演示 就添加一张背景图，SDK支持添加多张占位图
  taskId?: string
  url?: string
  serverRecordEnable: boolean = false
  liveMode: boolean = false
  layoutWidth?: number
  layoutHeight?: number
  layoutBgRGB?: string

  //占位图
  imgUrl?: string
  imgWidth: number = 0
  imgHeight: number = 0
  imgX: number = 0
  imgY: number = 0
  imgZ: number = 0

  //是否开启单路视频透传
  singleVideoPassThrough: boolean = false
  //音频发送码率
  audioBitrate?: number
  //音频采样率
  audioSampleRate?: number
  //音频编码格式: 0 - aac, 1 - HE-AAC
  audioCodecType?: number
  //音频通道数
  audioChannels?: number
  //当主播离线的时候 是否使用占位图?
  UsePlaceImage: boolean = false
  //额外的SEI信息
  extraSEI?: string

  //远端用户 - 790520
  remoteSubVideo: boolean = false
  remoteSubAudio: boolean = false
  remoteLayoutWidth: number = 0
  remoteLayoutHeight: number = 0
  remoteX: number = 0
  remoteY: number = 0
  remoteZOrder: number = 0
  remoteAdaption: number = 0

  login?: model.LoginInfo

  onPageShow(): void {
    console.info(this.TAG, '=== LiveStream Show ===')
    this.login = router.getParams() as model.LoginInfo

    this.chat = ChatPresenter.getInstance()
    this.chat.setDelegate(this.delegate)
  }

  onBackPress(): boolean | void {
    console.info(this.TAG, '=== LiveStream page backpress ===')
    this.chat?.leave()
    this.chat?.removeDelegate(this.delegate)
    this.chat?.enableVideo(false)
  }

  build() {
    Row() {
      Column() {
        Scroll(this.scroller){
          Flex({ direction: FlexDirection.Column }) {

            Text(this.message)
              .fontSize(25)
              .fontWeight(FontWeight.Bold)
              .margin({left: 10, top: 10})

            Divider().color(Color.Grey).margin({left: 10, right: 10, top: 5}).strokeWidth(1)

            Row() {
              Text('TaskID: ')
                .fontSize(20)
              TextInput({ placeholder: 'input task id.'})
                .type(InputType.Normal)
                .onChange(value => {
                  console.info(this.TAG, 'taskId: ' + value)
                  this.taskId = value
                })
            }.width('100%').margin({left: 10, top: 10})

            Row() {
              Text('StreamUrl: ')
                .fontSize(20)
              TextInput({placeholder: 'input stream url.'})
                .type(InputType.Normal)
                .onChange(value => {
                  console.info(this.TAG, 'streamUrl: ' + value)
                  this.url = value
                })
            }.width('100%').margin({left: 10, top: 5})

            Row() {

              Text('视频直播: ')
                .fontSize(20)

              Toggle({ type: ToggleType.Checkbox, isOn: false })
                .onChange(isOn => {
                  console.info(this.TAG, 'toggle is on: ' + isOn)
                  this.liveMode = isOn
                }).selectedColor(Color.Pink)

            }.width('100%').margin({left: 10, top: 5})

            Row() {

              Text('画布尺寸: ')
                .fontSize(20)
              Text('宽: ')
                .fontSize(20)
              TextInput().type(InputType.Number).onChange(value => {
                console.info(this.TAG, 'layout width: ' + value)
                try {
                  this.layoutWidth = Number.parseInt(value)
                } catch (e) {
                  Prompt.showToast({message: JSON.stringify(e)})
                  this.layoutWidth = 0
                }
              }).width(80)
              Text('高: ')
                .fontSize(20).margin({left: 10})
              TextInput().type(InputType.Number).onChange(value => {
                console.info(this.TAG, 'height: ' + value)
                try {
                  this.layoutHeight = Number.parseInt(value)
                } catch (e) {
                  Prompt.showToast({message: JSON.stringify(e)})
                  this.layoutHeight = 0
                }
              }).width(80)

            }.width('100%').margin({left: 10, top: 5})

            Row() {
              Text('SEI信息: ').fontSize(20)
              TextInput().type(InputType.Normal).onChange(value => {
                console.info(this.TAG, 'Set sei info: ' + value)
                this.extraSEI = value
              })
            }.margin({ left: 10, top: 5})

            Row() {
              Text('背景设置')
                .fontSize(25).fontWeight(FontWeight.Bold)
            }.margin({ left: 10, top: 20})
            Divider().color(Color.Grey).margin({left: 10, right: 10, top: 5}).strokeWidth(1)

            Row() {
              Text('图片链接:')
                .fontSize(20)
              TextInput().type(InputType.Normal).onChange(value => {
                console.info(this.TAG, 'Set Image url: ' + value)
                this.imgUrl = value
              }).margin({left: 5}).width('100%')
            }.margin({ left: 10, top: 20})

            Row() {
              Text('width: ').fontSize(20)
              TextInput().type(InputType.Number).onChange(value => {
                console.info(this.TAG, 'Set Image width: ' + value)
                try {
                  this.imgWidth = Number.parseInt(value)
                } catch (e) {
                  Prompt.showToast({message: JSON.stringify(e)})
                }
              }).width(100)
              Text('height: ').fontSize(20).margin({left: 10})
              TextInput().type(InputType.Number).onChange(value => {
                try {
                  this.imgHeight = Number.parseInt(value)
                } catch (e) {
                  Prompt.showToast({message: JSON.stringify(e)})
                }
              }).width(100)
            }.margin({ left: 10, top: 10})

            Row(){
              Text('X: ').fontSize(20)
              TextInput().type(InputType.Number).onChange(value => {
                try {
                  this.imgX = Number.parseInt(value)
                } catch (e) {
                  Prompt.showToast({message: JSON.stringify(e)})
                }
              }).width(80)
              Text('Y: ').fontSize(20).margin({left: 5})
              TextInput().type(InputType.Number).onChange(value => {
                try {
                  this.imgY = Number.parseInt(value)
                } catch (e) {
                  Prompt.showToast({message: JSON.stringify(e)})
                }
              }).width(80)
              Text('Z: ').fontSize(20).margin({left: 5})
              TextInput().type(InputType.Number).onChange(value => {
                try {
                  this.imgZ = Number.parseInt(value)
                } catch (e) {
                  Prompt.showToast({message: JSON.stringify(e)})
                }
              }).width(80)
            }.margin({ left: 10, top: 10})
            Row(){
              Text('背景颜色: ').fontSize(20)
              TextInput({placeholder: 'input rgb, eg: 60-67-83'}).type(InputType.Normal).onChange(value => {
                let rgb: string[] = value.split('-')
                if(rgb.length <= 0) {
                  Prompt.showToast({message: '设置背景颜色格式错误!'})
                } else {
                  this.layoutBgRGB = value
                }
              })
            }.margin({ left: 10, top: 10})
            Row() {
              Toggle({type: ToggleType.Checkbox , isOn: false}).selectedColor(Color.Pink).onChange(value => {
                console.info(this.TAG, '是否使用占位图: ' + value)
                this.UsePlaceImage = value
              })
              Text('使用占位图').margin({left: 5})
            }.margin({ left: 10, top: 10})
            Row() {
              Toggle({type: ToggleType.Checkbox , isOn: false}).selectedColor(Color.Pink).onChange(isOn => {
                console.info(this.TAG, '是否开启服务器录制: ' + isOn)
                this.serverRecordEnable = isOn
              })
              Text('开启录制').margin({left: 5})
            }.margin({ left: 10, top: 5})
            Row() {
              Toggle({type: ToggleType.Checkbox , isOn: false}).selectedColor(Color.Pink).onChange(isOn => {
                console.info(this.TAG, '是否开启单路透传开关：' + isOn)
                this.singleVideoPassThrough = isOn
              })
              Text('单路视频透传开关').margin({left: 5})
            }.margin({ left: 10, top: 5})

            Row() {
              Text('音频参数设置')
                .fontSize(25).fontWeight(FontWeight.Bold)
            }.margin({ left: 10, top: 20})

            Divider().color(Color.Grey).margin({left: 10, right: 10, top: 5}).strokeWidth(1)
            Row() {
              Text('码率(kbps): ').fontSize(20)
              TextInput({placeholder: '0表示默认码率'}).type(InputType.Number).onChange(value => {
                console.info(this.TAG, 'Set audio bitrate: ' + value)
                try {
                  this.audioBitrate = Number.parseInt(value)
                } catch (e) {
                  Prompt.showToast({message: JSON.stringify(e)})
                }
              })
            }.margin({ left: 10, top: 5})
            Row() {
              Text('音频采样率(Hz): ').fontSize(20)
              TextInput({placeholder: '只支持 32000 44100 48000'}).type(InputType.Number).onChange(value => {
                console.info(this.TAG, 'Set audio sampleRate: ' + value)
                try {
                  this.audioSampleRate = Number.parseInt(value)
                } catch (e) {
                  Prompt.showToast({message: JSON.stringify(e)})
                }
              })
            }.margin({ left: 10, top: 5})
            Row() {
              Text('音频规格: ').fontSize(20)
              TextInput({placeholder: '0: LC-ACC, 1: HE-AAC'}).type(InputType.Number).onChange(value => {
                console.info(this.TAG, 'Set audio codec type: ' + value)
                try {
                  this.audioCodecType = Number.parseInt(value)
                } catch (e) {
                  Prompt.showToast({message: JSON.stringify(e)})
                }
              })
            }.margin({ left: 10, top: 5})
            Row() {
              Text('声道数: ').fontSize(20)
              TextInput({placeholder: '默认:2'}).type(InputType.Number).onChange(value => {
                console.info(this.TAG, 'Set audio channels num: ' + value)
                try {
                  this.audioChannels = Number.parseInt(value)
                } catch (e) {
                  Prompt.showToast({message: JSON.stringify(e)})
                }
              })
            }.margin({ left: 10, top: 5})

            Divider().color(Color.Grey).margin({left: 10, right: 10, top: 5}).strokeWidth(1)

            Text('设置用户布局') //这里为了演示，只添加自己
              .fontSize(25).fontWeight(FontWeight.Bold).margin({ left: 10, top: 10})
            Divider().color(Color.Grey).margin({left: 10, right: 10, top: 5}).strokeWidth(1)

            Row(){
              Toggle({type: ToggleType.Checkbox }).onChange(value => {
                console.info(this.TAG, 'Set remote user sub video enabled: ' + value)
                this.remoteSubVideo = value
              })
              Text('订阅视频').fontSize(20).margin({left : 5})
            }.margin({ left: 10, top: 5})

            Row(){
              Toggle({type: ToggleType.Checkbox }).onChange(value => {
                console.info(this.TAG, 'Set remote user sub audio enabled: ' + value)
                this.remoteSubAudio = value
              })
              Text('订阅音频').fontSize(20).margin({left : 5})
            }.margin({ left: 10, top: 5})

            Row() {
              Text('画面尺寸').fontSize(20)
              Text('宽: ').fontSize(20).margin({ left: 5})
              TextInput().type(InputType.Number).onChange(value => {
                console.info(this.TAG, 'Set remote user width: ' + value)
                try {
                  this.remoteLayoutWidth = Number.parseInt(value)
                } catch (e) {
                  this.remoteLayoutWidth = 0
                }
              }).width(80)
              Text('高: ').fontSize(20).margin({left: 5})
              TextInput().type(InputType.Number).onChange(value => {
                console.info(this.TAG, 'Set remote user height: ' + value)
                try {
                  this.remoteLayoutHeight = Number.parseInt(value)
                } catch (e) {
                  this.remoteLayoutHeight = 0
                }
              }).width(80)
            }.margin({ left: 10, top: 5})

            Row() {
              Text('布局偏移').fontSize(20)
              Text('X: ').fontSize(20).margin({left: 5})
              TextInput().type(InputType.Number).onChange(value => {
                console.info(this.TAG, 'Set remote user X: ' + value)
                try {
                  this.remoteX = Number.parseInt(value)
                } catch (e) {
                  this.remoteX = 0
                }
              }).width(80)
              Text('Y: ').fontSize(20).margin({left: 5})
              TextInput().type(InputType.Number).onChange(value => {
                console.info(this.TAG, 'Set remote user Y: ' + value)
                try {
                  this.remoteY = Number.parseInt(value)
                } catch (e) {
                  this.remoteY = 0
                }
              }).width(80)
            }.margin({ left: 10, top: 5})

            Row() {
              Text('ZOrder: ').fontSize(20)
              TextInput().type(InputType.Number).onChange(value => {
                console.info(this.TAG, 'Set remote user zorder: ' + value)
                try {
                  this.remoteZOrder = Number.parseInt(value)
                } catch (e) {
                  this.remoteZOrder = 0
                }
              })
            }.margin({ left: 10, top: 5})


            Row(){
              Text('缩放').fontSize(20)
              Column() {
                Row() {
                  Radio({ value: 'radio1', group: 'radioGroup'}).checked(false).onChange(isOn => {
                    this.remoteAdaption = 0
                  })
                  Text('优先保证视频完整显示').fontSize(20).margin({left: 5})
                }
                Row() {
                  Radio({ value: 'radio2', group: 'radioGroup'}).checked(true).onChange(isOn => {
                    this.remoteAdaption = 1
                  })
                  Text('优先保证视窗被填满').fontSize(20).margin({left:5})
                }
              }.justifyContent(FlexAlign.Start)
            }.margin({ left: 10, top: 5})

            Divider().color(Color.Grey).margin({left: 10, right: 10, top: 5}).strokeWidth(1)
            Row() {
              Button('添加任务').width('30%').onClick(() => {

                console.info(this.TAG, '=== Add Live Stream Task ===')
                if(!this.isValid()) {
                  Prompt.showToast({message: '参数校验失败'})
                  return
                }

                let taskInfo = this.buildLiveStreamTask()
                this.chat?.addLiveStreamTask(taskInfo)

              }).type(ButtonType.Normal).borderRadius(5)

              Button('删除任务').width('30%').onClick(() => {
                if(this.taskId) {
                  this.chat?.removeLiveStreamTask(this.taskId)
                } else {
                  console.info(this.TAG, 'Live stream task is not exist.')
                }
              }).type(ButtonType.Normal).borderRadius(5).margin({left: 5})

            }.width('100%').margin({ left: 10, top: 10})
          }
        }.scrollable(ScrollDirection.Vertical)
        .scrollBar(BarState.Auto)
        .scrollBarColor(Color.Gray)
        .scrollBarWidth(5)
        .edgeEffect(EdgeEffect.Spring)
      }
      .width('100%')
    }
    .height('100%')
  }

  isValid(): boolean {
    if(this.taskId && this.url && this.layoutWidth && this.layoutHeight) {
      return true
    }
    return false
  }

  buildLiveStreamTask(): NERtcConstants.NERtcLiveStreamTaskInfo {

    let sampleRate = NERtcConstants.NERtcLiveStreamAudioSampleRate.kNERtcLiveStreamAudioSampleRate44100
    if(this.audioSampleRate) {
      if(this.audioSampleRate == 32000) {
        sampleRate = NERtcConstants.NERtcLiveStreamAudioSampleRate.kNERtcLiveStreamAudioSampleRate32000
      } else if(this.audioSampleRate == 44100) {
        sampleRate = NERtcConstants.NERtcLiveStreamAudioSampleRate.kNERtcLiveStreamAudioSampleRate44100
      } else if(this.audioSampleRate == 48000) {
        sampleRate = NERtcConstants.NERtcLiveStreamAudioSampleRate.kNERtcLiveStreamAudioSampleRate48000
      }
    }

    let audioCodec = NERtcConstants.NERtcLiveStreamAudioCodecProfile.kNERtcLiveStreamAudioCodecProfileLCAAC
    if(this.audioCodecType) {
      if(this.audioCodecType == 0) {
        audioCodec = NERtcConstants.NERtcLiveStreamAudioCodecProfile.kNERtcLiveStreamAudioCodecProfileLCAAC
      } else if(this.audioCodecType == 1) {
        audioCodec = NERtcConstants.NERtcLiveStreamAudioCodecProfile.kNERtcLiveStreamAudioCodecProfileHEAAC
      }
    }

    let config: NERtcConstants.NERtcLiveConfig = {
      interruptedPlaceImage: this.UsePlaceImage,
      singleVideoPassthrough: this.singleVideoPassThrough,
      audioBitrate: this.audioBitrate ?? 0,
      sampleRate: sampleRate,
      channels: this.audioChannels ?? 1,
      audioCodecProfile: audioCodec
    }

    let layout: NERtcConstants.NERtcLiveStreamLayout = new NERtcConstants.NERtcLiveStreamLayout()
    layout.width = this.layoutWidth!
    layout.height = this.layoutHeight!
    if(this.layoutBgRGB) {
      let rgb = this.layoutBgRGB.split('-')
      let color = this.argb(255, Number.parseInt(rgb[0]), Number.parseInt(rgb[1]), Number.parseInt(rgb[2]))
      layout.backgroundColor = color
    }

    //这里只是为了演示，只推自己
    let userTranscodingList: NERtcConstants.NERtcLiveStreamUserTranscoding[] = []
    let scaleMode = this.remoteAdaption == 0 ? NERtcConstants.NERtcLiveStreamVideoScaleMode.kNERtcLsModeVideoScaleFit : NERtcConstants.NERtcLiveStreamVideoScaleMode.kNERtcLsModeVideoScaleCropFill
    let userTranscoding: NERtcConstants.NERtcLiveStreamUserTranscoding = {
      uid: BigInt(this.login?.uid!),
      videoPush: this.remoteSubVideo,
      audioPush: this.remoteSubAudio,
      x: this.remoteX,
      y: this.remoteY,
      zOrder: this.remoteZOrder,
      width: this.remoteLayoutWidth,
      height: this.remoteLayoutHeight,
      adaption: scaleMode
    }
    userTranscodingList[0] = userTranscoding
    layout.users = userTranscodingList

    //这里只是为了演示，实际上SDK可支持多个背景图
    if(this.imgUrl) {
      let imageInfos: NERtcConstants.NERtcLiveStreamImageInfo[] = []
      let image: NERtcConstants.NERtcLiveStreamImageInfo = {
        url: this.imgUrl!,
        width: this.imgWidth,
        height: this.imgHeight,
        x: this.imgX,
        y: this.imgY,
        zOrder: this.imgZ
      }
      imageInfos[0] = image
      layout.bgImages = imageInfos
    }

    let taskInfo: NERtcConstants.NERtcLiveStreamTaskInfo = new NERtcConstants.NERtcLiveStreamTaskInfo
    taskInfo.taskID = this.taskId!
    taskInfo.streamURL = this.url!
    taskInfo.serverRecordEnabled = this.serverRecordEnable
    taskInfo.lsMode = this.liveMode ? NERtcConstants.NERtcLiveStreamMode.kNERtcLsModeVideo : NERtcConstants.NERtcLiveStreamMode.kNERtcLsModeAudio
    taskInfo.config = config
    taskInfo.layout = layout
    if(this.extraSEI) {
      taskInfo.extraInfo = this.extraSEI
    }
    return taskInfo
  }


  argb(alpha: number, red: number, green: number, blue: number): number {
    return (alpha << 24) | (red << 16) | (green << 8) | blue
  }

}