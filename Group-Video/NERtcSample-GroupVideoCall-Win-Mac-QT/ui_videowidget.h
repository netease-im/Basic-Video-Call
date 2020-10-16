/********************************************************************************
** Form generated from reading UI file 'videowidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOWIDGET_H
#define UI_VIDEOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_videowidget
{
public:
    QWidget *toolbar;
    QLabel *uid;
    QWidget *video;

    void setupUi(QWidget *videowidget)
    {
        if (videowidget->objectName().isEmpty())
            videowidget->setObjectName(QString::fromUtf8("videowidget"));
        videowidget->resize(400, 300);
        toolbar = new QWidget(videowidget);
        toolbar->setObjectName(QString::fromUtf8("toolbar"));
        toolbar->setGeometry(QRect(0, 0, 400, 12));
        toolbar->setMinimumSize(QSize(0, 12));
        toolbar->setMaximumSize(QSize(16777215, 12));
        toolbar->setStyleSheet(QString::fromUtf8(""));
        uid = new QLabel(toolbar);
        uid->setObjectName(QString::fromUtf8("uid"));
        uid->setGeometry(QRect(0, 0, 54, 12));
        video = new QWidget(videowidget);
        video->setObjectName(QString::fromUtf8("video"));
        video->setGeometry(QRect(0, 12, 400, 300));
        video->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0)"));

        retranslateUi(videowidget);

        QMetaObject::connectSlotsByName(videowidget);
    } // setupUi

    void retranslateUi(QWidget *videowidget)
    {
        videowidget->setWindowTitle(QCoreApplication::translate("videowidget", "Form", nullptr));
        uid->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class videowidget: public Ui_videowidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOWIDGET_H
