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

class audioStreamInfo {
  public samplingRate: audio.AudioSamplingRate = audio.AudioSamplingRate.SAMPLE_RATE_44100;
  public channels: audio.AudioChannel = audio.AudioChannel.CHANNEL_2;
  public sampleFormat: audio.AudioSampleFormat = audio.AudioSampleFormat.SAMPLE_FORMAT_S16LE;
  public encodingType: audio.AudioEncodingType = audio.AudioEncodingType.ENCODING_TYPE_RAW;
}

class audioRendererInfo {
  public content: audio.ContentType = audio.ContentType.CONTENT_TYPE_SPEECH;
  public usage: audio.StreamUsage = audio.StreamUsage.STREAM_USAGE_VOICE_COMMUNICATION;
  rendererFlags: number = 0;
}

class audioRendererOptions {
  public streamInfo: audioStreamInfo = new audioStreamInfo();
  public rendererInfo: audioRendererInfo = new audioRendererInfo();
}

const TAG = 'mAudioRender';
// 与使用AudioRenderer开发音频播放功能过程相似，关键区别在于audioRenderInfo参数和音频数据来源
export default class AudioRenderHelper {
  private renderModel?: audio.AudioRenderer;
  private audioRendererOptions_: audioRendererOptions = new audioRendererOptions;
  // 初始化，创建实例
  async init(): Promise<void> {
    try {
      this.renderModel = await audio.createAudioRenderer(this.audioRendererOptions_);
      //Logger.info(`${TAG}: creating AudioRenderer success`);
    } catch (err) {
      //Logger.error(`${TAG}: creating AudioRenderer failed, code is ${err.code}, message: ${err.message}`);
    }
  }
  // 开始一次音频渲染
  async start(): Promise<void> {
    if (!this.renderModel) {
      //Logger.info(`${TAG}: start failed AudioRenderer is null`);
      return;
    }
    try {
      let stateGroup = [audio.AudioState.STATE_PREPARED, audio.AudioState.STATE_PAUSED, audio.AudioState.STATE_STOPPED];
      if (stateGroup.indexOf(this.renderModel.state) === -1) { // 当且仅当状态为prepared、paused和stopped之一时才能启动渲染
        //Logger.info(`${TAG}: start failed`);
        return;
      }
      await this.renderModel.start(); // 启动渲染
      await this.renderModel.setVolume(1.0); //调节音量
      //Logger.info(`${TAG}: start AudioRenderer success`);
    } catch (err) {
      //Logger.error(`${TAG}: start AudioRenderer failed, code is ${err.code}, message: ${err.message}`);
    }
  }


  async write(buffer: ArrayBuffer): Promise<number> {
    if (!this.renderModel) {
      //Logger.info(`${TAG}: start failed AudioRenderer is null`);
      return 0;
    }

    try {
      let len: number = await this.renderModel.write(buffer);
      return len;
    } catch (err) {
      //Logger.error(`${TAG}: AudioRenderer write  failed, error: ${err.message}`);
    }
    return 0;
  }

  // 停止渲染
  async stop(): Promise<void> {
    if (!this.renderModel) {
      //Logger.info(`${TAG}: start failed AudioRenderer is null`);
      return;
    }
    try {
      // 只有渲染器状态为running或paused的时候才可以停止
      if (this.renderModel.state !== audio.AudioState.STATE_RUNNING && this.renderModel.state !== audio.AudioState.STATE_PAUSED) {
        //Logger.info(`${TAG} Renderer is not running or paused.`);
        return;
      }
      // await this.renderModel.stop(); // 停止渲染
    } catch (err) {
      //Logger.error(`${TAG}: AudioRenderer stop  failed, error: ${err.message}`);
    }
  }
  // 销毁实例，释放资源
  async release(): Promise<void> {
    if (!this.renderModel) {
      //Logger.info(`${TAG}: start failed AudioRenderer is null`);
      return;
    }

    //Logger.info(`${TAG} Renderer  release`);
    try {
      //渲染器状态不是released状态，才能release
      if (this.renderModel.state === audio.AudioState.STATE_RELEASED) {
        //Logger.info(`${TAG} Renderer already released`);
        return;
      }
      await this.renderModel.release(); // 释放资源
    } catch (err) {
      //Logger.error(`${TAG}: AudioRenderer release failed, error: ${err.message}`);
    }
  }
}
