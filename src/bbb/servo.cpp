#include <iostream>
#include "BlackLib.h" 
#include <unistd.h>    
#include <iostream>
#include <signal.h>
#include <string.h>


BlackPWM   *pwm1;


static void signal_handler(int sig, siginfo_t *siginfo, void *context) {
    int signum;
    pwm1->setRunState(pwm_value::stop);
    std::cerr << "closing PWM" << std::endl;
    exit(1);
}


int main(int argc, char *argv[]) {
    struct sigaction act;
    act.sa_sigaction = &signal_handler;
    act.sa_flags     = SA_SIGINFO;
    sigaction (SIGINT, &act, NULL);

    float duty_min = 3.0;
    float duty_max = 11.0;
    float duty = 0;    
    float slt    = 15000; //sleep time (us)
    float step   = 0.05;
    
    //parse args
    for (int i=1; i < argc; i++) {
        if (strcmp(argv[i],"-sl") == 0) {
            slt = atof(argv[i+1]);
        }else if (strcmp(argv[i],"-st") == 0) {
            step = atof(argv[i+1]);
        } else if (strcmp(argv[i],"-h") == 0) {
            std::cout << "usage: "  << argv[0] << " [options]\n" <<
                         "options:\n" <<
                         "-sl : sleep time\n" <<
                         "-st : step\n" << std::endl;
            exit(0);

        }    
    }

    pwm1 = new BlackPWM(EHRPWM2B); 
    pwm1->setPeriodTime(20000000); //50Hz
    pwm1->setDutyPercent((duty_min+duty_max)/2);
    pwm1->setRunState(pwm_value::stop);
    usleep(1000);
    pwm1->setRunState(pwm_value::run);
      
    while ( 1 ) {
       for (  ; duty < duty_max ; duty += step) {
         pwm1->setDutyPercent(duty);
         usleep(slt);
       }
       for (  ; duty > duty_min ; duty -= step) {
         pwm1->setDutyPercent(duty);
         usleep(slt);
       }
    }
    pwm1->setRunState(pwm_value::stop);

    return 0;
}
