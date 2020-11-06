#include "mainwindow.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QRegExpValidator>
#include <QDebug>
#include <QTime>
#include <QRandomGenerator>
#include "Toast.h"


mainwindow::mainwindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);
    resize(600, 400);

    m_engine = std::make_shared<smaple_nertc::NRTCEngine>(nullptr);
    videowindowPtr = std::make_shared<VideoWindow>();
    videowindowPtr->setNeRtcEngine(m_engine);

    connect(this, &mainwindow::joinchannelSignal, videowindowPtr.get(), &VideoWindow::onJoinChannel);
    connect(videowindowPtr.get(), &VideoWindow::closeVideoWindowSignal, this, &mainwindow::oncloseVideoWindow);
    ui.setupUi(this);

    //保证存数字
    QRegExp rx("^[0-9]{12}$");
    
    QRegExpValidator *validator = new QRegExpValidator(rx, this);

    ui.roomid->setValidator(validator);

    ui.userId->setValidator(validator);

    this->setWindowTitle("NERtcSample-GroupVideoCall");
}

mainwindow::~mainwindow()
{

}



void mainwindow::initEnv()
{
    auto videolist = m_engine->getVideoDeviceList();
    QVariantList videonamelist = videolist["name"].value<QVariantList>();
    QVariantList videoguidlist = videolist["guid"].value<QVariantList>();
    for ( int i = 0 ;   i < videonamelist.size(); ++i )
    { 
        auto devicename =  videonamelist[i].value<QString>();
        auto deviceid   =  videoguidlist[i].value<QString>();
        
        ui.video_comboBox->addItem(devicename, deviceid);
    }
    auto audiolist = m_engine->getPlayoutDeviceList();
    QVariantList audionamelist = audiolist["name"].value<QVariantList>();
    QVariantList audioguidlist = audiolist["guid"].value<QVariantList>();
    for (int i = 0; i < audionamelist.size(); ++i)
    {
        auto devicename = audionamelist[i].value<QString>();
        auto deviceid = audioguidlist[i].value<QString>();

        ui.audio_comboBox->addItem(devicename, deviceid);
    }
}


void mainwindow::on_joinChannel_clicked(bool bchecked)
{
    auto strRoomid = ui.roomid->text();
    qDebug() << strRoomid;
    if (strRoomid.length() > 12 || strRoomid == 0)
    {

        Toast::showTip(QString("房间号填写错误（12位数字以内）").toUtf8(), this);
        return;
    }

    //UID随机生成，可自己把控
    auto userid = ui.userId->text();
    if (userid.length() == 0)
    {
        auto n = QRandomGenerator::global()->bounded(10000, 9999999);
        userid = QString::number(n);

    }
    
    qDebug() << userid;
    this->hide();
    m_engine->setVideoDevice(ui.video_comboBox->currentData().value<QString>());
    m_engine->setPlayoutDevice(ui.audio_comboBox->currentData().value<QString>());

    emit joinchannelSignal(strRoomid, userid);
 
     
}

void mainwindow::oncloseVideoWindow()
{
    ui.roomid->setText("");
    this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
    this->show();

}

