#include "game.h"










Game::Game(int l) : Level(l), _isJumping(false), _jumpKeyDown(false), Vel(0, 0)	{
	PixelsPerSecond = 60.0f / 1000.0f;
	accX = 0.2f; decX = 0.3f; //To simulate slow startup and slow slowdown movements. (We don't want instantaneous keydown movement; or do we?)
	maxVelX = 5.0f; maxVelY = 10.0f; //We need to make sure that speed gets capped.
	jumpInitialVel = 45.0f; //This is the initial jump velocity
	accY = 0.16f; //Dunno if we'll use this yet.

	Map = LevelMap();
	
	if (Level != -1)	{
		InitLevel(); //This will load whatever level is selected.
	}
}



void Game::InitLevel()	{
	//INITIALLIZE ALL OF THE LEVEL OBJECTS
	
	int test = Map.Container.AddSprite(Point(0, 0));
	Map.Container.Children[test].AddLine(true, Point (-2000, 150), Point (5000, 150), Color(255, 255, 255), Color(255, 0, 0));
	//Map.Container.Children[test].AddRect(true, Point (-2000, 0), Size (5000, 150), Color (255, 25, 2, 222));
	
	test = Map.Container.AddSprite(Point(300, 150));
	Map.Container.Children[test].AddRect(true, Point (0, 0), Size(50, 50), Color (192, 49, 222, 255));

	//test = Map.Container.AddSprite(Point(200, 250));
	//Map.Container.Children[test].AddRect(true, Point (0, 0), Size(50, 100), Color (192, 249, 222, 255));

	test = Map.Container.AddSprite(Point(200, 250));
	Map.Container.Children[test].AddTriangle(true, Point (0, 0), Point(100, 20), Point(50, 100), Color (192, 249, 222, 255));

	test = Map.Container.AddSprite(Point(400, 550));
	Map.Container.Children[test].AddRect(true, Point (0, 0), Size(50, 50), Color (92, 49, 222, 255));

	test = Map.Container.AddSprite(Point(200, 450));
	Map.Container.Children[test].AddRect(true, Point (0, 0), Size(25, 50), Color (192, 49, 22, 255));

	test = Map.Container.AddSprite(Point(220, 750));
	Map.Container.Children[test].AddRect(true, Point (0, 0), Size(50, 50), Color (22, 44, 222, 255));

	test = Map.Container.AddSprite(Point(100, 250));
	Map.Container.Children[test].AddRect(true, Point (0, 0), Size(50, 250), Color (244, 122, 93, 255));

	
	test = Map.Container.AddSprite(Point(100, 750));
	Map.Container.Children[test].AddRect(true, Point (0, 0), Size(50, 250), Color (244, 122, 93, 255));


	test = Map.Container.AddSprite(Point(-200, 150));
	Map.Container.Children[test].AddRect(true, Point(0, 0), Size(100, 1000), Color (120, 255, 0, 255));

	Player = Sprite(Point(50, 151));
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
			Vel.X = -10;
		}else if (event.key.keysym.sym == SDLK_RIGHT)	{
			Vel.X = 10;

		}else if (event.key.keysym.sym == SDLK_SPACE)	{
			if (!_jumpKeyDown)	{
				Player_Jump();
			}
		    _jumpKeyDown = true;
		}
	}else if (event.type == SDL_KEYUP)	{
		if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT)	{
			Vel.X = 0;
		}else if (event.key.keysym.sym == SDLK_SPACE)	{
			_jumpKeyDown = false;
		}
	}
}

bool _playerJumping = false;
Point safePoint;
Point scaledVel;
void Game::Step()	{
	Vel.Y -= accY ; //Apply gravity
	
	scaledVel = ScaleVelocityToFrameRate(Vel);
	for (size_t i = 1; i < Map.Container.Children.size(); i++)	{
		if (PredictCollision(Player, Map.Container.Children[i], scaledVel, &safePoint) == true)	{//WE COLLIDED
			scaledVel = safePoint;
			_isJumping = false;
		}
		//if (PredictCollision(Player, Map.Container.Children[i], Point (0, scaledVel.Y), &safePoint) == true)	{//WE COLLIDED
		//	scaledVel.Y = safePoint.Y;
		//	_isJumping = false;
		//}
	}
	if (PredictCollision(Player, Map.Container.Children[0], Point(0, scaledVel.Y), &safePoint) == true)	{
		scaledVel.Y = safePoint.Y;
		_isJumping = false;
	}

	Vel = UnScaleVelocityToFrameRate(scaledVel);
	Player.Move(Point (0, scaledVel.Y));
	Map.Container.Move(Point (-scaledVel.X, 0));
}




Point Game::ScaleVelocityToFrameRate(Point Vel)	{
	return Point(Vel.X * (float)FrameTimeElapsed * PixelsPerSecond, Vel.Y * (float)FrameTimeElapsed * PixelsPerSecond);
}Point Game::UnScaleVelocityToFrameRate(Point Vel)	{
	return Point(Vel.X / (float)FrameTimeElapsed / PixelsPerSecond, Vel.Y / (float)FrameTimeElapsed / PixelsPerSecond);
}




void Game::Player_Jump()	{
	if (!_isJumping)	{
		_isJumping = true;
		Vel.Y = jumpInitialVel;
	}
}