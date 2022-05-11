#include "SimonLeds.h"

void SimonLeds::allOn() {
    greenLed.on();
    redLed.on();
    yellowLed.on();
    blueLed.on();
}

void SimonLeds::allOff() {
    greenLed.off();
    redLed.off();
    yellowLed.off();
    blueLed.off();
}


SimonLeds::SimonLeds(Led &greenLed, Led &redLed, Led &yellowLed, Led &blueLed, Piezzo &buzzer) {
    this-> greenLed = greenLed;
    this-> redLed = redLed;
    this-> yellowLed = yellowLed;
    this-> blueLed = blueLed;
    this-> buzzer = buzzer;

    void initSimonLeds();

}

void SimonLeds::flashCorrect() {

  for (int i = 0; i < 2; i++) {
    
    timer.startTimer(200);
    while (!timer.isTimerReady()){
    allOff();
    buzzer.quiet();
    }

    timer.startTimer(400);
    while(!timer.isTimerReady()){
    allOn();
    buzzer.quiet();
    }
  }
}

void SimonLeds::flashIncorrect() {

  for (int i = 0; i < 4; i++) {
    
    timer.startTimer(300);
    while (!timer.isTimerReady()){
    allOff();
    buzzer.quiet();
    }

    timer.startTimer(500);
    while(!timer.isTimerReady()){
    allOn();
    buzzer.soundTone(badSound);
    }
  }

}

void SimonLeds::initSimonLeds() {
    greenLed.init();
    redLed.init();
    yellowLed.init();
    blueLed.init();
}
