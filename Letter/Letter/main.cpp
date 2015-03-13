

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
	SDL_RenderSetLogicalSize(sdlRenderer, 1920, 1200);

	SDL_SetRelativeMouseMode(SDL_TRUE);

 
 
	std::cout << "OpenGL is running\n";
	std::cout << "Main loop has started\n";

	//Handles the main loop
	bool isRunning = true;
 
	//For handling with event
	SDL_Event event;
			SDL_RenderClear(sdlRenderer);
			SDL_SetRenderDrawColor(sdlRenderer, 0xFF, 0x00, 0xFF, 0xFF);
			SDLCust test = SDLCust();
			test.RenderDrawLine(sdlRenderer, 4.3, 2.7, 12.8, 11.4);
			SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_RenderPresent(sdlRenderer);

	while(isRunning == true)	{
		 while ( SDL_PollEvent(&event) )	{
			if (event.type == SDL_QUIT)	{
				isRunning = false;
			}
			// SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			//             "Missing file",
			//             "File is missing. Please reinstall the program.",
			//            NULL);
			


			//Draw the page...




//			SDL_GL_SwapWindow(sdlWindow); //Swap to new frame
		 }
		SDL_Delay(1);
	}
	return 0;
}





















