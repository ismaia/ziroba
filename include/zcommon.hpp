#ifndef __ZCOMMON__
#define __ZCOMMON__

#include <vector>
#include <string>
#include <mraa.hpp>
#include "zmotion.hpp"

using namespace std;



struct ZCmd {
   int  device;
   int  action;
   int  value;
};

struct ZiroRobot {
      std::vector<mraa::Gpio *>     gpioVec;
      std::vector<mraa::Pwm  *>     pwmVec;
      std::vector<DCMotor *>  dcMotorVec;
      int  port;
      bool running;
      bool enDevs;
};

extern ZiroRobot zbot;

void Tokenize(const string& str,
              vector<string>& tokens,
              const std::string& delimiters = " ");


/**
 * Protocol:
 * Android_ResID:cmd:value
 */
int decodeCmd(const char *cmd, ZCmd & zcmd);


void listPlatformPins();


#endif
