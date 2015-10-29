#include <iostream>
#include <getopt.h>
#include <unistd.h>
#include <signal.h>

#include "mraa.hpp"
#include <SFML/Network.hpp>
#include "zdefs.hpp"
#include "znet.hpp"
#include "zmotion.hpp"
#include "pinmapper.hpp"


static void parse_args(int argc, char **argv);
static void signal_handler(int sig);


using namespace ziro;

int main(int argc, char ** argv) {
    parse_args(argc,argv);
    running = true;
    std::cout << "Ziroba Robot" << std::endl;


    //======================= Signals ========================================
    static struct sigaction sig_act;
    sig_act.sa_handler = &signal_handler;
    sigemptyset (&sig_act.sa_mask);
    sig_act.sa_flags   = 0;
    if (sigaction(SIGINT, &sig_act, NULL) == -1) {
      std::cerr << "cannot handle SIGINT!" << std::endl;
    }
    if (sigaction(SIGSEGV, &sig_act, NULL) == -1) {
      std::cerr << "cannot hangle SIGSEGV!" << std::endl;
    }
    //========================================================================


    //===================== Robot Device Initialization ======================
    int pwm1Pin  = PinMapper::getInstance().getPinNumber("pwm1");
    std::cout << "pwm1Pin:" << pwm1Pin << std::endl;

    int gpio1Pin = PinMapper::getInstance().getPinNumber("gpio1");
    std::cout << "gpio1Pin:" << gpio1Pin << std::endl;

    int pwm2Pin  = PinMapper::getInstance().getPinNumber("pwm2");
    std::cout << "pwm2Pin:" << pwm2Pin << std::endl;

    int gpio2Pin = PinMapper::getInstance().getPinNumber("gpio2");
    std::cout << "gpio2Pin:" << gpio2Pin << std::endl;


    DCMotor dcmotor1(pwm1Pin, gpio1Pin);
    DCMotor dcmotor2(pwm2Pin, gpio2Pin);

    //===================== Network Initialization ===========================
    int port = (zargs.port == -1) ? 8090 :  zargs.port;
    char *buff;
    ZCommandService cmdService(port);

    cmdService.listenAndConnect();
    std::cout << "Connected to port [" << port << "] for commands" << std::endl;
    //========================================================================

    while (running) {
        cmdService.wait();
        if (cmdService.isReady()) {
            cmdService.recvBuff();
            buff = cmdService.getBuff();
            std::cout << buff << std::endl;
            cmdService.clearBuff();
        }
    }

    return 0;
}


//parse command line arguments
static void
parse_args(int argc, char **argv)
{
       int opt=0;
       opterr=0;

       static struct option long_options[] = {
            {"help"    ,no_argument      , 0,  'h' },
            {"verbose" ,no_argument      , 0,  'v' },
            {"port"    ,required_argument, 0,  'p' },
            {"pins"    ,no_argument      , 0,  'l' },
            {"mapfile" ,required_argument, 0,  'm' },
            {0,0,0,0}
       };

        int long_index =0;
        int show_help  =0;

        while ((opt = getopt_long(argc, argv,"hvp:lm:",
                       long_options, &long_index )) != -1) {

            switch (opt) {
                 case 'h' :
                     show_help=1;
                     break;
                 case 'v' :
                     break;
                 case 'p' :
                     ziro::zargs.port = atoi(optarg);
                     break;
                 case 'l' :
                     PinMapper::getInstance().listPlatformPins();
                     exit(EXIT_SUCCESS);
                     break;
                 case 'm' :
                    PinMapper::getInstance().init(optarg);
                    break;

                 case '?':
                 default:
                     show_help=1;
                 break;
           }//switch
        }//while


        if (show_help) {
           std::cout <<
                "usage: ziroba [options] \n"             <<
                "options:\n"                             <<
                "-h, --help   : show this help\n"        <<
                "-v, --verbose: show verbose output\n"   <<
                "-p, --port   : TCP port for commands\n" <<
                "-l, --pins   : List Platform Pins"      << std::endl;

           exit(EXIT_FAILURE);
        }

}

static void signal_handler(int sig) {
   ziro:running = false;
   std::cout << "Ziroba Turned Off" << std::endl;
}
