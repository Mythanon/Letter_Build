#pragma once
#ifndef DRAWING_H
#define DRAWING_H

#include "SDL.h"
#include "glew.h"
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <vector>
//#include <unordered_map>
//#include <map>
//#include <vector>

#include "errorHandler.h"
#include "picoPNG.h"
#include "IOManager.h"

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


class Drawing{
public:	
	struct GLTexture	{GLuint id; int width, height; };
	class ImageLoader	{
	public: 
		static GLTexture loadPNG(std::string filePath);
	};


	//SHADER CLASS
	class GLSL	{
	private:
		GLuint _programId;
		GLuint _vertexShaderId;
		GLuint _fragmentShaderId;

		void compileShader(const std::string& filePath, GLuint Id);
		int _numAttributes;
	public:
		GLSL();
		~GLSL();

		GLuint uni_time, uni_isTexture, uni_curTexture;

		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		void linkShaders();
		void addAttribute(const std::string& attributeName);

		GLuint getUniformLocation(const std::string& uniformName);
		void loadUniformLocations();

		void use();
		void unuse();
	};








	//SPRITE CLASS
	class Sprite	{
	private :
		GLSL _cP;
		Color _dC;
		int _vC;
		struct _VertexContainer {
			std::vector<Position> Point;
			std::vector<Color> Color;
			GLTexture Texture;
			int Type;
			int Size;
			GLuint vboID;
		};
		std::vector<_VertexContainer> _vList;

		void _UpdateList();
		void _DrawLine(int vId);
		void _DrawTriangle(int vId);
		void _DrawRect(int vId);
		void _DrawTexture(int vId);
	public :
		Sprite(GLSL& ColorProgram = GLSL(), float X = -1, float Y = -1, float Scale = 1);
		~Sprite();
		float X, Y, Scale;
		Color DrawColor;
		void Move(float X, float Y);
		void MoveTo(float X, float Y);
		void SetScale(float Scale);
		void SetColor(Color C);
		void AddLine(Position P1, Position P2, Color C1 = Color(0, 0, 0, 0, 1), Color C2 = Color(0, 0, 0, 0, 1));
		void AddTriangle(Position P1, Position P2, Position P3, Color C1 = Color(0, 0, 0, 0, 1), Color C2 = Color(0, 0, 0, 0, 1), Color C3 = Color(0, 0, 0, 0, 1));
		void AddRect(Position P1, Position P2, Color C1 = Color(0, 0, 0, 0, 1), Color C2 = Color(0, 0, 0, 0, 1));
		void AddTexture(Position P1, Position P2, GLTexture Texture);
		//void DrawCircle(float X, float Y, float R, int sheetId = -1);
		void Update();
	};




};





#endif