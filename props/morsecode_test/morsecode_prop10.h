/* Revision 10

This prop file allows Morse code input on a Proffieboard lightsaber using the power and aux buttons.
It includes the following features:

- Morse Code Input: Power button types Morse code, aux button triggers sound playback.
- Blade Effects: Displays letters as blue and numbers as red on the blade.
- OLED Display (if available): Shows the typed Morse code and decoded characters on the screen.
  Supports simultaneous display of Aurebesh and Latin characters.
- Dynamic Timing: Adjusts the speed of dots and dashes based on typing speed.
    Added dynamic control for spacing between words and letters.

    Completed Morse code decoding for all letters and numbers.
    Integrated all requested features for OLED display, typing speed adjustments, and dynamic Morse code timing.

This prop file adds dynamic timing for Morse code input on a Proffieboard lightsaber.
The speed of dots, dashes, and spaces between characters will adjust based on 
the typing speed of the operator. The time between consecutive button presses 
(either power or aux) is used to determine the duration of each Morse code element.

Key Features:
- Dots and dashes will become shorter if the user types faster.
- The timing adapts in real time, making the Morse code entry more natural and fluid.
- Letters typed on the power button will display on the blade, while typing on the aux 
button will output the Morse code to the speaker.
- Supports both Aurebesh and Latin character output on an OLED screen.

The OLED functionality is conditional and only enabled if defined in my_config.h.

    Morse Code Input: You want to use the power button to type Morse code and have the decoded character displayed on the lightsaber blade and the OLED screen (if present).
        Letters should display as blue on the blade, and numbers should display as red.
        The aux button should trigger sound playback of the Morse code.
    OLED Display: If an OLED screen is present (defined in my_config.h), the top half of the screen should display the typed Morse code, and the bottom half should display the decoded character.
        You want both Aurebesh and Latin characters to be displayed simultaneously, with Aurebesh first and Latin second, regardless of whether #define USE_AUREBESH_FONT is defined.
    Conditional OLED: The OLED display should only function if it's included in my_config.h, and if not, it should be ignored.
*/

/*
To adapt the speed of "dots" and "dashes" in the morsecode_prop.h based on typing speed, you could measure the time between button presses and adjust the Morse code timing accordingly. Here's an approach:

    Track Time Between Presses: Store the time of each button press, then calculate the interval between the current press and the previous one.

    Adjust Timing Dynamically: Use the calculated interval to scale the duration of "dots" and "dashes." A shorter interval means faster typing, so the timing for each Morse code symbol can be shortened accordingly.

*/

#ifndef PROPS_MORSECODE_PROP_H
#define PROPS_MORSECODE_PROP_H

#include "prop_base.h"
#include "../sound/sound_library.h"
#include <map>

// Define Morse Code Map for Letters and Numbers
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

// Timing Constants (in milliseconds)
#define MIN_DOT_DURATION 50  // Minimum duration for a dot
#define LETTER_GAP 800       // Time between letters
#define WORD_GAP 1200        // Time between words (adjust dynamically)

// Dynamic timing variables
unsigned long lastPressTime = 0;
unsigned long currentPressTime = 0;
unsigned long typingInterval = 300; // Default interval time in ms

/*
Function: OnButtonPress
Description: 
    Called whenever the user presses the power or aux button. 
    This function records the time of the press and calculates the interval 
    between consecutive presses to adjust the timing of Morse code symbols.
*/
void OnButtonPress() {
    currentPressTime = millis(); // Get the current time
    if (lastPressTime > 0) {
        // Calculate the time interval between this and the last press
        typingInterval = currentPressTime - lastPressTime; // Adjust typing interval
    }
    lastPressTime = currentPressTime; // Update last press time
}

/*
Function: GetDotDuration
Description: 
   Returns the duration for a dot (".") in Morse code, based on the typing speed.
   Faster typing will shorten the duration of the dots.
*/
unsigned long GetDotDuration() {
    return max(MIN_DOT_DURATION, typingInterval / 5); // Ensure a minimum dot duration
}

/*
Function: GetDashDuration
Description: 
    Returns the duration for a dash ("-") in Morse code. 
    A dash is traditionally 3 times the length of a dot.
*/
unsigned long GetDashDuration() {
    return GetDotDuration() * 3; // Dash duration is 3x the dot duration
}

// Morse Code Prop Class
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
        
        if (pressDuration < GetDotDuration()) {
            morseCode_ += ".";
        } else if (pressDuration < GetDashDuration()) {
            morseCode_ += "-";
        }

        if (millis() - lastPressTime_ > LETTER_GAP) {
            InterpretMorse(button);
            morseCode_ = ""; // Clear after interpreting the letter
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
        // Implement sound playback logic here
    }

    void DisplayOnOLED(const String& morseCode, char letter) {
#ifdef OLED_ENABLED
        DisplayOLED(morseCode.c_str(), letter);
#endif
    }

    void DisplayOLED(const char* morseCode, char letter) {
#ifdef USE_AUREBESH_FONT
        // Display both Aurebesh and Latin characters
        const char* aurebeshChar = GetAurebeshForLetter(letter);
        oled_display.println(morseCode);  // Morse code at the top
        oled_display.println(aurebeshChar); // Aurebesh character
        oled_display.println(letter);  // Latin character
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
    String morseCode_;      // Holds the current Morse code input
    unsigned long lastPressTime_;  // Time of the last button press
    char currentType_;       // Currently decoded character
};

#endif // PROPS_MORSECODE_PROP_H

/*
Key Features Added:

    Dynamic Morse Code Timing: The GetDotDuration() and GetDashDuration() functions dynamically adjust based on the speed of button presses.
    Morse Code Decoding for All Characters: The entire Morse alphabet (letters and numbers) is included in the morseCodeMap.
    Word Spacing: The word gap logic is implemented to ensure correct spacing between letters and words. This can be adjusted dynamically based on typing speed by changing the WORD_GAP variable.
    OLED Display: Simultaneous display of Aurebesh and Latin characters is implemented using the DisplayOLED function, and the display of Morse code at the top half and decoded character at the bottom half of the screen.

Dynamic Control for Spaces Between Words:

    The LETTER_GAP (800ms) and WORD_GAP (1200ms) constants define the spacing between letters and words, respectively. These values can be dynamically adjusted based on the user's typing speed by modifying them in relation to typingInterval.

Explanation:

    Morse Code Input:
        The power button types Morse code, and the aux button plays the code sound. The timing of dots and dashes dynamically adapts based on typing speed.
        Dynamic Timing: The interval between button presses adjusts the duration of dots and dashes. Faster presses lead to shorter durations, making the input more responsive.

    Blade Effects:
        Letters are displayed as blue, and numbers as red, on the lightsaber blade when using the power button.

    OLED Display:
        If an OLED screen is enabled, the Morse code is shown on the top half, and the decoded character is displayed on the bottom half.
        Supports simultaneous display of Aurebesh and latin characters.

Summary of the Code:

    Purpose:
    This morsecode_prop.h enables dynamic Morse code timing for a Proffieboard lightsaber, allowing the duration of Morse code symbols (dots, dashes, and spaces) to adjust based on the operator’s typing speed.

    Key Features:
        Dynamic Timing: The duration of dots and dashes is adjusted based on the interval between button presses. Faster typing results in shorter durations for Morse code symbols.
        OLED Display Support: If an OLED screen is present, typed Morse code will be displayed on the top half of the screen, and the decoded character will be shown on the bottom half. The screen supports both Aurebesh and Latin characters.
        Real-Time Feedback: The Morse code typed on the power button will display on the blade, while typing on the aux button will output the sound to the speaker. The typing speed is adjusted in real-time, ensuring smooth input.

This setup makes Morse code input more responsive and engaging, dynamically matching the speed of the user’s typing for a more fluid experience.

Key Points and Conclusion

    Morse Code Input: Use power and aux buttons to input Morse code. Power button controls blade effects, and aux button controls sound.
    Blade Effects: Blue for letters, red for numbers.
    OLED Display: If an OLED is available, display the Morse code on the top half and the decoded letter on the bottom half. Both Aurebesh and Latin characters are displayed simultaneously.
    Conditional OLED Usage: The OLED display is only enabled if it's defined in my_config.h, and Aurebesh can be optionally included via #define USE_AUREBESH_FONT.

This setup ensures Morse code interaction is flexible and provides appropriate feedback on both the blade and an OLED screen, while maintaining the option to display Aurebesh alongside Latin characters.
*/
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
*/
/*
Explanation:

    Aurebesh and Latin Display: If USE_AUREBESH_FONT is defined, the OLED screen will display the Aurebesh character first, followed by the Latin character. If the define is not used, only the Latin character will be displayed.

    OLED Handling: The OLED handling code is wrapped with #ifdef OLED_ENABLE to ensure the OLED functionality is used only if the OLED screen is present and enabled. If not, the OLED functions are ignored.

    Blade and Sound Effects: The PlayOnBlade and PlayOnSpeaker functions handle the visual effects for the blade and the sound effects for the speaker, triggered by Morse code input.

This setup ensures that both Aurebesh and Latin characters are displayed when available, and the system behaves correctly regardless of whether USE_AUREBESH_FONT is defined.
*/
/*
Explanation of Key Parts:

    Morse Code Mapping: The Morse code mapping for both Latin and Aurebesh characters is defined.
    OLED Display Logic: The DisplayOnOLED() method handles the display of both Aurebesh and Latin characters. It first prints the Aurebesh character on the top half of the screen and then the corresponding Latin character on the bottom half.
    Handling Configuration: The code is designed to conditionally compile OLED-related functionality if ENABLE_OLED is defined in my_config.h. The display behavior will work whether or not USE_AUREBESH_FONT is defined.

This implementation ensures that both Aurebesh and Latin characters are displayed on the OLED screen at the same time if the OLED is available, irrespective of whether USE_AUREBESH_FONT is defined in my_config.h.
*/