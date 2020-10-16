#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "videoWindow.h"
#include "nrtc_engine.h"

class mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    mainwindow(QWidget *parent = Q_NULLPTR);
    ~mainwindow();
public:
    void initEnv();
signals:
    void joinchannelSignal(QString& roomid, QString& nickname);
public slots:
    void on_joinChannel_clicked(bool bchecked);
    void oncloseVideoWindow();
private:
    Ui::mainwindowClass ui;
private:
    std::shared_ptr<VideoWindow> videowindowPtr;
    std::shared_ptr<smaple_nertc::NRTCEngine> m_engine;
};
