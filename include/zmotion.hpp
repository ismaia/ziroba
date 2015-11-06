#ifndef __ZMOTION__
#define __ZMOTION__

#include "mraa.hpp"


class DCMotor {
    public:
       DCMotor(mraa::Pwm * pwm, mraa::Gpio *gpio);
       ~DCMotor();
       void setDuty(float duty);
       void setDir(int dir);
       void toggleDir();
       void stop();
       void disablePwm();
       void enablePwm();
    private:
       //dc motor 1
       mraa::Pwm          *pwm;
       mraa::Gpio         *gpio;
       bool               gpioVal;

};

#endif
