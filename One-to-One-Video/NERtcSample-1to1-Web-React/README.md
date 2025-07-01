# 云信音视频移动端浏览器H5 Demo

## 功能

- H5音视频通话会前检测功能
- H5音视频实时通话功能（包含各种会控）

## 结构

- src： 源码目录
  - main.tsx： 入口文件
  - App.tsx： 根组件，作为所有其他组件的容器
  - src/pages： 页面目录
    - src/pages/home： 首页
    - src/pages/preview： 会前检测页面
    - src/pages/rtc: 实时通话页面
  - src/components： 组件目录
  - src/config： 全局配置
  - src/constant： 全局定义
  - src/assets： 静态资源
  - src/store： 全局变量
  - src/types： 类型定义
  - src/hooks： 全局钩子
  - src/routes: 路由配置
  - src/features： 功能模块目录
  - src/utils： 工具库
- dist： 打包目录
- package.json： 依赖包
- tsconfig.json： ts语法编译配置
- .umirc.ts： 开发环境配置

## 开发流程

### 环境依赖

- 脚手架: umi
- 环境要求：node v18.x
- src/config/config.ts： 配置云信的appkey和secret

### 开发环境启动

- npm install (node使用 v18版本)
- npm run dev

### 打包

- npm run build

### 部署
