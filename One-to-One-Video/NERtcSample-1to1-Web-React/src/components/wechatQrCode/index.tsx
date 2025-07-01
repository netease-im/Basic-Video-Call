import { useState, useEffect } from "react";
import { QRCodeSVG } from "qrcode.react";
import { CopyToClipboard } from "react-copy-to-clipboard";
import "./index.css";

const WechatQrCode = () => {
  const [currentUrl, setCurrentUrl] = useState("");
  const [isCopied, setIsCopied] = useState(false);
  const [size, setSize] = useState(200);
  const [bgColor, setBgColor] = useState("#ffffff");
  const [fgColor, setFgColor] = useState("#000000");

  // 获取当前页面URL
  useEffect(() => {
    setCurrentUrl(window.location.href);
  }, []);

  // 重置复制状态
  useEffect(() => {
    if (isCopied) {
      const timer = setTimeout(() => setIsCopied(false), 2000);
      return () => clearTimeout(timer);
    }
  }, [isCopied]);

  // 下载二维码
  const downloadQRCode = () => {
    const svg = document.getElementById("qr-code-canvas") as Node;
    const svgData = new XMLSerializer().serializeToString(svg);
    const canvas = document.createElement("canvas");
    const ctx = canvas.getContext("2d") as CanvasRenderingContext2D;
    const img = new Image();

    img.onload = () => {
      canvas.width = img.width;
      canvas.height = img.height;
      ctx.drawImage(img, 0, 0);
      const pngFile = canvas.toDataURL("image/png");
      const downloadLink = document.createElement("a");
      downloadLink.download = "QRCode";
      downloadLink.href = pngFile;
      downloadLink.click();
    };

    img.src =
      "data:image/svg+xml;base64," +
      btoa(unescape(encodeURIComponent(svgData)));
  };

  return (
    <div className="qr-code-container">
      <h2>请使用微信扫码访问当前页面</h2>

      <div className="qr-code-box">
        {currentUrl ? (
          <QRCodeSVG
            id="qr-code-canvas"
            value={currentUrl}
            size={size}
            bgColor={bgColor}
            fgColor={fgColor}
            level="H" // 纠错级别：L, M, Q, H
          />
        ) : (
          <div className="loading">加载中...</div>
        )}
      </div>

      <div className="url-display">
        <input type="text" value={currentUrl} readOnly className="url-input" />
        <CopyToClipboard text={currentUrl} onCopy={() => setIsCopied(true)}>
          <button className="copy-btn">
            {isCopied ? "已复制!" : "复制链接"}
          </button>
        </CopyToClipboard>
      </div>

      <div className="action-buttons">
        <button onClick={downloadQRCode} className="download-btn">
          下载二维码
        </button>
      </div>

      <div className="customize-section">
        <h3>自定义二维码</h3>
        <div className="custom-controls">
          <div className="control-group">
            <label>大小:</label>
            <input
              type="range"
              min="100"
              max="400"
              value={size}
              onChange={(e) => setSize(parseInt(e.target.value))}
            />
            <span>{size}px</span>
          </div>

          <div className="control-group">
            <label>背景色:</label>
            <input
              type="color"
              value={bgColor}
              onChange={(e) => setBgColor(e.target.value)}
            />
          </div>

          <div className="control-group">
            <label>前景色:</label>
            <input
              type="color"
              value={fgColor}
              onChange={(e) => setFgColor(e.target.value)}
            />
          </div>
        </div>
      </div>

      <div className="instructions">
        <h3>使用说明</h3>
        <ol>
          <li>下载二维码</li>
          <li>打开微信，点击右上角"+"</li>
          <li>选择"扫一扫"功能</li>
          <li>扫描二维码图片即可访问当前页面</li>
        </ol>
      </div>
    </div>
  );
};

export default WechatQrCode;
