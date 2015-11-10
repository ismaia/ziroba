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
		gpioVal(0),
		duty(0.0f)
 {
		 if (pwm == NULL) {
				 std::cerr << "Can't open PWM!" << std::endl;
				 exit(1);
		 }
		 pwm->period_ms(1);
		 pwm->write(0.0f); //duty = 100%
		 pwm->enable(false);
		 usleep(10000);

		 if (gpio == NULL) {
				 std::cerr << "Can't open GPIO!" << std::endl;
				 exit(1);
		 }
		 gpio->dir(mraa::DIR_OUT);
}


void DCMotor::setDuty(float duty) {
	   this->duty = duty;
		 pwm->write(duty);
		 pwm->enable(true);
		 usleep(200);
}

void  DCMotor::setDir(int dir) {
	   gpioVal = dir;
		 pwm->write(duty);
	   pwm->enable(true);
		 gpio->write(dir);
		 usleep(200);
}

void DCMotor::stop() {
	   pwm->write( 0.0f );
	   pwm->enable(true);
		 usleep(200);
}

void DCMotor::enable() {
	   pwm->write(duty);
		 pwm->enable(true);
		 usleep(200);
}

void DCMotor::disable() {
	   duty = 0.0f;
		 pwm->write(duty);
		 pwm->enable(false);
		 usleep(200);
}

void DCMotor::toggleDir() {
		 gpioVal = !gpioVal;
		 gpio->write((int)gpioVal);
}

DCMotor::~DCMotor() {
		delete pwm;
		delete gpio;
}
