#ifndef PIEZZO_H
#define PIEZZO_H

#include <Arduino.h>

class Piezzo {

    private:
        byte pin;
        // int frequency;
        // int duration;

    public:
        Piezzo(){}  // default constructor - do not use
        Piezzo(byte pin);   // constructor

        void soundTone(int frequency);
        void soundTone(int frequency, int duration);
        void quiet();

};


#endif