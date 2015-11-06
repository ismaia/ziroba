#include "zmotion.hpp"
#include <iostream>
#include <sstream>
#include <string>


DCMotor::DCMotor(mraa::Pwm * pwm, mraa::Gpio *gpio)
   :pwm(pwm),
    gpio(gpio),
    gpioVal(0)
 {
     if (pwm == NULL) {
         std::cerr << "Can't open PWM!" << std::endl;
         exit(1);
     }
     //pwm->percent
     pwm->period_us(1000);
     pwm->enable(1);

     if (gpio == NULL) {
         std::cerr << "Can't open GPIO!" << std::endl;
         exit(1);
     }
     gpio->dir(mraa::DIR_OUT);
}

void DCMotor::setSpeed(int duty) {
     pwm->enable(true);
     pwm->config_percent( period, duty );
}

void DCMotor::stop() {
     pwm->config_percent( period, 0 );
}

void DCMotor::toggleDir() {
     gpioVal = !gpioVal;
     gpio->write((int)gpioVal);
}

DCMotor::~DCMotor() {
    delete pwm;
    delete gpio;
}
