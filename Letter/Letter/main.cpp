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
	ScreenRes.Ratio = ((float)ScreenRes.Width / ScreenRes.Height);

	ColorProgram = GLSL();
	ColorProgram.compileShaders("Shader/colorShading.vert", "Shader/colorShading.frag");
	ColorProgram.addAttribute("vertexPosition");
	ColorProgram.addAttribute("vertexColor");
	ColorProgram.addAttribute("vertexUV");
	ColorProgram.linkShaders();
	ColorProgram.loadUniformLocations();

	//Init resource manager
	Resources = ResourceManager();
}

void GameObject::Loop()	{
	float _FPSCurTicks = 0, _FPSLastTick = SDL_GetTicks(), _FPSFrameCount = 0;
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
		RunTime = SDL_GetTicks();
		_FPSCurTicks = _FPSCurTicks + RunTime - _FPSLastTick;
		_FPSFrameCount++;
		if (_FPSCurTicks > 1000)	{//A second has passed; Lets see how many frames have been processed, set FPS to that number, and remove a 1000ms(1 second) from _FPSCurTicks
			_FPS = _FPSFrameCount;
			std::cout << _FPS << std::endl;
			_FPSCurTicks -= 1000;
			_FPSFrameCount = 0;
		}
		_FPSLastTick = RunTime;
		//SDL_Delay(2);
	}
}

void GameObject::DrawScreen()	{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ColorProgram.use();
	if (_gameState == GameState::PLAY)	{
		game.Draw();
	}
	ColorProgram.unuse();
	SDL_GL_SwapWindow(SDLWindow);
}

void GameObject::ProcessInput()	{
	while ( SDL_PollEvent(&event) )	{
		if (event.type == SDL_QUIT)	{
			_gameState = GameState::EXIT;
		}else	{
			if (_gameState == GameState::PLAY)	{
				game.KeyHandler(event);
			}
		}
	}
}



void GameObject::GameStep()	{
	if (_gameState == GameState::PLAY)	{
		game.Step();
	}
}







