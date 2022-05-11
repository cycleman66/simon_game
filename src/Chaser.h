#ifndef CHASER_H
#define CHASER_H

#include <Arduino.h>
#include "Led.h"
#include "Timer.h"

class Chaser {

    private:
        Led greenLed;
        Led redLed;
        Led yellowLed;
        Led blueLed;
        Timer timer;

        int durationMs {100};

        enum Colour {
            green,
            red,
            yellow,
            blue,
        };
        Colour colour;

    public:
        Chaser(){}; // default constructor, do not use
        Chaser(Led &greedLed, Led &redLed, Led &yellowLed, Led &blueLed);

    void setup();

    void loop();


};


#endif