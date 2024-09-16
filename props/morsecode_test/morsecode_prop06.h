/*
Explanation of Requests

You want to create a morsecode_prop.h file that handles Morse code input via buttons on your lightsaber and displays the input and corresponding characters on an OLED screen (if available). Additionally:

    Morse Code Input: You want to use the power button to type Morse code and have the decoded character displayed on the lightsaber blade and the OLED screen (if present).
        Letters should display as blue on the blade, and numbers should display as red.
        The aux button should trigger sound playback of the Morse code.
    OLED Display: If an OLED screen is present (defined in my_config.h), the top half of the screen should display the typed Morse code, and the bottom half should display the decoded character.
        You want both Aurebesh and Latin characters to be displayed simultaneously, with Aurebesh first and Latin second, regardless of whether #define USE_AUREBESH_FONT is defined.
    Conditional OLED: The OLED display should only function if it's included in my_config.h, and if not, it should be ignored.
*/

//To do, addapt the speed of "dots", "dash", ... in function of the typing speed of the operator 

#ifndef PROPS_MORSECODE_PROP_H
#define PROPS_MORSECODE_PROP_H

#include "prop_base.h"
#include "../sound/sound_library.h"
#include <map>

// Define Morse Code Map
const char* morseCodeMap[][2] = {
    {"A", ".-"},   {"B", "-..."}, {"C", "-.-."}, {"D", "-.."},  {"E", "."},    {"F", "..-."},
    {"G", "--."},  {"H", "...."}, {"I", ".."},   {"J", ".---"}, {"K", "-.-"},  {"L", ".-.."},
    {"M", "--"},   {"N", "-."},   {"O", "---"},  {"P", ".--."}, {"Q", "--.-"}, {"R", ".-."},
    {"S", "..."},  {"T", "-"},    {"U", "..-"},  {"V", "...-"}, {"W", ".--"},  {"X", "-..-"},
    {"Y", "-.--"}, {"Z", "--.."},
    {"1", ".----"}, {"2", "..---"}, {"3", "...--"}, {"4", "....-"}, {"5", "....."},
    {"6", "-...."}, {"7", "--..."}, {"8", "---.."}, {"9", "----."}, {"0", "-----"}
};
/*
const char* morseMap[36] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",    // A-I
    ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",  // J-R
    "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",          // S-Z
    "-----", ".----", "..---", "...--", "....-", ".....",              // 0-5
    "-....", "--...", "---..", "----."                                 // 6-9
};
*/

// Define Aurebesh Map
const char* aurebeshMap[][2] = {
    {"A", "𐤀"}, {"B", "𐤁"}, {"C", "𐤂"}, {"D", "𐤃"}, {"E", "𐤄"}, {"F", "𐤅"}, {"G", "𐤆"}, 
    {"H", "𐤇"}, {"I", "𐤈"}, {"J", "𐤉"}, {"K", "𐤊"}, {"L", "𐤋"}, {"M", "𐤌"}, {"N", "𐤍"}, 
    {"O", "𐤎"}, {"P", "𐤏"}, {"Q", "𐤐"}, {"R", "𐤑"}, {"S", "𐤒"}, {"T", "𐤓"}, {"U", "𐤔"}, 
    {"V", "𐤕"}, {"W", "𐤖"}, {"X", "𐤗"}, {"Y", "𐤘"}, {"Z", "𐤙"},
    {"1", "𐤚"}, {"2", "𐤛"}, {"3", "𐤜"}, {"4", "𐤝"}, {"5", "𐤞"},
    {"6", "𐤟"}, {"7", "𐤠"}, {"8", "𐤡"}, {"9", "𐤢"}, {"0", "𐤣"}
};

#define DOT_DURATION 200  // Duration in ms for a dot
#define DASH_DURATION 600  // Duration in ms for a dash
#define LETTER_GAP 800  // Duration in ms between letters

class MorseCode : public PROP_INHERIT_PREFIX PropBase {
public:
    MorseCode() : morseCode_(""), lastPressTime_(0), currentType_('\0') {}

    const char* name() override { return "MorseCode"; }

    bool Event(enum BUTTON button, EVENT event) override {
        if (event == EVENT_PRESSED) {
            StartPress(button);
        } else if (event == EVENT_RELEASED) {
            EndPress(button);
        }
        return true;
    }

    void StartPress(BUTTON button) {
        lastPressTime_ = millis();
    }

    void EndPress(BUTTON button) {
        unsigned long pressDuration = millis() - lastPressTime_;
        
        if (pressDuration < DOT_DURATION) {
            morseCode_ += ".";
        } else if (pressDuration < DASH_DURATION) {
            morseCode_ += "-";
        }

        if (millis() - lastPressTime_ > LETTER_GAP) {
            InterpretMorse(button);
            morseCode_ = "";
        }
    }

    void InterpretMorse(BUTTON button) {
        for (int i = 0; i < 36; i++) {
            if (strcmp(morseCode_.c_str(), morseCodeMap[i][1]) == 0) {
                char letter = morseCodeMap[i][0][0];
                if (button == BUTTON_POWER) {
                    DisplayOnBlade(letter);
                } else if (button == BUTTON_AUX) {
                    PlayOnSpeaker(letter);
                }
                DisplayOnOLED(morseCode_, letter);
                break;
            }
        }
    }

    void DisplayOnBlade(char letter) {
        if (isalpha(letter)) {
            SetColor(0, 0, 255);  // Blue for letters
        } else if (isdigit(letter)) {
            SetColor(255, 0, 0);  // Red for numbers
        }
    }

    void PlayOnSpeaker(char letter) {
        // Implement sound playback
    }

    void DisplayOnOLED(const String& morseCode, char letter) {
#ifdef OLED_ENABLED
        DisplayOLED(morseCode.c_str(), letter);
#endif
    }

    void DisplayOLED(const char* morseCode, char letter) {
#ifdef USE_AUREBESH_FONT
        // Display Aurebesh + Latin if USE_AUREBESH_FONT is defined
        const char* aurebeshChar = GetAurebeshForLetter(letter);
        oled_display.println(morseCode);  // Morse code at the top
        oled_display.println(aurebeshChar);
        oled_display.println(letter);  // Latin equivalent
#else
        oled_display.println(morseCode);  // Morse code at the top
        oled_display.println(letter);  // Latin character
#endif
    }

    const char* GetAurebeshForLetter(char letter) {
        for (int i = 0; i < 36; i++) {
            if (aurebeshMap[i][0][0] == letter) {
                return aurebeshMap[i][1];
            }
        }
        return "?";  // Fallback for unsupported characters
    }

private:
    String morseCode_;
    unsigned long lastPressTime_;
    char currentType_;  // Holds the current character
};

#endif // PROPS_MORSECODE_PROP_H

/*
Explanation for Additions to my_config.h

    Enable OLED Screen: Add the option to use an OLED screen if available.
    Optional Aurebesh Font: Define USE_AUREBESH_FONT to use Aurebesh characters in addition to Latin characters on the OLED.
    Conditional Display: The OLED-related functionality should be enabled only if the OLED screen is included in the configuration.

Code to Add to my_config.h
*/

// Enable OLED if available
#define OLED_ENABLED

// Optional: Define to use Aurebesh font
// #define USE_AUREBESH_FONT

#ifdef OLED_ENABLED
#include "oled_display.h"  // Make sure the necessary OLED display library is included
#endif

/*
Key Points and Conclusion

    Morse Code Input: Use power and aux buttons to input Morse code. Power button controls blade effects, and aux button controls sound.
    Blade Effects: Blue for letters, red for numbers.
    OLED Display: If an OLED is available, display the Morse code on the top half and the decoded letter on the bottom half. Both Aurebesh and Latin characters are displayed simultaneously.
    Conditional OLED Usage: The OLED display is only enabled if it's defined in my_config.h, and Aurebesh can be optionally included via #define USE_AUREBESH_FONT.

This setup ensures Morse code interaction is flexible and provides appropriate feedback on both the blade and an OLED screen, while maintaining the option to display Aurebesh alongside Latin characters.
*/
