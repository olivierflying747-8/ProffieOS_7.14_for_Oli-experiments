// Revision 26 created by OlivierFlying747-8 (with a big help from ryryog25)
/*
Explanation:

    Button Handling:
        First Power Button Press:
            Plays the jetpack idle starting sound.
            Loops the idle sound until 1 minute passes, the jetpack is started, or
            the aux button is pressed (plays a false start sound and restarts the 1-minute idle loop).
            If no "Second Power Button Press" within 1 minute, the jetpack will shutdown (no sound effect).

        Second Power Button Press:
            Plays the jetpack starting sound.
            Loops the jetpack running sound until the power button is pressed again.

        Third Power Button Press:
            Plays the jetpack stopping sound.
            Loops the idle sound until 1 minute passes, the jetpack is restarted, or the Aux button is pressed
            (restarts the 1-minute idle loop).

        Aux Button Presses:
            When running: Plays a stuttering sound.
            When idle: Plays a false start sound and restarts the 1-minute idle loop.
            When off: Plays a self-destruct sound.

        The jetpack turns off automatically if idle for more than 1 minute.
        This can be changed with "#define JETPACK_IDLE_TIME 1000 * 60 * 1" (millisec * sec * minutes) in your config,
        you can change "1" to the minute(s) you want.

    Loop Function:
        Monitors the 1-minute timer during idle mode to turn off the jetpack completely if the time expires.

    To do:
        - Complete "blades effects" in "my_config.h"
          Here’s an example configuration for the blade setup:
StylePtr<InOutTrL<TrFade<300>, TrFade<300>, AudioFlicker<Red, Blue>>>,
StylePtr<InOutTrL<TrFade<300>, TrFade<300>, AudioFlicker<Red, White>, EffectUser<EFFECT_USER1>>>, // Running mode (yellow glow)
StylePtr<InOutTrL<TrFade<300>, TrFade<300>, AudioFlicker<Orange, White>, EffectUser<EFFECT_USER2>>>, // Stuttering mode (orange flash)
StylePtr<InOutTrL<TrFade<300>, TrFade<300>, AudioFlicker<Purple, White>, EffectUser<EFFECT_USER3>>>, // False start (purple flash)
StylePtr<InOutTrL<TrFade<300>, TrFade<300>, AudioFlicker<Red, White>, EffectUser<EFFECT_USER4>>>, // Self-destruct (red flash)
StylePtr<InOutTrL<TrFade<300>, TrFade<300>, AudioFlicker<Blue, White>, EffectUser<EFFECT_USER5>>>, // Shutdown (blue glow)
StylePtr<InOutTrL<TrFade<300>, TrFade<300>, AudioFlicker<White, White>, EffectUser<EFFECT_USER6>>>, // Idle (dim white)

        - Complete "Missile functions" activated with POWER & AUX, and make animations for OLED
*/

#ifndef PROPS_JETPACK_PROP_H
#define PROPS_JETPACK_PROP_H

#include "prop_base.h"
#include "../sound/sound_library.h"
//#include "../display/ssd1306.h"

#define PROP_TYPE Jetpack

#ifndef JETPACK_IDLE_TIME
#define JETPACK_IDLE_TIME 1000 * 60 * 1 // Jetpack max idle time in millisec (default 1 min) before shutdown
#endif

// == sounds for jetpack ==
EFFECT(startidlemode);      // jetpack starting at idle (0 to idle)     | v   <-- Just a check-list to make sure the
EFFECT(idle);               // jetpack running at idle                  | v    various sound effects are added in the code.
EFFECT(falsestart);         // jetpack false start sound                | v
EFFECT(startjetpack);       // jetpack starting sound (idle to run)     | v
EFFECT(running);            // jetpack running sound                    | v
EFFECT(stuttering);         // jetpack stuttering sound                 | v
EFFECT(shutdown);           // jetpack stopping sound (run to idle)     | v
//"NO_EFFECT()"             // I don't think idle to zero is needed ??? | v  // Not real syntax, just a place holder.
// == sounds for missile ==
EFFECT(selfdestruct);       // jetpack exploding sound                  | v
EFFECT(aiming);             // viewfinder coming down "click" sound     | v  // From Mando S02E06 "nice shot" "I was aiming for the other one"
EFFECT(targetting);         // viewfinder finds target sound            | v
EFFECT(missilelaunch);      // missile launch sound                     | v  // Make animations for OLED from the episode
EFFECT(missilegoesboom);    // explosion in the distance sound          | v
EFFECT(disarm);             // viewfinder going back up                 | v

class Jetpack : public PROP_INHERIT_PREFIX PropBase {
public:
    Jetpack() : PropBase(), jetpack_on_(false), idle_(false), timer_(0) {}
    const char* name() override { return "Jetpack"; }

    // Event handling for button presses
    bool Event(enum BUTTON button, EVENT event) override {
        if (event != EVENT_PRESSED) return false;

        if (button == BUTTON_POWER) {
            if (idle_) StartJetpack();                  // Transition from idle to running (rev more up)
            else if (jetpack_on_) ShutDownMode();       // Transition from running to idle (rev down)
            else StartIdleMode();                       // Jetpack initial start from 0 to idle (rev up)
            return true;
        }

        if (button == BUTTON_AUX) {
            if (jetpack_on_) {
            PlayStutteringSound();                      // Jetpack running, play stuttering
            //SaberBase::DoEffect(EFFECT_USER2, 0, 0);  // Trigger user effect for stuttering
            } else if (idle_) {
            PlayFalseStartSound();                      // Jetpack idle, play false start and reset idle timer
            //SaberBase::DoEffect(EFFECT_USER3, 0, 0);  // Trigger user effect for false start
            } else PlaySelfDestructSound();             // Jetpack off, play self-destruct
            //SaberBase::DoEffect(EFFECT_USER4, 0, 0);  // Trigger user effect for self-destruct
            return true;
        }
        if ((button == BUTTON_POWER) && (button == BUTTON_AUX)) {
            MissileLaunch();
            return true;
        }
    }

    // Optional Event2 function, if needed (currently does nothing)
    bool Event2(enum BUTTON button, EVENT event, uint32_t modifiers) override {
        return false;  // No action
    } // Missile launch, explosion & other functions, could be added here, I suppose ???

    // Transition to Running Mode (from idle to run)
    void StartJetpack() {
        jetpack_on_ = true;
        idle_ = false;
        //PlaySound(SFX_startjetpack);
        if (!hybrid_font.PlayPolyphonic(&SFX_startjetpack)) beep();
        PlayRunningSound();                                             // Will the jetpack running sound loop until next power press ???
        //SaberBase::DoEffect(EFFECT_USER1, 0, 0);      // Trigger user effect for running
        Serial.println("Jetpack ON and Running");
        //::../display/ssd1306:SetMessage("jetpack/n running");
        //display.SetMessage("jetpack running");
        //SetScreenNow(SCREEN_MESSAGE);
    }

    // Transition from Running Mode (from run to idle)
    void ShutDownMode() {
        jetpack_on_ = false;
        idle_ = true;
        if (!hybrid_font.PlayPolyphonic(&SFX_shutdown)) beep();
        //SaberBase::DoEffect(EFFECT_USER5, 0, 0);  // Trigger user effect for shutting down
        Serial.println("Jetpack Shutting Down");
        //SetMessage("jetpack/nshutdown");
        //SetScreenNow(SCREEN_MESSAGE);
    }

    // Initial start transition Mode (from 0 to idle)
    void StartIdleMode() {
        jetpack_on_ = false;
        idle_ = true;
        timer_ = millis();  // Start the idle timer
        if (!hybrid_font.PlayPolyphonic(&SFX_startidlemode)) beep();
        //SaberBase::DoEffect(EFFECT_USER6, 0, 0);  // Trigger user effect for idle
        StartIdleLoop();
        Serial.println("Jetpack Idling");
        //SetMessage("jetpack/nidling");
        //SetScreenNow(SCREEN_MESSAGE);
    }

    // Stop Idle Mode (Jetpack completely off)
    void StopIdleMode() {
        idle_ = false;
        Serial.println("jetpack completely off");
    }

    // Loop for Idle Mode
    void StartIdleLoop() {
        if (!hybrid_font.PlayPolyphonic(&SFX_idle)) beep();
    }

    // Main loop to handle idle timer
    void Loop() override {
        if (idle_ && (millis() - timer_ > JETPACK_IDLE_TIME)) {  // 1 minute in milliseconds
            StopIdleMode();  // Stop jetpack if idle for more than defined time
        }
    }

    // Play running Sound
    void PlayRunningSound() {
        if (!hybrid_font.PlayPolyphonic(&SFX_running)) beep();
    }

    // Jetpack running, play stuttering sound
    void PlayStutteringSound() {
        if (!hybrid_font.PlayPolyphonic(&SFX_stuttering)) beep();
        Serial.println("jetpack stuttering");
    }

    // Jetpack idle, play false start sound
    void PlayFalseStartSound() {
        if (!hybrid_font.PlayPolyphonic(&SFX_falsestart)) beep();
        Serial.println("jetpack false start");
        StartIdleLoop();
    }

    // Jetpack off, play self destruct
    void PlaySelfDestructSound() {
        if (!hybrid_font.PlayPolyphonic(&SFX_selfdestruct)) beep();
        Serial.println("jetpack self destruct");
        StopIdleMode(); // Turn off the jetpack completely after self-destruct
    }

    // Missile launch sequence
    void MissileLaunch() {
        if (!hybrid_font.PlayPolyphonic(&SFX_aiming)) beep();
        Serial.println("Aiming");
        // display on OLED (if OLED available) animation of viewfinder coming down;
        if (!hybrid_font.PlayPolyphonic(&SFX_targetting)) beep();
        Serial.println("Targetting");
        // display on OLED (if OLED available) animation of targetting;
        if (!hybrid_font.PlayPolyphonic(&SFX_missilelaunch)) beep();
        Serial.println("Launching Missile");
        // display on OLED (if OLED available) animation of jetpack launching missile;
        if (!hybrid_font.PlayPolyphonic(&SFX_missilegoesboom)) beep();
        // display on OLED (if OLED available) animation of explosion;
        Serial.println("Missile Explodes");
/*
        if !(jetpack_on_) {
            //SaberBase::DoEffect(EFFECT_USER4, 0, 0);
            #if defined(INCLUDE_SSD1306) || defined(ENABLE_SSD1306)
            Display on OLED ("Mando - Nice shot/nBoba - I was aiming for the other one")
            #endif
        }
*/
        if (!hybrid_font.PlayPolyphonic(&SFX_disarm)) beep();
        // display on OLED (if OLED available) animation of viewfinder going back up;
        Serial.println("Disarming");
    }

    void DoMotion(const Vec3&, bool) override { }  // I think a jetpack shouldn't have "movement effects"

private:
/*
    void PlaySound(int sound) {  // Changed to pass int by value, no & needed
        if (!hybrid_font.PlayPolyphonic(sound)) {
            beep();
        }
    }
    void PlaySound(Effect* sound) {  // Use Effect* directly
        if (!hybrid_font.PlayPolyphonic(sound)) {
            beep();
        }
    }
    void PlaySound(SoundFont& sound) {
        if (!hybrid_font.PlayPolyphonic(&sound)) {
            beep();
        }
    }

    void PlaySound(sound) {
        if (!hybrid_font.PlayPolyphonic(&SFX_sound)) {
            beep();
        }
    }
*/

    void beep() { // auto beepers (Fallback beep if sound fails/is missing), thanks to ryryog25
        beeper.Beep(0.05, 2000);
        beeper.Silence(0.05);
        beeper.Beep(0.05, 2000);
    }

    bool jetpack_on_;
    bool idle_;
    unsigned long timer_;
};

#endif // PROPS_JETPACK_PROP_H


/*
// From Jetpack guy (@Steve77)
#ifdef CONFIG_PRESETS
Preset presets[] = {
   { "SmthGrey", "tracks/press.wav",
    StyleFirePtr<RED, YELLOW>(),
    StylePtr<InOutHelper<White, 1,1>>(), "fire"}
};

BladeConfig blades[] = {
 { 0, WS281XBladePtr<16, bladePin, Color8::GRB, PowerPINS<bladePowerPin2, bladePowerPin3> >(),
    SimpleBladePtr<CH1LED, NoLED, NoLED, NoLED, bladePowerPin6, -1, -1, -1>()
  , CONFIGARRAY(presets) },
};
#endif
*/
