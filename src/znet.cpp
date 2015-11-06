#include "znet.hpp"
#include "zcommon.hpp"
#include <iostream>
#include <string.h>

static size_t buff_bytes;

sf::SocketSelector netMonitor;

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


ZCommandService::ZCommandService(int port, size_t buff_size)
    :listener(),
      socket(),
      port(port),
      buff_size(buff_size),
      recv_bytes(0),
      buff(new char[buff_size])
{
    buff_bytes = buff_size*sizeof(char);
    listener.setBlocking(false);
    socket.setBlocking(false);
}

ZCommandService::~ZCommandService() {
    delete buff;
}

bool ZCommandService::isReady()
{
    return netMonitor.isReady(socket);
}


bool ZCommandService::listenAndConnect() {
    if (listener.listen(port) == sf::Socket::Done) {
        std::cout << "listening on port:" << port << std::endl;
    }else exit(EXIT_FAILURE);

    netMonitor.add(listener);
    while (1) {
        netMonitor.wait();
        if (netMonitor.isReady(listener))  {
            if (listener.accept(socket)  == sf::Socket::Done) {
                netMonitor.add(socket);
                return true;
            }else {
                std::cerr << "Can't accept connection at port " << port << std::endl;
                exit(EXIT_FAILURE);
            }
        }
    }
}


void ZCommandService::clearBuff() {
    memset(buff, 0 , buff_bytes);
}

bool ZCommandService::sendBuff()
{
    sf::Socket::Status status;
    status = socket.send(buff,buff_size);
    return (status == sf::Socket::Done);
}

bool ZCommandService::recvBuff()
{
    sf::Socket::Status status;
    status = socket.receive(buff, buff_bytes, recv_bytes);
    return (status == sf::Socket::Done);
}

char * ZCommandService::getBuff()
{
    return buff;
}

void ZCommandService::wait()
{
    netMonitor.add(socket);
    netMonitor.wait();
}

int ZCommandService::decodeCmd(const char *cmd, ZNetCmd & zcmd) {
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
       if (zargs.debug) {
           std::cout << "device:"  << zcmd.device << "," <<
                        "action:"  << zcmd.action << "," <<
                        "value:"   << zcmd.value << std::endl;
       }
   }
   return -1;
}
