#include <cstdio>

#include "Platform.h"
#include "Keyboard.h"
#include "UltrasonicNavigation.h"
#include <vector>

Keyboard k;
Platform p;
UltrasonicNavigation us;

int main()
{
	using namespace std;
	vector<int> distances;
	distances = us.readUSArduino();
	float k; //coefficient for driving by the wall

	us.initializeController();
	while (true)
	{
		us.print();
	}
    return 0;
}

