#include <iostream>
#include <getopt.h>
#include <unistd.h>
#include <signal.h>


#include "mraa.hpp"
#include <SFML/Network.hpp>
#include "zcommon.hpp"
#include "znet.hpp"
#include "zmotion.hpp"


static void parse_args(int argc, char **argv);
static void signal_handler(int sig);

using namespace mraa;

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
    int statusLEDPin;
    int pwm1Pin;
    int gpio1Pin;
    int pwm2Pin;
    int gpio2Pin;


    DCMotor * dcmotor1 = NULL;
    DCMotor * dcmotor2 = NULL;
    Gpio    * statusLED = NULL;

    if (zbot.enDevs) {
      cout << "Platform:" << mraa_get_platform_name() << std::endl;
      int res =  mraa_init();
      if (res == MRAA_ERROR_PLATFORM_ALREADY_INITIALISED)
          cerr << "MRAA already initialized!!" << std::endl;
        else if (res == MRAA_UNKNOWN_PLATFORM)
                 cerr << "MRAA unknown Platform!!" << std::endl;
          else if (res == MRAA_ERROR_PLATFORM_NOT_INITIALISED)
                  cerr << "MRAA platform not initialized!!" << std::endl;



    }

    //===================== Network Initialization ===========================
    int port = (zbot.port == -1) ? 8090 :  zbot.port;
    char *buff;
    ZCommandService cmdService(port);

    cmdService.listenAndConnect();
    std::cout << "Receiving commands on port [" << port << "] " << std::endl;
    //========================================================================


    //=================== Main Loop ==========================================
    std::vector<std::string> cmdTokens;

    while (zbot.running) {
        cmdService.wait();
        if (cmdService.isReady()) {
            cmdService.recvBuff();
            buff = cmdService.getBuff();

            ZCmd zcmd;
            decodeCmd(buff, zcmd);

            // switch (zcmd) {
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
            cmdTokens.clear();
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
            {"ndevs"   ,no_argument      , 0,  'n' },
            {"pwm"     ,required_argument, 0,  'm' },
            {"gpio"    ,required_argument, 0,  'g' },
            {"chip"    ,required_argument, 0,  'c' },
            {0,0,0,0}
       };

        int long_index =0;
        int show_help  =0;

        while ((opt = getopt_long(argc, argv,"hvp:ln:m:g:c:",
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
                     listPlatformPins();
                     exit(EXIT_SUCCESS);
                     break;
                 case 'n' :
                 break;
                 case 'm' :
                 break;
                 case 'g' :
                 break;
                 case 'c' :
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
   mraa_deinit();
   exit(EXIT_SUCCESS);
}
