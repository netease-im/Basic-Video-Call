/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainwindowClass
{
public:
    QWidget *centralWidget;
    QPushButton *joinChannel;
    QLineEdit *roomid;
    QLineEdit *userId;
    QComboBox *video_comboBox;
    QComboBox *audio_comboBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QMainWindow *mainwindowClass)
    {
        if (mainwindowClass->objectName().isEmpty())
            mainwindowClass->setObjectName(QString::fromUtf8("mainwindowClass"));
        mainwindowClass->resize(475, 327);
        centralWidget = new QWidget(mainwindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        joinChannel = new QPushButton(centralWidget);
        joinChannel->setObjectName(QString::fromUtf8("joinChannel"));
        joinChannel->setGeometry(QRect(180, 270, 91, 31));
        roomid = new QLineEdit(centralWidget);
        roomid->setObjectName(QString::fromUtf8("roomid"));
        roomid->setGeometry(QRect(130, 50, 211, 31));
        userId = new QLineEdit(centralWidget);
        userId->setObjectName(QString::fromUtf8("userId"));
        userId->setGeometry(QRect(130, 100, 211, 31));
        video_comboBox = new QComboBox(centralWidget);
        video_comboBox->setObjectName(QString::fromUtf8("video_comboBox"));
        video_comboBox->setGeometry(QRect(130, 150, 211, 31));
        audio_comboBox = new QComboBox(centralWidget);
        audio_comboBox->setObjectName(QString::fromUtf8("audio_comboBox"));
        audio_comboBox->setGeometry(QRect(130, 200, 211, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 150, 51, 31));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, 200, 51, 31));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 50, 51, 31));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(50, 100, 51, 31));
        mainwindowClass->setCentralWidget(centralWidget);

        retranslateUi(mainwindowClass);

        QMetaObject::connectSlotsByName(mainwindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *mainwindowClass)
    {
        mainwindowClass->setWindowTitle(QCoreApplication::translate("mainwindowClass", "mainwindow", nullptr));
        joinChannel->setText(QCoreApplication::translate("mainwindowClass", "\345\212\240\345\205\245\351\242\221\351\201\223", nullptr));
        roomid->setPlaceholderText(QCoreApplication::translate("mainwindowClass", "\350\276\223\345\205\245\347\233\270\345\220\214\346\210\277\351\227\264\345\217\267\345\215\263\345\217\257\351\200\232\350\257\235", nullptr));
        userId->setPlaceholderText(QCoreApplication::translate("mainwindowClass", "\350\276\223\345\205\245userID", nullptr));
        label->setText(QCoreApplication::translate("mainwindowClass", "\350\247\206\351\242\221\350\256\276\345\244\207", nullptr));
        label_2->setText(QCoreApplication::translate("mainwindowClass", "\351\237\263\351\242\221\350\256\276\345\244\207", nullptr));
        label_3->setText(QCoreApplication::translate("mainwindowClass", "\346\210\277\351\227\264ID", nullptr));
        label_4->setText(QCoreApplication::translate("mainwindowClass", "\347\224\250\346\210\267ID", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainwindowClass: public Ui_mainwindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
