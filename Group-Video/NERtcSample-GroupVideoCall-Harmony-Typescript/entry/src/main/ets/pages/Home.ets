import prompt from '@ohos.promptAction';
import router from '@ohos.router';
import { LoginInfo } from './chat/ChatModel'
import AbilityAccessCtrl from '@ohos.abilityAccessCtrl';

@Entry
@Component
struct Home {

  TAG: string = "Home"

  onPageShow() {
    this.requestPermission()
  }

  @State cname: string = ""
  @State uid: string = ""
  build() {
    Row() {
      Column() {
        Flex({ direction: FlexDirection.Column }) {

          Text('NERtcDemo')
            .margin({ top: 22 })
            .width('100%')
            .fontSize(50)
            .fontWeight(FontWeight.Bold)
            .textAlign(TextAlign.Start)
            .padding(20)

          TextInput({placeholder: "Please input channel name."})
            .type(InputType.Normal)
            .onChange((value: string) => {
              this.cname = value;
            })
            .padding(20)
            .margin({ top: 30, left: 10, right: 10})
            .copyOption(CopyOptions.LocalDevice)
          TextInput({placeholder: "Please input user id."})
            .type(InputType.Normal)
            .onChange((value: string) => {
              this.uid = value
            })
            .padding(20)
            .margin(10)
            .type(InputType.Number)
            .copyOption(CopyOptions.LocalDevice)

            Row({ space: 35}) {
              Button("Start", { type: ButtonType.Normal, stateEffect: true})
                .onClick(() => {
                  this.transToChat()
                })
                .width('35%')
                .height(60)
                .fontSize(20)
                .borderRadius(10)


              Button("Auto", { type: ButtonType.Normal, stateEffect: true})
                .onClick(() => {
                  prompt.showToast({ duration: 2000, message: "In Development"})
                })
                .width('35%')
                .height(60)
                .fontSize(20)
                .borderRadius(10)

            }.justifyContent(FlexAlign.Center).width('100%').margin({ top: 20 }).height(80)
        }
      }
      .width('100%')
    }
    .height('100%')
  }

  transToChat(): void {

    if(this.cname === "") {
      prompt.showToast({ duration: 2000, message: "Please input channel name."})
      return
    }
    if(this.uid === "") {
      prompt.showToast({ duration: 2000, message: "Please input user id."})
      return
    }

    let param: LoginInfo = {
      cname: this.cname,
      uid: this.uid
    }
    router.pushUrl({ url: 'pages/Call',  params: param }, (err)=> {
      if(err) {
        console.error(`Invoke pushUrl failed, code is ${err.code}, message is ${err.message}`)
        return
      }
      console.info("Invoke pushUrl success.")
    })
  }

  async requestPermission() {
    let atManager = AbilityAccessCtrl.createAtManager();
    let context = getContext(this);
    try {
      //Mic.
      atManager.requestPermissionsFromUser(context, ["ohos.permission.MICROPHONE"], (err, data) => {
        if(err) {
          prompt.showToast({message: `request mic error: ${err}`})
          return
        }
        let grant: boolean = data.authResults[0] === AbilityAccessCtrl.GrantStatus.PERMISSION_GRANTED;
        let message: string = grant ? "麦克风已授权" : "麦克风未权限"
        prompt.showToast({message: message, duration: 2000})
      })

      //Camera.
      atManager.requestPermissionsFromUser(context, ["ohos.permission.CAMERA"], (err, data)=>{
        if(err) {
          prompt.showToast({message: `request camera error: ${err}`})
          return
        }
        let messageStr: string = data.authResults[0]
          === AbilityAccessCtrl.GrantStatus.PERMISSION_GRANTED ? "摄像头已授权" : "摄像头未授权"
        prompt.showToast({
          message:messageStr,
          duration:2000
        })
      });
    } catch(err) {
      console.info(this.TAG, `Request permission error: ${err}`)
    }
  }
}