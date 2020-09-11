#pragma once
#include <string>
#include <SDL.h>


class Texture
{
public:

	Uint32 height;
	Uint32 width;
	SDL_Renderer* renderer;
	SDL_Texture* sdlTexture;


	//Constructor
	Texture();
	Texture(std::string path, SDL_Renderer* newRenderer = NULL);

	//Destructor
	~Texture();

	//functions
	void Free();
	void Init(std::string path, SDL_Renderer* newRenderer = NULL);
	void Render(Uint32 x, Uint32 y, SDL_Rect* clip = NULL, float angle = 0.0f, SDL_Point* center = NULL, SDL_RendererFlip = SDL_FLIP_NONE);
	void SetAlpha(Uint8 alpha);
	void SetBlendMode(SDL_BlendMode blending);
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	
};

