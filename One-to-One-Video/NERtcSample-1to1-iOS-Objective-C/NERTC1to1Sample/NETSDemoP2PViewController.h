//
//  NETSDemoP2PViewController.h
//  NERtcP2pSample
//
//  Created by NetEase on 2020/08/01.
//  Copyright (c) 2014-2020 NetEase, Inc. All rights reserved.
//  点对点会议页面

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface NETSDemoP2PViewController : UIViewController

+ (instancetype)instanceWithRoomId:(NSString *)roomId
                            userId:(uint64_t)userId;

@end

NS_ASSUME_NONNULL_END
