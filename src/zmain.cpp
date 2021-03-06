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


static void signal_handler(int sig);

using namespace mraa;

int main(int argc, char ** argv) {
	std::cout << "Ziroba" << std::endl;
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

	//default args
	zargs.port = -1;
  zargs.enableDevs = 1;

	parse_args(argc,argv);
	if (zargs.debug) {
		std::cout << "PWM Count:" << zargs.pwmVec.size() << std::endl;
		std::cout << "GPIO Count:" << zargs.gpioVec.size() << std::endl;
	}

	if (zargs.enableDevs) {
		cout << "Platform:" << mraa_get_platform_name() << std::endl;
		mraa_init();
	}
  zbot.start();


	//===================== Network Initialization ===========================
	int port = (zargs.port == -1) ? 8090 :  zargs.port;
	ZCommandService cmdService(port);


	std::cout << "Receiving commands on port [" << port << "] " << std::endl;
	//========================================================================


	//=================== Main Loop ==========================================
	ZNetCmd zCmd;
	while (zbot.isRunning()) {
			cmdService.wait();
			if (cmdService.isReady()) {
					cmdService.recvBuff();
					cmdService.decodeBuff(zCmd);
          if (zargs.enableDevs) {
					  zbot.executeCmd(zCmd);
					}
					usleep(1000); //IO Wait
					cmdService.clearBuff();
			}
	}

	return 0;
}


static void signal_handler(int sig) {
	 zbot.stop();
	 std::cout << "Ziroba Turned Off" << std::endl;
	 mraa_deinit();
}
