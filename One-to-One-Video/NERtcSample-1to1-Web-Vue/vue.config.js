/*
* vue config
* */
const fs = require('fs-extra')
module.exports = {
    publicPath: '/',
    devServer: {
        port: 8020,
        overlay: {
            warnings: false,
            errors: true
        },
        https: true,
        key: fs.readFileSync('./cert/key.pem'),
        cert: fs.readFileSync('./cert/cert.pem'),
        openPage: '#/?path=single'
    },
    configureWebpack: config => {
        if (process.env.NODE_ENV === 'development') {
            config.devtool = 'eval-source-map'
        }
    }
}
