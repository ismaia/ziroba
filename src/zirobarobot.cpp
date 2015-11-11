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
	statusLED->write(0);
}


void ZirobaRobot::executeCmd(ZNetCmd & zcmd) {
	//local copies
	int dev     = zcmd.device;
	int act     = zcmd.action;
  float value = zcmd.value;
  DCMotor * dcMotor = NULL;
	static unsigned int sleep = 1000;

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
				usleep((useconds_t)sleep);
				if (zargs.debug) std::cout << "setduty:" << value << std::endl;
				break;
		case SET_DIR:
				dcMotor->setDir(value);
				usleep((useconds_t)sleep);
				if (zargs.debug) std::cout << "setdir:" << value << std::endl;
				break;
		case STOP:
				dcMotor->disable();
				usleep((useconds_t)sleep);
		  	break;
		case TOGGLE_DIR:
				dcMotor->toggleDir();
				usleep((useconds_t)sleep);
		    break;

		default:
		    dcMotor1->disable();
				dcMotor2->disable();
				usleep((useconds_t)sleep);		    
		    break;
	}
}
