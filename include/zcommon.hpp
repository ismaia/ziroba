#ifndef __ZCOMMON__
#define __ZCOMMON__

#include <vector>
#include <string>

using namespace std;


// /**
//  * Protocol:
//  * Android's ResourceID:cmd:value
//  */
// enum zcmds {  CMD_DCMOT1 = 2131624015,
//               CMD_DCMOT2 = 2131624016      };
//

struct ZCmd {
   int  device;
   int  action;
   int  value;
};

struct ZiroRobot {
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


#endif
