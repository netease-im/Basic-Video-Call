//
//  NTESDemoUserModel.m
//  NERtcP2pSample
//
//  Created by NetEase on 2020/08/01.
//  Copyright (c) 2014-2020 NetEase, Inc. All rights reserved.
//  

#import "NTESDemoUserModel.h"
#import <NERtcSDK/NERtcSDK.h>

@class NERtcVideoCanvas;

@implementation NTESDemoUserModel

- (NERtcVideoCanvas *)setupCanvas {
    
    //显示渲染视图，UI切换为通话渲染状态
    _renderContainer.hidden = NO;
    
    //SDK setup canvas
    NERtcVideoCanvas *canvas = [[NERtcVideoCanvas alloc] init];
    canvas.container = _renderContainer;
    canvas.renderMode = kNERtcVideoRenderScaleCropFill;
    return canvas;
}

- (void)resetCanvas {
    
    //隐藏渲染视图，UI切换为通话之前的状态
    _renderContainer.hidden = YES;
    
    //SDK内部会在渲染时在外部配置的渲染view上增加内部实际渲染view，因此需要在重置的时候清理一下
    [_renderContainer.subviews makeObjectsPerformSelector:@selector(removeFromSuperview)];
}

@end
