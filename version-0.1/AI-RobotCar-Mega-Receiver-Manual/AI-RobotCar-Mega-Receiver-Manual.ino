#include "AI_RobotCar.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(47, 48); // CE, CSN

const byte address[6] = "ApaIT";

struct dataStream{
  int  X;   // 16bit
  int  X0;
  int  Y;   // 16bit
  int  Y0;
  int Button;
};

dataStream joyStick;


/*
 * TODO
 * nRF24L01
 * calibrate the input of joystick, make sure 0 at 512
 */

AI_RobotCar Car(5,6,7,8,9,10,"ApaCar");

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

}
/*
void loop() {
    if (radio.available()) {
    radio.read(&joyStick, sizeof(dataStream));
    //
    Serial.println("joyStick.X : " + String(joyStick.X));
    Serial.println("joyStick.Y : " + String(joyStick.Y));
    Serial.println("joyStick.Button : " + String(joyStick.Button));
    //
    Car.control(joyStick.X,joyStick.X0,joyStick.Y,joyStick.Y0);

  }
  //delay(500);


}
*/

void loop(){
  Car.control(500,590,500,590);
  delay(1000);
}
