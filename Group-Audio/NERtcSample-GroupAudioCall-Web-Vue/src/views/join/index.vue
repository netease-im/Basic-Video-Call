<template>
    <div class="join">
        <div class="content">
            <img src="../../assets/img/logo.png" alt="" class="logo">
            <input
                type="text"
                v-model.trim="channelName"
                placeholder="请输入房间号"
            >
            <button :disabled="!isSupport" class="submit-btn" @click="handleSubmit">加入房间</button>
            <div class="errorMsg" v-show="!isSupport">当前浏览器不支持体验，建议下载安装最新chrome浏览器</div>
        </div>
    </div>
</template>

<script>
    import { message } from '../../components/message'
    import { checkBrowser } from '../../common'

    export default {
        name: 'join',
        data () {
            return {
                channelName: '',
                isSupport: true,
            }
        },
        mounted() {
            if (!checkBrowser('chrome') && !checkBrowser('safari')) {
                this.isSupport = false;
            }
        },
        methods: {
            handleSubmit () {
                const { channelName } = this
                if (!channelName) {
                    message('请输入房间号')
                    return
                } else if (!/^[0-9]{1,12}$/.test(channelName)) {
                    message('房间号为12位以内的数字');
                    return
                }
                const { path = 'single' } = this.$route.query
                this.$router.push({
                    path: `/${path}`,
                    query: { channelName }
                })
            }
        },
    }

</script>

<style scoped lang="less">
.join {
    height: 100vh;
    background: #F7F8FA;
    display: flex;
    align-items: center;
    justify-content: center;
    .content {
        width: 400px;
        height: 400px;
        padding-top: 60px;
        background: #fff;
        box-shadow: 0 4px 10px 0 rgba(47,56,111,0.1);
        border-radius: 8px;
        .logo {
            display: block;
            height: 55px;
            margin: 0 auto;
        }

        input {
            display: block;
            width: 315px;
            height: 44px;
            margin: 50px auto 40px;
            border: none;
            outline: medium;
            border-bottom: 1px solid #DCDFE5;
            font-family: PingFangSC-Regular;
            font-size: 17px;

            &::placeholder {
                color: #B0B6BE;
            }
        }

        .submit-btn {
            display: block;
            display: block;
            width: 315px;
            height: 50px;
            margin: 0 auto;
            border: none;
            outline: medium;
            background: #337EFF;
            border-radius: 25px;
            font-family: PingFangSC-Regular;
            font-size: 16px;
            color: #FFFFFF;
            cursor: pointer;
            &:active {
                background: darken(#337EFF, 5%);
            }
            &:disabled {
                background: #dddddd;
                cursor: not-allowed;
            }
        }

        .errorMsg {
            font-size: 14px;
            text-align: center;
            color: red;
            margin-top: 10px;
        }
    }
}

</style>
