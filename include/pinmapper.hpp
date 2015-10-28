#ifndef __PINMAPPER__
#define __PINMAPPER__

class PinMapper {
  public:
    static PinMapper & getInstance() {
      static PinMapper instance;
      return instance;
    }


    int getPin(const char * pinName);

  private:
    PinMapper() {}
    PinMapper(PinMapper const &);
    void operator=(PinMapper const &);    
};

#endif
