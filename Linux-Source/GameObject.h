#pragma once

#define DEBUG true

#include <SDL2/SDL.h>
#include "Matrix.h"
#include "MMath.h"

using namespace MATH;

class Body;
class Scene;
class Texture;

class GameObject
{
private:
	//Members
	Body* body;
	Scene* scene;
	Texture* texture;

	//Debug Draw
#if DEBUG
	SDL_Point debugDrawPoints[360];
#endif

public:
	//Porperties
	Body* GetBody();
	Scene* GetScene();
	Texture* GetTexture();

	//Consturctors
	GameObject();
	GameObject(Scene* scene, Body* body, Texture* texture);

	//Functions
	virtual void Init(Scene* scene, Body* body, Texture* texture);
	virtual void Render(const Matrix4& projectionMatrix);
	virtual void Update(const float deltaTime);

	//Debug draw
#if DEBUG
	virtual void DebugDraw(const Matrix4& projectionMatrix, Uint8 r = 0xFF, Uint8 g = 0x00, Uint8 b = 0x00, Uint8 a = 0xFF);
#endif
};

