MODINSTDIR = speech
include(../../modules.pri)

SOURCES = speech.cpp
HEADERS = speech.h
TBL_SOURCES = speech.tbl

OTHER_FILES = speech.xl speech.tbl traces.tbl
OTHER_FILES += doc/speech.doxy.h doc/Doxyfile.in

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

QMAKE_SUBSTITUTES = doc/Doxyfile.in
QMAKE_DISTCLEAN = doc/Doxyfile
DOXYFILE = doc/Doxyfile
DOXYLANG = en,fr
include(../../modules_doc.pri)
