#pragma once
#define I2C_WAT_BUS 1

#include "Device.h"
#include <iostream>
#include <mraa.hpp>

#define WATER_ADR 8
#define TURN_OFF 0
#define WAIT_FOR_CONTACT 1
#define GET_CLEAN 2
#define GET_MIXED 3
#define FLUSH_DIRTY 4

class Water :
	private Device
{
private:
	bool isSelfControlled = true;
	int command[4] = { 0,0,0,0 };
	int status = 1;
	int bytesInMessage = 1;

	mraa::I2c i2c = mraa::I2c(I2C_WAT_BUS);
public:

	void debugWater(int cmd);
	Water();
	~Water();
};

