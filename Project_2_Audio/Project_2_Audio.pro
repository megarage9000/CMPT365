QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abac-master/bitstream.cpp \
    abac-master/cabac.cpp \
    abac-master/memory.cpp \
    abac-master/test.cpp \
    lzwmap.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    wavcompression.cpp \
    wavfile.cpp

HEADERS += \
    abac-master/base.h \
    abac-master/bitstream.h \
    abac-master/cabac.h \
    abac-master/math.h \
    abac-master/memory.h \
    abac-master/version.h \
    fromLittleEndian.h \
    lzwmap.h \
    mainwindow.h \
    qcustomplot.h \
    wavcompression.h \
    wavfile.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    abac-master/LICENSE \
    abac-master/Makefile \
    abac-master/README.md \
    abac-master/abac-test
