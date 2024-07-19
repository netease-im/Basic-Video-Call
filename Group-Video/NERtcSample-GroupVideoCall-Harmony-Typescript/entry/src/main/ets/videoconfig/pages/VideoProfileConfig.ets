import { NERtcSDK, NERtcConstants } from '@nertc/nertc_sdk';

import ChatPresenter from '../../common/Presenter';
import Utils from '../../common/Utils';
import * as model from '../../common/Model'
import config from '../../common/Config'
import Presenter from '../../common/Presenter';

const TAG: string = 'Sample_VideoProfileConfig'

@Component
@Entry
struct VideoProfileConfig {
  videoStreamType: number = NERtcConstants.NERtcVideoStreamType.kNERtcVideoStreamTypeMain;
  profileType: number = NERtcConstants.NERtcVideoProfileType.kNERtcVideoProfileStandard;
  customWidth: number = 0;
  customHeight: number = 0;
  frameRate: number = NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps15;
  isJoined: boolean = false;

  build() {
    Row() {
      Column() {
        Text("视频画质设置")
          .margin({ top: 24 });

        Row() {
          Text("视频类型：")
          Select([{ value: '视频主流' },
            { value: '视频辅流' }])
            .selected(0)
            .value('视频主流')
            .space(12)
            .margin({ left: 12 })
            .onSelect((index: number, text?: string) => {
              this.videoStreamType = text == "视频主流" ? NERtcConstants.NERtcVideoStreamType.kNERtcVideoStreamTypeMain : NERtcConstants.NERtcVideoStreamType.kNERtcVideoStreamTypeSub;
            });
        }
        .margin({ top: 24 });

        Row() {
          Text("分辨率档位：")
          Select([{ value: 'Lowest' },
            { value: 'Low' },
            { value: 'Standard' },
            { value: '720P' },
            { value: '1080P' }])
            .selected(this.profileType)
            .value('Standard')
            .space(12)
            .margin({ left: 12 })
            .onSelect((index: number, text?: string) => {
              this.profileType = index;
            });
        }
        .margin({ top: 24 });


        Row() {
          Text("自定义(高优先级)：")
          TextInput({ placeholder: "视频宽" })
            .onChange((value: string) => {
              this.customWidth = Number.parseInt(value);
            })
            .width(100)
            .type(InputType.Number)
            .margin({ left: 12 })

          TextInput({ placeholder: "视频高" })
            .onChange((value: string) => {
              this.customHeight = Number.parseInt(value);
            })
            .width(100)
            .type(InputType.Number)
            .margin({ left: 12 })
        }
        .margin({ top: 24 });


        Row() {
          Text("帧率档位：")
          Select([{ value: 'Default' },
            { value: 'Fps7' },
            { value: 'Fps10' },
            { value: 'Fps15' },
            { value: 'Fps24' },
            { value: 'Fps30' }])
            .selected(3)
            .value('Fps15')
            .space(12)
            .margin({ left: 12 })
            .onSelect((index: number, text?: string) => {
              switch (index) {
                case 0:
                  this.frameRate = NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFpsDefault;
                case 1:
                  this.frameRate = NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps7;
                  break;
                case 2:
                  this.frameRate = NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps10;
                  break;
                case 3:
                  this.frameRate = NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps15;
                  break;
                case 4:
                  this.frameRate = NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps24;
                  break;
                default:
                  this.frameRate = NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps30;
                  break;
              }

            });
        }
        .margin({ top: 12 });


        Button("设置好了").fontSize(16).onClick((event) => {
          this.joinRtcRoom();
        })
          .margin({ top: 12 });
      }
      .width('100%')
    }.width('100%')
  }

  joinRtcRoom(): void {

    if (this.isJoined) {
      console.info(TAG, "already joined room ")
      return;
    }
    console.info(TAG, "streamType: " + this.videoStreamType +
      " , profileType: " + this.profileType +
      " , customWidth: " + this.customWidth +
      " , customHeight: " + this.customHeight +
      " , frameRate: " + this.frameRate)

    // step 1 : 初始化sdk
    // NERtcSDK.getInstance().init()
    // Presenter.getInstance().init(getContext(this))


    //step 2: 设置video config
    let videoConfig: NERtcConstants.NERtcVideoEncodeConfiguration = {
      maxProfile: this.profileType,
      width: this.customWidth,
      height: this.customHeight,
      framerate: this.frameRate,
      minFramerate: 0,
      bitrate: 0,
      minBitrate: 0,
      cropMode: NERtcConstants.NERtcVideoCropMode.kNERtcVideoCropDefault,
      degradationPreference: NERtcConstants.NERtcDegradationPreference.kNERtcDegradationDefault,
      mirrorMode: NERtcConstants.NERtcVideoMirrorMode.kNERtcVideoMirrorModeAuto,
      orientationMode: NERtcConstants.NERtcVideoOutputOrientationMode.kNERtcVideoOutputOrientationModeAdaptative
    };
    NERtcSDK.getInstance().setLocalVideoConfig(videoConfig, this.videoStreamType);


    //step 3: 打开视频
    NERtcSDK.getInstance().enableLocalVideo(true, this.videoStreamType);

    //step 4: 设置本地画布
    // NERtcSDK.getInstance().setupLocalVideoCanvas();

    //step5: 入会
    // let uid = Utils.getRandomNumber(1, 100000)
    // let ret = NERtcSDK.getInstance().joinChannel('', config.CHANNEL_NAME, BigInt(uid))
    // if (ret == 0) {
    //   this.isJoined = true;
    // }
    // console.info(TAG, "uid: " + uid + " , cname:" + config.CHANNEL_NAME + " , ret: " + ret)
  }

  onPageHide(): void {
    if (this.isJoined) {
      NERtcSDK.getInstance().leaveChannel();
      this.isJoined = false;
    }
  }
}