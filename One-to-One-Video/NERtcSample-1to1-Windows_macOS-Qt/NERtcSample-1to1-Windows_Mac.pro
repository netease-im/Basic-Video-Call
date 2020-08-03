TEMPLATE = app

QT += core\
    quick \
    gui \
    multimedia\
    svg

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/main.cpp \
        src/nrtc_engine.cpp \
        src/frameprovider.cpp \
        src/videorenderimpl.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

unix:!android {
    isEmpty(target.path) {
        qnx {
            target.path = /tmp/$${TARGET}/bin
        } else {
            target.path = /opt/$${TARGET}/bin
        }
        export(target.path)
    }
    INSTALLS += target
}

Debug:{
    DESTDIR     = Debug
    MOC_DIR     = Debug/.moc
    OBJECTS_DIR = Debug/.obj
    UI_DIR      = Debug/.ui
    RCC_DIR     = Debug/.rcc
}

Release:{
    DESTDIR     = Release
    MOC_DIR     = Release/.moc
    OBJECTS_DIR = Release/.obj
    UI_DIR      = Release/.ui
    RCC_DIR     = Release/.rcc
}

win32: {
    LIBS += -L$$PWD/nertc_sdk_win/dll/x64/ -L$$PWD/nertc_sdk_win/lib/x64/ -lnertc_sdk
    INCLUDEPATH += $$PWD/nertc_sdk_win/api
    DEPENDPATH += $$PWD/nertc_sdk_win/api

    LIBS += -L$$PWD/libyuv_win/lib/ -llibyuv
    INCLUDEPATH += $$PWD/libyuv_win
    DEPENDPATH += $$PWD/libyuv_win

}

HEADERS += \
    src/app_dump.h \
    src/nrtc_engine.h \
    src/frameprovider.h \
    src/videorenderimpl.h

macx: {
    LIBS += -L$$PWD/libyuv_mac/lib/ -lyuv
    INCLUDEPATH += $$PWD/libyuv_mac/include
    DEPENDPATH += $$PWD/libyuv_mac/include
    PRE_TARGETDEPS += $$PWD/libyuv_mac/lib/libyuv.a

    LIBS += -F$$PWD/nertc_sdk_mac/ -framework nertc_sdk_Mac
    INCLUDEPATH += $$PWD/nertc_sdk_mac/nertc_sdk_Mac.framework/Versions/A/Headers
    DEPENDPATH += $$PWD/nertc_sdk_mac/nertc_sdk_Mac.framework/Versions/A/Headers

    LIBS += -F$$PWD/nertc_sdk_mac/ -framework NEFundation_Mac
    INCLUDEPATH += $$PWD/nertc_sdk_mac/NEFundation_Mac.framework/Versions/A/Headers
    DEPENDPATH += $$PWD/nertc_sdk_mac/NEFundation_Mac.framework/Versions/A/Headers
}
