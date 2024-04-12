import { NERtcVideoView } from 'sdk';
import ChatPresenter, { remoteUsers } from '../common/Presenter';
import router from '@ohos.router';
import * as model from '../common/Model';
import Delegate from '../common/Delegate';

@Entry
@Component
struct VideoCall {

  @State message: string = '1v1音视频通话';
  TAG: string = "VideoCall"
  chat?: ChatPresenter
  @State local?: model.User = undefined
  @State remote?: model.User = undefined

  delegate: Delegate = {

    onJoin:(result: number, channelId: bigint): void => {
      console.info(this.TAG, 'join channel result: ' + result)
    },

    onLeave:(result: number): void => {
      console.info(this.TAG, 'leave channel result: ' + result)
    },

    onUserJoin:(uid: bigint): void => {
      console.info(this.TAG, `User: ${uid} joined.`)
      if(this.remote == undefined) {
        this.remote = { uid: uid }
        console.info(this.TAG, 'Create Remote User.')
      }
    },

    onUserLeave:(uid: bigint, reason: number): void => {
      console.info(this.TAG, `User: ${uid} leave.`)
      if(this.remote && this.remote.uid === uid) {
        this.remote = undefined
      }
    }
  }

  onPageShow(): void {
    console.info(this.TAG, '==== VideoCall Show ===')
    this.chat = ChatPresenter.getInstance()

    let login = router.getParams() as model.LoginInfo
    this.local = { uid: BigInt(login?.uid ?? 0) }

    let uid = remoteUsers[0]
    if(uid != undefined) {
      this.remote = { uid: uid }
    }

    this.chat.setDelegate(this.delegate)
    //现在监听不到前后台切换，解决切后台黑屏的情况
    this.chat.enableVideo(false)
    setTimeout(() => {
      this.chat?.enableVideo(true)
    })
  }

  onBackPress(): boolean | void {
    console.info(this.TAG, '==== VideoCall page backpress ====')
    this.chat?.leave()
    this.chat?.removeDelegate(this.delegate)
    this.chat?.enableVideo(false)
  }

  build() {
    Row() {
      Column() {

        Flex({ direction: FlexDirection.Column }) {
          Stack({ alignContent: Alignment.BottomStart }) {
            Stack({ alignContent: Alignment.TopEnd }){

              if(this.remote) {
                NERtcVideoView ({
                  canvasId: String(this.remote.uid),
                  onLoad: (() => {
                    if(this.remote) {
                      console.info(this.TAG, `User: ${String(this.remote?.uid)} surface create.`)
                      this.chat?.attach(this.remote)
                    }
                  }),
                  onDestroy: (() => {
                    if(this.remote) {
                      console.info(this.TAG, `User: ${String(this.remote?.uid)} surface release.`)
                    }
                  })
                }).width('100%').height('100%')
              }

              if(this.local) {
                NERtcVideoView({
                  canvasId: String(this.local.uid),
                  onLoad: (() => {
                    console.info(this.TAG, `User: ${this.local?.uid} surface create.`)
                    if(this.local) this.chat?.attach(this.local)
                  }),
                  onDestroy: (() => {
                    console.info(this.TAG, `User: ${this.local?.uid} surface release.`)
                  })
                }).width(this.remote ? 200 : '100%').height(this.remote ? 200 : '100%')
              }

            }.width('100%').height('100%')
          }.width('100%').height('100%')
        }

      }
      .width('100%')
    }
    .height('100%')
  }
}