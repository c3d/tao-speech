// ****************************************************************************
//  speech.h                                                       Tao project 
// ****************************************************************************
// 
//   File Description:
// 
//     Speech interface for Tao Presentations
// 
// 
// 
// 
// 
// 
// 
// 
// ****************************************************************************
// This software is licensed under the GNU General Public License v3.
// See file COPYING for details.
//  (C) 2011 Christophe de Dinechin <christophe@taodyne.com>
//  (C) 2011 Taodyne SAS
// ****************************************************************************

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
