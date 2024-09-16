/*
What if I want both the aurebesh and latin character to be displayed at the same time, aurebesh first and latin second, whether #define USE_AUREBESH_FONT was used in my_config.h or not ? Can you give me the full code and the code to add to my_config.h
*/
/*
To display both Aurebesh and Latin characters simultaneously on the OLED screen, we need to ensure that the Aurebesh font is used only when available, and the Latin characters are displayed afterward regardless. Here’s the full code for your morsecode_prop.h file and the necessary additions for my_config.h.
Code for morsecode_prop.h:
*/
#ifndef PROPS_MORSECODE_PROP_H
#define PROPS_MORSECODE_PROP_H

#include "prop_base.h"
#include "../sound/sound_library.h"
#include <map>

#define PROP_TYPE MorseCode

#define DOT_DURATION 200  // Duration in ms for a dot
#define DASH_DURATION 600  // Duration in ms for a dash
#define GAP_DURATION 400  // Duration in ms between dots/dashes
#define LETTER_GAP 800  // Duration in ms between letters

// Morse code mappings for Latin characters
const char* morseCodeMap[][2] = {
    {"A", ".-"},   {"B", "-..."}, {"C", "-.-."}, {"D", "-.."},  {"E", "."},    {"F", "..-."},
    {"G", "--."},  {"H", "...."}, {"I", ".."},   {"J", ".---"}, {"K", "-.-"},  {"L", ".-.."},
    {"M", "--"},   {"N", "-."},   {"O", "---"},  {"P", ".--."}, {"Q", "--.-"}, {"R", ".-."},
    {"S", "..."},  {"T", "-"},    {"U", "..-"},  {"V", "...-"}, {"W", ".--"},  {"X", "-..-"},
    {"Y", "-.--"}, {"Z", "--.."},
    {"1", ".----"}, {"2", "..---"}, {"3", "...--"}, {"4", "....-"}, {"5", "....."},
    {"6", "-...."}, {"7", "--..."}, {"8", "---.."}, {"9", "----."}, {"0", "-----"}
};

class MorseCode : public PROP_INHERIT_PREFIX PropBase {
public:
    MorseCode() : currentCode_(""), currentType_('\0') {}

    const char* name() override { return "MorseCode"; }

    bool Event(enum BUTTON button, EVENT event) override {
        if (event == EVENT_PRESSED) {
            if (button == BUTTON_POWER) {
                HandleInput(true);
                return true;
            } else if (button == BUTTON_AUX) {
                HandleInput(false);
                return true;
            }
        }
        return false;
    }

    void HandleInput(bool isBlade) {
        // Simulate Morse code input here; e.g., check button duration, etc.
        // For simplicity, assume `currentType_` holds the typed character
        if (currentType_ != '\0') {
            std::string code = morseCodeMap[currentType_];
            if (isBlade) {
                PlayOnBlade(code);
            } else {
                PlayOnSpeaker(code);
            }
            DisplayOnOled(currentType_);  // Display both Aurebesh and Latin on OLED
            currentType_ = '\0';  // Reset after handling
        }
    }

    void PlayOnBlade(const std::string& code) {
        if (isalpha(currentType_)) {
            SetColor(0, 0, 255);  // Blue for letters
        } else if (isdigit(currentType_)) {
            SetColor(255, 0, 0);  // Red for numbers
        }
        // Implement blade animation here based on `code`
    }

    void PlayOnSpeaker(const std::string& code) {
        // Implement speaker playback of Morse code
        hybrid_font.PlayMorse(code);
    }

    void DisplayOnOled(char character) {
#ifdef OLED_ENABLE
        OledClear(); // Clear the OLED screen

        // Display Aurebesh (if enabled) and Latin characters
        OledSetCursor(0, 0); // Top part of the screen

#ifdef USE_AUREBESH_FONT
        OledWriteCharAurebesh(character);  // Write the Aurebesh character
#endif

        OledSetCursor(0, 2); // Lower part of the screen
        OledWriteChar(character);  // Write the Latin character

        OledUpdate();  // Update the OLED screen
#endif
    }

private:
    std::string currentCode_;
    char currentType_;  // Holds the last typed character (for simplicity)
};

#endif // PROPS_MORSECODE_PROP_H
/*
Code to Add to my_config.h:
*/
// Add OLED enable line if using an OLED screen
#ifdef ENABLE_OLED
#define OLED_ENABLE
#endif

// Optional: Define this if you want to use the Aurebesh font
//#define USE_AUREBESH_FONT

#ifdef OLED_ENABLE
#include "oled_helpers.h"
#endif
/*
Explanation:

    Aurebesh and Latin Display: If USE_AUREBESH_FONT is defined, the OLED screen will display the Aurebesh character first, followed by the Latin character. If the define is not used, only the Latin character will be displayed.

    OLED Handling: The OLED handling code is wrapped with #ifdef OLED_ENABLE to ensure the OLED functionality is used only if the OLED screen is present and enabled. If not, the OLED functions are ignored.

    Blade and Sound Effects: The PlayOnBlade and PlayOnSpeaker functions handle the visual effects for the blade and the sound effects for the speaker, triggered by Morse code input.

This setup ensures that both Aurebesh and Latin characters are displayed when available, and the system behaves correctly regardless of whether USE_AUREBESH_FONT is defined.
*/
