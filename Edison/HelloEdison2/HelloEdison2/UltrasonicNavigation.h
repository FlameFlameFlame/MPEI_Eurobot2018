#pragma once

#define I2C_NAV_BUS 1
#define NAV_ADR 5
#define US_ADR 6

#include "controller.h"
#include "Platform.h"
#include <mraa.h>
#include <vector>
class UltrasonicNavigation :
	private Controller
{
public:
	UltrasonicNavigation();
	~UltrasonicNavigation();
  
	int takeControl(Platform* p);
	void releaseDevice();
	void releaseAll() { }

	int initializeController();

private:
	Platform* controlling;
	int takeControl(Platform* p);
	void releaseDevice();
	void releaseAll() { };
	void turn(float d_angle);

	int initializeController() { }
	std::vector<int> readUSArduino();

	mraa::I2c i2c = mraa::I2c(I2C_NAV_BUS);
	Platform* controlling;
	std::vector<float> readArduino();

	float abs_float(float x) {
		if (x >= 0)
			return x;
		else
			return -x;
	}
};

