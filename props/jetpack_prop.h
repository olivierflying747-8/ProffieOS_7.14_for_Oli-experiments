// Revision 22 created by OlivierFlying747-8 (with a big help from ryryog25) This is work in progress.
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
        Add "Missile functions", would a double click or a long push work ??? Should this be in "Event" or "Event2" ???
                                                                                What is "Event2" for anyways ???
        Add "blades effects", if at all possible ??? (probably needs to be done in "my_config.h" ???)

*/

#ifndef PROPS_JETPACK_PROP_H
#define PROPS_JETPACK_PROP_H

#include "prop_base.h"
#include "../sound/sound_library.h"

#define PROP_TYPE Jetpack

#ifndef JETPACK_IDLE_TIME
#define JETPACK_IDLE_TIME 1000 * 60 * 1 // Jetpack max idle time in millisec (default 1 min) before shutdown
#endif

EFFECT(startidlemode);      // jetpack starting at idle (0 to idle)     | v   <-- Just a check-list to make sure
EFFECT(idle);               // jetpack running at idle                  | v    the various sound effects are added.
EFFECT(falsestart);         // jetpack false start sound                | v
EFFECT(startjetpack);       // jetpack starting sound (idle to run)     | v
EFFECT(running);            // jetpack running sound                    | v
EFFECT(stuttering);         // jetpack stuttering sound                 | v
EFFECT(shutdown);           // jetpack stopping sound (run to idle)     | v
//"NO_EFFECT()"             // I don't think idle to zero is needed ??? | v  // Not real syntax, just a place holder.
EFFECT(selfdestruct);       // jetpack exploding sound                  | v
//EFFECT(aiming);           // viewfinder coming down "click" sound     | o  // From Mando S02E06 "nice shot" "I was aiming for the other one"
//EFFECT(targetting);       // viewfinder finds target sound            | o
//EFFECT(missilelaunch);    // missile launch sound                     | o
//EFFECT(missilegoesboom);  // explosion in the distance sound          | o
//EFFECT(name ?)            // viewfinder going back up                 | o

class Jetpack : public PROP_INHERIT_PREFIX PropBase {
public:
    Jetpack() : PropBase(), jetpack_on_(false), idle_(false), timer_(0) {}
    const char* name() override { return "Jetpack"; }

    // Event handling for button presses
    bool Event(enum BUTTON button, EVENT event) override {
        if (event != EVENT_PRESSED) return false;

        if (button == BUTTON_POWER) {
            if (idle_) StartJetpack();              // Transition from idle to running (rev more up)
            else
                if (jetpack_on_) ShutDownMode();    // Transition from running to idle (rev down)
                else StartIdleMode();               // Jetpack initially starts idle (rev up)
                }
            return true;

        if (button == BUTTON_AUX)
            if (jetpack_on_)
                if (!hybrid_font.PlayPolyphonic(&SFX_stuttering)) beep();       // Jetpack running, play stuttering
            else
                if (idle_) {
                    if (!hybrid_font.PlayPolyphonic(&SFX_falsestart)) beep();   // Jetpack idle, play false start and reset idle timer
                    StartIdleLoop();
                    } 
                else
                    if (!hybrid_font.PlayPolyphonic(&SFX_selfdestruct)) beep(); // Jetpack off, play self-destruct
            return true;
    }

    // Overriding Event2 to resolve ambiguity
    bool Event2(enum BUTTON button, EVENT event, uint32_t) override {
        return Event(button, event);
    }   // Missile launch, explosion & other functions, could come here I suppose ???

    // Transition to Running Mode (from idle to run)
    void StartJetpack() {
        jetpack_on_ = true;
        idle_ = false;
        if (!hybrid_font.PlayPolyphonic(&SFX_startjetpack)) beep();
        if (!hybrid_font.PlayPolyphonic(&SFX_running)) beep();          // Will the jetpack running sound loop until
        Serial.println("Jetpack ON and Running");                       // next power press ???
        }

    // Transition from Running Mode (from run to idle)
    void ShutDownMode() {
        jetpack_on_ = false;
        idle_ = true;
        if (!hybrid_font.PlayPolyphonic(&SFX_shutdown)) beep();
        Serial.println("Jetpack Shutting Down");
        }

    // Transition to Idle Mode (from 0 to idle)
    void StartIdleMode() {
        jetpack_on_ = false;
        idle_ = true;
        timer_ = millis();  // Start the idle timer
        if (!hybrid_font.PlayPolyphonic(&SFX_startidlemode)) beep();
        StartIdleLoop();
        Serial.println("Jetpack OFF, but Idling");
        }

    // Stop Idle Mode (Jetpack completely off)
    void StopIdleMode() {
        idle_ = false;
        Serial.println("Jetpack completely OFF");
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

/* --- The following are more place holders ---
    // Play running Sound
    void PlayRunningSound() {
        if (!hybrid_font.PlayPolyphonic(&SFX_running)) beep();
        }
    // Jetpack running, play stuttering sound
    void PlayStutteringSound() {
        if (!hybrid_font.PlayPolyphonic(&SFX_stuttering)) beep();
        }
    // Jetpack idle, play false start sound
    void PlayFalseStartSound() {
        if (!hybrid_font.PlayPolyphonic(&SFX_falsestart)) beep();
        }
    void PlaySelfDestructSound() {
        if (!hybrid_font.PlayPolyphonic(&SFX_selfdestruct)) beep();
        StopIdleMode(); // Turn off the jetpack completely after self-destruct
        }
*/

  void DoMotion(const Vec3&, bool) override { }     //I think a jetpack shouldn't have "movement effects" ???

private:
    void beep() { //auto beepers (Fallback beep if sound fails/is missing), thanks to ryryog25
        beeper.Beep(0.05, 2000);
        beeper.Silence(0.05);
        beeper.Beep(0.05, 2000);
    }

    bool jetpack_on_;
    bool idle_;
    unsigned long timer_;
};

#endif // PROPS_JETPACK_PROP_H
