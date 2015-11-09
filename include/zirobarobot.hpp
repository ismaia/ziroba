#ifndef __ZIROBAROBOT__
#define __ZIROBAROBOT__

#include "zcommon.hpp"


enum ZDevice {
   DCMOTOR1 = 0,
   DCMOTOR2,
   CAMERA
};

extern std::map<std::string,int> actionMap;


class ZirobaRobot {
  public:
    ZirobaRobot();
    void start();
    void stop();
    bool isRunning() { return running; }

    DCMotor *dcMotor1;
    DCMotor *dcMotor2;
    mraa::Gpio * statusLED;
    bool     running;
    void executeCmd(ZNetCmd & zcmd);
};
extern ZirobaRobot zbot;




#endif
