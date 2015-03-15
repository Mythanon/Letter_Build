
#include "drawing.h";
#include <unordered_map>
#include <map>
#include <vector>


//COMMON FUNCTIONS --TODO, MOVE TO COMMON FUNC.CPP
double Common_Round(double num)	{
	return (num > 0.0) ? floor(num + 0.5) : ceil(num - 0.5);
}



//RENDER SPRITE INITIALIZEr
SDLCust::RenderSprite::RenderSprite(SDL_Renderer *R, float XPos, float YPos, float W, float H)	{
	Renderer = R; X = XPos; Y = YPos; Width = W; Height = H;
}
//CONSTRUCTOR FOR INDIVIDUAL PIXEL SHEETS
SDLCust::RenderSprite::PixelSheet::PixelSheet(int nX, int nY)	{
	X = nX; Y = nY;
}

void SDLCust::RenderSprite::SetColor(Uint8 R, Uint8 G, Uint8 B, Uint8 A)	{
	cR = R; cG = G; cB = B; cA = A;
}

//LINE MAPPER, WILL ADD COORDISPONDING PIXELS TO A PIXELSHEET FOR DRAWING ON RENDERUPDATE
void SDLCust::RenderSprite::DrawLine(float X1, float Y1, float X2, float Y2)	{
	Sheet.push_back(PixelSheet(X1, Y1));
	Sheet[Sheet.size() - 1].R = cR;	Sheet[Sheet.size() - 1].G = cG; Sheet[Sheet.size() - 1].B = cB; Sheet[Sheet.size() - 1].A = cA;
	float xI = 0, yI = 0, r = (X2 - X1) / (Y2 - Y1);
	if (X1 > X2)	{xI = X1; X1 = X2; X2 = xI - 1; xI = X2 - X1 + 1;}
	for (int x = ceil(X1) + ((xI == 0 || (xI != 0 && Y1 > Y2)) ? 1 : 0) + ((Y1 < Y2) ? 0 : -1), oX = x - 1; x < floor(X2) + ((xI != 0 && Y1 > Y2) ? 1 : 0); x ++, oX ++)
		for (int cX = oX + 1; cX <= x + 1; cX ++)	
			Sheet[Sheet.size() - 1].p.push_back(std::make_pair(cX - X1, ceil((1 / r) * (x - X1 - xI) + Y1 + yI) - Y1));
	if (xI != 0)	{xI = X1; X1 = X2 + 1; X2 = xI;}
	if (Y1 > Y2)	{yI = Y1; Y1 = Y2; Y2 = yI; yI = Y2 - Y1;}
	for (int y = ceil(Y1), oY = y - 1; y < floor(Y2); y ++, oY ++)	
		for (int cY = oY + 1; cY <= y + 1; cY ++)
			Sheet[Sheet.size() - 1].p.push_back(std::make_pair(ceil(r * (y - Y1 - yI) + X1) - X1, cY - Y1));
}
void SDLCust::RenderSprite::DrawCircle(float X, float Y, float R)	{
	Sheet.push_back(PixelSheet(X - R, Y - R));
	for(int cY = -R; cY <= R; cY++)
		for(int cX =-R; cX <=R; cX ++)
			if(cX * cX + cY * cY <= R * R + R * 0.8f)
				Sheet[Sheet.size() - 1].p.push_back(std::make_pair(cX + R, cY + R));
}


void SDLCust::RenderSprite::Move(float XPos, float YPos)	{
	X = XPos; Y = YPos;
	//Update();
}

void SDLCust::RenderSprite::Update()	{
	float sX, sY;
	for (int i = 0; i < Sheet.size(); i++)	{
		SDL_SetRenderDrawColor(Renderer, Sheet[i].R, Sheet[i].G, Sheet[i].B, Sheet[i].A);
			for (int pI = 0; pI < Sheet[i].p.size(); pI ++)	{
			//p[std::make_pair(Sheet[i].p[pI].first + Sheet[i].X, Sheet[i].p[pI].second + Sheet[i].Y)] = i;
			SDL_RenderDrawPoint(Renderer, Sheet[i].p[pI].first + Sheet[i].X + X, Sheet[i].p[pI].second + Sheet[i].Y + Y);
		}
	}
}
//REALLY NEED TO MAKE THIS BETTER FOR COLOR CHECKING!!!
void SDLCust::RenderSprite::ToScreen()	{
	Uint8 oR = 0x00, oG = 0x00, oB = 0x00, oA = 0x00;
	for(auto cP = p.begin(); cP != p.end(); cP++) {
		/*if (Sheet[cP->second].r != oR || Sheet[cP->second].g != oG || Sheet[cP->second].b != oB || Sheet[cP->second].a != oA)	{
			oR = Sheet[cP->second].r; oG = Sheet[cP->second].g; oB = Sheet[cP->second].b; oA = Sheet[cP->second].a;
			SDL_SetRenderDrawColor(Renderer, oR, oG, oB, oA);
		}*/
		SDL_RenderDrawPoint(Renderer, cP->first.first + X, cP->first.second + Y);
	}
}


//CUSTOM DRAW LINE BY PIXEL FUNCTION (RASTERIZED) 100% PIXEL PERCISION (NOTE: Subpixels round up.)
void SDLCust::RenderDrawLine(SDL_Renderer *Renderer, float X1, float Y1, float X2, float Y2)	{
	float xI = 0, yI = 0, r = (X2 - X1) / (Y2 - Y1);
	if (X1 > X2)	{xI = X1; X1 = X2; X2 = xI - 1; xI = X2 - X1 + 1;}
	for (int x = ceil(X1) + ((xI == 0 || (xI != 0 && Y1 > Y2)) ? 1 : 0) + ((Y1 < Y2) ? 0 : -1), oX = x - 1; x < floor(X2) + ((xI != 0 && Y1 > Y2) ? 1 : 0); x ++, oX ++)
		for (int cX = oX + 1; cX <= x + 1; cX ++)	
			SDL_RenderDrawPoint(Renderer, cX, ceil((1 / r) * (x - X1 - xI) + Y1 + yI));
	if (xI != 0)	{xI = X1; X1 = X2 + 1; X2 = xI;}
	if (Y1 > Y2)	{yI = Y1; Y1 = Y2; Y2 = yI; yI = Y2 - Y1;}
	for (int y = ceil(Y1), oY = y - 1; y < floor(Y2); y ++, oY ++)	
		for (int cY = oY + 1; cY <= y + 1; cY ++)	
			SDL_RenderDrawPoint(Renderer, ceil(r * (y - Y1 - yI) + X1), cY);
}

//CUSTOM DRAW CIRCLE BY PIXEL FUNCTION (RASTERIZED) 100% PIXEL PERCISION AS WELL >> This completes by treating circle like a box, and filling in pixels if the 
//																					distance from the point to draw is <= radius (and 0.8f for pixel precision fix)
void SDLCust::RenderDrawCircle(SDL_Renderer *Renderer, float X, float Y, float R)	{
	for(int cY = -R; cY <= R; cY++)
		for(int cX =-R; cX <=R; cX ++)
			if(cX * cX + cY * cY <= R * R + R * 0.8f)
				SDL_RenderDrawPoint(Renderer, X + cX, Y + cY);
}