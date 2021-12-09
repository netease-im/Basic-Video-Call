QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    rtcengine.cpp \
    yuvrender.cpp

HEADERS += \
    NERtcSDK/include/nertc_audio_device_manager.h \
    NERtcSDK/include/nertc_base.h \
    NERtcSDK/include/nertc_base_types.h \
    NERtcSDK/include/nertc_device_collection.h \
    NERtcSDK/include/nertc_engine.h \
    NERtcSDK/include/nertc_engine_defines.h \
    NERtcSDK/include/nertc_engine_event_handler.h \
    NERtcSDK/include/nertc_engine_event_handler_ex.h \
    NERtcSDK/include/nertc_engine_ex.h \
    NERtcSDK/include/nertc_engine_media_stats_observer.h \
    NERtcSDK/include/nertc_error_code.h \
    NERtcSDK/include/nertc_introduction-cn.h \
    NERtcSDK/include/nertc_introduction.h \
    NERtcSDK/include/nertc_video_device_manager.h \
    NERtcSDK/include/nertc_warn_code.h \
    mainwindow.h \
    rtcengine.h \
    yuvrender.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -L$$PWD/NERtcSDK/lib/x86_64 -lnertc_sdk -lprotoopp

INCLUDEPATH += $$PWD/NERtcSDK/include
DEPENDPATH += $$PWD/NERtcSDK/include

DISTFILES += \
    NERtcSDK/lib/libnertc_sdk.so \
    NERtcSDK/lib/libprotoopp.so
