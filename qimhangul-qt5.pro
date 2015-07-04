# qimhangul-qt5 project file

TEMPLATE = lib
TARGET = qimhangul
VERSION = 0.0.1
DISTFILES += ChangeLog ChangeLog.old COPYING AUTHORS README
QT_PLUGIN_DIR = $$[QT_INSTALL_PLUGINS]

target.path = $${QT_PLUGIN_DIR}/platforminputcontexts
INSTALLS += target

CONFIG += debug plugin qt thread
PLUGIN_TYPE = platforminputcontexts
PLUGIN_CLASS_NAME = QHangulPlatformInputContextPlugin

QT += gui-private x11extras widgets

# Input
INCLUDEPATH += .
HEADERS += \
    main.h \
    qimhangulplatforminputcontext.h

SOURCES += \
    main.cpp \
    qimhangulplatforminputcontext.cpp

#OTHER_FILES += qimhangul-qt5.json

CONFIG += link_pkgconfig
PKGCONFIG += libhangul

unix {
    SOURCES += qimhangulplatforminputcontext_x11.cpp
}

