/*
 * Copyright (c) 2023 Hunan OpenValley Digital Industry Development Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import audio from '@ohos.multimedia.audio';
import media from '@ohos.multimedia.media';
import hilog from '@ohos.hilog';
//import Logger from '../utils/Logger';

const TAG = 'mAudioCapturer';

// export default class AudioCapturerHelper {
//   private audioCapturer?: audio.AudioCapturer;
//   private audioRecorder?: media.AVRecorder;
// }


// export default class AudioCapturerInfo {
//   recursion: boolean;
//   listNum?: number;
// }

class audioStreamInfo {
  public samplingRate: audio.AudioSamplingRate = audio.AudioSamplingRate.SAMPLE_RATE_44100;
  public channels: audio.AudioChannel = audio.AudioChannel.CHANNEL_2;
  public sampleFormat: audio.AudioSampleFormat = audio.AudioSampleFormat.SAMPLE_FORMAT_S16LE;
  public encodingType: audio.AudioEncodingType = audio.AudioEncodingType.ENCODING_TYPE_RAW;
}

class audioCapturerInfo {
  public source: audio.SourceType = audio.SourceType.SOURCE_TYPE_VOICE_COMMUNICATION;
  public capturerFlags: number = 0;
}

class audioCapturerOptions {
  public streamInfo: audioStreamInfo = new audioStreamInfo();
  public capturerInfo: audioCapturerInfo = new audioCapturerInfo();
}

// 与使用AudioCapturer开发音频录制功能过程相似，关键区别在于audioCapturerInfo参数和音频数据流向
export default class AudioCapturerHelper {
  private audioCapturer?: audio.AudioCapturer;
  private audioCapturerOptions_: audioCapturerOptions = new audioCapturerOptions;

  async init(): Promise<void> {
    try {
      this.audioCapturer = await audio.createAudioCapturer(this.audioCapturerOptions_);
      //Logger.info(`${TAG}: create AudioCapturer success`);
      //hilog.info(0xFF00, "mAudioCapturer", "create AudioCapturer success");
    } catch (err) {
      //Logger.error(`${TAG}: Invoke createAudioCapturer failed, code is ${err.code}, message is ${err.message}`);
      //hilog.info(0xFF00, "mAudioCapturer", "Invoke createAudioCapturer failed, code is %{public}s ", err.message);
    }
  }

  async start(callback: (buffer: ArrayBuffer, size: number) => void): Promise<void> {
    if (!this.audioCapturer) {
      //Logger.info(`${TAG}: start failed AudioCapturer is null`);
      return;
    }

    let stateGroup = [audio.AudioState.STATE_PREPARED, audio.AudioState.STATE_PAUSED, audio.AudioState.STATE_STOPPED];
    if (stateGroup.indexOf(this.audioCapturer.state) === -1) { // 当且仅当状态为prepared、paused和stopped之一时才能启动采集
      //Logger.info(`${TAG}: start failed`);
      return;
    }

    try {
      await this.audioCapturer.start(); // 启动采集
      //Logger.info(`${TAG}: start AudioCapturer success`);
      let bufferSize: number = await this.audioCapturer.getBufferSize(); // rk打印出来2972? 先不用
      //Logger.info(`${TAG}: read bufferSize ${bufferSize}`);
      while (true) {

        let buffer: ArrayBuffer = await this.audioCapturer.read(bufferSize, true);
        if (buffer === undefined) {
          //Logger.error(`${TAG}: read buffer failed`);
        } else {
          if (callback) {
            callback(buffer, bufferSize);
          }
        }
      }
    } catch (err) {
      //Logger.error(`${TAG}: start Capturer failed, code is ${err.code}, message is ${err.message}`);
    }
  }

  //停止采集
  async stop(): Promise<void> {

    if (!this.audioCapturer) {
      //Logger.info(`${TAG}: start failed AudioCapturer is null`);
      return;
    }
    //Logger.info(`${TAG}:  Capturer stop`);
    try {
      //只有采集器状态为STATE_RUNNING或STATE_PAUSED的时候才可以停止
      if (this.audioCapturer.state !== audio.AudioState.STATE_RUNNING && this.audioCapturer.state !== audio.AudioState.STATE_PAUSED) {
        //Logger.info(`${TAG}: Capturer is not running or paused`);
        return;
      }
     this.audioCapturer.stop(); // 停止采集
    } catch (err) {
      //Logger.error(`${TAG}: stop Capturer failed, code is ${err.code}, message is ${err.message}`);
    }
  }

  // 销毁实例，释放资源
  async release(): Promise<void> {
    if (!this.audioCapturer) {
      //Logger.info(`${TAG}: start failed AudioCapturer is null`);
      return;
    }
    //Logger.info(`${TAG}:  Capturer release`);
    try {
      // 采集器状态不是STATE_RELEASED或STATE_NEW状态，才能release
      if (this.audioCapturer.state === audio.AudioState.STATE_RELEASED || this.audioCapturer.state === audio.AudioState.STATE_NEW) {
        //Logger.info(`${TAG}:  Capturer already released`);
        return;
      }
      await this.audioCapturer.release(); // 释放资源
    } catch (err) {
      //Logger.error(`${TAG}: release Capturer failed, code is ${err.code}, message is ${err.message}`);
    }
  }

}

