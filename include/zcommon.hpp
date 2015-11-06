#ifndef __ZCOMMON__
#define __ZCOMMON__

#include <vector>
#include <string>
#include <mraa.hpp>
#include "zmotion.hpp"

using namespace std;


struct ZSysArgs {
  int  port;
  bool enableDevs;
  bool debug;
};
extern ZSysArgs zargs;


/**
 * Protocol:
 * Android_ResID:cmd:value
 */



void listPlatformPins();

void Tokenize(const string& str,
                      vector<string>& tokens,
                      const string& delimiters);


#endif
