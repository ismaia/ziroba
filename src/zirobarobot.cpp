#include "zirobarobot.hpp"
#include <iostream>


ZirobaRobot zbot;


ZirobaRobot::ZirobaRobot() {
	running = false;

}


void ZirobaRobot::start() {
	running = true;
  if (zargs.enableDevs) {
      if (zargs.pwmVec.size() >= 2 && zargs.gpioVec.size() >= 2) {
         zbot.initDCMotor1(zargs.pwmVec[0], zargs.gpioVec[0]);
         zbot.initDCMotor2(zargs.pwmVec[1], zargs.gpioVec[1]);
         zbot.dcMotor1->setDuty(0.0f);
         zbot.dcMotor2->setDuty(0.0f);
       }
  }
}


void ZirobaRobot::stop() {
	running = false;
}

void ZirobaRobot::initDCMotor1(mraa::Pwm *pwm, mraa::Gpio *gpio) {
  dcMotor1 = new DCMotor(pwm, gpio);
	
}

void ZirobaRobot::initDCMotor2(mraa::Pwm *pwm, mraa::Gpio *gpio) {
  dcMotor2 = new DCMotor(pwm, gpio);
}


void ZirobaRobot::executeCmd(ZNetCmd & zcmd) {
  float duty = 0.0f;
  DCMotor * dcMotor = NULL;

  //select device
  switch (zcmd.device) {
      case DCMOTOR1:
        dcMotor = dcMotor1;
        break;
      case DCMOTOR2:
        dcMotor = dcMotor2;
        break;
      default:
        break;
    }


   switch (zcmd.action) {
     case SET_DUTY:
         duty = (float)zcmd.value/100.0f;
         dcMotor->setDuty(duty);
         if (zargs.debug) std::cout << "setduty:" << duty << std::endl;
        break;
     case SET_DIR:
         dcMotor->setDir(zcmd.value);
         if (zargs.debug) std::cout << "setdir:" << zcmd.value << std::endl;
        break;
     case STOP:
         dcMotor->stop();
     default:
        break;
   }
}
