// *****************************************************************************
// speech.cpp                                                      Tao3D project
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

#include "speech.h"
#include "tao/module_api.h"


static Speech *speech_current_voice = NULL;


XL::Name_p speech_say(XL::Tree_p self, text what)
// ----------------------------------------------------------------------------
//   Say something through the loudspeaker
// ----------------------------------------------------------------------------
{
    try
    {
        if (!speech_current_voice)
            speech_voice(self, "");

        if (speech_current_voice)
        {
            speech_current_voice->speak(+what);
            if (speech_current_voice->doneSpeaking())
                return XL::xl_false;
        }
    }
    catch (QtSpeech::Error &e)
    {
        IFTRACE(speech)
            std::cerr << "Speech error: " << +e.msg << "\n";
        return XL::xl_false;
    }

    return XL::xl_true;
}


XL::Text_p speech_voice(XL::Tree_p self, text voice)
// ----------------------------------------------------------------------------
//   Select the current voice
// ----------------------------------------------------------------------------
{
    QString qvoice = +voice;

    if (!speech_current_voice ||
        speech_current_voice->name().name != qvoice)
    {
        IFTRACE(speech)
            std::cerr << "Requesting voice '" << voice << "'\n";
        try
        {
            Speech::VoiceNames voiceNames = Speech::voices();
            foreach (Speech::VoiceName voiceName, voiceNames)
            {
                IFTRACE(speech)
                    std::cerr << "id=" << +voiceName.id
                              << " name=" << +voiceName.name
                              << "\n";
                if (voiceName.name == qvoice)
                {
                    IFTRACE(speech)
                        std::cerr << "Selecting " << +voiceName.name
                                  << " id " << +voiceName.id
                                  << "\n";
                    delete speech_current_voice;
                    speech_current_voice = new Speech(voiceName);
                    break;
                }
            }

            if (!speech_current_voice)
            {
                IFTRACE(speech)
                    std::cerr << "Selecting default voice\n";
                speech_current_voice = new Speech();
            }
        }
        catch (QtSpeech::Error &e)
        {
            IFTRACE(speech)
                std::cerr << "Speech error: " << +e.msg << "\n";
            return new XL::Text("Speech error: " + +e.msg,
                                "\"", "\"", self->Position());
        }
    }

    return new XL::Text(+speech_current_voice->name().name,
                        "\"", "\"", self->Position());
}


XL::Tree_p speech_voices(XL::Tree_p self, int count)
// ----------------------------------------------------------------------------
//   Return a comma-separated list of available voices
// ----------------------------------------------------------------------------
{
    try
    {
        XL::Tree_p          result     = NULL;
        XL::Tree_p         *parent     = &result;
        Speech::VoiceNames  voiceNames = Speech::voices();
        XL::TreePosition    pos        = self->Position();

        foreach (Speech::VoiceName voiceName, voiceNames)
        {
            if (count-- <= 0)
                break;

            XL::Text_p vname = new XL::Text(+voiceName.name, "\"", "\"", pos);
            if (*parent)
            {
                XL::Infix *infix = new XL::Infix(",", *parent, vname, pos);
                *parent = infix;
                parent = &infix->right;
            }
            else
            {
                *parent = vname;
            }
        }

        if (!result)
            return XL::xl_nil;

        return result;
    }
    catch (QtSpeech::Error &e)
    {
        IFTRACE(speech)
            std::cerr << "Speech error: " << +e.msg << "\n";
        return new XL::Text("Speech error: " + +e.msg,
                            "\"", "\"", self->Position());
    }

    return XL::xl_nil;
}


int module_exit()
{
    if (speech_current_voice)
    {
        IFTRACE(speech)
            std::cerr << "Speech: module_exit: deleting current voice\n";
        delete speech_current_voice;
        speech_current_voice = NULL;
    }
    return 0;
}

XL_DEFINE_TRACES
