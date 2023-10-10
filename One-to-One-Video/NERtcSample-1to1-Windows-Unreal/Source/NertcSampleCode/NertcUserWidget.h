// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "INertcEngineEx.h"
#include "INertcEngineEventHandler.h"
#include "INertcAudioDeviceManager.h"
#include <string>
#include "NertcUserWidget.generated.h"

/**
 * 
 */
using namespace nertc;
UCLASS()
class NERTCSAMPLECODE_API UNertcUserWidget : public UUserWidget, public IRtcEngineEventHandler, public IRtcMediaStatsObserver
{
	GENERATED_BODY()
public:
  void NativeConstruct() override;
  void NativeDestruct() override;

  void InitNertcEngine(std::string appKey, std::string logPath);
  void ReleaseNertcEngine();

  UFUNCTION(BlueprintCallable)
  void OnJoinChannelClicked();
    
  UFUNCTION(BlueprintCallable)
  void OnLeaveChannelClicked();

public:
  //重写onJoinChannel虚函数，调用joinChannel后，SDK会自动调用该函数，通知结果
  void onJoinChannel(channel_id_t cid, nertc::uid_t uid, NERtcErrorCode result, uint64_t elapsed) override;
  //重写onConnectionStateChange虚函数，链接状态发生变更时，SDK会自动调用该函数
  void onConnectionStateChange(NERtcConnectionStateType state, NERtcReasonConnectionChangedType reason)override;
  //重写onLeaveChannel虚函数，离开房间后，SDK会自动调用该函数
  void onLeaveChannel(NERtcErrorCode result, uint64_t channel_id) override;
  //调用setStatsObserver之后，SDK会定期回调onRtcStats函数，将SDK内部数据，例如CPU使用率等，通知给您
  void onRtcStats(const NERtcStats& stats) override;

private:
  //用来保存SDK引擎对象的指针
  nertc::IRtcEngineEx* nertc_engine_;
  //用来保存音频设备管理器的指针
  nertc::IAudioDeviceManager* audio_device_manager_;
};
