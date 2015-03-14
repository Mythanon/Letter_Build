
#include "drawing.h";


//COMMON FUNCTIONS --TODO, MOVE TO COMMON FUNC.CPP
double Common_Round(double num)	{
	return (num > 0.0) ? floor(num + 0.5) : ceil(num - 0.5);
}


//BUG : Working quite well, each possibility :
//(1, 2), (2, 1)
//(2, 1), (1, 2)
//(2, 2), (1, 1)
//In those variations end with a leading and/or trailing additional pixel.
//This can be fixed with a couple if statements modifying the begin/end x/y in each for loop with a +1 depending on the condition.
//Consider this function complete.
void SDLCust::RenderDrawLine(SDL_Renderer *Renderer, float X1, float Y1, float X2, float Y2)	{
	float xI = 0, yI = 0, r = (X2 - X1) / (Y2 - Y1);
	if (X1 > X2)	{xI = X1; X1 = X2; X2 = xI - 1; xI = X2 - X1 + 1;}
	for (int x = ceil(X1), oX = x - 1; x < floor(X2); x ++, oX ++)	{
		for (int cX = oX + 1; cX <= x + 1; cX ++)	{
			SDL_RenderDrawPoint(Renderer, cX, ceil((1 / r) * (x - X1 - xI) + Y1 + yI));
		}
	}
	if (xI != 0)	{xI = X1; X1 = X2 + 1; X2 = xI;}
	if (Y1 > Y2)	{yI = Y1; Y1 = Y2; Y2 = yI; yI = Y2 - Y1;}
	for (int y = ceil(Y1), oY = y - 1; y < floor(Y2); y ++, oY ++)	{
		for (int cY = oY + 1; cY <= y + 1; cY ++)	{
			SDL_RenderDrawPoint(Renderer, ceil(r * (y - Y1 - yI) + X1), cY);
		}
	}
}