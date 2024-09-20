// attempt 025 (works with one saber + one blaster & no sound)

/*
multi_prop.h allows for 2 (3) (or more) discrete prop files to be used, 
alternating on a 2 buttons extra long push.
Your prop NEEDS to have two or more buttons.

How to use:
#ifdef CONFIG_PROP
#include "../props/multi_prop.h"
#include "../props/saber_fett263_buttons.h"
#include "../props/blaster.h"
#include "../props/detonator.h"    // <-- This doesn't work yet !!!
#undef PROP_TYPE
#define PROP_TYPE MultiProp <SaberFett263Buttons, Blaster, Detonator>
#endif

//#define MODE_SWITCH_TO_NEXT_PROP        //Place holder for the future. I have no idea how this should work?
/* @profezzorn: "I think your prop is going to need an enum which can take three values. 
Then everywhere there is an if statement that figures out which prop to call, you need to replace that 
with a switch() which select which prop to call.

If none of the above makes sense, go read some C++ basics first."
*/

#ifndef PROPS_MULTI_PROP_H
#define PROPS_MULTI_PROP_H

#ifdef PROP_INHERIT_PREFIX
#error multi_prop.h must be included first
#else
#define PROP_INHERIT_PREFIX virtual
#endif

#if NUM_BUTTONS < 2
#error Your prop NEEDS 2 or more buttons
#endif

#include "prop_base.h"

EFFECT(blastermode); 
EFFECT(sabermode); 
EFFECT(detmode);
//EFFECT(jetmode);
//EFFECT(droidmode);
//EFFECT(morsecodemode);
//EFFECT(tronmode);

enum class PropMode {
    SABER,
    BLASTER,
    //DETONATOR,  // Uncomment when ready to implement Detonator functionality
    //JETPACK,    // Uncomment when ready to implement Jetpack functionality (jetpack_prop.h in progress)
    //DROID,      // Uncomment if implementing Droid functionality
    //MORSECODE,  // Uncomment if implementing MorseCode functionality
    //TRON,       // Uncomment if implementing Tron Motorcycle Stick/Disk "Thingy" functionality (Why ? Because I have a very wild imagination & it sounds fun!)
};

// Define the duration for TWO_BUTTONS_eXtra_LONG_PUSH (4 sec)
#define TWO_BUTTONS_X_LONG_PUSH 1000 * 4

enum BUTTON_COMBO_STATE {
    BUTTONS_IDLE,
    BUTTONS_HOLDING,
    BUTTONS_HELD,
};

BUTTON_COMBO_STATE comboState = BUTTONS_IDLE;
unsigned long holdStartTime = 0;
PropMode currentMode = PropMode::SABER;  // Initial state is Saber

// Function to handle mode switching
void switchModes() {
    switch (currentMode) {
        case PropMode::SABER:
            currentMode = PropMode::BLASTER;
            break;
        case PropMode::BLASTER:
            currentMode = PropMode::SABER;                                  //::DETONATOR;
            break;
        //case PropMode::DETONATOR:
        //    currentMode = PropMode::SABER;
        //    break;
    }
}

template<class Saber, class Blaster>                                        //, class Detonator
class MultiProp : public virtual Saber, public virtual Blaster {            //, public virtual Detonator
public:
    uint32_t map_button(uint32_t b) {
        switch (b) {
#if NUM_BUTTONS == 3
            case BUTTON_AUX: return BUTTON_FIRE;
            case BUTTON_AUX2: return BUTTON_MODE_SELECT;
#else
            case BUTTON_POWER: return BUTTON_FIRE;
            case BUTTON_AUX: return BUTTON_MODE_SELECT;
#endif
            default: return b; } }
    uint32_t reverse_map_button(uint32_t b) {
        switch (b) {
#if NUM_BUTTONS == 3
            case BUTTON_FIRE: return BUTTON_AUX;
            case BUTTON_MODE_SELECT: return BUTTON_AUX2;
#else
            case BUTTON_FIRE: return BUTTON_POWER;
            case BUTTON_MODE_SELECT: return BUTTON_AUX;
#endif
            default: return b; } }

    const char* name() override { return "PropMode"; }

    // Event handling for button presses
    bool Event(enum BUTTON button, EVENT event) override {
        if (event == EVENT_PRESSED) {
            if (button == BUTTON_POWER || button == BUTTON_AUX) {
                if (comboState == BUTTONS_IDLE) {
                    holdStartTime = millis();   // Start the timer
                    comboState = BUTTONS_HOLDING;} } }
        else if (event == EVENT_RELEASED) {
            if (button == BUTTON_POWER || button == BUTTON_AUX) {
                comboState = BUTTONS_IDLE; } }  // Reset state if any button is released
        if (comboState == BUTTONS_HOLDING) {
            if ((millis() - holdStartTime) >= TWO_BUTTONS_X_LONG_PUSH) {
                comboState = BUTTONS_HELD;
                switchModes();                  // Switch the prop mode
                return true; } }                // Stop further event processing
        // Call the appropriate Event function based on the current mode
        switch (currentMode) {
            case PropMode::SABER:
                return Saber::Event(button, event);
            case PropMode::BLASTER:
                return Blaster::Event(button, event);
            //case PropMode::DETONATOR:
            //    return Detonator::Event(button, event);
       }
        return false;  // Event was not handled
    }

// Overriding Event2 to resolve ambiguity
    bool Event2(enum BUTTON button, EVENT event, uint32_t modifiers) override {
        // Call the appropriate Event2 function based on the current mode
        switch (currentMode) {
            case PropMode::SABER:
                return Saber::Event2(button, event, modifiers);
            case PropMode::BLASTER:
                return Blaster::Event2(button, event, modifiers);
            //case PropMode::DETONATOR:
            //   return Detonator::Event2(button, event, modifiers);
        }
    
        return false;  // Event was not handled
    }

    void SetPreset(int preset_num, bool announce) override {
        switch (currentMode) {
            case PropMode::SABER:
                Saber::SetPreset(preset_num, announce);
                break;
            case PropMode::BLASTER:
                Blaster::SetPreset(preset_num, announce);
                break;
            //case PropMode::DETONATOR:
            //    Detonator::SetPreset(preset_num, announce);
            //    break;
       }
    }
    void Loop() override {
        switch (currentMode) {
            case PropMode::SABER:
                Saber::Loop();
                break;
            case PropMode::BLASTER:
                Blaster::Loop();
                break;
            //case PropMode::DETONATOR:
            //    Detonator::Loop();
            //    break;
       }
    }
    void DoMotion(const Vec3& motion, bool clear) override {
        switch (currentMode) {
            case PropMode::SABER:
                Saber::DoMotion(motion, clear);
                break;
            case PropMode::BLASTER:
                Blaster::DoMotion(motion, clear);
                break;
            //case PropMode::DETONATOR:
            //    Detonator::DoMotion(motion, clear);
            //    break;
       }
    }
    void Clash(bool stab, float strength) override {
        switch (currentMode) {
            case PropMode::SABER:
                Saber::Clash(stab, strength);
                break;
            case PropMode::BLASTER:
                Blaster::Clash(stab, strength);
                break;
            //case PropMode::DETONATOR:
            //    Detonator::Clash(stab, strength);
            //    break;
       }
    }
    void SB_Effect(EffectType effect, float location) override {
        switch (currentMode) {
            case PropMode::SABER:
                if (!hybrid_font.PlayPolyphonic(&SFX_sabermode)) {
                    beeper.Beep(0.05, 2000);
                    beeper.Silence(0.05);
                    beeper.Beep(0.05, 2000);
                }
                Saber::SB_Effect(effect, location);
                break;
            case PropMode::BLASTER:
                if (!hybrid_font.PlayPolyphonic(&SFX_blastermode)) {
                    beeper.Beep(0.05, 2000);
                    beeper.Silence(0.05);
                    beeper.Beep(0.05, 2000);
                }
                Blaster::SB_Effect(effect, location);
                break;
            /*
            case PropMode::DETONATOR:
                if (!hybrid_font.PlayPolyphonic(&SFX_detmode)) {
                    beeper.Beep(0.05, 2000);
                    beeper.Silence(0.05);
                    beeper.Beep(0.05, 2000);
                }
                Detonator::SB_Effect(effect, location);
                break;
            */
       }
    }
};
#endif
