#include "zmotion.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <errno.h>
#include <time.h>


DCMotor::DCMotor(mraa::Pwm * pwm, mraa::Gpio *gpio)
	 :pwm(pwm),
		gpio(gpio),
		gpioVal(0)
 {
		 if (pwm == NULL) {
				 std::cerr << "Can't open PWM!" << std::endl;
				 exit(1);
		 }
		 pwm->write(0.0f); //duty = 100%

		 if (gpio == NULL) {
				 std::cerr << "Can't open GPIO!" << std::endl;
				 exit(1);
		 }
		 gpio->dir(mraa::DIR_OUT);
}


void DCMotor::setDuty(float duty) {
		 pwm->write(duty);
}
void  DCMotor::setDir(int dir) {
	   gpio->write(dir);
}

void DCMotor::stop() {
		 pwm->write( 0.0f );
}

void DCMotor::enable() {
		 pwm->enable(true);
}

void DCMotor::disable() {
		 pwm->enable(false);
}

void DCMotor::toggleDir() {
		 gpioVal = !gpioVal;
		 gpio->write((int)gpioVal);
}

DCMotor::~DCMotor() {
		delete pwm;
		delete gpio;
}
