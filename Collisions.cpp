#pragma once
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
	float bWidth = 10.0f;
	float bDepth = 10.0f;
	float height = 16.0f;

	for (auto& i : vTargets)
	{
		for (auto& x : vMagazine)
		{
			float minX = i->model->GetX() - bWidth / 2 - sRad; 
			float maxX = i->model->GetX() + bWidth / 2 + sRad; 
			float minZ = i->model->GetZ() - bDepth / 2 - sRad; 
			float maxZ = i->model->GetZ() + bDepth / 2 + sRad; 
			float minY = i->model->GetY() - height / 2 - sRad;
			float maxY = i->model->GetY() + height / 2 + sRad;

			if (x->model->GetX() > minX && x->model->GetX() < maxX && x->model->GetZ() > minZ && x->model->GetZ() < maxZ && x->model->GetY() > minY && x->model->GetY() < maxY)
			{
				i->state = Hit;
				x->status = Spent;
				x->model->SetY(0.2f);
			}

		}
	}
}


bool targetBoxCollision(std::vector<sTarget*>& vTargets, IModel* camDummy)
{
	float sRad = 2.0f;
	float bWidth = 5.0f;
	float bDepth = 5.0f;

	for (auto& i : vTargets)
	{
		float minX = i->box->GetX() - bWidth - sRad; //Min x pos before a collision has happened
		float maxX = i->box->GetX() + bWidth + sRad; //Max x pos before a collision has happened
		float minZ = i->box->GetZ() - bDepth - sRad; //Min z pos before a collision has happened
		float maxZ = i->box->GetZ() + bDepth + sRad; //Max z pos before a collision has happened

		if (camDummy->GetX() > minX && camDummy->GetX() < maxX && camDummy->GetZ() > minZ && camDummy->GetZ() < maxZ)
		{
			return true;
		}
	}
	return false;
}