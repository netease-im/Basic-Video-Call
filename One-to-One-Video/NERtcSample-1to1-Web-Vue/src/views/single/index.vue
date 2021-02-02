<template>
    <div class="wrapper">
        <div class="content">
            <!--画面div-->
            <div class="main-window" ref='large'></div>
            <!--小画面div-->
            <div class="sub-window" ref='small'>
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
<script>

    import { message } from '../../components/message'
    import WebRTC2 from '../../sdk/NIM_Web_WebRTC2_v3.9.1.js'
    import config from '../../../config'
    import { getToken } from '../../common'

    export default {
        name: 'single',
        data () {
            return {
                isSilence: false,
                isDesc: true,
                isStop: false,
                desc: '等待对方进入...',
                client: null,
                localUid: Math.ceil(Math.random() * 1e5),
                localStream: null,
                remoteStream: null
            }
        },
        mounted () {
            // 初始化音视频实例
            console.warn('初始化音视频sdk')
            window.self = this
            this.client = WebRTC2.createClient({
                appkey: config.appkey,
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
                remoteStream.stop()
            })

            this.client.on('stream-subscribed', evt => {
                console.warn('收到了对端的流，准备播放')
                const remoteStream = evt.stream;
                //用于播放对方视频画面的div节点
                this.isDesc = false
                const div = this.$refs.small
                remoteStream.play(div).then(() => {
                    console.warn('播放视频')
                    remoteStream.setRemoteRenderMode({ // 设置视频窗口大小
                        width: 160,
                        height: 90,
                        cut: false // 是否裁剪
                    })
                }).catch(err => {
                    console.warn('播放对方视频失败了: ', err)
                })
            })

            this.getToken().then(token => {
                this.joinChannel(token)
            }).catch(e => {
                message(e)
                console.error(e)
            })
        },
        destroyed() {
            try {
                this.localStream.destroy()
                WebRTC2.destroy()
            } catch (e) {
                // 为了兼容低版本，用try catch包裹一下
            }
        },
        methods: {
            getToken() {
                return getToken({
                    uid: this.localUid,
                    appkey: config.appkey,
                    appSecret: config.appSecret,
                    channelName: this.$route.query.channelName
                }).then(token => {
                    return token
                }, (e) => {
                    throw e;
                });
            },
            returnJoin(time = 2000) {
                setTimeout(() => {
                    this.$router.push({
                        path: '/'
                    })
                }, time)
            },
            joinChannel (token) {
                if (!this.client) {
                    message('内部错误，请重新加入房间')
                    return
                }
                console.info('开始加入房间: ', this.$route.query.channelName)
                this.client.join({
                    channelName: this.$route.query.channelName,
                    uid: this.localUid,
                    token,
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
                    console.warn('本地 subscribe 成功')
                }).catch(err => {
                    console.warn('本地 subscribe 失败: ', err)
                    message('订阅对方的流失败')
                })
            },
            setOrRelieveSilence () {
                const { isSilence } = this
                this.isSilence = !isSilence
                if (this.isSilence) {
                    console.warn('关闭mic')
                    this.localStream.close({
                        type: 'audio'
                    }).then(() => {
                        console.warn('关闭 mic sucess')
                    }).catch(err => {
                        console.warn('关闭 mic 失败: ', err)
                        message('关闭 mic 失败')
                    })
                } else {
                    console.warn('打开mic')
                    if (!this.localStream) {
                        message('当前不能打开mic')
                        return
                    }
                    this.localStream.open({
                        type: 'audio'
                    }).then(() => {
                        console.warn('打开mic sucess')
                    }).catch(err => {
                        console.warn('打开mic失败: ', err)
                        message('打开mic失败')
                    })
                }
            },
            stopOrOpenVideo () {
                const { isStop } = this
                this.isStop = !isStop
                if (this.isStop) {
                    console.warn('关闭摄像头')
                    this.localStream.close({
                        type: 'video'
                    }).then(() => {
                        console.warn('关闭摄像头 sucess')
                    }).catch(err => {
                        console.warn('关闭摄像头失败: ', err)
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
                        console.warn('打开摄像头 sucess')
                        const div = self.$refs.large
                        this.localStream.play(div)
                        this.localStream.setLocalRenderMode({ // 设置视频窗口大小
                            width: div.clientWidth,
                            height: div.clientHeight,
                            cut: true // 是否裁剪
                        })
                    }).catch(err => {
                        console.warn('打开摄像头失败: ', err)
                        message('打开摄像头失败')
                    })
                }
            },
            handleOver () {
                console.warn('离开房间')
                this.client.leave()
                this.returnJoin(1)
            }
        }
    }
</script>

<style scoped lang="less">
.wrapper {
    height: 100vh;
    background-image: linear-gradient(179deg, #141417 0%, #181824 100%);
    display: flex;
    flex-direction: column;

    .content {
        flex: 1;
        position: relative;

        .main-window {
            height: 100%;
            width: 67vh;
            //width: 37vw;
            //width: 427px;
            margin: 0 auto;
            background: #25252d;
        }

        .sub-window {
            width: 165px;
            height: 95px;
            background: #25252d;
            position: absolute;
            z-index: 9;
            right: 16px;
            top: 16px;
            border: 1px solid #FFFFFF;

            .loading-text {
                display: block;
                width: 100%;
                text-align: center;
                line-height: 90px;
                font-size: 12px;
                color: #fff;
                font-weight: 400;
            }
        }
    }

    .tab-bar {
        height: 54px;
        background-image: linear-gradient(180deg, #292933 7%, #212129 100%);
        box-shadow: 0 0 0 0 rgba(255, 255, 255, 0.30);
        list-style: none;
        display: flex;
        justify-content: center;
        align-items: center;
        color: #fff;

        li {
            height: 54px;
            width: 125px;
            cursor: pointer;
            //静音
            &.silence {
                background: url("../../assets/img/icon/silence.png") no-repeat center;
                background-size: 60px 54px;

                &:hover {
                    background: url("../../assets/img/icon/silence-hover.png") no-repeat center;
                    background-size: 60px 54px;
                }

                &:active {
                    background: url("../../assets/img/icon/silence-click.png") no-repeat center;
                    background-size: 60px 54px;
                }

                &.isSilence { //已经开启静音
                    background: url("../../assets/img/icon/relieve-silence.png") no-repeat center;
                    background-size: 60px 54px;

                    &:hover {
                        background: url("../../assets/img/icon/relieve-silence-hover.png") no-repeat center;
                        background-size: 60px 54px;
                    }

                    &:active {
                        background: url("../../assets/img/icon/relieve-silence-click.png") no-repeat center;
                        background-size: 60px 54px;
                    }
                }
            }

            //结束按钮
            &.over {
                background: url("../../assets/img/icon/over.png") no-repeat center;
                background-size: 68px 36px;

                &:hover {
                    background: url("../../assets/img/icon/over-hover.png") no-repeat center;
                    background-size: 68px 36px;
                }

                &:active {
                    background: url("../../assets/img/icon/over-click.png") no-repeat center;
                    background-size: 68px 36px;
                }
            }

            // 停止按钮
            &.stop {
                background: url("../../assets/img/icon/stop.png") no-repeat center;
                background-size: 60px 54px;

                &:hover {
                    background: url("../../assets/img/icon/stop-hover.png") no-repeat center;
                    background-size: 60px 54px;
                }

                &:active {
                    background: url("../../assets/img/icon/stop-click.png") no-repeat center;
                    background-size: 60px 54px;
                }

                //已经是停止状态
                &.isStop {
                    background: url("../../assets/img/icon/open.png") no-repeat center;
                    background-size: 60px 54px;

                    &:hover {
                        background: url("../../assets/img/icon/open-hover.png") no-repeat center;
                        background-size: 60px 54px;
                    }

                    &:active {
                        background: url("../../assets/img/icon/open-click.png") no-repeat center;
                        background-size: 60px 54px;
                    }
                }
            }
        }
    }
}
</style>
