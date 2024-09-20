// attempt 037 (working version for saber-blaster-detonator-jetpack, all with sound-effects on transition between props.
//                                                                       (provided by NoSloppy)
// adding MorseCode

/*
multi_prop.h allows for 5 (maybe more coming) discrete prop files to be used, 
alternating on a 2 buttons extra long push (4 seconds - not customisable !) with or without a blade attached.
Blade detect function has no effect on multi_prop.h
Your prop NEEDS to have two or more buttons.
Multi_prop.h MUST be declared before the other props.
Props MUST be declared in the right order & one and only one of each type MUST be included.

This prop is for fun and not Star Wars cannon. It only exists to add extra functionality to your saber, if you so choose.
Thank you for reading.

You can find all 5 sound files (created by NoSloppy) used in multi_prop.h on my dropbox here:
https://www.dropbox.com/scl/fi/p2pj9os5v4seel0wmzwcz/Multi_prop_sounds_by_NoSloppy.zip?rlkey=hi6589mexymnx4jmxhtwqjfu0&st=3klofs5m&dl=0

How to use: add this to your config
#ifdef CONFIG_PROP                              //What to use in PROP_TYPE MultiProp <...>
#include "../props/multi_prop.h"                //use MultiProp <...> (choose only 1 saber & 1 blaster)
//#include "../props/saber_caiwyn_buttons.h"    //use CaiwynButtons   <-- works alone   | NOT compiling with multi_prop.h
//#include "../props/saber.h"                   //use Saber                | Compiling with multi_prop.h
//#include "../props/saber_BC_buttons.h"        //use SaberBCButtons       | Compiling with multi_prop.h
#include "../props/saber_fett263_buttons.h"     //use SaberFett263Buttons  | Compiling with multi_prop.h
//#include "../props/saber_sa22c_buttons.h"     //use SaberSA22CButtons    | Compiling with multi_prop.h
//#include "../props/saber_shtok_buttons.h"     //use SaberShtokButtons    | Compiling with multi_prop.h
//#include "../props/blaster.h"                 //use Blaster              | compiling with multi_prop.h (works with or without "bullet count" in CONFIG_BOTTOM)

// IMPORTANT NOTE: blaster_BC_buttons.h (at the time of writing) is not "stock" compatible with multi_prop.h
// A small modification needs to be added to it's code. I will let NoSloppy decide for the best course of action
// to modify his prop. I do have "my version" of blaster_BC_buttons.h working, so it is possible.

//These 4 EFFECTs need to be here before #include "../props/blaster_BC_buttons.h" or it will not compile with multi_prop.h
//========================================================================================================================
#ifndef PROPS_SABER_BC_BUTTONS_H
EFFECT(volup);      // for increse volume
EFFECT(voldown);    // for decrease volume
EFFECT(volmin);     // for minimum volume reached
EFFECT(volmax);     // for maximum volume reached
#endif
#include "../props/blaster_BC_buttons.h"        //use BlasterBC            | Compiling with multi_prop.h (after modifications to BlasterBC on line 152
                                                //                         | from "#ifndef PROPS_DUAL_PROP_H" to "#if !defined(PROPS_MULTI_PROP_H) && !defined(PROPS_DUAL_PROP_H)"
                                                //                         | Also need to add in "../common/saber_base.h" on line 105 "DEFINE_EFFECT(DESTRUCT)" or BlasterBC will just no work !
                                                //                         | (MUST have "bullets counts" activated in CONFIG_BOTTOM)
#include "../props/detonator.h"                 //use Detonator            | Compiling with multi_prop.h
#include "../props/jetpack_prop.h"              //use Jetpack              | Compiling with multi_prop.h
#include "../props/morsecode_prop.h"            //use MorseCode - In progress (type morse code on the buttons & it plays on LEDs, speaker & OLED)
                                                //(another of my crazy idea!)
//#include "../props/droid_prop.h"              //In progress (plays with droids sounds)
//#include "../props/vehicle_prop.h"            //To be created (find better name - plays with SW vehicles sounds and their weapons - ships, speeders, walkers, pod-racers, ...)
#undef PROP_TYPE
#define PROP_TYPE MultiProp <SaberFett263Buttons, Blaster, Detonator, Jetpack, MorseCode>
#endif
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
EFFECT(jetmode);
//"NO_EFFECT"(morsecodemode); // No need for a "morsecode.wav" file. This is done using "Beepers".
//EFFECT(droidmode);        // Uncomment if implementing droid
//EFFECT(vehiclemode);      // Uncomment if implementing Vehicle

enum class PropMode {
    SABER,
    BLASTER,
    DETONATOR,
    JETPACK,
    MORSECODE,      // (morsecode_prop.h in progress)
    //DROID,        // Uncomment when ready to implement Droid functionality (droid_prop.h in progress)
    //VEHICLE,      // Uncomment if implementing Vehicle
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
            if (!hybrid_font.PlayPolyphonic(&SFX_blastermode)) { //auto beepers (Fallback beep if sound fails/is missing)
                beeper.Beep(0.05, 2000);
                beeper.Silence(0.05);
                beeper.Beep(0.05, 2000);
                };
            currentMode = PropMode::BLASTER;
            break;
        case PropMode::BLASTER:
            if (!hybrid_font.PlayPolyphonic(&SFX_detmode)) { //auto beepers
                beeper.Beep(0.05, 2000);
                beeper.Silence(0.05);
                beeper.Beep(0.05, 2000);
                };
            currentMode = PropMode::DETONATOR;
            break;
        case PropMode::DETONATOR:
            if (!hybrid_font.PlayPolyphonic(&SFX_jetmode)) { //auto beepers
                beeper.Beep(0.05, 2000);
                beeper.Silence(0.05);
                beeper.Beep(0.05, 2000);
                };
            currentMode = PropMode::JETPACK;
            break;
        case PropMode::JETPACK:
            //No "SFX" for MorseCode, it will be in morse code !
                { beeper.Beep(0.05, 2000);
                beeper.Silence(0.05);
                beeper.Beep(0.05, 4000);
                beeper.Silence(0.05);
                beeper.Beep(0.05, 2000);
                beeper.Silence(0.05);
                beeper.Beep(0.05, 2000);
                };
            currentMode = PropMode::MORSECODE;
        case PropMode::MORSECODE:
            /*
            if (!hybrid_font.PlayPolyphonic(&SFX_droidmode)) { //auto beepers
                beeper.Beep(0.05, 2000);
                beeper.Silence(0.05);
                beeper.Beep(0.05, 2000);
                };
            currentMode = PropMode::DROID;
            break;
            */
            if (!hybrid_font.PlayPolyphonic(&SFX_sabermode)) { //auto beepers
                beeper.Beep(0.05, 2000);
                beeper.Silence(0.05);
                beeper.Beep(0.05, 2000);
                };
            currentMode = PropMode::SABER;
            break;
        /*
        case PropMode::DROID:
            if (!hybrid_font.PlayPolyphonic(&SFX_vehiclemode)) { //auto beepers
                beeper.Beep(0.05, 2000);
                beeper.Silence(0.05);
                beeper.Beep(0.05, 2000);
                };
            currentMode = PropMode::VEHICLE;
            break;
        case PropMode::VEHICLE:
            if (!hybrid_font.PlayPolyphonic(&SFX_sabermode)) { //auto beepers
                beeper.Beep(0.05, 2000);
                beeper.Silence(0.05);
                beeper.Beep(0.05, 2000);
                };
            currentMode = PropMode::SABER;
            break;
        */
    }
}

// Template to support multi-prop modes
template<class Saber, class Blaster, class Detonator, class Jetpack, class MorseCode> /*, class Droid, class Vehicle*/
class MultiProp : public virtual Saber, public virtual Blaster, public virtual Detonator, public virtual Jetpack, public virtual MorseCode { /*, public virtual Droid, public virtual Vehicle*/
public:

    // Button mapping for 2 and 3-button setups
             // The "Blater mapping"
  uint32_t map_button(uint32_t b) {
    switch (b) {
#if NUM_BUTTONS == 3
        case BUTTON_AUX: return BUTTON_FIRE;
        case BUTTON_AUX2: return BUTTON_MODE_SELECT;
#else
        case BUTTON_POWER: return  BUTTON_FIRE;
        case BUTTON_AUX: return BUTTON_MODE_SELECT;
#endif
      default: return b;
    }
  }
             // The "return to normal mapping"
  uint32_t reverse_map_button(uint32_t b) {
    switch (b) {
#if NUM_BUTTONS == 3
        case BUTTON_FIRE: return BUTTON_AUX;
        case BUTTON_MODE_SELECT: return BUTTON_AUX2;
#else
        case BUTTON_FIRE: return  BUTTON_POWER;
        case BUTTON_MODE_SELECT: return BUTTON_AUX;
#endif
      default: return b;
    }
  }

    const char* name() override { return "PropMode"; }

    // Event handling for button presses, including combos for switching modes
    bool Event(enum BUTTON button, EVENT event) override {
        if (event == EVENT_PRESSED) {
            if (button == BUTTON_POWER && button == BUTTON_AUX) {
                if (comboState == BUTTONS_IDLE) {
                    holdStartTime = millis();   // Start the timer
                    comboState = BUTTONS_HOLDING;
                }
            }
        }
        else if (event == EVENT_RELEASED) {
            if (button == BUTTON_POWER || button == BUTTON_AUX) {
                comboState = BUTTONS_IDLE;  // Reset state if any button is released
            }
        }
        if (comboState == BUTTONS_HOLDING) {
            if ((millis() - holdStartTime) >= TWO_BUTTONS_X_LONG_PUSH) {
                comboState = BUTTONS_HELD;
                switchModes();                  // Switch the prop mode
                return true;                    // Stop further event processing
            }
        }

        // Call the appropriate Event function based on the current mode
        switch (currentMode) {
            case PropMode::SABER:
                return Saber::Event(button, event);
                break;
            case PropMode::BLASTER: {
              button = static_cast<enum BUTTON>(map_button(button));
                  // Map modifiers to blaster
                  uint32_t m = current_modifiers;
                  current_modifiers = 0;
                  for (; m; m &= m - 1) current_modifiers |= map_button(m & -m);
                  bool ret = Blaster::Event(button, event);
                  // Map modifiers back to normal
                  m = current_modifiers;
                  current_modifiers = 0;
                  for (; m; m &= m - 1) current_modifiers |= reverse_map_button(m & -m);
                  return ret;
                };
                break;
            case PropMode::DETONATOR:
                return Detonator::Event(button, event);
                break;
            case PropMode::JETPACK:
                return Jetpack::Event(button, event);
                break;
            case PropMode::MORSECODE:
                return MorseCode::Event(button, event);
                break;
            /*
            case PropMode::DROID:
                return Droid::Event(button, event);
                break;
            case PropMode::VEHICLE:
                return Vehicle::Event(button, event);
                break;
            */
       }
        return false;  // Event was not handled
    }

    // Overriding Event2 to resolve ambiguity
    bool Event2(enum BUTTON button, EVENT event, uint32_t modifiers) override {
        switch (currentMode) {
            case PropMode::SABER:
                return Saber::Event2(button, event, modifiers);
                break;
            case PropMode::BLASTER:
                return Blaster::Event2(button, event, modifiers);
                break;
            case PropMode::DETONATOR:
                return Detonator::Event2(button, event, modifiers);
                break;
            case PropMode::JETPACK:
                return Jetpack::Event2(button, event, modifiers);
                break;
            case PropMode::MORSECODE:
                return MorseCode::Event2(button, event);
                break;
            /*
            case PropMode::DROID:
                return Droid::Event2(button, event, modifiers);
                break;
            case PropMode::VEHICLE:
               return Vehicle::Event2(button, event, modifiers);
                break;
            */
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
            case PropMode::DETONATOR:
                Detonator::SetPreset(preset_num, announce);
                break;
            case PropMode::JETPACK:
                Jetpack::SetPreset(preset_num, announce);
                break;
            case PropMode::MORSECODE:
                MorseCode::SetPreset(preset_num, announce);
                break;
            /*
            case PropMode::DROID:
                Droid::SetPreset(preset_num, announce);
                break;
            case PropMode::VEHICLE:
                Vehicle::SetPreset(preset_num, announce);
                break;
            */
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
            case PropMode::DETONATOR:
                Detonator::Loop();
                break;
            case PropMode::JETPACK:
                Jetpack::Loop();
                break;
            case PropMode::MORSECODE:
                MorseCode::Loop();
                break;
            /*
            case PropMode::DROID:
                Droid::Loop();
                break;
            case PropMode::VEHICLE:
                Vehicle::Loop();
                break;
            */
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
            case PropMode::DETONATOR:
                Detonator::DoMotion(motion, clear);
                break;
            case PropMode::JETPACK:
                Jetpack::DoMotion(motion, clear);
                break;
            case PropMode::MORSECODE:
                MorseCode::DoMotion(motion, clear);
                break;
            /*
            case PropMode::DROID:
                Droid::DoMotion(motion, clear);
                break;
             case PropMode::VEHICLE:
                Vehicle::DoMotion(motion, clear);
                break;
            */
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
            case PropMode::DETONATOR:
                Detonator::Clash(stab, strength);
                break;
            case PropMode::JETPACK:
                Jetpack::Clash(stab, strength);
                break;
            case PropMode::MORSECODE:
                MorseCode::Clash(stab, strength);
                break;
            /*
            case PropMode::DROID:
                Droid::Clash(stab, strength);
                break;
            case PropMode::VEHICLE:
                Vehicle::Clash(stab, strength);
                break;
            */
       }
    }

    void SB_Effect(EffectType effect, float location) override {
        switch (currentMode) {
            case PropMode::SABER:
                Saber::SB_Effect(effect, location);
                break;
            case PropMode::BLASTER:
                Blaster::SB_Effect(effect, location);
                break;
            case PropMode::DETONATOR:
                Detonator::SB_Effect(effect, location);
                break;
            case PropMode::JETPACK:
                Jetpack::SB_Effect(effect, location);
                break;
            case PropMode::MORSECODE:
                MorseCode::SB_Effect(effect, location);
                break;
            /* 
            case PropMode::DROID:
                Droid::SB_Effect(effect, location);
                break;
            case PropMode::VEHICLE:
                Vehicle::SB_Effect(effect, location);
                break;
            */
       }
    }

/*
private:
    void beep() { //auto beepers (Fallback beep if sound fails/is missing), thanks to ryryog25
        beeper.Beep(0.05, 2000);
        beeper.Silence(0.05);
        beeper.Beep(0.05, 2000);
    }
*/

};

#endif // PROPS_MULTI_PROP_H
