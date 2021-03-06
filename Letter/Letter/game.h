#pragma once
#include "global.h"

#ifndef GAME_H
#define GAME_H



class Game	{
private:
	bool _isJumping, _jumpKeyDown; //To prevent mid-air jumping and to prevent automatic jump on land from jump key from being held 




public:
	struct MapObject	{
		Point Location;
		Size Size;
		SpriteType Type;
	};
	struct MapData	{
		std::vector<Sprite> ObjectList;


	};

	int Level;
	Game(int Level = -1);
	
	Sprite Player;
	LevelMap Map;

	void InitLevel();
	void Draw();
	void KeyHandler(SDL_Event event);
	void Step();

	void Player_Jump();
	//Point ScaleVelocityToFrameRate(Point Vel);
	//Point UnScaleVelocityToFrameRate(Point Vel);
	//float PixelsPerSecond; //This is to scale the velocity down based on how fast the frame rate is, to keep moving at the same rate/second no matter what the FPS is.
	float Gravity;
	float Controls_XVel;


	float accX, decX;
	float maxVelX, maxVelY;

	float jumpInitialVel;

};





#endif