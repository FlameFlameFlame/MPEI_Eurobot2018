#pragma once
#define I2C_NAV_BUS 1

#include "controller.h"
#include "Platform.h"
#include <mraa.h>
#include <vector>

using namespace std;


struct Point {
	float x, y;
};

class Navigation :
	private Controller
{
public:
	Navigation(float x0, float y0, float angle0) {
		x = x0;
		y = y0;
		angle = angle0;
	}
	~Navigation();
	
	int takeControl(Platform* plt);
	void releaseDevice();
	void releaseAll();

	int initializeController();

	void setDestination(float xnew, float ynew);
	void stop();
private:
	int cur_point = 0;
	vector<Point> route;

	vector<Point> planMovement(float x0, float y0);

	mraa::I2c i2c = mraa::I2c(I2C_NAV_BUS);
	vector<float> readArduino();
	
	float x, y, angle;
	void rotate(float d_angle);
	void moveToNextPoint();
	float angle(float x1, float y1);

	Platform* controlling;
};

