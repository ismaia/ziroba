#ifndef __ZIROBAROBOT__
#define __ZIROBAROBOT__

#include "zmotion.hpp"
#include "znet.hpp"


class ZirobaRobot {
  public:
    ZirobaRobot();
    void start();
    void stop();
    bool isRunning() { return running; }

  private:
    DCMotor *dcMotor1;
    DCMotor *dcMotor2;
    bool     running;
};
extern ZirobaRobot zbot;


#endif
