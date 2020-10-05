#include "Body.h"



Body::Body(float newMass, const Vec3& newPosition, float newRadius, float newRestitution, bool newActivity)
{
	Activity = newActivity;
	Mass = newMass;
	Position = newPosition;
	Velocity = VECTOR_ZERO;
	Radius = newRadius;
	Restitution = newRestitution;
	Acceleration = VECTOR_ZERO;
}


void Body::ApplyForceToCentre(const Vec3& force)
{
	Acceleration += force / Mass;
}
