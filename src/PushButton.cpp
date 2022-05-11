#include "PushButton.h"

PushButton::PushButton(byte pin, bool isPullUp, bool internalPullUpActivated){
    this->pin = pin;
    this->isPullUp = isPullUp;
    this->internalPullUpActivated = internalPullUpActivated;

    lastTimeStateChanged = millis();
    debounceDelay = 50;
}

void PushButton::init(){
    if (isPullUp && internalPullUpActivated){
        pinMode(pin, INPUT_PULLUP);
    }
    else {
        pinMode(pin, INPUT);
    }
    state = digitalRead(pin);
}
void PushButton::readState(){
    unsigned long timeNow = millis();
    if (timeNow - lastTimeStateChanged > debounceDelay) {
        byte newState = digitalRead(pin);
        if (newState != state){
            state = newState;
            lastTimeStateChanged = timeNow; 
        }
    }
}

bool PushButton::isPressed(){
    readState();
    if (isPullUp){
        return (state == LOW);
    }
    else {
        return (state == HIGH);
    }
}