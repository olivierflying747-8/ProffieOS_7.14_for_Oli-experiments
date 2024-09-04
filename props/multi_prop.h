#ifndef PROPS_MULTI_PROP_H
#define PROPS_MULTI_PROP_H

/*
multi_prop.h allows for 3 (or more) discrete prop files to be used, 
alternating on a 2 buttons extra long push.
Your prop NEEDS to have two or more buttons.
This is useful when you want a saber (with or without a blade), to toggle to a blaster, to a thermal detonator, //to a jetpack
and you want the buttons to take on different behaviors.

How to use:
#ifdef CONFIG_PROP
#include "../props/multi_prop.h"
#include "../props/saber_fett263_buttons.h"
#include "../props/blaster.h"                //or "../props/blaster_DC_buttons.h"
#include "../props/detonator.h"
//#include "../props/jetpack.h"              //to be created
#undef PROP_TYPE
#define PROP_TYPE SaberBlasterPropDetonator<saber_fett263_buttons, Blaster, Detonator>         //SaberBlasterDetonatorJetpakProp<saber_fett_263_buttons, Blaster, Detonator,Jetpack>
#endif
*/

enum class PropState {
    SABER,
    BLASTER,
    DETONATOR,
    //JETPACK,  // Uncomment if implementing Jetpack functionality
};

// Define the duration for TWO_BUTTONS_X_LONG_PUSH
#define TWO_BUTTONS_X_LONG_PUSH 4000  // Duration in milliseconds

enum BUTTON_COMBO_STATE {
  BUTTONS_IDLE,
  BUTTONS_HOLDING,
  BUTTONS_HELD,
};

BUTTON_COMBO_STATE comboState = BUTTONS_IDLE;
unsigned long holdStartTime = 0;
PropState currentMode = PropState::SABER;  // Initial state is Saber

// Function to handle mode switching
void switchModes() {
    switch (currentMode) {
        case PropState::SABER:
            currentMode = PropState::BLASTER;
            break;
        case PropState::BLASTER:
            currentMode = PropState::DETONATOR;
            break;
        case PropState::DETONATOR:
            currentMode = PropState::SABER;
            break;
        //case PropState::JETPACK:
        //    currentMode = PropState::SABER;
        //    break;
    }
    // Feedback for mode switch (sound or LED)
}

bool Event(enum BUTTON button, EVENT event) override {
    // Handle button press events
    if (event == EVENT_PRESSED) {
        if (button == BUTTON_POWER || button == BUTTON_AUX) {
            if (comboState == BUTTONS_IDLE) {
                holdStartTime = millis();  // Start the timer
                comboState = BUTTONS_HOLDING;
            }
        }
    }
    // Handle button release events
    else if (event == EVENT_RELEASED) {
        if (button == BUTTON_POWER || button == BUTTON_AUX) {
            comboState = BUTTONS_IDLE;  // Reset if any button is released
        }
    }

    // Check if both buttons are held long enough to trigger TWO_BUTTONS_X_LONG_PUSH
    if (comboState == BUTTONS_HOLDING) {
        if ((millis() - holdStartTime) >= TWO_BUTTONS_X_LONG_PUSH) {
            if (button == (BUTTON_POWER | BUTTON_AUX)) {
                comboState = BUTTONS_HELD;
                switchModes();  // Switch the prop mode
                return true;  // Stop further event processing
            }
        }
    }

    // If no custom event is triggered, pass the event to the default handler
    switch (currentMode) {
        case PropState::SABER:
            return Saber::Event(button, event);
        case PropState::BLASTER:
            return Blaster::Event(button, event);
        case PropState::DETONATOR:
            return Detonator::Event(button, event);
    }

    return false;
}

// Template class to handle multiple props
template<class Saber, class Blaster, class Detonator/*, class Jetpack*/>
class SaberBlasterProp : public virtual Saber, public virtual Blaster, public virtual Detonator /*, public virtual Jetpack*/ {
public:
    // Button mapping logic
    uint32_t map_button(uint32_t b) {
        switch (b) {
#if NUM_BUTTONS == 3
            case BUTTON_AUX: return BUTTON_FIRE;
            case BUTTON_AUX2: return BUTTON_MODE_SELECT;
#else
            case BUTTON_POWER: return BUTTON_FIRE;
            case BUTTON_AUX: return BUTTON_MODE_SELECT;
#endif
            default: return b;
        }
    }

    // Reverse button mapping logic
    uint32_t reverse_map_button(uint32_t b) {
        switch (b) {
#if NUM_BUTTONS == 3
            case BUTTON_FIRE: return BUTTON_AUX;
            case BUTTON_MODE_SELECT: return BUTTON_AUX2;
#else
            case BUTTON_FIRE: return BUTTON_POWER;
            case BUTTON_MODE_SELECT: return BUTTON_AUX;
#endif
            default: return b;
        }
    }

    const char* name() override { return "SaberBlasterProp"; }

    bool Event(enum BUTTON button, EVENT event) override {
        // Handle the TWO_BUTTONS_X_LONG_PUSH event
        if (comboState == BUTTONS_HELD) {
            comboState = BUTTONS_IDLE;  // Reset combo state after handling
            return true;  // Event was handled by custom logic
        }

        // Call the appropriate Event function based on the current mode
        switch (currentMode) {
            case PropState::SABER:
                return Saber::Event(button, event);
            case PropState::BLASTER:
                return Blaster::Event(button, event);
            case PropState::DETONATOR:
                return Detonator::Event(button, event);
            // case PropState::JETPACK:
            //     return Jetpack::Event(button, event);
        }

        return false;  // Event was not handled
    }

    // Override other functions like Loop, Clash, etc. with similar logic
    // to handle them according to the current mode

    void Loop() override {
        switch (currentMode) {
            case PropState::SABER:
                Saber::Loop();
                break;
            case PropState::BLASTER:
                Blaster::Loop();
                break;
            case PropState::DETONATOR:
                Detonator::Loop();
                break;
            // case PropState::JETPACK:
            //     Jetpack::Loop();
            //     break;
        }
    }

    // Implement other methods similarly...

};

#endif  // PROPS_MULTI_PROP_H
