#include "zmotion.hpp"
#include <iostream>

DCMotor::DCMotor(int pwmPin, int gpioPin)
   :ppin(pwmPin),
    gpin(gpioPin)
 {

     pwm  = new mraa::Pwm( pwmPin );

     if (pwm == NULL) {
         std::cerr << "Can't open PWM pin :" <<  pwmPin << std::endl;
         exit(1);
     }
         
     gpio = new mraa::Gpio( gpioPin );
     if (gpio == NULL) {
         std::cerr << "Can't open GPIO pin :" << gpioPin << std::endl;
         exit(1);
     }
}

DCMotor::~DCMotor() {
}

void DCMotor::stop() {
}
