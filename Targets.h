#pragma once
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include "ModelCreation.h"
#include <iostream>
#include <vector>
#include <memory>
#include "Math.h"
#include "Engine.h"
enum targetStates{Ready, Hit, Down, Reset};
struct sTarget
{
	IMesh* targetMesh;
	IModel* model;
	targetStates state;
};
struct Terrorist_target :public sTarget
{
	Terrorist_target(float spawnX ,float spawnY ,float spawnZ,float rotation)
	{
		targetMesh = myEngine->LoadMesh("Target.x");
		model = targetMesh->CreateModel(spawnX, spawnY, spawnZ);
		 model->ScaleY(1.6);
		model->ScaleZ(0.1);
		model->RotateLocalY(rotation);
		state = Ready;
	}
};

const int numRedTargets=3;
const int numGreenTargets = 0;

void spawnTargets(vector<sTarget*> &vTargets);
void moveTargets(vector<sTarget*> &vTargets, float frameTime);