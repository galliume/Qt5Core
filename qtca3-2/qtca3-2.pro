QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-qtca3-1-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/myLib/release/ -lmyLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-qtca3-1-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/myLib/debug/ -lmyLib
else:unix: LIBS += -L$$PWD/../build-qtca3-1-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/myLib/ -lmyLib

INCLUDEPATH += $$PWD/../build-qtca3-1-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/myLib/debug
DEPENDPATH += $$PWD/../build-qtca3-1-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/myLib/debug

HEADERS += \
    myLib_global.h \
    mylib.h
