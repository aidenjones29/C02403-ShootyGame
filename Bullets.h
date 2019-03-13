#pragma once
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include "ModelCreation.h"
#include "Collisions.h"
#include "wtypes.h" 
#include <iostream>
#include <vector>
#include <memory>

struct sBullet
{
	IModel* model;
	float timeAlive = 0;
	bool isFired = false;
};



void spawnBullets(int maxBullets, IMesh* bulletMesh, vector<sBullet*> &vBullets);

//void moveBullets()
