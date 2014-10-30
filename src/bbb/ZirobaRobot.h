//*************************************************
//Ziroba Robot API
//By Isaac Maia
//Universidade Federal da Paraiba - UFPB
//Departamento de Eng. Elétrica
//Sep/2014
//*************************************************

#include <iostream>
#include <string>
#include <vector>


class ZirobaRobot {
    public:               
        ZirobaRobot(bool debug = false, bool usePWM = false, bool useRadar = false);
        ~ZirobaRobot();
        void  turnLeft();
        void  turnRight();
        void  moveForward();
        void  moveBackward();
        void  stop();
        void  setSpeed(float s);
        void  incSpeed();
        void  decSpeed();
        float getSpeed() { return speed; }
        void  runRadar();
        void  stopRadar();
        
    private:
        float  speed;
        bool   usePWM;
        bool   useRadar;
        
        //disabled constructors
        ZirobaRobot(ZirobaRobot const&);
        void operator=(ZirobaRobot const&);

};
