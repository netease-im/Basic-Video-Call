//
//  NTESMeetingViewController.m
//  NERtcGroupMeetingSample
//
//  Created by 丁文超 on 2020/3/23.
//  Copyright © 2020 丁文超. All rights reserved.
//

#import "NTESMeetingViewController.h"
#import <NERtcSDK/NERtcSDK.h>

@interface NTESMeetingViewController () <NERtcEngineDelegateEx>

@property (strong, nonatomic) IBOutlet UIView *localUserView;
@property (strong, nonatomic) IBOutletCollection(UIView) NSArray *remoteUserViews;


@end

@implementation NTESMeetingViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.title = [NSString stringWithFormat:@"Room %@", self.roomID];
    [self setupRTCEngine];
    [self joinCurrentRoom];
}

- (void)dealloc
{
    [NERtcEngine.sharedEngine leaveChannel];
    [NERtcEngine destroyEngine];
}

- (void)setupRTCEngine
{
    NERtcEngine *coreEngine = [NERtcEngine sharedEngine];
    NERtcEngineContext *context = [[NERtcEngineContext alloc] init];
    context.engineDelegate = self;
    context.appKey = @"<#请输入您的app key#>";
    [coreEngine setupEngineWithContext:context];
    [coreEngine enableLocalAudio:YES];
    [coreEngine enableLocalVideo:YES];
}

- (void)joinCurrentRoom
{
    [NERtcEngine.sharedEngine joinChannelWithToken:@"" channelName:self.roomID myUid:self.userID completion:^(NSError * _Nullable error, uint64_t channelId, uint64_t elapesd) {
        NERtcVideoCanvas *canvas = [[NERtcVideoCanvas alloc] init];
        canvas.container = self.localUserView;
        [NERtcEngine.sharedEngine setupLocalVideoCanvas:canvas];
    }];
}

- (void)onNERtcEngineUserDidJoinWithUserID:(uint64_t)userID userName:(NSString *)userName
{
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

- (void)onNERtcEngineUserVideoDidStartWithUserID:(uint64_t)userID videoProfile:(NERtcVideoProfileType)profile
{
    [NERtcEngine.sharedEngine subscribeRemoteVideo:YES forUserID:userID streamType:kNERtcRemoteVideoStreamTypeHigh];
}

- (void)onNERtcEngineUserDidLeaveWithUserID:(uint64_t)userID reason:(NERtcSessionLeaveReason)reason
{
    [self.view viewWithTag:(NSInteger)userID].tag = 0;
}


@end
