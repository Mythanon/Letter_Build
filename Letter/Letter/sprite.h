#pragma once
#ifndef DRAWING_H
#define DRAWING_H

#include "global.h"


#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <map>





struct CollisionData	{
	bool isCollided;
	Position Point;
};

//SPRITE CLASS
class Sprite	{
private :
	Color _dC;
	int _vC;
	bool _iN;
	struct _VertexContainer {
		std::vector<Position> Point;
		std::vector<Color> Color;
		GLTexture Texture;
		bool HasCollision;
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
	Sprite(float X = -1, float Y = -1, float Scale = 1, bool isNormalized = false);
	~Sprite();
	float X, Y, Scale;
	Color DrawColor;
	void Move(float X, float Y);
	void MoveTo(float X, float Y);
	void SetScale(float Scale);
	void SetColor(Color C);
	void AddLine(bool HasCollision, Position P1, Position P2, Color C1 = Color(0, 0, 0, 0, 1), Color C2 = Color(0, 0, 0, 0, 1));
	void AddTriangle(bool HasCollision, Position P1, Position P2, Position P3, Color C1 = Color(0, 0, 0, 0, 1), Color C2 = Color(0, 0, 0, 0, 1), Color C3 = Color(0, 0, 0, 0, 1));
	void AddRect(bool HasCollision, Position P1, Position P2, Color C1 = Color(0, 0, 0, 0, 1), Color C2 = Color(0, 0, 0, 0, 1));
	void AddTexture(bool HasCollision, Position P1, Position P2, std::string TexturePath);
	//void DrawCircle(float X, float Y, float R, int sheetId = -1);
	void Update();

	CollisionData IsCollidedWith(Sprite Sprite);
};





#endif