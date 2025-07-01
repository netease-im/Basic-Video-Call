export type VisibilityState = "visible" | "hidden";
export type VisibilityChangeCallback = (state: VisibilityState) => void;
export type VisibilityEventType = "change" | "hide" | "show";

class BrowserVisibilityMonitor {
  private isHidden: boolean;
  private callbacks: Map<VisibilityEventType, Set<VisibilityChangeCallback>>;
  private isWeChatBrowser: boolean;

  constructor() {
    this.isHidden = false;
    this.callbacks = new Map();
    this.isWeChatBrowser = /MicroMessenger/i.test(navigator.userAgent);
    this.initEventListeners();
  }

  private initEventListeners(): void {
    // 标准 Page Visibility API
    document.addEventListener("visibilitychange", this.handleVisibilityChange);

    // 备用 blur/focus 事件
    window.addEventListener("blur", this.handleWindowBlur);
    window.addEventListener("focus", this.handleWindowFocus);

    // 微信浏览器特殊处理
    if (this.isWeChatBrowser) {
      window.addEventListener("pagehide", this.handleWeChatHide);
      window.addEventListener("pageshow", this.handleWeChatShow);
    }
  }

  private handleVisibilityChange = (): void => {
    this.updateState(document.hidden);
  };

  private handleWindowBlur = (): void => {
    if (!this.isHidden) {
      this.updateState(true);
    }
  };

  private handleWindowFocus = (): void => {
    if (this.isHidden) {
      this.updateState(false);
    }
  };

  private handleWeChatHide = (): void => {
    this.updateState(true);
  };

  private handleWeChatShow = (): void => {
    this.updateState(false);
  };

  private updateState(hidden: boolean): void {
    const oldState = this.isHidden;
    this.isHidden = hidden;

    if (oldState !== hidden) {
      this.notifyCallbacks();
    }
  }

  private notifyCallbacks(): void {
    const state: VisibilityState = this.isHidden ? "hidden" : "visible";

    // 通用 change 事件
    this.triggerCallbacks("change", state);

    // 特定 hide/show 事件
    this.triggerCallbacks(this.isHidden ? "hide" : "show", state);
  }

  private triggerCallbacks(
    type: VisibilityEventType,
    state: VisibilityState,
  ): void {
    const callbacks = this.callbacks.get(type);
    if (callbacks) {
      callbacks.forEach((callback) => callback(state));
    }
  }

  public on(
    event: VisibilityEventType,
    callback: VisibilityChangeCallback,
  ): () => void {
    if (!this.callbacks.has(event)) {
      this.callbacks.set(event, new Set());
    }
    const callbacks = this.callbacks.get(event)!;
    callbacks.add(callback);

    return () => {
      callbacks.delete(callback);
    };
  }

  public off(
    event: VisibilityEventType,
    callback: VisibilityChangeCallback,
  ): void {
    const callbacks = this.callbacks.get(event);
    if (callbacks) {
      callbacks.delete(callback);
    }
  }

  public getState(): VisibilityState {
    return this.isHidden ? "hidden" : "visible";
  }

  public destroy(): void {
    document.removeEventListener(
      "visibilitychange",
      this.handleVisibilityChange,
    );
    window.removeEventListener("blur", this.handleWindowBlur);
    window.removeEventListener("focus", this.handleWindowFocus);

    if (this.isWeChatBrowser) {
      window.removeEventListener("pagehide", this.handleWeChatHide);
      window.removeEventListener("pageshow", this.handleWeChatShow);
    }

    this.callbacks.clear();
  }
}

export default BrowserVisibilityMonitor;
