#ifndef ZMOTOR_H
#define ZMOTOR_H
namespace zb {
    class Motor {
       Motor();
       moveForward();
       moveBackward();
       virtual rotate(float angle);
       virtual incSpeed();
       virtual decSpeed();
       virtual setSpeed();

    };

    class Servo : public Motor {
    };
}
#endif
