#include "errorHandler.h"

#include <iostream>
#include <SDL.h>

void FatalError(std::string ErrorString)	{
	std::cout << ErrorString << std::endl;
	std::cout << "Enter any key to quit...";
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
	exit(1);
}

