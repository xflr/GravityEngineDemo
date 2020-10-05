#include "GameManager.h"
#include "Scene.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sstream>



Clock* GameManager::GetClock()
{
	return &clock;
}

Scene* GameManager::GetScene()
{
	return scene;
}

Scene& GameManager::GetAdressOfScene()
{
	return *scene;
}

Window* GameManager::GetWindow()
{
	return &window;
}
GameManager::GameManager()
{
	scene = NULL;
}


GameManager::GameManager(Uint32 pixelWidth, Uint32 pixelHeight, bool startFullScreen, Uint32 sdlFlags, Uint32 imgFlags)
{
	BeginGame(pixelWidth, pixelHeight, startFullScreen, sdlFlags, imgFlags);
}

void GameManager::BeginGame(Uint32 pixelWidth, Uint32 pixelHeight, bool startFullScreen, Uint32 sdlFlags, Uint32 imgFlags)
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::stringstream message;
		message << "SDL could not initialize SDL Error : " << SDL_GetError() << std::endl;
		//throw std::exception(message.str().c_str());
	}

	//create the window
	window.Init("GravityEngine by Alexandre Bressane - CONTROLS: LEFT - RIGHT (ANGLE), UP DOWN (FOR POWER) and SPACE (Shoot)", pixelWidth, pixelHeight, false, startFullScreen);

	//initialize PNG loading
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::stringstream message;
		message << "SDL_image could not be initialize! SDL_image Error: " << IMG_GetError() << std::endl;
		//throw std::exception(message.str().c_str());
	}

	//Start game clock
	clock.Start();
}

void GameManager::BeginScene(Scene* newScene)
{

	//Set current scene and load its assets
	scene = newScene;
	scene->Begin();

	bool isQuitting = false;
	while (!isQuitting)
	{
		//Handle events on queue
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				isQuitting = true;
			}

			//Handle windows events
			window.HandleEvent(e);

			if (scene)
			{
				scene->HandleEvent(e);
			}
		}

		//Mesure the current time.
		clock.Update();


		//Update Scene
		
		if (scene)
		{
			isQuitting = isQuitting || scene->Update(clock.deltaSeconds);

		}

		//Render Scene
		if (!window.isMinimized)
		{
			window.Clear();
			if (scene)
			{
				scene->Render();
			}
			window.Draw();
		}
	}
	EndScene();
}

void GameManager::EndScene()
{
	if (scene)
	{
		scene->End();
		scene = NULL;
	}
}

void GameManager::EndGame()
{
	//Destroy Window
	window.Free();

	//Quit SDL subsystems.
	IMG_Quit();
	SDL_Quit();
}
