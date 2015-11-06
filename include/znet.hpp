#ifndef __ZNET_H__
#define __ZNET_H__
#include <SFML/Network.hpp>
#include "zcommon.hpp"



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
        int             getAction(const string & actionName);
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