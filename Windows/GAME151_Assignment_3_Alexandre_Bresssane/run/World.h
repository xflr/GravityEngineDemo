#pragma once
#include<vector>
#include"Body.h"
#include "Vector.h"
#include <algorithm>

class World
{

private:
	//Members
	std::vector<Body*> bodies;
	float elapsedTime;

public:

	//properties
	std::vector<Body*>::iterator GetBodies();
	float GetElapsedTime();

	//Construstor
	World();

	//Destructor
	~World();

	//Functions
	bool AddBody(Body* body);
	bool RemoveBody(Body*  body);
	void Update(float deltaTime);
	bool TestCollision(const Body* a, const Body* b, Vec3* outNormalBtoA = NULL);
};

