#pragma once
#include "global.h"

#include "game.h"



enum class GameState {INTRO, INTROMENU, LOADSCREEN, PLAY, MENU, CREDIT, EXIT};


class GameObject	{
private:
	GameState _gameState;
	bool _gameStateLoaded;
	float _FPS;

public:
	GameObject();
	void Run();
	void Init();
	void Loop();
	void DrawScreen();
	void ProcessInput();
	void GameStep();


	SDL_Event event;

	Game game;

};








