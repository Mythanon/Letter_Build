#include "game.h"










Game::Game(int l) : Level(l), _isJumping(false), _jumpKeyDown(false)	{
	PixelsPerSecond = 60.0f / 1000.0f;
	accX = 0.2f; decX = 0.3f; //To simulate slow startup and slow slowdown movements. (We don't want instantaneous keydown movement; or do we?)
	maxVelX = 5.0f; maxVelY = 10.0f; //We need to make sure that speed gets capped.
	jumpInitialVel = 4500.0f; //This is the initial jump velocity
	Gravity = 0.00016f; //Dunno if we'll use this yet.

	Map = LevelMap();
	Map.Container = Sprite(Point(0, 150));
	
	Controls_XVel = 0;

	if (Level != -1)	{
		InitLevel(); //This will load whatever level is selected.
	}
}



void Game::InitLevel()	{
	//INITIALLIZE ALL OF THE LEVEL OBJECTS
	
	int test = Map.Container.AddSprite(Point(0, 0));
	Map.Container.Children[test].AddLine(true, Point (-2000, 0), Point (5000, 0), Color(255, 255, 255), Color(255, 0, 0));
	//Map.Container.Children[test].AddRect(true, Point (-2000, 0), Size (5000, 150), Color (255, 25, 2, 222));
	
	//test = Map.Container.AddSprite(Point(300, 150));
	//Map.Container.Children[test].AddRect(true, Point (0, 0), Size(50, 50), Color (192, 49, 222, 255));

	////test = Map.Container.AddSprite(Point(200, 250));
	////Map.Container.Children[test].AddRect(true, Point (0, 0), Size(50, 100), Color (192, 249, 222, 255));

	test = Map.Container.AddSprite(Point(220, 0));
	Map.Container.Children[test].AddTriangle(true, Point (0, 0), Point(100, 20), Point(50, 100), Color (192, 249, 222, 255));

	//test = Map.Container.AddSprite(Point(400, 550));
	//Map.Container.Children[test].AddRect(true, Point (0, 0), Size(50, 50), Color (92, 49, 222, 255));

	//test = Map.Container.AddSprite(Point(200, 450));
	//Map.Container.Children[test].AddRect(true, Point (0, 0), Size(25, 50), Color (192, 49, 22, 255));

	//test = Map.Container.AddSprite(Point(220, 750));
	//Map.Container.Children[test].AddRect(true, Point (0, 0), Size(50, 50), Color (22, 44, 222, 255));

	//test = Map.Container.AddSprite(Point(100, 250));
	//Map.Container.Children[test].AddRect(true, Point (0, 0), Size(50, 250), Color (244, 122, 93, 255));

	//
	//test = Map.Container.AddSprite(Point(100, 750));
	//Map.Container.Children[test].AddRect(true, Point (0, 0), Size(50, 250), Color (244, 122, 93, 255));


	//test = Map.Container.AddSprite(Point(-200, 150));
	//Map.Container.Children[test].AddRect(true, Point(0, 0), Size(100, 1000), Color (120, 255, 0, 255));

	Player = Sprite(Point(50, 151));
	Player.Weight = 100;
	Player.AddTexture(true, Point (0, 0), Size (40, 40), "Textures/coin.png");
	Player.AddRect(false, Point(Player.CollisionField.BottomLeft.X - Player.Position.X, Player.CollisionField.BottomLeft.Y - Player.Position.Y), Player.CollisionField.Size, Color(255, 0, 0, 30));
	//Based on level.... TODO:Initialize map (Add load from file, and build the file editor (map creator))
}



void Game::Draw()	{
	Map.Container.Update();
	Map.Container.UpdateChildren();
	Player.Update();
}





void Game::KeyHandler(SDL_Event event)	{
	if (event.type == SDL_KEYDOWN)	{
		if (event.key.keysym.sym == SDLK_LEFT)	{
			Controls_XVel = -10;
		}else if (event.key.keysym.sym == SDLK_RIGHT)	{
			Controls_XVel = 10;

		}else if (event.key.keysym.sym == SDLK_SPACE)	{
			if (!_jumpKeyDown)	{
				Player_Jump();
			}
		    _jumpKeyDown = true;
		}
	}else if (event.type == SDL_KEYUP)	{
		if ((event.key.keysym.sym == SDLK_LEFT && Controls_XVel == -10) || (event.key.keysym.sym == SDLK_RIGHT && Controls_XVel == 10))	{
			Controls_XVel = 0;
		}else if (event.key.keysym.sym == SDLK_SPACE)	{
			_jumpKeyDown = false;
		}
	}
}

bool _playerJumping = false;
void Game::Step()	{
	Player.SetVelocityX(Controls_XVel);
	Player.ApplyGravity(Gravity);
	std::cout << Player.Velocity.Y << std::endl;
	//Sleep(100);
	//At this point, the velocity of each point of the player should be set correctly.


	for (size_t i = 0; i < Map.Container.Children.size(); i++)	{
		if (HandleCollision(Player, Map.Container.Children[i]) == true)	{//WE COLLIDED
			_isJumping = false;
		}else	{
			Player.Move(Point (0, Player.Velocity.Y));
			Map.Container.Move(Point (-Player.Velocity.X, 0));
		}
	}


}



void Game::Player_Jump()	{
	if (!_isJumping)	{
		_isJumping = true;
		Player.SetVelocity(Point (Player.Velocity.X, jumpInitialVel));
	}
}