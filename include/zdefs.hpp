#ifndef __ZDEFS__
#define __ZDEFS__



namespace ziro {

#define  DCMOTOR1_ID 1
#define  DCMOTOR2_ID 2

struct ZiroRobot {
    int  port;
    bool running;
    bool enDevs;
};

ZiroRobot zbot = { -1  , false , true };


}


#endif
