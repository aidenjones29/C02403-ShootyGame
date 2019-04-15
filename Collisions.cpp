#pragma once
#include "Collisions.h"

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

			float minX = i->model->GetX() - bWidth / 2 - sRad; //Min x pos before a collision has happened
			float maxX = i->model->GetX() + bWidth / 2 + sRad; //Max x pos before a collision has happened
			float minZ = i->model->GetZ() - bDepth / 2 - sRad; //Min z pos before a collision has happened
			float maxZ = i->model->GetZ() + bDepth / 2 + sRad; //Max z pos before a collision has happened
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

sideHit targetBoxCollision(std::vector<sTarget*>& vTargets, IModel* camDummy, float oldPos[])
{
	float sRad = 2.0f;
	float bWidth = 7.0f;
	float bDepth = 7.0f;

	for (auto& i : vTargets)
	{
		float minX = i->box->GetX() - bWidth - sRad; //Min x pos before a collision has happened
		float maxX = i->box->GetX() + bWidth + sRad; //Max x pos before a collision has happened
		float minZ = i->box->GetZ() - bDepth - sRad; //Min z pos before a collision has happened
		float maxZ = i->box->GetZ() + bDepth + sRad; //Max z pos before a collision has happened

		if (camDummy->GetX() > minX && camDummy->GetX() < maxX && camDummy->GetZ() > minZ && camDummy->GetZ() < maxZ)
		{
			if (oldPos[0] < minX || oldPos[0] > maxX) return LeftRight;
			if (oldPos[1] < minZ || oldPos[1] > maxZ) return FrontBack;
		}
	}
	return NoSide;
}

sideHit WallCollision(const float Walls[maxWALLLLLLLZZZ][5], IModel* camDummy, float oldPos[])
{
	float sRad = 2.0f;
	float oWWidth = 50.0f;
	float oWDepth = 4.0f;
	float iWWidth = 20.0f;
	float iWDepth = 2.0f;

	float minX = 0;
	float maxX = 0;
	float minZ = 0;
	float maxZ = 0;

	for (int i = 0; i < maxWALLLLLLLZZZ; i++)
	{
		if (Walls[i][0] == 1)
		{
			if (Walls[i][4] == 0)
			{
				minX = Walls[i][1] - oWWidth - sRad; //Min x pos before a collision has happened
				maxX = Walls[i][1] + oWWidth + sRad; //Max x pos before a collision has happened
				minZ = Walls[i][3] - oWDepth - sRad;
				maxZ = Walls[i][3] + oWDepth + sRad; //Max z pos before a collision has happened

				if (camDummy->GetX() > minX && camDummy->GetX() < maxX && camDummy->GetZ() > minZ && camDummy->GetZ() < maxZ)
				{
					if (oldPos[0] < minX || oldPos[0] > maxX) return LeftRight;
					if (oldPos[1] < minZ || oldPos[1] > maxZ) return FrontBack;
				}
			}
			else
			{
				if (i == 16 || i == 17 || i == 23)
				{
					minX = Walls[i][1] - oWDepth - sRad;
					maxX = Walls[i][1] + oWDepth + sRad;
					minZ = Walls[i][3] - (oWWidth / 2) - sRad;
					maxZ = Walls[i][3] + (oWWidth / 2) + sRad;
				}
				else
				{
					minX = Walls[i][1] - oWDepth - sRad; //Min x pos before a collision has happened
					maxX = Walls[i][1] + oWDepth + sRad; //Max x pos before a collision has happened
					minZ = Walls[i][3] - oWWidth - sRad;
					maxZ = Walls[i][3] + oWWidth + sRad; //Max z pos before a collision has happened
				}

				if (camDummy->GetX() > minX && camDummy->GetX() < maxX && camDummy->GetZ() > minZ && camDummy->GetZ() < maxZ)
				{
					if (oldPos[0] < minX || oldPos[0] > maxX) return LeftRight;
					if (oldPos[1] < minZ || oldPos[1] > maxZ) return FrontBack;
				}
			}
		}
		else
		{
			if (Walls[i][4] == 0)
			{
				minX = Walls[i][1] - iWWidth - sRad; //Min x pos before a collision has happened
				maxX = Walls[i][1] + iWWidth + sRad; //Max x pos before a collision has happened
				minZ = Walls[i][3] - iWDepth - sRad;
				maxZ = Walls[i][3] + iWDepth + sRad; //Max z pos before a collision has happened

				if (camDummy->GetX() > minX && camDummy->GetX() < maxX && camDummy->GetZ() > minZ && camDummy->GetZ() < maxZ)
				{
					if (oldPos[0] < minX || oldPos[0] > maxX) return LeftRight;
					if (oldPos[1] < minZ || oldPos[1] > maxZ) return FrontBack;
				}
			}
			else
			{
				minX = Walls[i][1] - iWDepth - sRad; //Min x pos before a collision has happened
				maxX = Walls[i][1] + iWDepth + sRad; //Max x pos before a collision has happened
				minZ = Walls[i][3] - iWWidth - sRad;
				maxZ = Walls[i][3] + iWWidth + sRad; //Max z pos before a collision has happened

				if (camDummy->GetX() > minX && camDummy->GetX() < maxX && camDummy->GetZ() > minZ && camDummy->GetZ() < maxZ)
				{
					if (oldPos[0] < minX || oldPos[0] > maxX) return LeftRight;
					if (oldPos[1] < minZ || oldPos[1] > maxZ) return FrontBack;
				}
			}

		}
	}
	return NoSide;
}

sideHit allFenceCollisions(IModel* camDummy, float oldPos[])
{
	const int numFenceCollisions = 8;
	float minX[numFenceCollisions] = {-50.0f, -20.0f, 130.0f,  50.0f, 130.0f, -55.0f, 133.0f, 133.0f};
	float maxX[numFenceCollisions] = {113.0f, -13.0f, 175.0f, 135.0f, 175.0f,  95.0f, 175.0f, 175.0f};
	float minZ[numFenceCollisions] = { 90.0f, -20.0f,  64.0f, -40.0f, -10.0f, -12.0f, 300.0f, 345.0f};
	float maxZ[numFenceCollisions] = {124.0f, 124.0f, 124.0f,  -2.0f,  49.0f,  50.0f, 323.0f, 360.0f};

	for (int i = 0; i < numFenceCollisions; i++)
	{
		if (camDummy->GetX() > minX[i] && camDummy->GetX() < maxX[i] && camDummy->GetZ() > minZ[i] && camDummy->GetZ() < maxZ[i])
		{
			if (oldPos[0] < minX[i] || oldPos[0] > maxX[i]) return LeftRight;
			if (oldPos[1] < minZ[i] || oldPos[1] > maxZ[i]) return FrontBack;
		}
	}
	return NoSide;
}