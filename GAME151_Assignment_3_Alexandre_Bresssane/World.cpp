#include "World.h"


std::vector<Body*>::iterator World::GetBodies()
{
	return bodies.begin();
}

float World::GetElapsedTime()
{
	return elapsedTime;
}

World::World()
{
	elapsedTime = 0.0f;
}


World::~World()
{
	for (auto body : bodies)
	{
		delete body;
	}

	bodies.clear();
}

bool World::AddBody(Body* body)
{
	auto it = std::find(bodies.begin(), bodies.end(), body);
	if (it == bodies.end())
	{
		bodies.push_back(body);
		return true;
	}

	return false;
}

bool World::RemoveBody(Body* body)
{
	auto it = std::find(bodies.begin(), bodies.end(), body);
	if (it != bodies.end())
	{
		bodies.erase(it);
		return true;
	}
	return false;
}

void World::Update(float deltaTime)
{
	for (auto body : bodies)
	{
		//Euler integrate new positions for each of the bodies
		body->Velocity += deltaTime * body->Acceleration;
		body->Position += deltaTime * body->Velocity;

		//Reset acceleration to zero
		body->Acceleration = VECTOR_ZERO;
	}

	elapsedTime += deltaTime;
}

bool World::TestCollision(const Body* a, const Body* b, Vec3* outNormalBtoA)
{
	//Find a vector from B to A
	Vec3 btoA = a->Position - b->Position;

	//Get the distance from the center of B to the center A
	float distance = sqrt((btoA.x * btoA.x) + (btoA.y * btoA.y) + (btoA.z * btoA.z));

	//Check that the distance is less then the sum of the radii
	if (distance <= (a->Radius + b->Radius))
	{
		//Set the normal to the collision
		if (outNormalBtoA)
		{
			*outNormalBtoA = btoA / distance;
		}
		return true;
	}
	return false;
}
