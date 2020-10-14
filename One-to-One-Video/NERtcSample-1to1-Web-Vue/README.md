# Web-g2-demo

## 1.项目简介
这个开源示例项目演示了如何快速集成 网易云信 新一代（G2）音视频 SDK，实现1对1的音视频通话。

## 2.功能包含

- 加入房间
- 静音、取消静音
- 关闭、打开视频
- 离开房间

[在线体验](https://app.yunxin.163.com/webdemo/g2web/index.html#/?path=single)

## 3.技术栈
vue （vue-cli 4.x）

## 4.前提条件，appkey获取

1. 若您已经与专属客户经理取得联系，可直接向他获取Appkey
2. 若您并未与专属客户经理取得联系那么请按后续步骤获取Appkey
3. 首先在[网易云信](https://id.163yun.com/register?h=media&t=media&clueFrom=nim&from=bdjjnim0035&referrer=https://app.yunxin.163.com/?clueFrom=nim&from=bdjjnim0035)注册账号
4. 然后在「应用」一栏中创建您的项目
5. 等待专属客户经理联系您，并向他获取Appkey

## 5.开始运行项目
- node开发环境 version 8+


## 6.开始运行项目

### 安装依赖

```
npm install
```

### 本地启动

```
npm run dev
```

### 正式环境打包

```
npm run build
```

### 代码检查及修复

```
npm run lint
```

## 7.注意事项

- 当前功能内部署了云信的3.7.0版本的sdk，如需要最新版本的sdk请主动去[云信官网](https://yunxin.163.com/)下载
- 从云信获取到应用appkey和appSecret之后，需要使用者主动去代码中添加：`/config/index`中
- 云信sdk音视频功能，需要运行在安全环境中：https链接或者本地链接（localhost、127.0.0.1）
- 更多内容请访问[云信官网](https://yunxin.163.com/)了解
