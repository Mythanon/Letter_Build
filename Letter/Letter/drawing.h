#ifndef DRAWING_H
#define DRAWING_H

#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include <string>
#include <math.h>
#include <unordered_map>
#include <map>
#include <vector>

class SDLCust{


public:	
	void RenderDrawLine(SDL_Renderer *Renderer, float X1, float Y1, float X2, float Y2);
	void RenderDrawCircle(SDL_Renderer *Renderer, float X, float Y, float R);
	class RenderSprite	{
	private :
		Uint8 cR, cG, cB, cA;
		std::map<std::pair<int, int>, int> p;
	public :
		float X, Y, Width, Height;
		SDL_Renderer *Renderer;
		class PixelSheet {
		public :
			int X, Y;
			Uint8 R, G, B, A;
			std::vector<std::pair<int, int>> p;
			PixelSheet(int X = 0, int Y = 0);
		};
		std::vector<PixelSheet> Sheet;
		RenderSprite(SDL_Renderer *Renderer, float XPos = 0, float YPos = 0, float Width = 0, float Height = 0);
		void SetColor(Uint8 R, Uint8 G, Uint8 B, Uint8 A);
		void DrawLine(float X1, float Y1, float X2, float Y2);
		void DrawCircle(float X, float Y, float R);
		void Move(float X, float Y);
		void Update();
		void ToScreen();
	};
};





#endif