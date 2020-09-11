#pragma once

#include <SDL.h>
#include "Matrix.h"
#include "World.h"

class GameManager;

class Scene
{

protected:
	GameManager* game;
	Matrix4 projectionMatrix;
	World world;

public:
	//properties
	GameManager* GetGame();
	Matrix4& GetProjectionMatrix();
	World* GetWorld();

	//Abstract
	virtual void Begin() = 0;
	virtual void End() = 0;
	virtual void HandleEvent(const SDL_Event& e) = 0;
	virtual void Render() = 0;
	virtual bool Update(const float deltaTime) = 0;


	//Constructors
	Scene();
	Scene(GameManager* game);

	//Functions
	void Init(GameManager* game);
	void SetCameraBounds(float xMin, float xMax, float yMin, float yMax);
};

