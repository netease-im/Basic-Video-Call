import { NERtcConstants } from 'sdk'
import { LoginInfo, ChatState, ChatResult, NERtcData, Init, Join, SetUp, Response, SetUpResponse,
  CallbackResponse,
  EnableVideo
} from './ChatModel';
import UIDelegate, { OPERATOR } from './Delegate'
import Config from '../../common/Config'
import DemoUser from '../../model/DemoUser';
import worker from '@ohos.worker';
import { API } from './ChatModel'

let uiDelegate_: UIDelegate
let state_: ChatState = ChatState.CHAT_IDLE
let TAG: string = 'MultiChat'
let worker_: worker.ThreadWorker

export class ChatPresenter {

  private login?: LoginInfo

  constructor(uiDelegate: UIDelegate) {
    uiDelegate_ = uiDelegate

    if(!worker_) {
      worker_ = new worker.ThreadWorker('demo/ets/pages/chat/Worker.ets', { name: 'nertc_worker' })
      worker_.onexit = code => {
        console.warn(TAG, `chat worker exit:${code}`)
      }
      worker_.onerror = err => {
        console.warn(TAG, `chat worker error:${JSON.stringify(err)}`)
      }
      worker_.onmessageerror = event => {
        console.info(TAG, `chat worker onmessageerror: ${JSON.stringify(event)}`)
      }
      worker_.onmessage = message => {
        console.info(TAG, `chat worker onmessage: ${JSON.stringify(message)}`)
        let response = message.data as Response
        switch(response.api) {
          case API.JOIN:
            {
              let ret: number = response.ret
              state_ = (ret == NERtcConstants.ErrorCode.NO_ERROR) ? ChatState.CHAT_ING : ChatState.CHAT_IDLE
              if(state_ != ChatState.CHAT_ING) uiDelegate_?.notify({result: state_, detail: `Error: JoinChannel failed, code:${ret}`})
            }
            break;
          case API.SETUP:
            {
              let setUp = response as SetUpResponse
              console.info(TAG, `uid:${setUp.uid} setup canvas ret:${setUp.ret}`)
            }
            break;
          case API.LEAVE:
            {
              let ret: number = response.ret
              console.info(TAG, `LeaveChannel ret:${ret}`)
              state_ = ChatState.CHAT_IDLE
              let detail: string = JSON.stringify({func: 'leaveChannel', ret: ret})
              let result: ChatResult = { result: state_, detail: detail}
              uiDelegate_?.notify(result)
            }
            break;
          case API.ON_JOIN:
            {
              let onJoin = response as CallbackResponse
              state_ = onJoin.ret == NERtcConstants.ErrorCode.NO_ERROR ? ChatState.CHAT_ED : ChatState.CHAT_IDLE
              let detail: string = JSON.stringify({ func: 'join', result: onJoin.ret, channelId: onJoin.object['channelId'], elapsed: onJoin.object['elapsed'], uid: onJoin.object['uid']})
              uiDelegate_?.notify( {result: state_, detail: detail} )

              if(state_ == ChatState.CHAT_ED) {
                let enableVideo: EnableVideo = { api: API.ENABLE_VIDEO, enable: true}
                __call_nertc__(enableVideo)
              }
              console.info(TAG, `Join channel: ${onJoin.ret}, elapsed: ${onJoin.object['elapsed']}`)
            }
            break;
          case API.ON_LEAVE:
            {
              state_ = ChatState.CHAT_IDLE
              let detail: string = JSON.stringify({func: 'leave', result: response.ret })
              uiDelegate_?.notify( {result: state_, detail: detail} )
              console.info(TAG, `Leave channel: ${response.ret}`)
            }
            break;
          case API.ON_USER_JOIN:
            {
              let onUserJoin = response as CallbackResponse
              let demoUser = new DemoUser(BigInt(onUserJoin.object['uid']), onUserJoin.object['uid'])
              uiDelegate_?.update(OPERATOR.ADD, demoUser)
              let detail: string = JSON.stringify({func: 'onUserJoin', uid: onUserJoin.object['uid']})
              uiDelegate_?.notify( {result: state_, detail: detail} )
              console.info(TAG, `User:${onUserJoin.object['uid']} joined.`)
            }
            break;
          case API.ON_USER_LEAVE:
            {
              let onUserLeave = response as CallbackResponse
              let demoUser = new DemoUser(BigInt(onUserLeave.object['uid']), onUserLeave.object['uid'])
              uiDelegate_?.update(OPERATOR.DEL, demoUser)
              let detail: string = JSON.stringify({func: "onUserLeave", uid: onUserLeave.object['uid']})
              uiDelegate_?.notify({result: state_, detail: detail})
              console.info(TAG, `User:${onUserLeave.object['uid']} leave.`)
            }
            break;
        }
      }
    }
  }

  join(login: LoginInfo): void {
    this.login = login
    let init: Init = { api: API.INIT, key: Config.APPKEY, level: NERtcConstants.LogLevel.INFO}
    __call_nertc__(init)
    if(login) {
      let join: Join = { api: API.JOIN, token: '', cname: login?.cname, uid: login?.uid }
      __call_nertc__(join)
    } else {
      uiDelegate_?.notify({result: state_, detail: 'Error: login is empty.'})
      return
    }

    let demoUser = new DemoUser(BigInt(login?.uid), login?.uid)
    uiDelegate_?.update(OPERATOR.ADD, demoUser)
    console.info(TAG, "=== Invoke join End. ===")
  }

  attach(user: DemoUser): void {
    let isMe = user.uid.toString() === this.login?.uid
    let setup: SetUp = { api: API.SETUP, uid: user.uid.toString(), xComponentId: user.xComponentId, isMe: isMe }
    __call_nertc__(setup)
  }

  release() {
    __call_nertc__({ api: API.LEAVE })
    __call_nertc__({ api: API.RELEASE })
  }
}

function __call_nertc__(data: NERtcData): void {
  worker_.postMessage(data)
}


