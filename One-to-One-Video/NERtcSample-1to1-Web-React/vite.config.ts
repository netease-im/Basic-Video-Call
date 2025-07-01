import { defineConfig } from 'vite';
import react from '@vitejs/plugin-react';
import { fileURLToPath } from 'node:url';
import path from 'node:path';
const __dirname = path.dirname(fileURLToPath(import.meta.url));
// https://vite.dev/config/
export default defineConfig({
  base: process.env.NODE_ENV === 'production' ? '/webdemo/nertcDemoH5/' : '/',
  server: {
    // proxy: {
    //   // 详细配置写法
    //   '/api': {
    //     target: 'http://1.95.20.209:38074',
    //     changeOrigin: true,
    //     rewrite: path => path.replace(/^\/api/, ''),
    //   },
    // },
    host: '0.0.0.0',
    port: 5173,
    open: true, // 自动打开浏览器
    strictPort: true,
    cors: true, // 允许跨域（如果前端需要访问后端API）
    https: {
      key: path.resolve(__dirname, './ssh/server.key'),
      cert: path.resolve(__dirname, './ssh/server.crt'),
    },
  },
  resolve: {
    alias: {
      '@': path.resolve(__dirname, './src'),
      // 修复 React 运行时冲突
      'react/jsx-runtime': path.resolve(__dirname, 'node_modules/react/jsx-runtime.js'),
      'react/jsx-dev-runtime': path.resolve(__dirname, 'node_modules/react/jsx-dev-runtime.js'),
    },
  },
  plugins: [
    react({
      jsxRuntime: 'automatic', // 显式指定 JSX 运行时模式
    }),
  ],
  optimizeDeps: {
    include: ['react', 'react-dom', 'react-router-dom', 'nertc-web-sdk'],
    esbuildOptions: {
      format: 'esm',
    },
  },
});
