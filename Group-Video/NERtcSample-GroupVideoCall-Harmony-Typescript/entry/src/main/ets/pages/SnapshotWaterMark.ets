import ChatPresenter from '../common/Presenter';
import router from '@ohos.router';
import * as model from '../common/Model';
import { NERtcConstants, NERtcSDK, NERtcVideoView } from '@nertc/nertc_sdk';
import image from '@ohos.multimedia.image';

@Entry
@Component
struct SnapshotWaterMark {

  @State message: string = '截图和水印';
  chat?: ChatPresenter
  @State local?: model.User = undefined
  TAG: string = 'Snapshot-WaterMark'
  @State image?: image.PixelMap = undefined

  onPageShow(): void {

    console.info(this.TAG, '==== Snapshot && WaterMark')
    this.chat = ChatPresenter.getInstance()

    let login = router.getParams() as model.LoginInfo
    this.local = { uid: BigInt(login?.uid ?? 0)}

    this.chat.enableVideo(false)
    setTimeout(() => {
      this.chat?.enableVideo(true)
    })
  }

  onBackPress(): boolean | void {

    console.info(this.TAG, '==== Snapshot && WaterMark ====')
    this.chat?.leave()
    this.chat?.enableVideo(false)
  }

  build() {
    Row() {
      Column() {

        Flex({ direction: FlexDirection.Column}) {
          Row() {

            if(this.local) {

              NERtcVideoView({
                canvasId: String(this.local.uid),
                onLoad: (() => {
                  if(this.local) {
                    console.info(this.TAG, 'User: ' + this.local.uid + " surface create.")
                    this.chat?.attach(this.local)
                  }
                })
              }).width('50%').height('100%')

            }

            Image(this.image).width('50%').height('100%')
          }.width('100%').height('50%')

          Button('截图', { type: ButtonType.Normal, stateEffect: true}).onClick(() => {

            console.info(this.TAG, 'User click take local snapshot button.')
            setTimeout(() => {
              NERtcSDK.getInstance().takeLocalSnapshot(NERtcConstants.NERtcVideoStreamType.kNERtcVideoStreamTypeMain, {
                onTakeSnapshotResult:(errorCode: number, image?: image.PixelMap): void => {

                  if(errorCode != NERtcConstants.ErrorCode.NO_ERROR) {
                    console.info(this.TAG, 'Take local snapshot failed.')
                    return
                  }
                  if(image) {
                    this.image = image
                  }
                }})
            })
          }).width('30%').height(50).borderRadius(5)
        }
      }
      .width('100%')
    }
    .height('100%')
  }
}