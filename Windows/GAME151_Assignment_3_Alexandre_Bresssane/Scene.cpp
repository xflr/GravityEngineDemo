#include "Scene.h"
#include "GameManager.h"
#include "MMath.h"
#include "Matrix.h"

using namespace MATH;


GameManager* Scene::GetGame()
{
	return game;
}

Matrix4& Scene::GetProjectionMatrix()
{
	return projectionMatrix;
}

World* Scene::GetWorld()
{
	return &world;
}


Scene::Scene()
{
	game = NULL;
}
Scene::Scene(GameManager* game)
{
	Init(game);
}

void Scene::Init(GameManager* game)
{
	this->game = game;

	//Set up a reasonable default for the projection matrix
	projectionMatrix = MMath::viewportNDC(game->GetWindow()->width, game->GetWindow()->height) * MMath::orthographic(0.0f, 16.0f, 0.0f, 9.0f, 0.0f, 1.0f);
}

void Scene::SetCameraBounds(float xMin, float xMax, float yMin, float yMax)
{
	projectionMatrix = MMath::viewportNDC(game->GetWindow()->width, game->GetWindow()->height) * MMath::orthographic(xMin, xMax, yMin, yMax, -1.0f, 1.0f);

}

