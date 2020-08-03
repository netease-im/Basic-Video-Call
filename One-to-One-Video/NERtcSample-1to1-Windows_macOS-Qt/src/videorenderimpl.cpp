//  Created by NetEase on 8/3/2020.
//  Copyright (c) 2014-2020 NetEase, Inc. All rights reserved.
//

#include "videorenderimpl.h"

VideoRenderImpl::VideoRenderImpl(FrameProvider* frameProvider, QObject* parent)
    : QObject(parent)
    , m_frameProvider(frameProvider)
{
    // Post video frame when receive video data from nrtc SDK
    connect(this, &VideoRenderImpl::receivedVideoFrame, frameProvider, &FrameProvider::deliverFrame);
}
