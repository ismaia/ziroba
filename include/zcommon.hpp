#ifndef __ZCOMMON__
#define __ZCOMMON__

#include <vector>
#include <map>
#include <string>
#include <mraa.hpp>
#include "zmotion.hpp"

using namespace std;


struct ZSysArgs {
  int  port;
  bool enableDevs;
  bool debug;
  std::vector<mraa::Gpio *> gpioVec;
  std::vector<mraa::Pwm *> pwmVec;
};
extern ZSysArgs zargs;

//Nerwork Command Format: device:action:value
struct ZNetCmd {
       int  device;
       int  action;
       int  value;
};

extern std::map<std::string,int> actionMap;

void listPlatformPins();

void Tokenize(const string& str,
                      vector<string>& tokens,
                      const string& delimiters);

void parse_args(int argc, char **argv);


#endif
