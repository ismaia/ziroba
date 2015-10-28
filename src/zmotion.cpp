#include "zmotion.hpp"
#include <iostream>

DCMotor::DCMotor(int pwmPin, int gpioPin) {

    pwm  = mraa_pwm_init( pwmPin );

    if (pwm == NULL) {
        std::cerr << "Can't open PWM pin :" <<  pwmPin << std::endl;
        exit(1);
    }

    gpio = mraa_gpio_init( gpioPin );
    if (gpio == NULL) {
        std::cerr << "Can't open GPIO pin :" << gpioPin << std::endl;
        exit(1);
    }
}

DCMotor::~DCMotor() {
}

void DCMotor::stop() {
}
