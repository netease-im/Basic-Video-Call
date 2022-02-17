module.exports = {
  lintOnSave: false,
  pluginOptions: {
    electronBuilder: {
        nodeIntegration: true
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