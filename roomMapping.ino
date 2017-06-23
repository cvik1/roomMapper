/*
 * The following code naviagates a robot along the right hand wall of a room
 * using ultrasonic sensors, storing room data to a microSD card.
 * This project is run on an Arduino Uno with a Adafruit motor shield, a
 * microSD reader shield, two DC motos, and two ultrasonic sensors.
 */


#include <Wire.h>
#include <Adafruit_MotorShield.h> //include motor shield library
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <EPROM.h> //include library to write to Arduino "hard drive"

// initialize motor shield and motor objects
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1); // left motor
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2); // right motor

// define pins for untrasonic sensors
const int trig1 = 12;
const int echo1 = 13;

const int trig2 = 6;
const int echo2 = 7;

void setup() {
  AFMS.begin(); // start motor shield
  // define input/output pins for untrasonic sensors
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT_PULLUP);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT_PULLUP);

  myMotor1->setSpeed(100);
  myMotor2->setSpeed(100);

}

void loop() {
  long duration1, duration2, front, right; // ultrasonic sensor varaibles

  // send trigger signals
  digitalWrite(trig1, LOW); // start low to clean noise
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH); // high pulse
  delayMicroseconds(10);
  digitalWrite(trig1, LOW); // finish low to ensure clean echo

  digitalWrite(trig2, LOW); // start low to clean noise
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH); // high pulse
  delayMicroseconds(10);
  digitalWrite(trig2, LOW); // finish low to ensure clean echo

  // read receiving signal
  duration1 = pulseIn(echo1, HIGH); // read in off echo pin
  // convert to ditance to object in front
  front = (duration1/2) / 29; // the return time is half of total time
  // divide by 29 for speed of sounce 29cm/µs

  duration2 = pulseIn(echo2, HIGH); // read in off echo pin
  right = (duration2/2) / 29; // distance to right wall

  // if right wall is within range, and no object is close enough
  // in front, continue
  if (front > 10 && right < 10) {
    delay(40);
    myMotor1->run(FORWARD);
    myMotor2->run(FORWARD);
    // TODO add movement to mapping data

  }

  // if right wall is too far, turn right and continue forward
  else if (front > 10 && right > 10) {
    myMotor1->run(FORWARD); // run left forward and right backward
    myMotor2->run(BACKWARD); // to turn to the right

    myMotor1->run(FORWARD); // continue forward
    myMotor2->run(BACKWARD);

    // TODO add movement to mapping data
  }

  // if right wall is close and front is close, we have a corner so
  // turn left and continue forward
  else if (front < 10 && right < 10) {
    myMotor1->run(BACKWARD); // run left back and right forward
    myMotor2->run(FORWARD); // to turn to the left

    myMotor1->run(FORWARD); // continue forward
    myMotor2->run(FORWARD);

    // TODO add movement to mapping data
  }

}
