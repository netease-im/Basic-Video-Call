import { Outlet } from "react-router-dom";
import { AppProvider } from "./store/index";
import { RTCProvider } from "./store/index";
import Navbar from "./components/nav";
import Logo from "@/assets/yunxinLogo.png";
import "./App.css";
import VConsole from "vconsole";

new VConsole();
function App() {
  return (
    <AppProvider>
      <RTCProvider>
        {" "}
        {/* 在最外层或适当位置添加 RTCProvider */}
        <div className="app">
          <Navbar logoSrc={Logo} appName={"音视频H5"} />
          <Outlet /> {/* 子路由会渲染在这里 */}
        </div>
      </RTCProvider>
    </AppProvider>
  );
}

export default App;
