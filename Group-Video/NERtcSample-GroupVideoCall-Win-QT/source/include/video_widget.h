#ifndef _VIDEO_WIDGET_H
#define _VIDEO_WIDGET_H

#include <QWidget>

class QLabel;
class VideoWidget: public QWidget
{
public:
    VideoWidget(QWidget* parent = nullptr);
    ~VideoWidget();

public:
    // 获取窗口句柄
    void* GetVideoHwnd();

    // 窗口是否已有用户加入
    const bool IsJoin();

    // 设置状态
    void SetJoinStatus(const bool    &state);

    void SetCenterName(const QString &name);

    // 获取uid
    const QString GetUserId();

private:
    void setUi();

private:
    QLabel* center_name_label_;
    bool    is_join_ = false;
};

#endif //_VIDEO_WIDGET_H
