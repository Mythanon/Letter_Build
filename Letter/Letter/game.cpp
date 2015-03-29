#include "game.h"










Game::Game(int l) : Level(l)	{
	if (Level != -1)	{
		InitLevel();
	}
}

Sprite Box;
float xVol = 0;
float yVol = 0;

void Game::InitLevel()	{
	Map = Sprite(0, 150);
	Map.AddLine(true, Position (0, 0), Position (1000, 0), Color(255, 255, 255), Color(255, 0, 0));
	Map.Update();
	Player = Sprite(50, 150);
	Player.AddTexture(true, Position (0, 0), Position (20, 20), "Textures/coin.png");

	//Based on level.... TODO:Initialize map (Add load from file, and build the file editor (map creator))
	/*Box = Drawing::Sprite(_colorProgram,  0, -0.5);
	Box.AddRect(Position (0, 0), Position (0.2, 0.2), Color(255, 0, 0), Color(255, 255, 0));*/

}



void Game::Draw()	{
	Map.Update();
	Box.Update();
	Player.Update();
}




void Game::KeyHandler(SDL_Event event)	{
	if (event.type == SDL_KEYDOWN)	{
		if (event.key.keysym.sym == SDLK_LEFT)	{
			xVol = -1;
		}else if (event.key.keysym.sym == SDLK_RIGHT)	{
			xVol = 1;
		}else if (event.key.keysym.sym == SDLK_SPACE)	{
			Player_Jump();
		}
	}else if (event.type == SDL_KEYUP)	{
		if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT)	{
			xVol = 0;
		}
	}
}

bool _playerJumping = false;
void Game::Step()	{
	Player.Move(xVol, yVol);
	if (Player.IsCollidedWith(Map) != false)	{

	}
	/*if (_playerJumping == true)	{
		yVol -= 0.000025;
		if (Player.Y <= Floor.Y)	{
			Player.Y = Floor.Y;
			yVol = 0;
			_playerJumping = false;
		}
	}*/
}









void Game::Player_Jump()	{
	_playerJumping = true;
	yVol = 0.003;
}