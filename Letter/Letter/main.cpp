#include "main.h";

int main( int argc, char* argv[])	{		//INITIAL FUNCTION CALL ON LOAD
	GameObject Game = GameObject();
	Game.Run();
	return 0;
}


GameObject::GameObject() : _gameState(GameState::PLAY), _gameStateLoaded(false)	{

}
void GameObject::Run()	{
	Init();
	//DECLARE ANY TEMP VARIABLES HERE FOR DEBUG PURPOSES ~##################################################
	SYSTEMTIME t;	GetSystemTime(&t);
	std::cout << "SDL and OpenGL started at (" << t.wHour << ":" << t.wMinute << ":" << t.wSecond << ":" << t.wMilliseconds << ")" << std::endl;

	Loop();
}
void GameObject::Init()	{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); // Set Version To __
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2); // __ Version 3.2
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //We would like to double buffer!
	SDL_Init(SDL_INIT_EVERYTHING); //Initialize SDL

	SDLWindow = SDL_CreateWindow("Test Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_OPENGL);// | SDL_WINDOW_FULLSCREEN_DESKTOP); //Init window
	if (SDLWindow == NULL)
		FatalError("Error 1: The window failed to initialize!");
	SDL_GLContext glContext = SDL_GL_CreateContext(SDLWindow); //Create the GL context
	if (glContext == nullptr)
		FatalError("Error 2: Failed to create open-gl context!");
	GLenum error = glewInit(); //This helps with windows hardware helpers.
	if (error != GLEW_OK)	{
		std::cout << "Glew not okay! " << error;
		FatalError("Error 3: Could not initialize Glew!");
	}

	glClearColor(0, 0, 0, 1); //Set background color to black for now. This will remain after every buffer change!
	SDL_GL_SetSwapInterval(0); //TURN ON VSYNC OR OFF
	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  //Make scaled rendering look better
	//Set the computed screen resolution (What the program sees)
	//SDL_RenderSetLogicalSize(sdlRenderer, 1920, 1200);

	//Allow the mouse cursor #Fails...
	//SDL_SetRelativeMouseMode(SDL_TRUE);


	GLint m_viewport[4];
	glGetIntegerv(GL_VIEWPORT, m_viewport);
	ScreenRes = ScreenResolution();
	ScreenRes.Width = m_viewport[2];
	ScreenRes.Height = m_viewport[3];
	ScreenRes.Ratio = ((float)ScreenRes.Width / ScreenRes.Height); //RETURNS THE RATIO BETWEEN SCREENWIDTH/HEIGHT  (4:3 aspect ratio returns 1.33..)

	ColorProgram = GLSL(); //Initializes our GLSL Graphics Buffer program.
	ColorProgram.compileShaders("Shader/colorShading.vert", "Shader/colorShading.frag");
	ColorProgram.addAttribute("vertexPosition");
	ColorProgram.addAttribute("vertexColor");
	ColorProgram.addAttribute("vertexUV");
	ColorProgram.linkShaders();
	ColorProgram.loadUniformLocations();

	Resources = ResourceManager(); //Init resource manager
}

void GameObject::Loop()	{
	Uint32 FPSCurTicks = 0, FPSLastTick = SDL_GetTicks();
	float FPSFrameCount = 0, FPSFrameCutOff;
	while(_gameState != GameState::EXIT)	{
		if (_gameStateLoaded == false)	{
			//INITIALIZE GAME STATE
			if (_gameState == GameState::PLAY)	{
				game = Game(1);
			}
			_gameStateLoaded = true;
		}
		ProcessInput();
		DrawScreen();
		GameStep();
		
		//Handle FPS
		RunTime = SDL_GetTicks();
		FrameTimeElapsed = RunTime - FPSLastTick;
		FPSCurTicks = FPSCurTicks + FrameTimeElapsed;
		FPSFrameCount++;
		if (FPSCurTicks > 1000)	{//A second has passed; Lets see how many frames have been processed in 1000MS, set FPS to that number, and remove a 1000MS from _FPSCurTicks
			FPSFrameCutOff =((float)(FPSCurTicks - 1000) / FrameTimeElapsed);
			_FPS = FPSFrameCount - 1 + (1 - FPSFrameCutOff);
			std::cout << _FPS << std::endl;
			FPSCurTicks -= 1000;
			FPSFrameCount = FPSFrameCutOff;
		}
		FPSLastTick = RunTime;
//		SDL_Delay(3);
	}
}

void GameObject::DrawScreen()	{
	//Clear the screen
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Draw to the screen
	ColorProgram.use();

	//Call the draw function in whatever class depending on the current game state.
	if (_gameState == GameState::PLAY)	{
		game.Draw(); 
	}

	//Swap to the new buffered window.
	ColorProgram.unuse();
	SDL_GL_SwapWindow(SDLWindow);
}

void GameObject::ProcessInput()	{
	while ( SDL_PollEvent(&event) )	{
		if (event.type == SDL_QUIT)	{
			_gameState = GameState::EXIT; //We can call SDL_QUIT anywhere which will then set event.type == SDL_QUIT then quitting the game.
		}else	{
			if (_gameState == GameState::PLAY)	{
				game.KeyHandler(event); //Pass event information to the game class.
			}
		}
	}
}



void GameObject::GameStep()	{//Essentially a wrapper to call the current gamestate gamestep function
	if (_gameState == GameState::PLAY)	{
		game.Step(); //Call the step function in game class.
	}
}







