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

void bulletToTarget(std::vector<sTarget*>& vTargets, std::vector<sBullet*>& vMagazine)
{
	float sRad = 0.02f;
	float bWidth = 20.0f;
	float bDepth = 5.0f;
	for (auto& i : vTargets)
	{
		for (auto& x : vMagazine)
		{


			float minX = i->model->GetX() - bWidth / 2 - sRad; //Min x pos before a collision has happened
			float maxX = i->model->GetX() + bWidth / 2 + sRad; //Max x pos before a collision has happened
			float minZ = i->model->GetZ() - bDepth / 2 - sRad; //Min z pos before a collision has happened
			float maxZ = i->model->GetZ() + bDepth / 2 + sRad; //Max z pos before a collision has happened
			if (x->model->GetX() > minX && x->model->GetX() < maxX && x->model->GetZ() > minZ && x->model->GetZ() < maxZ)
			{
				i->state = Hit;
				x->status = Spent;
				x->model->SetY(0.2f);
			}

		}
	}
}

