#include "zmotion.hpp"
#include <iostream>
#include <sstream>
#include <string>



DCMotor::DCMotor(int pwmPin, int gpioPin)
   :period(0),
    duty(0),
    gpioVal(0)
 {

     pwm  = new mraa::Pwm( pwmPin );
     if (pwm == NULL) {
         std::cerr << "Can't open PWM pin :" <<  pwmPin << std::endl;
         exit(1);
     }
     pwm->enable(true);
     period = pwm->max_period();
     pwm->period_ms(period);


     gpio = new mraa::Gpio( gpioPin );
     if (gpio == NULL) {
         std::cerr << "Can't open GPIO pin :" << gpioPin << std::endl;
         exit(1);
     }
     gpio->dir(mraa::DIR_OUT);
}

void DCMotor::setSpeed(int duty) {
     pwm->enable(true);
     pwm->config_percent( period, duty );
}

void DCMotor::stop() {
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



void parseAndExecCommand(const char * cmd) {
   std::string str(cmd);
   size_t pos = str.find("bar1");
   if (pos != std::string::npos) {
     std::cout << str.substr(pos+2) << std::endl;
   }

}
