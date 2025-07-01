import React, {
  useState,
  useRef,
  useEffect,
  useCallback,
  forwardRef,
  useImperativeHandle,
} from "react";
import "./index.css";

type PipVideoProps = {
  initialPosition?: { x: number; y: number };
  width?: string; // 如 "25vw"
  aspectRatio?: string; // 如 "9/16"
  content?: string;
  onClick?: React.MouseEventHandler<HTMLDivElement>; // 添加 onClick 类型
  // React 18+ 需要显式声明 children
  children?: React.ReactNode;
};

// 定义暴露给父组件的 Ref 类型
export type PipHandle = {
  getElement: () => HTMLDivElement | null;
};

const Pip = forwardRef<PipHandle, PipVideoProps>(
  (
    {
      initialPosition = { x: 10, y: 10 },
      width = "25vw",
      aspectRatio = "3/4",
      content = "等待视频流",
      children, // 2. 直接从 props 解构 children
      onClick, // 接收 onClick
      ...restProps // 接收其他所有 props（如 className、style 等）
    },
    ref, // 接收外部传入的 ref
  ) => {
    const [position, setPosition] = useState(initialPosition);
    const [isDragging, setIsDragging] = useState(false);
    const pipRef = useRef<HTMLDivElement>(null);
    const offset = useRef({ x: 0, y: 0 });
    const [showContent, setShowContent] = useState(true);
    const observerRef = useRef<MutationObserver>();

    // 检测 video 是否存在
    const checkVideo = useCallback(() => {
      const hasVideo = !!pipRef.current?.querySelector("video");
      console.log("检测 video 存在:", hasVideo);
      setShowContent(!hasVideo);
      return hasVideo;
    }, []);

    useEffect(() => {
      if (!pipRef.current) return;

      // MutationObserver 监听 DOM 变化
      observerRef.current = new MutationObserver(() => {
        checkVideo();
      });
      observerRef.current.observe(pipRef.current, {
        childList: true,
        subtree: true,
      });
      // 初始检测
      checkVideo();
      return () => {
        observerRef.current?.disconnect();
      };
    }, []);

    // 关键修改：使用 useImperativeHandle 暴露 ref
    useImperativeHandle(ref, () => ({
      getElement: () => pipRef.current, // 直接返回内部 DOM 元素
    }));
    // 处理鼠标/触摸按下
    const handleStart = (e: React.MouseEvent | React.TouchEvent) => {
      setIsDragging(true);
      const clientX = "touches" in e ? e.touches[0].clientX : e.clientX;
      const clientY = "touches" in e ? e.touches[0].clientY : e.clientY;

      if (pipRef.current) {
        const rect = pipRef.current.getBoundingClientRect();
        offset.current = {
          x: clientX - rect.left,
          y: clientY - rect.top,
        };
      }
      // 阻止触摸滚动
      // if ('touches' in e) {
      //     e.preventDefault();
      // }
    };

    // 处理移动
    const handleMove = (e: MouseEvent | TouchEvent) => {
      if (!isDragging || !pipRef.current) return;

      // 获取当前鼠标/触摸位置
      const clientX = "touches" in e ? e.touches[0].clientX : e.clientX;
      const clientY = "touches" in e ? e.touches[0].clientY : e.clientY;

      // 计算新位置（基于 right 定位）
      const newRight = window.innerWidth - clientX - offset.current.x;
      const newTop = clientY - offset.current.y;

      // 边界检查（防止拖出视窗）
      const maxRight = window.innerWidth - pipRef.current.offsetWidth;
      const maxTop = window.innerHeight - pipRef.current.offsetHeight - 100;

      setPosition({
        x: Math.max(0, Math.min(newRight, maxRight)), // right 值
        y: Math.max(0, Math.min(newTop, maxTop)), // top 值
      });

      // 阻止触摸滚动
      if ("touches" in e) {
        e.preventDefault();
      }
    };

    // 处理释放
    const handleEnd = () => {
      setIsDragging(false);
    };

    // 绑定/解绑全局事件
    useEffect(() => {
      if (isDragging) {
        document.addEventListener("mousemove", handleMove);
        document.addEventListener("touchmove", handleMove as EventListener);
        document.addEventListener("mouseup", handleEnd);
        document.addEventListener("touchend", handleEnd);
      } else {
        document.removeEventListener("mousemove", handleMove);
        document.removeEventListener("touchmove", handleMove as EventListener);
        document.removeEventListener("mouseup", handleEnd);
        document.removeEventListener("touchend", handleEnd);
      }

      return () => {
        document.removeEventListener("mousemove", handleMove);
        document.removeEventListener("touchmove", handleMove as EventListener);
        document.removeEventListener("mouseup", handleEnd);
        document.removeEventListener("touchend", handleEnd);
      };
    }, [isDragging]);

    return (
      <div
        ref={pipRef} // 内部 ref 绑定到 div 元素上
        className="pip"
        style={{
          position: "absolute",
          right: `${position.x}px`,
          top: `${position.y}px`,
          width,
          aspectRatio,
          cursor: isDragging ? "grabbing" : "pointer", // 动态光标
          color: "white",
          fontSize: "16px",
          display: "flex",
          alignItems: "center",
          justifyContent: "center",
          // 关键修复：确保容器能正确传递事件
          pointerEvents: "none", // 容器不拦截事件
        }}
        onMouseDown={handleStart}
        onTouchStart={handleStart}
        onClick={onClick} // 透传 onClick
        {...restProps} // 透传其他所有 props
      >
        {/* 内容区域 - 添加事件处理层 */}
        <div
          style={{
            position: "absolute",
            top: 0,
            left: 0,
            right: 0,
            bottom: 0,
            pointerEvents: "auto", // 子元素可以接收事件
            display: "flex",
            justifyContent: "center",
            alignItems: "center",
          }}
          //onMouseDown={handleStart}
          //onTouchStart={handleStart}
        >
          {children}
        </div>
        {showContent && content}
      </div>
    );
  },
);
export default Pip;
