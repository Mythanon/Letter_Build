#pragma once
#ifndef GAME_H
#define GAME_H

#include "global.h"


class Game	{
private:
	bool _isJumping, _jumpKeyDown; //To prevent mid-air jumping and to prevent automatic jump on land from jump key from being held 




public:
	struct MapObject	{
		Position Location;
		Size Size;
		SpriteType Type;
	};
	struct MapData	{
		std::vector<Sprite> ObjectList;


	};

	int Level;
	Game(int Level = -1);
	
	Sprite Player;
	Sprite Map;
	
	void InitLevel();
	void Draw();
	void KeyHandler(SDL_Event event);
	void Step();

	void Player_Jump();

	float fScale;
	float velX, velY;
	float accX, decX;
	float maxVelX, maxVelY;

	float jumpInitialVel;
	float accY;

};





#endif