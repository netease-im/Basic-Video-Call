import audio from '@ohos.multimedia.audio';

const TAG = 'mAudioCapturer';

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

export default class AudioCapturerHelper {
  private audioCapturer?: audio.AudioCapturer;
  private audioCapturerOptions_: audioCapturerOptions = new audioCapturerOptions;

  async init(): Promise<void> {
    try {
      this.audioCapturer = await audio.createAudioCapturer(this.audioCapturerOptions_);
      console.info(TAG, "create AudioCapturer success");
    } catch (err) {
      console.info(TAG, "Invoke createAudioCapturer failed, code is %{public}s ", err.message);
    }
  }

  async start(callback: (buffer: ArrayBuffer, size: number) => void): Promise<void> {
    if (!this.audioCapturer) {
      console.info(TAG, "start failed AudioCapturer is null");
      return;
    }

    let stateGroup = [audio.AudioState.STATE_PREPARED, audio.AudioState.STATE_PAUSED, audio.AudioState.STATE_STOPPED];
    if (stateGroup.indexOf(this.audioCapturer.state) === -1) { // 当且仅当状态为prepared、paused和stopped之一时才能启动采集
      console.info(TAG, "start failed");
      return;
    }

    try {
      await this.audioCapturer.start(); // 启动采集
      let bufferSize: number = await this.audioCapturer.getBufferSize();
      console.info(TAG, "read bufferSize start");
      while (true) {

        let buffer: ArrayBuffer = await this.audioCapturer.read(bufferSize, true);
        if (buffer === undefined) {

        } else {
          if (callback) {
            callback(buffer, bufferSize);
          }
        }
      }
    } catch (err) {

    }
  }

  //停止采集
  async stop(): Promise<void> {

    if (!this.audioCapturer) {
      return;
    }
    console.info(TAG, "stop");
    try {
      //只有采集器状态为STATE_RUNNING或STATE_PAUSED的时候才可以停止
      if (this.audioCapturer.state !== audio.AudioState.STATE_RUNNING && this.audioCapturer.state !== audio.AudioState.STATE_PAUSED) {
        return;
      }
      this.audioCapturer.stop(); // 停止采集
    } catch (err) {
    }
  }

  // 销毁实例，释放资源
  async release(): Promise<void> {
    if (!this.audioCapturer) {
      return;
    }
    console.info(TAG, "release");
    try {
      // 采集器状态不是STATE_RELEASED或STATE_NEW状态，才能release
      if (this.audioCapturer.state === audio.AudioState.STATE_RELEASED || this.audioCapturer.state === audio.AudioState.STATE_NEW) {
        return;
      }
      await this.audioCapturer.release(); // 释放资源
    } catch (err) {
    }
  }

}