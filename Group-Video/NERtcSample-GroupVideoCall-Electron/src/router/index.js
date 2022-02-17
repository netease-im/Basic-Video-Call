import Vue from 'vue'
import Router from 'vue-router'
import Nertc from '../components/Nertc'
import store from '../store/index';

Vue.use(Router)

const router = new Router({
  routes: [
    {
      path: '/',
      name: 'nertc',
      component: Nertc
    },
    {
      path: '*',
      redirect: '/'
    }
  ]
})

const NERtcSDK = require('nertc-electron-sdk').default;
router.beforeEach((to, from, next)=>{

  let nertcEngine = store.getters.getNertcEngine
  console.log("nertcEngine: "+ nertcEngine)
  if(nertcEngine === null){
    nertcEngine = new NERtcSDK.NERtcEngine()
    store.commit('setNertcEngine',nertcEngine)
  }
  next()
})

export default router



