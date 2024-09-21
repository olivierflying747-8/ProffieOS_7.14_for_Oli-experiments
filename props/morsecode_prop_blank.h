#ifndef PROPS_MORSECODE_PROP_H
#define PROPS_MORSECODE_PROP_H

#include "prop_base.h"

#define PROP_TYPE MorseCode

class MorseCode : public PROP_INHERIT_PREFIX PropBase {
public:
    MorseCode() : PropBase() {}
    const char* name() override { return "MorseCode"; }

    // Event handling for button presses
    bool Event(enum BUTTON button, EVENT event) override {
        return Event(button, event);
        return true;
    }

    // Optional Event2 function, if needed (currently does nothing)
    bool Event2(enum BUTTON button, EVENT event, uint32_t modifiers) override {
        return false;  // No action
    }
};

#endif // PROPS_MORSECODE_PROP_H
