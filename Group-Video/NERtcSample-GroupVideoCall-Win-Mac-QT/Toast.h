/** @file   Toast.h
 *  @brief  Qtģ�ⰲ׿�ƶ��ͻ���Toast��ʾ��Ϣ
 *  @note   qss set in ui file
 *  @author liangkdm
 *  @date   2020/09/22
 */
#pragma once

#include <QtWidgets/QWidget>
#include "ui_Toast.h"

class Toast : public QWidget
{
    Q_OBJECT

public:
    Toast(QWidget *parent = Q_NULLPTR);
    ~Toast();

    void setText(const QString& text);

    void showAnimation(int timeout = 2000);// ������ʽshow����Ĭ��2�����ʧ

public:
    // ��̬����
    static void showTip(const QString& text, QWidget* parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    Ui::ToastClass ui;
};
