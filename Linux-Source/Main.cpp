#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GameManager.h"
#include "Peggle.h"
#include "Matrix.h"
#include "MMath.h"

using namespace MATH;

//Simple simulation of gravity engine by Alexandre Bressane. Using public

//DEFINE RESOLUTION OF THE GAME AND LOAD PNG LIBS
#define RENDER_WIDTH 1280
#define RENDER_HIGHT 720
#define WINDOW_FULLSCREEN false
#define SDL_FLAGS SDL_INIT_VIDEO
#define IMG_FLAGS IMG_INIT_PNG


int main(int argc, char* args[])
{
	//CREATE A GAME MANAGER INSTANCE
	GameManager game(RENDER_WIDTH, RENDER_HIGHT, WINDOW_FULLSCREEN, SDL_FLAGS, IMG_FLAGS);

	//CREATE THE LEVEL PEGGLE ON GAME MANAGER INSTANCE
	Peggle peggle(&game);

	//START THE LEVEL PEGGLE ON SCENE MANAGER
	game.BeginScene(&peggle);

	//END GAME AND UNLOAD THE SCREEN
	game.EndGame();
	return 0;
}



