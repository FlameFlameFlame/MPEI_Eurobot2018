#include <cstdio>

#include "Platform.h"
#include "Keyboard.h"
#include "UltrasonicNavigation.h"

Keyboard k;
Platform p;
UltrasonicNavigation us;

int main()
{
	us.initializeController();
	while (true)
	{
		us.print();
	}
    return 0;
}