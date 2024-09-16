/*
To enhance your morsecode_prop.h and add the desired features such as blade effects (configured through my_config.h) and OLED screen integration, here's what we can do:
1. Blade Effects in my_config.h

You can define specific blade effects for the Morse code in your my_config.h file using the EffectSequence and BladeStyles. Here's a breakdown of how to approach it:

    Blue Blade for Letters: Define a blade effect for letters in Morse code.
    Red Blade for Numbers: Define a blade effect for numbers in Morse code.

Here's how you might define these effects in your my_config.h:*/

// Blade effects for Morse code
StylePtr<InOutHelper<White, Black>> MorseLetterStyle = StylePtr<Red>();  // For numbers
StylePtr<InOutHelper<Blue, Black>> MorseNumberStyle = StylePtr<Blue>();  // For letters

/*
Then, in the MorseCode prop, trigger these effects depending on the character type (letter or number).
2. Blade Effects Configuration

In your MorseCode::PlayOnBlade function, call the appropriate effect from the my_config.h file. For instance, if the input is a letter, you trigger the MorseLetterStyle, and if it's a number, you trigger MorseNumberStyle.
3. OLED Screen Integration

Yes, it's possible to integrate the OLED screen to display the typed Morse code and the decoded character. You would need to handle OLED rendering in your prop.

The top half of the screen will show the Morse code input (dots and dashes), while the bottom will display the decoded character. You can use the following methods:

    ProffieOS's oled.h: Use the OLED API functions like DisplayText() to manage OLED content.

Example integration in your MorseCode prop:
*/
#include "oled.h"  // Include OLED functions

void UpdateOLED(const String& morseCode, char decodedChar) {
    OLED_Clear();
    OLED_DisplayText(0, 0, morseCode.c_str());    // Morse code in top half
    OLED_DisplayText(0, 32, String(decodedChar)); // Decoded char in bottom half
    OLED_Show();  // Update the OLED
}
/*
4. Integrating OLED in the Prop

In your EndPress function, after decoding the Morse code, call the UpdateOLED function to update the display:
*/
void EndPress(BUTTON button) {
    unsigned long pressDuration = millis() - lastPressTime_;
    isPressing_ = false;

    if (pressDuration < DOT_DURATION) {
        morseCode_ += ".";
    } else if (pressDuration < DASH_DURATION) {
        morseCode_ += "-";
    }

    if (millis() - lastPressTime_ > LETTER_GAP) {
        char decodedChar = InterpretMorse(button);
        UpdateOLED(morseCode_, decodedChar);  // Update OLED with Morse code and decoded char
        morseCode_ = "";
    }
}
/*
5. Improving Blade Effects

To synchronize blade effects with Morse code input:

    Add a pulsing or flashing effect to the blade based on Morse code patterns (dots or dashes).
    You can use a quick flash for dots and a longer one for dashes, controlled via timers inside PlayOnBlade.
    */
void PlayOnBlade(const std::string& code) {
    for (char c : code) {
        if (c == '.') {
            // Flash for dot
            SetColor(0, 0, 255);  // Quick blue flash for letters
            delay(DOT_DURATION);
        } else if (c == '-') {
            // Flash for dash
            SetColor(0, 0, 255);  // Longer blue flash for letters
            delay(DASH_DURATION);
        }
    }
}
/*
6. OLED Optimization

If you want the OLED to display characters smoothly, limit frequent updates, or use millis() to update periodically, preventing screen flickering.

These changes will give you:

    Blade effects for dots and dashes, customizable in my_config.h.
    Blue effects for letters and red effects for numbers.
    Real-time OLED display of the Morse code typed and decoded characters.

Let me know if you need further refinement or help with integrating these ideas!
*/
/*
Here’s a full code implementation of your Morse code prop with the requested features: blade effects based on Morse code (blue for letters, red for numbers) defined in my_config.h, and an OLED screen that displays both the Morse code and the decoded character.
*/
#ifndef PROPS_MORSECODE_PROP_H
#define PROPS_MORSECODE_PROP_H

#include "prop_base.h"
#include "../sound/sound_library.h"
#include "oled.h" // For OLED screen handling

#define DOT_DURATION 200  // Duration in ms for a dot
#define DASH_DURATION 600 // Duration in ms for a dash
#define LETTER_GAP 800    // Duration in ms between letters

// Morse code mappings for letters and numbers
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
    MorseCode() : morseCode_(""), currentType_('\0'), lastPressTime_(0), isPressing_(false) {}

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
            char decodedChar = InterpretMorse(button);
            UpdateOLED(morseCode_, decodedChar);  // Update OLED with Morse code and decoded char
            PlayOnBladeOrSpeaker(button, decodedChar);
            morseCode_ = "";  // Reset after decoding
        }
    }

    // Interpret the Morse code and return the decoded character
    char InterpretMorse(BUTTON button) {
        for (int i = 0; i < 36; i++) {
            if (strcmp(morseCode_.c_str(), morseCodeMap[i][1]) == 0) {
                return (i < 26) ? 'A' + i : '0' + (i - 26);
            }
        }
        return '\0';  // Return null character if no match
    }

    // Play the appropriate effect based on the button pressed (blade or speaker)
    void PlayOnBladeOrSpeaker(BUTTON button, char decodedChar) {
        if (button == BUTTON_POWER) {
            PlayOnBlade(decodedChar);
        } else if (button == BUTTON_AUX) {
            PlayOnSpeaker(decodedChar);
        }
    }

    // Update the OLED screen with Morse code and the decoded character
    void UpdateOLED(const String& morseCode, char decodedChar) {
        OLED_Clear();
        OLED_DisplayText(0, 0, morseCode.c_str());    // Morse code in top half
        OLED_DisplayText(0, 32, String(decodedChar)); // Decoded character in bottom half
        OLED_Show();  // Show the updated content
    }

    // Play blade effect based on the decoded character
    void PlayOnBlade(char decodedChar) {
        if (isalpha(decodedChar)) {
            SetBladeEffect(MORSE_LETTER_STYLE);  // Defined in `my_config.h` as blue
        } else if (isdigit(decodedChar)) {
            SetBladeEffect(MORSE_NUMBER_STYLE);  // Defined in `my_config.h` as red
        }

        // Pulse the blade for each dot or dash in the Morse code
        for (char c : morseCode_) {
            if (c == '.') {
                // Quick pulse for a dot
                BladePulse(200);  // Duration for a dot
            } else if (c == '-') {
                // Longer pulse for a dash
                BladePulse(600);  // Duration for a dash
            }
        }
    }

    // Play sound on the speaker based on the decoded character
    void PlayOnSpeaker(char decodedChar) {
        hybrid_font.PlayMorse(String(decodedChar));  // Use a hybrid font to play sound
    }

private:
    String morseCode_;      // Stores the currently typed Morse code
    char currentType_;      // The decoded character (letter/number)
    unsigned long lastPressTime_;
    bool isPressing_;
};

#endif // PROPS_MORSECODE_PROP_H

/*
my_config.h Blade Effects
*/
// Define styles for Morse code blade effects in `my_config.h`

#define MORSE_LETTER_STYLE StylePtr<InOutHelper<Blue, Black>>()  // Blue blade effect for letters
#define MORSE_NUMBER_STYLE StylePtr<InOutHelper<Red, Black>>()   // Red blade effect for numbers

// Blade pulse effect function (for quick flashes)
void BladePulse(int duration) {
    SetColor(255, 255, 255);  // Flash white light during Morse code pulse
    delay(duration);  // Keep it on for the dot/dash duration
    SetColor(0, 0, 0);  // Turn off blade (or return to normal)
}
/*
Breakdown of the Code:

    Morse Code Input:
        StartPress and EndPress: These functions handle button press duration to differentiate between dots (.) and dashes (-).
        The morseCode_ variable stores the Morse code sequence being input.

    Morse Code Interpretation:
        The InterpretMorse function compares the typed Morse code against the predefined morseCodeMap and returns the corresponding decoded letter or number.

    Blade and Speaker Control:
        The PlayOnBladeOrSpeaker function determines whether to play the Morse code on the blade or speaker based on which button was used.
        The PlayOnBlade function controls the blade colors using SetBladeEffect, which references the styles defined in my_config.h.
        The PlayOnSpeaker function uses a hybrid font to play sound on the speaker.

    OLED Screen Display:
        The UpdateOLED function updates the OLED screen to show the Morse code being typed in the top half and the decoded character in the bottom half.

This code will:

    Display the Morse code input and its decoded character on an OLED screen.
    Control the blade effects (blue for letters, red for numbers) based on Morse code input.
    Handle both blade effects and speaker playback depending on which button (power or aux) is used to type the Morse code.

Let me know if you need further adjustments!
*/
/*
the oled screen can only be used if it was included in my_config.h, if it was not, then it must be ignored or disabled
*/
/*
To handle the case where the OLED screen might not be included in my_config.h, you can add conditional compilation checks based on whether the OLED library is included. This way, if the OLED screen isn't defined, the related code will be ignored or disabled.

Here’s how you can adjust the code in morsecode_prop.h to achieve this:
morsecode_prop.h
*/
#ifndef PROPS_MORSECODE_PROP_H
#define PROPS_MORSECODE_PROP_H

#include "prop_base.h"
#include "../sound/sound_library.h"

#ifdef ENABLE_OLED // Only include the OLED code if OLED is enabled
#include "oled.h"  // For OLED screen handling
#endif

#define DOT_DURATION 200  // Duration in ms for a dot
#define DASH_DURATION 600 // Duration in ms for a dash
#define LETTER_GAP 800    // Duration in ms between letters

// Morse code mappings for letters and numbers
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
    MorseCode() : morseCode_(""), currentType_('\0'), lastPressTime_(0), isPressing_(false) {}

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
            char decodedChar = InterpretMorse(button);
            #ifdef ENABLE_OLED
            UpdateOLED(morseCode_, decodedChar);  // Update OLED if enabled
            #endif
            PlayOnBladeOrSpeaker(button, decodedChar);
            morseCode_ = "";  // Reset after decoding
        }
    }

    // Interpret the Morse code and return the decoded character
    char InterpretMorse(BUTTON button) {
        for (int i = 0; i < 36; i++) {
            if (strcmp(morseCode_.c_str(), morseCodeMap[i][1]) == 0) {
                return (i < 26) ? 'A' + i : '0' + (i - 26);
            }
        }
        return '\0';  // Return null character if no match
    }

    // Play the appropriate effect based on the button pressed (blade or speaker)
    void PlayOnBladeOrSpeaker(BUTTON button, char decodedChar) {
        if (button == BUTTON_POWER) {
            PlayOnBlade(decodedChar);
        } else if (button == BUTTON_AUX) {
            PlayOnSpeaker(decodedChar);
        }
    }

    #ifdef ENABLE_OLED
    // Update the OLED screen with Morse code and the decoded character
    void UpdateOLED(const String& morseCode, char decodedChar) {
        OLED_Clear();
        OLED_DisplayText(0, 0, morseCode.c_str());    // Morse code in top half
        OLED_DisplayText(0, 32, String(decodedChar)); // Decoded character in bottom half
        OLED_Show();  // Show the updated content
    }
    #endif

    // Play blade effect based on the decoded character
    void PlayOnBlade(char decodedChar) {
        if (isalpha(decodedChar)) {
            SetBladeEffect(MORSE_LETTER_STYLE);  // Defined in `my_config.h` as blue
        } else if (isdigit(decodedChar)) {
            SetBladeEffect(MORSE_NUMBER_STYLE);  // Defined in `my_config.h` as red
        }

        // Pulse the blade for each dot or dash in the Morse code
        for (char c : morseCode_) {
            if (c == '.') {
                BladePulse(200);  // Quick pulse for a dot
            } else if (c == '-') {
                BladePulse(600);  // Longer pulse for a dash
            }
        }
    }

    // Play sound on the speaker based on the decoded character
    void PlayOnSpeaker(char decodedChar) {
        hybrid_font.PlayMorse(String(decodedChar));  // Use a hybrid font to play sound
    }

private:
    String morseCode_;      // Stores the currently typed Morse code
    char currentType_;      // The decoded character (letter/number)
    unsigned long lastPressTime_;
    bool isPressing_;
};

#endif // PROPS_MORSECODE_PROP_H
/*
Updates:

    Conditional OLED Handling: The OLED-related code is wrapped inside #ifdef ENABLE_OLED. This condition checks if OLED functionality has been enabled in my_config.h. If ENABLE_OLED is defined, the OLED-related code is included; otherwise, it is ignored or disabled.

    my_config.h: Add the ENABLE_OLED definition to enable OLED support.

my_config.h
*/
// Define this macro to enable OLED support
#define ENABLE_OLED

// Define styles for Morse code blade effects in `my_config.h`
#define MORSE_LETTER_STYLE StylePtr<InOutHelper<Blue, Black>>()  // Blue blade effect for letters
#define MORSE_NUMBER_STYLE StylePtr<InOutHelper<Red, Black>>()   // Red blade effect for numbers

// Blade pulse effect function (for quick flashes)
void BladePulse(int duration) {
    SetColor(255, 255, 255);  // Flash white light during Morse code pulse
    delay(duration);  // Keep it on for the dot/dash duration
    SetColor(0, 0, 0);  // Turn off blade (or return to normal)
}
/*
Notes:

    OLED Support: You can now control whether the OLED screen is used by defining or omitting #define ENABLE_OLED in my_config.h. If the OLED screen is not included, the code that updates the screen will be ignored.
    Blade Effects: The Morse code characters will still trigger the correct blade effects (blue for letters, red for numbers) regardless of whether the OLED is enabled.

This setup ensures that the OLED screen is optional, and its absence won’t interfere with the rest of the functionality.
*/
/*
what would happen on the OLED screen, if #define USE_AUREBESH_FONT was used in my_config.h ?
*/
/*
If #define USE_AUREBESH_FONT is used in my_config.h, it means that the OLED display will be using the Aurebesh font instead of the default font (likely Latin-based characters). Here’s how that would affect the OLED screen behavior in your morsecode_prop.h file:

    Morse Code Display (Top Half): The typed Morse code (dots and dashes) will not be affected, as those symbols (dots . and dashes -) exist in most fonts, including Aurebesh. So, the OLED screen will still correctly display the Morse code sequence on the top half of the screen.

    Decoded Character (Bottom Half): If you are displaying letters (A-Z) or numbers (0-9) as decoded characters, the effect depends on how Aurebesh is implemented:
        If the Aurebesh font supports the full alphabet (A-Z) and numbers, the OLED will show the Aurebesh representation of these characters.
        If the Aurebesh font replaces standard Latin letters with Aurebesh symbols, the characters displayed on the OLED will be the Aurebesh equivalents. This means instead of seeing "A" or "1", you’ll see the corresponding Aurebesh symbol for those characters.

Example Behavior:

    Without Aurebesh:
        Top half: ..- (Morse code for "U")
        Bottom half: U (decoded letter)

    With Aurebesh Font:
        Top half: ..- (Morse code for "U" stays the same)
        Bottom half: Aurebesh symbol for "U" (instead of the Latin "U", you'll see the Aurebesh equivalent).

How to Handle This in Code:

If you want to toggle between Aurebesh and standard characters dynamically (or choose what to display based on the font), you can conditionally modify the character handling depending on whether USE_AUREBESH_FONT is defined. For example, you might want to display the decoded Morse character using the Aurebesh font if it's enabled or use the Latin alphabet if it's not.
Conditional Handling Example:

In your morsecode_prop.h file, you can add conditional logic for handling Aurebesh as follows:
*/
#ifdef USE_AUREBESH_FONT
    // Show decoded character in Aurebesh (depends on how Aurebesh is implemented)
    void ShowDecodedCharacter(char decodedChar) {
        OLED_DisplayText(0, 32, TranslateToAurebesh(decodedChar));  // You would need a mapping function for Aurebesh
    }
#else
    // Default Latin alphabet handling
    void ShowDecodedCharacter(char decodedChar) {
        OLED_DisplayText(0, 32, String(decodedChar));  // Normal character display
    }
#endif
/*
In this case, you would need a TranslateToAurebesh() function that maps the decoded character (A-Z, 0-9) to the corresponding Aurebesh glyph.
Conclusion:

    If #define USE_AUREBESH_FONT is used, the OLED screen will display Aurebesh characters instead of Latin characters for the decoded Morse code.
    The Morse code itself (dots and dashes) should remain unaffected.
    You can add conditional logic in your code to handle the display based on whether Aurebesh is enabled or not.
*/
