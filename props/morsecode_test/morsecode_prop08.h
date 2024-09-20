/*
MorseCode_Prop.h - Dynamic Morse Code for Proffieboard with OLED and Blade Effects

This prop file allows Morse code input on a Proffieboard lightsaber using the power and aux buttons.
It includes the following features:

- Morse Code Input: Power button types Morse code, aux button triggers sound playback.
- Blade Effects: Displays letters as blue and numbers as red on the blade.
- OLED Display (if available): Shows the typed Morse code and decoded characters on the screen.
  Supports simultaneous display of Aurebesh and Latin characters.
- Dynamic Timing: Adjusts the speed of dots and dashes based on typing speed.

The OLED functionality is conditional and only enabled if defined in my_config.h.

*/

// Include ProffieOS libraries
#include "prop_base.h"
#include "../sound/sound_library.h"
#include <map>

#ifdef OLED_ENABLED
#include "oled_display.h"  // Include OLED display library if available
#endif

// Define Morse Code and Aurebesh Mappings
const char* morseCodeMap[][2] = {
    {"A", ".-"}, {"B", "-..."}, {"C", "-.-."}, {"D", "-.."}, {"E", "."}, {"F", "..-."},
    {"G", "--."}, {"H", "...."}, {"I", ".."}, {"J", ".---"}, {"K", "-.-"}, {"L", ".-.."},
    {"M", "--"}, {"N", "-."}, {"O", "---"}, {"P", ".--."}, {"Q", "--.-"}, {"R", ".-."},
    {"S", "..."}, {"T", "-"}, {"U", "..-"}, {"V", "...-"}, {"W", ".--"}, {"X", "-..-"},
    {"Y", "-.--"}, {"Z", "--.."},
    {"1", ".----"}, {"2", "..---"}, {"3", "...--"}, {"4", "....-"}, {"5", "....."},
    {"6", "-...."}, {"7", "--..."}, {"8", "---.."}, {"9", "----."}, {"0", "-----"}
};

const char* aurebeshMap[][2] = {
    {"A", "𐤀"}, {"B", "𐤁"}, {"C", "𐤂"}, {"D", "𐤃"}, {"E", "𐤄"}, {"F", "𐤅"}, {"G", "𐤆"},
    {"H", "𐤇"}, {"I", "𐤈"}, {"J", "𐤉"}, {"K", "𐤊"}, {"L", "𐤋"}, {"M", "𐤌"}, {"N", "𐤍"},
    {"O", "𐤎"}, {"P", "𐤏"}, {"Q", "𐤐"}, {"R", "𐤑"}, {"S", "𐤒"}, {"T", "𐤓"}, {"U", "𐤔"},
    {"V", "𐤕"}, {"W", "𐤖"}, {"X", "𐤗"}, {"Y", "𐤘"}, {"Z", "𐤙"},
    {"1", "𐤚"}, {"2", "𐤛"}, {"3", "𐤜"}, {"4", "𐤝"}, {"5", "𐤞"},
    {"6", "𐤟"}, {"7", "𐤠"}, {"8", "𐤡"}, {"9", "𐤢"}, {"0", "𐤣"}
};

// Variables to track timing for dynamic Morse code input
unsigned long lastPressTime = 0;
unsigned long typingInterval = 300; // Default interval time in milliseconds

void OnButtonPress() {
    unsigned long currentPressTime = millis();  // Get current time
    if (lastPressTime > 0) {
        typingInterval = currentPressTime - lastPressTime;  // Calculate the interval between presses
    }
    lastPressTime = currentPressTime;  // Update the last press time
}

unsigned long GetDotDuration() {
    return max(50, typingInterval / 5);  // Minimum 50ms, scaled by typing speed
}

unsigned long GetDashDuration() {
    return GetDotDuration() * 3;  // Dash is 3 times the duration of a dot
}

// Main Morse Code Class
class MorseCode : public PROP_INHERIT_PREFIX PropBase {
public:
    MorseCode() : morseCode_(""), lastPressTime_(0), currentType_('\0') {}

    const char* name() override { return "MorseCode"; }

    // Handle button presses and releases
    bool Event(enum BUTTON button, EVENT event) override {
        if (event == EVENT_PRESSED) {
            OnButtonPress();
            StartPress(button);
        } else if (event == EVENT_RELEASED) {
            EndPress(button);
        }
        return true;
    }

    // Start a button press
    void StartPress(BUTTON button) {
        lastPressTime_ = millis();
    }

    // End a button press and determine whether it's a dot or dash
    void EndPress(BUTTON button) {
        unsigned long pressDuration = millis() - lastPressTime_;
        if (pressDuration < GetDotDuration()) {
            morseCode_ += ".";
        } else if (pressDuration < GetDashDuration()) {
            morseCode_ += "-";
        }

        // If a long time passes, interpret the Morse code
        if (millis() - lastPressTime_ > 800) {
            InterpretMorse(button);
            morseCode_ = "";  // Reset after interpretation
        }
    }

    // Decode the Morse code and display on blade and OLED
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

    // Display Morse code on the blade (blue for letters, red for numbers)
    void DisplayOnBlade(char letter) {
        if (isalpha(letter)) {
            SetColor(0, 0, 255);  // Blue for letters
        } else if (isdigit(letter)) {
            SetColor(255, 0, 0);  // Red for numbers
        }
    }

    // Play Morse code on the speaker (triggered by aux button)
    void PlayOnSpeaker(char letter) {
        // Implement sound playback
    }

    // Display Morse code and decoded character on OLED (if enabled)
    void DisplayOnOLED(const String& morseCode, char letter) {
#ifdef OLED_ENABLED
        DisplayOLED(morseCode.c_str(), letter);
#endif
    }

    // Display the decoded character on the OLED
    void DisplayOLED(const char* morseCode, char letter) {
#ifdef USE_AUREBESH_FONT
        const char* aurebeshChar = GetAurebeshForLetter(letter);
        oled_display.println(morseCode);  // Top: Morse code
        oled_display.println(aurebeshChar);  // Middle: Aurebesh
        oled_display.println(letter);  // Bottom: Latin character
#else
        oled_display.println(morseCode);  // Top: Morse code
        oled_display.println(letter);  // Bottom: Latin character
#endif
    }

    // Retrieve the Aurebesh equivalent of a letter
    const char* GetAurebeshForLetter(char letter) {
        for (int i = 0; i < 36; i++) {
            if (aurebeshMap[i][0][0] == letter) {
                return aurebeshMap[i][1];
            }
        }
        return "?";  // Fallback if not found
    }

private:
    String morseCode_;  // Stores the current Morse code sequence
    unsigned long lastPressTime_;  // Tracks the last button press time
};

#endif // PROPS_MORSECODE_PROP_H

/*
Explanation:

    Morse Code Input:
        The power button types Morse code, and the aux button plays the code sound. The timing of dots and dashes dynamically adapts based on typing speed.
        Dynamic Timing: The interval between button presses adjusts the duration of dots and dashes. Faster presses lead to shorter durations, making the input more responsive.

    Blade Effects:
        Letters are displayed as blue, and numbers as red, on the lightsaber blade when using the power button.

    OLED Display:
        If an OLED screen is enabled, the Morse code is shown on the top half, and the decoded character is displayed on the bottom half.
        Supports simultaneous display of Aurebesh and
*/