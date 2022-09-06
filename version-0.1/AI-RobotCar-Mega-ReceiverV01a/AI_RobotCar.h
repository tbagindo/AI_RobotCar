#ifndef AI_ROBOTCAR_H
#define AI_ROBOTCAR_H
#include <Arduino.h>

class AI_DCMotor{
  private:
  byte _pinA;
  byte _pinB;
  byte _pinEN;
  String _name;
  public:
  AI_DCMotor(byte pinA, byte pinB, byte pinEN);
  AI_DCMotor(byte pinA, byte pinB, byte pinEN, String name);
  void init();
  void setDir(byte DIR);
  void setSpeed(byte speed);
  String getName();
};

class AI_RobotCar{
  private:
  AI_DCMotor _mL;
  AI_DCMotor _mR;
  String _name;
  int _speed;
  int _speedL;
  int _speedR;
  int _dirL;
  int _dirR;
  int _th =80;
  
  public:
  AI_RobotCar(
    int pin1_A, 
    int pin1_B, 
    int pin1_EN, 
    int pin2_A, 
    int pin2_B, 
    int pin2_EN, 
    String name
    );// : mL(pin1_A,pin1_B,pin1_EN), mR(pin2_A,pin2_B,pin2_EN);
  String getName();
  void setDir(int dirL, int dirR);
  void setSpeed(int speedL, int speedR);
  void control(int X,int Y);
};
#endif
