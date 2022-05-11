#ifndef PUSH_BUTTON_H   // header guards (define guards)
#define PUSH_BUTTON_H

#include <Arduino.h>

class PushButton
{
    private:
        byte pin;
        byte state;

        bool isPullUp;  // are we using a Pull Up resistor? TRUE if yes, FALSE if no.
        bool internalPullUpActivated;   // are we using internal Pull Up?

        unsigned long lastTimeStateChanged;
        unsigned long debounceDelay;
        
        void readState();

    public:
        PushButton() {} // do not use
        PushButton(byte pin, bool isPullUp, bool internalPullUpActivated);

        void init();

        bool isPressed();
    
};

#endif