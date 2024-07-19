import {NERtcConstants} from '@nertc/nertc_sdk';
import Delegate from '../common/Delegate';
import ChatPresenter from '../common/Presenter';
import { LoadingDialog } from '@ohos.arkui.advanced.Dialog'

@Entry
@Component
export struct MainAndSubStream {
  TAG: string = "NetworkProbe"
  quality_arr: string[] = ["质量未知", "质量极好", "用户主观感觉和极好差不多，但码率可能略低于极好", "用户主观感受有瑕疵但不影响沟通", "勉强能沟通但不顺畅",
                      "网络质量非常差，基本不能沟通", "完全无法沟通"]
  @State uplinkProbe: boolean = true;
  @State downlinkProbe: boolean = true;
  @State uplinkProbeBitrate: string = "5000000";
  @State downlinkProbeBitrate: string = "200000";
  @State result: string = "";
  onPageShow() {
    console.info(this.TAG, '=== CallPage show ===')
    ChatPresenter.getInstance().setDelegate(this.delegate)
    this.init()
  }
  onPageHide(): void {
    ChatPresenter.getInstance().release()
    ChatPresenter.getInstance().removeDelegate(this.delegate)
  }
  init() {
    ChatPresenter.getInstance().init(getContext())
  }
  ProbeWaitDialog: CustomDialogController = new CustomDialogController({
    builder: LoadingDialog({
      content: '正在网络探测'
    }),
    autoCancel: false,
    customStyle: true,
    alignment: DialogAlignment.Center
  })
  public delegate: Delegate = {
    onJoin: (result: number, channelId: bigint): void => {

    },
    onLeave: (result: number): void =>{

    },
    onUserJoin:(uid: bigint): void => {

    },
    onUserLeave:(uid: bigint, reason: number): void => {

    },
    onUserAudioStart:(uid: bigint): void =>{

    },
    onUserAudioStop:(uid: bigint): void =>{

    },
    onUserVideoStart:(uid: bigint): void =>{

    },
    onLastmileQuality:(quality: number): void =>{
      //`onLastmileQuality`：网络质量状态回调，以打分形式描述上下行网络质量的主观体验。该回调视网络情况在约 5 秒内返回。
      this.result += `网络质量： ${this.quality_arr[quality]} \n`
    },
    onLastmileProbeResult:(result: NERtcConstants.LiteSDKProbeResult): void =>{
      //`onLastmileProbeResult`：网络质量探测报告回调，报告中通过客观数据反馈上下行网络质量。该回调视网络情况在约 30 秒内返回。
      this.result += `rtt： ${result.rtt} \n`
      this.result += `ResultType： ${result.type} \n`
      this.result += `上行丢包率： ${result.upLinkResult?.packetLossRate} \n`
      this.result += `上行jitter： ${result.upLinkResult?.jitter} \n`
      this.result += `上行带宽： ${result.upLinkResult?.availableBandWidth} \n`
      this.result += `下行丢包率： ${result.downLinkResult?.packetLossRate} \n`
      this.result += `下行jitter： ${result.downLinkResult?.jitter} \n`
      this.result += `下行带宽： ${result.downLinkResult?.availableBandWidth} \n`
      this.ProbeWaitDialog.close()
    }
  };
  build() {
    Row() {
      Column() {
        Text('通话前网络探测')
          .width('100%')
          .fontSize(20)
          .textAlign(TextAlign.Center)
          .margin({ top: "20vp", bottom: "20vp" })

        Row() {
          Text(this.result)
            .width(250)
            .height(400)
            .fontSize(15)
            .border({ width: 1 })
            .padding(10)
            .margin(5)

        }
        Row() {
          Text('期望上行码率：')
            .fontSize(15)
            .textAlign(TextAlign.Start)
            .margin({ left: "20vp"})
          TextInput({text: this.uplinkProbeBitrate})
        }
        Row() {
          Text('期望下行码率：')
            .fontSize(15)
            .textAlign(TextAlign.Start)
            .margin({ left: "20vp"})
          TextInput({text:this.downlinkProbeBitrate})
        }
        Row() {
          Toggle({ type: ToggleType.Checkbox, isOn: this.uplinkProbe })
            .margin({ left: "20vp"})
            .onChange((isOn: boolean) => {
                this.uplinkProbe = !this.uplinkProbe
            })
          Text('uplinkProbe')
            .width('100%')
            .fontSize(15)
            .textAlign(TextAlign.Start)
            .margin({ top: "20vp", bottom: "20vp" })
        }
        Row() {
          Toggle({ type: ToggleType.Checkbox, isOn: this.downlinkProbe })
            .margin({ left: "20vp"})
            .onChange((isOn: boolean) => {
                this.downlinkProbe = !this.downlinkProbe
            })
          Text('downlinkProbe')
            .width('100%')
            .fontSize(15)
            .textAlign(TextAlign.Start)
            .margin({ top: "20vp", bottom: "20vp" })
        }
        Row() {
          Button("开始网络探测")
            .width('100%')
            .fontSize(20)
            .margin({ top: "20vp", bottom: "20vp" })
            .onClick(()=>{
              let config: NERtcConstants.LastmileProbeConfig = new NERtcConstants.LastmileProbeConfig()
              config.probeUplink = this.uplinkProbe
              config.probeDownlink = this.downlinkProbe
              config.expectedUplinkBitrate = BigInt(this.uplinkProbeBitrate);
              config.expectedDownlinkBitrate = BigInt(this.downlinkProbeBitrate);
              this.result = ""
              this.ProbeWaitDialog.open()
              ChatPresenter.getInstance().startLastmileProbeTest(config);//关闭主流
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