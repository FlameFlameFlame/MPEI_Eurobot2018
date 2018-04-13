#pragma once

#define I2C_NAV_BUS 1
#define NAV_ADR 5
#define US_ADR 5

#include "controller.h"
#include "Platform.h"
#include <iostream>
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
	std::vector<int> readUSArduino();
	std::vector<float> readArduino();

	void print() {
		using namespace std;

		for (auto i : readUSArduino())
			cout << i << ' ';
		cout << endl;
	}

private:
	Platform* controlling;
	void turn(float d_angle);

	mraa::I2c i2c = mraa::I2c(I2C_NAV_BUS);

	float abs_float(float x) {
		if (x >= 0)
			return x;
		else
			return -x;
	}
};

