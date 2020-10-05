#pragma once
#include "Texture.h"
#include "Vector.h"

using namespace MATH;

class Body
{
public:

	//Members
	Vec3 Acceleration;
	float Mass;
	Vec3 Position;
	float Radius;
	float Restitution;
	Vec3 Velocity;
	bool Activity;

	//Constructor
	Body(float mass = 1.0f, const Vec3& position = VECTOR_ZERO, float radius = 0.75f, float Restitution = 0.75f, bool activity = true);

	//Functions
	void ApplyForceToCentre(const Vec3& force);
};

