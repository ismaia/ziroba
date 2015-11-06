#ifndef __ZMOTION__
#define __ZMOTION__

#include "mraa.hpp"


class DCMotor {
    public:
       DCMotor(mraa::Pwm * pwm, mraa::Gpio *gpio);
       ~DCMotor();
       void setSpeed(int duty);
       void toggleDir();
       void stop();


    private:
       //dc motor 1
       mraa::Pwm          *pwm;
       int                period;
       int                duty;
       mraa::Gpio         *gpio;
       bool               gpioVal;

};

#endif
