#ifndef __ZDEFS__
#define __ZDEFS__

namespace ziro {
  struct args {
    int port;
  };
  args zargs = { -1 };
}


#define CLEAR_BUFF(buff) memset(buff, 0, sizeof(buff)) 

#endif

