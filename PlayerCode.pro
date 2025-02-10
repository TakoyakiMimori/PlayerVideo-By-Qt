QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH = $$PWD/include
LIBS += -L$$PWD/lib
LIBS += -llibvlc
LIBS += -llibvlccore
#QMAKE_POST_LINK += $$escape_expand( \\n\
#        xcopy /Y \"$$VLC_SDK_PATH\\lib\\*.dll\" "$$OUT_PWD\\debug\" && \
#        xcopy /Y \"$$VLC_SDK_PATH\\lib\\*.dll\" "$$OUT_PWD\\release\" \
#    )

SOURCES += \
    CVlc.cpp \
    header.cpp \
    main.cpp \
    mainwindow.cpp \
    playerwindow.cpp

HEADERS += \
    CVlc.h \
    header.h \
    mainwindow.h \
    playerwindow.h

FORMS += \
    mainwindow.ui \
    playerwindow.ui \
    playerwindow.ui
CONFIG += PRECOMPILED_HEADER
PRECOMPILED_DIR += .
PRECOMPILED_HEADER += header.h

############ 设置输出路径、文件名、加载的链接库 ###############
CONFIG(debug, debug|release){
    DESTDIR =$$PWD/bin/bin_Debug # 输出目录
    TARGET = XVLCDemod  # 输出文件名
}
else{
    DESTDIR =$$PWD/bin/bin_Release
    TARGET = XVLCDemo
}
