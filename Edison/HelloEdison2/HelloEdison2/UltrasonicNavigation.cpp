#include "UltrasonicNavigation.h"



UltrasonicNavigation::UltrasonicNavigation()
{

}


UltrasonicNavigation::~UltrasonicNavigation()
{

}

int UltrasonicNavigation::takeControl(Platform* p) {
	controlling = p;
	controlling->initializeDevice();
}

void UltrasonicNavigation::releaseDevice() {
	int cmd[4] = { 0,0,0,0 };
	controlling->getCmdFromController(cmd);
}

std::vector<int> UltrasonicNavigation::readUSArduino() {
	i2c.address(US_ADR);
	uint8_t message[4];
	i2c.read(message, 4);

	using namespace std;
	vector<int> result;
	for (int i = 0; i < 4; i++)
	{
		result.push_back((int)message[i]);
	}
	return result;
}

void UltrasonicNavigation::turn(float d_angle) {
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

//read current position from navigational Arduino
std::vector<float> UltrasonicNavigation::readArduino() {
	using namespace std;

	vector<float> result(3);
	i2c.address(NAV_ADR);
	uint8_t message[12];
	i2c.read(message, 12);

	union u_tag {
		uint8_t bytes[4];
		float fval;
	} u;
h
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
