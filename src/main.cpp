#include <Arduino.h>
// #include "Simon.h"
#include "Led.h"
#include "SimonLeds.h"
#include "PushButton.h"
#include "Chaser.h"
// #include "SimonButton.h"
#include "Timer.h"
#include "Piezzo.h"

// hardware setup - pin definitions
#define GREEN_LED_PIN 13
#define RED_LED_PIN 12
#define YELLOW_LED_PIN 11
#define BLUE_LED_PIN 10
#define GREEN_BUTTON_PIN 2
#define RED_BUTTON_PIN 3
#define YELLOW_BUTTON_PIN 4
#define BLUE_BUTTON_PIN 5
#define BUZZER_PIN 8

const int redSound = 293;
const int greenSound = 261;
const int yellowSound = 329;
const int blueSound = 349;
const int badSound = 233;

// Game states for State Machine
enum State {
  RESET,
  START,
  DISPLAY_SEQUENCE,
  GET_USER_INPUT,
  USER_CORRECT,
  USER_ERROR,
  WIN,
};
State currentState = RESET;
State previousState = RESET;

// Global variables
int level = 1;
const int maxLevel = 30;
int sequence[maxLevel];
int sound[maxLevel];
int playerSequence[maxLevel];
int note = 0;
int velocity = 1000;


// instantiate objects
Led greenLed(GREEN_LED_PIN);
Led redLed(RED_LED_PIN);
Led yellowLed(YELLOW_LED_PIN);
Led blueLed(BLUE_LED_PIN);
Piezzo buzzer(BUZZER_PIN);
SimonLeds simonLeds(greenLed, redLed, yellowLed, blueLed, buzzer);
PushButton greenButton(GREEN_BUTTON_PIN, true, true);
PushButton redButton(RED_BUTTON_PIN, true, true);
PushButton yellowButton(YELLOW_BUTTON_PIN, true, true);
PushButton blueButton(BLUE_BUTTON_PIN, true, true);
Timer timer;
Chaser chaser(greenLed, redLed, yellowLed, blueLed);

// SimonButton greenSimonButton(greenLed, greenButton, buzzer, greenSound);
// SimonButton redSimonButton(redLed, redButton, buzzer, redSound);


void generateSequence() {
  // Generates random sequence
  // 1 = green, 2 = red, 3 = yellow, 4 = blue
 
  // Seed for true random number
  // randomSeed(millis());
 
  for (int i = 0; i < maxLevel; i++) {
 
    // generate random numbers between 1 and 4;
    sequence[i] = random(1, 5);
 
    switch (sequence[i]) {
      case 1:
        note = greenSound;
        break;
      case 2:
        note = redSound;
        break;
      case 3:
        note = yellowSound;
        break;
      case 4:
        note = blueSound;
        break;
    }
 
    // Sound will match LED output
    sound[i] = note;
    Serial.print(sequence[i]);
  }
}


void displaySequence() {
  // Turn off all LEDs
  simonLeds.allOff(); //?
 
  Serial.print("level = ");
  Serial.println(level);
 
  for (int i = 0; i < level; i++) {
    // Serial.print("Display Function sequence[i] is: ");
    // Serial.println(sequence[i]);

    delay(100); // so that notes don't run into each other

    switch (sequence[i]) {
      case 1:
        // Serial.println("Display case 1");
        timer.startTimer(velocity);
        while (!timer.isTimerReady()){
          greenLed.on();
          buzzer.soundTone(greenSound);
        }
        greenLed.off();
        buzzer.quiet();
      break;

      case 2:
        // Serial.println("Display case 2");
        timer.startTimer(velocity);
        while (!timer.isTimerReady()){
          redLed.on();
          buzzer.soundTone(redSound);
        }
        redLed.off();
        buzzer.quiet();
      break;
      
      case 3:
        // Serial.println("Display case");
        timer.startTimer(velocity);
        while (!timer.isTimerReady()){
          yellowLed.on();
          buzzer.soundTone(yellowSound);
        }
        yellowLed.off();
        buzzer.quiet();
      break;
      
      case 4:
        // Serial.println("Display case
        timer.startTimer(velocity);
        while (!timer.isTimerReady()){
          blueLed.on();
          buzzer.soundTone(blueSound);
        }
        blueLed.off();
        buzzer.quiet();
      break;

    }   // switch
  }   // for
}   // function


bool getSequence() {


  static bool flag;

  for (int i = 0; i < level; i++) {

    delay(250); // to avoid reading the previous button press on this for-loop
    
    flag = false;

    while (flag == false) { 

      if (greenButton.isPressed()) {

        timer.startTimer(500);

        while (!timer.isTimerReady()){
          greenLed.on();
          buzzer.soundTone(greenSound);
        }

        greenLed.off();
        buzzer.quiet();

        playerSequence[i] = 1;  // 1 = green
        flag = true;
        if (playerSequence[i] != sequence[i]) {
          return false;
        }
      }

      else if (redButton.isPressed()) {

        timer.startTimer(500);

        while (!timer.isTimerReady()){
          redLed.on();
          buzzer.soundTone(redSound);
        }
        
        redLed.off();
        buzzer.quiet();

        playerSequence[i] = 2;  // 2 = red
        flag = true;
        if (playerSequence[i] != sequence[i]) {
          return false;
        }
      }
      else if (yellowButton.isPressed()) {

        timer.startTimer(500);

        while (!timer.isTimerReady()){
          yellowLed.on();
          buzzer.soundTone(yellowSound);
        }

        yellowLed.off();
        buzzer.quiet();

        playerSequence[i] = 3;  // 3 = yellow
        flag = true;
        if (playerSequence[i] != sequence[i]) {
          return false;
        }
      }
      else if (blueButton.isPressed())
      {
        timer.startTimer(500);

        while (!timer.isTimerReady()){
          blueLed.on();
          buzzer.soundTone(blueSound);
        }

        blueLed.off();
        buzzer.quiet();

        playerSequence[i] = 4;  // 4 = blue
        flag = true;
        if (playerSequence[i] != sequence[i]) {
          return false;
        }
      }
      
    }
  }
  return true;
}


State resetState(){
  // Serial.println("RESET STATE");
  level = 1;
  velocity = 1000;
  simonLeds.allOff();
  buzzer.quiet();
  generateSequence();

  return START;
}

State startState(){
  // Serial.println("START STATE");
  chaser.loop();  // run chaser until green button is pressed

  if (greenButton.isPressed()) {
    simonLeds.allOff();
    timer.startTimer(2000);
    return DISPLAY_SEQUENCE;
  }
  return START; 
}

State displaySequenceState(){
  // Serial.println("DISPLAY SEQUENCE STATE");
  if (timer.isTimerReady()) {
    displaySequence();
    return GET_USER_INPUT;
  }
  return DISPLAY_SEQUENCE;
}

State getUserInputState(){
  // Serial.println("GET USER INPUT STATE");

  if (getSequence()) {
    timer.startTimer(250);  // for simonLeds.flashCorrect()
    return USER_CORRECT;
  }
  else {
    return USER_ERROR;
  }
}

State userCorrectState(){
  // Serial.println("USER CORRECT STATE");

  simonLeds.flashCorrect();
  level += 1;
  velocity -= 50;

  if (level > maxLevel) {
    return WIN;
  }

  timer.startTimer(1000);
  return DISPLAY_SEQUENCE; 
}

State userErrorState(){
  // Serial.println("USER ERROR STATE");
  timer.startTimer(500);
  simonLeds.flashIncorrect();

  return RESET;
}

State winState(){
  Serial.println("WIN STATE");
  return RESET;
}


void simonStateMachine() {

  previousState = currentState;

  switch (currentState) {

    case RESET: // 0
      currentState = resetState();
    break;

    case START: // 1
      currentState = startState();
    break;

    case DISPLAY_SEQUENCE: // 2
      currentState = displaySequenceState();
    break;

    case GET_USER_INPUT: // 3
      currentState = getUserInputState();
    break;

    case USER_CORRECT: // 4
      currentState = userCorrectState();
    break;

    case USER_ERROR:  // 5
      currentState = userErrorState();
    break;

    case WIN: // 6
      currentState = winState();
    break;

    default:
      currentState = RESET;
    break;

  }

}


void setup() {
  randomSeed(analogRead(A0)); // to generate a random seed
  greenButton.init();
  redButton.init();
  yellowButton.init();
  blueButton.init();
  Serial.begin(112500);
  chaser.setup();
}


void loop() {
  simonStateMachine();

  // if (currentState != previousState) {
  //   Serial.print("State = ");
  //   Serial.println(currentState);
  // }

}















