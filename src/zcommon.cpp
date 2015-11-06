#include "zcommon.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include <iostream>
#include <map>
#include <mraa.hpp>
#include <mraa.h>

ZSysArgs  zargs;

void Tokenize(const string& str,
                      vector<string>& tokens,
                      const string& delimiters)
{
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}




void listPlatformPins() {
  int pin_count = 0;

  uint8_t platform_offset = MRAA_MAIN_PLATFORM_OFFSET;
  pin_count += mraa_get_platform_pin_count(platform_offset);

  for (int k=0; k<1 ; k++) {
    for (int i = 0; i < pin_count; ++i) {
        if (strcmp(mraa_get_pin_name(i), "INVALID") != 0) {
            int pin_id = platform_offset > 0 ? mraa_get_sub_platform_id(i) : i;
            fprintf(stdout, "%02d ", pin_id);
            fprintf(stdout, "%*s: ", (MRAA_PIN_NAME_SIZE - 1), mraa_get_pin_name(i));
            if (mraa_pin_mode_test(i, MRAA_PIN_GPIO))
                fprintf(stdout, "GPIO ");
            if (mraa_pin_mode_test(i, MRAA_PIN_I2C))
                fprintf(stdout, "I2C  ");
            if (mraa_pin_mode_test(i, MRAA_PIN_SPI))
                fprintf(stdout, "SPI  ");
            if (mraa_pin_mode_test(i, MRAA_PIN_PWM))
                fprintf(stdout, "PWM  ");
            if (mraa_pin_mode_test(i, MRAA_PIN_AIO))
                fprintf(stdout, "AIO  ");
            if (mraa_pin_mode_test(i, MRAA_PIN_UART))
                fprintf(stdout, "UART ");
            fprintf(stdout, "\n");
        }
    }
    platform_offset = MRAA_SUB_PLATFORM_OFFSET;
    pin_count += mraa_get_platform_pin_count(platform_offset);
  }
}


//parse command line arguments
void parse_args(int argc, char **argv)
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
      mraa::Pwm * pwm = NULL;
      mraa::Gpio * gpio = NULL;


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
                   pwm_chip   = -1;
                   pwm_n      = -1;
                   pwm_expo   = -1;
                   gpio_chip  = -1;
                   gpio_n     = -1;
                   gpio_expo  = -1;
                   pwm        = NULL;
                   gpio       = NULL;

                   while (*subopts != '\0' && !errfnd)  {
                     switch(getsubopt(&subopts, (char **)dev_opts, &value)) {
                          case PWM_CHIP:
                            pwm_chip = atoi(value);
                            if (pwm_n != -1) {
                              pwm = new mraa::Pwm(pwm_n, true, pwm_chip);
                            }
                            break;
                          case PWM_N:
                            pwm_n = atoi(value);
                            if (pwm_chip != -1)
                              pwm = new mraa::Pwm(pwm_n, true, pwm_chip);
                            break;
                          case PWM_EXPORT:
                            pwm_expo = atoi(value);
                              if (pwm_chip == -1 && pwm_n == -1)
                                pwm = new mraa::Pwm(pwm_expo);
                              else std::cerr << "export is not allowed alog with chip option"  << std::endl;
                            break;
                          case GPIO_CHIP:
                            gpio_chip = atoi(value);
                            if (gpio_n != -1)
                              gpio = new mraa::Gpio(gpio_n, true, gpio_chip);
                            break;
                          case GPIO_N:
                            gpio_n = atoi(value);
                            if (gpio_chip != -1)
                              gpio = new mraa::Gpio(gpio_n, true, gpio_chip);
                            break;
                          case GPIO_EXPORT:
                            gpio_expo = atoi(value);
                            if (gpio_chip == -1 && gpio_n == -1)
                                gpio = new mraa::Gpio(gpio_expo);
                            else std::cerr << "export is not allowed alog with chip option"  << std::endl;
                            break;
                          default:
                            errfnd = 1;
                            break;
                        }
                        if (pwm != NULL)
                           zargs.pwmVec.push_back(pwm);
                        if (gpio != NULL)
                           zargs.gpioVec.push_back(gpio);
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
