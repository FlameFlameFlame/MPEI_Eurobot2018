#pragma once
#include "controller.h"
#include "Platform.h"

class Keyboard :
	protected Controller
{
public:
	Keyboard();
	~Keyboard();

	int takeControl(Platform*);
	void releaseDevice(Platform*);
	void startConsole();
	void stopConsole();

	void control();
private:
	Platform* controlling;
	uint8_t lateral_speed = 64;
	uint8_t rotational_speed = 64;
};

