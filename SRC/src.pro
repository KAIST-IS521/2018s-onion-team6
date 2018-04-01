QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    onion_messenger.cpp \
    heartbeat.cpp \
    user_info.cpp \
    shell.cpp \
    socket.cpp \
    PgpManager.cpp \
    msgclient.cpp \
    msgserver.cpp \
    heartbeat.cpp \
    jsoncpp.cpp \
    main.cpp \
    msgclient.cpp \
    msgserver.cpp \
    onion_messenger.cpp \
    PgpManager.cpp \
    serversocket.cpp \
    shell.cpp \
    socket.cpp \
    socketaddress.cpp \
    user_info.cpp \
    pgpmanager.cpp

HEADERS += \
    onion_messenger.h \
    heartbeat.h \
    user_info.h \
    shell.h \
    socket.h \
    PgpManager.h \
    config.h \
    clientsocket.h \
    config.h \
    heartbeat.h \
    msgclient.h \
    msgserver.h \
    onion_messenger.h \
    PgpManager.h \
    serversocket.h \
    shell.h \
    socket.h \
    socketaddress.h \
    user_info.h \
    pgpmanager.h

SUBDIRS += \
    src.pro

DISTFILES += \
    src.pro.user
