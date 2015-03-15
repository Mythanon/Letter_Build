

//DEFAULT INCLUDES

#include "main.h";


SDL_Window *sdlWindow;
SDL_Renderer *sdlRenderer;

void draw_page()	{
	SDL_SetRenderDrawColor(sdlRenderer, 0xFF, 0x00, 0xFF, 0xFF);
	//SDL_RenderDrawPoint(sdlRenderer, 400, 300);
	//SDL_RenderDrawPoint(sdlRenderer, 401, 300);
	//SDL_RenderDrawPoint(sdlRenderer, 402, 300);
	//SDL_RenderDrawPoint(sdlRenderer, 403, 300);
	//SDL_RenderDrawPoint(sdlRenderer, 404, 300);
}









int main( int argc, char* argv[])	{
	//initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
  
	//Set OpenGL memory usage
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	//Init window
	SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &sdlWindow, &sdlRenderer);


	SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
	SDL_RenderClear(sdlRenderer);
	//SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL); In the case we want to draw the screen using a texture (c# bitmap)




	SDL_RenderPresent(sdlRenderer);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
	//SDL_RenderSetLogicalSize(sdlRenderer, 1920, 1200);

	SDL_SetRelativeMouseMode(SDL_TRUE);

 
 
	std::cout << "OpenGL is running\n";
	std::cout << "Main loop has started\n";

	//Handles the main loop
	bool isRunning = true;
	SYSTEMTIME t;
 
	//For handling with event
	SDL_Event event;
	SDL_RenderClear(sdlRenderer);
    GetSystemTime(&t); // or GetLocalTime(&t)
    printf("The system time is: %02d:%02d:%02d.%03d\n", 
        t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
	SDL_SetRenderDrawColor(sdlRenderer, 0xFF, 0x00, 0xFF, 0xFF);
	SDLCust test = SDLCust();
	
	SDLCust::RenderSprite Sprite = SDLCust::RenderSprite(sdlRenderer, 200, 100);
	Sprite.SetColor(0xFF, 0x00, 0xFF, 0xFF);
	Sprite.DrawLine(0, 0, 0, 840);
	Sprite.DrawLine(1200, 0, 1200, 840);
	Sprite.DrawCircle(20, 20, 15);
	Sprite.DrawCircle(20, 420, 15);
	Sprite.DrawCircle(20, 820, 15);
	for (int y = 0; y <= 840; y += 40)	{
		Sprite.DrawLine(0, y, 1200, y);
	}
	Sprite.Update();
	//Sprite.ToScreen();
	SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0x00, 0x00, 0xFF);
	GetSystemTime(&t); // or GetLocalTime(&t)
    printf("The system time is: %02d:%02d:%02d.%03d\n", 
        t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
	SDL_RenderPresent(sdlRenderer);
	int lastM = t.wMilliseconds;
	int xVol = 0;
	int yVol = 0;
	while(isRunning == true)	{
		SDL_RenderClear(sdlRenderer);
		 while ( SDL_PollEvent(&event) )	{
			if (event.type == SDL_QUIT)	{
				isRunning = false;
			}else if (event.type == SDL_KEYDOWN)	{
				if (event.key.keysym.sym == SDLK_LEFT)	{
					xVol = -5;
				}else if (event.key.keysym.sym == SDLK_RIGHT)	{
					xVol = 5;
				}else if (event.key.keysym.sym == SDLK_UP)	{
					yVol = -5;
				}else if (event.key.keysym.sym == SDLK_DOWN)	{
					yVol = 5;
				}
			}else if (event.type == SDL_KEYUP)	{
				if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT)	{
					xVol = 0;
				}else if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN)	{
					yVol = 0;
				}
			}
			// SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			//             "Missing file",
			//             "File is missing. Please reinstall the program.",
			//            NULL);

		 }
		Sprite.Move(Sprite.X + xVol, Sprite.Y + yVol);
		SDL_SetRenderDrawColor(sdlRenderer, 0xFF, 0x00, 0xFF, 0xFF);
		Sprite.Update();
		SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderPresent(sdlRenderer);
		GetSystemTime(&t); // or GetLocalTime(&t)
		std::cout << 1000 / (t.wMilliseconds - lastM) << "\n";
		lastM = t.wMilliseconds;
	}
	return 0;
}





















