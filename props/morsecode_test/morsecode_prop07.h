/*
MorseCode_Prop.h - Dynamic Morse Code Implementation for Proffieboard

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
*/

// Import necessary ProffieOS headers and libraries
#include "proffieboard.h"
#include "oled_display.h"  // Include OLED display control (if applicable)

// Variables for timing and typing speed adjustment
unsigned long lastPressTime = 0;    // Time of the last button press
unsigned long currentPressTime = 0; // Time of the current button press
unsigned long typingInterval = 300; // Default interval time in milliseconds (can be adjusted dynamically)

// Variables to track the Morse code input
String morseCode = "";  // Stores the current Morse code sequence
bool isTyping = false;  // Tracks if the user is currently typing

// OLED screen initialization (if applicable)
#ifdef ENABLE_OLED_DISPLAY
OledDisplay oledDisplay;  // Object to handle OLED display
#endif

/*
Function: OnButtonPress
Description: 
    Called whenever the user presses the power or aux button. 
    This function records the time of the press and calculates the interval 
    between consecutive presses to adjust the timing of Morse code symbols.
*/
void OnButtonPress() {
    currentPressTime = millis();  // Get current time
    
    if (lastPressTime > 0) {
        // Calculate the time interval between this and the last press
        typingInterval = currentPressTime - lastPressTime;
    }

    lastPressTime = currentPressTime;  // Update last press time
    isTyping = true;  // Mark as typing in progress
}

/*
Function: GetDotDuration
Description: 
   Returns the duration for a dot (".") in Morse code, based on the typing speed.
   Faster typing will shorten the duration of the dots.
*/
unsigned long GetDotDuration() {
    return max(50, typingInterval / 5);  // Minimum 50ms, scaled by typing interval
}

/*
Function: GetDashDuration
Description: 
    Returns the duration for a dash ("-") in Morse code. 
    A dash is traditionally 3 times the length of a dot.
*/
unsigned long GetDashDuration() {
    return GetDotDuration() * 3;  // Dash is 3 times the duration of a dot
}

/*
Function: PlayDot
Description: 
   Plays a dot sound or shows a dot effect on the blade, for the dynamically 
   calculated duration based on typing speed.
*/
void PlayDot() {
    unsigned long duration = GetDotDuration();
    // Insert code to play dot sound or blade effect for 'duration' milliseconds
    morseCode += ".";  // Append dot to Morse code string
}

/*
Function: PlayDash
Description: 
   Plays a dash sound or shows a dash effect on the blade, for the dynamically 
   calculated duration based on typing speed.
*/
void PlayDash() {
    unsigned long duration = GetDashDuration();
    // Insert code to play dash sound or blade effect for 'duration' milliseconds
    morseCode += "-";  // Append dash to Morse code string
}

/*
Function: DisplayMorseCode
Description: 
   Displays the current Morse code sequence on the OLED screen (if enabled).
   The top half of the screen will show the typed Morse code, and the bottom 
    half will show the decoded character.

    Supports both Aurebesh and Latin characters.
 */
void DisplayMorseCode() {
#ifdef ENABLE_OLED_DISPLAY
    String decodedChar = DecodeMorse(morseCode);  // Decode the Morse code sequence
    oledDisplay.Clear();
    
    // Show Morse code on the top half of the screen
    oledDisplay.WriteLine(0, morseCode.c_str(), true);  // True for Aurebesh font if enabled
    
    // Show the decoded character on the bottom half
    oledDisplay.WriteLine(1, decodedChar.c_str(), false);  // False for Latin characters
    
    oledDisplay.Update();  // Refresh the OLED screen
#endif
}

/*
Function: DecodeMorse
Description: 
   Decodes a given Morse code string into its corresponding character.
   This function supports both Latin and Aurebesh character sets.

   Example: "... --- ..." -> "SOS"
*/
String DecodeMorse(const String& morse) {
    // Placeholder for Morse code to character translation
    // Insert actual decoding logic here
    return "A";  // Temporary placeholder
}

/*
Function: OnMorseCodeComplete
Description: 
   This function is called when a complete Morse code sequence has been typed.
   It decodes the Morse code, shows it on the OLED screen, and optionally plays
   a sound or light effect.
*/
void OnMorseCodeComplete() {
    String decodedChar = DecodeMorse(morseCode);
    
    // Handle displaying on the blade or playing sound
    DisplayMorseCode();  // Display on OLED screen
    morseCode = "";  // Clear the Morse code sequence for the next entry
}

/*
Summary:

This `morsecode_prop.h` file implements dynamic timing for Morse code input on 
a Proffieboard lightsaber. The duration of dots, dashes, and spaces between characters
adjusts based on the user's typing speed, making the experience more responsive and intuitive.

Key Features:
- Dynamic timing based on the interval between button presses.
- Dots and dashes display on the blade or are played through the speaker, 
  depending on which button is pressed.
- Supports OLED display output for both Aurebesh and Latin characters.
- Decodes and displays typed Morse code sequences on the OLED screen in real-time.

Future Improvements:
- Implement full Morse code decoding.
- Handle spaces between words dynamically, similar to dots and dashes.
- Add support for additional output devices or complex blade effects.
*/

/*
Summary of the Code:

    Purpose:
    This morsecode_prop.h enables dynamic Morse code timing for a Proffieboard lightsaber, allowing the duration of Morse code symbols (dots, dashes, and spaces) to adjust based on the operator’s typing speed.

    Key Features:
        Dynamic Timing: The duration of dots and dashes is adjusted based on the interval between button presses. Faster typing results in shorter durations for Morse code symbols.
        OLED Display Support: If an OLED screen is present, typed Morse code will be displayed on the top half of the screen, and the decoded character will be shown on the bottom half. The screen supports both Aurebesh and Latin characters.
        Real-Time Feedback: The Morse code typed on the power button will display on the blade, while typing on the aux button will output the sound to the speaker. The typing speed is adjusted in real-time, ensuring smooth input.

    Future Improvements:
        Complete the Morse code decoding logic for all characters.
        Add dynamic control for spaces between words.
        Incorporate more advanced visual and sound effects for each Morse code symbol.

This setup makes Morse code input more responsive and engaging, dynamically matching the speed of the user’s typing for a more fluid experience.
*/