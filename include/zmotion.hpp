#ifndef __ZMOTION__
#define __ZMOTION__

#include "mraa.hpp"


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
       mraa::Pwm          *pwm;
       int                ppin;

       mraa::Gpio         *gpio;
       int                gpin;

};

#endif
