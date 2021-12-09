#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "rtcengine.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_yuvDataComming(uint32_t uid, std::vector<unsigned char> data_y, std::vector<unsigned char> data_u, std::vector<unsigned char> data_v, int w, int h);

    void on_join_clicked();

    void on_leave_clicked();

    void on_preview_start_clicked();

    void on_preview_stop_clicked();

private:
    Ui::MainWindow *ui;
    RtcEngine *rtc_engine;
};
#endif // MAINWINDOW_H
