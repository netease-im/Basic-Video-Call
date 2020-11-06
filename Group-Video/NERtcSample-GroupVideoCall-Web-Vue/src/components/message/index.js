import MessageComponent from './index.vue'
import Vue from 'vue'

export function message (content, duration) {
    const Instance = new Vue({
        render (h) {
            return h(MessageComponent, {
                props: {
                    content,
                    duration
                }
            })
        }
    })
    const component = Instance.$mount()
    document.body.appendChild(component.$el)
}
