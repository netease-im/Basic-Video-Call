#pragma once
#include <QWidget>
#include "ui_videowidget.h"

class VideoWidget : public QWidget
{
    Q_OBJECT
public:
    VideoWidget(QWidget *parent = Q_NULLPTR);
    ~VideoWidget();
public:
    void setUsrID(QString strid);
    void closeRender();
    void* getVideoHwnd();
protected:
private:
    Ui::videowidget ui;
};
