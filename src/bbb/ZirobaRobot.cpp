#include "ZirobaRobot.h"
#include <iostream>
#include "BlackLib.h" 
#include <unistd.h>

typedef struct robotDevices {
    BlackGPIO  *m1En;
    BlackGPIO  *m1I1;
    BlackGPIO  *m1I2;
    BlackGPIO  *m2En;
    BlackGPIO  *m2I1;
    BlackGPIO  *m2I2;
    BlackPWM   *pwm1; //motor 1 enable
    BlackPWM   *pwm2; //motor 2 enable
}robotDevices;

static robotDevices rDevs;


ZirobaRobot::ZirobaRobot(bool debug, bool usePWM, bool useRadar) {
  static bool once = false;
  this->usePWM = usePWM;
  this->useRadar = useRadar;

  if (debug)
      std::cout << "Initializing Ziroba Robot..." << std::endl;

  if (!once) {
      once = true;
      if (!usePWM) {
        rDevs.m1En  = new BlackGPIO(GPIO_20,output); //chip enable              
        rDevs.m2En  = new BlackGPIO(GPIO_49,output);
      }else {
        rDevs.pwm1  = new BlackPWM(EHRPWM1A);
        rDevs.pwm2  = new BlackPWM(EHRPWM1B);
      }
      
      rDevs.m1I1  = new BlackGPIO(GPIO_68,output); //H bridge: input logic 1  
      rDevs.m1I2  = new BlackGPIO(GPIO_44,output); //H bridge: input logic 2  
      rDevs.m2I1  = new BlackGPIO(GPIO_46,output);
      rDevs.m2I2  = new BlackGPIO(GPIO_65,output);

      sleep(2);
      if (!usePWM) {
        rDevs.m1En->setValue(high);
        rDevs.m2En->setValue(high);
      }else {
        rDevs.pwm1->setRunState(pwm_value::stop);
        rDevs.pwm2->setRunState(pwm_value::stop);
        rDevs.pwm1->setPolarity(reverse);
        rDevs.pwm2->setPolarity(reverse);
        rDevs.pwm1->setPeriodTime(5000000); //5ms
        rDevs.pwm2->setPeriodTime(5000000);
      }

      rDevs.m1I1->setValue(low);
      rDevs.m1I2->setValue(low);
      rDevs.m2I1->setValue(low);
      rDevs.m2I2->setValue(low);

      speed = 100;

      sleep(1);
  }               
  if (debug)
      std::cout << "ready!" << std::endl;
}

ZirobaRobot::~ZirobaRobot() {
  
  if (!usePWM){
    delete  rDevs.m1En;
    delete  rDevs.m2En;
  }else {
    delete rDevs.pwm1;
    delete rDevs.pwm2;
  }

  delete  rDevs.m1I1;
  delete  rDevs.m1I2;
  delete  rDevs.m2I1;
  delete  rDevs.m2I2;
}

void ZirobaRobot::turnLeft() {
  if (!usePWM){
    rDevs.m1En->setValue(high);
    rDevs.m2En->setValue(high);
  }else {
    rDevs.pwm1->setRunState(pwm_value::run);
    rDevs.pwm2->setRunState(pwm_value::run);
    rDevs.pwm1->setDutyPercent(speed);
    rDevs.pwm2->setDutyPercent(speed);
  }
  rDevs.m1I1->setValue(low);
  rDevs.m1I2->setValue(high);
  rDevs.m2I1->setValue(high);
  rDevs.m2I2->setValue(low);
}

void ZirobaRobot::turnRight() {
  if (!usePWM){
    rDevs.m1En->setValue(high);
    rDevs.m2En->setValue(high);
  }else {
    rDevs.pwm1->setRunState(pwm_value::run);
    rDevs.pwm2->setRunState(pwm_value::run);
    rDevs.pwm1->setDutyPercent(speed);
    rDevs.pwm2->setDutyPercent(speed);
  }

  rDevs.m1I1->setValue(high);
  rDevs.m1I2->setValue(low);
  rDevs.m2I1->setValue(low);
  rDevs.m2I2->setValue(high);
}

void ZirobaRobot::moveForward() {
  if (!usePWM){
    rDevs.m1En->setValue(high);
    rDevs.m2En->setValue(high);
  }else {
    rDevs.pwm1->setRunState(pwm_value::run);
    rDevs.pwm2->setRunState(pwm_value::run);
    rDevs.pwm1->setDutyPercent(speed);
    rDevs.pwm2->setDutyPercent(speed);
  }

  rDevs.m1I1->setValue(high);
  rDevs.m1I2->setValue(low);
  rDevs.m2I1->setValue(high);
  rDevs.m2I2->setValue(low);
}

void ZirobaRobot::moveBackward() {
  if (!usePWM){
    rDevs.m1En->setValue(high);
    rDevs.m2En->setValue(high);
  }else {
    rDevs.pwm1->setRunState(pwm_value::run);
    rDevs.pwm2->setRunState(pwm_value::run);
    rDevs.pwm1->setDutyPercent(speed);
    rDevs.pwm2->setDutyPercent(speed);
  }

  rDevs.m1I1->setValue(low);
  rDevs.m1I2->setValue(high);
  rDevs.m2I1->setValue(low);
  rDevs.m2I2->setValue(high);
}

void ZirobaRobot::stop() {
  if (!usePWM){
    rDevs.m1En->setValue(low);
    rDevs.m2En->setValue(low);
  }else {
    rDevs.pwm1->setRunState(pwm_value::stop);
    rDevs.pwm2->setRunState(pwm_value::stop);
  }
}

void ZirobaRobot::setSpeed(float s) {
  if (usePWM){
    speed = s;
    rDevs.pwm1->setDutyPercent(speed);
    rDevs.pwm2->setDutyPercent(speed);
  }
}


void ZirobaRobot::incSpeed() {
  if (usePWM){
    speed += 0.5f;
    rDevs.pwm1->setDutyPercent(speed);
    rDevs.pwm2->setDutyPercent(speed);
  }
}

void ZirobaRobot::decSpeed() {
  if (usePWM){
    speed -= 0.5f;
    rDevs.pwm1->setDutyPercent(speed);
    rDevs.pwm2->setDutyPercent(speed);
  }
}

