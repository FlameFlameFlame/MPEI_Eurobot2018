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

	bool isSelfControlled;

	bool initialized;

	void parseCmdFromController(int data[3]);
	mraa::I2c i2c = mraa::I2c(I2C_BUS);
public:
	int getCmdFromController(int cmd[3]);

	int initializeDevice();
	int getStatus() { return this->status; }

	Platform();
	~Platform();
};
#endif // !PLATFORM_H