
#include "drawing.h";

//COMMON FUNCTIONS --TODO, MOVE TO COMMON FUNC.CPP
double Common_Round(double num)	{
	return (num > 0.0) ? floor(num + 0.5) : ceil(num - 0.5);
}



void SDLCust::RenderDrawLine(SDL_Renderer *Renderer, float X1, float Y1, float X2, float Y2)	{
	SDL_SetRenderDrawColor(Renderer, 0xFF, 0x00, 0xFF, 0xFF);
	float dX = X2 - X1;
	float dY = Y2 - Y1;
	float rX = dX / dY;
	float rY = dY / dX;

	bool firstPixelFlag = true;
	for (float x = X1, y = Y1; x <= X2, y <= Y2; x += rX, y += rY)	{
		int oldX = (int)floor(x - rX);
		int newX = (int)floor(x);
		int oldY = (int)floor(y - rY);
		int newY = (int)floor(y);
		if (firstPixelFlag == false)	{
			if (newX != oldX)	{
				float aY = (((newX - X1) * rX) + ((y - Y1) * rY));
				std::cout << "X-intersect: " << newX << ", Y: " << ((newX) * rX) << "\n";

				SDL_RenderDrawPoint(Renderer, oldX, newY);
				SDL_RenderDrawPoint(Renderer, newX, newY);
			}

			if (newY != oldY)	{
				std::cout << "Y: " << newY << "\n";
				SDL_RenderDrawPoint(Renderer, oldX, oldY);
				SDL_RenderDrawPoint(Renderer, oldX, newY);
			}
		}
		firstPixelFlag = false;
	}

	
	/*float diffX = X2 - X1;
	float diffY = Y2 - Y1;
	float ratioX = diffX / diffY;
	float ratioY = diffY / diffX;
	int amountOfPixels = (diffX + diffY) / 2;

	for (int i = 0; i < amountOfPixels; i++)	{
		int x = (int)Common_Round(X1 + (i * ratioX));
		int y = (int)Common_Round(Y1 + (i * ratioY));
		SDL_RenderDrawPoint(Renderer, x, y);
	}*/

}