#include "Texture.h"
#include <SDL_image.h>
#include <sstream>


Texture::Texture()
{
	sdlTexture = NULL;
	renderer = NULL;
	height = 0;
	width = 0;
}


Texture::Texture(std::string path, SDL_Renderer* newRenderer)
{
	sdlTexture = NULL;
	renderer = NULL;
	height = 0;
	width = 0;

	Init(path, newRenderer);
}

Texture::~Texture()
{
	Free();
}

void Texture::Free()
{
	if (sdlTexture != NULL)
	{
		SDL_DestroyTexture(sdlTexture);
		sdlTexture = NULL;
		height = 0;
		width = 0;
	}
}

void Texture::Init(std::string path, SDL_Renderer* newRenderer)
{
	//Get rid of preexisting texture;
	Free();

	//Load image at specified path;
	SDL_Surface* loadSurface = IMG_Load(path.c_str());
	if (loadSurface == NULL)
	{
		std::stringstream message;
		message << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << std::endl;
		throw std::exception(message.str().c_str());
	}


	//Color key image
	//TODO Change color keying?
	SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface->format, 0, 0xff, 0xff));

	//Assign the new renderer if provided and destroy the old renderer
	if (newRenderer != NULL)
	{
		renderer = newRenderer;
	}

	//Create texture from surface pixels
	sdlTexture = SDL_CreateTextureFromSurface(renderer, loadSurface);
	if (sdlTexture == NULL)
	{
		std::stringstream message;
		message << "Unable to create texture from " << path << " SDL_image Error: " << IMG_GetError() << std::endl;
		throw std::exception(message.str().c_str());
	}


	//Image dimensions
	height = loadSurface->h;
	width = loadSurface->w;

	//Get rid of surface we used to load the image
	SDL_FreeSurface(loadSurface);
}

void Texture::Render(Uint32 x, Uint32 y, SDL_Rect* clip, float angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//set rendering space and render to screen
	SDL_Rect renderQuad = { int(x), int(y), int(width), int(height) };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to the screen
	SDL_RenderCopyEx(renderer, sdlTexture, clip, &renderQuad, angle, center, flip);
}


void Texture::SetAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(sdlTexture, alpha);
}

void Texture::SetBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(sdlTexture, blending);
}

void Texture::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb;
	SDL_SetTextureColorMod(sdlTexture, red, green, blue);
}
