//
//  NETSAppDelegate.m
//  NERtcP2pSample
//
//  Created by NetEase on 2020/08/01.
//  Copyright (c) 2014-2020 NetEase, Inc. All rights reserved.
//

#import "NETSAppDelegate.h"
#import "AppKey.h"

@interface NETSAppDelegate ()

@end

@implementation NETSAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    NSAssert(![AppKey isEqualToString:@"请填入您的AppKey"],
             @"请在AppKey.h中填入您的APPKey之后，再运行Demo");
    return YES;
}
@end
