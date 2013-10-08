include(../speech.pri)
include(../../modules.pri)

SOURCES = speech.cpp
HEADERS = speech.h
TBL_SOURCES = speech.tbl

OTHER_FILES = speech.xl speech.tbl traces.tbl

INSTALLS    += thismod_icon

QT += core
LIBS += -L../qt-speech/\$(DESTDIR) -lQtSpeech

macx {
    LIBS *= -framework AppKit
}

unix:!mac {
    LIBS += -lncurses
    LIBS += -L$$PWD/festival/festival/src/lib -lFestival
    LIBS += -L$$PWD/festival/speech_tools/lib -lestools -lestbase -leststring
}
