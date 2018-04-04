#include "Platform.h"
#include <mraa.hpp>
#include <iostream>
#include <math.h>

#define PLATFORM_ADDRESS 0x04

//messages to platform
#define HELLO_BYTE 0xAA
#define FORWARD_BYTE 0x01
#define LEFT_BYTE 0x02
#define RIGHT_BYTE 0x03
#define BACKWARS_BYTE 0x04
#define ROT_LEFT_BYTE 0x05
#define ROT_RIGHT_BYTE 0x06
#define STOP_BYTE 0xFF

Platform::Platform() {

}

Platform::~Platform() {
	delete &status;
}

//To initialize platform we're sending it HELLO_BYTE then waiting for it to responce with HELLO_BYTE
int Platform::initializeDevice()
{
	using namespace std;

	isSelfControlled = false;
	//cout << "Initializing platform" << endl;
	i2c.address(PLATFORM_ADDRESS);
	i2c.writeByte(HELLO_BYTE);
	uint8_t data[1];
	i2c.read(data,1);

	if (data[0] != 0xAA) {
		cout << "Cannot connect with Arduino. It sent " << int(data[0]) << endl;
		initialized = false;
		status = -1;
	}
	else {
		initialized = true;
		cout << "Platform initialized!" << endl;
		status = 0;
	}
	return status;
}


//gets command from controller
//first byte is action, second is Vx, third is Vy, fourth is omega
int Platform::getCmdFromController(int cmd[3]) {
	parseCmdFromController(cmd);
	return this->status;
	return 0;
}

//I2C message to platform consists of 7 bytes: 0xFF, speed sign, speed, direction sign, direction, rotational speed sign, rotational speed
void Platform::parseCmdFromController(int data[3]) {
	double angle = data[1] * 3.1415 / 180;

	int8_t Vx = data[0] * cos(angle);
	int8_t Vy = data[0] * sin(angle);

	uint8_t i2cmsg[7];
	if (data[0] || data[1] || data[2])
	{
		i2cmsg[0] = 0xFF;
		//Vx
		i2cmsg[1] = bool (Vx > 0);
		i2cmsg[2] =  abs(Vx);
		//Vy
		i2cmsg[3] = bool(Vy > 0);
		i2cmsg[4] =  abs(Vy);
		//rotational_speed
		i2cmsg[5] = bool(data[2] > 0);
		i2cmsg[6] =  abs(data[2]);

		status = 1;
	}
	else {
		for (int i = 0; i < 7; i++)
			i2cmsg[i] = 0;
		status = 0;
	}
	if (initialized) {
		i2c.write(i2cmsg, 7);
	}
}