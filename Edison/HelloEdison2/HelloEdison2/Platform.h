#pragma once
#define I2C_BUS 1

#include <ncurses.h>
#include <mraa.hpp>
#include "Device.h"

#ifndef PLATFORM_H



class Platform :
	private Device
{
private:
	//int speed;
	//int rot_speed;
	//uint8_t* cmdFromController;
	//uint8_t* i2ccmd;

	bool isSelfControlled;

	bool initialized;

	void parseCmdFromController(int data[3]);
	//void sendI2C(uint8_t i2ccmd[4]);
	mraa::I2c i2c = mraa::I2c(I2C_BUS);
public:
	//void stop();

	int getCmdFromController(int cmd[3]);

	int initializeDevice();
	int getStatus() { return this->status; }

	Platform();
	~Platform();
	 
	/*void setSpeed(int spd) {
	(spd < 256 && spd > 0) ? speed = spd : printw("Unacceptable speed");
	}
	int  getSpeed() { return speed; }
	void setRotSpeed(int rot_spd) {
	(rot_spd < 256 && rot_spd > 0) ? rot_speed = rot_spd : printw("Unacceptable speed");
	}
	int  getRotSpeed() { return rot_speed; }*/
	/*void moveForward();
	void moveBackwards();
	void moveLeft();
	void moveRight();
	void rotateLeft();
	void rotateRight();*/
};
#endif // !PLATFORM_H