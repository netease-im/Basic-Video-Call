//  Created by NetEase on 8/3/2020.
//  Copyright (c) 2014-2020 NetEase, Inc. All rights reserved.
//

#pragma once
#include <QObject>
#include <QVideoFrame>
#include "nertc_engine.h"
#include "frameprovider.h"

class VideoRenderImpl : public QObject
{
    Q_OBJECT
public:
    explicit VideoRenderImpl(FrameProvider* frameProvider, QObject* parent = nullptr);

signals:
    void receivedVideoFrame(const QVideoFrame& frame, const QSize& videoSize);

private:
    FrameProvider* m_frameProvider;
};
