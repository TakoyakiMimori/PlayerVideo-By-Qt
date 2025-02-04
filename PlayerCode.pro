QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
VLC_SDK_PATH = "D:/File/VideoPlayer/PlayerCode"
INCLUDEPATH += \
    $$VLC_SDK_PATH/include
LIBS += \
    -L$$VLC_SDK_PATH/lib
LIBS += -llibvlc -llibvlccore

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
    playerwindow.ui
CONFIG += PRECOMPILED_HEADER
PRECOMPILED_DIR += $$VLC_SDK_PATH/include
PRECOMPILED_HEADER += header.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
