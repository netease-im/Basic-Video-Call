import { NERtcConstants, NERtcVideoView } from '@nertc/nertc_sdk';
import ChatPresenter, { remoteUsers } from '../common/Presenter';
import router from '@ohos.router';
import * as model from '../common/Model';
import Delegate from '../common/Delegate';
import fs from '@ohos.file.fs';
import fileIo from '@ohos.file.fs';
import { BusinessError } from '@ohos.base';
import prompt from '@ohos.promptAction';

@Entry
@Component
export struct MainAndSubStreamVideo{
  TAG: string = "MainAndSubStreamVideo"
  chat?: ChatPresenter
  @State cname: string = ""
  @State uid: string = ""
  @State local?: model.User = undefined
  @State remoteUser?:model.User = undefined
  @State login: model.LoginInfo = {
    cname: "1395",
    uid: Math.floor(Math.random() * 10000).toString()
  };
  i420FilePath: string = "";
  i420Width: number = 1024;
  i420Height: number = 576;
  i420FrameRate: number = NERtcConstants.NERtcVideoFrameRate.kNERtcVideoFrameRateFps15;
  isJoined: boolean = false;
  intervalTaskId: number = -1;
  yuvFile?: fileIo.File;
  fileReadOffset: number = 0;
  readFileCatchException = (err: BusinessError) => {
    console.error(this.TAG, "read file data failed with error message: " + err.message + ", error code: " + err.code);
  };

  onPageShow() {
    console.info(this.TAG, '=== CallPage show ===')
    this.local = { uid: BigInt(this.login?.uid ?? 0) }
    this.chat = ChatPresenter.getInstance()
    ChatPresenter.getInstance().setDelegate(this.delegate)
    this.init()
    this.beforeJoin()
    this.joinRoom()

    //现在监听不到前后台切换，解决切后台黑屏的情况
    this.chat.enableVideo(false)
    this.chat.enableSubVideo(false)
    setTimeout(() => {
      //开启主流
      this.chat?.enableVideo(true)
      //开启辅流
      this.chat?.enableSubVideo(true)
    })

    //开启外部输入走辅流
    this.chat.setExternalVideoSouce(true,NERtcConstants.NERtcVideoStreamType.kNERtcVideoStreamTypeSub)

    this.checkRawYUVFile()
      .then(()=>{
      this.startPushI420();
    })
      .catch((err: Error)=> {
    })
  }

  onPageHide(): void {
    ChatPresenter.getInstance().leave()
    ChatPresenter.getInstance().removeDelegate(this.delegate)
    ChatPresenter.getInstance().release()

    if (this.intervalTaskId != -1) {
      clearInterval(this.intervalTaskId);
      console.info(this.TAG, "clearInterval succeed , id: " + this.intervalTaskId);
    }

    if (this.yuvFile) {
      fs.close(this.yuvFile).then(() => {
        console.info(this.TAG, "close file succeed");
      }).catch((err: BusinessError) => {
        console.error(this.TAG, "close file failed with error message: " + err.message + ", error code: " + err.code);
      });
    }
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
  delegate: Delegate = {

    onJoin:(result: number, channelId: bigint): void => {
      console.info(this.TAG, 'join channel result: ' + result)
    },

    onLeave:(result: number): void => {
      console.info(this.TAG, 'leave channel result: ' + result)
    },

    onUserJoin:(uid: bigint): void => {
      console.info(this.TAG, `User: ${uid} joined.`)
      if(this.remoteUser == undefined) {
        this.remoteUser = { uid: uid }
        console.info(this.TAG, 'Create Remote User.')
      }
    },

    onUserLeave:(uid: bigint, reason: number): void => {
      console.info(this.TAG, `User: ${uid} leave.`)
      if(this.remoteUser && this.remoteUser.uid === uid) {
        this.remoteUser = undefined
      }
    }
  }

  async startPushI420() {
    this.yuvFile = fs.openSync(this.i420FilePath, fs.OpenMode.READ_ONLY);
    if (!this.yuvFile) {
      prompt.showToast({ message: "文件读取异常" });
      return;
    }
    console.info(this.TAG, "file fd: " + this.yuvFile.fd);
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
          console.warn(this.TAG, "read file to the end so loop again , readLen:" + readLen);
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
        this.chat?.pushExternalVideoFrame(videoFrame,NERtcConstants.NERtcVideoStreamType.kNERtcVideoStreamTypeSub);
      })
        .catch(this.readFileCatchException);
    }, pushIntervalMs);
  }

  async checkRawYUVFile(): Promise<void>{
    return new Promise((resovle, reject) => {
      let dir: string = getContext(this).filesDir + "/media";
      this.i420FilePath = dir + "/1024_576.yuv"
      if (fs.accessSync(this.i420FilePath)) {
        console.info(this.TAG, "yuv test file is already exist path: " + this.i420FilePath);
        resovle()
        return;
      }
      fs.mkdirSync(dir);
      console.warn(this.TAG, 'yuv test file is not exist.')

      getContext(this).resourceManager.getRawFileContent("1024_576.yuv").then(data => {
        let writeLen = fs.createStreamSync(this.i420FilePath, 'w').writeSync(data.buffer)
        console.info(this.TAG, 'write 1024_576.yuv len: ' + writeLen + ", path: " + this.i420FilePath);
        resovle()
      }).catch((error: BusinessError) => {
        reject(error)
      });
    })
  }


  build() {
    Row() {
      Column(){
        Text('房间号: ' + this.cname)
          .width('100%')
          .fontSize(20)
          .textAlign(TextAlign.Center)
          .margin({ top: "20vp", bottom: "20vp" })
        Row() {
          //本地主流画布
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
            }).width('50%').height('40%')
            //本地辅流画布
            NERtcVideoView({
              canvasId: String(this.local.uid + 'sub'),
              onLoad: (() => {
                console.info(this.TAG, `User: ${this.local?.uid} surface create.`)
                if (this.local) this.chat?.attachSub(this.local)
              }),
              onDestroy: (() => {
                console.info(this.TAG, `User: ${this.local?.uid} surface release.`)
              })
            }).width('50%').height('40%')
          }
        }.justifyContent(FlexAlign.SpaceBetween)
        Row() {
          //远端主流画布
          if (this.remoteUser) {
            NERtcVideoView({
              canvasId: String(this.remoteUser.uid),
              onLoad: (() => {
                console.info(this.TAG, `User: ${this.remoteUser?.uid} surface create.`)
                if (this.local) this.chat?.attach(this.remoteUser)
              }),
              onDestroy: (() => {
                console.info(this.TAG, `User: ${this.remoteUser?.uid} surface release.`)
              })
            }).width('50%').height('40%')
            //远端辅流画布
            NERtcVideoView({
              canvasId: String(this.remoteUser.uid + 'sub'),
              onLoad: (() => {
                console.info(this.TAG, `User: ${this.remoteUser?.uid} surface create.`)
                if (this.local) this.chat?.attachSub(this.remoteUser)
              }),
              onDestroy: (() => {
                console.info(this.TAG, `User: ${this.remoteUser?.uid} surface release.`)
              })
            }).width('50%').height('40%')
          }
        }.justifyContent(FlexAlign.SpaceBetween)
      }
      .width('100%')
      .height('100%')
      .justifyContent(FlexAlign.Start)
    }
    .width('100%')
    .height('100%')
  }
}