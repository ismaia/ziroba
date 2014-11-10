//*****************************************************
//Ziroba Robot Joystick Client
//This cliet communicates via Bluetooth l2cap protocol
//
//By Isaac Maia
//Universidade Federal da Paraiba - UFPB
//Departamento de Eng. Elétrica
//Sep/2014
//*****************************************************


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <fcntl.h> 
#include <linux/input.h>
#include <linux/joystick.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/l2cap.h>

#include <ZRobot.h>
#include <sys/socket.h>
#include <iomanip>


//------------------------------- ZirobaJoystick ----------------------------
typedef struct js_event JSEvent;
enum js_action {
    UP_REL     =  0,
    UP_PRESS   =  1,                
    RIGHT_REL  =  2,                
    RIGHT_PRESS=  3,                
    DOWN_REL   =  4,                
    DOWN_PRESS =  5,                
    LEFT_REL   =  6,                
    LEFT_PRESS =  7                
};


class ZirobaJoystick {
  public:
      ZirobaJoystick();
      ~ZirobaJoystick();
      void setLeftCmd(std::string & cmd);
      void setRightCmd(std::string & cmd);
      void readState();
      JSEvent & getEvent() { return ev; }
      js_action isButtonPressed() {
             return (js_action)(2*ev.number + ev.value);
             //   ev.number == 0 && ev.value == 0 UP_REL        0  
             //   ev.number == 0 && ev.value == 1 UP_PRESS      1
             //   ev.number == 1 && ev.value == 0 RIGHT_REL     2
             //   ev.number == 1 && ev.value == 1 RIGHT_PRESS   3
             //   ev.number == 2 && ev.value == 0 DOWN_REL      4
             //   ev.number == 2 && ev.value == 1 DOWN_PRESS    5
             //   ev.number == 3 && ev.value == 0 LEFT_REL      6
             //   ev.number == 3 && ev.value == 1 LEFT_PRESS    7
       }
  private:
     JSEvent ev;
     int     fd;
};

ZirobaJoystick::ZirobaJoystick() {
    if ((fd = open("/dev/input/js0", O_RDONLY)) < 0) {
            perror("Can't open joystick device /dev/input/js0");
            exit(0);
    }
}

ZirobaJoystick::~ZirobaJoystick() {
    close(fd);    
}

void ZirobaJoystick::readState() {
    if (read(fd, &ev, sizeof(struct js_event)) != sizeof(struct js_event)) {
           perror("\nError reading joystick");
    }
}
//------------------------------- ZirobaJoystick -----------------------------




//------------------------------- ZirobaJoystickClient ------------------------

#define BUFF_SZ 32
//bluetooth joystick client
class ZirobaBtJoystickClient {
    public:
        ZirobaBtJoystickClient(const char * dest);
        ~ZirobaBtJoystickClient();
        void sendCmd(const char * cmd);
    private:
        struct sockaddr_l2 addr;        
        int    sokt; 
};

ZirobaBtJoystickClient::ZirobaBtJoystickClient(const char * dest) {
    sokt = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);

    // set the connection parameters (who to connect to)
    addr.l2_family     = AF_BLUETOOTH;
    addr.l2_psm        = htobs(0x1001);
    addr.l2_cid        = 0;
    addr.l2_bdaddr_type= 0;

    //convert string to address
    str2ba( dest , &addr.l2_bdaddr );

    std::cout << "server addr:" << dest << std::endl;

    if ( connect(sokt, (struct sockaddr *)&addr, sizeof(addr)) < 0) {        
        perror("Can't connect to server");
        exit(1);
    }
}
ZirobaBtJoystickClient::~ZirobaBtJoystickClient() {
    close(sokt);
}


void ZirobaBtJoystickClient::sendCmd(const char * cmd) {
      if ( send(sokt, cmd ,  BUFF_SZ , 0) < 0 ) {
          perror("Can't send msg to server");
      }
}

//------------------------------- ZirobaJoystickClient ------------------------





//--------------------------------------- MAIN --------------------------------

using namespace std;

int main(int argc, char **argv)
{
    ZirobaJoystick joystick;

    std::string addr;
    if (argc>1) addr = argv[1];
    else addr = "00:15:83:3D:0A:57";
    
    ZirobaBtJoystickClient btClient(addr.c_str());

    cout << "Client connected!" << endl;

    char cmd[BUFF_SZ];
    memset(cmd,0,BUFF_SZ);

    while ( 1 ) {
        joystick.readState();
        memset(cmd,0,BUFF_SZ);
        switch ((int)joystick.isButtonPressed()) {
            case UP_REL     :
                sprintf(cmd,"%s","s");
                break;
            case UP_PRESS   :
                sprintf(cmd,"%s","f");
                break;
            case RIGHT_REL  :     
                sprintf(cmd,"%s","s");
                break;
            case RIGHT_PRESS:
                sprintf(cmd,"%s","r");
                break;
            case DOWN_REL   :
                sprintf(cmd,"%s","s");
                break;
            case DOWN_PRESS :
                sprintf(cmd,"%s","b");
                break;
            case LEFT_REL   :
                sprintf(cmd,"%s","s");
                break;
            case LEFT_PRESS :
                sprintf(cmd,"%s","l");
                break;
        }
        cout << "sending cmd:" << cmd << endl;
        btClient.sendCmd(cmd);
        fflush(stdout);
    }
}


