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
	Point ReturnPoint;
};

enum class SpriteType {LINE, TRIANGLE, RECT, TEXTURE, CIRCLE};

//SPRITE CLASS
class Sprite	{
private :
	Color _dC;
	int _vC;
	bool _iN;
	struct _ElementObject {
		std::vector<Point> Point;
		std::vector<Color> Color;
		GLTexture Texture;
		bool HasCollision;
		SpriteType Type;
		int Size;
		GLuint vboID;
	};
	std::vector<_ElementObject> _vList;
	int _collisionObjId;
	struct _CollisionFieldObject	{
		Point BottomLeft; //Base border of object
		Point TopRight;
		Size Size;
		SpriteType Type;
	};
	void _AdjustCollisionField(std::vector<Point> Points);

	Point _scaleMoveToFrame(Point Transition);
	void _UpdateList();
	void _DrawObject(int vId);
public :
	Sprite(Point Position = Point(0, 0), float Scale = 1, bool isNormalized = false);
	~Sprite();
	Point Position;
	float Scale, PixelsPerSecond;
	Color DrawColor;
	_CollisionFieldObject CollisionField;
	void Move(Point OffsetPoint);
	void MoveTo(Point NewPoint);
	void SetScale(float Scale);
	void SetColor(Color C);
	std::vector<Sprite> Children;
	int AddSprite(Point Position = Point(0, 0), float Scale = 1, bool isNormalized = false);
	int AddLine(bool HasCollision, Point P1, Point P2, Color C1 = Color(0, 0, 0, 0, 1), Color C2 = Color(0, 0, 0, 0, 1));
	int AddTriangle(bool HasCollision, Point P1, Point P2, Point P3, Color C1 = Color(0, 0, 0, 0, 1), Color C2 = Color(0, 0, 0, 0, 1), Color C3 = Color(0, 0, 0, 0, 1));
	int AddRect(bool HasCollision, Point Position, Size Size, Color C1 = Color(0, 0, 0, 0, 1), Color C2 = Color(0, 0, 0, 0, 1));
	int AddTexture(bool HasCollision, Point Position, Size Size, std::string TexturePath);
	//void DrawCircle(float X, float Y, float R, int sheetId = -1);
	void Update();
	void UpdateChildren();
	void SetCollisionObject(int ObjectId);
	CollisionData PredictCollision(Sprite CompareTo, Point Transition); 
//	CollisionData IsCollidedWith(Sprite Sprite);
};





#endif