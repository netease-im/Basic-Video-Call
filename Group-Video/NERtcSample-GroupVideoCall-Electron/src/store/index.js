import Vue from 'vue'
import Vuex from 'vuex'

Vue.use(Vuex)

const store =  new Vuex.Store({
  state: {
    nertcEngine: null,
  },

  getters:{
    getNertcEngine(state){
      return state.nertcEngine
    }
  },

  mutations:{
      setNertcEngine(state, nertcEngine){
        state.nertcEngine = nertcEngine
      }
  }
})

export default store
