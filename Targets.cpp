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
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//COURSE TARGETS (HOSTILE)
	const int numOfCourseTargets = 19;
	IModel* courseTargets[numOfCourseTargets];

	//Room 1
	courseTargets[0] = targetMesh->CreateModel(80, 12, 160);
	courseTargets[1] = targetMesh->CreateModel(80, 12, 200);
	courseTargets[2] = targetMesh->CreateModel(60, 12, 240);
	courseTargets[3] = targetMesh->CreateModel(50, 12, 220);
	courseTargets[4] = targetMesh->CreateModel(50, 12, 140);

	//Room 2
	courseTargets[5] = targetMesh->CreateModel(260, 12, 290);
	courseTargets[6] = targetMesh->CreateModel(260, 12, 340);

	courseTargets[7] = targetMesh->CreateModel(260, 12, 140);
	courseTargets[8] = targetMesh->CreateModel(260, 12, 180);

	courseTargets[9] = targetMesh->CreateModel(190, 12, 260);

	courseTargets[10] = targetMesh->CreateModel(190, 12, 180);
	courseTargets[11] = targetMesh->CreateModel(210, 12, 180);

	courseTargets[12] = targetMesh->CreateModel(310, 12, 100);
	courseTargets[13] = targetMesh->CreateModel(325, 12, 140);
	courseTargets[14] = targetMesh->CreateModel(340, 12, 100);

	courseTargets[15] = targetMesh->CreateModel(290, 12, 100);
	courseTargets[16] = targetMesh->CreateModel(250, 12, 100);
	courseTargets[17] = targetMesh->CreateModel(185, 12, 95);
	courseTargets[18] = targetMesh->CreateModel(190, 12, 15);

	for (int i = 0; i < numOfCourseTargets; i++)
	{
		if (i == 0 || i == 1 || i == 2 || i == 7 || i == 8 || i == 9 || i == 17 || i == 18)
		{
			courseTargets[i]->RotateLocalY(-90);
		}
		if (i == 3 || i == 5 || i == 6)
		{
			courseTargets[i]->RotateLocalY(90);
		}
		if (i == 4 || i == 10 || i == 11 || i == 12 || i == 13 || i == 14)
		{
			courseTargets[i]->RotateLocalY(180);
		}
		courseTargets[i]->ScaleY(1.6);
		courseTargets[i]->ScaleZ(0.1);
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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