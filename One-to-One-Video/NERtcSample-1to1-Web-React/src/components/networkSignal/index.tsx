import React, { useMemo } from "react";
import "./index.css";

// 类型定义
type SignalLevel = 0 | 1 | 2 | 3;

interface Props {
  level: SignalLevel;
}

// 使用memo包裹组件 + 自定义比较函数
const NetworkSignal: React.FC<Props> = React.memo(
  ({ level }) => {
    const getColor = (bar: number, level: SignalLevel) => {
      let color = "#f0f0f0"; // 默认灰色，unkown
      switch (level) {
        case 1:
          color = "#ff4d4f"; // 红色，极差
          if (bar > 2) {
            color = "#f0f0f0";
          }
          break;
        case 2:
          color = "#faad14"; // 黄色，一般
          if (bar > 3) {
            color = "#f0f0f0";
          }
          break;
        case 3:
          color = "#52c41a"; // 绿色，很好
          break;
      }
      return color;
    };

    // 使用useMemo缓存计算结果
    const bars = useMemo(() => {
      //const colors = ["#ff4d4f", "#faad14", "#52c41a"];
      return [1, 2, 3, 4].map((bar) => ({
        bar,
        color: getColor(bar, level),
        active: bar <= level + 1,
      }));
    }, [level]);
    console.log("NetworkSignal render level: ", level);
    return (
      <div className="network-signal-container">
        <div className="signal-bars">
          {bars.map(({ bar, color, active }) => (
            <div
              key={bar}
              className={`signal-bar ${active ? "active" : ""}`}
              style={{ backgroundColor: color }}
            />
          ))}
        </div>
      </div>
    );
  },
  (prev, next) => prev.level === next.level,
); // 仅level变化时重新渲染

export default NetworkSignal;
export type { SignalLevel };
