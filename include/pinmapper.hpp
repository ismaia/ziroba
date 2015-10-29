#ifndef __PINMAPPER__
#define __PINMAPPER__
#include <fstream>

class PinMapper {
  public:
    static PinMapper & getInstance() {
      static PinMapper instance;
      return instance;
    }

    int init(const char * pinMapFile);
    void listPlatformPins();


  private:
    PinMapper() {}
    PinMapper(PinMapper const &);
    void operator=(PinMapper const &);
    std::fstream mapfile;
};

#endif
