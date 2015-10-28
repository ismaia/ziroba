#ifndef __ZMOTION__
#define __ZMOTION__

#include "mraa/gpio.h"
#include "mraa/pwm.h"


class DCMotor {
    public:
       DCMotor(int pwmPin, int gpioPin);
       ~DCMotor();

       /**
        * Stops the motor
        */
       void stop();

       /**
        * Sets the motor's speed
        */
       void setSpeed(float speed);

       /**
        * Increases motor's speed
        */
       void speedUp();

       /**
        * Decreases motor's speed
        */
       void speedDown();

       /**
        * Sets the motor's direction
        */
       void setDirection();

       void toggleDirection();

       void moveForward();
       void moveBackward();

    private:
       //dc motor 1
       mraa_pwm_context   pwm;
       int                ppin;

       mraa_gpio_context  gpio;
       int                gpin;

};

#endif
