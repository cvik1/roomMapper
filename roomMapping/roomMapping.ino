/*
 * The following code naviagates a robot along the right hand wall of a room
 * using ultrasonic sensors, storing room data to a microSD card.
 * This project is run on an Arduino Uno with a Adafruit motor shield, a
 * microSD reader shield, two DC motos, and two ultrasonic sensors.
 */


#include <Wire.h>
#include <Adafruit_MotorShield.h> //include motor shield library
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <SPI.h>
#include <SD.h>

// initialize motor shield and motor objects
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(2); // left motor
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(3); // right motor

// the Sd card is connected to the SPI bus as follows
const int mosi = 11;
const int miso = 12;
const int clk = 13;
const int CS = 8;

//declare varaibles needed for SD functions
Sd2Card card;
SdVolume volume;
SdFile file;

// define the pushbutton pin
const int PUSHBUTTON = 0;

// define pins for untrasonic sensors
const int trig1 = 6;
const int echo1 = 7;

const int trig2 = 2;
const int echo2 = 3;

void setup() {
  AFMS.begin(); // start motor shield
  // define input/output pins for untrasonic sensors
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT_PULLUP);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT_PULLUP);

  myMotor1->setSpeed(75);
  myMotor2->setSpeed(75);
/*
  //start the SD card
  if (!SD.begin(CS)) {
      //do something to let us know the card opened
      return;
  }
  myFile = SD.open("map_data", FILE_WRITE);
  //check to see if file opened
  if (myFile) {
      myFile.println("");
  }
  else {
      //do something to let us know the file isnt open
  }
*/
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


  // int length; // value to keep track of "how many movements"




  // if right wall is within range, and no object is close enough
  // in front, continue
  if (front > 15 && right < 10) {
    delay(40);

    // robot has small tendency to right, so if right wall is too close, we'll do a small corrective turn
    /*
    if (right<5) {
      delay(40);
      myMotor1->run(BACKWARD); //run left back and right forward
      myMotor2->run(FORWARD); // to turn left

      delay(100); //wait short amount of time for very small turn

      // this movement does not affect the map and so will not be recorded.
    }
    */

    myMotor1->run(FORWARD);
    myMotor2->run(FORWARD);

    delay(400); // give robot time to move forward
    /*
    myFile.println(0);
    length++;
    */
  }

  // if right wall is too far, turn right and continue forward
  else if (front > 15 && right > 10) {
    delay(40);
    myMotor1->run(FORWARD); // run left forward and right backward
    myMotor2->run(BACKWARD); // to turn to the right

    delay(625); // wait long enough that we can turn 45˚

    myMotor1->run(FORWARD); // continue forward
    myMotor2->run(FORWARD);

    /*
    myFile.println(1);
    length+=2;
    */
  }

  // if right wall is close and front is close, we have a corner so
  // turn left and continue forward
  //TODO calculate turning radius and configure turns
  else if (front < 15 && right < 10) {
    delay(40);
    myMotor1->run(BACKWARD); // run left back and right forward
    myMotor2->run(FORWARD); // to turn to the left

    delay(625); //wait long enough that we can turn 45˚

    myMotor1->run(FORWARD); // continue forward
    myMotor2->run(FORWARD);

    /*
    myFile.println(2);
    length+=2;
    */
  }
  myMotor1->run(RELEASE);
  myMotor2->run(RELEASE);
  delay(100);
}
