//import webSocket from '@ohos.net.webSocket';
//import Socket from '@ohos.net.socket';
//import TCPSocket from '@ohos.net.socket';
//import ServerSocket from '@ohos.net.ServerSocket';

//import  ServerRequest from '@ohos.net.http';
//import WebSocket  from '@ohos.net.websocket';

import { BusinessError } from '@ohos.base';
import prompt from '@ohos.promptAction';
import TALogicManager from '../ta/TALogicManager';
import webSocket from '@ohos.net.webSocket';



// import { createHttpServer, createRouter, ServerRequest } from '@ohos.net.http';
// import { createWebSocket, WebSocket } from '@ohos.net.websocket';


const TAG: string = '[Demo][Ta]';

export default class TACore {

  public taLogicManager: TALogicManager = new TALogicManager();
  //private  socket: webSocket.WebSocket = webSocket.createWebSocket();
  //private  socket: webSocket.WebSocket = new WebSocket('ws://0.0.0.0:50001');
  //private  socket: webSocket.WebSocket = webSocket.createWebSocket();

  //private tcpSocket: TCPSocket = Socket.constructTCPSocketInstance()

  //private  socket: webSocket.WebSocket = webSocket.createWebSocket()

  public startServer(): boolean {


    // let serverSocket: Socket  = new Socket();
    // SocketAddress serverAddress = new SocketAddress("127.0.0.1", 50001);
    // serverSocket.bind(serverAddress);
    // serverSocket.listen();

    // 接受客户端连接
    // while (true) {
    //     Socket clientSocket = serverSocket.accept();
    //     // 在这里可以处理clientSocket，接收数据，发送数据等
    // }

    // let tcpSocket = Socket.constructTCPSocketInstance();
    //
    //
    // tcpSocket.bind(50001);
    //
    // tcpSocket.listen((clientSocket) => {
    //   // 处理连接
    //   clientSocket.onData((data) => {
    //     // 处理接收到的数据
    //   });
    //
    //   clientSocket.onClose(() => {
    //     // 处理连接关闭
    //   });
    //
    //   clientSocket.send("Hello, client!"); // 向客户端发送数据
    // });
    //this.socket.connect("0.0.0.0:50001",)

    //private  socket: webSocket.WebSocket = webSocket.createWebSocket();


    // let defaultIpAddress = "ws://0.0.0.0:50001";
    // //let ws = webSocket.createWebSocket();
    // this.socket.on('open', (err:BusinessError, value: Object) => {
    //   if (err != undefined) {
    //     console.log(JSON.stringify(err));
    //     return;
    //   }
    //   // 当收到on('open')事件时，可以通过send()方法与服务器进行通信
    //   this.socket.send("Hello, server!", (err: BusinessError, value: boolean) => {
    //     if (!err) {
    //       console.log("send success");
    //     } else {
    //       console.log("send fail, err:" + JSON.stringify(err));
    //     }
    //   });
    // });
    // // this.socket.on('message',(BusinessError<void>, value: string | ArrayBuffer) => {
    // //   console.log("on message, message:" + value);
    // //   // 当收到服务器的`bye`消息时（此消息字段仅为示意，具体字段需要与服务器协商），主动断开连接
    // //   // if (value === 'bye') {
    // //   //   this.socket.close((err: BusinessError, value: boolean) => {
    // //   //     if (!err) {
    // //   //       console.log("close success");
    // //   //     } else {
    // //   //       console.log("close fail, err is " + JSON.stringify(err));
    // //   //     }
    // //   //   });
    // //   // }
    // // });
    // this.socket.on('close', (err: BusinessError, value: webSocket.CloseResult) => {
    //   console.log("on close, code is " + value.code + ", reason is " + value.reason);
    // });
    // this.socket.on('error', (err: BusinessError) => {
    //   console.log("on error, error:" + JSON.stringify(err));
    // });
    // this.socket.connect(defaultIpAddress, (err: BusinessError, value: boolean) => {
    //   if (!err) {
    //     console.log("connect success");
    //   } else {
    //     console.log("connect fail, err:" + JSON.stringify(err));
    //   }
    //   this.socket.close((err: BusinessError) => {
    //     if (!err) {
    //       console.log("close success");
    //     } else {
    //       console.log("close fail, err is " + JSON.stringify(err));
    //     }
    //   });
    // });

    return true
  }

  public stopServer(): void {
  }

  public execCommand(jsonString: string): string {
    let response = this.taLogicManager.execCommand(jsonString)
    return response
  }
}
