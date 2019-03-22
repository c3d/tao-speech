// *****************************************************************************
// speech.h                                                        Tao3D project
// *****************************************************************************
//
// File description:
//
//     Speech interface for Tao3D
//
//
//
//
//
//
//
//
// *****************************************************************************
// This software is licensed under the GNU General Public License v3
// (C) 2013, Baptiste Soulisse <baptiste.soulisse@taodyne.com>
// (C) 2013, Catherine Burvelle <catherine@taodyne.com>
// (C) 2013-2014,2019, Christophe de Dinechin <christophe@dinechin.org>
// (C) 2013, Jérôme Forissier <jerome@taodyne.com>
// *****************************************************************************
// This file is part of Tao3D
//
// Tao3D is free software: you can r redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Tao3D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Tao3D, in a file named COPYING.
// If not, see <https://www.gnu.org/licenses/>.
// *****************************************************************************

#include "tree.h"
#include"tao_utf8.h"
#include "../qt-speech/QtSpeech.h"

XL::Name_p speech_say(XL::Tree_p self, text what);
XL::Text_p speech_voice(XL::Tree_p self, text voice);
XL::Tree_p speech_voices(XL::Tree_p self, int count);

using namespace Tao;
using namespace QtSpeech_v1;


struct Speech : QtSpeech
{
    Q_OBJECT
public:
    Speech(VoiceName n = VoiceName()): QtSpeech(n), speaking(""), done(false)
    {
        connect(this, SIGNAL(finished()), this, SLOT(speechFinished()));
    }
    ~Speech() { tell(""); }

    void speak(QString s)
    {
        if (speaking != s)
        {
            IFTRACE(speech)
                std::cerr << "Speech: Starting to say \"" << +s << "\"\n";
            speaking = s;
            done = false;
            tell(s);
        }
    }

    bool doneSpeaking() { return done; }

public slots:
    void speechFinished()
    {
        IFTRACE(speech)
            std::cerr << "Speech: Done saying \"" << +speaking << "\"\n";
        done = true;
    }

private:
    QString speaking;
    bool    done;
};
