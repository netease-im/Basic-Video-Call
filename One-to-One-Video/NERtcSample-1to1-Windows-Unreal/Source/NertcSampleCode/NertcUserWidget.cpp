// Fill out your copyright notice in the Description page of Project Settings.


#include "NertcUserWidget.h"
#include <iostream>

const std::string g_appKey = "your appkey";
const std::string g_logPath = "your log path";
const std::string g_channelName = "your channel name";
const uint64_t g_userID = 123; //your userID

void UNertcUserWidget::NativeConstruct()
{
  Super::NativeConstruct();
  InitNertcEngine(g_appKey, g_logPath);
}

void UNertcUserWidget::NativeDestruct() {
  ReleaseNertcEngine();
  Super::NativeDestruct();
}

void UNertcUserWidget::InitNertcEngine(std::string appKey, std::string logPath) {
  nertc_engine_ = nertc::createNERtcEngine();

  if (!nertc_engine_)
    return;
  
  nertc::NERtcEngineContext context{};
  context.app_key = appKey.c_str();
  //设置引擎事件回调，确保YourProjectClass继承了IRtcEngineEventHandler
  context.event_handler = this;
  context.log_dir_path = logPath.c_str();
  context.log_level = kNERtcLogLevelInfo;

  auto ret = nertc_engine_->initialize(context);
  if (ret != 0) {
    ReleaseNertcEngine();
    return;
  }
  
  //设置游戏模式，获得更好的音频体验 （可选）
  nertc_engine_->setParameters("{\"sdk.enable.plugin.game.mode\":true}");

  //获取音频manager对象，用于操控音频设备 （可选）
  nertc_engine_->queryInterface(nertc::kNERtcIIDAudioDeviceManager, (void**)(&audio_device_manager_));
  if (!audio_device_manager_) {
    return;
  }

  //设置媒体状态回调，确保YourProjectClass继承了IRtcMediaStatsObserver （可选）
  nertc_engine_->setStatsObserver(this);
}
void UNertcUserWidget::ReleaseNertcEngine() {
  if (!nertc_engine_)
    return;
  nertc_engine_->release();
  delete nertc_engine_;
  nertc_engine_ = nullptr;
}
void UNertcUserWidget::OnJoinChannelClicked() {
  nertc_engine_->joinChannel("", g_channelName.c_str(), g_userID, NERtcJoinChannelOptions{});
}

void UNertcUserWidget::OnLeaveChannelClicked() {
  nertc_engine_->leaveChannel();
}

void UNertcUserWidget::onJoinChannel(channel_id_t cid, nertc::uid_t uid, NERtcErrorCode result, uint64_t elapsed) {
  std::cout << "onJoinChannel"<<std::endl;
}
void UNertcUserWidget::onConnectionStateChange(NERtcConnectionStateType state, NERtcReasonConnectionChangedType reason) {
  std::cout << "onConnectionStateChange" << std::endl;
}

void UNertcUserWidget::onLeaveChannel(NERtcErrorCode result, uint64_t channel_id) {
  std::cout << "onLeaveChannel" << std::endl;
}
void UNertcUserWidget::onRtcStats(const NERtcStats& stats) {
  std::cout << "onRtcStats" << std::endl;
}