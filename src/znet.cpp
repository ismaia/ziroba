#include "znet.hpp"
#include "zcommon.hpp"
#include <iostream>
#include <string.h>

static size_t buff_bytes;

sf::SocketSelector netMonitor;



ZCommandService::ZCommandService(int port, size_t buff_size)
:
socket(),
sender(),
port(port),
buff_size(buff_size),
recv_bytes(0),
buff(new char[buff_size])
{
  buff_bytes = buff_size*sizeof(char);
  socket.setBlocking(false);
  socket.bind(port);
}

ZCommandService::~ZCommandService() {
  delete buff;
}

bool ZCommandService::isReady()
{
  return netMonitor.isReady(socket);
}


void ZCommandService::clearBuff() {
  memset(buff, 0 , buff_bytes);
}


bool ZCommandService::recvBuff()
{
  sf::Socket::Status status;
  unsigned short    remotePort;
  status = socket.receive(buff, buff_bytes, recv_bytes, sender, remotePort);
  return (status == sf::Socket::Done);
}

void ZCommandService::wait()
{
  netMonitor.add(socket);
  netMonitor.wait();
}


int ZCommandService::decodeBuff(ZNetCmd & zcmd) {
  static char dev[10];
  static char act[10];
  static char val[10];

  memset(dev,'\0',10);
  memset(act,'\0',10);
  memset(val,'\0',10);

  //format dddd:aaaa:vvvvvvvv
  //       0123456789
  strncpy(dev, &buff[0] , 4);    //buff[0..3]
  strncpy(act, &buff[5] , 4);    //buff[5..7]
  strncpy(val, &buff[10], 8);    //buff[10..18]


  zcmd.device = std::atoi(dev);
  zcmd.action = std::atoi(act);
  zcmd.value  = std::atoi(val);


  if (zargs.debug) {
    std::cout << "Raw cmd....:" << buff << "\n"  <<
    "Decoded cmd:"
    << zcmd.device << ":" << zcmd.action << ":" << zcmd.value << std::endl;
  }


  return -1;
}
