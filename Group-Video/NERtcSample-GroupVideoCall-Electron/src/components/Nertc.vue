<template>
  <div>
    <el-row>
      <el-col :span="16" style="width: 850px">
        <el-row>
          <el-form :inline="true">
            <el-form-item label="app_key">
              <el-input size="small" v-model.trim="app_key" style="width: 150px height: 32px" placeholder="请输入appkey" clearable></el-input>
            </el-form-item>
            <el-form-item label="房间名">
              <el-row>
                <el-col :span="20">
                  <el-input :maxlength="64" class="home_input" size="small" v-model="channelName" clearable></el-input>
                </el-col>
              </el-row>
            </el-form-item>
            <el-form-item label="用户ID">
              <el-row>
                <el-col :span="20">
                  <el-input class="home_input" size="small" v-model="uid" clearable></el-input>
                </el-col>
              </el-row>
            </el-form-item>
          </el-form>
        </el-row>
        <el-row>
          <el-form :inline="true">
            <el-form-item>
              <el-button class="home_input" size="small" @click="init" style="width: 100px">初始化SDK</el-button>
            </el-form-item>
            <el-form-item>
                <el-button size="small" @click="onJoinChannel">加入房间</el-button>
            </el-form-item>
            <el-form-item>
                <el-button size="small" @click="onLeaveChannel">离开房间</el-button>
            </el-form-item>
          </el-form>
        </el-row>
        <el-row>
          <div>
            <el-form id="login" :inline="true">
              <el-form-item>
                <el-button size="small" @click="onStartPreview">开始预览</el-button>
              </el-form-item>
              <el-form-item>
                <el-button size="small" @click="onStopPreview">停止预览</el-button>
              </el-form-item>
              <el-form-item>
                <el-checkbox v-model="autoOpenRecord">自动开音频</el-checkbox>
              </el-form-item>
              <el-form-item>
                <el-checkbox v-model="autoSubRecord">自动订音频</el-checkbox>
              </el-form-item>
              <el-form-item>
                <el-checkbox v-model="autoOpenVideo">自动开视频</el-checkbox>
              </el-form-item>
              <el-form-item>
                <el-checkbox v-model="autoSubVideo">强制订视频</el-checkbox>
              </el-form-item>
            </el-form>
          </div>
        </el-row>
        <el-row>
          <el-form :inline="true">
            <el-form-item>
              <el-checkbox v-model="safeModel">安全模式</el-checkbox>
            </el-form-item>
            <el-form-item>
              <el-checkbox v-model="muteVideo" @change="onMuteVideo">停视频</el-checkbox
              >
            </el-form-item>
            <el-form-item>
              <el-checkbox v-model="muteAudio" @change="onMuteAudio">静音语音</el-checkbox
              >
            </el-form-item>
          </el-form>
        </el-row>
        <el-row>
          <div>屏幕共享参数：</div>
        </el-row>
        <el-row>
          <el-form :inline="true" v-model="screenForm">
            <el-form-item label="窗口">
              <el-row>
                <el-col :span="20">
                  <el-select class="home_input" size="small" @visible-change='onRefreshWindowList' v-model="curSelectedCaptureId">
                    <el-option  v-for="item in windowsList" :key="item.id" :label="item.name" :value="item.id"></el-option>
                  </el-select>
                </el-col>
              </el-row>
            </el-form-item>
          </el-form>
        </el-row>
        <el-row>
          <el-form :inline="true">
            <el-form-item>
              <el-button size="small" @click="onStartScreenCapture">开始共享窗口/屏幕</el-button
              >
            </el-form-item>
            <el-form-item>
              <el-button size="small" @click="onStartScreenCaptureRect">开始共享区域</el-button
              >
            </el-form-item>
            <el-form-item>
              <el-button size="small" @click="onPauseScreenCapture">暂停共享</el-button
              >
            </el-form-item>
            <el-form-item>
              <el-button size="small" @click="onResumeScreenCapture">恢复共享</el-button>
            </el-form-item>
            <el-form-item>
              <el-button size="small" @click="onStopScreenCapture">结束共享</el-button>
            </el-form-item>
          </el-form>
        </el-row>
        <p v-show="remoteSubViewList.length > 0">远端用户共享:</p>
        <el-row v-for="item in remoteSubViewList" v-bind:key="item.uid">
          <el-col :span="24">
            <p>{{ item.uid }}</p>
            <div
              :id="item.uid" style=" background-color: rgb(0, 0, 0) width: 480px height: 320px"/>
          </el-col>
        </el-row>
      </el-col>
      <el-col :span="8">
        <el-row>
          <el-col :span="24">
            <p>本地预览</p>
            <div id="localView" style=" background-color: rgb(0, 0, 0) width: 480px height: 320px"/>
          </el-col>
        </el-row>
        <el-row>
          <el-col :span="24">
            <p>本地屏幕共享</p>
            <div id="captureView" style=" background-color: rgb(0, 0, 0) width: 480px  height: 320px"/>
          </el-col>
        </el-row>
        <p v-show="remoteViewList.length > 0">远端视频：</p>
        <el-row v-for="item in remoteViewList" v-bind:key="item.uid">
          <el-col :span="24">
            <p>{{ item.uid }}</p>
            <div :id="setRemoteViewId(item.uid)" style=" background-color: rgb(0, 0, 0) width: 480px height: 320px"/>
          </el-col>
        </el-row>
      </el-col>
    </el-row>
  </div>
</template>

<script>
import store from "../store"
import utils from "../api/utils"

const KNOERROR = 0
const { desktopCapturer } = require("electron")
const separtor = ":"

export default {
  name: "home",
  data() {
    return {
      initSDK: false,
      isJoinChannel: false,
      nertcEngine: null,
      app_key: "",
      testDemoServer: false,
      channelName: "",
      uid: "", 
      token: "",
      safeModel: true,
      muteVideo: false,
      muteAudio: false,
      autoOpenRecord: true,
      autoSubRecord: true,
      autoOpenVideo: true,
      autoSubVideo: true,
      remoteViewList: [],
      remoteSubViewList: [],
      curSelectedCaptureId: "",
      windowsList: [],
      thumbWidth: "320",
      thumbHeight: "180",
      iconWidth: "32",
      iconHeight: "32",
      timer: null,
      screenForm: {
        srX: "",
        srY: "",
        srWidth: "",
        srHeight: "",
        rrX: "",
        rrY: "",
        rrWidth: "",
        rrHeight: "",
        screenShareProfile: 2,
        dimensionsW: "",
        dimensionsH: "",
        frameRate: "",
        bitrate: "",
        captureMouseCursor: true,
        excludedWindowCount: "",
        excludedWindowList: "",
        prefer: "",
      },
      screenShareProfileList: [
        { label: "640x480", value: 0 },
        { label: "1280x720", value: 1 },
        { label: "1920x1080", value: 2 },
        { label: "自定义", value: 3 },
      ],
      screenProfileCustomW: 1280,
      screenProfileCustomH: 720,
      preferList: [
        { label: "动画模式", value: 0 },
        { label: "细节模式", value: 1 },
      ],
    }
  },

  methods: {
    setRemoteViewId(id) {
      return id
    },
    async getToken() {
      let data = {}
      let demoServer = 'https://nrtc.netease.im/demo/getChecksum.action'
      await this.$axios
        .post(demoServer + "?uid=" + this.uid + "&appkey=" + this.app_key, data,
          {
            header: {
              "Content-Type": "application/x-www-form-urlencodedcharset=utf-8",
            },
          }
        ).then((res) => {
          if (res.data.code !== 200) {
            this.$message.error(`请求token失败，errorCode:${res.code}`)
            return
          }
          this.token = res.data.checksum
          return
        }).catch((e) => {
          this.$message.error(`请求token异常，e:${e}`)
        })
    },
    checkAppKey() {
      if (this.app_key === "") {
        this.$message.error("请输入正确的appKey")
        return false
      }
      return true
    },
    init() {
      if (this.initSDK) {
        return
      }
      if (!this.checkAppKey()) {
        return
      }

      //初始化sdk
      this.nertcEngine = store.state.nertcEngine
      let context = {}
      context.app_key = this.app_key
      context.log_level = 3
      context.log_dir_path = './'
      context.log_file_max_size_KBytes = 0
      let ret = this.nertcEngine.initialize(context)
      console.log(`initialize::ret = ${ret}`)
      if (KNOERROR != ret) {
        this.$message.error(`sdk初始化失败, code:${ret}`)
        return
      }

      //设置本地视频画布
      let canvas = {}
      canvas.view = document.getElementById("localView")
      canvas.mode = 0
      ret = this.nertcEngine.setupLocalVideoCanvas(canvas)
      console.log(`setupLocalVideoCanvas::ret:${ret}`)
      if (KNOERROR != ret) {
        this.$message.error(`本地预览画布设置失败, code:${ret}`)
        return
      }

      //注册sdk回调接口
      this.initEvents()
      this.initSDK = true
      this.$message.success("sdk初始化成功。")
    },
    unInit() {
      this.remoteViewList = []
      this.remoteSubViewList = []
      this.nertcEngine.enableLocalAudio(false)
      this.nertcEngine.enableLocalVideo(false)
      this.nertcEngine.leaveChannel()
      this.nertcEngine.release()
    },
    async onJoinChannel() {
      console.log("onJoinChannel::start")
      if (!this.initSDK) {
        this.$message.error("请先初始化sdk。")
        return
      }
      if (this.safeModel) {
        await this.getToken()
      } else {
        this.token = "" //非安全模式下token可以为空，安全模式下token不能为空
      }
      let pattern = /^[a-zA-Z0-9 ,!#$%&()+-:≤.,>? @\[\]^_{|}~”]+$/
      if (!pattern.test(this.channelName)) {
        this.$message.error(
          `通道名仅支持以下字符：a-zA-Z0-9,!#$%&()+-:≤.,>? @[]^_{|}~"空格,且最长支持64个字符。`
        )
        return
      }
      let ret = this.nertcEngine.setLocalVideoMirrorMode(1)
      ret = this.nertcEngine.enableDualStreamMode(true)
      ret = this.nertcEngine.enableLocalVideo(this.autoOpenVideo)
      ret = this.nertcEngine.enableLocalAudio(this.autoOpenRecord)
      ret = this.nertcEngine.joinChannel(
        this.token,
        this.channelName,
        parseInt(this.uid)
      )
      if (KNOERROR != ret) {
        this.$message.error(`加入房间失败, code:${ret}`)
        return
      }
      this.isJoinChannel = true
      console.log("onJoinChannel::end")
    },
    onLeaveChannel() {
      console.log("onLeaveChannel")
      this.remoteViewList = []
      this.remoteSubViewList = []
      let ret = 0
      ret = this.nertcEngine.enableLocalAudio(false)
      ret = this.nertcEngine.enableLocalVideo(false)
      ret = this.nertcEngine.leaveChannel()
      this.isJoinChannel = false
    },
    onStartPreview() {
      if (this.isJoinChannel) {
        let ret = this.nertcEngine.enableLocalVideo(true)
      } else {
        return new Promise((resolve, reject) =>{
          let videoDeviceList = this.nertcEngine.enumerateVideoCaptureDevices()
          resolve(videoDeviceList)
        }).then((videoDeviceList) =>{
          this.nertcEngine.setVideoDevice(videoDeviceList[0].device_id)
        }).then(()=>{
           this.nertcEngine.startVideoPreview()
        })
      }
    },
    onStopPreview() {
      if (this.isJoinChannel) {
        let ret = this.nertcEngine.enableLocalVideo(false)
        console.log(`enableLocalVideo::ret:${ret}`)
      } else {
        let ret = this.nertcEngine.stopVideoPreview()
        console.log(`stopVideoPreview::ret:${ret}`)
      }
    },
    onStartScreenCapture() {
      this.onStopScreenCapture()
      this.startScreenCaptureByWindowId()
    },

    onStartScreenCaptureRect() {
      if (!this.isJoinChannel) {
        this.$message.error("请先加入房间。")
        return
      }
      let canvas = {}
      canvas.view = document.getElementById("captureView")
      canvas.mode = 0
      let ret = this.nertcEngine.setupLocalSubStreamVideoCanvas(canvas)
      console.log(`setupLocalSubStreamVideoCanvas::ret:${ret}`)
      let screenRect = {}
      let regionRect = {}
      screenRect.x = parseInt(this.screenForm.srX)
      screenRect.y = parseInt(this.screenForm.srY)
      screenRect.width = parseInt(this.screenForm.srWidth)
      screenRect.height = parseInt(this.screenForm.srHeight)

      //可选参数和screenRect设置其一即可
      regionRect.x = NaN//parseInt(this.screenForm.rrX)
      regionRect.y = NaN//parseInt(this.screenForm.rrY)
      regionRect.width = NaN//parseInt(this.screenForm.rrWidth)
      regionRect.height = NaN//parseInt(this.screenForm.rrHeight)

      let param = {}
      param.dimensions = {}
      this.getSelCaptureParameter(
        this.screenForm.screenShareProfile,
        param.dimensions.width,
        param.dimensions.height
      )
      param.frame_rate = parseInt(this.screenForm.frameRate)
      param.bitrate = parseInt(this.screenForm.bitrate)
      param.capture_mouse_cursor = this.screenForm.captureMouseCursor
      param.excluded_window_count = parseInt(
        this.screenForm.excludedWindowCount
      )
      if (param.excluded_window_count > 0) {
        param.excluded_window_list = JSON.parse(
          this.screenForm.excludedWindowList
        )
      }
      param.prefer = parseInt(this.screenForm.prefer)
      ret = this.nertcEngine.startScreenCaptureByScreenRect(
        screenRect,
        regionRect,
        param
      )
      console.log(`startScreenCaptureByScreenRect::ret:${ret}`)
      if (KNOERROR != ret) {
        this.$message.error(`开启屏幕共享失败, code:${ret}`)
        return
      }
    },

    //共享窗口/屏幕
    startScreenCaptureByWindowId() {
      if (!this.isJoinChannel) {
        this.$message.error("请先加入房间。")
        return
      }
      let canvas = {}
      canvas.view = document.getElementById("captureView")
      canvas.mode = 0
      let ret = this.nertcEngine.setupLocalSubStreamVideoCanvas(canvas)
      console.log(`setupLocalSubStreamVideoCanvas::ret:${ret}`)

      let regionRect = {}
      regionRect.x = NaN//parseInt(this.screenForm.rrX)
      regionRect.y = NaN//parseInt(this.screenForm.rrY)
      regionRect.width = NaN//parseInt(this.screenForm.rrWidth)
      regionRect.height = NaN//parseInt(this.screenForm.rrHeight)

      let param = {}
      param.profile = parseInt(this.screenForm.screenShareProfile)
      param.dimensions = {}
      param.dimensions.width = parseInt(this.dimensionsW)
      param.dimensions.height = parseInt(this.dimensionsH)
      this.getSelCaptureParameter(
        this.screenForm.screenShareProfile,
        param.dimensions.width,
        param.dimensions.height
      )
      param.frame_rate = parseInt(this.screenForm.frameRate)
      param.bitrate = parseInt(this.screenForm.bitrate)
      param.capture_mouse_cursor = this.screenForm.captureMouseCursor
      param.excluded_window_count = parseInt(
        this.screenForm.excludedWindowCount
      )
      if (param.excluded_window_count > 0) {
        param.excluded_window_list = JSON.parse(
          this.screenForm.excludedWindowList
        )
      }
      param.prefer = parseInt(this.screenForm.prefer)
      let captureType = this.curSelectedCaptureId.split(":")[0]
      let windowId = this.curSelectedCaptureId.split(":")[1]
      if ("screen" === captureType) {
        this.nertcEngine.startScreenCaptureByDisplayId(
          parseInt(windowId),
          regionRect,
          param
        )
      } else {
        this.nertcEngine.startScreenCaptureByWindowId(
          parseInt(windowId),
          regionRect,
          param
        )
      }
    },

    //转换共享参数
    getSelCaptureParameter(profile, dimensionsW, dimensionsH) {
      switch (profile) {
        case 0:
          dimensionsW = 640
          dimensionsH = 480
          this.screenForm.frameRate = 5
          break
        case 1:
          dimensionsW = 1280
          dimensionsH = 720
          this.screenForm.frameRate = 5
          break
        case 2:
          dimensionsW = 1920
          dimensionsH = 1080
          this.screenForm.frameRate = 5
          break
        case 3:
          dimensionsW = this.screenProfileCustomW
          dimensionsH = this.screenProfileCustomH
          break
        default:
          dimensionsW = 1920
          dimensionsH = 1080
          this.screenForm.frameRate = 5
          break
      }
    },

    //停止共享
    onStopScreenCapture() {
      let ret = this.nertcEngine.stopScreenCapture()
      console.log(`stopScreenCapture::ret:${ret}`)
    },

    //暂停共享
    onPauseScreenCapture() {
      let ret = this.nertcEngine.pauseScreenCapture()
      console.log(`pauseScreenCapture::ret:${ret}`)
    },

    //恢复共享
    onResumeScreenCapture() {
      let ret = this.nertcEngine.resumeScreenCapture()
      console.log(`resumeScreenCapture::ret:${ret}`)
    },

    //刷新窗口id列表
    onRefreshWindowList() {
      this.windowsList = []

      if (process.platform === "win32") {
        console.log("process platform is win32")
        let windInfoList = this.nertcEngine.enumerateScreenCaptureSourceInfo(
          parseInt(this.thumbWidth),
          parseInt(this.thumbHeight),
          parseInt(this.iconWidth),
          parseInt(this.iconHeight)
        )
        for (let i = 0; i < windInfoList.length; ++i) {
          let srcinfo = windInfoList[i]
          const captureType = srcinfo.displayId ? "screen" : "window"
          const sid = srcinfo.displayId || srcinfo.sourceId.toString()
          this.windowsList.push({
            id: captureType + separtor + sid + ":0",
            name: srcinfo.sourceName,
            display_id: srcinfo.displayId,
            thumbnail: srcinfo.thumbBGRA,
            appIcon: srcinfo.iconBGRA,
          })
        }
        console.log("windowsList = " + this.windowsList)
      } else {
        desktopCapturer
          .getSources({
            types: ["window", "screen"],
            thumbnailSize: { width: 320, height: 180 },
            fetchWindowIcons: true,
          })
          .then(async (windInfoList) => {
            if (windInfoList.length > 0) {
              for (let i = 0; i < windInfoList.length; ++i) {
                let it = windInfoList[i]
                this.windowsList.push({
                  id: it.id,
                  name: it.name,
                })
              }
              console.log(`windowsList:${this.windowsList}`)
            }
          })
      }
    },

    //停止视频流发送
    onMuteVideo() {
      if (!this.isJoinChannel) {
        return
      }
      this.nertcEngine.muteLocalVideoStream(this.muteVideo)
    },

    //停止音频发送
    onMuteAudio() {
      if (!this.isJoinChannel) {
        return
      }
      this.nertcEngine.muteLocalAudioStream(this.muteAudio)
    },

    //向sdk注册回调,用于接受sdk信息
    initEvents() {
      console.log(`initEvent start::nertcEngine:${this.nertcEngine}`)
      if (this.nertcEngine == null) return

      this.nertcEngine.on("onError", (errorCode, msg) => {
        console.log(`onError res::errorCode:${errorCode} msg:${msg}`)
      })
      this.nertcEngine.on("onWarning", (warnCode, msg) => {})
      this.nertcEngine.on("onReleasedHwResources", (result) => {})
      this.nertcEngine.on("onJoinChannel", (cid, uid, result, elapsed) => {
        console.log(`onJoinChannel::uid:${uid}`)
      })

      this.nertcEngine.on("onLeaveChannel", (result) => {
        this.remoteViewList = []
        this.remoteSubViewList = []
      })

      this.nertcEngine.on("onUserJoined", (uid, userName) => {
        console.log(`onUserJoined uid:${uid}`)
        if (!this.autoSubVideo) {
          return
        } //未订视频时，不订阅

        let index = -1
        index = this.remoteViewList.findIndex((item) => {
          if (item.uid === uid) {
            return true
          }
        })
        if (index === -1) {
          this.remoteViewList.push({ uid: uid })
        }
        this.$nextTick(() => {
          let canvas = {}
          console.log(`getElementById::uid${uid}`)
          canvas.view = document.getElementById(uid)
          canvas.mode = 0
          let ret = this.nertcEngine.setupRemoteVideoCanvas(uid, canvas)
          console.log(`setupRemoteVideoCanvas::ret:${ret}`)
        })
      })

      this.nertcEngine.on("onUserVideoStart", (uid, maxProfile) => {
        if (!this.autoSubVideo) {
          return
        } //未订视频时，不订阅
        console.log(`onUserVideoStart::uid:${uid}`)
        let ret = this.nertcEngine.subscribeRemoteVideoStream(uid, 0, true)
        console.log(`subscribeRemoteVideoStream::ret:${ret}`)
      })

      this.nertcEngine.on("onUserVideoStop", (uid) => {
        console.log(`onUserVideoStop uid:${uid}`)
        for (let i = 0; i < this.remoteViewList.length; ++i) {
          let it = this.remoteViewList[i]
          if (it.uid == uid) {
            this.remoteViewList.splice(i, 1)
            break
          }
        }
      })

      this.nertcEngine.on("onUserSubStreamVideoStart", (uid, maxProfile) => {
        console.log(`onUserSubStreamVideoStart`)
        let index = -1
        for (let i = 0; i < this.remoteSubViewList.length; ++i) {
          let item = this.remoteSubViewList[i]
          if (item.uid == `SubStreamVideo:${uid}`) {
            index = i
            break
          }
        }
        if (index === -1) {
          this.remoteSubViewList.push({
            uid: `SubStreamVideo:${uid}`,
          })
        }

        this.$nextTick(() => {
          let canvas = {}
          console.log(`getElementById::uid:${uid}`)
          let id = "SubStreamVideo:" + uid
          canvas.view = document.getElementById(id)
          canvas.mode = 0
          this.nertcEngine.setupRemoteSubStreamVideoCanvas(uid, canvas)
          this.nertcEngine.subscribeRemoteVideoSubStream(uid, true)
        })
      })

      this.nertcEngine.on("onUserSubStreamVideoStop", (uid) => {
        for (let i = 0; i < this.remoteSubViewList.length; ++i) {
          let item = this.remoteSubViewList[i]
          if (item.uid == `SubStreamVideo:${uid}`) {
            this.remoteSubViewList.splice(i, 1)
            break
          }
        }
      })

      this.nertcEngine.on("onDisconnect", (result) => {})
      this.nertcEngine.on("onClientRoleChanged", (oldRole, newRole) => {})
      this.nertcEngine.on("onReconnectingStart", (cid, uid) => {})
      this.nertcEngine.on("onConnectionStateChange", (state, reason) => {})
      this.nertcEngine.on("onRejoinChannel", (cid, uid, result, elapsed) => {})
      this.nertcEngine.on("onUserLeft", (uid, reason) => {})
      this.nertcEngine.on("onUserAudioStart", (uid) => {})
      this.nertcEngine.on("onUserAudioStop", (uid) => {})
      this.nertcEngine.on("onRtcStats", (stats) => {})
      this.nertcEngine.on("onLocalAudioStats", (stats) => {})
      this.nertcEngine.on("onRemoteAudioStats", (uc, stats) => {})
      this.nertcEngine.on("onLocalVideoStats", (stats) => {})
      this.nertcEngine.on("onRemoteVideoStats", (uc, stats) => {})
      this.nertcEngine.on("onNetworkQuality", (uc, stats) => {})
      this.nertcEngine.on("onUserVideoProfileUpdate", (uid, maxProfile) => {})
      this.nertcEngine.on("onUserAudioMute", (uid, mute) => {})
      this.nertcEngine.on("onUserVideoMute", (uid, mute) => {})
      this.nertcEngine.on(
        "onAudioDeviceStateChanged",
        (deviceID, deviceType, deviceState) => {}
      )
      this.nertcEngine.on(
        "onAudioDefaultDeviceChanged",
        (deviceID, deviceType) => {}
      )
      this.nertcEngine.on(
        "onVideoDeviceStateChanged",
        (deviceID, deviceType, deviceState) => {}
      )
      this.nertcEngine.on("onFirstAudioDataReceived", (uid) => {})
      this.nertcEngine.on("onFirstVideoDataReceived", (uid) => {})
      this.nertcEngine.on("onFirstAudioFrameDecoded", (uid) => {})
      this.nertcEngine.on(
        "onFirstVideoFrameDecoded",
        (uid, width, height) => {}
      )
      this.nertcEngine.on(
        "onAudioMixingStateChanged",
        (state, errorCode) => {}
      )
      this.nertcEngine.on("onAudioMixingTimestampUpdate", (timestampMS) => {})
      this.nertcEngine.on("onAudioEffectFinished", (effectID) => {})
      this.nertcEngine.on("onLocalAudioVolumeIndication", (vol) => {})
      this.nertcEngine.on(
        "onRemoteAudioVolumeIndication",
        (vols, count, total) => {}
      )
      this.nertcEngine.on("onAddLiveStreamTask", (taskID, url, error) => {})
      this.nertcEngine.on("onUpdateLiveStreamTask", (taskID, url, error) => {})
      this.nertcEngine.on("onRemoveLiveStreamTask", (taskID, error) => {})
      this.nertcEngine.on("onLiveStreamState", (taskID, url, state) => {})
      this.nertcEngine.on("onAudioHowling", (howling) => {})
      this.nertcEngine.on("onReceSEIMsg", (uid, data) => {})
      console.log("initCallback complete. ")
    },
  },
  destroyed() {
    this.unInit()
  },
  beforeDestroy() {},
  mounted() {
    this.channelName = utils.randUid()
    this.uid = utils.randUid()
  },
}
</script>

<style scoped>
.home_input {
  width: 120px;
  height: 32px;
}

#login {
  max-width: 1200px;
}
</style>
