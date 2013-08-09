# Linux build dependency for qt-speech: Festival
# apt-get install festival festival-dev

TEMPLATE = subdirs
SUBDIRS  = speech qt-speech
speech.depends = qt-speech
