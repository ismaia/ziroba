#include "pinmapper.hpp"
#include "mraa/gpio.h"
#include <string.h>



int PinMapper::init(const char * pinMapFile) {
   return mapfile.open(pinMapFile);
}

int PinMapper::listPlatformPins() {
  int pin_count = 0;

  uint8_t platform_offset = MRAA_MAIN_PLATFORM_OFFSET;
  pin_count += mraa_get_platform_pin_count(platform_offset);

  for (int k=0; k<2 ; k++) {
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
    platform_offset = MRAA_SUB_PLATFORM_OFFSET;
    pin_count += mraa_get_platform_pin_count(platform_offset);
  }
  return -1;
}
