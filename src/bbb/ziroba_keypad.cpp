//*************************************************
//Ziroba Robot Control Interface
//By Isaac Maia
//Universidade Federal da Paraiba - UFPB
//Departamento de Eng. Elétrica
//Sep/2014
//*************************************************

#include <ncurses.h>
#include <unistd.h>

#include "BlackLib.h" 
#include <iostream>
#include <string>
#include <ZirobaRobot.h>


//glabal functions
void updateWindow(std::string &, std::string &);

int main(int argc, char *argv[])
{	
        bool usePWM   = 0;
        bool printDbg = 0;

        //parse arguments
        for (int i=1; i < argc;  i++) {
          if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
              std::cout <<  "usage: " << argv[0] << " [options]\n" <<
                            "options:\n"         <<
                            "-p :  use pwm\n"    << 
                            "-d :  print debug"  << std::endl;
              exit(0);
          }else if (strcmp(argv[i], "-p") == 0) usePWM = 1; 
           else if (strcmp(argv[i], "-d") == 0) printDbg = 1;  

        }
        
        ZirobaRobot  robot(printDbg,usePWM);

        //------------ Window settings -------------
	initscr();			// Start curses mode 		
	cbreak();			// Line buffering disabled everty thing to me 		*/
	keypad(stdscr, TRUE);		// I need that nifty 
        nodelay(stdscr, TRUE);          // non-bloking input
        curs_set(0);                    // hide cursor
        noecho();                       // disables echo
        box(stdscr,0,0);
        mvprintw(1,1,"Ziroba Robot Control");
        mvprintw(2,1,"Arrow Keys: Directions, s (stop) , +/- (speed)" );
        mvprintw(3,1,"Press 'q' to exit");
        //------------------------------------------
        
        std::string cmd;     //command
        std::string speed;   //speed
        speed = std::to_string(robot.getSpeed());
                
        updateWindow(cmd,speed);

        int ch;
	while ( (ch = getch()) != 'q' )
	{	switch(ch)
		{	case KEY_LEFT:
                                cmd="LEFT     ";
                                robot.turnLeft();
				break;
			case KEY_RIGHT:
                                cmd="RIGHT    ";
                                robot.turnRight();
				break;
			case KEY_UP:
                                cmd="UP       ";
                                robot.moveForward();
				break;
			case KEY_DOWN:
                                cmd="DOWN     ";
                                robot.moveBackward();
				break;	
			case 's':
                                cmd="STOP     ";
                                robot.stop();
				break;	
                                
			case '+':
			case '=':
                                cmd="Speed up ";
                                robot.incSpeed();      
                                speed = std::to_string(robot.getSpeed());
				break;	
                                
			case '-':
                                cmd="Slow Down";
                                robot.decSpeed();
                                speed = std::to_string(robot.getSpeed());
				break;	
		}
                updateWindow(cmd,speed);
                usleep(15000);
	}
		
	endwin(); 
	return 0;
}



void updateWindow(std::string & cmd, std::string & speed) { 
    mvprintw(5,1,"Received Command.....:%s", cmd.c_str());
    mvprintw(6,1,"Speed................:%s", speed.c_str());
    refresh();
}



