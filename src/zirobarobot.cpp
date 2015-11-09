#include "zirobarobot.hpp"
#include <iostream>

ZirobaRobot zbot;


ZirobaRobot::ZirobaRobot() {
	running = false;
}


void ZirobaRobot::start() {

  if (zargs.enableDevs) {
      if (zargs.pwmVec.size() >= 2 && zargs.gpioVec.size() >= 3) {
				 dcMotor1 = new DCMotor(zargs.pwmVec[0], zargs.gpioVec[0]);
				 dcMotor2 = new DCMotor(zargs.pwmVec[1], zargs.gpioVec[1]);

         zbot.dcMotor1->setDuty(0.0f);
				 zbot.dcMotor1->enable();
         zbot.dcMotor2->setDuty(0.0f);
				 zbot.dcMotor2->enable();

				 //status led
				 statusLED = zargs.gpioVec[2];
				 statusLED->dir(mraa::DIR_OUT);
				 statusLED->write(1);
       }
  }
	running = true;
}


void ZirobaRobot::stop() {
	running = false;
}


void ZirobaRobot::executeCmd(ZNetCmd & zcmd) {
	//local copies
	int dev     = zcmd.device;
	int act     = zcmd.action;
  float value = zcmd.value;
  DCMotor * dcMotor = NULL;

	// //select device
	switch (dev) {
		case DCMOTOR1:
				dcMotor = dcMotor1;
				break;
		case DCMOTOR2:
				dcMotor = dcMotor2;
				break;
		default:
		    break;
	}

	switch (act) {
		case SET_DUTY:
				value = (float)value/100.0f;
				dcMotor->setDuty(value);
				usleep(10000);
				if (zargs.debug) std::cout << "setduty:" << value << std::endl;
				break;
		case SET_DIR:
				dcMotor->setDir(value);
				usleep(10000);
				if (zargs.debug) std::cout << "setdir:" << value << std::endl;
				break;
		case STOP:
				dcMotor->stop();
				usleep(10000);
		  	break;
		default:
		break;
	}
}
