#include "GameObject.h"
#include "Body.h"
#include "GameManager.h"
#include "Scene.h"
#include "Texture.h"
#include "Window.h"


Body* GameObject::GetBody()
{
	return body;
}

Scene* GameObject::GetScene()
{
	return scene;
}

Texture* GameObject::GetTexture()
{
	return texture;
}

GameObject::GameObject()
{
	body = NULL;
	scene = NULL;
	texture = NULL;
}


GameObject::GameObject(Scene* scene, Body* body, Texture* texture)
{
	Init(scene, body, texture);
}

void GameObject::Init(Scene* scene, Body* body, Texture* texture)
{
	this->body = body;
	this->scene = scene;
	this->texture = texture;
}

void GameObject::Render(const Matrix4& projectionMatrix)
{
	//transform body's position to render space
	Vec3 physicsPosition = body->Position;
	Vec3 renderPosition = projectionMatrix * physicsPosition;

	//Render to the screen
	texture->Render(renderPosition.x - 0.5f * texture->width, renderPosition.y - 0.5f * texture->height);

}

void GameObject::Update(const float deltaTime)
{
	//do nothing unless a subclass overrides
}

#if DEBUG
void GameObject::DebugDraw(const Matrix4& projectionMatrix, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	//get renderer

	SDL_Renderer* renderer = scene->GetGame()->GetWindow()->renderer;


	//save the draw colour that the renderer was set to before this
	Uint8 rOld, gOld, bOld, aOld;
	SDL_GetRenderDrawColor(renderer, &rOld, &gOld, &bOld, &aOld);

	//set render colour to red.
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	//Build the array of points to draw(in screen coordinates)
	for (int i = 0; i < 360; i++)
	{
		//Find angle around the circle in radians and use that to build a vector
		//representing the radius as a vector from the center of the body pointing out.
		float radians = float(i) * M_PI / 180.0f;
		Vec3 radiusVector = Vec3(body->Radius * cos(radians), body->Radius * sin(radians), 0.0f);

		//Transform the position of the point( center of the body + radius vector) into the screen coordinates to render this point at.
		Vec3 physicsPosition = body->Position + radiusVector;
		Vec3 renderPosition = projectionMatrix * physicsPosition;

		//Set the actual SDL_Point struct with the values from our transformed Vec3
		debugDrawPoints[i].x = renderPosition.x;
		debugDrawPoints[i].y = renderPosition.y;

	}

	//Tell SDL to draw the points we just generated
	SDL_RenderDrawPoints(renderer, debugDrawPoints, 360);

	//Make sure to set the renderer's draw colour back to whatever it was 
	SDL_SetRenderDrawColor(renderer, rOld, gOld, bOld, aOld);
}



#endif