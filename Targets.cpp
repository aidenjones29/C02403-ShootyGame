#pragma once
#include "Targets.h"

float redTargetWorldPositions[numRedTargets][4] =
{
	{0,12,-3,180}, {35,12,-3,180}, {70,12,-3,180},{80, 12, 160, 270},{80, 12, 200, 270},{60, 12, 260, 270},{55, 12, 220, 90},{55, 12, 140, 90},
	{260, 12, 290, 90},{260, 12, 335, 90},{250, 12, 140, 270},{250, 12, 180, 270},{185, 12, 260, 270},{190, 12, 176, 180},{210, 12, 176, 180},
	{307, 12, 100, 180},{325, 12, 140, 180},{338, 12, 100, 180},{290, 12, 105, 0},{248, 12, 105, 0},{185, 12, 95, 270},{185, 12, 25, 270}
};

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