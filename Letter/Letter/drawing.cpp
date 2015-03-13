
#include "drawing.h";


//COMMON FUNCTIONS --TODO, MOVE TO COMMON FUNC.CPP
double Common_Round(double num)	{
	return (num > 0.0) ? floor(num + 0.5) : ceil(num - 0.5);
}


//BUG #1 : for loops inside miss all pixels in between pixel intersections when theres more than 2 pixels to be drawn and X2>X1 or Y2>Y1 (backwards drawn lines)
//This bug happens because we are incrementing cX++ and cY++ instead of +dX, this also means we have to change the cX/cY to >= then x - 1, which complicates it further, is it even possible with 1 loop? 
void SDLCust::RenderDrawLine(SDL_Renderer *Renderer, float X1, float Y1, float X2, float Y2)	{
	int dX = (X1 < X2) ? 1 : -1;
	int dY = (Y1 < Y2) ? 1 : -1;
	float r = (X2 - X1) / (Y2 - Y1);
	for (int x = ceil(X1), oX = floor(X1); x <= floor(X2); x += dX, oX += dX)	{
		for (int cX = oX + 1; cX <= x + 1; cX ++)	{
			SDL_RenderDrawPoint(Renderer, cX, ceil((1 / r) * (x - X1) + Y1));
		}
	}
	for (int y = ceil(Y1), oY = floor(Y1); y <= floor(Y2); y += dY, oY += dY)	{
		for (int cY = oY + 1; cY <= y + 1; cY ++)	{
			SDL_RenderDrawPoint(Renderer, ceil(r * (y - Y1) + X1), cY);
		}
	}
}
//HERE IS THE CLEAN READABLE VERSION OF @MYTHANON DRAW LINE FUNCTION, COMPLETE
//
//void SDLCust::RenderDrawLine(SDL_Renderer *Renderer, float X1, float Y1, float X2, float Y2)	{
//	float dX = X2 - X1;
//	float dY = Y2 - Y1;
//	float rX = dX / dY;
//	float rY = dY / dX;
//	int oX = floor(X1), oY = floor(Y1);
//	for (int x = ceil(X1), y = ceil(Y1); x <= ceil(X2), y <= ceil(Y2); x++, y++)	{
//		float aY = ceil(rY * (x - X1) + Y1);
//		float aX = ceil(rX * (y - Y1) + X1);
//		for (int cX = oX + 1; cX <= x + 1; cX ++)	{
//			SDL_RenderDrawPoint(Renderer, cX, aY);
//		}
//		for (int cY = oY + 1; cY <= y + 1; cY ++)	{
//			SDL_RenderDrawPoint(Renderer, aX, cY);
//		}
//		oX = x;
//		oY = y;
//	}
//	
//}