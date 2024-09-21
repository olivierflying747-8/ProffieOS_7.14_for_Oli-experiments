#ifndef PROPS_BLANK_PROP_H
#define PROPS_BLANK_PROP_H

#include "prop_base.h"

#define PROP_TYPE Blank

class Blank : public PROP_INHERIT_PREFIX PropBase {
public:
    Blank() : PropBase() {}
    const char* name() override { return "Blank"; }

    // Event handling for button presses (do nothing)
    bool Event(enum BUTTON button, EVENT event) override {
        return false;  // No action
    }

    // Optional Event2 function, if needed (currently does nothing)
    bool Event2(enum BUTTON button, EVENT event, uint32_t modifiers) override {
        return false;  // No action
    }
};

#endif // PROPS_BLANK_PROP_H