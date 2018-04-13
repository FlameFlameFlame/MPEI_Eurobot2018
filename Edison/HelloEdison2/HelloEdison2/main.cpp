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
	//using namespace std;
	//vector<int> distances;
	////distances = us.readUSArduino();
	//k.takeControl(&p);
	//k.startConsole();

	//us.initializeController();
	//while (true)
	//{
	//	k.control();
	//	distances = us.readUSArduino();
	//	for (auto i : distances)
	//		std::cout << i << ' ';
	//	std::cout << endl;
	//}
 //   return 0;


	k.startConsole();
	k.takeControl(&p);
	while (true)
	{
		//p.initializeDevice();
		k.control();
	}
	return 0;
}

