#include "Piezzo.h"

Piezzo::Piezzo(byte pin){
    this->pin = pin;
}

void Piezzo::soundTone(int frequency){
    tone(pin, frequency);
}

void Piezzo::soundTone(int frequency, int duration){
    tone(pin, frequency, duration);
}

void Piezzo::quiet(){
    noTone(pin);
}