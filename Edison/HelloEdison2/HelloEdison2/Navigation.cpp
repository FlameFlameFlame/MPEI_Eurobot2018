#include "Navigation.h"
#include <iostream>
#include <math.h>
#define NAV_ADR 6                //address of navigational arduino
#define COL_AVOID_ARD 5
#define ROUTE_RESOLUTION 10
#define MARGIN 5

Navigation::~Navigation() {
}

int Navigation::initializeController() {

}

int Navigation::takeControl(Platform* plt) {
	controlling = plt;
	controlling->initializeDevice();
	return controlling->getStatus();
}

void Navigation::releaseDevice() {
	int temp[4] = { 0,0,0,0 };
	controlling->getCmdFromController(temp);
}

void Navigation::releaseAll() {

}

//read current position from navigational Arduino
vector<float> Navigation::readArduino() {
	vector<float> result(3);
	i2c.address(NAV_ADR);
	uint8_t message[12];
	i2c.read(message, 12);

	union u_tag {
		uint8_t bytes[4];
		float fval;
	} u;

	//converting massive of bytes to float using union u
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			u.bytes[j] = message[i + j];
			result[i] = u.fval;
		}
	}
	return result;
}

void Navigation::setDestination(float xnew, float ynew) {
	float x_next = 0;
	float y_next = 0;
	using namespace std;

	route = planMovement(xnew, ynew);
	while (cur_point < ROUTE_RESOLUTION) {
		x_next = route[cur_point].x;
		y_next = route[cur_point].y;


		cout << "Rotating" << endl;
		rotate(angle(x_next, y_next));
		cout << "Moving to point " << cur_point << "\n";
		moveToNextPoint();
		cur_point++;
	}
}


//setting up a route
vector<Point> Navigation::planMovement(float x1, float y1) {
	float x_d = (x - x1) / ROUTE_RESOLUTION;
	float y_d = (y - y1) / ROUTE_RESOLUTION;

	vector<Point> result;
	Point temp;
	for (int i = 0; i < ROUTE_RESOLUTION; i++) {
		temp.x = x + x_d * (i + 1);
		temp.y = y + y_d * (i + 1);
		result.push_back(temp);
	}
	return result;
}

float Navigation::angle(float x1, float y1) {
	//calculating an angle by the product of two vectors

	float x_dest = x1 - x;
	float y_dest = y1 - y;
	float dest_leght = sqrt(pow(x_dest, 2) + pow(y_dest, 2));

	float cos_alpha = dest_leght / x_dest;

	if (y1 > y)
		return acos(cos_alpha);
	else if (y1 < y)
		return 2 * M_PI - acos(cos_alpha);
	else if (x1 > x)
		return M_PI;
	else if (x1 < x)
		return 0.0f;
}

void Navigation::rotate(float d_angle) {
	float angle0 = readArduino()[2];
	float new_angle = angle0 + d_angle;

	int cmd[3] = { 0,0,0 };
	int rot_speed = 255;
	
	while (abs_float(d_angle) > 0.05) {
		cmd[2] = (int)d_angle;
		controlling->getCmdFromController(cmd);
		d_angle = new_angle - readArduino()[2];
	}
}
