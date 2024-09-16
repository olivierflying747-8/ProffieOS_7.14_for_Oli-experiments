/*
Creating a morsecode_prop.h for your lightsaber, where the power and/or aux buttons are used to type Morse code, involves capturing button inputs, interpreting them as Morse code, and then triggering effects either on the blade or through the speaker based on which button is used.

Here's a basic outline of how this could be implemented:
1. Define the Morse Code Mapping

First, you need to define the Morse code for each character (letters, numbers, etc.).

2. Capture Button Presses

You need to capture button presses and translate them into Morse code input. A press would register as a dot, a longer hold as a dash.
3. Implement Timing Logic

Timing is crucial for Morse code interpretation. You would need to measure how long the button is held down and released to distinguish between dots and dashes.
4. Playback the Morse Code

Once a valid Morse code sequence is input, it can be played back using the blade effects (if the power button is used) or via sound (if the aux button is used).
Example Implementation

Here’s a simplified example:
*/
#ifndef PROPS_MORSECODE_PROP_H
#define PROPS_MORSECODE_PROP_H

#include "prop_base.h"
#include "../sound/sound_library.h"

#define DOT_DURATION 200  // Duration in ms for a dot
#define DASH_DURATION 600  // Duration in ms for a dash
#define GAP_DURATION 400  // Duration in ms between dots/dashes
#define LETTER_GAP 800  // Duration in ms between letters

class MorseCode : public PROP_INHERIT_PREFIX PropBase {
public:
    MorseCode() : morseCode_(""), lastPressTime_(0), isPressing_(false) {}

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
        isPressing_ = true;
    }

    void EndPress(BUTTON button) {
        unsigned long pressDuration = millis() - lastPressTime_;
        isPressing_ = false;

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
            if (strcmp(morseCode_.c_str(), morseMap[i]) == 0) {
                char letter = (i < 26) ? 'A' + i : '0' + (i - 26);
                if (button == BUTTON_POWER) {
                    PlayOnBlade(letter);
                } else if (button == BUTTON_AUX) {
                    PlayOnSpeaker(letter);
                }
                break;
            }
        }
    }

    void PlayOnBlade(char letter) {
        // Implement blade effect for the corresponding letter
    }

    void PlayOnSpeaker(char letter) {
        // Implement sound effect for the corresponding letter
    }

private:
    String morseCode_;
    unsigned long lastPressTime_;
    bool isPressing_;
};

#endif // PROPS_MORSECODE_PROP_H

/*
To create a morsecode_prop.h for your lightsaber that plays Morse code on the blade and speaker with the specified colors for letters and numbers, here's how you can approach it:
Step-by-Step Implementation

    Define Morse Code Map: Create a map to associate each letter and number with its corresponding Morse code pattern.

    Handle Button Events: Detect when the power or aux button is pressed to input Morse code. Store the input sequence.

    Interpret Morse Code: Translate the input sequence into letters or numbers.

    Control Blade Colors: Use different colors for letters (blue) and numbers (red) when the Morse code is typed on the power button.

    Play Sound: If the Morse code is typed on the aux button, play the corresponding sound on the speaker.

Example Code Structure

Here's a simplified version of what the code might look like:
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

// Morse code mappings
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

private:
    std::string currentCode_;
    char currentType_;  // Holds the last typed character (for simplicity)
};

#endif // PROPS_MORSECODE_PROP_H

/*
Explanation:

    Morse Code Map: The morseCodeMap stores each letter and number with its Morse code pattern.
    Event Handling: The Event function captures button presses and directs input to either the blade or speaker based on the button pressed.
    Color Handling: PlayOnBlade sets the blade color based on whether the input is a letter (blue) or a number (red).
    Sound Handling: PlayOnSpeaker triggers the Morse code sound on the speaker if the aux button is used.

This structure allows the lightsaber to respond to Morse code input, with distinct behaviors for the blade and speaker, and color-coded output for letters and numbers. You can customize and expand this basic structure to fit your specific needs.
*/
