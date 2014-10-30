/**
 * L2Cap Server for command mensages 
 * Isaac Maia
 */


#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/l2cap.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <ZirobaRobot.h>



#define BUFF_SZ 32 

//Bluetooth Server 
class BtServer {
    public:
        BtServer();
        ~BtServer(); 
        int receiveMsg();
        std::string & getMsg() { return recvMsg; }
        void setDebug(bool d) { debug = d; }
    private:
        struct sockaddr_l2 locAddr; //local Addr
        struct sockaddr_l2 remAddr; //remote Addr
        int                locSokt; //Local Socket
        int                remSokt; //remote socket
        socklen_t          opt; 
        std::string        recvMsg; //received msg
        bool               debug;
};

BtServer::BtServer() {
    debug = false;

    locSokt = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);
    
    bdaddr_t tmp = {};
    bacpy(&locAddr.l2_bdaddr  , &tmp);

    // bind socket to port 0x1001 of the first available bluetooth adapter
    locAddr.l2_family      = AF_BLUETOOTH;
//    locAddr.l2_bdaddr      = *BDADDR_ANY;
    locAddr.l2_psm         = htobs(0x1001);
    locAddr.l2_cid         = 0;
    locAddr.l2_bdaddr_type = 0;
    
    bind(locSokt, (struct sockaddr *)&locAddr, sizeof(locAddr));
    std::cout << "listening connections..." << std::endl;

    //put local socket into listening mode
    listen(locSokt, 1);
    
    socklen_t opt = sizeof(remAddr);
    
    // accept one connection
    remSokt = accept(locSokt, (struct sockaddr *)&remAddr, &opt);    

    char strAddr[32];
    //convert address to string
    ba2str( &remAddr.l2_bdaddr, strAddr );
    std::cout << "Accepted Connection from " << strAddr << std::endl;
}

BtServer::~BtServer() {
    close(remSokt);
    close(locSokt);
}

int BtServer::receiveMsg() {
    char buf[BUFF_SZ];
    int  bytes = 0;
    recvMsg.clear();

    bytes = recv(remSokt, buf, BUFF_SZ, 0);
    recvMsg = buf;   
    if( debug && bytes > 0 ) {
        std::cout << "received [" << recvMsg << "]" << std::endl;
    }
    
    return bytes;
}

int main(int argc, char **argv)
{
    BtServer btServer;
    btServer.setDebug(false);

    ZirobaRobot zRobot(0,0);

    char cmd[BUFF_SZ];
    std::cout << "Receiving..." << std::endl;

    while ( btServer.receiveMsg() > 0) {
        btServer.getMsg().copy(cmd,2); 
        
        switch (cmd[0]) {
          case 'f':
              zRobot.moveForward();
              break;
          case 'b':
              zRobot.moveBackward();
              break;
          case 'l':
              zRobot.turnLeft();
              break;
          case 'r':
              zRobot.turnRight();
              break;
          case 's':
              zRobot.stop();
              break;
         }
    }

    return 0;
}



