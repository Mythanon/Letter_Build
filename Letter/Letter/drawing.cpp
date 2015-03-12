
#include "SDL.h"
#include "SDL_opengl.h"
#include <math.h>

//COMMON FUNCTIONS --TODO, MOVE TO COMMON FUNC.CPP
double Common_Round(double num)	{
	return (num > 0.0) ? floor(num + 0.5) : ceil(num - 0.5);
}


void SDLCust_SetRenderDrawLine(SDL_Renderer *Renderer, int X1, int Y1, int X2, int Y2)	{
	SDL_SetRenderDrawColor(Renderer, 0xFF, 0x00, 0xFF, 0xFF);
	float diffX = X2 - X1;
	float diffY = Y2 - Y1;
	float ratioX = diffY / diffX;
	float ratioY = diffX / diffY;
	int amountOfPixels = (diffX + diffY) / 2;

	for (int i = 1; i <= amountOfPixels; i++)	{
		int x = (int)Common_Round(X1 + (i * ratioX));
		int y = (int)Common_Round(Y1 + (i * ratioY));
		SDL_RenderDrawPoint(Renderer, x, y);
	}

}