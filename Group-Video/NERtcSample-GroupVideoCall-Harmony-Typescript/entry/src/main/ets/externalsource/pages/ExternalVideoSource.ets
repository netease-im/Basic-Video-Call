import fs from '@ohos.file.fs';
import fileIo from '@ohos.file.fs';
import config from '../../common/Config'
import Utils from '../../common/Utils';
import { NERtcSDK, NERtcConstants } from 'sdk/Index';
import prompt from '@ohos.promptAction';
import { BusinessError } from '@ohos.base';
import buffer from '@ohos.buffer';


const TAG: string = 'Sample_ExternalVideoSource'

@Entry
@Component
struct ExternalVideoSource {
  videoStreamType: number = NERtcConstants.NERtcVideoStreamType.kNERtcVideoStreamTypeMain;
  @State i420FilePath: string = "";
  i420Width: number = 1024;
  i420Height: number = 576;
  i420FrameRate: number = NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps15;
  isJoined: boolean = false;
  intervalTaskId: number = -1;
  yuvFile?: fileIo.File;
  fileReadOffset: number = 0;
  readFileCatchException = (err: BusinessError) => {
    console.error(TAG, "read file data failed with error message: " + err.message + ", error code: " + err.code);
  };

  build() {
    Row() {
      Column() {
        Text("自定义视频输入")
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

        TextInput({ placeholder: "I420 文件路径", text: this.i420FilePath })
          .onChange((value) => {
            if (value.length < 1) {
              return;
            }
            this.i420FilePath = value;
          })
          .margin({ top: 24 })
          .width("80%")
          .type(InputType.Normal)

        TextInput({ placeholder: "I420 视频宽：" + this.i420Width })
          .onChange((value) => {
            this.i420Width = Number.parseInt(value);
          })
          .margin({ top: 24 })
          .width("50%")
          .type(InputType.Number)

        TextInput({ placeholder: "I420 视频高：" + this.i420Height })
          .onChange((value) => {
            this.i420Height = Number.parseInt(value);
          })
          .margin({ top: 24 })
          .width("50%")
          .type(InputType.Number)

        Row() {
          Text("I420 帧率：")
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
                case 1:
                  this.i420FrameRate = NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps7;
                  break;
                case 2:
                  this.i420FrameRate = NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps10;
                  break;
                case 3:
                  this.i420FrameRate = NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps15;
                  break;
                case 4:
                  this.i420FrameRate = NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps24;
                  break;
                default:
                  this.i420FrameRate = NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps30;
                  break;
              }
            });
        }
        .margin({ top: 24 });

        Button("入会并发送自定义视频").fontSize(16).onClick((event) => {
          this.joinRtcRoom();
        })
          .margin({ top: 12 });
      }
      .width("100%")

    }.width("100%")
  }

  onPageShow(): void {
    this.checkRawYUVFile();
  }

  onPageHide(): void {
    if (this.isJoined) {
      NERtcSDK.getInstance().leaveChannel();
      this.isJoined = false;
    }

    if (this.intervalTaskId != -1) {
      clearInterval(this.intervalTaskId);
      console.info(TAG, "clearInterval succeed , id: " + this.intervalTaskId);
    }

    if (this.yuvFile) {
      fs.close(this.yuvFile).then(() => {
        console.info(TAG, "close file succeed");
      }).catch((err: BusinessError) => {
        console.error(TAG, "close file failed with error message: " + err.message + ", error code: " + err.code);
      });
    }
  }

  joinRtcRoom(): void {
    if (!this.checkUserSetting()) {
      return;
    }

    if (this.isJoined) {
      console.info(TAG, "already joined room ")
      return;
    }

    console.info(TAG, "streamType: " + this.videoStreamType +
      " , i420FilePath: " + this.i420FilePath +
      " , i420Width: " + this.i420Width +
      " , i420Height: " + this.i420Height +
      " , i420FrameRate: " + this.i420FrameRate)

    // step 1 : 初始化sdk
    // NERtcSDK.getInstance().init()
    // Presenter.getInstance().init(getContext(this))


    //step 2: 设置video config
    let videoConfig: NERtcConstants.NERtcVideoEncodeConfiguration = {
      maxProfile: NERtcConstants.NERtcVideoProfileType.kNERtcVideoProfileStandard,
      width: this.i420Width,
      height: this.i420Height,
      framerate: this.i420FrameRate,
      minFramerate: 0,
      bitrate: 0,
      minBitrate: 0,
      cropMode: NERtcConstants.NERtcVideoCropMode.kNERtcVideoCropDefault,
      degradationPreference: NERtcConstants.NERtcDegradationPreference.kNERtcDegradationDefault,
      mirrorMode: NERtcConstants.NERtcVideoMirrorMode.kNERtcVideoMirrorModeAuto,
      orientationMode: NERtcConstants.NERtcVideoOutputOrientationMode.kNERtcVideoOutputOrientationModeAdaptative
    };
    NERtcSDK.getInstance().setLocalVideoConfig(videoConfig, this.videoStreamType);

    //step 3: 打开外部输入开关
    NERtcSDK.getInstance().setExternalVideoSource(true, NERtcConstants.NERtcVideoStreamType.kNERtcVideoStreamTypeMain)

    //step 4: 打开视频
    NERtcSDK.getInstance().enableLocalVideo(true, this.videoStreamType);

    //step 5: 设置本地画布
    // NERtcSDK.getInstance().setupLocalVideoCanvas();


    //step6: 入会
    let uid = Utils.getRandomNumber(1, 100000)
    let ret = NERtcSDK.getInstance().joinChannel('', config.CHANNEL_NAME, BigInt(uid))
    if (ret == 0) {
      this.isJoined = true;
    }
    console.info(TAG, "uid: " + uid + " , cname:" + config.CHANNEL_NAME + " , ret: " + ret)

    if (ret == 0) {
      //按帧率持续push 外部视频数据
      this.startPushI420();
    }
  }

  async startPushI420() {
    this.yuvFile = fs.openSync(this.i420FilePath, fs.OpenMode.READ_ONLY);
    if (!this.yuvFile) {
      prompt.showToast({ message: "文件读取异常" });
      return;
    }
    console.info(TAG, "file fd: " + this.yuvFile.fd);
    let pushIntervalMs = 1000 / this.i420FrameRate;
    // i420 一帧数据 = w*h*1.5 ;
    let videoFrameLen = this.i420Width * this.i420Height * 3 / 2;

    let videoFrameBuffer = new ArrayBuffer(videoFrameLen);
    let transformMatrixArray: Float32Array = new Float32Array([0]);

    this.intervalTaskId = setInterval(() => {
      if (!this.yuvFile) {
        return;
      }
      fs.read(this.yuvFile.fd, videoFrameBuffer, { offset: this.fileReadOffset }).then((readLen: number) => {
        if (readLen != videoFrameLen) {
          this.fileReadOffset = 0;
          console.warn(TAG, "read file to the end so loop again , readLen:" + readLen);
          return;
        }
        this.fileReadOffset += readLen;
        let data: Uint8Array = new Uint8Array(videoFrameBuffer as ArrayBuffer);
        let videoFrame: NERtcConstants.NERtcVideoFrame = {
          width: this.i420Width,
          height: this.i420Height,
          rotation: NERtcConstants.NERtcVideoFrameRotation.kLiteSDKVideoFrameRotationType0,
          format: NERtcConstants.NERtcVideoFormat.I420,
          timeStamp: BigInt(0),
          data: data,
          strideY: 0,
          strideU: 0,
          strideV: 0,
          textureId: 0,
          transformMatrix: transformMatrixArray
        };
        NERtcSDK.getInstance().pushExternalVideoFrame(videoFrame, NERtcConstants.NERtcVideoStreamType.kNERtcVideoStreamTypeMain);
      })
        .catch(this.readFileCatchException);
    }, pushIntervalMs);
  }

  async checkRawYUVFile() {
    let dir: string = getContext(this).filesDir + "/media";
    this.i420FilePath = dir + "/1024_576.yuv"
    if (fs.accessSync(this.i420FilePath)) {
      console.info(TAG, "yuv test file is already exist path: " + this.i420FilePath);
      return;
    }
    fs.mkdirSync(dir);
    console.warn(TAG, 'yuv test file is not exist.')

    getContext(this).resourceManager.getRawFileContent("1024_576.yuv").then(data => {
      let writeLen = fs.createStreamSync(this.i420FilePath, 'w').writeSync(data.buffer)
      console.info(TAG, 'write 1024_576.yuv len: ' + writeLen + ", path: " + this.i420FilePath);
    }).catch((error: BusinessError) => {
      console.error(TAG, "checkRawYUVFile failed with error message: " + error.message + ", error code: " + error.code);
    });
  }

  checkUserSetting(): boolean {
    if (this.yuvFile) {
      prompt.showToast({ message: "已经开始push 数据了" });
      return false;
    }
    if (this.i420FilePath.length == 0 || this.i420Width < 64 || this.i420Height < 64 || this.i420FrameRate == 0) {
      prompt.showToast({ message: "参数设置异常" });
      console.error(TAG, "wrong param streamType: " + this.videoStreamType +
        " , i420FilePath: " + this.i420FilePath +
        " , i420Width: " + this.i420Width +
        " , i420Height: " + this.i420Height +
        " , i420FrameRate: " + this.i420FrameRate)
      return false;
    }

    let res = fs.accessSync(this.i420FilePath);
    if (!res) {
      console.error(TAG, "file not exists , path: " + this.i420FilePath);
      prompt.showToast({ message: "文件不存在" });
      return false;
    }
    return true;
  }
}