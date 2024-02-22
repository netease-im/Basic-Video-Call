

import router from '@ohos.router';
import CommonConstants from '../common/CommonConstants';

@Entry
@Component
struct Settings {
  @State message: string = '开发中'

  build() {
    Row() {
      Column() {
        Button("back")
          .fontSize(20)
          .width(200)
          .height(20)
          .backgroundColor("#007DFF")
          .onClick(() => {
            router.back();
          })
        Text(this.message)
          .fontSize(50)
          .fontWeight(FontWeight.Bold)
      }
      .width('100%')
    }
    .height('100%')
  }
}