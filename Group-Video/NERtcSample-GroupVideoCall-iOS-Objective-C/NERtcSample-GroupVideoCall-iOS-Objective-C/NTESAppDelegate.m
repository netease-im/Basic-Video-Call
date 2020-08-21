//
//  NTESAppDelegate.m
//  NERtcGroupMeetingSample
//
//  Created by 丁文超 on 2020/3/23.
//  Copyright © 2020 丁文超. All rights reserved.
//

#import "NTESAppDelegate.h"

@implementation NTESAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // 强制触发网络权限请求
    [[NSURLSession.sharedSession dataTaskWithRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:@"https://www.baidu.com"]]] resume];
    return YES;
}

@end
