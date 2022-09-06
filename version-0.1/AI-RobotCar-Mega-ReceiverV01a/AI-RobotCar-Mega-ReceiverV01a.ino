#include "AI_RobotCar.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

/*
 * September 2022
 * ApaITU RobotCar example code
 * Receiver Arduino Mega
 * RF24 pins
 * CE : 47
 * CSN : 48
 * 
 * L298 pins
 * pinL_A : 5
 * pinL_B : 6
 * pinL_EN : 7
 * pinR_A : 8
 * pinR_B : 9
 * pinR_EN : 10
 * 
 * Single JoyStick
 * UP: Forward
 * Down : Reverse
 * Full Left : Rotate
 * Left : Turn Left
 * Center : Straigth
 * Right : Turn Right
 * Full Right : Rotate Right
 */
RF24 radio(47, 48); // CE, CSN

const byte address[6] = "ApaIT";

struct dataStream{
  int  X;   // 16bit
  int  Y;   // 16bit
  int Button;
};

dataStream joyStick;


/*
 * TODO
 * nRF24L01
 * calibrate the input of joystick, make sure 0 at 512
 */

AI_RobotCar Car(5,6,7,8,9,10);

void setup() {
  //Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

}

void loop() {
    if (radio.available()) {
    radio.read(&joyStick, sizeof(dataStream));

    Car.control(joyStick.X,joyStick.Y);

  }
  //delay(300);


}


    /*
    Serial.println("joyStick.X : " + String(joyStick.X));
    Serial.println("joyStick.Y : " + String(joyStick.Y));
    Serial.println("joyStick.Button : " + String(joyStick.Button));
    */
