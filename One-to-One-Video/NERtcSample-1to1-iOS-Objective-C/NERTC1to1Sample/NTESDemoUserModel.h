//
//  NTESDemoUserModel.h
//  NERtcP2pSample
//
//  Created by NetEase on 2020/08/01.
//  Copyright (c) 2014-2020 NetEase, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class NERtcVideoCanvas;

NS_ASSUME_NONNULL_BEGIN

@interface NTESDemoUserModel : NSObject

//用户ID
@property (nonatomic, assign) uint64_t uid;

//渲染视图
@property (nonatomic, weak) UIView *renderContainer;

//已订阅了视频流
@property (nonatomic, assign) BOOL subscribedVideo;

//建立SDK Canvas
- (NERtcVideoCanvas *)setupCanvas;

//重置Canvas
- (void)resetCanvas;

@end

NS_ASSUME_NONNULL_END
