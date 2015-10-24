#ifndef __ZMOTION__
#define __ZMOTION__

#include "mraa/gpio.h"


class DCMotor {
    public:
       DCMotor();
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
       void setDirection( );
       void moveForward();
       void moveBackward();

};

#endif
