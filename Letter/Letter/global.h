#pragma once
#ifndef GLOBAL_H
#define GLOBAL_H

//CORE COMPONENT INCLUDES
#include <Windows.h>
#include <SDL.h>
#include "glew.h"
#include "SOIL.h"

//BUILT IN C++ INCLUDES
#include <iostream>
#include <string>


//COMMON STRUCTS THAT ARE GLOBALLY ACCESSIBLE
struct ScreenResolution {int Width, Height; float Ratio;};
struct Size{float Width, Height;
Size (float Width = 1, float Height = 1)	: Width(Width), Height(Height)	{}
};
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


//CUSTOM GLOBALLY NEEDED CLASSES
#include "GLSL.h" //Graphics Buffering Class
#include "errorHandler.h" 
#include "resourceManager.h" //Manages reusable textures etc
#include "IOManager.h" 
#include "sprite.h"





extern SDL_Window *SDLWindow;
extern ScreenResolution ScreenRes;
extern GLSL ColorProgram;
extern Uint32 RunTime, Time, FrameTimeElapsed;
extern ResourceManager Resources;







#endif