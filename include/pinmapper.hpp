#ifndef __PINMAPPER__
#define __PINMAPPER__
#include "zdefs.hpp"

class PinMapper {
  public:
    static PinMapper & getInstance() {
      static PinMapper instance;
      return instance;
    }

    void init(char * pinmapFile);
    int getPinNumber(const char * pinName);
    void listPlatformPins();



  private:
    PinMapper() {}
    PinMapper(PinMapper const &);
    void operator=(PinMapper const &);

};

#endif
