module.exports = {
  lintOnSave: false,
  pluginOptions: {
    electronBuilder: {
        nodeIntegration: true,
        externals: ['nertc-electron-sdk'],
        builderOptions: {
          asarUnpack: [
            './node_modules/nertc-electron-sdk/**/*' // 匹配需要解包的文件或目录
          ],
          // extraResources: [
          //   {
          //     from: './node_modules/nertc-electron-sdk/build/Release',
          //     to: 'unasar',
          //     filter: ['**/*.node']
          //   }
          // ]
        }
    }
  },
  configureWebpack:{

    module: {
      rules: [
        {
          test: /\.node$/, //匹配.node文件配置对应loader
          loader: 'native-ext-loader',
          options: {
            emit: true,
            rewritePath: './node_modules/nertc-electron-sdk/build/Release'
          }
        }
      ],
    },
  }
}