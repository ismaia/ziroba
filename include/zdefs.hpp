#ifndef __ZDEFS__
#define __ZDEFS__

#include <vector>
#include <string>

using namespace std;

#define  DCMOTOR1_ID 1
#define  DCMOTOR2_ID 2

//protocol
// device:action:value
// dcmotor1:setspeed:100
enum zcmds {  CMD_TOGGLE_DIR = 0 ,
              CMD_DCMOTOR1_SET   ,
              CMD_DCMOTOR2_SET  };


struct ZiroRobot {
    int  port;
    bool running;
    bool enDevs;
};

ZiroRobot zbot = { -1  , false , true };

void Tokenize(const string& str,
              vector<string>& tokens,
              const std::string& delimiters = " ");





#endif
