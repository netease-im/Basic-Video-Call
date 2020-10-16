#include "videowidget.h"
VideoWidget::VideoWidget(QWidget *parent /*= Q_NULLPTR*/)
    :QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground, true);
    
    ui.setupUi(this);
    QFont font;
    font.setPixelSize(12);
    font.setBold(true);
    ui.uid->setFont(font);
    
}

VideoWidget::~VideoWidget()
{

  
}

void VideoWidget::setUsrID(QString strid)
{
    QString str = "UsrId : " + strid;
    ui.uid->setText(str);
    ui.uid->adjustSize();

}

void VideoWidget::closeRender()
{
    ui.uid->setText("");
    ui.uid->adjustSize();
    repaint();
}

void* VideoWidget::getVideoHwnd()
{
    return (void*)ui.video->winId();
}

