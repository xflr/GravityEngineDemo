#pragma once
#include <string>
#include <SDL2/SDL.h>

class Window
{
public:

	bool hasMouseFocus;
	bool hasKeyboadFocus;
	Uint32 height;
	Uint32 width;
	bool isFullscreen;
	bool isMinimized;
	SDL_Renderer* renderer;
	std::string title;
	SDL_Window* window;
	

	//Constructor
	Window();

	//Destructor
	~Window();

	
	void Clear() const;
	void Draw() const;
	void Free();
	void HandleEvent(const SDL_Event& e);
	void Init(const std::string title, Uint32 width, Uint32 height, bool startMinimized = false, bool startFullscreen = false);
};

