// attempt 029 (working version for saber-blaster-detonator-jetpack, all with sound-effects on transition between props.
//                                                                       (provided by NoSloppy)

/*
multi_prop.h allows for 4 discrete prop files to be used, 
alternating on a 2 buttons extra long push.
Your prop NEEDS to have two or more buttons.
Multi_prop.h MUST be declared first.

How to use:
#ifdef CONFIG_PROP                              //What to use in PROP_TYPE MultiProp <...>
#include "../props/multi_prop.h"                //use MultiProp <...> (choose only 1 saber & 1 blaster)
//#include "../props/saber.h"                   //use Saber                             | Compiling with multi_prop.h
//#include "../props/saber_BC_buttons.h"        //use SaberBCButtons                    | Compiling with multi_prop.h
#include "../props/saber_fett263_buttons.h"     //use SaberFett263Buttons               | Compiling with multi_prop.h
//#include "../props/saber_sa22c_buttons.h"     //use SaberSA22CButtons                 | Compiling with multi_prop.h
//#include "../props/saber_shtok_buttons.h"     //use SaberShtokButtons                 | Compiling with multi_prop.h
//#include "../props/blaster.h"                 //use Blaster                           | Compiling with multi_prop.h
//These 4 EFFECT need to be here before #include "../props/blaster_BC_buttons.h" or it will not compile with multi_prop.h
//=======================================================================================================================
#ifndef PROPS_SABER_BC_BUTTONS_H
EFFECT(volup);      // for increse volume
EFFECT(voldown);    // for decrease volume
EFFECT(volmin);     // for minimum volume reached
EFFECT(volmax);     // for maximum volume reached
#endif
#include "../props/blaster_BC_buttons.h"        //use BlasterBC                         | Compiling with multi_prop.h (after modifications to BlasterBC on line 152
                                                //                                      | from "#ifndef PROPS_DUAL_PROP_H" to "#if !defined(PROPS_MULTI_PROP_H) && !defined(PROPS_DUAL_PROP_H)"
                                                //                                      | Also need to add in "../common/saber_base.h" on line 105 "DEFINE_EFFECT(DESTRUCT)" or BlasterBC will just no work !
#include "../props/detonator.h"                 //use Detonator                         | Compiling with multi_prop.h (but line 17 needs to be changed from "constexpr bool powered_ = true;"
                                                //                                      | to "bool powered_ = true;" or to "static constexpr bool powered_ = true;")
#include "../props/jetpack_prop.h"              //use Jetpack                           | should ba able to compile with attempt 29
//#include "../props/droid_prop.h"              //To be created (play with droids sounds)
//#include "../props/morse_code_prop.h"         //To be created (type morse code on the buttons & it plays on LEDs & speaker)
                                                //(another of my crazy idea!)
//#include "../props/tron.h"                    //To be created for the Tron Motorcycle Stick/Disk "Thingy"
                                                //(Why ? Because I have a very wild imagination & it sounds fun!)
#undef PROP_TYPE
#define PROP_TYPE MultiProp <SaberFett263Buttons, Blaster, Detonator, Jetpack>
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
EFFECT(droidmode);
EFFECT(morsecodemode);
EFFECT(tronmode);

enum class PropMode {
    SABER,
    BLASTER,
    DETONATOR,
    JETPACK,      // Uncomment when ready to implement Jetpack functionality (jetpack_prop.h in progress)
    //DROID,      // Uncomment when ready to implement Droid functionality (droid_prop.h in progress)
    //MORSECODE,  // Uncomment when ready to implement MorseCode functionality (morsecode_prop.h in progress)
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
            currentMode = PropMode::DETONATOR;
            break;
        case PropMode::DETONATOR:
            currentMode = PropMode::JETPACK;
            break;
        case PropMode::JETPACK:
            currentMode = PropMode::SABER;
            break;                  //::DROID;         
        /*
        case PropMode::DROID:
            currentMode = PropMode::SABER;
            break;                  //::MORSECODE;
        case PropMode::MORSECODE:
            currentMode = PropMode::SABER;
            break;                  //::TRON;
        case PropMode::TRON:
            currentMode = PropMode::SABER;
            break;
        */
    }
}

template<class Saber, class Blaster, class Detonator, class Jetpack> /*, class Droid, class Morsecode, class Tron*/
class MultiProp : public virtual Saber, public virtual Blaster, public virtual Detonator, public virtual Jetpack { /*, public virtual Droid, public virtual Morsecode, public virtual Tron*/
public:
    uint32_t map_button(uint32_t b) {                       //
        switch (b) {                                        //
#if NUM_BUTTONS == 3                                        //
            case BUTTON_AUX: return BUTTON_FIRE;            //
            case BUTTON_AUX2: return BUTTON_MODE_SELECT;    //
#else                                                       //
            case BUTTON_POWER: return BUTTON_FIRE;          // I do not know if this part is needed in multi_prop.h
            case BUTTON_AUX: return BUTTON_MODE_SELECT;     // It is a copy from dual_prop.h
#endif                                                      //
            default: return b; } }                          // I do not know how or if I need to add to it for the other
    uint32_t reverse_map_button(uint32_t b) {               // props (Detonator & Jetpack) that I have added to multi_prop.h
        switch (b) {                                        //
#if NUM_BUTTONS == 3                                        //
            case BUTTON_FIRE: return BUTTON_AUX;            //
            case BUTTON_MODE_SELECT: return BUTTON_AUX2;    //
#else                                                       //
            case BUTTON_FIRE: return BUTTON_POWER;          //
            case BUTTON_MODE_SELECT: return BUTTON_AUX;     //
#endif                                                      //
            default: return b; } }                          //

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
            case PropMode::DETONATOR:
                return Detonator::Event(button, event);
            case PropMode::JETPACK:
                return Jetpack::Event(button, event);
            /*
            case PropMode::DROID:
                return Droid::Event(button, event);
            case PropMode::MORSECODE:
                return Morsecode::Event(button, event);
            case PropMode::TRON:
                return Tron::Event(button, event);
            */
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
            case PropMode::DETONATOR:
                return Detonator::Event2(button, event, modifiers);
            case PropMode::JETPACK:
               return Jetpack::Event2(button, event, modifiers);
            /*
            case PropMode::DROID:
               return Droid::Event2(button, event, modifiers);
            case PropMode::MORSECODE:
                return Morsecode::Event2(button, event);
            case PropMode::TRON:
               return Tron::Event2(button, event, modifiers);
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
            /*
            case PropMode::DROID:
                Droid::SetPreset(preset_num, announce);
                break;
            case PropMode::MORSECODE:
                Morsecode::SetPreset(preset_num, announce);
                break;
            case PropMode::TRON:
                Tron::SetPreset(preset_num, announce);
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
            /*
            case PropMode::DROID:
                Droid::Loop();
                break;
            case PropMode::MORSECODE:
                Morsecode::Loop();
                break;
            case PropMode::TRON:
                Tron::Loop();
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
            /*
            case PropMode::DROID:
                Droid::DoMotion(motion, clear);
                break;
            case PropMode::MORSECODE:
                Morsecode::DoMotion(motion, clear);
                break;
             case PropMode::TRON:
                Tron::DoMotion(motion, clear);
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
            /*
            case PropMode::DROID:
                Droid::Clash(stab, strength);
                break;
            case PropMode::MORSECODE:
                Morsecode::Clash(stab, strength);
                break;
            case PropMode::TRON:
                Tron::Clash(stab, strength);
                break;
            */
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
            case PropMode::DETONATOR:
                if (!hybrid_font.PlayPolyphonic(&SFX_detmode)) {
                    beeper.Beep(0.05, 2000);
                    beeper.Silence(0.05);
                    beeper.Beep(0.05, 2000);
                }
                Detonator::SB_Effect(effect, location);
                break;
            case PropMode::JETPACK:
                if (!hybrid_font.PlayPolyphonic(&SFX_jetmode)) {
                    beeper.Beep(0.05, 2000);
                    beeper.Silence(0.05);
                    beeper.Beep(0.05, 2000);
                }
                Jetpack::SB_Effect(effect, location);
                break;
            /* 
            case PropMode::DROID:
                if (!hybrid_font.PlayPolyphonic(&SFX_droidmode)) {
                    beeper.Beep(0.05, 2000);
                    beeper.Silence(0.05);
                    beeper.Beep(0.05, 2000);
                }
                Droid::SB_Effect(effect, location);
                break;
            case PropMode::MORSECODE:               //No "SFX" for Morsecode, it will be in morse code !
                {   beeper.Beep(0.05, 2000);
                    beeper.Silence(0.05);
                    beeper.Beep(0.05, 4000);
                    beeper.Silence(0.05);
                    beeper.Beep(0.05, 2000);
                    beeper.Silence(0.05);
                    beeper.Beep(0.05, 2000);
                }
                Morsecode::SB_Effect(effect, location);
                break;
            case PropMode::TRON:
                if (!hybrid_font.PlayPolyphonic(&SFX_tronmode)) {
                    beeper.Beep(0.05, 2000);
                    beeper.Silence(0.05);
                    beeper.Beep(0.05, 2000);
                }
                Tron::SB_Effect(effect, location);
                break;
            */
       }
    }
};
#endif

/*
our multi_prop.h file is well-organized, and it lays the groundwork for switching between different prop modes such as Saber, Blaster, Detonator, Jetpack, and others (Morsecode, Droid, Tron) once implemented. The core structure for handling events, looping, motion, clashes, and sound effects seems in place.

Here are a few observations and suggestions to further refine it:
Suggestions:

    Combo Button Handling (comboState and switching logic):
        The button handling logic is currently written to switch modes if either the Power or Aux button is held for 4 seconds. You may want to add a visual or audible feedback when mode switching occurs (e.g., play a short sound effect or flash the blade) to confirm the change.

    Sound Effect Fallback:
        You use a fallback beep in SB_Effect() when the polyphonic sound is not available for the mode. If you want the system to strictly avoid fallback sounds, consider adding custom sounds for each prop mode or refining the fallback conditions based on your needs.

    Unused Class Declarations (Commented Modes):
        Classes for Droid, Morsecode, and Tron modes are commented out but referenced in several places. Once you implement these classes, uncomment the corresponding cases and effects in the various functions (Event(), SetPreset(), Loop(), etc.).

    Button Mapping:
        You have a basic button mapping for 2-button and 3-button setups. If you plan to expand the functionality for additional props or adjust the behavior of the Detonator or Jetpack modes, make sure that the button mappings for each mode are clear and work well with all the different modes.

    Extending switchModes():
        Once you start implementing the other prop modes (Morsecode, Droid, Tron), don't forget to extend switchModes() and the other switch statements to handle these new modes. The same applies to effects like SFX_droidmode or any other specific sounds/effects for these modes.

    Mode Feedback:
        Depending on how you want users to interact with different modes, you might want to add a feedback mechanism that indicates which mode is active, such as different LED colors or flashes.

    Jetpack Integration:
        Since the Jetpack mode is already uncommented, make sure you are ready to link it with the behavior described in your jetpack_prop.h file, especially focusing on the event handling and the sound effect playback.

Next Steps:

    Refactor when needed: Once the other prop modes are implemented, revisit the code to refactor repeated logic between modes.
    Testing: Test thoroughly to ensure smooth transitions between modes and proper event handling, especially for long presses and combos.

Would you like to further refine specific parts of the code, or should I help you implement the remaining modes like Morsecode or Droid next?
*/
