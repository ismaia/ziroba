#include <iostream>
#include <getopt.h>
#include <unistd.h>


#include "mraa.h"
#include <SFML/Network.hpp>
#include "zdefs.hpp"
#include "znet.hpp"
#include "zmotion.hpp"
#include "pinmapper.hpp"



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
            {0,0,0,0}
       };

        int long_index =0;
        int show_help  =0;

        while ((opt = getopt_long(argc, argv,"hvd:n:b:m",
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
                "-p, --port   : TCP port for commands\n" << std::endl;

           exit(EXIT_FAILURE);
        }

}


using namespace ziro;

int main(int argc, char ** argv) {
    parse_args(argc,argv);
    running = true;

    std::cout << "Ziroba Robot, " <<  "mraa Version:" << mraa_get_version() <<
                                                                       std::endl;

    int port = (zargs.port == -1) ? 8090 :  zargs.port;

    
    char *buff;
    ZCommandService cmdService(port);


    cmdService.listenAndConnect();
    std::cout << "Connected to port [" << port << "] for commands" << std::endl;


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
