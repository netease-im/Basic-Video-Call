#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMoveEvent>
#include <QMessageBox>
#include <QDebug>
#include "json/json.h"
#include "call_widget.h"
#include "engine.h"
#include "video_widget.h"

CallWidget::CallWidget(Engine* engine, QWidget *parent /*= nullptr*/)
:engine_(engine)
,QWidget(parent)
{
    setUi();

    connect(engine_, &Engine::sigJoinChannel, this, &CallWidget::onJoinChannel);
    connect(engine_, &Engine::sigUserJoined, this, &CallWidget::onUserJoin);
    connect(engine_, &Engine::sigUserVideoStart, this, &CallWidget::onUserVideoStart);
    connect(engine_, &Engine::sigUserLeft, this, &CallWidget::onUserLeft);
}

CallWidget::~CallWidget()
{
    qDebug() << "~CallWidget~CallWidget~CallWidget";
}

int CallWidget::JoinChannel(const JoinInfo &join_info)
{
    //Init engine
    QString log_dir_path = qApp->applicationDirPath() + "/NERTC";
    bool init = engine_->Init(log_dir_path.toStdString().c_str());
    if (true == init)
    {
        engine_->EnableVideo(join_info.open_camera_);
        engine_->EnableAudio(join_info.open_mic_);

        // 设置自己的渲染窗口
        void* hwnd = (void*)video_widget_list_[0]->GetVideoHwnd();
        engine_->SetupLocalVideo(hwnd);

        return engine_->JoinChannel(join_info.channel_name_.toStdString(), join_info.uid_.toStdString());
    }
}

void CallWidget::setUi()
{
    this->setMinimumSize(QSize(1366, 718));

    QWidget* video_page = new QWidget();
    QVBoxLayout* main_layout = new QVBoxLayout(video_page);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    QWidget* central_widget = new QWidget(video_page);
    central_widget->setStyleSheet("QWidget{background-color: rgb(0, 0, 0);}");

    vertical_layout_ = new QVBoxLayout(central_widget);
    vertical_layout_->setSpacing(2);
    vertical_layout_->setContentsMargins(58, 8, 58, 8);

    video_top_hlayout_ = new QHBoxLayout();
    vertical_layout_->addLayout(video_top_hlayout_);

    video_middle_hlayout_ = new QHBoxLayout();
    vertical_layout_->addLayout(video_middle_hlayout_);

    video_bottom_hlayout_ = new QHBoxLayout();
    vertical_layout_->addLayout(video_bottom_hlayout_);

    main_layout->addWidget(central_widget);

    QHBoxLayout* h_layout = new QHBoxLayout(this);
    h_layout->setSpacing(0);
    h_layout->setContentsMargins(0, 0, 0, 0);
    h_layout->addWidget(video_page);

    for (size_t i = 0; i < max_count_; i++)
    {
        VideoWidget* video_widget = new VideoWidget(this);
        video_widget->SetJoinStatus(false);
        video_widget_list_.push_back(video_widget);
    }
    video_top_hlayout_->addWidget(video_widget_list_[0]);
}

void CallWidget::adjustVideoLayout()
{
    clearLayout();

    int count = 0;
    int top_max = 2;
    int middle_max = 4;
    if (user_count_ > 4)
    {
        top_max = 3;
        middle_max = 6;
    }

    for (int i = 0; i < max_count_; i++)
    {
        if (count >= user_count_)
        {
            break;
        }

        if (true == video_widget_list_[i]->IsJoin())
        {
            if (top_max > count)
            {
                video_top_hlayout_->addWidget(video_widget_list_[i]);
            }
            else if (middle_max > count)
            {
                video_middle_hlayout_->addWidget(video_widget_list_[i]);
            }
            else if (max_count_ > count)
            {
                video_bottom_hlayout_->addWidget(video_widget_list_[i]);
            }
            ++count;
        }
    }
}

void CallWidget::clearLayout()
{
    while (video_top_hlayout_->count())
    {
        video_top_hlayout_->itemAt(0)->widget()->setParent(nullptr);
    }

    while (video_middle_hlayout_->count())
    {
        video_middle_hlayout_->itemAt(0)->widget()->setParent(nullptr);
    }

    while (video_bottom_hlayout_->count())
    {
        video_bottom_hlayout_->itemAt(0)->widget()->setParent(nullptr);
    }
}

void CallWidget::onJoinChannel(const quint64& uid, const int& reson)
{
    qDebug() << "CallWidget::onJoinChannel:" << reson;
    video_widget_list_[0]->SetJoinStatus(true);
    video_widget_list_[0]->SetCenterName(QString::number(uid));
    this->showNormal();
    this->resize(1184, 666);
}

void CallWidget::onUserJoin(const quint64& uid, const QString& name)
{
    qDebug() << "CallWidget::onUserJoin";

    for (int i = 1; i < max_count_; ++i)
    {
        if (false == video_widget_list_[i]->IsJoin())
        {
            video_widget_list_[i]->SetJoinStatus(true);
            video_widget_list_[i]->SetCenterName(QString::number(uid));
            void* hwnd = video_widget_list_[i]->GetVideoHwnd();
            engine_->SetupRemoteVideo(uid, hwnd);
            user_count_++;
            adjustVideoLayout();
            break;
        }
    }
}

void CallWidget::onUserVideoStart(const quint64& uid, const int& profile)
{
    qDebug() << "NECallWidget::onUserVideoStart: uid:" << uid << ", profile: " << profile;

    int ret = engine_->SubscribeRemoteVideoStream(uid, nertc::kNERtcRemoteVideoStreamTypeHigh, true);
    if (ret)
    {
        qDebug() << "can not subscribe remote video stream! ret: " << ret;
    }
}

void CallWidget::onUserLeft(const quint64& uid, const int& result)
{
    qDebug() << "CallWidget::onUserLeft";
    for (int i = 1; i < max_count_; ++i)
    {
        QString id_str = video_widget_list_[i]->GetUserId();
        if (id_str.toInt() == uid)
        {
            video_widget_list_[i]->SetJoinStatus(false);
            video_widget_list_[i]->SetCenterName("");
        }
    }
    user_count_--;
    adjustVideoLayout();
    engine_->SetupRemoteVideo(uid, nullptr);
}

