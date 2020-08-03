<template>
    <div class="home">
        <div class="content">
            <!--画面div-->
            <div class="main-window" ref='large' @click="swapPlaces"></div>
            <!--小画面div-->
            <div class="sub-window" ref='small' @click="swapPlaces">
                <span class="loading-text" v-show='isDesc'>{{desc}}</span>
            </div>
        </div>
        <!--底层栏-->
        <ul class="tab-bar">
            <li :class="{silence:true, isSilence}" @click="setOrRelieveSilence"></li>
            <li class="over" @click="handleOver"></li>
            <li :class="{stop:true,isStop}" @click="stopOrOpenVideo"></li>
        </ul>
    </div>
</template>
<script src="https://unpkg.com/axios/dist/axios.min.js"></script>
<script>

    import { message } from '../../components/message'
    import WebRTC2 from '../../NIM_Web_WebRTC2_v3.6.0.js'

    export default {
        name: 'home',
        data () {
            return {
                isSilence: false,
                isDesc: true,
                isStop: false,
                desc: '等待对方进入...',
                appkey: '',
                token: '',
                client: null,
                localUid: Math.ceil(Math.random() * 1e5),
                localStream: null,
                remoteStream: null
            }
        },
        mounted () {
            // 初始化音视频实例
            console.log('初始化音视频sdk')
            window.self = this
            this.client = WebRTC2.createClient({
                appkey: this.appkey,
                debug: true
            })
            //监听事件
            this.client.on('peer-online', evt => {
                console.warn(`${evt.uid} 加入房间`)
            })

            this.client.on('peer-leave', evt => {
                console.warn(`${evt.uid} 离开房间`)
                if (this.remoteStream.getId() === evt.uid) {
                    this.remoteStream = null
                    this.isDesc = true
                    this.desc = '对方离开房间了'
                    message(this.desc)
                    preprocessingDiv()
                }
            })

            this.client.on('stream-added', evt => {
                var remoteStream = evt.stream;
                console.warn('收到对方发布的订阅消息: ', remoteStream.getId())

                if (this.remoteStream && this.remoteStream.getId() !== remoteStream.getId()) {
                    console.warn('房间里第三个人加入，忽略')
                    return
                } else {
                    this.remoteStream = remoteStream
                }
                this.subscribe(remoteStream)
            })

            this.client.on('stream-removed', evt => {
                var remoteStream = evt.stream;
                console.warn('对方停止订阅: ', remoteStream.getId())
                this.preprocessingDiv()
                remoteStream.stop()
            })

            this.client.on('stream-subscribed', evt => {
                console.warn('收到了对端的流，准备播放')
                const remoteStream = evt.stream;
                //用于播放对方视频画面的div节点
                this.isDesc = false
                const div = this.$refs.small
                remoteStream.play(div).then(() => {
                    console.log('播放视频')
                    remoteStream.setRemoteRenderMode({ // 设置视频窗口大小
                        width: 160,
                        height: 90,
                        cut: false // 是否裁剪
                    })
                }).catch(err => {
                    console.log('播放对方视频失败了: ', err)
                })
            })
            this.joinChannel()
        },
        methods: {
            returnJoin(time = 2000) {
                setTimeout(() => {
                    this.$router.push({
                        path: '/'
                    })
                }, time)
            },

            joinChannel () {
                if (!this.client) {
                    message('内部错误，请重新加入房间')
                    return
                }
                console.info('开始加入房间: ', this.$route.query.channelName)
                this.client.join({
                    channelName: this.$route.query.channelName,
                    uid: this.localUid,
                    token: this.token
                }).then( data => {
                    console.info('加入房间成功，开始初始化本地音视频流')
                    this.initLocalStream()
                }).catch(error => {
                    console.error('加入房间失败：', error)
                    message(`${error}: 请检查appkey或者token是否正确`)
                    this.returnJoin()
                })
            },

            initLocalStream () {
                //初始化本地的Stream实例，用于管理本端的音视频流
                this.localStream = WebRTC2.createStream({
                    uid: this.localUid,
                    audio: true, //是否启动mic
                    video: true, //是否启动camera
                    screen: false, //是否启动屏幕共享
                })

                //设置本地视频质量
                this.localStream.setVideoProfile({
                    resolution: WebRTC2.VIDEO_QUALITY_720p, //设置视频分辨率
                    frameRate: WebRTC2.CHAT_VIDEO_FRAME_RATE_15 //设置视频帧率
                })
                //设置本地音频质量
                this.localStream.setAudioProfile('speech_low_quality')
                //启动媒体，打开实例对象中设置的媒体设备
                this.localStream.init().then(() => {
                    console.warn('音视频开启完成，可以播放了')
                    const div = self.$refs.large
                    this.localStream.play(div)
                    this.localStream.setLocalRenderMode({ // 设置视频窗口大小
                        width: div.clientWidth,
                        height: div.clientHeight,
                        cut: true // 是否裁剪
                    })
                    // 发布
                    this.publish()
                }).catch(err => {
                    console.warn('音视频初始化失败: ', err)
                    message('音视频初始化失败')
                    this.localStream = null
                })
            },
            publish () {
                console.warn('开始发布视频流')
                //发布本地媒体给房间对端
                this.client.publish(this.localStream).then(() => {
                    console.warn('本地 publish 成功')
                }).catch(err => {
                    console.error('本地 publish 失败: ', err)
                    message('本地 publish 失败')
                })
            },
            subscribe () {
                this.remoteStream.setSubscribeConfig({
                    audio: true,
                    video: true
                })
                this.client.subscribe(this.remoteStream).then(() => {
                    console.log('本地 subscribe 成功')
                }).catch(err => {
                    console.log('本地 subscribe 失败: ', err)
                    message('订阅对方的流失败')
                })
            },
            setOrRelieveSilence () {
                const { isSilence } = this
                this.isSilence = !isSilence
                if (this.isSilence) {
                    console.log('关闭mic')
                    this.localStream.close({
                        type: 'audio'
                    }).then(() => {
                        console.log('关闭 mic sucess')
                    }).catch(err => {
                        console.log('关闭 mic 失败: ', err)
                        message('关闭 mic 失败')
                    })
                } else {
                    console.log('打开mic')
                    if (!this.localStream) {
                        message('当前不能打开mic')
                        return
                    }
                    this.localStream.open({
                        type: 'audio'
                    }).then(() => {
                        console.log('打开mic sucess')
                    }).catch(err =>{
                        console.log('打开mic失败: ', err)
                        message('打开mic失败')
                    })
                }
            },
            stopOrOpenVideo () {
                const { isStop } = this
                this.isStop = !isStop
                if (this.isStop) {
                    console.log('关闭摄像头')
                    this.preprocessingDiv()
                    this.localStream.close({
                        type: 'video'
                    }).then(()=>{
                        console.log('关闭摄像头 sucess')
                    }).catch(err =>{
                        console.log('关闭摄像头失败: ', err)
                        message('关闭摄像头失败')
                    })
                } else {
                    console.warn('打开摄像头')
                    if (!this.localStream) {
                        message('当前不能打开camera')
                        return
                    }
                    this.localStream.open({
                        type: 'video'
                    }).then(() => {
                        console.log('打开摄像头 sucess')
                        const div = self.$refs.large
                        this.localStream.play(div)
                        this.localStream.setLocalRenderMode({ // 设置视频窗口大小
                            width: div.clientWidth,
                            height: div.clientHeight,
                            cut: true // 是否裁剪
                        })
                    }).catch(err =>{
                        console.log('打开摄像头失败: ', err)
                        message('打开摄像头失败')
                    })
                }
            },
            handleOver () {
                console.log('离开房间')
                this.client.leave()
                this.returnJoin(1)
            },
            swapPlaces () {
                console.warn('交换视频窗口')
                if (this.$refs.large.children && this.$refs.large.children.length && this.$refs.small.children.length > 1) {
                    /*this.$refs.small.lastElementChild.lastElementChild.srcObject = [this.$refs.large.lastElementChild.lastElementChild.srcObject , this.$refs.large.lastElementChild.lastElementChild.srcObject = this.$refs.small.lastElementChild.lastElementChild.srcObject][0]*/
                    const smallDiv = this.$refs.small.lastElementChild
                    const largeDiv = this.$refs.large.lastElementChild
                    const smallDIvUid = smallDiv.lastElementChild.dataset.uid
                    const largeDIvUid = largeDiv.lastElementChild.dataset.uid
                    console.warn('localStream uid： %s, largeDIvUid: %s, smallDIvUid: %s', this.localStream.getId(), largeDIvUid, smallDIvUid)
                    if (smallDIvUid == this.localStream.getId() || smallDIvUid == 'local') {
                        this.localStream.setLocalRenderMode({ // 设置视频窗口大小
                            width: this.$refs.large.clientWidth,
                            height: this.$refs.large.clientHeight,
                            cut: true // 是否裁剪
                        })
                        this.remoteStream.setRemoteRenderMode({
                            width: this.$refs.small.clientWidth,
                            height: this.$refs.small.clientHeight,
                            cut: true // 是否裁剪
                        })
                    } else {
                        this.localStream.setLocalRenderMode({ // 设置视频窗口大小
                            width: this.$refs.small.clientWidth,
                            height: this.$refs.small.clientHeight,
                            cut: true // 是否裁剪
                        })
                        this.remoteStream.setRemoteRenderMode({
                            width: this.$refs.large.clientWidth,
                            height: this.$refs.large.clientHeight,
                            cut: true // 是否裁剪
                        })
                    }
                    this.$refs.large.removeChild(largeDiv)
                    this.$refs.small.removeChild(smallDiv)
                    this.$refs.large.appendChild(smallDiv)
                    this.$refs.small.appendChild(largeDiv)
                }
            },
            preprocessingDiv () {
                //为了防止关闭摄像头时，清除不对的div
                const largeDIvUid = this.$refs.large.children && this.$refs.large.children.length ? this.$refs.large.lastElementChild.lastElementChild.dataset.uid : null
                const smallDIvUid = this.$refs.small.children.length > 1 ? this.$refs.small.lastElementChild.lastElementChild.dataset.uid : null
                console.warn('本地的uid： %s, largeDIvUid: %s, smallDIvUid: %s', this.localStream.getId(), largeDIvUid, smallDIvUid)
                //上面的代码可知，默认本端添加的是large的div，远端添加的是small的div
                if (this.localStream.getId() != largeDIvUid && largeDIvUid != 'local' ) {
                    console.warn('把远端放到小的div里面，本端放到大的div里面')
                    this.swapPlaces()
                }
            }
        }
    }
</script>

<style scoped lang="less">
    @import './index';
</style>
