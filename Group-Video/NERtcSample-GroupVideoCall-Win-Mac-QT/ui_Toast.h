/********************************************************************************
** Form generated from reading UI file 'Toast.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOAST_H
#define UI_TOAST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ToastClass
{
public:
    QGridLayout *gridLayout;
    QLabel *label;

    void setupUi(QWidget *ToastClass)
    {
        if (ToastClass->objectName().isEmpty())
            ToastClass->setObjectName(QString::fromUtf8("ToastClass"));
        ToastClass->resize(170, 52);
        ToastClass->setMinimumSize(QSize(0, 52));
        ToastClass->setMaximumSize(QSize(16777215, 52));
        gridLayout = new QGridLayout(ToastClass);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(ToastClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("background-color: rgba(211,211,211,0.80);\n"
"border-radius: 10px;\n"
"color: #000000;\n"
"font-family: microsoft yahei;\n"
"font-size: 16px;\n"
"padding-left:25px;\n"
"padding-right:25px;"));
        label->setAlignment(Qt::AlignCenter);
        label->setIndent(-1);

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(ToastClass);

        QMetaObject::connectSlotsByName(ToastClass);
    } // setupUi

    void retranslateUi(QWidget *ToastClass)
    {
        ToastClass->setWindowTitle(QCoreApplication::translate("ToastClass", "Toast", nullptr));
        label->setText(QCoreApplication::translate("ToastClass", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ToastClass: public Ui_ToastClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOAST_H
