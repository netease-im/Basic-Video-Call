#include "Toast.h"
#include <QPropertyAnimation>
#include <QScreen>
#include <QGuiApplication>
#include <QPainter>
#include <QTimer>

Toast::Toast(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::Tool);// �ޱ߿� ��������
    setAttribute(Qt::WA_TranslucentBackground, true);   // ����͸��
}

Toast::~Toast()
{
}

void Toast::setText(const QString& text)
{
    ui.label->setText(text);
}

void Toast::showAnimation(int timeout /*= 2000*/)
{
    // ��ʼ����
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    show();

    QTimer::singleShot(timeout, [&]
    {
        // ��������
        QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
        animation->setDuration(1000);
        animation->setStartValue(1);
        animation->setEndValue(0);
        animation->start();
        connect(animation, &QPropertyAnimation::finished, [&]
        {
            close();
            deleteLater();// �رպ�����
        });
    });
}

void Toast::showTip(const QString& text, QWidget* parent /*= nullptr*/)
{
    Toast* toast = new Toast(parent);
    toast->setWindowFlags(toast->windowFlags() | Qt::WindowStaysOnTopHint); // �ö�
    toast->setText(text);
    toast->adjustSize();    //�������ı�������´�С

    toast->showAnimation();
}

void Toast::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    paint.begin(this);
    auto kBackgroundColor = QColor(255, 255, 255);
    kBackgroundColor.setAlpha(0.0 * 255);// ͸����Ϊ0 
    paint.setRenderHint(QPainter::Antialiasing, true);
    paint.setPen(Qt::NoPen);
    paint.setBrush(QBrush(kBackgroundColor, Qt::SolidPattern));//���û�ˢ��ʽ 
    paint.drawRect(0, 0, width(), height());
    paint.end();
}
