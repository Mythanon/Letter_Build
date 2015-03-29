#pragma once
#ifndef GLOBAL_H
#define GLOBAL_H

#include <Windows.h>
#include <SDL.h>
#include "glew.h"
#include "SOIL.h"

#include <iostream>
#include <string>
#include <stdio.h>

struct ScreenResolution {int Width, Height; float Ratio;};

struct Position{float X, Y;
Position (float X = 0, float Y = 0)	: X(X), Y(Y)	{}
};
struct Color	{GLubyte R, G, B, A; bool isEmpty; 
Color(GLubyte R = 0, GLubyte G = 0, GLubyte B = 0, GLubyte A = 255, bool empty = 0) : R(R), G(G), B(B), A(A), isEmpty(empty)	{}
};
struct UV {float U, V;
UV(float U = 0, float V = 0) : U(U), V(V)	{}
};

struct Vertex	{Position Position; Color Color; UV UV;};



#include "GLSL.h"
#include "errorHandler.h"
#include "resourceManager.h"
#include "IOManager.h"
#include "sprite.h"





extern SDL_Window *SDLWindow;
extern ScreenResolution ScreenRes;
extern GLSL ColorProgram;
extern float RunTime, Time;
extern ResourceManager Resources;







#endif