#include "Collisions.h"

bool FenceCollision(IModel* cameraDummy)
{
	if (-10 < cameraDummy->GetX() && 130 > cameraDummy->GetX() && 50 < cameraDummy->GetZ() && 90 > cameraDummy->GetZ()) //Checks if the car and wall are in collision
	{
		return true;     //Returns true if collision happens for the collision resolution.
	}
	else
	{
		return false;    //Returns a false when a collision hasnt happened.
	}
	return false;
}

bool gunInteraction(IModel* gunInteractionDummy, IModel* Gun)
{
	float xVect;
	float zVect;
	float distance;

	xVect = gunInteractionDummy->GetX() - Gun->GetX();
	zVect = gunInteractionDummy->GetZ() - Gun->GetZ();
	distance = sqrt((xVect * xVect) + (zVect * zVect));

	if (distance <  5.0f)
	{
		return true;
	}

	return false;
}