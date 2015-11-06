#include <getopt.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include <iostream>
#include "mraa.hpp"
#include <SFML/Network.hpp>
#include "zcommon.hpp"
#include "znet.hpp"
#include "zmotion.hpp"
#include "zirobarobot.hpp"


static void parse_args(int argc, char **argv);
static void signal_handler(int sig);

using namespace mraa;

int main(int argc, char ** argv) {
    parse_args(argc,argv);
    zbot.start();
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

    if (zargs.enableDevs) {
      cout << "Platform:" << mraa_get_platform_name() << std::endl;
      mraa_init();
    }

    //===================== Network Initialization ===========================
    int port = (zargs.port == -1) ? 8090 :  zargs.port;
    char *buff;
    ZCommandService cmdService(port);

    cmdService.listenAndConnect();
    std::cout << "Receiving commands on port [" << port << "] " << std::endl;
    //========================================================================


    //=================== Main Loop ==========================================
    std::vector<std::string> cmdTokens;

    while (zbot.isRunning()) {
        cmdService.wait();
        if (cmdService.isReady()) {
            cmdService.recvBuff();
            buff = cmdService.getBuff();

            ZNetCmd zcmd;
            cmdService.decodeCmd(buff, zcmd);

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
      char *subopts, *value;
      int errfnd = 0;

      enum {
       PWM_CHIP = 0,
       PWM_N,
       PWM_EXPORT,
       GPIO_CHIP,
       GPIO_N,
       GPIO_EXPORT
      };

      int pwm_chip   = -1;
      int pwm_n      = -1;
      int pwm_expo   = -1;
      int gpio_chip  = -1;
      int gpio_n     = -1;
      int gpio_expo  = -1;

       static const char *dev_opts[] = {
           [PWM_CHIP]    = "pwm_chip"   ,
           [PWM_N]       = "pwm_n"      ,
           [PWM_EXPORT]  = "pwm_export" ,
           [GPIO_CHIP]   = "gpio_chip"  ,
           [GPIO_N]      = "gpio_n"     ,
           [GPIO_EXPORT] = "gpio_export",
           NULL
       };

       static struct option long_options[] = {
            {"help"        ,no_argument      , 0,  'h' },
            {"verbose"     ,no_argument      , 0,  'v' },
            {"port"        ,required_argument, 0,  'p' },
            {"pins"        ,no_argument      , 0,  'l' },
            {"ndevs"       ,no_argument      , 0,  'n' },
            {"dev"         ,required_argument, 0,  'd' },
            {0,0,0,0}
       };

        int long_index =0;
        int show_help  =0;

        while ((opt = getopt_long(argc, argv,"hvp:lnd:",
                       long_options, &long_index )) != -1) {

            switch (opt) {
                 case 'h' :
                     show_help=1;
                     break;
                 case 'v' :
                     zargs.debug = true;
                     break;
                 case 'p' :
                     zargs.port = atoi(optarg);
                     break;
                 case 'l' :
                     listPlatformPins();
                     exit(EXIT_SUCCESS);
                     break;
                 case 'n' :
                     zargs.enableDevs = false;
                     break;

                 case 'd' :
                   subopts = optarg;

                   while (*subopts != '\0' && !errfnd)  {
                     switch(getsubopt(&subopts, (char **)dev_opts, &value)) {
                          case PWM_CHIP:
                            pwm_chip = atoi(value);
                            break;
                          case PWM_N:
                            pwm_n = atoi(value);
                            break;
                          case PWM_EXPORT:
                            pwm_expo = atoi(value);
                            break;
                          case GPIO_CHIP:
                            gpio_chip = atoi(value);
                            break;
                          case GPIO_N:
                            gpio_n = atoi(value);
                            break;
                          case GPIO_EXPORT:
                            gpio_expo = atoi(value);
                            break;
                          default:
                            errfnd = 1;
                            break;
                        }
                   }

                   if (pwm_chip !=-1) {
                      mraa::Pwm * pwm = new mraa::Pwm(pwm_n, true, pwm_chip);
                   }else if (pwm_expo != -1) {
                        mraa::Pwm * pwm = new mraa::Pwm(pwm_n);
                   }

                   if (gpio_chip != -1) {
                     mraa::Gpio * gpio = new mraa::Gpio(gpio_n, true, gpio_chip);
                   }else if (gpio_expo != -1) {
                     mraa::Gpio * gpio = new mraa::Gpio(gpio_n);
                   }


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
                "-n, --nodevs : Does not enable devices\n" <<
                "-d, --dev    : Specifies hardware used in a specific robot device\n" <<
                "     sub options: pwm_chip=n, pwm_n=n , pwm_export=n\n" <<
                "                  gpio_chip=n, gpio_n=n , gpio_export=n\n" <<
            std::endl;
           exit(EXIT_FAILURE);
        }

}

static void signal_handler(int sig) {
   zbot.stop();
   std::cout << "Ziroba Turned Off" << std::endl;
   mraa_deinit();
   exit(EXIT_SUCCESS);
}
