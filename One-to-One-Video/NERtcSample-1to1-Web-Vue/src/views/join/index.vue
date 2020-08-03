<template>
    <div class="join">
        <div class="content">
            <img src="../../assets/img/logo.png" alt="" class="logo">
            <input
                type="text"
                v-model.trim="channelName"
                placeholder="请输入房间号"
            >
            <button class="submit-btn" @click="handleSubmit">加入频道</button>
        </div>
    </div>
</template>

<script>
    import { message } from '../../components/message'

    export default {
        name: 'join',
        data () {
            return {
                channelName: ''
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
                this.$router.push({
                    path: '/home',
                    query: { channelName }
                })
            }
        }
    }

</script>

<style scoped lang="less">
    @import "./index";

</style>
