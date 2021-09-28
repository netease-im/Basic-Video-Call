//
//  NTESMeetingViewController.m
//  NERtcGroupMeetingSample
//
//  Created by 丁文超 on 2020/3/23.
//  Copyright © 2020 丁文超. All rights reserved.
//

#import "NTESMeetingViewController.h"
#import "NTESAppConfig.h"

#import <NERtcSDK/NERtcSDK.h>

@interface NTESMeetingViewController () <NERtcEngineDelegateEx>

@property (strong, nonatomic) IBOutlet UIView *localUserView;
@property (strong, nonatomic) IBOutletCollection(UIView) NSArray *remoteUserViews;

@end

@implementation NTESMeetingViewController

#pragma mark - Life Cycle

- (void)dealloc {
    NSLog(@"%s", __FUNCTION__);
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Leave" style:UIBarButtonItemStylePlain target:self action:@selector(onBackAction:)];
    self.title = [NSString stringWithFormat:@"Room %@", self.roomID];
    
    [self setupRTCEngine];
    [self joinCurrentRoom];
}

#pragma mark - Functions

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
    context.appKey = kAppKey;
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

- (void)joinCurrentRoom {
    NERtcEngine *coreEngine = [NERtcEngine sharedEngine];
    
    //多人音视频通话场景的视频推荐配置
    //其他场景下请联系云信技术支持获取配置
    NERtcVideoEncodeConfiguration *config = [[NERtcVideoEncodeConfiguration alloc] init];
    config.width = 640;
    config.height = 360;
    config.frameRate = kNERtcVideoFrameRateFps15;
    [coreEngine setLocalVideoConfig:config];
    
    //多人音视频通话场景的音频推荐配置
    //其他场景下请联系云信技术支持获取配置
    [coreEngine setAudioProfile:kNERtcAudioProfileStandard
                       scenario:kNERtcAudioScenarioSpeech];
    
    [coreEngine enableLocalAudio:YES];
    [coreEngine enableLocalVideo:YES];
    
    __weak typeof(self) weakSelf = self;
    [coreEngine joinChannelWithToken:@"" channelName:self.roomID myUid:self.userID completion:^(NSError * _Nullable error, uint64_t channelId, uint64_t elapesd) {
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
            NERtcVideoCanvas *canvas = [[NERtcVideoCanvas alloc] init];
            canvas.container = weakSelf.localUserView;
            [coreEngine setupLocalVideoCanvas:canvas];
        }
    }];
}

#pragma mark - SDK回调（含义请参考NERtcEngineDelegateEx定义）

- (void)onNERtcEngineDidError:(NERtcError)errCode {
    NSString *message = [NSString stringWithFormat:@"nertc engine did error.code:%@", @(errCode)];
    [self showDismissAlertWithMessage:message actionBlock:^{
        [[NERtcEngine sharedEngine] leaveChannel];
    }];
}

- (void)onNERtcEngineUserDidJoinWithUserID:(uint64_t)userID userName:(NSString *)userName {
    NERtcVideoCanvas *canvas = [[NERtcVideoCanvas alloc] init];
    for (UIView *view in self.remoteUserViews) {
        if (view.tag == 0) {
            canvas.container = view;
            [NERtcEngine.sharedEngine setupRemoteVideoCanvas:canvas forUserID:userID];
            view.tag = (NSInteger)userID;
            break;
        }
    }
}

- (void)onNERtcEngineUserVideoDidStartWithUserID:(uint64_t)userID videoProfile:(NERtcVideoProfileType)profile {
    [NERtcEngine.sharedEngine subscribeRemoteVideo:YES forUserID:userID streamType:kNERtcRemoteVideoStreamTypeHigh];
}

- (void)onNERtcEngineUserDidLeaveWithUserID:(uint64_t)userID reason:(NERtcSessionLeaveReason)reason {
    [self.view viewWithTag:(NSInteger)userID].tag = 0;
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

#pragma mark - Actions

- (void)onBackAction:(id)sender {
    [NERtcEngine.sharedEngine leaveChannel];
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
