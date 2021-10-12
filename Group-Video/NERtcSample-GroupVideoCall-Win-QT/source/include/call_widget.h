#ifndef _CALL_WIDGET_H
#define _CALL_WIDGET_H

#include <QWidget>
#include <QList>

struct JoinInfo
{
    bool open_mic_;
    bool open_camera_ ;
    QString channel_name_;
    QString uid_;
};

class QHBoxLayout;
class QVBoxLayout;
class VideoWidget;
class Engine;
class CallWidget: public QWidget
{
    Q_OBJECT

public:
    CallWidget(Engine* engine, QWidget *parent = nullptr);
    ~CallWidget();

public:
    int JoinChannel(const JoinInfo &join_info);

private:
    void setUi();
    void adjustVideoLayout();
    void clearLayout();

private Q_SLOTS:
    void onJoinChannel(const quint64& uid, const int& reson);
    void onUserJoin(const quint64& uid, const QString& name);
    void onUserVideoStart(const quint64& uid, const int& profile);
    void onUserLeft(const quint64& uid, const int& result);

private:
    QVBoxLayout* vertical_layout_;

    QHBoxLayout* video_top_hlayout_;
    QHBoxLayout* video_middle_hlayout_;
    QHBoxLayout* video_bottom_hlayout_;

    QList<VideoWidget*> video_widget_list_;

private:
    Engine *engine_;
    int     user_count_ = 1;
    int     max_count_  = 9;
};

#endif //_CALL_WIDGET_H
