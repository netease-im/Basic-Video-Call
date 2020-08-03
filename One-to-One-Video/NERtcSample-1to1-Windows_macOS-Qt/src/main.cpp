//  Created by NetEase on 8/3/2020.
//  Copyright (c) 2014-2020 NetEase, Inc. All rights reserved.
//

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFont>
#include "frameprovider.h"
#include "nrtc_engine.h"

#ifdef WIN32
#include "app_dump.h"
#endif

int main(int argc, char* argv[]) {
#ifdef WIN32
    ::SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);
#endif

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    //设置默认字体
    QFont font;
    font.setFamily("PingFang SC");
    app.setFont(font);

    //std::unique_ptr<NRTCEngine> m_engine(new NRTCEngine);
    NRTCEngine* m_engine = new NRTCEngine;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("NRTCEngine", m_engine);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    qmlRegisterType<FrameProvider>("FrameProvider", 1, 0, "FrameProvider");  

    int ret = app.exec();
    //m_engine.release();
    delete m_engine;
    return ret;
}
