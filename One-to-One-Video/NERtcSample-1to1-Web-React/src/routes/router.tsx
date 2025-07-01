import { createBrowserRouter, createHashRouter } from "react-router-dom";
//import Home from '../pages/home'
import Preview from "../pages/preview";
import RTC from "../pages/rtc";
import App from "../App";
import Loading from "../components/loading";
import { lazy, Suspense } from "react";
const Home = lazy(() => import("../pages/home"));

// 路由配置
const routes = [
  {
    path: "/",
    element: <App />,
    children: [
      {
        index: true,
        element: (
          <Suspense fallback={<Loading />}>
            <Home />
          </Suspense>
        ),
      },
      { path: "home", element: <Home /> },
      { path: "preview", element: <Preview /> },
      { path: "rtc", element: <RTC /> },
    ],
  },
];

//@ts-ignore
const isDev = import.meta.env.MODE === "development";
// 或 import.meta.env.DEV
console.log("isDev", isDev);
const router = isDev ? createBrowserRouter(routes) : createHashRouter(routes);

export default router;
