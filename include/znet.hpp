#ifndef __ZNET_H__
#define __ZNET_H__
#include <SFML/Network.hpp>
#include "zcommon.hpp"


//Nerwork Command Format: device:action:value
struct ZNetCmd {
       int  device;
       int  action;
       int  value;
};


//TCP Server
class ZCommandService {
    public:
        ZCommandService(int port, size_t buff_size = 128);
        ~ZCommandService();
        bool            isReady();
        bool            listenAndConnect();
        void            clearBuff();
        bool            sendBuff();
        bool            recvBuff();
        char *          getBuff();
        void            wait();
        int             decodeCmd(const char *cmd, ZNetCmd & zcmd);
    private:
        sf::TcpListener   listener;
        sf::TcpSocket     socket;
        int               port;
        size_t            buff_size;
        size_t            recv_bytes;
        char *            buff;
};

//UDP Server
class ZVideoService {

};



#endif
