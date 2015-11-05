#include "pinmapper.hpp"
#include "mraa/gpio.h"
#include <string.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

static char * pinmapFileName = NULL;

using namespace std;

void PinMapper::init(char * pinmapFile) {
   pinmapFileName = pinmapFile;
}

int PinMapper::getPinNumber(const char * pinName) {
   std::fstream mapfile(pinmapFileName);
   std::string line;
   std::size_t pos;
   std::vector<std::string> tokens;
   std::string str = pinName; //fist column : Program Pin Name
   int count = 0;

   if (mapfile.good()) {
      while ( std::getline(mapfile, line) ) {
             pos = line.find(str);
             if (pos != std::string::npos) {
               Tokenize(line, tokens, " :");
               if (count == 0) {
                 str = tokens[1]; //second column: Physical Name
                 count++;
                } else {
                 std::string phyPinNum = tokens[0];
                 return std::atoi(phyPinNum.c_str());
               }
             }
             tokens.clear();
      }
   }
   mapfile.close();
   return -1;
}

void PinMapper::listPlatformPins() {
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
