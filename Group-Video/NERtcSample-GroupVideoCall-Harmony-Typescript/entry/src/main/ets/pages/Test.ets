
import prompt from '@ohos.promptAction';
import AbilityAccessCtrl, { Permissions } from '@ohos.abilityAccessCtrl';
import { NERtcSDK, NERtcCallback, NERtcConstants, NERtcStatsObserver, NERtcVideoView} from 'sdk'
import fs, { Filter } from '@ohos.file.fs';
import common from '@ohos.app.ability.common';
import base from '@ohos.base';
import AudioCapturerHelper from '../audio/AudioCapturerHelper';
import TALogicManager from '../ta/TALogicManager';
import TACore from '../ta/TACore';
import router from '@ohos.router';
import CommonConstants from '../common/CommonConstants';
import DemoUser from '../model/DemoUser'
import util from '@ohos.util';

const TAG: string = 'DEMO';
let mCapturer: AudioCapturerHelper = new AudioCapturerHelper();
let taLogicManager: TALogicManager = new TALogicManager();
let taCore: TACore = new TACore();

@Entry
@Component
struct Index {
   @State isMute: boolean = false;
   @State enableAudio: boolean = true;
   context = getContext(this) as common.UIAbilityContext;
   filesDir:string = this.context.filesDir
   currentUTC: Date = new Date();
   @State userList: Array<DemoUser> = [];

   myUid : string = "";
   cname : string = "";

  FindUser(uid: BigInt): number {
    let index = this.userList.findIndex(obj => obj.uid === uid)
    return index;
  }

  callback: NERtcCallback = {
     onJoinChannel: (result: number, channelId: BigInt, elapsed: BigInt, uid: BigInt): void => {
       console.info(TAG, "result: " + result + ", channelId : " + channelId + ", elapsed: " + elapsed + ", uid: " + uid);
     },

     onLeaveChannel: (result: number): void => {
       console.info(TAG, "result: " + result )
     },

     onUserJoined: (uid: bigint): void => {
       console.info(TAG, "uid: " + uid)
       let stringValue: string = uid.toString();
       let user : DemoUser = new DemoUser(uid, stringValue);
       this.userList.push(user);
     },

    onUserLeave: (uid: bigint, reason: number): void => {
       console.info(TAG, "uid: " + uid + ", reason: " + reason)
       let stringValue: string = uid.toString();

       let index : number = this.FindUser(uid);
       this.userList.splice(index,1);
     },

     onUserAudioStart: (uid: bigint): void => {
       console.info(TAG, "uid: " + uid)
     },

     onUserAudioStop: (uid: bigint): void => {
       console.info(TAG, "uid: " + uid)
     },

     onUserVideoStart: (uid: bigint, maxProfile: number): void => {
       console.info(TAG, "uid: " + uid + ", maxProfile: " + maxProfile)
     },

     onUserVideoStop: (uid: bigint): void => {
       console.info(TAG, "uid: " + uid)
     },

     onDisconnect: (reason: number): void => {
        console.info(TAG, "reason: " + reason)
     },

     onClientRoleChange:(oldRole: number, newRole: number): void => {
        console.info(TAG, "oldRole: " + oldRole + ", newRole: " + newRole)
     },

     onReceiveSEIMessage:(userId: bigint, data: Uint8Array, dataSize: number): void =>{
       let textDecoder = util.TextDecoder.create()
       let retStr = textDecoder.decodeWithStream(data)
       console.info(TAG, "onReceiveSEIMessage: " + retStr)
     }
  }

  statsObserver: NERtcStatsObserver = {

    onRtcStats(stats: NERtcConstants.NERtcStats): void {
      console.info(TAG, "onRtcStats:" + stats.toString())
    },

    onLocalAudioStats(stats: NERtcConstants.NERtcAudioSendStats): void {
      console.info(TAG, "onLocalAudioStats:" + stats.toString())
    },

    onRemoteAudioStats(statsArray: Array<NERtcConstants.NERtcAudioRecvStats>): void {
      console.info(TAG, "onRemoteAudioStats:" + statsArray.toString())
    },

    onLocalVideoStats(stats: NERtcConstants.NERtcVideoSendStats): void {
      console.info(TAG, "onLocalVideoStats:" + stats.toString())
    },

    onRemoteVideoStats(statsArray: Array<NERtcConstants.NERtcVideoRecvStats>): void {
      console.info(TAG, "onRemoteVideoStats:" + statsArray.toString())
    },

    onNetworkQuality(statsArray: Array<NERtcConstants.NERtcNetworkQualityInfo>): void {
      console.info(TAG, "onNetworkQuality:" + statsArray.toString())
    }
  }

  aboutToAppear(){
    if (this.myUid.trim().length <= 0) {
      let randomNumber:number = Math.floor(Math.random() * (999999 - 100000 + 1)) + 100000;
      this.myUid = randomNumber.toString();
    }
  }

  async requestCameraPermissions() {
    let atManager = AbilityAccessCtrl.createAtManager();
    try {
      let context = getContext(this);
      atManager.requestPermissionsFromUser(context, ["ohos.permission.CAMERA"], (err, data)=>{
        console.info("data:" + JSON.stringify(data));
        console.info("data permissions:" + data.permissions);
        console.info("data authResults:" + data.authResults);

        let messageStr: string = data.authResults[0] === AbilityAccessCtrl.GrantStatus.PERMISSION_GRANTED ? "摄像头已授权" : "摄像头未授权"
        prompt.showToast({
          message:messageStr,
          duration:2000
        })
      });
    } catch(err) {
      console.log(`catch err->${JSON.stringify(err)}`);
    }
  }

  async requestMicphonePermissions() {
    const permissions: Array<Permissions> = [
      'ohos.permission.MICROPHONE'
    ];
    let atManager = AbilityAccessCtrl.createAtManager();
    let context = getContext(this);
    await atManager.requestPermissionsFromUser(context, permissions).then((data) => {

      let messageStr: string = data.authResults[0] === AbilityAccessCtrl.GrantStatus.PERMISSION_GRANTED ? "麦克风权限已授权" : "麦克风未授权"
      prompt.showToast({
        message:messageStr,
        duration:2000
      })
      console.info(TAG, `Request permissions succeed, data is: ${data}`);
    }).catch((error: Error) => {
      console.info(TAG, `Request permissions failed, error is: ${error}`);
    }).catch((err: base.BusinessError) => {
      console.info(TAG, `requestPermissionsFromUser failed, code is ${err.code}, message is ${err.message}`)
    });
  }

  //获取文件列表
  getListFile(): void {
    class ListFileOption {
      public recursion: boolean = false;
      public listNum: number = 0;
      public filter: Filter = {};
    }
    let option = new ListFileOption();
    option.filter.suffix = ['.png', '.jpg', '.txt', 'pcm'];          // 匹配文件后缀名为'.png','.jpg','.txt'
    option.filter.displayName = ['*'];                    // 匹配文件全名以'test'开头
    option.filter.fileSizeOver = 0;                           // 匹配文件大小大于等于0
    option.filter.lastModifiedAfter = new Date(0).getTime();  // 匹配文件最近修改时间在1970年1月1日之后
    let files = fs.listFileSync(this.filesDir, option);
    for (let i = 0; i < files.length; i++) {
      console.info(TAG, "The name of file: " + files[i])
    }
  }

  async pushExternalCaptureAudioFrame(data: ArrayBuffer) {

    // public samplingRate: audio.AudioSamplingRate = audio.AudioSamplingRate.SAMPLE_RATE_16000;
    // public channels: audio.AudioChannel = audio.AudioChannel.CHANNEL_2;
    // public sampleFormat: audio.AudioSampleFormat = audio.AudioSampleFormat.SAMPLE_FORMAT_S16LE;
    // public encodingType: audio.AudioEncodingType = audio.AudioEncodingType.ENCODING_TYPE_RAW;

    let sampleRate: number = 44100;
    let channels: number = 2;
    let duration: number = 20; //推送的时间间隔，20ms
    //let sampleLength: number = sampleRate * channels * duration * 2 / 1000;
    //let samplesPerChannel :number = sampleRate * duration / 1000;
    let samplesPerChannel :number = data.byteLength / channels / 2;
    let lastSyncTimestamp: number = 0;
    let type: number = 0;

    let uint8Array = new Uint8Array(data);
    //NERtcSDK.getInstance().pushExternalAudioFrame(uint8Array, samplesPerChannel, sampleRate, channels, lastSyncTimestamp, type);
  }

  async startAudioCapture(): Promise<void> {
    await mCapturer.init();
    await mCapturer.start((buffer: ArrayBuffer, size: number) => {

      this.pushExternalCaptureAudioFrame(buffer)
      // parent.postMessage({
      //   'code': Constants.WORK_MESSAGE_CAPTURER_SEND,
      //   'buffer': buffer
      // }, [buffer]);
    });
  }
  touchFunc(event?: TouchEvent) {
    // 外部处理触控事件
    if (event) {
      console.log("lzh===> out touchFunc:" + event.type);
    }
  }
  @State strHermesJson: string = ''
  controller: TextInputController = new TextInputController()
  @State message: string = 'NERtcDemo'
  build() {
    Column() {
      Flex({ direction: FlexDirection.Column }){
          Button("Settings")
            .margin({ top: 22, left: 20 })
            .type(ButtonType.Capsule)
            .fontSize(20)
            .fontWeight(FontWeight.Regular)
            .fontWeight(FontWeight.Bold)
            .onClick(() => {
              router.pushUrl({
                url: CommonConstants.SETTINGS_URL,
                params: {
                  // src: CommonConstants.SECOND_SRC_MSG
                }
              }).catch((error: Error) => {
                console.info(TAG, 'IndexPage push error' + JSON.stringify(error));
              });
            })

          Text(this.message)
            .margin({ top: 22})
            .fontSize(50)
            .height(80)
            .fontWeight(FontWeight.Bold)
            .textAlign(TextAlign.Center)
            .onClick(() => {
            })

          TextInput({ text: this.cname, placeholder: 'cname', controller: this.controller })
            .placeholderColor(Color.Grey)
            .placeholderFont({ size: 14, weight: 400 })
            .caretColor(Color.Blue)
            .height(50)
            .margin(20)
            .fontSize(14)
            .fontColor(Color.Black)
            .onChange((value: string) => {
              this.cname = value
            })
            .onSubmit(() => {
            })

          TextInput({ text: this.myUid, placeholder: 'uid', controller: this.controller })
            .placeholderColor(Color.Grey)
            .placeholderFont({ size: 14, weight: 400 })
            .caretColor(Color.Blue)
            .margin({ left: 20, right: 20 })
            .height(50)
            .fontSize(14)
            .fontColor(Color.Black)
            .onChange((value: string) => {
              this.myUid = value;
            })
            .onSubmit(() => {
            })


        List({ space: 20, initialIndex: 0 }) {
            ListItem() {
              Column() {

                Row() {
                  Button("初始化引擎")
                    .margin({ top: 22, left: 20 })
                    .type(ButtonType.Capsule)
                    .fontSize(20)
                    .fontWeight(FontWeight.Regular)
                    .fontWeight(FontWeight.Bold)
                    .onClick(() => {

                      // let option: NERtcConstants.NERtcOption = new NERtcConstants.NERtcOption();
                      // option.logLevel = NERtcConstants.LogLevel.INFO;
                      // option.logDir = "test";
                      //
                      // NERtcSDK.getInstance().init("6acf024e190215b685905444b6e57dd7", this.callback, option)
                      // prompt.showToast({message: "init done", duration: 2000});
                    })

                  Button("JoinChannel")
                    .margin({ top: 22, left: 20 })
                    .type(ButtonType.Capsule)
                    .fontSize(20)
                    .fontWeight(FontWeight.Regular)
                    .fontWeight(FontWeight.Bold)
                    .onClick(() => {
                      if (this.cname.trim().length <= 0) {
                        prompt.showToast({message: "cname is empty", duration: 2000})
                        return;
                      }

                      if (isNaN(Number(this.myUid))) {
                         prompt.showToast({message: "uid is not number", duration: 2000})
                         return;
                      }

                      let my_uid : BigInt = BigInt(this.myUid);
                      let ret = NERtcSDK.getInstance().joinChannel("", this.cname, my_uid.valueOf())
                      prompt.showToast({message: 'join channel result: ' + ret, duration: 2000})

                      // let  randomBigInt: bigint = BigInt(Math.floor(Math.random() * Number.MAX_SAFE_INTEGER));
                      let index :number = this.FindUser(my_uid);
                      if (index >= 0) {
                        return;
                      }

                      let stringValue: string = my_uid.toString();
                      let user : DemoUser = new DemoUser(my_uid, stringValue);
                      user.isMe = true;
                      this.userList.push(user);
                    })
                }

                Row() {
                  Button("LeaveChannel")
                    .margin({ top: 22, left: 20 })
                    .type(ButtonType.Capsule)
                    .fontSize(20)
                    .fontWeight(FontWeight.Regular)
                    .fontWeight(FontWeight.Bold)
                    .onClick(() => {
                      let ret = NERtcSDK.getInstance().leaveChannel();
                      prompt.showToast({message: "leave channel result: " + ret, duration: 2000})

                      this.userList.splice(0,this.userList.length);
                    })
                }

                Row() {
                  Button(this.isMute ? "UnMuteAudio" : "MuteAudio")
                    .margin({ top: 22, left: 20 })
                    .type(ButtonType.Capsule)
                    .fontSize(20)
                    .fontWeight(FontWeight.Regular)
                    .fontWeight(FontWeight.Bold)
                    .onClick(() => {
                      this.isMute = !this.isMute;
                      let ret = NERtcSDK.getInstance().muteLocalAudioStream(this.isMute);
                      prompt.showToast({message: "muteLocalAudioStream result: " + ret})
                    })
                  Button(this.enableAudio ? "关闭语音" : "打开语音")
                    .margin({ top: 22, left: 20 })
                    .type(ButtonType.Capsule)
                    .fontSize(20)
                    .fontWeight(FontWeight.Regular)
                    .fontWeight(FontWeight.Bold)
                    .onClick(() => {
                        this.enableAudio = !this.enableAudio;
                        let ret = NERtcSDK.getInstance().enableLocalAudio(this.enableAudio);
                        prompt.showToast({message: "enableLocalAudio result: " + ret})
                    })
                }

                Grid(){
                  ForEach(this.userList, (item: DemoUser) => {
                    GridItem(){
                      NERtcVideoView({
                        sCanvasId: item.xComponentId,
                        onLoad: (() => {
                          let canvas: NERtcConstants.NERtcVideoCanvas = {
                            xComponentId: item.xComponentId
                          }

                          if (item.isMe) {
                            let ret = NERtcSDK.getInstance().enableLocalVideo(true);
                            NERtcSDK.getInstance().setupLocalVideoCanvas(canvas);
                          } else {
                            let ret = NERtcSDK.getInstance().setupRemoteVideoCanvas(canvas, item.uid);
                          }
                        }),
                      }).width(150).height(150)

                    }
                  },(item: DemoUser) => `${item.uid}`)
                }

                Row() {
                  Button("sendSEI")
                    .margin({ top: 22, left: 20 })
                    .type(ButtonType.Capsule)
                    .fontSize(20)
                    .fontWeight(FontWeight.Regular)
                    .fontWeight(FontWeight.Bold)
                    .onClick(() => {
                      let msg: string = "test sei"
                      let buff: Uint8Array = new util.TextEncoder().encodeInto(msg); //utf-8

                      let ret = NERtcSDK.getInstance().sendSEIMessage(buff, buff.length)
                      prompt.showToast({ message: "setupLocalVideoCanvas result: " + ret })
                    })

                  Button("sendSEI 辅流")
                    .margin({ top: 22, left: 20 })
                    .type(ButtonType.Capsule)
                    .fontSize(20)
                    .fontWeight(FontWeight.Regular)
                    .fontWeight(FontWeight.Bold)
                    .onClick(() => {
                      let msg: string = "test sei sub stream";
                      let buff: Uint8Array = new util.TextEncoder().encodeInto(msg); //utf-8

                      let ret = NERtcSDK.getInstance().sendSEIMessage(buff, buff.length,NERtcConstants.NERtcVideoStreamType.kNERtcVideoStreamTypeSub);
                      prompt.showToast({ message: "setupLocalVideoCanvas result: " + ret })
                    })
                }

                  Row() {
                  Button("setLocalVideoCanvas")
                    .margin({ top: 22, left: 20 })
                    .type(ButtonType.Capsule)
                    .fontSize(20)
                    .fontWeight(FontWeight.Regular)
                    .fontWeight(FontWeight.Bold)
                    .onClick(() => {
                      let canvas : NERtcConstants.NERtcVideoCanvas = {
                        xComponentId : CommonConstants.XCOMPONENT_ID_2
                      }

                      let ret = NERtcSDK.getInstance().setupLocalVideoCanvas(canvas);
                      prompt.showToast({message: "setupLocalVideoCanvas result: " + ret})
                    })

                  Button("setRemoteVideoCanvas")
                    .margin({ top: 22, left: 20 })
                    .type(ButtonType.Capsule)
                    .fontSize(20)
                    .fontWeight(FontWeight.Regular)
                    .fontWeight(FontWeight.Bold)
                    .onClick(() => {
                      let canvas : NERtcConstants.NERtcVideoCanvas = {
                        xComponentId : "289741"
                      }
                      let uid: BigInt = BigInt("289741");

                      let ret = NERtcSDK.getInstance().setupRemoteVideoCanvas(canvas, uid);
                      prompt.showToast({message: "setupRemoteVideoCanvas result: " + ret})
                    })
                }
                Row() {
                  Button("MuteLocalVideo")
                    .margin({ top: 22, left: 20 })
                    .type(ButtonType.Capsule)
                    .fontSize(20)
                    .fontWeight(FontWeight.Regular)
                    .fontWeight(FontWeight.Bold)
                    .onClick(() => {
                    })

                  Button("UnMuteLocalVideo")
                    .margin({ top: 22, left: 20 })
                    .type(ButtonType.Capsule)
                    .fontSize(20)
                    .fontWeight(FontWeight.Regular)
                    .fontWeight(FontWeight.Bold)
                    .onClick(() => {
                    })
                }
                Row() {
                  Button("切换为主播")
                    .margin({ top: 22, left: 20 })
                    .type(ButtonType.Capsule)
                    .fontSize(20)
                    .fontWeight(FontWeight.Regular)
                    .fontWeight(FontWeight.Bold)
                    .onClick(() => {
                    })

                  Button("切换为观众")
                    .margin({ top: 22, left: 20 })
                    .type(ButtonType.Capsule)
                    .fontSize(20)
                    .fontWeight(FontWeight.Regular)
                    .fontWeight(FontWeight.Bold)
                    .onClick(() => {
                    })
                }
                Row() {
                  Button("检测麦克风权限")
                    .margin({ top: 22, left: 10 })
                    .type(ButtonType.Capsule)
                    .fontSize(20)
                    .fontWeight(FontWeight.Regular)
                    .fontWeight(FontWeight.Bold)
                    .onClick(() => {
                      // PermissionHelper.alreadyGrantMicrophone((err: BusinessError<void>, result: boolean) => {
                      //   Logger.info(TAG, `err: ${err}, result: ${result}`)
                      //   if(err != null) {
                      //     prompt.showToast({message: 'invoke error!', duration: 2000})
                      //   } else {
                      //     let grant: string = result ? "Grant Permission." : "Not Grant Permission.";
                      //     prompt.showToast({message: grant, duration: 2000})
                      //   }
                      // });
                    })

                  Button("申请麦克风权限")
                    .margin({ top: 22, left: 10 })
                    .type(ButtonType.Capsule)
                    .fontSize(20)
                    .fontWeight(FontWeight.Regular)
                    .fontWeight(FontWeight.Bold)
                    .onClick(() => {
                      console.info("申请麦克风权限");
                      this.requestMicphonePermissions()
                    })
                }

                Row() {
                  Button("打开外部音频渲染")
                    .margin({ top: 22, left: 10 })
                    .type(ButtonType.Capsule)
                    .fontSize(20)
                    .fontWeight(FontWeight.Regular)
                    .fontWeight(FontWeight.Bold)
                    .onClick(() => {
                      console.info(TAG, "设置外部音频渲染")
                      // let set_ret: number = this.engine.setExternalAudioRender(true, 44100, 2);
                      // console.info("RTCSDK set_ret: " + set_ret);
                    })

                  Button("打开外部音频输入")
                    .margin({ top: 22, left: 10 })
                    .type(ButtonType.Capsule)
                    .fontSize(20)
                    .fontWeight(FontWeight.Regular)
                    .fontWeight(FontWeight.Bold)
                    .onClick(() => {
                    })
                }

                Row() {
                  Button("PCM")
                    .margin({ top: 22, left: 10 })
                    .type(ButtonType.Capsule)
                    .fontSize(20)
                    .fontWeight(FontWeight.Regular)
                    .fontWeight(FontWeight.Bold)
                    .onClick(() => {

                      let option: NERtcConstants.NERtcCreateAudioMixingOption = new NERtcConstants.NERtcCreateAudioMixingOption()
                      option.path = "/sdcard/test.pcm"
                      option.sendVolume = 60
                      option.playbackVolume = 80

                      let ret: number = NERtcSDK.getInstance().startAudioMixing(option)
                      console.info(TAG, "startAudioMixing ret: " + ret)
                    })

                  Button("麦克风采集")
                    .margin({ top: 22, left: 10 })
                    .type(ButtonType.Capsule)
                    .fontSize(20)
                    .fontWeight(FontWeight.Regular)
                    .onClick(() => {
                    })
                }

                Row() {
                  Button("设置外部视频输入")
                    .margin({ top: 22, left: 10 })
                    .type(ButtonType.Capsule)
                    .fontSize(20)
                    .fontWeight(FontWeight.Regular)
                    .fontWeight(FontWeight.Bold)
                    .onClick(() => {
                    })

                  Button("YUV输入")
                    .margin({ top: 22, left: 10 })
                    .type(ButtonType.Capsule)
                    .fontSize(20)
                    .fontWeight(FontWeight.Regular)
                    .onClick(() => {
                    })
                }

                Row() {
                  Button("检测摄像头权限")
                    .margin({ top: 22, left: 10 })
                    .type(ButtonType.Capsule)
                    .fontSize(20)
                    .fontWeight(FontWeight.Regular)
                    .fontWeight(FontWeight.Bold)
                    .onClick(() => {
                    })

                  Button("申请摄像头权限")
                    .margin({ top: 22, left: 10 })
                    .type(ButtonType.Capsule)
                    .fontSize(20)
                    .fontWeight(FontWeight.Regular)
                    .onClick(() => {
                      this.requestCameraPermissions()
                    })
                }

                Row() {
                  Button("打开摄像头")
                    .margin({ top: 22, left: 10 })
                    .type(ButtonType.Capsule)
                    .fontSize(20)
                    .fontWeight(FontWeight.Regular)
                    .onClick(() => {
                      let ret = NERtcSDK.getInstance().enableLocalVideo(true);
                      prompt.showToast({message: "enableLocalVideo true, result: " + ret})
                    })

                  Button("关闭摄像头")
                    .margin({ top: 22, left: 10 })
                    .type(ButtonType.Capsule)
                    .fontSize(20)
                    .fontWeight(FontWeight.Regular)
                    .onClick(() => {
                      let ret = NERtcSDK.getInstance().enableLocalVideo(false);
                      prompt.showToast({message: "enableLocalVideo false, result: " + ret})
                    })
                }
                .width('100%')

                Row() {
                  Button("打开麦克风")
                    .margin({ top: 22, left: 10 })
                    .type(ButtonType.Capsule)
                    .fontSize(20)
                    .fontWeight(FontWeight.Regular)
                    .onClick(() => {
                      let ret = NERtcSDK.getInstance().setSpeakerphoneOn(true);
                      console.info(TAG, "enableLocalAudio true result:" + ret)
                    })

                  Button("关闭麦克风")
                    .margin({ top: 22, left: 10 })
                    .type(ButtonType.Capsule)
                    .fontSize(20)
                    .fontWeight(FontWeight.Regular)
                    .onClick(() => {
                      let ret = NERtcSDK.getInstance().enableLocalAudio(false);
                      console.info(TAG, "enableLocalAudio true result:" + ret)
                    })
                }
                .width('100%')
                Column() {
                  TextInput({ text: this.strHermesJson, placeholder: '自动化命令', controller: this.controller })
                    .placeholderColor(Color.Grey)
                    .placeholderFont({ size: 14, weight: 400 })
                    .caretColor(Color.Blue)
                    .margin({ top: 22, left: 10 })
                    .height(40)
                    .margin(20)
                    .fontSize(14)
                    .fontColor(Color.Black)
                    .onChange((value: string) => {
                      this.strHermesJson = value
                    })
                    .onSubmit(() => {
                      let response = taLogicManager.execCommand(this.strHermesJson)
                      console.info(TAG, "execCommand response:" + response)
                    })
                }
                .width('100%')
              }
            }
          }
      }
    }
    .height('100%')
  }
}


