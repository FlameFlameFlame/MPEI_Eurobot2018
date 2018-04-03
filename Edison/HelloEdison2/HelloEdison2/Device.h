#pragma once
class Device
{
protected:
	bool isSelfControlled;
	int command[4];
	int status;
	int bytesInMessage;
	//virtual void sendI2C(uint8_t*) = 0;
	//virtual uint8_t* parseCmdFromController((uint8_t*)) = 0;

public:
	Device() { isSelfControlled = false; status = -1; }
	//virtual ~Device() = 0;

	virtual int initializeDevice() = 0;	
};

