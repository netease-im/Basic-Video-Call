#ifndef _JOIN_WIDGET_H
#define _JOIN_WIDGET_H

#include <QMainWindow>
#include "call_widget.h"

class QPushButton;
class QLineEdit;
class QCheckBox;
class CallWidget;
class Engine;
class JoinWidget: public QMainWindow
{
    Q_OBJECT

public:
    JoinWidget(QWidget *parent = nullptr);
    ~JoinWidget();

private:
    void setUi();

private Q_SLOTS:
    void onBtnJoinClicked();

private:
    QPushButton* join_btn_;
    QLineEdit*   channel_name_edit_;
    QLineEdit*   nick_name_edit_;
    QCheckBox*   open_camera_;
    QCheckBox*   open_mic_;
    CallWidget*  call_widget_;

private:
    std::shared_ptr<Engine> engine_;
};

#endif //_JOIN_WIDGET_H
