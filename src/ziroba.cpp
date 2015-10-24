#include <iostream>
#include <zvision.h>
#include <zmotion.h>
#include <string>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#include "mraa.h"
#include <SFML/Network.hpp>
#include "zdefs.h"



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

    int port = (zargs.port == -1) ? 8090 :  zargs.port;

    sf::TcpListener listener;
    // bind the listener to a port
    if (listener.listen(port) != sf::Socket::Done)
    {
        std::cerr << "Can't listen port " << port << std::endl;
        exit(EXIT_FAILURE);
    }else std::cout << "Listening on port " << port << std::endl;

    // accept a new connection
    sf::TcpSocket socket;
    if (listener.accept(socket) != sf::Socket::Done)
    {
        std::cerr << "Can't accept connection at port " << port << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Connected on port " << port << std::endl;

    char buff[128];     
    CLEAR_BUFF(buff);
    

    std::size_t nbytes;
    sf::Socket::Status status = sf::Socket::NotReady;        

    while ( status != sf::Socket::Disconnected  ) {
        status = socket.receive(buff, sizeof(buff) , nbytes);
        std::cout << buff << std::endl;
        CLEAR_BUFF(buff);
    }

    return 0;
}
