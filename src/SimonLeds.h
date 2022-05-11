#ifndef SIMON_LEDS_H
#define SIMON_LEDS_H

#include <Arduino.h>
#include "Led.h"
#include "Timer.h"
#include "Piezzo.h"


class SimonLeds {

    private:
        Led greenLed;
        Led redLed;
        Led yellowLed;
        Led blueLed;
        Timer timer;
        Piezzo buzzer;

        byte cycles = 0;
        const int badSound = 233;

        void initSimonLeds();

    public:
        SimonLeds(){}   // default constructor - do not use
        SimonLeds(Led &greenLed, Led &redLed, Led &yellowLed, Led &blueLed, Piezzo &buzzer);

        void flashCorrect();

        void flashIncorrect();

        void allOn();

        void allOff();

        // void chaser(byte cycles);
        
};



#endif