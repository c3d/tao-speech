# Linux build dependency for qt-speech: Festival
# apt-get install festival festival-dev

TEMPLATE = subdirs
SUBDIRS  = speech qt-speech
speech.depends = qt-speech

!build_pass:linux-g++*:!exists(/usr/include/festival/festival.h):error("You need the Festival library: apt-get install festival festival-dev")

QMAKE_SUBSTITUTES = doc/Doxyfile.in
QMAKE_DISTCLEAN = doc/Doxyfile
DOXYFILE = doc/Doxyfile
DOXYLANG = en,fr
include(speech.pri)
include(../modules_doc.pri)
