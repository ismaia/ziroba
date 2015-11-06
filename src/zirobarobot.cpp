#include "zirobarobot.hpp"


ZirobaRobot zbot;

ZirobaRobot::ZirobaRobot() {
  running = false;

}


void ZirobaRobot::start() {
  running = true;
}


void ZirobaRobot::stop() {
  running = false;
}
