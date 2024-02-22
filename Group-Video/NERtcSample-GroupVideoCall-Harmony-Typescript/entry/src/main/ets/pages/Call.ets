import router from '@ohos.router';
import { ChatResult, LoginInfo } from './chat/ChatModel'
import { NERtcVideoView } from 'sdk';
import { ChatPresenter } from './chat/Presenter';
import DemoUser from '../model/DemoUser';
import ChatNotify, { OPERATOR } from './chat/Delegate';
import Prompt from '@system.prompt';

@Entry
@Component
struct Call {

  TAG: string = "CallPage"
  @State
  login?: LoginInfo = undefined
  chat?: ChatPresenter
  @State
  users: Array<DemoUser> = []


  uiDelegate: ChatNotify = {

    notify:(result: ChatResult): void => {
      console.info(this.TAG, `Channel state:${result.result}`)
      Prompt.showToast( {duration: 2000, message: result.detail})
    },

    update:(operator: OPERATOR, demoUser: DemoUser): void => {
      let user = this.users.find(user => user.uid === demoUser.uid)
      if(operator == OPERATOR.ADD) {
        if(!user) {
          if(demoUser.uid == BigInt(this.login?.uid ?? "0")) this.users[0] = demoUser
          if(demoUser.uid != BigInt(this.login?.uid ?? "0")) this.users.push(demoUser)
        } else {
          console.warn(`${demoUser.uid} is exist, ignore.`)
        }
      }
      if(operator == OPERATOR.DEL) {
        if(user) {
          this.users = this.users.filter(user => user.uid !== demoUser.uid)
        } else {
          console.warn(`${demoUser.uid} is not exist, ignore.`)
        }
      }
    }
  }

  onPageShow() {
    console.info(this.TAG, '=== CallPage show ===')
    this.login = router.getParams() as LoginInfo
    this.chat = new ChatPresenter(this.uiDelegate)
    this.chat.join(this.login)
  }

  onBackPress() {
    console.info(this.TAG, '==== CallPage backpress ===')
    this.chat?.release()
  }

  build() {
    Row() {
      Column() {
        Flex({ direction: FlexDirection.Column }) {
          Stack({ alignContent: Alignment.TopEnd }){
            if(this.login) {
              NERtcVideoView({
                sCanvasId: this.login.uid,
                onLoad: (() => {
                  console.info(this.TAG, `User:${this.login?.uid} surface create.`)
                  let user = this.users.find(user => user.uid == BigInt(this.login?.uid ?? "0"))
                  if(user) this.chat?.attach(user)
                }),
                onDestroy: (() => {
                  console.info(this.TAG, `User:${this.login?.uid} surface release.`)
                })
              }).width('100%').height('100%')
            }
            if(this.users[1]) {
              NERtcVideoView({
                sCanvasId: this.users[1].uid.toString(),
                onLoad: (() => {
                  if(this.users[1]) {
                    console.info(this.TAG, `User:${this.users[1].uid} surface create.`)
                    this.chat?.attach(this.users[1])
                  }
                }),
                onDestroy: (() => {
                  if(this.users[1]) {
                    console.info(this.TAG, `User:${this.users[1].uid} surface release.`)
                  }
                })
              }).width(200).height(200)
            }
          }
        }
      }
      .width('100%')
    }
    .height('100%')
  }

}