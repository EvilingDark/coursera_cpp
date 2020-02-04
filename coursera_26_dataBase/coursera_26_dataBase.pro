TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        condition_parser.cpp \
        database.cpp \
        date.cpp \
        main.cpp \
        node.cpp \
        token.cpp

HEADERS += \
    condition_parser.h \
    condition_parser_test.h \
    database.h \
    date.h \
    node.h \
    test_runner.h \
    token.h
