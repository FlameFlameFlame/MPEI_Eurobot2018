#include <cstdio>

#include "Platform.h"
#include "Keyboard.h"

Keyboard k;
Platform p;

int main()
{
	k.startConsole();
	k.takeControl(&p);
	while (true)
	{
		//p.initializeDevice();
		k.control();
	}
    return 0;
}