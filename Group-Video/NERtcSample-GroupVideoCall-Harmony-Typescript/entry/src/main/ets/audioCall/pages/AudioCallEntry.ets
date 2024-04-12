import prompt from '@ohos.promptAction';
import AbilityAccessCtrl from '@ohos.abilityAccessCtrl';
import router from '@ohos.router';
import { LoginInfo } from '../../common/Model'

@Entry
@Component
struct audioCallEntry {

  TAG: string = "audioCallEntry"

  onPageShow() {
    this.uid = Math.floor(Math.random() * 10000).toString()
    this.requestPermission()
  }

  @State cname: string = "1392"
  @State uid: string = ""
  @State tex: string = ""
  build() {
    Row() {
      Column() {
          Text('NERtc 音频通话示例')
            .width('100%')
            .fontSize(30)
            .fontWeight(FontWeight.Bold)
            .textAlign(TextAlign.Center)
            .margin({ top: "20vp", bottom: "20vp" })
          Image($r('app.media.logo'))
            .width("180vp")
            .objectFit(ImageFit.Contain).margin(15)
            .margin({ top: "10vp", bottom: "40vp" })
          TextInput({placeholder: "请输入房间号", text: this.cname})
            .type(InputType.Normal)
            .onChange((value: string) => {
              this.cname = value;
            })
            .padding(20)
            .margin({ top: 30, left: 10, right: 10})
            .copyOption(CopyOptions.LocalDevice)
          TextInput({placeholder: "请输入用户id", text: this.uid})
            .type(InputType.Normal)
            .onChange((value: string) => {
              this.uid = value
            })
            .padding(20)
            .margin(10)
            .type(InputType.Number)
            .copyOption(CopyOptions.LocalDevice)

          Row({ space: 35}) {
            Button("进入房间", { type: ButtonType.Normal, stateEffect: true})
              .onClick(() => {
                this.transToChat()
              })
              .width('60%')
              .height(60)
              .fontSize(20)
              .borderRadius(10)

          }.justifyContent(FlexAlign.Center).width('100%').margin({ top: 20 }).height(80)

      }
      .width('100%')
      .height('100%')
      .justifyContent(FlexAlign.Start)
    }
    .height('100%')
    .justifyContent(FlexAlign.Start)
  }

  transToChat(): void {

    if(this.cname === "") {
      prompt.showToast({ duration: 2000, message: "请输入房间号."})
      return
    }
    if(this.uid === "") {
      prompt.showToast({ duration: 2000, message: "请输入用户id."})
      return
    }

    let param: LoginInfo = {
      cname: this.cname,
      uid: this.uid
    }
    router.pushUrl({ url: 'audioCall/pages/AudioCall',  params: param }, (err)=> {
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
      atManager.requestPermissionsFromUser(context, ["ohos.permission.MICROPHONE", "ohos.permission.CAMERA"], (err, data) => {
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

}