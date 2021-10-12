#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include "video_widget.h"

VideoWidget::VideoWidget(QWidget* parent /*= nullptr*/)
:QWidget(parent)
{
    this->setStyleSheet("QWidget{background-color: #292933;}");
    setUi();
}

VideoWidget::~VideoWidget()
{
    qDebug() << "VideoWidget::~VideoWidget";
}

void* VideoWidget::GetVideoHwnd()
{
    return (void*)this->winId();
}

const bool VideoWidget::IsJoin()
{
    return is_join_;
}

void VideoWidget::SetJoinStatus(const bool &state)
{
    is_join_ = state;
    this->setVisible(state);
}

void VideoWidget::SetCenterName(const QString &name)
{
    center_name_label_->setText(name);
}

const QString VideoWidget::GetUserId()
{
    return center_name_label_->text();
}

void VideoWidget::setUi()
{
    QWidget *content_widget = new QWidget();
    center_name_label_ = new QLabel(content_widget);
    center_name_label_->setStyleSheet("QLabel{color: rgb(255, 255, 255);\
                                             font-size: 36px;\
                                             background-color: transparent;}");
    center_name_label_->setText("user");
    center_name_label_->setAlignment(Qt::AlignCenter);

    QVBoxLayout *main_layout = new QVBoxLayout(this);
    main_layout->addWidget(center_name_label_);
}
