import { ChatResult, ChatState, LoginInfo } from './chat/ChatModel'
import router from '@ohos.router';
import { ChatPresenter } from './chat/Presenter';
import ChatNotify, { OPERATOR } from './chat/Delegate';
import Prompt from '@system.prompt';
import DemoUser from '../model/DemoUser';
import { NERtcVideoView } from 'sdk';

@Entry
@Component
struct Chat {

  TAG: string = "MultiChat"
  @State
  users: Array<DemoUser> = []
  myUid: bigint = BigInt('0')
  @State
  title: string = "Channel-"
  chat?: ChatPresenter

  uiDelegate: ChatNotify = {

    notify:(result: ChatResult): void => {
      console.info(this.TAG, `Channel state:${result.result}`)
      Prompt.showToast( {duration: 2000, message: result.detail})
    },

    update:(operator: OPERATOR, demoUser: DemoUser): void => {
      let user = this.users.find(user => user.uid === demoUser.uid)
      if(operator == OPERATOR.ADD) {
        if(!user) {
          if(demoUser.uid == this.myUid) this.users[0] = demoUser
          if(demoUser.uid != this.myUid) this.users.push(demoUser)
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
    console.info(this.TAG, '=== onPageShow ===')
    let login = router.getParams() as LoginInfo
    this.chat = new ChatPresenter(this.uiDelegate)
    this.myUid = BigInt(login.uid).valueOf()
    this.chat.join(login)
    this.title += login?.cname ?? ""
  }

  onBackPress() {
    this.chat?.release()
  }

  build() {
    Row() {
      Column() {
        Flex({ direction: FlexDirection.Column }) {
          Text(this.title)
            .margin({ top: 22, left: 5 })
            .width('100%')
            .fontSize(40)
            .fontWeight(FontWeight.Bold)
            .textAlign(TextAlign.Start)
          Grid(){
            ForEach(this.users, (item: DemoUser) => {
              GridItem() {
                Stack({ alignContent: Alignment.TopStart }) {
                  NERtcVideoView({
                    sCanvasId: item.xComponentId,
                    onLoad: (() => {
                      console.info(this.TAG, `User:${item.uid} surface create.`)
                      let user = this.users.find(user => user.uid == item.uid)
                      if(user) this.chat?.attach(user)
                    }),
                    onDestroy: (() => {
                      console.info(this.TAG, `User:${item.uid} surface release.`)
                    })
                  }).width('100%').height('100%')
                  Text(`uid:${item.uid}`)
                    .width('100%')
                    .fontColor(Color.White)
                    .textAlign(TextAlign.Start)
                    .margin(5)
                }
              }.width('50%').height(200).margin({top: 10})
            }, (item: DemoUser) => `${item.uid}`)
          }
          .cachedCount(4)
          .columnsGap(15)
          .columnsTemplate('1fr 1fr')
        }
      }
      .width('100%')
    }
    .height('100%')
  }
}