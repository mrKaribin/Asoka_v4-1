QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DefaultTypes/Assistent/assistent.cpp \
    Engine/System/system.cpp \
    Engine/engine.cpp \
    Instruments/SQL/SQLITE/libs/windows/shell.c \
    Instruments/SQL/SQLITE/libs/windows/sqlite3.c \
    Instruments/SQL/SQLITE/sqlite.cpp \
    main.cpp \

HEADERS += \
    DefaultTypes/Assistent/Linguistics/adjective.h \
    DefaultTypes/Assistent/Linguistics/morpheme_analyzer.h \
    DefaultTypes/Assistent/Linguistics/noun.h \
    DefaultTypes/Assistent/Linguistics/types.h \
    DefaultTypes/Assistent/Linguistics/verb.h \
    DefaultTypes/Assistent/Linguistics/word.h \
    DefaultTypes/Assistent/Logic/action.h \
    DefaultTypes/Assistent/Logic/functional.h \
    DefaultTypes/Assistent/Logic/lelement.h \
    DefaultTypes/Assistent/Logic/object.h \
    DefaultTypes/Assistent/Logic/property.h \
    DefaultTypes/Assistent/Logic/shape.h \
    DefaultTypes/Assistent/assistent.h \
    DefaultTypes/aarray.h \
    DefaultTypes/abytearray.h \
    DefaultTypes/aevent.h \
    DefaultTypes/astring.h \
    DefaultTypes/atime.h \
    Engine/System/acore.h \
    Engine/System/lcore.h \
    Engine/System/system.h \
    Engine/aidentifier.h \
    Engine/aobject.h \
    Engine/asoka.h \
    Engine/atask.h \
    Engine/athread.h \
    Engine/templates.h \
    Engine/typedefs.h \
    GUI/Console/console_interface.h \
    GUI/Console/console_logic.h \
    GUI/aconsole.h \
    GUI/awidget.h \
    Instruments/SQL/SQLITE/asqlite.h \
    Instruments/SQL/SQLITE/asqlite_reply.h \
    Instruments/SQL/SQLITE/asqlite_request.h \
    Instruments/SQL/SQLITE/libs/windows/sqlite3.h \
    Instruments/SQL/SQLITE/libs/windows/sqlite3ext.h \
    Instruments/Tester/engine.h \
    Instruments/Tester/tester.h \
    Instruments/utfcpp/utf8.h \
    Instruments/utfcpp/utf8/checked.h \
    Instruments/utfcpp/utf8/core.h \
    Instruments/utfcpp/utf8/unchecked.h \
    asoka_engine.h \

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
