#pragma once
#include "Targets.h"

float redTargetWorldPositions[numRedTargets][4] = { {0,12,-3,180}, {35,12,-3,180}, {70,12,-3,180} };

float greenTargetWorldPositions[numRedTargets][4];

void spawnTargets(vector<sTarget*> &vTargets) 
{
	for (int i = 0; i < numRedTargets; i++)
	{
		sTarget* target = new Terrorist_target(redTargetWorldPositions[i][0],redTargetWorldPositions[i][1],redTargetWorldPositions[i][2], redTargetWorldPositions[i][3]);
		vTargets.push_back(target);
	}
}

void moveTargets(vector<sTarget*> &vTargets, float frameTime)
{
	for (auto& vTargets : vTargets)
	{
		switch (vTargets->state)
		{
		case Ready:
			break;
		case Hit:
			vTargets->model->MoveY(-50.0f*frameTime);
			if (vTargets->model->GetY() < -15.0f)
			{
				vTargets->state = Down;
			}
			break;
		case Down:
			break;
		case Reset:
			vTargets->model->MoveY(50.0f * frameTime);
			if (vTargets->model->GetY() >= 12.0f)
			{
				vTargets->state = Ready;
			}
		default:
			break;
		}
	}
}