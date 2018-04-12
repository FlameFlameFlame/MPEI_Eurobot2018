#include "Keyboard.h"
#include <iostream>



Keyboard::Keyboard() {
}


Keyboard::~Keyboard() {
}

void Keyboard::startConsole() {
	std::cout << "Okay, trying to control from keyboard" << std::endl;
}

void Keyboard::stopConsole() {

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

	int cmd[3] = { 0, 0, 0 };

	cin >> cmd[0];
	cin >> cmd[1];
	cin >> cmd[2];
	controlling->getCmdFromController(cmd);
}
