import axios from 'axios'

let instance = axios.create()

instance.interceptors.request.use(
    config => {
        console.log("axios request");
        //config.headers['token'] = '123456';
        //config.headers.uid = "";

        return config;
    },
    err => {
        return Promise.reject(err)
    })


instance.interceptors.response.use(
    response => {
        /*//拦截响应，做统一处理
        if (response.data.code) {
            switch (response.data.code) {
                case 1000:

            }
        }*/
        return response
    },
    //接口错误状态处理，也就是说无响应时的处理
    error => {
        return Promise.reject(error.response.status) // 返回接口返回的错误信息
    })


export default instance;