# ******************************************************************************
# speech.pro                                                       Tao3D project
# ******************************************************************************
#
# File description:
#
#
#
#
#
#
#
#
# ******************************************************************************
# This software is licensed under the GNU General Public License v3
# (C) 2013, Baptiste Soulisse <baptiste.soulisse@taodyne.com>
# (C) 2013, Catherine Burvelle <catherine@taodyne.com>
# (C) 2013-2014,2019, Christophe de Dinechin <christophe@dinechin.org>
# (C) 2013, Jérôme Forissier <jerome@taodyne.com>
# ******************************************************************************
# This file is part of Tao3D
#
# Tao3D is free software: you can r redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Tao3D is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Tao3D, in a file named COPYING.
# If not, see <https://www.gnu.org/licenses/>.
# ******************************************************************************
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
