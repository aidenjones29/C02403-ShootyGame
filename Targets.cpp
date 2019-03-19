
#include "Targets.h"
float targetWorldPositions[numTargets][4] = { {0,12,-5,180}, {35,12,-5,180}, {70,12,-5,180} };

void spawnTargets(IMesh* targetMesh, vector<sTarget*> &vTargets) 
{


	for (int i = 0; i < numTargets; i++)
	{
		sTarget* target = new sTarget;
		target->model = targetMesh->CreateModel(targetWorldPositions[i][0],targetWorldPositions[i][1],targetWorldPositions[i][2]);
		target->model->RotateLocalY(targetWorldPositions[i][3]);
		target->model->ScaleY(1.6);
		target->model->ScaleZ(0.1);
		target->state = Ready;
		vTargets.push_back(target);
	}

}
void moveTargets(vector<sTarget*> &vTargets,float frameTime)
{
	for (int i = 0; i < numTargets; i++)
	{
		switch (vTargets[i]->state)
		{
		case Ready:
			break;
		case Hit:
			vTargets[i]->model->MoveY(-50.0f*frameTime);
			if (vTargets[i]->model->GetY() < -15.0f) 
			{
				vTargets[i]->state = Down;
			}
			break;
		case Down:
			break;
		case Reset:
			vTargets[i]->model->MoveY(50.0f * frameTime);
			if (vTargets[i]->model->GetY() >= 12.0f)
			{
				vTargets[i]->state = Ready;
			}
		default:
			break;
		}

	}

}