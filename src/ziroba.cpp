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
static void parse_cmd(const char *cmd);
static void signal_handler(int sig);



int main(int argc, char ** argv) {
    parse_args(argc,argv);
    zbot.running = true;
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


    //===================== Robot Devices Initialization =====================
    int pwm1Pin;
    int gpio1Pin;
    int pwm2Pin;
    int gpio2Pin;


    DCMotor * dcmotor1;
    DCMotor * dcmotor2;

    if (zbot.enDevs) {
      pwm1Pin  = PinMapper::getInstance().getPinNumber("pwm1");
      gpio1Pin = PinMapper::getInstance().getPinNumber("gpio1");

      pwm2Pin  = PinMapper::getInstance().getPinNumber("pwm2");
      gpio2Pin = PinMapper::getInstance().getPinNumber("gpio2");

      dcmotor1 = new DCMotor(pwm1Pin, gpio1Pin);
      dcmotor2 = new DCMotor(pwm2Pin, gpio2Pin);
    }

    //===================== Network Initialization ===========================
    int port = (zbot.port == -1) ? 8090 :  zbot.port;
    char *buff;
    ZCommandService cmdService(port);

    cmdService.listenAndConnect();
    std::cout << "Connected to port [" << port << "] for commands" << std::endl;
    //========================================================================


    //=================== Main Loop ==========================================
    while (zbot.running) {
        cmdService.wait();
        if (cmdService.isReady()) {
            cmdService.recvBuff();
            buff = cmdService.getBuff();
            std::cout << buff << std::endl;
            // switch (cmd) {
            //     case DCMOTOR1_ID:
            //        dcmmotor1.execCommand(cmd);
            //        break;
            //     case DCMOTOR2_ID:
            //        dcmmotor2.execCommand(cmd);
            //        break;
            //     default:
            //        break;
            // }
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
            {"mapfile" ,required_argument, 0,  'f' },
            {"ndevs"   ,no_argument      , 0,  'n' },
            {0,0,0,0}
       };

        int long_index =0;
        int show_help  =0;

        while ((opt = getopt_long(argc, argv,"hvp:lf:n",
                       long_options, &long_index )) != -1) {

            switch (opt) {
                 case 'h' :
                     show_help=1;
                     break;
                 case 'v' :
                     break;
                 case 'p' :
                     zbot.port = atoi(optarg);
                     break;
                 case 'l' :
                     PinMapper::getInstance().listPlatformPins();
                     exit(EXIT_SUCCESS);
                     break;
                 case 'f' :
                     PinMapper::getInstance().init(optarg);
                     break;
                 case 'n' :
                     zbot.enDevs = false;
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
                "-l, --pins   : List Platform Pins\n"    <<
                "-f, --mapfile: Pin mapping file\n"      <<
                "-n, --nodevs : Does not enable devices" <<
            std::endl;

           exit(EXIT_FAILURE);
        }

}

static void signal_handler(int sig) {
   zbot.running = false;
   std::cout << "Ziroba Turned Off" << std::endl;
}
