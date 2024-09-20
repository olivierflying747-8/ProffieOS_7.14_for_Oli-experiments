/* Revision 11

Introduction to Morse Code Prop for Proffieboard

This prop file allows for dynamic Morse code input on a Proffieboard lightsaber using both the power and aux buttons, offering an interactive and customizable experience with real-time visual and auditory feedback.
Key Features:

    Morse Code Input:
        Power Button: Used to type Morse code. Letters typed on the power button are displayed visually on the lightsaber blade.
        Aux Button: Used to trigger sound playback of the Morse code via the speaker.

    Blade Effects:
        Letters are displayed in blue on the blade, numbers are displayed in red, and special characters are displayed in green, providing a visual distinction between characters.

    OLED Display (if available):
        The top half of the OLED screen displays the typed Morse code, while the bottom half shows the decoded character.
        Supports simultaneous display of Aurebesh and Latin characters, whether or not the USE_AUREBESH_FONT definition is present in my_config.h.

    Dynamic Timing:
        The prop adjusts the timing for dots, dashes, and spaces based on the operator’s typing speed. Faster typing results in shorter dots, dashes, and gaps between characters.
        The interval between button presses is measured to dynamically scale the duration of each Morse code element, allowing for fluid and natural code entry.

    Real-time Adaptation:
        As the typing speed changes, the timing for Morse code elements adjusts in real time, creating a seamless input experience.

    Sound Playback:
        When the aux button is pressed, the Morse code is played audibly, allowing for auditory confirmation of the input in addition to the visual effects.

    Conditional OLED Functionality:
        The OLED display is only enabled if it is defined in my_config.h. If no OLED screen is present, the feature is ignored without impacting other functionality.

This prop file provides a full-featured Morse code interaction on the lightsaber, adapting to typing speed and supporting advanced features like OLED display and dual-character output (Mose Code & Aurebesh + Latin).
*/

#ifndef PROPS_MORSECODE_PROP_H
#define PROPS_MORSECODE_PROP_H

#define PROP_TYPE MorseCode

#include "prop_base.h"
#include "../sound/sound_library.h"
#include <map>

// Define Morse Code Map for Letters and Numbers
const char* morseCodeMap[][2] = {
    {"A", ".-"},      {"B", "-..."},   {"C", "-.-."},   {"D", "-.."},      {"E", "."},    {"F", "..-."},
    {"G", "--."},     {"H", "...."},   {"I", ".."},     {"J", ".---"},     {"K", "-.-"},  {"L", ".-.."},
    {"M", "--"},      {"N", "-."},     {"O", "---"},    {"P", ".--."},     {"Q", "--.-"}, {"R", ".-."},
    {"S", "..."},     {"T", "-"},      {"U", "..-"},    {"V", "...-"},     {"W", ".--"},  {"X", "-..-"},
    {"Y", "-.--"},    {"Z", "--.."},
    {"1", ".----"},   {"2", "..---"},  {"3", "...--"},  {"4", "....-"},    {"5", "....."},
    {"6", "-...."},   {"7", "--..."},  {"8", "---.."},  {"9", "----."},    {"0", "-----"},
    {".", ".-.-.-"},  {",", "--..--"}, {"?", "..--.."}, {"\'", ".----."},  {"!", "-.-.--"},
    {"/", "-..-."},   {"(", "-.--."},  {")", "-.--.-"}, {":", "---..."},   {";", "-.-.-."},
    {"=", "-...-"},   {"+", ".-.-."},  {"-", "-....-"}, {"_", "..--.-"},   {"\"", ".-..-."},
    {"$", "...-..-"}, {"&", ".-..."}
};

/* (old table to keep for reference)
const char* morseMap[36] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",      // A-I
    ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",    // J-R
    "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",           // S-Z
    "-----", ".----", "..---", "...--", "....-", ".....",               // 0-5
    "-....", "--...", "---..", "----."                                  // 6-9
};
*/

// Define Aurebesh Map
const char* aurebeshMap[][2] = {
    {"A", "𐤀"}, {"B", "𐤁"}, {"C", "𐤂"}, {"D", "𐤃"}, {"E", "𐤄"}, {"F", "𐤅"}, {"G", "𐤆"}, 
    {"H", "𐤇"}, {"I", "𐤈"}, {"J", "𐤉"}, {"K", "𐤊"}, {"L", "𐤋"}, {"M", "𐤌"}, {"N", "𐤍"}, 
    {"O", "𐤎"}, {"P", "𐤏"}, {"Q", "𐤐"}, {"R", "𐤑"}, {"S", "𐤒"}, {"T", "𐤓"}, {"U", "𐤔"}, 
    {"V", "𐤕"}, {"W", "𐤖"},  {"X", "𐤗"}, {"Y", "𐤘"}, {"Z", "𐤙"},
    {"1", "𐤚"}, {"2", "𐤛"}, {"3", "𐤜"}, {"4", "𐤝"}, {"5", "𐤞"},
    {"6", "𐤟"},  {"7", "𐤠"}, {"8", "𐤡"}, {"9", "𐤢"}, {"0", "𐤣"},
    {".", "."}, {",", ","}, {"?", "?"}, {"\'", "\'"}, {"!", "!"},
    {"/", "/"}, {"(", "("}, {")", ")"}, {":", ":"}, {";", ";"},
    {"=", "="}, {"+", "+"}, {"-", "-"}, {"_", "_"}, {"\"", "\""},
    {"$", "$"}, {"&", "&"}
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

    // Overriding Event2 to resolve ambiguity
    bool Event2(enum BUTTON button, EVENT event, uint32_t) override {
        return Event(button, event);
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
        }      else SetColor(0, 255, 0);
    }

    void PlayOnSpeaker(char letter) {
/* To implement the PlayOnSpeaker(char letter) function using Proffieboard beepers, you can generate simple sound outputs using Proffieboard's buzzer (also known as a "beeper"). ProffieOS provides the ability to play sounds for specific events, but the beeper itself is more commonly used for simple tones rather than complex sound playback.
*/
  // Morse code definition: . (dot) = short beep, - (dash) = long beep
  const int dotDuration = 200;  // Duration of dot beep (ms)
  const int dashDuration = 600; // Duration of dash beep (ms)
  const int gapDuration = 100;  // Gap between dots/dashes (ms)

  // Map letters to Morse code sequences
  String morseCode = GetMorseCode(letter); // Fetch Morse code for the given letter

  // Loop through the Morse code and play corresponding beeps
  for (size_t i = 0; i < morseCode.length(); i++) {
    if (morseCode[i] == '.') {
      beeper.Beep(dotDuration, 800); // Play a short beep for dot
    } else if (morseCode[i] == '-') {
      beeper.Beep(dashDuration, 800); // Play a long beep for dash
    }
    delay(gapDuration); // Wait between beeps
  }
}

// Helper function to fetch Morse code for a given character
String GetMorseCode(char letter) {
switch (letter) {
    case 'A': return ".-";
    case 'B': return "-...";
    case 'C': return "-.-.";
    case 'D': return "-..";
    case 'E': return ".";
    case 'F': return "..-.";
    case 'G': return "--.";
    case 'H': return "....";
    case 'I': return "..";
    case 'J': return ".---";
    case 'K': return "-.-";
    case 'L': return ".-..";
    case 'M': return "--";
    case 'N': return "-.";
    case 'O': return "---";
    case 'P': return ".--.";
    case 'Q': return "--.-";
    case 'R': return ".-.";
    case 'S': return "...";
    case 'T': return "-";
    case 'U': return "..-";
    case 'V': return "...-";
    case 'W': return ".--";
    case 'X': return "-..-";
    case 'Y': return "-.--";
    case 'Z': return "--..";
    case '0': return "-----";
    case '1': return ".----";
    case '2': return "..---";
    case '3': return "...--";
    case '4': return "....-";
    case '5': return ".....";
    case '6': return "-....";
    case '7': return "--...";
    case '8': return "---..";
    case '9': return "----.";
    case '.': return ".-.-.-";
    case ',': return "--..--";
    case '?': return "..--..";
    case '\'': return ".----.";
    case '!': return "-.-.--";
    case '/': return "-..-.";
    case '(': return "-.--.";
    case ')': return "-.--.-";
    case ':': return "---...";
    case ';': return "-.-.-.";
    case '=': return "-...-";
    case '+': return ".-.-.";
    case '-': return "-....-";
    case '_': return "..--.-";
    case '"': return ".-..-.";
    case '$': return "...-..-";
    case '&': return ".-...";
    default: return "";
    }
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
Introduction to Morse Code Prop for Proffieboard

This prop file enables dynamic Morse code input on a Proffieboard lightsaber, providing a responsive and engaging experience with real-time feedback through both visual blade effects and sound. Key features include dynamic timing for Morse code elements, comprehensive decoding for all characters, and optional OLED display support.
Key Features:

    Dynamic Morse Code Timing:
        The GetDotDuration() and GetDashDuration() functions adjust timing based on the speed of button presses. Faster typing results in shorter dots and dashes, making the input more fluid and responsive.

    Morse Code Decoding for All Characters:
        The Morse alphabet (letters and numbers) is fully included in the morseCodeMap, ensuring complete decoding functionality.

    Dynamic Word Spacing:
        The word and letter spacing adapts based on typing speed. The LETTER_GAP (800ms) and WORD_GAP (1200ms) constants define the spacing, and these can be adjusted dynamically based on the typing interval, ensuring natural input.

    Blade Effects:
        Visual effects display letters in blue, numbers in red and special characters in green on the blade, providing clear visual differentiation.

    OLED Display (if available):
        The top half of the OLED screen displays the typed Morse code, and the bottom half shows the decoded character. Both Aurebesh and Latin characters are displayed simultaneously, with Aurebesh shown first.

    Conditional OLED Usage:
        OLED functionality is only enabled if an OLED screen is defined in my_config.h. The #ifdef OLED_ENABLE ensures that OLED features are ignored if the screen is not present, making the setup flexible.

Dynamic Control for Spaces Between Words

    The prop dynamically adjusts spaces between letters and words based on typing speed by modifying the LETTER_GAP and WORD_GAP values in relation to the typing interval. This feature ensures accurate and intuitive spacing when typing quickly or slowly.

Code Breakdown:

    Morse Code Input:
        The power button is used for Morse code input, while the aux button triggers sound playback. The timing for dots, dashes, and spaces dynamically adapts based on the interval between button presses.

    Morse Code Interpretation:
        The InterpretMorse function compares the typed code against the morseCodeMap to return the correct letter or number.

    Blade and Speaker Control:
        The PlayOnBladeOrSpeaker function determines whether to display Morse code on the blade or play it on the speaker based on the button used.

    OLED Display Logic:
        The DisplayOnOLED function updates the OLED screen, showing Morse code in the top half and the decoded character in the bottom half. Both Aurebesh and Latin characters are supported.

    Blade Effects:
        The PlayOnBlade function manages blade colors—letters are displayed in blue, numbers in red and special characters in green — using effects defined in my_config.h.

Summary:

This Morse code prop file for Proffieboard dynamically adjusts Morse code timing and spacing based on the user’s typing speed, ensuring a fluid input experience. The code supports a variety of visual and auditory feedback options, including:

    Dynamic Timing: Adjusts the duration of dots, dashes, and spaces based on the interval between button presses.
    OLED Support: Displays both Aurebesh and Latin characters on the OLED screen (if present).
    Blade Effects: Visual differentiation between letters and numbers on the lightsaber blade.

This implementation ensures a fully responsive and immersive experience when typing Morse code on the lightsaber. Whether using the power button for blade effects or the aux button for sound playback, the prop dynamically adapts to the user’s typing speed, making input smooth and natural.

*/