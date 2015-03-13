#ifndef DRAWING_H
#define DRAWING_H

#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include <string>
#include <math.h>

class SDLCust{


public:	
	void RenderDrawLine(SDL_Renderer *Renderer, float X1, float Y1, float X2, float Y2);

};





#endif