#include "Water.h"
#include <mraa.h>


Water::Water()
{
}


Water::~Water()
{
}


void Water::debugWater(int cmd) {
	using namespace std;
	if (cmd == 1) {
		cout << "Debugging contact!" << endl;

		const uint8_t cmd = 1;
		i2c.writeByte(cmd);

		uint8_t responce[1];
		do {
			i2c.read(responce, 1);
		} while (responce[0] != 0xFF);
	}
	else if (cmd == 2) {
		cout << "Debugging getting clean water!" << endl;
		const uint8_t cmd = 2;
		i2c.writeByte(cmd);
	}
	else if (cmd == 3) {
		cout << "Debugging getting mixed water!" << endl;
		const uint8_t cmd = 3;
		i2c.writeByte(cmd);
	}
	else if (cmd == 4) {
		cout << "Debugging flushing dirty water!" << endl;
		const uint8_t cmd = 4;
		i2c.writeByte(cmd);
	}
}