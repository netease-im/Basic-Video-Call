#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QLabel>
#include <QDebug>
#include "engine.h"
#include "join_widget.h"

JoinWidget::JoinWidget(QWidget *parent /*= nullptr*/)
:QMainWindow(parent)
{
    setWindowTitle(QString::fromLocal8Bit("多人通话"));
    setFixedSize(460, 470);

    this->setUi();

    engine_ = std::make_shared<Engine>();

    call_widget_ = new CallWidget(engine_.get());
    call_widget_->hide();

    //
    connect(join_btn_, &QPushButton::clicked, this, &JoinWidget::onBtnJoinClicked);
}

JoinWidget::~JoinWidget()
{
    qDebug() << "JoinWidget::~JoinWidget begin";
    delete call_widget_;
    qDebug() << "JoinWidget::~JoinWidget";
}

void JoinWidget::setUi()
{
    QWidget *central_widget = new QWidget(this);
    central_widget->setStyleSheet("background-color: rgb(255, 255, 255);");

    //
    join_btn_ = new QPushButton(central_widget);
    join_btn_->setText(u8"加入频道");
    join_btn_->setGeometry(QRect(70, 350, 320, 50));
    join_btn_->setCursor(QCursor(Qt::PointingHandCursor));
    join_btn_->setStyleSheet("QPushButton{background-color: rgb(51, 126, 255);\
                                          border-radius: 25px;\
                                          font-size: 16px;\
                                          color: #FFFFFF;\
                                          width: 320;\
                                          height: 50;}");

    //
    channel_name_edit_ = new QLineEdit(central_widget);
    channel_name_edit_->setPlaceholderText(u8"输入相同房间号即可通话");
    channel_name_edit_->setGeometry(QRect(70, 95, 320, 44));
    channel_name_edit_->setStyleSheet("QLineEdit{font-size: 17px;\
                                                 color: #B0B6BE;\
                                                 border-width: 0px;}");

    //
    nick_name_edit_ = new QLineEdit(central_widget);
    nick_name_edit_->setPlaceholderText(u8"输入昵称");
    nick_name_edit_->setGeometry(QRect(70, 165, 320, 44));
    nick_name_edit_->setStyleSheet("QLineEdit{font-size: 17px;\
                                              color: #B0B6BE;\
                                              border-width: 0px;}");

    //
    open_camera_ = new QCheckBox(central_widget);
    open_camera_->setText(u8"入会时打开摄像头");
    open_camera_->setGeometry(QRect(70, 235, 181, 21));
    open_camera_->setChecked(true);

    //
    open_mic_ = new QCheckBox(central_widget);
    open_mic_->setText(u8"入会时打开麦克风");
    open_mic_->setGeometry(QRect(70, 265, 161, 31));
    open_mic_->setChecked(true);

    //
    QLabel *join_channel_label = new QLabel(central_widget);
    join_channel_label->setText(u8"加入频道");
    join_channel_label->setStyleSheet("QLabel{font-size: 24px;\
                                              color: #333333;}");
    join_channel_label->setGeometry(QRect(182, 20, 96, 44));


    this->setCentralWidget(central_widget);
}

void JoinWidget::onBtnJoinClicked()
{
    JoinInfo join_info;
    join_info.channel_name_ = channel_name_edit_->text();
    join_info.uid_ = nick_name_edit_->text();
    join_info.open_camera_ = open_camera_->isChecked();
    join_info.open_mic_ = open_mic_->isChecked();

    if (0 == call_widget_->JoinChannel(join_info))
    {
        this->hide();
    }
}
