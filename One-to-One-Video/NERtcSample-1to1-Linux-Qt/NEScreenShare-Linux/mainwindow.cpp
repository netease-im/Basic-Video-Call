#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->yunxin_website->setOpenExternalLinks(true);

    QString log_dir = QCoreApplication::applicationDirPath() + "/Log";

    rtc_engine = new RtcEngine();
    if (rtc_engine) {
        if (!rtc_engine->init(APP_KEY, log_dir.toStdString(), kNERtcLogLevelInfo, 50000)) {
            // TODO
            return;
        }
    }

    setWindowTitle("NERtc SDK Demo: " + QString::fromStdString(rtc_engine->getSdkVersion()));
    setFixedSize(this->width(), this->height());

    //signal-slot
    connect(rtc_engine, &RtcEngine::yuvDataComming, this, &MainWindow::on_yuvDataComming);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (rtc_engine) {
        delete rtc_engine;
        rtc_engine = nullptr;
    }
}

void MainWindow::on_yuvDataComming(uint32_t uid, std::vector<unsigned char> data_y, std::vector<unsigned char> data_u, std::vector<unsigned char> data_v, int w, int h)
{
    if (uid == 0) {
        ui->local_video_canvas->showYuv(data_y, data_u, data_v, w, h);
    } else {
        ui->remote_user_id->setText(QString::number(uid));
        ui->remote_video_canvas->showYuv(data_y, data_u, data_v, w, h);
    }
}

void MainWindow::on_join_clicked()
{
    std::string token;
    if (ui->token_enable->isChecked()) {
        token = ui->token->text().toStdString();
    }
    std::string room_name = ui->room_name->text().toStdString();
    uint32_t user_id = ui->user_id->text().toUInt();
    rtc_engine->joinRoom(token, room_name, user_id);
}


void MainWindow::on_leave_clicked()
{
    rtc_engine->leaveRoom();
}

void MainWindow::on_screen_share_start_clicked()
{
    rtc_engine->startScreenCaptureByScreenRect(NERtcRectangle(), NERtcRectangle(), NERtcScreenCaptureParameters());
}


void MainWindow::on_screenshare_stop_clicked()
{
    rtc_engine->stopScreenCapture();
}

