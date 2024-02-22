const TAG: string = '[Demo][Ta]';

export default class RtcTool {

  static respDataString(code: string, method: string): string {
    class Data {
      result: string = code;
      type: string = "reply";
      method: string = method;
    }
    let data: Data = new Data();
    const jsonData = JSON.stringify(data);
    return jsonData
  }

  static respDataNumber(code: number, method: string): string {
    class Data {
      result: number = code;
      type: string = "reply";
      method: string = method;
    }
    let data: Data = new Data();
    const jsonData = JSON.stringify(data);
    return jsonData
  }

  static respDataBigint(code: BigInt, method: string): string {
    class Data {
      result: BigInt = code;
      type: string = "reply";
      method: string = method;
    }
    let data: Data = new Data();
    const jsonData = JSON.stringify(data);
    return jsonData
  }
}