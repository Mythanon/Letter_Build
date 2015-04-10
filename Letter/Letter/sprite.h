#pragma once
#include "global.h"

#ifndef DRAWING_H
#define DRAWING_H

enum class SpriteType {LINE, TRIANGLE, RECT, TEXTURE, CIRCLE};
//struct SpritePoint	{
//	float X, Y;
//	float Weight;
//	Velocity Velocity;
//	Color Color;
//	SpritePoint (float X = 0, float Y = 0)	: X(X), Y(Y)	{}
//};

//SPRITE CLASS
class Sprite	{
private :
	Color _dC;
	int _vC;
	bool _iN;
	int _collisionObjId;
	struct _CollisionFieldObject	{
		Point BottomLeft; //Base border of object
		Point TopRight;
		Size Size;
		SpriteType Type;
	};
	void _AdjustCollisionField(std::vector<Point> Points);
	struct _CollisionDetectReturn {bool Collided; Point Point;};

	Point _scaleMoveToFrame(Point Transition);
	void _UpdateList();
	void _DrawObject(int vId);
public :
	Sprite(Point Position = Point(0, 0), float Scale = 1, bool IsFixed = true, bool isNormalized = false);
	~Sprite();
	Point Position;
	float Scale;
	float Weight;
	Point Velocity;
	bool Fixed;
	Color DrawColor;
	_CollisionFieldObject CollisionField;
	void Move(Point OffsetPoint);
	void MoveTo(Point NewPoint);
	void SetScale(float Scale);
	void SetWeight(float Weight);
	void SetColor(Color C);
	void SetVelocity(Point Velocity);
	void SetVelocityX(float XVelocity);
	void SetVelocityY(float YVelocity);
	void ApplyGravity(float Gravity);
	struct ElementObject {
		std::vector<Point> Velocity;
		std::vector<Point> Point;
		std::vector<Color> Color;
		GLTexture Texture;
		bool HasCollision;
		SpriteType Type;
		int Size;
		GLuint vboID;
	};
	std::vector<Sprite> Children;
	std::vector<ElementObject> Element;
	int AddSprite(Point Position = Point(0, 0), float Scale = 1, bool isNormalized = false);
	int AddLine(bool HasCollision, Point P1, Point P2, Color C1 = Color(0, 0, 0, 0, 1), Color C2 = Color(0, 0, 0, 0, 1));
	int AddTriangle(bool HasCollision, Point P1, Point P2, Point P3, Color C1 = Color(0, 0, 0, 0, 1), Color C2 = Color(0, 0, 0, 0, 1), Color C3 = Color(0, 0, 0, 0, 1));
	int AddRect(bool HasCollision, Point Position, Size Size, Color C1 = Color(0, 0, 0, 0, 1), Color C2 = Color(0, 0, 0, 0, 1));
	int AddTexture(bool HasCollision, Point Position, Size Size, std::string TexturePath);
	//void DrawCircle(float X, float Y, float R, int sheetId = -1);
	void Update();
	void UpdateChildren();
	void SetCollisionObject(int ObjectId);
};


float LineLength(Point LinePointA, Point LinePointB);
bool LineIntersection(Point Line1A, Point Line1B, Point Line2A, Point Line2B, Point *IntersectPoint);
bool isPointOnLine (Point ThePoint, Point LineA, Point LineB);
bool PredictCollision(Sprite CompareFrom, Sprite CompareTo, Point Transition, Point *SafeTransition, float *Angle);
bool HandleCollision(Sprite CompareFrom, Sprite CompareTo);








#include "levelMap.h"
#include "userInterface.h"


#endif