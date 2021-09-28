//
//  NETSDemoP2PViewController.m
//  NERtcP2pSample
//
//  Created by NetEase on 2020/08/01.
//  Copyright (c) 2014-2020 NetEase, Inc. All rights reserved.
//  

#import "NETSDemoP2PViewController.h"
#import "NTESDemoUserModel.h"
#import "AppKey.h"

#import <NERtcSDK/NERtcSDK.h>

@interface NETSDemoP2PViewController ()<NERtcEngineDelegateEx>

//渲染视图控件，SDK需要通过设置渲染view来建立canvas
@property (weak, nonatomic) IBOutlet UIView *localRender;  //本地渲染视图
@property (weak, nonatomic) IBOutlet UIView *remoteRender; //远端渲染视图
@property (weak, nonatomic) IBOutlet UILabel *remoteStatLab;

//上个页面传过来的参数
@property (nonatomic, copy) NSString *roomId;  //房间ID
@property (nonatomic, assign) uint64_t userId; //本人uid

//Demo的 canvas 模型，包括uid 和 container, 用来建立sdk canvas
@property (nonatomic, strong) NTESDemoUserModel *localCanvas;  //本地
@property (nonatomic, strong) NTESDemoUserModel *remoteCanvas; //远端

@end

@implementation NETSDemoP2PViewController

#pragma mark - Public

+ (instancetype)instanceWithRoomId:(NSString *)roomId
                            userId:(uint64_t)userId {
    UIStoryboard *storyBoard = [UIStoryboard storyboardWithName:@"Main" bundle:[NSBundle mainBundle]];
    NETSDemoP2PViewController *ret = [storyBoard instantiateViewControllerWithIdentifier:@"NETSDemoP2PViewController"];
    ret.roomId = roomId;
    ret.userId = userId;
    
    //初始化SDK
    [ret setupRTCEngine];
    
    return ret;
}

#pragma mark - Life Cycle

- (void)dealloc {
    NSLog(@"%s", __FUNCTION__);
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    //直接加入channel
    [self joinChannelWithRoomId:_roomId userId:_userId];
}

#pragma mark - Functions

//初始化SDK
- (void)setupRTCEngine {
    //默认情况下日志会存储在App沙盒的Documents目录下
    NERtcLogSetting *logSetting = [[NERtcLogSetting alloc] init];
#if DEBUG
    logSetting.logLevel = kNERtcLogLevelInfo;
#else
    logSetting.logLevel = kNERtcLogLevelWarning;
#endif
    
    NERtcEngineContext *context = [[NERtcEngineContext alloc] init];
    context.engineDelegate = self;
    context.appKey = AppKey;
    context.logSetting = logSetting;
    [[NERtcEngine sharedEngine] setupEngineWithContext:context];
}

//释放SDK资源
- (void)destroyRTCEngineWithCompletion:(void(^)(void))completion {
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^{
        [NERtcEngine destroyEngine];
        
        if (completion) {
            completion();
        }
    });
}

//建立本地canvas模型
- (NERtcVideoCanvas *)setupLocalCanvas {
    _localCanvas = [[NTESDemoUserModel alloc] init];
    _localCanvas.uid = _userId;
    _localCanvas.renderContainer = self.localRender;
    return [_localCanvas setupCanvas];
}

//建立远端canvas模型
- (NERtcVideoCanvas *)setupRemoteCanvasWithUid:(uint64_t)uid {
    _remoteCanvas = [[NTESDemoUserModel alloc] init];
    _remoteCanvas.uid = uid;
    _remoteCanvas.renderContainer = self.remoteRender;
    return [_remoteCanvas setupCanvas];
}

//加入房间
- (void)joinChannelWithRoomId:(NSString *)roomId
                       userId:(uint64_t)userId {
    NERtcEngine *coreEngine = [NERtcEngine sharedEngine];
    
    //1v1音视频通话场景的视频推荐配置
    //其他场景下请联系云信技术支持获取配置
    NERtcVideoEncodeConfiguration *config = [[NERtcVideoEncodeConfiguration alloc] init];
    config.width = 640;
    config.height = 360;
    config.frameRate = kNERtcVideoFrameRateFps15;
    [coreEngine setLocalVideoConfig:config];
    
    //1v1音视频通话场景的音频推荐配置
    //其他场景下请联系云信技术支持获取配置
    [coreEngine setAudioProfile:kNERtcAudioProfileStandard
                       scenario:kNERtcAudioScenarioSpeech];
    
    [coreEngine enableLocalAudio:YES];
    [coreEngine enableLocalVideo:YES];
    
    __weak typeof(self) weakSelf = self;
    [coreEngine joinChannelWithToken:@""
                         channelName:roomId
                               myUid:userId
                          completion:^(NSError * _Nullable error, uint64_t channelId, uint64_t elapesd) {
        if (error) {
            //加入失败，弹框之后退出当前页面
            NSString *message = [NSString stringWithFormat:@"join channel fail.code:%@", @(error.code)];
            [weakSelf showDismissAlertWithMessage:message actionBlock:^{
                [weakSelf destroyRTCEngineWithCompletion:^{
                    dispatch_async(dispatch_get_main_queue(), ^{
                        [weakSelf.navigationController popViewControllerAnimated:YES];
                    });
                }];
            }];
        } else {
            //加入成功，建立本地canvas渲染本地视图
            NERtcVideoCanvas *canvas = [weakSelf setupLocalCanvas];
            [coreEngine setupLocalVideoCanvas:canvas];
        }
    }];
}

#pragma mark - Actions

//UI 挂断按钮事件
- (IBAction)onHungupAction:(UIButton *)sender {
    [NERtcEngine.sharedEngine leaveChannel];
}

//UI 关闭本地音频按钮事件
- (IBAction)onAudioMuteAction:(UIButton *)sender {
    sender.selected = !sender.selected;
    [NERtcEngine.sharedEngine enableLocalAudio:!sender.selected];
}

//UI 关闭本地视频按钮事件
- (IBAction)onVideoMuteAction:(UIButton *)sender {
    sender.selected = !sender.selected;
    [NERtcEngine.sharedEngine enableLocalVideo:!sender.selected];
}

//UI 切换摄像头按钮事件
- (IBAction)onSwitchCameraAction:(UIButton *)sender {
    [NERtcEngine.sharedEngine switchCamera];
}

#pragma mark - SDK回调（含义请参考NERtcEngineDelegateEx定义）

- (void)onNERtcEngineDidError:(NERtcError)errCode {
    NSString *message = [NSString stringWithFormat:@"nertc engine did error.code:%@", @(errCode)];
    [self showDismissAlertWithMessage:message actionBlock:^{
        [[NERtcEngine sharedEngine] leaveChannel];
    }];
}

- (void)onNERtcEngineUserDidJoinWithUserID:(uint64_t)userID
                                  userName:(NSString *)userName {
    //如果已经setup了一个远端的canvas，则不需要再建立了
    if (_remoteCanvas != nil) {
        return;
    }
    
    //建立远端canvas，用来渲染远端画面
    NERtcVideoCanvas *canvas = [self setupRemoteCanvasWithUid:userID];
    [NERtcEngine.sharedEngine setupRemoteVideoCanvas:canvas
                                           forUserID:userID];
}

- (void)onNERtcEngineUserVideoDidStartWithUserID:(uint64_t)userID
                                    videoProfile:(NERtcVideoProfileType)profile {
    //如果已经订阅过远端视频流，则不需要再订阅了
    if (_remoteCanvas.subscribedVideo) {
        return;
    }
    
    //订阅远端视频流
    _remoteCanvas.subscribedVideo = YES;
    [NERtcEngine.sharedEngine subscribeRemoteVideo:YES
                                         forUserID:userID
                                        streamType:kNERtcRemoteVideoStreamTypeHigh];
}

- (void)onNERtcEngineUserVideoDidStop:(uint64_t)userID {
    if (userID == _remoteCanvas.uid) {
        _remoteStatLab.hidden = YES;
    }
}

- (void)onNERtcEngineUserDidLeaveWithUserID:(uint64_t)userID
                                     reason:(NERtcSessionLeaveReason)reason {
    //如果远端的人离开了，重置远端模型和UI
    if (userID == _remoteCanvas.uid) {
        _remoteStatLab.hidden = NO;
        [_remoteCanvas resetCanvas];
        _remoteCanvas = nil;
    }
}

- (void)onNERtcEngineDidDisconnectWithReason:(NERtcError)reason {
    //网络连接中断时会触发该回调，触发之后的操作则由开发者按需实现
}

- (void)onNERtcEngineDidLeaveChannelWithResult:(NERtcError)result {
    //调用leaveChannel之后，若需要释放SDK资源，建议在收到该回调之后，再调用destroyEngine
    [self destroyRTCEngineWithCompletion:^{
        dispatch_async(dispatch_get_main_queue(), ^{
            [self.navigationController popViewControllerAnimated:YES];
        });
    }];
}

#pragma mark - Helper

- (void)showDismissAlertWithMessage:(NSString *)message actionBlock:(void(^)(void))actionBlock {
    UIAlertController *alertVC = [UIAlertController alertControllerWithTitle:@"退出提示"
                                                                     message:message
                                                              preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *exitAction = [UIAlertAction actionWithTitle:@"退出"
                                                         style:UIAlertActionStyleDefault
                                                       handler:^(UIAlertAction * _Nonnull action) {
        if (actionBlock) {
            actionBlock();
        }
    }];
    [alertVC addAction:exitAction];
    [self presentViewController:alertVC animated:YES completion:nil];
}

@end
