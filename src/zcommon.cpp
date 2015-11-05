#include "zcommon.hpp"
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <map>

ZiroRobot zbot = { -1  , false , true };

//Android Resource Map [ResName, LocalID]
static std::map<std::string,int> androidResMap {
   { "skb1", 1 },  //seekbar1
   { "skb2", 2 },  //seekbar2
   { "but1", 3 }   //buttomA
 };


static std::map<std::string,int> actionMap {
   { "setduty"  , 0 },
   { "stop"     , 1 },
   { "setdir"   , 2 },
   { "toggledir", 3 }
};

void Tokenize(const string& str,
                      vector<string>& tokens,
                      const string& delimiters)
{
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}

int decodeCmd(const char *cmd, ZCmd & zcmd) {
   std::string strCmd(cmd);
   std::vector<std::string> cmdTokens;
   //std::cout << cmd << std::endl;

   Tokenize(strCmd, cmdTokens, ":");

   if (cmdTokens.size() >= 3) {
       std::string resName = cmdTokens[0];
       int action   = actionMap[ cmdTokens[1] ];
       int value    = std::atoi(cmdTokens[2].c_str());

       zcmd.device  = androidResMap[resName];
       zcmd.action  = action;
       zcmd.value   = value;
       cout << "resID:"  << zcmd.device << "," <<
               "action:" << zcmd.action << "," <<
               "value:"  << zcmd.value << std::endl;
   }
}
