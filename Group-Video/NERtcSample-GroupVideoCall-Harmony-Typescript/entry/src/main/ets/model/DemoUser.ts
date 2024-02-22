

export default class DemoUser {
  /**
   * classify uid
   */
  uid: BigInt;
  /**
   * classify xComponentId
   */
  xComponentId: string;

  width: number;
  height: number;

  isMe: boolean;

  constructor(uid: BigInt, xComponentId: string) {
    this.uid = uid;
    this.xComponentId = xComponentId;
    this.width = 150;
    this.height = 150;
    this.isMe = false;
  }
}

