#pragma once
#ifndef GAME_H
#define GAME_H

#include "global.h"


class Game	{
private:




public:
	struct MapObject	{
		Position Location;
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

};





#endif