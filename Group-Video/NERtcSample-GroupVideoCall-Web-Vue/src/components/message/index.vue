<template>
    <div
        :class="`message ${show?'active':''}`"
        ref="message"
    >
        <span class="icon"></span>
        <p>{{content}}</p>
    </div>
</template>

<script>
    export default {
        name: 'message',
        props: {
            content: { // 提示信息
                type: String,
                default: ''
            },
            duration: { // 显示时间
                type: Number,
                default: 2000
            }
        },
        data () {
            return {
                show: false
            }
        },
        mounted () {
            setTimeout(() => {
                this.show = true
                setTimeout(() => {
                    this.destory()
                }, this.duration)
            }, 20)
        },
        methods: {
            destory () {
                this.show = false
                setTimeout(() => { // css动画200ms
                    this.$refs.message.remove()
                }, 200)
            }
        }
    }
</script>

<style scoped lang="less">
    .message {
        display: flex;
        align-items: center;
        height: 40px;
        padding: 0 16px;
        background: #FFFFFF;
        border: 1px solid #EBEDF0;
        box-shadow: 0 2px 6px 0 rgba(23, 23, 26, 0.10);
        border-radius: 2px;
        position: fixed;
        left: 50%;
        top: 20px;
        transform: translate(-50%, -30px);
        opacity: 0;
        transition: all .2s;

        &.active {
            transform: translate(-50%, 0);
            opacity: 1;
        }

        .icon {
            display: block;
            width: 14px;
            height: 14px;
            margin-right: 8px;
            background: url("../../assets/img/icon/error.png") no-repeat center;
            background-size: 14px;
        }

        p {
            font-family: PingFangSC-Regular;
            font-size: 14px;
            color: #333333;
            letter-spacing: 0;
            white-space: nowrap;
        }
    }
</style>
