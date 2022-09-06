#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(10, 9); // CE, CSN

const byte address[6] = "ApaIT";

struct dataStream{
  int  X;   // 16bit
  int  Y;   // 16bit
  int Button;
};

dataStream joyStick;

void setup() {
  //Serial.begin(9600);
  pinMode(2,INPUT_PULLUP);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();

  
}


void loop() {
  joyStick.X = analogRead(A1);
  joyStick.Y = analogRead(A0);
  joyStick.Button = digitalRead(2);
  //kirim joyStick
  radio.write(&joyStick, sizeof(dataStream));

  
  //delay(100);
}
