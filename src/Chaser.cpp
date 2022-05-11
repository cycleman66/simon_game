#include "Chaser.h"

    Chaser::Chaser(Led &greenLed, Led &redLed, Led &yellowLed, Led &blueLed) {
        this->greenLed = greenLed;
        this->redLed = redLed;
        this->yellowLed = yellowLed;
        this->blueLed = blueLed;

        timer.startTimer(durationMs);
        Colour colour = green;  // start colour
    }

    void Chaser::setup() {
        greenLed.init();
        redLed.init();
        yellowLed.init();
        blueLed.init();

        greenLed.off();
        redLed.off();
        yellowLed.off();
        blueLed.off();

    }

    void Chaser::loop() {

        switch (colour) {
            case green:
                greenLed.on();

                if (timer.isTimerReady()) {
                    greenLed.off();
                    colour = red;
                    timer.startTimer(durationMs);
                }
                break;

            case red:
                redLed.on();

                if (timer.isTimerReady()) {
                    redLed.off();
                    colour = yellow;
                    timer.startTimer(durationMs);
                }
                break;

            case yellow:
                yellowLed.on();

                if (timer.isTimerReady()) {
                    yellowLed.off();
                    colour = blue;
                    timer.startTimer(durationMs);
                }
                break;

            case blue:
                blueLed.on();

                if (timer.isTimerReady()) {
                    blueLed.off();
                    colour = green;
                    timer.startTimer(durationMs);
                }
                break;
        }        
    }
