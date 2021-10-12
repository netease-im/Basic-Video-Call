#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include "video_widget.h"

VideoWidget::VideoWidget(QWidget* parent /*= nullptr*/)
:QWidget(parent)
{
    this->setStyleSheet("QWidget{background-color: #292933;}");
}

VideoWidget::~VideoWidget()
{
    qDebug() << "VideoWidget::~VideoWidget";
}

void* VideoWidget::GetVideoHwnd()
{
    return (void*)this->winId();
}
