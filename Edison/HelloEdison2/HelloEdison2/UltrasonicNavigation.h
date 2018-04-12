#pragma once
#include "controller.h"
#include "Platform.h"
#include <mraa.h>

class UltrasonicNavigation :
	public Controller
{
public:
	UltrasonicNavigation();
	~UltrasonicNavigation();

	int takeControl();
	void releaseDevice();
	void releaseAll() { }

	int initializeController();

private:
	Platform* controlling;

};
