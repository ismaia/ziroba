#include "znet.h"
#include <iostream>
#include <string.h>

static size_t buff_bytes;

sf::SocketSelector netMonitor;


ZCommandService::ZCommandService(int port, size_t buff_size)
    :listener(),
      socket(),
      port(port),
      buff_size(buff_size),
      recv_bytes(0),
      buff(new char[buff_size])
{
    buff_bytes = buff_size*sizeof(char);
    listener.setBlocking(false);
    socket.setBlocking(false);
}

ZCommandService::~ZCommandService() {
    delete buff;
}


bool ZCommandService::isReady()
{
    return netMonitor.isReady(socket);
}


bool ZCommandService::listenAndConnect() {
    if (listener.listen(port) == sf::Socket::Done) {
        std::cout << "listening on port:" << port << std::endl;
    }else exit(EXIT_FAILURE);

    netMonitor.add(listener);
    while (1) {
        netMonitor.wait();
        if (netMonitor.isReady(listener))  {
            if (listener.accept(socket)  == sf::Socket::Done) {
                netMonitor.add(socket);
                return true;
            }else {
                std::cerr << "Can't accept connection at port " << port << std::endl;
                exit(EXIT_FAILURE);
            }
        }
    }
}


void ZCommandService::clearBuff() {
    memset(buff, 0 , buff_bytes);
}

bool ZCommandService::sendBuff()
{
    sf::Socket::Status status;
    socket.send(buff,buff_size);
    return (status == sf::Socket::Done);
}

bool ZCommandService::recvBuff()
{
    sf::Socket::Status status;
    status = socket.receive(buff, buff_bytes, recv_bytes);
    return (status == sf::Socket::Done);
}

char * ZCommandService::getBuff()
{
    return buff;
}

void ZCommandService::wait()
{
    netMonitor.add(socket);
    netMonitor.wait();
}


