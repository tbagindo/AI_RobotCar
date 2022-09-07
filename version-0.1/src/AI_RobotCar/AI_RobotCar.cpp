/*
* ApaITU channel : https://www.youtube.com/channel/UChBQyf27VmOEk8uWdQYuX-Q
* AI_RobotCar.cpp
* September 2022
* Version 01b
*/

#include <Arduino.h>
#include "AI_RobotCar.h"

AI_DCMotor::AI_DCMotor(byte pinA, byte pinB, byte pinEN){
  this->_pinA = pinA;
  this->_pinB = pinB;
  this->_pinEN = pinEN;
  init();
}

AI_DCMotor::AI_DCMotor(byte pinA, byte pinB, byte pinEN,String name){
  this->_pinA = pinA;
  this->_pinB = pinB;
  this->_pinEN = pinEN;
  this->_name = name;
  init();
}

void AI_DCMotor::init(){
  pinMode(_pinA,OUTPUT);
  pinMode(_pinB,OUTPUT);
  pinMode(_pinEN,OUTPUT);
}

void AI_DCMotor::setDir(byte DIR){
  if(DIR){  //forward
    digitalWrite(_pinA,HIGH);
    digitalWrite(_pinB,LOW);
    //Serial.println(getName()+ " setDir(Forward) ");
  }else{    //reverse
    digitalWrite(_pinA,LOW);
    digitalWrite(_pinB,HIGH);
    //Serial.println(getName()+ " setDir(Reverse) ");
  }
}

void AI_DCMotor::setSpeed(byte speed){
  byte pwm = map(speed,0,100,0,255);
  analogWrite(_pinEN,pwm);
  //Serial.println(getName()+ " setSpeed("+String(pwm)+") ");
}

String AI_DCMotor::getName(){
  return _name;
}

AI_RobotCar::AI_RobotCar(
    int pin1_A, 
    int pin1_B, 
    int pin1_EN, 
    int pin2_A, 
    int pin2_B, 
    int pin2_EN, 
    String name
    ) : 
    _mL(pin1_A,pin1_B,pin1_EN), 
    _mR(pin2_A,pin2_B,pin2_EN){
      this->_name = name;
}

AI_RobotCar::AI_RobotCar(
    int pin1_A, 
    int pin1_B, 
    int pin1_EN, 
    int pin2_A, 
    int pin2_B, 
    int pin2_EN
    ) : 
    _mL(pin1_A,pin1_B,pin1_EN), 
    _mR(pin2_A,pin2_B,pin2_EN){
}

String AI_RobotCar::getName(){
  return _name;
}

void AI_RobotCar::setDir(int dirL, int dirR){
  
}

void AI_RobotCar::setSpeed(int speedL, int speedR){
  
}

void AI_RobotCar::control(int X,int Y){
  
  /*
   * map _speed from Y Axis
   * -100-0 reverse
   * 0  stop
   * 0-100 forward
   */
  
  int X0 = 591;
  int Y0 = 580;
  //_th 30
  
  if(Y<Y0-_th){
    _speed = map(Y,Y0-_th,0,0,-100);
  }
  if(Y>=(Y0-_th) && Y<(Y0+_th)){
    _speed = 0;
  }
  if(Y>=Y0+_th){
    _speed = map(Y,Y0+_th,1023,0,100);
  }

  /*
   * map X Axis to direction
   * a) rotate Left
   * b) turn Left
   * c) Straight
   * d) turn Right
   * e) rotate Right
   */
   
  if(X<_th){
    //rotate Left
    _dirL=1;
    _dirR=0;
    _speedL = 50;
    _speedR = 50;
  }
  if(X>_th && X<X0-_th){
    //turn Left
    _dirL=1;
    _dirR=1;
    int x = map(X,X0-_th,_th,0,90);
    _speedL=abs(_speed)-x;
    _speedR=abs(_speed);
  }
  if(X>=X0-_th && X<X0+_th){
    //Straight
    _dirL=1;
    _dirR=1;
    _speedL=abs(_speed);
    _speedR=abs(_speed);
  }
  if(X>=X0+_th && X<1023-_th){
    //turn Right
    int x = map(X,X0+_th,1023-_th,0,90);
    _dirL=1;
    _dirR=1;
    _speedL=abs(_speed);
    _speedR=abs(_speed)-x;
    
  }
  if(X>1023-_th){
    //rotate Right
    _dirL=0;;
    _dirR=1;
    _speedL=50;
    _speedR=50;
  }

  /*
   * speed < 0
   * reverse the direction by inverse _dir=!_dir;
   * and abs(_speedL) and abs(_speedR)
   * 
   */
  if(_speed<0){
    _dirL=!_dirL;
    _dirR=!_dirR;
    _speedL=abs(_speedL);
    _speedR=abs(_speedR);
    //Serial.println("Speed negative : " + String(_speed));
  }
  
  _mL.setDir(_dirL);
  _mR.setDir(_dirR);
  _mL.setSpeed(_speedL);
  _mR.setSpeed(_speedR);

}
