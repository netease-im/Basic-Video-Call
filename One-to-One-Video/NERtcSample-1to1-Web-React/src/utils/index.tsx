import { sha1 } from "js-sha1";

/* 生成一个随机数 */
export const getRandomInt = (min: number, max: number): number => {
  min = Math.ceil(min);
  max = Math.floor(max);
  return Math.floor(Math.random() * (max - min + 1)) + min;
};

/* 判断是否为微信浏览器 */
export const isWeixinBrowser = (): boolean => {
  const ua = navigator.userAgent.toLowerCase();
  return ua.includes("micromessenger");
};

/* 判断是否为chrome浏览器 */
export const checkChrome = () => {
  // 排除 Firefox/Safari 等非 Chromium 内核
  if (
    navigator.userAgent.includes("Firefox") ||
    (navigator.userAgent.includes("Safari") &&
      !navigator.userAgent.includes("Chrome"))
  ) {
    return false;
  }

  // 核心检测逻辑
  const isChromium = "chrome" in window;
  const isEdge = navigator.userAgent.includes("Edg/");
  const isOpera = navigator.userAgent.includes("OPR/");

  // 包含 Chrome、Edge、Opera、Vivaldi 等 Chromium 系浏览器
  return (
    (isChromium || navigator.userAgent.includes("Chrome")) &&
    !isEdge &&
    !isOpera
  );
};

type winVersion =
  | "10.0"
  | "6.3"
  | "6.2"
  | "6.1"
  | "6.0"
  | "5.2"
  | "5.1"
  | "5.0";

/* 获取操作系统和浏览器信息 */
export const getSystemInfo = () => {
  const userAgent = navigator.userAgent.toLowerCase();
  let os = undefined;
  let osVersion = undefined;
  let browser = undefined;
  let browserVersion = undefined;
  const isMobile = /mobile|android|iphone|ipad|ipod/i.test(userAgent);
  const isWeChat = /micromessenger/i.test(userAgent);

  console.warn("userAgent: ", navigator.userAgent);

  // 检测操作系统及版本
  if (/harmonyos/i.test(userAgent)) {
    os = "Harmony";
    osVersion = userAgent.match(/harmonyos (\d+\.\d+)/i)?.[1] || osVersion;
  } else if (/android/i.test(userAgent)) {
    os = "Android";
    osVersion = userAgent.match(/android (\d+\.\d+)/i)?.[1] || osVersion;
  } else if (/iphone|ipad|ipod/i.test(userAgent)) {
    os = "iOS";
    osVersion =
      userAgent.match(/os (\d+_\d+)/i)?.[1]?.replace("_", ".") ||
      userAgent.match(/cpu (iphone )?os (\d+_\d+)/i)?.[2]?.replace("_", ".") ||
      osVersion;
  } else if (/windows nt/i.test(userAgent)) {
    os = "Windows";
    // Windows版本映射
    const winVersionMap = {
      "10.0": "10/11",
      "6.3": "8.1",
      "6.2": "8",
      "6.1": "7",
      "6.0": "Vista",
      "5.2": "XP",
      "5.1": "XP",
      "5.0": "2000",
    };
    const ntVersion = userAgent.match(
      /windows nt (\d+\.\d+)/i,
    )?.[1] as winVersion;
    osVersion = winVersionMap[ntVersion] || ntVersion || osVersion;
  } else if (/linux/i.test(userAgent)) {
    os = "Linux";
    // Linux发行版检测
    if (/ubuntu/i.test(userAgent)) {
      osVersion = userAgent.match(/ubuntu[\/ ](\d+\.\d+)/i)?.[1] || osVersion;
    } else if (/debian/i.test(userAgent)) {
      osVersion = userAgent.match(/debian[\/ ](\d+)/i)?.[1] || osVersion;
    } else if (/fedora/i.test(userAgent)) {
      osVersion = userAgent.match(/fedora[\/ ](\d+)/i)?.[1] || osVersion;
    }
  } else if (/macintosh|mac os x/i.test(userAgent)) {
    os = "MacOS";
    osVersion =
      userAgent.match(/mac os x (\d+[._]\d+)/i)?.[1]?.replace("_", ".") ||
      osVersion;
  }

  // 检测浏览器及版本
  if (isWeChat) {
    browser = "WeChat";
    // 微信内置浏览器版本检测
    browserVersion =
      userAgent.match(/micromessenger\/(\d+\.\d+\.\d+)/i)?.[1] ||
      browserVersion;
  } else if (/chrome|crios/i.test(userAgent) && !/edge/i.test(userAgent)) {
    browser = "Chrome";
    browserVersion =
      userAgent.match(/(chrome|crios)\/(\d+\.\d+)/i)?.[2] || browserVersion;
  } else if (/firefox|fxios/i.test(userAgent)) {
    browser = "Firefox";
    browserVersion =
      userAgent.match(/(firefox|fxios)\/(\d+\.\d+)/i)?.[2] || browserVersion;
  } else if (/safari/i.test(userAgent) && !/chrome/i.test(userAgent)) {
    browser = "Safari";
    browserVersion =
      userAgent.match(/version\/(\d+\.\d+)/i)?.[1] || browserVersion;
  } else if (/edge/i.test(userAgent)) {
    browser = "Edge";
    browserVersion =
      userAgent.match(/edge\/(\d+\.\d+)/i)?.[1] || browserVersion;
  } else if (/trident/i.test(userAgent)) {
    browser = "IE";
    browserVersion = userAgent.match(/rv:(\d+\.\d+)/i)?.[1] || browserVersion;
  } else if (/opera|opr/i.test(userAgent)) {
    browser = "Opera";
    browserVersion =
      userAgent.match(/(opera|opr)\/(\d+\.\d+)/i)?.[2] || browserVersion;
  }

  return {
    os,
    osVersion,
    browser,
    browserVersion,
    isMobile,
    isWeChat,
    userAgent: navigator.userAgent, // 返回原始UA
  };
};
/* 从 location.hash 提取查询参数 */
export const getHashSearch = (hash: string) => {
  const searchIndex = hash.indexOf("?");
  const search = searchIndex !== -1 ? hash.substring(searchIndex) : "";

  return search;
};

/** 云信基础Token鉴权（https://doc.yunxin.163.com/nertc/server-apis/TcxNDAxMTI?platform=server）
    这里仅用于展示，实际项目中不要使用明文的 secret，建议使用应用服务器生成 token
*/
export const getAppToken = async ({
  appkey,
  secret,
  uid,
  channelName,
}: {
  appkey: string;
  secret: string;
  uid: string;
  channelName: string;
}) => {
  const Nonce = Math.ceil(Math.random() * 1e9);
  const CurTime = Math.ceil(Date.now() / 1000);
  const CheckSum = sha1(`${secret}${Nonce}${CurTime}`);

  const headers = new Headers({
    "Content-Type": "application/x-www-form-urlencoded;charset=utf-8",
  });
  headers.append("AppKey", appkey);
  headers.append("Nonce", Nonce.toString());
  headers.append("CurTime", CurTime.toString());
  headers.append("CheckSum", CheckSum);

  const data = await fetch(
    "https://api.netease.im/nimserver/user/getToken.action",
    {
      method: "POST",
      headers: headers,
      body: `uid=${encodeURIComponent(uid)}&channelName=${encodeURIComponent(channelName)}`,
    },
  );

  const result = await data.json();
  console.log("getAppToken result: ", result);
  if (result?.token) {
    console.log("getAppToken token: ", result);
    return result.token;
  } else {
    console.error(result || data);
    return null;
  }
};

// 这里仅用于展示，实际项目中不要使用明文的 secret，建议使用应用服务器生成 token
export const ajax = async ({
  url,
  appkey,
  secret,
  headers,
  body,
}: {
  url: string;
  appkey: string;
  secret: string;
  headers?: Headers;
  body: string;
}) => {
  console.log("ajax 请求: ", url, appkey, secret, body);
  const Nonce = Math.ceil(Math.random() * 1e9);
  const CurTime = Math.ceil(Date.now() / 1000);
  const CheckSum = sha1(`${secret}${Nonce}${CurTime}`);

  const httpHeaders = new Headers(headers || {});
  httpHeaders.append("Content-Type", "application/json");
  httpHeaders.append("AppKey", appkey);
  httpHeaders.append("Nonce", Nonce.toString());
  httpHeaders.append("CurTime", CurTime.toString());
  httpHeaders.append("CheckSum", CheckSum);
  httpHeaders;
  const data = await fetch(url, {
    method: "POST",
    headers: httpHeaders,
    body,
  });

  const result = await data.json();
  return result;
};
