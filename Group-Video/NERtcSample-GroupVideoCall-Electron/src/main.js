import Vue from 'vue'
import App from './App.vue'
import router from './router'
import store from './store'
import Element from 'element-ui'
import axios from './api/axios'
import 'element-ui/lib/theme-chalk/index.css'

if (!process.env.IS_WEB) Vue.use(require('vue-electron'))
//Vue.http = Vue.prototype.$http = axios
Vue.prototype.$axios = axios;
Vue.config.productionTip = false
Vue.use(Element)

Vue.config.productionTip = false

new Vue({
  render: h => h(App),
  router,
  data: store,
}).$mount('#app')
