MODINSTDIR = speech

include(../../modules.pri)

SOURCES = speech.cpp
HEADERS = speech.h
TBL_SOURCES = speech.tbl

OTHER_FILES = speech.xl speech.tbl traces.tbl
OTHER_FILES += doc/speech.doxy.h doc/Doxyfile.in

INSTALLS    += thismod_icon

LICENSE_FILES = speech.taokey.notsigned
include(../../licenses.pri)

QT += core
LIBS += -L../qt-speech -lQtSpeechd

macx {
    LIBS *= -framework AppKit
}


QMAKE_SUBSTITUTES = doc/Doxyfile.in
QMAKE_DISTCLEAN = doc/Doxyfile
DOXYFILE = doc/Doxyfile
DOXYLANG = en,fr
include(../../modules_doc.pri)
