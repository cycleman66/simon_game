#include "Led.h"

Led::Led(byte pin)   // We need to add the class name in front of any function
{
    this->pin = pin;
    state = LOW;
}

void Led::init()
{
    pinMode(pin, OUTPUT);
}

void Led::init(byte defaultState)
{
    init();
    if (defaultState == HIGH) {
    on();
    }
    else {
    off();
    }
}

void Led::on()
{
    state = HIGH;
    digitalWrite(pin, state);
}

void Led::on(byte brightness){
    state = HIGH;
    analogWrite(pin, brightness);
}


void Led::off()
{
    state = LOW;
    digitalWrite(pin, state);
}

void Led::toggle(){
    if (isPoweredOn()){
       off(); 
    }
    else {
        on();
    }
}

// returns TRUE or FALSE
bool Led::isPoweredOn(){
    return (state == HIGH);
}

void Led::pulseLed(int pulseDuration){
    timer.startTimer(pulseDuration);
    on();
    if (timer.isTimerReady()) {
        off();
    }    
}