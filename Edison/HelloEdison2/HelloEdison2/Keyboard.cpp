#include "Keyboard.h"
#include <iostream>



Keyboard::Keyboard() {
}


Keyboard::~Keyboard() {
}

void Keyboard::startConsole() {
	/*initscr();
	keypad(stdscr, true);
	curs_set(0);
	halfdelay(1); //wainting 0.1 seconds, then returning ERR

	printw("Control platform from the keyboard. Press any key to start. \n");
	control();
	refresh();
	getch();*/
	std::cout << "Okay, trying to control from keyboard" << std::endl;
}

void Keyboard::stopConsole() {
	/*printw("Stopping keyboard control. Press any key to exit. \n");
	refresh();
	getch();
	enddwin();*/
	
}

int Keyboard::takeControl(Platform* plt) {
	controlling = plt;
	controlling->initializeDevice();
	return controlling->getStatus();
}

void Keyboard::releaseDevice(Platform* plt) {
	int cmd[3] = { 0,0,0 };
	controlling->getCmdFromController(cmd);
	controlling = NULL;
}

void Keyboard::control() {
	using namespace std;

	//std::cout << "Enter three parameters: speed, direction and rotational speed" << std::endl;

	int cmd[3] = { 0, 0, 0 };
	/*for (int i = 0; i < 3; ++i) {
		//cout << "Enter parameter " << i << endl;
		cin >> cmd[i];
	}*/

	cin >> cmd[0];
	cout << cmd[0] << endl;

	cin >> cmd[1];
	cout << cmd[1] << endl;

	cin >> cmd[2];
	cout << cmd[2] << endl;
	controlling->getCmdFromController(cmd);
	/*switch (getch()) {
		case 'w': case 'W':
			cmd[0] = 1;
			cmd[1] = lateral_speed;
			//controlling->getCmdFromController((uint8_t*) ( 1, lateral_speed, 0, 0 ));
			break;
		case 's': case 'S':
			cmd[0] = 1;
			cmd[1] = -lateral_speed;
			//controlling->getCmdFromController((uint8_t*)(1, -lateral_speed, 0, 0));
			break;
		case 'a': case 'A':
			cmd[0] = 1;
			cmd[2] = -lateral_speed;
			//controlling->getCmdFromController((uint8_t*)(1, 0, -lateral_speed, 0));
			break;
		case 'd': case 'D':
			cmd[0] = 1;
			cmd[2] = lateral_speed;
			//controlling->getCmdFromController((uint8_t*)(1, 0, lateral_speed, 0));
			break;
		case 'q': case 'Q':
			cmd[0] = 1;
			cmd[3] = rotational_speed;
			//controlling->getCmdFromController((uint8_t*)(1, 0, 0, rotational_speed));
			break;
		case 'e': case 'E':
			cmd[0] = 1;
			cmd[3] = -rotational_speed;
			//controlling->getCmdFromController((uint8_t*)(1, 0, 0, -rotational_speed));
			break;
		case ERR: default:
			cmd[0] = 0;
			cmd[1] = 0;
			cmd[2] = 0;
			cmd[3] = 0;
			//controlling->getCmdFromController((uint8_t*)(0, 0, 0, 0));
			break;
		case 'x': case 'X':
			//controlling->getCmdFromController((uint8_t*)(0, 0, 0, 0));
			this->releaseDevice(controlling);
			this->stopConsole();
			exit = true;
			break;
		}
		if (!exit) {
			controlling->getCmdFromController(cmd);
			//printw("Hey! \n");
		}
	}*/
}
