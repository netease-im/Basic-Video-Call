import router from '@ohos.router';
import Delegate from '../../common/Delegate';
import ChatPresenter from '../../common/Presenter'
import { NERtcSDK, NERtcConstants, NERtc, NERtcVideoView} from 'sdk/Index';
import * as model from '../../common/Model';
import prompt from '@ohos.promptAction';

@Entry
@Component
struct VideoSettings {

  TAG: string = "VideoSettings";

  @State channel_name: string = "";

  @State local_user?: model.User = undefined;

  @State remote_user_1?: model.User = undefined;
  @State remote_user_2?: model.User = undefined;
  @State remote_user_3?: model.User = undefined;
  @State remote_user_4?: model.User = undefined;
  remote_user_list: bigint[] = [];

  @State capture_config: NERtcConstants.NERtcCameraCaptureConfiguration = new NERtcConstants.NERtcCameraCaptureConfiguration();
  @State encode_config: NERtcConstants.NERtcVideoEncodeConfiguration = new NERtcConstants.NERtcVideoEncodeConfiguration();

  delegate: Delegate = {
    onJoin: (result: number, channelId: bigint): void => {
      prompt.showToast({ message: 'Join channel result:' + result, duration: 2000 });
    },
    onLeave: (result: number): void =>{

    },
    onUserJoin:(uid: bigint): void => {
      if (this.isUserAlreadyExist(uid)) {
        return;
      }
      this.remote_user_list.push(uid);
      if (this.remote_user_1 == undefined) {
        this.remote_user_1 = { uid: uid };
        console.info(this.TAG, 'Create Remote User1.');
      } else if(this.remote_user_2 == undefined) {
        this.remote_user_2 = { uid: uid };
        console.info(this.TAG, 'Create Remote User2.');
      } else if(this.remote_user_3 == undefined) {
        this.remote_user_3 = { uid: uid };
        console.info(this.TAG, 'Create Remote User3.');
      } else if (this.remote_user_4 == undefined) {
        this.remote_user_4 = { uid: uid };
        console.info(this.TAG, 'Create Remote User4.');
      }
    },
    onUserLeave:(uid: bigint, reason: number): void => {
      if (this.isUserAlreadyExist(uid)) {
        return;
      }
      this.remote_user_list.splice(this.remote_user_list.indexOf(uid), 1);
      if (this.remote_user_1 && this.remote_user_1.uid === uid) {
        this.remote_user_1 = undefined;
      } else if (this.remote_user_2 && this.remote_user_2.uid === uid) {
        this.remote_user_2 = undefined;
      } else if (this.remote_user_3 && this.remote_user_3.uid === uid) {
        this.remote_user_3 = undefined;
      } else if (this.remote_user_4 && this.remote_user_4.uid === uid) {
        this.remote_user_4 = undefined;
      }
    },
  }

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

  isUserAlreadyExist(uid: bigint): boolean {
    let is_exist: boolean = false;
    for (let i = 0; i < this.remote_user_list.length; i++) {
      if (this.remote_user_list[i] == uid) {
        is_exist = true;
        break;
      }
    }
    return is_exist;
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
    let params: object = router.getParams();
    let login_param: model.LoginInfo = params["login_param"];
    this.channel_name = login_param.cname;
    this.local_user = { uid: BigInt(login_param?.uid ?? 0) };
    this.capture_config = params["video_capture_config"];
    this.encode_config = params["video_encode_config"];

    ChatPresenter.getInstance().setDelegate(this.delegate);
    ChatPresenter.getInstance().init(getContext());
    ChatPresenter.getInstance().enableVideo(true);
    ChatPresenter.getInstance().enableAudio(true);
    ChatPresenter.getInstance().setCameraCaptureConfig(this.capture_config);
    ChatPresenter.getInstance().setLocalVideoConfig(this.encode_config);
    ChatPresenter.getInstance().join(login_param);
  }

  onPageHide(): void {
    ChatPresenter.getInstance().leave();
    ChatPresenter.getInstance().removeDelegate(this.delegate);
    ChatPresenter.getInstance().release();
  }

  build() {
    Row() {
      Column() {
        Text('房间号: ' + this.channel_name)
          .width('100%')
          .fontSize(20)
          .textAlign(TextAlign.Center)
          .margin({ top: "20vp", bottom: "20vp" })
        Row() {
          if (this.local_user) {
            NERtcVideoView({
              canvasId: String(this.local_user?.uid),
              onLoad: (() => {
                console.info(this.TAG, `User: ${this.local_user?.uid} surface create.`)
                if (this.local_user) {
                  ChatPresenter.getInstance().attach(this.local_user);
                }
              }),
              onDestroy: (() => {
                console.info(this.TAG, `User: ${this.local_user?.uid} surface release.`)
              })
            }).width('100%').height('100%')
          }
        }
        .width('100%')
        .height('30%')
        Row() {
          if (this.remote_user_1) {
            NERtcVideoView({
              canvasId: String(this.remote_user_1.uid),
              onLoad: (() => {
                if (this.remote_user_1) {
                  console.info(this.TAG, `User: ${String(this.remote_user_1?.uid)} surface create.`)
                  ChatPresenter.getInstance().attach(this.remote_user_1)
                }
              }),
              onDestroy: (() => {
                if (this.remote_user_1) {
                  console.info(this.TAG, `User: ${String(this.remote_user_1?.uid)} surface release.`)
                }
              })
            }).width('25%').height('100%')
          } else {
            Image($r('app.media.common_user_portrait'))
              .width("25%")
              .objectFit(ImageFit.Contain).margin(15)
              .margin({ top: "10vp", bottom: "40vp" })
          }
          if (this.remote_user_2) {
            NERtcVideoView({
              canvasId: String(this.remote_user_2.uid),
              onLoad: (() => {
                if (this.remote_user_2) {
                  console.info(this.TAG, `User: ${String(this.remote_user_2?.uid)} surface create.`)
                  ChatPresenter.getInstance().attach(this.remote_user_2)
                }
              }),
              onDestroy: (() => {
                if (this.remote_user_2) {
                  console.info(this.TAG, `User: ${String(this.remote_user_2?.uid)} surface release.`)
                }
              })
            }).width('25%').height('100%')
          } else {
            Image($r('app.media.common_user_portrait'))
              .width("25%")
              .objectFit(ImageFit.Contain).margin(15)
              .margin({ top: "10vp", bottom: "40vp" })
          }
          if (this.remote_user_3) {
            NERtcVideoView({
              canvasId: String(this.remote_user_3.uid),
              onLoad: (() => {
                if (this.remote_user_3) {
                  console.info(this.TAG, `User: ${String(this.remote_user_3?.uid)} surface create.`)
                  ChatPresenter.getInstance().attach(this.remote_user_3)
                }
              }),
              onDestroy: (() => {
                if (this.remote_user_3) {
                  console.info(this.TAG, `User: ${String(this.remote_user_3?.uid)} surface release.`)
                }
              })
            }).width('25%').height('100%')
          } else {
            Image($r('app.media.common_user_portrait'))
              .width("25%")
              .objectFit(ImageFit.Contain).margin(15)
              .margin({ top: "10vp", bottom: "40vp" })
          }
          if (this.remote_user_4) {
            NERtcVideoView({
              canvasId: String(this.remote_user_4.uid),
              onLoad: (() => {
                if (this.remote_user_4) {
                  console.info(this.TAG, `User: ${String(this.remote_user_4?.uid)} surface create.`)
                  ChatPresenter.getInstance().attach(this.remote_user_4)
                }
              }),
              onDestroy: (() => {
                if (this.remote_user_4) {
                  console.info(this.TAG, `User: ${String(this.remote_user_4?.uid)} surface release.`)
                }
              })
            }).width('25%').height('100%')
          } else {
            Image($r('app.media.common_user_portrait'))
              .width("25%")
              .objectFit(ImageFit.Contain).margin(15)
              .margin({ top: "10vp", bottom: "40vp" })
          }
        }
        .width('100%')
        .height('20%')
        .justifyContent(FlexAlign.SpaceBetween)
        Flex({ direction: FlexDirection.Column }) {
          List() {
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
            Button("修改视频编码配置", { type: ButtonType.Normal, stateEffect: true })
              .onClick(() => {
                ChatPresenter.getInstance().setLocalVideoConfig(this.encode_config);
              })
              .width('60%')
              .height(60)

              .borderRadius(10)
          }.justifyContent(FlexAlign.Center).width('100%').margin({ top: 20 }).height(80)
        }
        .width('100%')
        .height('40%')
      }
      .width('100%')
      .height('100%')
    }
    .width('100%')
    .height('100%')
  }
}