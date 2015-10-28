#include "pinmapper.hpp"
#include "mraa/gpio.h"
#include <string.h>


int PinMapper::getPin(const char * pinName) {
  int pin_count = 0;

  uint8_t platform_offset = MRAA_MAIN_PLATFORM_OFFSET;
  pin_count += mraa_get_platform_pin_count(platform_offset);

  for (int k=0; k<2 ; k++) {
      for (int i = 0; i < pin_count; ++i) {
          if (strcmp(mraa_get_pin_name(i), pinName) == 0) {
             int pin_id = platform_offset > 0 ? mraa_get_sub_platform_id(i) : i;
             return pin_id;
           }
      }
      platform_offset = MRAA_SUB_PLATFORM_OFFSET;
      pin_count += mraa_get_platform_pin_count(platform_offset);
  }
  return -1;
}
