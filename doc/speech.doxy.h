/**
 * @~english
 * @taomoduledescription{Speech, Speech synthesis module}
 * <tt>import Speech</tt> - The speech synthesis module lets your presentations speak.@n
 *
 * This module provides a @ref say function to speak a text out loud,
 * and @ref voice to change the voice used for speech.
 *
 * To say "Hello World", use:
 * @code
import Speech
say "Hello World"
 * @endcode
 *
 * Only one message is being said at any given time. A new message will
 * interrupt the previous spoken message. For example, you can create a simple
 * talking clock with the following:
 * @code
import Speech
say "It is currently " & text hours & " hours and " & text minutes & " minutes"
 * @endcode
 *
 * You can change the voice with the @ref voice command. The list of
 * voices is system-dependent. A comma-separated list of available
 * voices on the current system is returned by the @ref voices
 * command. The following example lets you listen to each of the
 * available voices on the system:
 * @code
import Speech
speech_page with voices
speech_page V:text ->
    page "Voice " & V,
        voice V
        text_box 0, 0, window_width, window_height,
            align 0.5
            vertical_align 0.5
            text "Currently playing the voice named " & V
            say "Your are currently listening to the voice named " & V
 * @endcode
 *
 * @endtaomoduledescription{Speech}
 *
 * @~french
 * @taomoduledescription{Speech, Synthèse vocale}
 * <tt>import Speech</tt> - Permet à vos présentation de parler.@n
 *
 * Ce module fournit une fonction @ref say pour réciter un texte,
 * et @ref voice pour changer la voix utilisée pour parler.
 *
 * À noter que certains systèmes peuvent ne fournir que la langue
 * anglaise par défaut, ou demander l'installation de voix
 * supplémentaires pour parler dans d'autres langues que l'anglais.
 *
 * Pour dire "Hello World", utilisez le code suivant:
 * @code
import Speech
say "Hello World"
 * @endcode
 *
 * Un seul message est prononcé à un moment donné. Un nouveau message
 * interrompra automatiquement le message parlé précédent. Par
 * exemple, vous pouvez créer une horloge parlante simple avec le code
 * suivant:
 * @code
import Speech
say "It is currently " & text hours & " hours and " & text seconds
 * @endcode
 *
 * Vous pouvez changer la voix utilisée pour parler en utilisant
 * la commande @ref voice. La liste des voix disponibles dépend
 * largement du système utilisé. La fonction @ref voices retourne une
 * liste XL des voix disponibles sur le système en cours. L'exemple
 * suivant vous permettra d'écouter chacune des voix disponibles sur
 * le système:
 * @code
import Speech
speech_page with voices
speech_page V:text ->
    page "Voice " & V,
        voice V
        text_box 0, 0, window_width, window_height,
            align 0.5
            vertical_align 0.5
            text "Currently playing the voice named " & V
            say "Your are currently listening to the voice named " & V
 * @endcode
 *
 * @endtaomoduledescription{Speech}
 *
 * @~
 * @{
 */

/**
 * @~english
 * Speak a given text.
 * Pronounce the given text through the speech synthesizer.
 * The text given by the @p speech argument will be spoken out loud.
 * The function returns @a true while speaking, @a false otherwise.
 * @~french
 * Énonce le texte donné.
 * Prononce le texte donné en utilisant le synthétiseur vocal.
 * Cette fonction retourne @a true tant que le texte est prononcé,
 * et @a false sinon.
 * @~
 */
boolean say(speech:text);

/**
 * @~english
 * Change the voice being used by the speech synthesizer.
 * The voice being used by subsequent @ref say commands will be the
 * voice with the name given in @p name. The voice will not be changed
 * if the name does not match one of the available voices.
 * The function returns the name of the current voice.
 * @~french
 * Change la voix utilisée par le synthétiseur vocal.
 * La voix utilisée pour les commandes @ref say suivantes sera celle
 * donnée en argument dans @p name. La voix ne changera pas si ce nom
 * ne correspond pas à une voix disponible.
 * Cette fonction retourne le nom de la voix en cours.
 * @~
 */
text voice(name:text);

/**
 * @~english
 * Return the list of available voices on the system.
 * This function returns a comma-separated list of all the speech synthesizer
 * voices available on the current system.
 * @~french
 * Retourne la liste des voix disponibles sur le système.
 * Cette fonction retourne une liste de toutes les voix de synthèse
 * vocale disponibles sur le système actuel.
 * @~
 */
tree voices();


/**
 * @}
 */
