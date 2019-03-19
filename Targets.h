#pragma once
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include "ModelCreation.h"
#include <iostream>
#include <vector>
#include <memory>
#include "Math.h"
enum targetStates{Ready, Hit, Down, Reset};
struct sTarget
{
	IMesh* targetMesh;
	IModel* model;
	targetStates state;

};
const int numTargets=3;
void spawnTargets(IMesh* bulletMesh, vector<sTarget*> &vTargets);
void moveTargets(vector<sTarget*> &vTargets, float frameTime);