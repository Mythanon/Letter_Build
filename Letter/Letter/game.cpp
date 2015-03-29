#include "game.h"










Game::Game(int l) : Level(l), _isJumping(false), _jumpKeyDown(false), velX(0.0f), velY(0.0f)	{
	fScale = 60.0f; //For 60FPS game steps.
	accX = 0.2f; decX = 0.3f; //To simulate slow startup and slow slowdown movements. (We don't want instantaneous keydown movement; or do we?)
	maxVelX = 5.0f; maxVelY = 10.0f; //We need to make sure that speed gets capped.
	jumpInitialVel = 8.0f; //This is the initial jump velocity
	accY = 0.5f; //Dunno if we'll use this yet.

	
	
	if (Level != -1)	{
		InitLevel(); //This will load whatever level is selected.
	}
}

Sprite Box;


void Game::InitLevel()	{
	//INITIALLIZE ALL OF THE LEVEL OBJECTS
	
	Map = Sprite(0, 150);
	Map.AddLine(true, Position (0, 0), Position (1000, 0), Color(255, 255, 255), Color(255, 0, 0));

	Map.Update();
	Player = Sprite(50, 150);
	Player.AddTexture(true, Position (0, 0), Position (20, 20), "Textures/coin.png");
	Player.PixelsPerSecond = fScale;
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
			velX = -15;
		}else if (event.key.keysym.sym == SDLK_RIGHT)	{
			velX = 15;
		}else if (event.key.keysym.sym == SDLK_SPACE)	{
			if (!_jumpKeyDown)	{
				Player_Jump();
			}
		    _jumpKeyDown = true;
		}
	}else if (event.type == SDL_KEYUP)	{
		if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT)	{
			velX = 0;
		}else if (event.key.keysym.sym == SDLK_SPACE)	{
			_jumpKeyDown = false;
		}
	}
}

bool _playerJumping = false;
void Game::Step()	{
	Player.Move(velX, velY);
	velY -= accY; //Apply gravity
	CollisionData curCollision = Player.IsCollidedWith(Map);
	if (curCollision.isCollided != false)	{ //WE COLLIDED
		//MOVE PLAYER BACK IN RESPECT TO WHERE THE COLLISION HAPPENED.

		//TODO REPLACE WITH PREDICT COLLISION CLASS PASSING IN THE NEW PLAYER POSITION VALUES. THUS GIVING US THE INFO TO MOVE THE PLAYER BACK JUST ENOUGH TO NOT BE COLLIDED ANYMORE
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
	if (!_isJumping)	{
		_isJumping = true;
		velY = 50;
	}
}