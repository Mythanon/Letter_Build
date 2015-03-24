#include "main.h";


SDL_Window *sdlWindow = NULL;
SDL_Renderer *sdlRenderer = NULL;

Drawing::Sprite Sprite;
Drawing::GLTexture Coin;
Drawing::GLSL ColorProgram;
float time;
void DrawGame()	{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ColorProgram.use();

	Sprite.Update();

	ColorProgram.unuse();
	SDL_GL_SwapWindow(sdlWindow);
}



int main( int argc, char* argv[])	{		//INITIAL FUNCTION CALL ON LOAD
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); // Set Version To __
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2); // __ Version 3.2
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //We would like to double buffer!
	SDL_Init(SDL_INIT_EVERYTHING); //Initialize SDL


	sdlWindow = SDL_CreateWindow("Test Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_OPENGL);// | SDL_WINDOW_FULLSCREEN_DESKTOP); //Init window
	if (sdlWindow == NULL)
		FatalError("Error 1: The window failed to initialize!");

	SDL_GLContext glContext = SDL_GL_CreateContext(sdlWindow); //Create the GL context
	if (glContext == nullptr)
		FatalError("Error 2: Failed to create open-gl context!");

	GLenum error = glewInit(); //This helps with windows hardware helpers.
	if (error != GLEW_OK)	{
		std::cout << "Glew not okay! " << error;
		FatalError("Error 3: Could not initialize Glew!");
	}

	glClearColor(0, 0, 0, 1); //Set background color to black for now. This will remain after every buffer change!
	//glFrontFace(GL_CCW);
	  
	//Set OpenGL memory usage
	/*SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );*/


	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  //Make scaled rendering look better

	SDL_Event event; //Event handler, contains info about mouse/keyboard input etc.

	

	//Set the computed screen resolution (What the program sees)
	//SDL_RenderSetLogicalSize(sdlRenderer, 1920, 1200);

	//Allow the mouse cursor #Fails...
	//SDL_SetRelativeMouseMode(SDL_TRUE);


	//DECLARE ANY TEMP VARIABLES HERE FOR DEBUG PURPOSES ~##################################################
	SYSTEMTIME t;	GetSystemTime(&t);
	std::cout << "SDL and OpenGL started at (" << t.wHour << ":" << t.wMinute << ":" << t.wSecond << ":" << t.wMilliseconds << ")" << std::endl;

	

	//START THE GAME LOOP
	bool isRunning = true;

	ColorProgram.compileShaders("Shader/colorShading.vert", "Shader/colorShading.frag");
	ColorProgram.addAttribute("vertexPosition");
	ColorProgram.addAttribute("vertexColor");
	ColorProgram.addAttribute("vertexUV");
	ColorProgram.linkShaders();
	ColorProgram.loadUniformLocations();


	int lastM = t.wMilliseconds;
	float xVol = 0;
	float yVol = 0;
	Sprite = Drawing::Sprite(ColorProgram, -1, -1);
	Sprite.SetColor(Color (255, 255, 255));
	Sprite.AddLine(Position (0, 0), Position (1, 1), Color(233, 233, 0));
	Sprite.AddLine(Position (0.2, 0.5), Position (0.3, 0.6), Color(233, 233, 0), Color(0, 233, 255));
	Sprite.AddTriangle(Position (0.4, 0.1), Position (0.7, 0.1), Position (0.5, 0.5), Color(255, 0, 255));
	Sprite.AddRect(Position (-1, 1.2), Position (1.4, -1), Color(233, 233, 0));

	
	Coin = Drawing::ImageLoader::loadPNG("Textures/test.png");
	Sprite.AddTexture(Position (0.1, 0.1), Position (1.9, 1.9), Coin);
	//ImageLoader::l

	time = 0.0f;





	while(isRunning == true)	{

		 while ( SDL_PollEvent(&event) )	{
			if (event.type == SDL_QUIT)	{
				isRunning = false;
			}else if (event.type == SDL_KEYDOWN)	{
				if (event.key.keysym.sym == SDLK_LEFT)	{
					xVol = -0.005;
				}else if (event.key.keysym.sym == SDLK_RIGHT)	{
					xVol = 0.005;
				}else if (event.key.keysym.sym == SDLK_UP)	{
					yVol = 0.005;
				}else if (event.key.keysym.sym == SDLK_DOWN)	{
					yVol = -0.005;
				}else if (event.key.keysym.sym == SDLK_0)	{
					Sprite.SetScale(Sprite.Scale - 0.02);
					Sprite.Update();
				}else if (event.key.keysym.sym == SDLK_1)	{
					Sprite.SetScale(Sprite.Scale + 0.02);
					Sprite.Update();
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
		Sprite.MoveTo(Sprite.X + xVol, Sprite.Y + yVol);
		time += 0.01f;
		DrawGame();
		
		SDL_Delay(2);
	}

	return 0;
}





















