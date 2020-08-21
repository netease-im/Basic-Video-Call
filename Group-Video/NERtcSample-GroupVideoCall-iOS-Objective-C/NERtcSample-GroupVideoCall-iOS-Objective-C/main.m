//
//  main.m
//  NERtcSample-GroupVideoCall-iOS-Objective-C
//
//  Created by Wenchao Ding on 2020/8/20.
//  Copyright © 2020 Wenchao Ding. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "NTESAppDelegate.h"

int main(int argc, char * argv[]) {
    NSString * appDelegateClassName;
    @autoreleasepool {
        // Setup code that might create autoreleased objects goes here.
        appDelegateClassName = NSStringFromClass([NTESAppDelegate class]);
    }
    return UIApplicationMain(argc, argv, nil, appDelegateClassName);
}
