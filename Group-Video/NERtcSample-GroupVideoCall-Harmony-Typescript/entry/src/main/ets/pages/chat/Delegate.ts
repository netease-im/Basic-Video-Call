import DemoUser from '../../model/DemoUser';
import { ChatResult } from './ChatModel'


export enum OPERATOR {
  ADD = 0,
  DEL = 1
}

export default interface UIDelegate {
  notify(result: ChatResult): void;
  update(operator: OPERATOR, user: DemoUser): void;
}