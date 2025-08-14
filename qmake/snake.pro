QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    ../main.cpp \
    ../components/selector.cpp \
    ../components/controller.cpp \
    ../components/model/tetris_model.cpp \
    ../components/view/cli_view.cpp \
    ../components/view/desktop_view.cpp \
    ../brick_game/tetris/fsm.c \
    ../brick_game/tetris/backend.c \
    ../brick_game/snake/snakemodel.cpp \
    ../gui/desktop/gamefield.cpp \
    ../gui/desktop/mainwindow.cpp \
    ../gui/cli/frontend.c

HEADERS += \
    ../components/selector.h \
    ../components/controller.h \
    ../components/model.h \
    ../components/specification.h \
    ../components/model/tetris_model.h \
    ../components/view/cli_view.h \
    ../components/view/desktop_view.h \
    ../components/view/view.h \
    ../brick_game/tetris/backend.h \
    ../brick_game/tetris/defines.h \
    ../brick_game/tetris/fsm.h \
    ../brick_game/tetris/types.h \
    ../brick_game/snake/snakemodel.h \
    ../brick_game/snake/types.h \
    ../gui/desktop/mainwindow.hpp \
    ../gui/cli/frontend.h

FORMS += \
    ../gui/desktop/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../gui/desktop/icons.qrc

LIBS += -lncurses
DESTDIR = ../build
OBJECTS_DIR = $${DESTDIR}/objects
MOC_DIR = $${DESTDIR}/moc
RCC_DIR = $${DESTDIR}/rcc
UI_DIR = $${DESTDIR}/ui