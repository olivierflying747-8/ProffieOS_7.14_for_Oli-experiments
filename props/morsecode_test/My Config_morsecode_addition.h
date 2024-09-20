//my_config.h Blade Effects

// Define styles for Morse code blade effects in `my_config.h`
#define MORSE_LETTER_STYLE StylePtr<InOutHelper<Blue, Black>>()  // Blue blade effect for letters
#define MORSE_NUMBER_STYLE StylePtr<InOutHelper<Red, Black>>()   // Red blade effect for numbers
#define MORSE_SPECHAR_STYLE StylePtr<InOutHelper<Green, Black>>()   // Green blade effect for special characters

// Blade pulse effect function (for quick flashes)
void BladePulse(int duration) {
    SetColor(255, 255, 255);  // Flash white light during Morse code pulse
    delay(duration);  // Keep it on for the dot/dash duration
    SetColor(0, 0, 0);  // Turn off blade (or return to normal)
}