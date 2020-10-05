#include "Window.h"
#include <sstream>



Window::Window()
{
	renderer = NULL;
	window = NULL;
	height = 0;
	width = 0;
	hasKeyboadFocus = false;
	hasMouseFocus = false;
	isFullscreen = false;
	isMinimized = false;
}


Window::~Window()
{
	Free();
}

void Window::Clear() const
{
	SDL_RenderClear(renderer);
}

void Window::Draw() const
{
	SDL_RenderPresent(renderer);
}

void Window::Free()
{
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
	}
	if (renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
	}

	height = 0;
	width = 0;
	hasKeyboadFocus = false;
	hasMouseFocus = false;
	isFullscreen = false;
	isMinimized = false;
}

void Window::HandleEvent(const SDL_Event& e)
{
	//Window event occured
	if (e.type == SDL_WINDOWEVENT)
	{
		switch (e.window.event)
		{
			//Get new dimensions and repaint on window size change
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			height = e.window.data2;
			width = e.window.data1;
			SDL_RenderPresent(renderer);
			break;

			//Repaint on exposure
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent(renderer);
			break;
			
			//Mouse entered window
		case SDL_WINDOWEVENT_ENTER:
			hasMouseFocus = true;
			break;

			//Mouse left window
		case SDL_WINDOWEVENT_LEAVE:
			hasMouseFocus = false;
			break;

			//Windows has Keyboard focus
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			hasKeyboadFocus = true;
			break;

			//Windows lost Keyboard focus
		case SDL_WINDOWEVENT_FOCUS_LOST:
			hasKeyboadFocus = false;
			break;

			//Windows Minimized
		case SDL_WINDOWEVENT_MINIMIZED:
			isMinimized = true;
			break;

			//Windows Maximized
		case SDL_WINDOWEVENT_MAXIMIZED:
			isMinimized = false;
			break;

			//Window restored
		case SDL_WINDOWEVENT_RESTORED:
			isMinimized = false;
			break;
		}
	}
}

void Window::Init(std::string title, Uint32 width, Uint32 height, bool startMinimized, bool startFullscreen)
{
	//Create Window
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window == NULL)
	{
		std::stringstream message;
		message << "Window could not be created! SDL Error : %s" << SDL_GetError() << std::endl;
		throw std::exception(message.str().c_str());
	}

	//Set window height and width and focus state
	this->height = height;
	this->width = width;
	hasKeyboadFocus = true;
	hasMouseFocus = true;

	//Set initial minimized state and fullscreen state
	isMinimized = startMinimized;
	if (isMinimized)
	{
		SDL_MinimizeWindow(window);
	}
	isFullscreen = startFullscreen;
	{
		if (isFullscreen)
		{
			SDL_SetWindowFullscreen(window, SDL_TRUE);
		}
	}

	//Create Renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		std::stringstream message;
		message << "Renderer could not be created! SDL Error : %s" << SDL_GetError() << std::endl;
		throw std::exception(message.str().c_str());
	}

	//Init renderer color
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
}