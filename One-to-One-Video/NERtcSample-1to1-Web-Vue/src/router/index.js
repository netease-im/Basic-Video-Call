import Vue from 'vue'
import VueRouter from 'vue-router'

Vue.use(VueRouter)

const routes = [{
    path: '/',
    name: 'join',
    component: () => import( /* webpackChunkName: "join" */ '../views/join/index.vue')
}, {
    path: '/home',
    name: 'home',
    component: () => import( /* webpackChunkName: "home" */ '../views/home/index.vue')
}]

const router = new VueRouter({
    mode: 'history',
    base: process.env.BASE_URL,
    routes
})

router.onError((error) => {
  const pattern = /Loading chunk (\w)+ failed/g;
  const isChunkLoadFailed = error.message.match(pattern);
  const targetPath = router.history.pending.fullPath;
  if (isChunkLoadFailed) {
     router.replace(targetPath);
  }
})

export default router
