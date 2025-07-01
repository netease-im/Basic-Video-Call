// useVisibility.ts
import { useEffect, useState } from "react";
import BrowserVisibilityMonitor from "@/features/browserVisibilityMonitor";
import type { VisibilityState } from "@/features/browserVisibilityMonitor";

const useVisibility = (): VisibilityState => {
  const [visibility, setVisibility] = useState<VisibilityState>("visible");

  useEffect(() => {
    const monitor = new BrowserVisibilityMonitor();
    setVisibility(monitor.getState());

    const unsubscribe = monitor.on("change", (state: string) => {
      setVisibility(state as VisibilityState);
    });

    return () => {
      unsubscribe();
      monitor.destroy();
    };
  }, []);

  return visibility;
};

export default useVisibility;
