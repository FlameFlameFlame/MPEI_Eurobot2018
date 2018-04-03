#include "controller.h"
#include <ncurses.h>

int Controller::takeControl()
{
	printw("Cannot takeControl for base Controller \n");
	return -1;
}

void Controller::releaseAll()
{
	printw("Cannot releaseAll for base Controller \n");
}

void Controller::releaseDevice()
{
	printw("Cannot releaseDevice for base Controller \n");
}

int Controller::initializeController()
{
	printw("Cannot initializeController for base Controller \n");
	return -1;
}