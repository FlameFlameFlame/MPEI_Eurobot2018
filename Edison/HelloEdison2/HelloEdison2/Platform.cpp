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
	/*if (!(i2c = new mraa::I2c(I2C_BUS))) {
		printw("Error! Couldn't initialize I2C bus! \n");
		status = -1;
	}
	else {
		i2c->address(PLATFORM_ADDRESS);
		i2c->writeByte(HELLO_BYTE);
		uint8_t data = i2c->readByte();

		if (data = !0xAA) {
			printw("Error! Platform not responding \n");
			status = -1;
		}
		else {
			status = 0;
			printw("Plaform initialized! \n");
		}
	}*/
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
	/*switch (data[0]) {
	case 0: {
		temp[0] = 0;
		temp[1] = 0;
		temp[2] = 0;
		temp[3] = 0;

		this->status = 0;
		break; }
	case 1: {
		temp[0] = 0xFF;
		temp[1] = data[1];
		temp[2] = data[2];
		temp[3] = data[3]; 

		this->status = 1;
		break; }
	default:
		std::cout << "Unrecognizable command to platform " << std::endl;
		temp[0] = 0;
		temp[1] = 0;
		temp[2] = 0;
		temp[3] = 0;

		this->status = -1;
		break;
	}*/

	float angle = data[1] * 3.1415 / 180;

	std::cout << "angle " << angle << "\n";

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

/*void Platform::sendI2C(uint8_t i2ccmd[7]) {
	if (initialized) {
		i2c.write((uint8_t*)i2ccmd, 7);
	}
}*/

/*void Platform::stop() {
	if (initialized) {
		i2c.write((uint8_t*)(0, 0, 0, 0), 4);
		status = 0;
	}
}*/