#pragma once
#include "Targets.h"

float redTargetWorldPositions[numRedTargets][4] =
{
	/*Spawn Targets*/{0,12,-3,180}, {35,12,-3,180}, {70,12,-3,180},

	/*Room 1*/{68, 12, 140, 240},{68, 12, 230, 300},{60, 12, 260, 270},{55, 12, 240, 90},{50, 12, 140, 130},

	/*Room 2*/{260, 12, 290, 90}, {260, 12, 335, 90}, {270, 12, 115, 180},{245, 12, 140, 270},{185, 12, 260, 270},{190, 12, 182, 210},{210, 12, 176, 180},
			  {307, 12, 100, 180},{325, 12, 140, 180},{338, 12, 100, 180},{290, 12, 105, 0},  {248, 12, 105, 0},  {185, 12, 95, 270}, {185, 12, 15, 270},

	/*HOSTAGES*/{68, 12, 180, 270},{30, 12, 140, 180},{190, 12, 285, 180},{250, 12, 120, 240},{194, 12, 260, 270},{194, 12, 130, 270},{194, 12, 150, 270},{220, 12, 105, 0}
};

float greenTargetWorldPositions[numRedTargets][4];

void spawnTargets(vector<sTarget*> &vTargets) 
{
	for (int i = 0; i < numRedTargets; i++)
	{
		sTarget* target = new Terrorist_target(redTargetWorldPositions[i][0],redTargetWorldPositions[i][1],redTargetWorldPositions[i][2], redTargetWorldPositions[i][3]);
		
		if (i > 21)
		{
			target->model->SetSkin("Hostage.png");
			target->hostage = true;
		}

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