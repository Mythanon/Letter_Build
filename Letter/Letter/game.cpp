#include "game.h"










Game::Game(int l) : Level(l), _isJumping(false), _jumpKeyDown(false), Vel(0, 0)	{
	fScale = 60.0f / 1000.0f; //For 60FPS game steps. Leave the 1000.0f there, its required.
	accX = 0.2f; decX = 0.3f; //To simulate slow startup and slow slowdown movements. (We don't want instantaneous keydown movement; or do we?)
	maxVelX = 5.0f; maxVelY = 10.0f; //We need to make sure that speed gets capped.
	jumpInitialVel = 8.0f; //This is the initial jump velocity
	accY = 0.1f; //Dunno if we'll use this yet.

	Map = LevelMap();
	
	if (Level != -1)	{
		InitLevel(); //This will load whatever level is selected.
	}
}



void Game::InitLevel()	{
	//INITIALLIZE ALL OF THE LEVEL OBJECTS
	
	int test = Map.Container.AddSprite(Point(0, 0));
	Map.Container.Children[test].AddLine(false, Point (-2000, 150), Point (5000, 150), Color(255, 255, 255), Color(255, 0, 0));
	Map.Container.Children[test].AddRect(true, Point (-2000, 0), Size (5000, 150), Color (255, 25, 2, 222));
	test = Map.Container.AddSprite(Point(300, 150));
	Map.Container.Children[test].AddTriangle(true, Point(-50, -50), Point(50, 300), Point(100, 0), Color(0, 255, 0, 255));
	test = Map.Container.AddSprite(Point(100, 550));
	Map.Container.Children[test].AddTriangle(true, Point(0, 0), Point(50, 300), Point(100, 0), Color(255, 0, 0, 255));
	test = Map.Container.AddSprite(Point(200, 350));
	Map.Container.Children[test].AddTriangle(true, Point(0, 0), Point(50, 300), Point(100, 0), Color(255, 0, 0, 255));
	test = Map.Container.AddSprite(Point(600, 750));
	Map.Container.Children[test].AddTriangle(true, Point(0, 0), Point(50, 300), Point(100, 0), Color(255, 0, 0, 255));
	test = Map.Container.AddSprite(Point(800, 150));
	Map.Container.Children[test].AddTriangle(true, Point(0, 0), Point(50, 300), Point(100, 0), Color(255, 0, 0, 255));
	test = Map.Container.AddSprite(Point(-200, 150));
	Map.Container.Children[test].AddRect(true, Point(0, 0), Size(100, 1000), Color (120, 255, 0, 255));

	Player = Sprite(Point(50, 151));
	Player.AddTexture(true, Point (0, 0), Size (60, 60), "Textures/coin.png");
	Player.AddRect(false, Point(Player.CollisionField.BottomLeft.X - Player.Position.X, Player.CollisionField.BottomLeft.Y - Player.Position.Y), Player.CollisionField.Size, Color(255, 0, 0, 50));
	Player.PixelsPerSecond = fScale;
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
			Vel.X = -2;
		}else if (event.key.keysym.sym == SDLK_RIGHT)	{
			Vel.X = 2;
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
void Game::Step()	{
	Vel.Y -= accY ; //Apply gravity
	
	for (size_t i = 1; i < Map.Container.Children.size(); i++)	{
		
		if (Player.PredictCollision(Map.Container.Children[i], Vel, &safePoint) == true)	{//WE COLLIDED
			Vel = safePoint;
			//MOVE PLAYER BACK IN RESPECT TO WHERE THE COLLISION HAPPENED.
			_isJumping = false;
			//TODO REPLACE WITH PREDICT COLLISION CLASS PASSING IN THE NEW PLAYER POSITION VALUES. THUS GIVING US THE INFO TO MOVE THE PLAYER BACK JUST ENOUGH TO NOT BE COLLIDED ANYMORE
		}
	}
	if (Player.PredictCollision(Map.Container.Children[0], Point(0, Vel.Y), &safePoint) == true)	{
	//	Player.Position.Y = Map.Position.Y;
		Vel.Y = safePoint.Y;
		_isJumping = false;
	}
	Player.Move(Point (0, Vel.Y));
	Map.Container.Move(Point (-Vel.X, 0));
}









void Game::Player_Jump()	{
	if (!_isJumping)	{
		_isJumping = true;
		Vel.Y = 50;//jumpInitialVel;
	}
}