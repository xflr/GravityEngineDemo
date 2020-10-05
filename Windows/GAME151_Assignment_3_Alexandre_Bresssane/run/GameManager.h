#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Clock.h"
#include "Window.h"

class Scene;

class GameManager
{
private:
	Clock clock;
	Scene* scene;
	Window window;


public:

	//Properties
	Clock* GetClock();
	Scene* GetScene();
	Scene& GetAdressOfScene();
	Window* GetWindow();

	//Constructors
	GameManager();
	GameManager(Uint32 pixelWidth, Uint32 pixelHeight, bool startFullScreen = false, Uint32 sdlFlags = SDL_INIT_VIDEO, Uint32 imgFlags = IMG_INIT_PNG);

	//Functions
	void BeginGame(Uint32 pixelWidth, Uint32 pixelHeight, bool startFullScreen = false, Uint32 sdlFlags = SDL_INIT_VIDEO, Uint32 imgFlags = IMG_INIT_PNG);
	void BeginScene(Scene* newScene);
	void EndScene();
	void EndGame();
};

