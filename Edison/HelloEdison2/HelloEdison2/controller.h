#pragma once

class Controller {
protected:
	bool isControlling;
public:
	Controller() { isControlling = 0; }
	//virtual ~Controller() = 0;

	virtual int takeControl();
	virtual void releaseDevice();
	virtual void releaseAll();

	virtual int initializeController();
};
