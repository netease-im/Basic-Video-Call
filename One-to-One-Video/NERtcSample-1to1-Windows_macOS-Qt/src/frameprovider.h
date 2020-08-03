//  Created by NetEase on 8/3/2020.
//  Copyright (c) 2014-2020 NetEase, Inc. All rights reserved.
//

#pragma once

#include <QSize>
#include <QTimer>
#include <QDebug>
#include <QObject>
#include <QVideoSurfaceFormat>
#include <QAbstractVideoSurface>

class FrameProvider : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QAbstractVideoSurface* videoSurface READ videoSurface WRITE setVideoSurface)

public:
	FrameProvider(QObject *parent=nullptr);
	~FrameProvider();

	QAbstractVideoSurface* videoSurface() const { return m_videoSurface; }
	void setVideoSurface(QAbstractVideoSurface* videoSurface);

signals:
	void providerInvalidated();

public slots:
	void restart();
	void deliverFrame(const QVideoFrame& frame, const QSize& videoSize);

private:
	QVideoSurfaceFormat     m_videoFormat;
	QAbstractVideoSurface* m_videoSurface;
};
