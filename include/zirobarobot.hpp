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
    void initDCMotor1(mraa::Pwm *pwm, mraa::Gpio *gpio);
    void initDCMotor2(mraa::Pwm *pwm, mraa::Gpio *gpio);
    DCMotor *dcMotor1;
    DCMotor *dcMotor2;
    bool     running;
    void executeCmd(ZNetCmd & zcmd);
};
extern ZirobaRobot zbot;




#endif
