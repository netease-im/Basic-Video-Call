import router from '@ohos.router';
import prompt from '@ohos.promptAction';
import { LoginInfo } from '../../common/Model'
import { NERtcSDK, NERtcConstants, NERtc } from 'sdk/Index';

@Entry
@Component
struct VideoSettingsEntry {

  TAG: string = "VideoSettingsEntry";

  @State cname: string = "192732";
  @State uid: string = "";

  @State capture_config: NERtcConstants.NERtcCameraCaptureConfiguration = new NERtcConstants.NERtcCameraCaptureConfiguration();
  @State encode_config: NERtcConstants.NERtcVideoEncodeConfiguration = new NERtcConstants.NERtcVideoEncodeConfiguration();

  @Builder generateGroupHeader(text: string) {
    Text(text)
      .fontSize(30)
      .backgroundColor('#fff1f3f5')
      .width('100%')
      .padding(5)
  }

  @Builder generateItemHeader(text: string) {
    Text(text)
      .fontSize(20)
      .fontColor('#FF7E8383')
  }

  queryDisplayTextWithProfile(profile: NERtcConstants.NERtcVideoProfileType): string {
    switch (profile) {
      case NERtcConstants.NERtcVideoProfileType.kNERtcVideoProfileLowest: return "lowest";
      case NERtcConstants.NERtcVideoProfileType.kNERtcVideoProfileLow: return "low";
      case NERtcConstants.NERtcVideoProfileType.kNERtcVideoProfileStandard: return "standard";
      case NERtcConstants.NERtcVideoProfileType.kNERtcVideoProfileHD720P: return "720p";
      default: break;
    }
    return "unknown";
  }

  queryDisplayTextWithFramerate(framerate: NERtcConstants.NERtcVideoFrameRate): string {
    switch (framerate) {
      case NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFpsDefault: return "default";
      case NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps7: return "fps-7";
      case NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps10: return "fps-10";
      case NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps15: return "fps-15";
      case NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps24: return "fps-24";
      case NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps30: return "fps-30";
      default: break;
    }
    return "unknown";
  }

  queryItemIndexWithFramerate(framerate: NERtcConstants.NERtcVideoFrameRate): number {
    switch (framerate) {
      case NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFpsDefault: return 0;
      case NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps7: return 1;
      case NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps10: return 2;
      case NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps15: return 3;
      case NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps24: return 4;
      case NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps30: return 5;
      default: break;
    }
    return -1;
  }

  queryFramerateWithItemIndex(index: number): NERtcConstants.NERtcVideoFrameRate {
    switch (index) {
      case 0: return NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFpsDefault;
      case 1: return NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps7;
      case 2: return NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps10;
      case 3: return NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps15;
      case 4: return NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps24;
      case 5: return NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps30;
      default: break;
    }
    return NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFpsDefault;
  }

  queryDisplayTextWithCropMode(mode: NERtcConstants.NERtcVideoCropMode): string {
    switch (mode) {
      case NERtcConstants.NERtcVideoCropMode.kNERtcVideoCropDefault: return "default";
      case NERtcConstants.NERtcVideoCropMode.kNERtcVideoCropMode16_9: return "16:9";
      case NERtcConstants.NERtcVideoCropMode.kNERtcVideoCropMode4_3: return "4:3";
      case NERtcConstants.NERtcVideoCropMode.kNERtcVideoCropMode1_1: return "1:1";
      default: break;
    }
    return "unknown";
  }

  queryDisplayTextWithDegradationPreference(preference: NERtcConstants.NERtcDegradationPreference): string {
    switch (preference) {
      case NERtcConstants.NERtcDegradationPreference.kNERtcDegradationDefault: return "default";
      case NERtcConstants.NERtcDegradationPreference.kNERtcDegradationMaintainFramerate: return "maintainFramerate";
      case NERtcConstants.NERtcDegradationPreference.kNERtcDegradationMaintainQuality: return "maintainQuality";
      case NERtcConstants.NERtcDegradationPreference.kNERtcDegradationBalanced: return "balanced";
      default: break;
    }
    return "unknown";
  }

  queryDisplayTextWithMirrorMode(mode: NERtcConstants.NERtcVideoMirrorMode): string {
    switch (mode) {
      case NERtcConstants.NERtcVideoMirrorMode.kNERtcVideoMirrorModeAuto: return "auto";
      case NERtcConstants.NERtcVideoMirrorMode.kNERtcVideoMirrorModeEnabled: return "enabled";
      case NERtcConstants.NERtcVideoMirrorMode.kNERtcVideoMirrorModeDisabled: return "disabled";
      default: break;
    }
    return "unknown";
  }

  queryDisplayTextWithOrientationMode(mode: NERtcConstants.NERtcVideoOutputOrientationMode): string {
    switch (mode) {
      case NERtcConstants.NERtcVideoOutputOrientationMode.kNERtcVideoOutputOrientationModeAdaptative: return "adaptative";
      case NERtcConstants.NERtcVideoOutputOrientationMode.kNERtcVideoOutputOrientationModeFixedLandscape: return "landscape";
      case NERtcConstants.NERtcVideoOutputOrientationMode.kNERtcVideoOutputOrientationModeFixedPortrait: return "portrait";
      default: break;
    }
    return "unknown";
  }

  onPageShow(): void {
    this.uid = Math.floor(Math.random() * 100000).toString();
  }

  build() {
    Row() {
      Column() {
        Flex({ direction: FlexDirection.Column }) {
          List() {
            ListItemGroup({header: this.generateGroupHeader("房间参数")}) {
              ListItem() {
                this.generateItemHeader("房间名称")
              }
              ListItem() {
                TextInput({ placeholder: "请输入房间名称", text: this.cname })
                  .type(InputType.Normal)
                  .onChange((value: string) => {
                    this.cname = value;
                  })
                  .padding(10)
                  .margin(10)
                  .copyOption(CopyOptions.LocalDevice)
              }
              ListItem() {
                this.generateItemHeader("用户ID")
              }
              ListItem() {
                TextInput({ placeholder: "请输入用户id", text: this.uid })
                  .type(InputType.Number)
                  .onChange((value: string) => {
                    this.uid = value;
                  })
                  .padding(10)
                  .margin(10)
                  .copyOption(CopyOptions.LocalDevice)
              }
            }

            ListItemGroup({header: this.generateGroupHeader("视频采集参数")}) {
              ListItem() {
                this.generateItemHeader("采集宽度")
              }
              ListItem() {
                TextInput({ placeholder: "请输入视频采集宽度", text: this.capture_config.width.toString() })
                  .type(InputType.Number)
                  .onChange((value: string) => {
                    this.capture_config.width = parseInt(value, 10);
                  })
                  .padding(10)
                  .margin(10)
                  .copyOption(CopyOptions.LocalDevice)
              }
              ListItem() {
                this.generateItemHeader("采集高度")
              }
              ListItem() {
                TextInput({ placeholder: "请输入视频采集高度", text: this.capture_config.height.toString() })
                  .type(InputType.Number)
                  .onChange((value: string) => {
                    this.capture_config.height = parseInt(value, 10);
                  })
                  .padding(10)
                  .margin(10)
                  .copyOption(CopyOptions.LocalDevice)
              }
            }

            ListItemGroup({header: this.generateGroupHeader("视频编码参数")}) {
              ListItem() {
                this.generateItemHeader("profile")
              }
              ListItem() {
                Select([{ value: this.queryDisplayTextWithProfile(NERtcConstants.NERtcVideoProfileType.kNERtcVideoProfileLowest) },
                  { value: this.queryDisplayTextWithProfile(NERtcConstants.NERtcVideoProfileType.kNERtcVideoProfileLow) },
                  { value: this.queryDisplayTextWithProfile(NERtcConstants.NERtcVideoProfileType.kNERtcVideoProfileStandard) },
                  { value: this.queryDisplayTextWithProfile(NERtcConstants.NERtcVideoProfileType.kNERtcVideoProfileHD720P) }])
                  .value(this.queryDisplayTextWithProfile(this.encode_config.maxProfile))
                  .selected(this.encode_config.maxProfile as number)
                  .space(12)
                  .margin({ left: 12 })
                  .onSelect((index: number, text?: string) => {
                    this.encode_config.maxProfile = index as NERtcConstants.NERtcVideoProfileType;
                  })
              }
              ListItem() {
                this.generateItemHeader("编码宽度")
              }
              ListItem() {
                TextInput({ placeholder: "请输入视频编码宽度", text: this.encode_config.width.toString() })
                  .type(InputType.Number)
                  .onChange((value: string) => {
                    this.encode_config.width = parseInt(value, 10);
                  })
                  .padding(10)
                  .margin(10)
                  .copyOption(CopyOptions.LocalDevice)
              }
              ListItem() {
                this.generateItemHeader("编码高度")
              }
              ListItem() {
                TextInput({ placeholder: "请输入视频编码高度", text: this.encode_config.height.toString() })
                  .type(InputType.Number)
                  .onChange((value: string) => {
                    this.encode_config.height = parseInt(value, 10);
                  })
                  .padding(10)
                  .margin(10)
                  .copyOption(CopyOptions.LocalDevice)
              }
              ListItem() {
                this.generateItemHeader("编码帧率")
              }
              ListItem() {
                Select([{ value: this.queryDisplayTextWithFramerate(NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFpsDefault) },
                  { value: this.queryDisplayTextWithFramerate(NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps7) },
                  { value: this.queryDisplayTextWithFramerate(NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps10) },
                  { value: this.queryDisplayTextWithFramerate(NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps15) },
                  { value: this.queryDisplayTextWithFramerate(NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps24) },
                  { value: this.queryDisplayTextWithFramerate(NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps30) }])
                  .value(this.queryDisplayTextWithFramerate(this.encode_config.framerate))
                  .selected(this.queryItemIndexWithFramerate(this.encode_config.framerate))
                  .space(12)
                  .margin({ left: 12 })
                  .onSelect((index: number, text?: string) => {
                    this.encode_config.framerate = this.queryFramerateWithItemIndex(index);
                  })
              }
              ListItem() {
                this.generateItemHeader("最小编码帧率")
              }
              ListItem() {
                TextInput({ placeholder: "请输入最小编码帧率", text: this.encode_config.minFramerate.toString() })
                  .type(InputType.Number)
                  .onChange((value: string) => {
                    this.encode_config.minFramerate = parseInt(value, 10);
                  })
                  .padding(10)
                  .margin(10)
                  .copyOption(CopyOptions.LocalDevice)
              }
              ListItem() {
                this.generateItemHeader("编码码率")
              }
              ListItem() {
                TextInput({ placeholder: "请输入编码码率", text: this.encode_config.bitrate.toString() })
                  .type(InputType.Number)
                  .onChange((value: string) => {
                    this.encode_config.bitrate = parseInt(value, 10);
                  })
                  .padding(10)
                  .margin(10)
                  .copyOption(CopyOptions.LocalDevice)
              }
              ListItem() {
                this.generateItemHeader("最小编码码率")
              }
              ListItem() {
                TextInput({ placeholder: "请输入最小编码码率", text: this.encode_config.minBitrate.toString() })
                  .type(InputType.Number)
                  .onChange((value: string) => {
                    this.encode_config.minBitrate = parseInt(value, 10);
                  })
                  .padding(10)
                  .margin(10)
                  .copyOption(CopyOptions.LocalDevice)
              }
              ListItem() {
                this.generateItemHeader("编码裁剪模式")
              }
              ListItem() {
                Select([{ value: this.queryDisplayTextWithCropMode(NERtcConstants.NERtcVideoCropMode.kNERtcVideoCropDefault) },
                  { value: this.queryDisplayTextWithCropMode(NERtcConstants.NERtcVideoCropMode.kNERtcVideoCropMode16_9) },
                  { value: this.queryDisplayTextWithCropMode(NERtcConstants.NERtcVideoCropMode.kNERtcVideoCropMode4_3) },
                  { value: this.queryDisplayTextWithCropMode(NERtcConstants.NERtcVideoCropMode.kNERtcVideoCropMode1_1) }])
                  .value(this.queryDisplayTextWithCropMode(this.encode_config.cropMode))
                  .selected(this.encode_config.cropMode as number)
                  .space(12)
                  .margin({ left: 12 })
                  .onSelect((index: number, text?: string) => {
                    this.encode_config.cropMode = index as NERtcConstants.NERtcVideoCropMode;
                  })
              }
              ListItem() {
                this.generateItemHeader("编码降级偏好")
              }
              ListItem() {
                Select([{ value: this.queryDisplayTextWithDegradationPreference(NERtcConstants.NERtcDegradationPreference.kNERtcDegradationDefault) },
                  { value: this.queryDisplayTextWithDegradationPreference(NERtcConstants.NERtcDegradationPreference.kNERtcDegradationMaintainFramerate) },
                  { value: this.queryDisplayTextWithDegradationPreference(NERtcConstants.NERtcDegradationPreference.kNERtcDegradationMaintainQuality) },
                  { value: this.queryDisplayTextWithDegradationPreference(NERtcConstants.NERtcDegradationPreference.kNERtcDegradationBalanced) }])
                  .value(this.queryDisplayTextWithDegradationPreference(this.encode_config.degradationPreference))
                  .selected(this.encode_config.degradationPreference as number)
                  .space(12)
                  .margin({ left: 12 })
                  .onSelect((index: number, text?: string) => {
                    this.encode_config.degradationPreference = index as NERtcConstants.NERtcDegradationPreference;
                  })
              }
              ListItem() {
                this.generateItemHeader("编码镜像模式")
              }
              ListItem() {
                Select([{ value: this.queryDisplayTextWithMirrorMode(NERtcConstants.NERtcVideoMirrorMode.kNERtcVideoMirrorModeAuto) },
                  { value: this.queryDisplayTextWithMirrorMode(NERtcConstants.NERtcVideoMirrorMode.kNERtcVideoMirrorModeEnabled) },
                  { value: this.queryDisplayTextWithMirrorMode(NERtcConstants.NERtcVideoMirrorMode.kNERtcVideoMirrorModeDisabled) }])
                  .value(this.queryDisplayTextWithMirrorMode(this.encode_config.mirrorMode))
                  .selected(this.encode_config.mirrorMode as number)
                  .space(12)
                  .margin({ left: 12 })
                  .onSelect((index: number, text?: string) => {
                    this.encode_config.mirrorMode = index as NERtcConstants.NERtcVideoMirrorMode;
                  })
              }
              ListItem() {
                this.generateItemHeader("编码方向")
              }
              ListItem() {
                Select([{ value: this.queryDisplayTextWithOrientationMode(NERtcConstants.NERtcVideoOutputOrientationMode.kNERtcVideoOutputOrientationModeAdaptative) },
                  { value: this.queryDisplayTextWithOrientationMode(NERtcConstants.NERtcVideoOutputOrientationMode.kNERtcVideoOutputOrientationModeFixedLandscape) },
                  { value: this.queryDisplayTextWithOrientationMode(NERtcConstants.NERtcVideoOutputOrientationMode.kNERtcVideoOutputOrientationModeFixedPortrait) }])
                  .value(this.queryDisplayTextWithOrientationMode(this.encode_config.orientationMode))
                  .selected(this.encode_config.orientationMode as number)
                  .space(12)
                  .margin({ left: 12 })
                  .onSelect((index: number, text?: string) => {
                    this.encode_config.orientationMode = index as NERtcConstants.NERtcVideoOutputOrientationMode;
                  })
              }
            }
          }.scrollBar(BarState.Auto).alignListItem(ListItemAlign.Center).margin({ top: 10 }).width('100%').height('100%')

          Row({ space: 35 }) {
            Button("进入房间", { type: ButtonType.Normal, stateEffect: true })
              .onClick(() => {
                this.pushVideoSettingsPage();
              })
              .width('60%')
              .height(60)
              
              .borderRadius(10)
          }.justifyContent(FlexAlign.Center).width('100%').margin({ top: 20 }).height(80)
        }
      }
      .width('100%')
      .height('100%')
      .justifyContent(FlexAlign.Start)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Start)
  }

  pushVideoSettingsPage(): void {
    if(this.cname === "") {
      prompt.showToast({ duration: 2000, message: "请输入房间号."})
      return
    }
    if(this.uid === "") {
      prompt.showToast({ duration: 2000, message: "请输入用户id."})
      return
    }

    let param: object = new Object();
    let login_param: LoginInfo = {
      cname: this.cname,
      uid: this.uid
    }

    param["login_param"] = login_param;
    param["video_capture_config"] = this.capture_config;
    param["video_encode_config"] = this.encode_config;

    router.pushUrl({ url: 'videoSettings/pages/VideoSettings',  params: param }, (err)=> {
      if(err) {
        console.error(`Invoke pushUrl failed, code is ${err.code}, message is ${err.message}`)
        return
      }
      console.info("Invoke pushUrl success.")
    })
  }



}