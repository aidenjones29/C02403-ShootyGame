#pragma once
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include "ModelCreation.h"
#include "Collisions.h"
#include "wtypes.h" 
#include <iostream>
#include <vector>
#include <memory>
#include "Math.h"

struct sBullet
{
	IModel* model;
	float timeAlive = 0;
	bool isFired = false;
	vector3D facingVector{ 0,0,0 };
	
};



void spawnBullets(int maxBullets, IMesh* bulletMesh, vector<sBullet*> &vBullets);
void refillNewWeapon(int magSize, vector<sBullet*> &vMagazine,vector<sBullet*> &vBullets);
void moveBullets(int magSize, vector<sBullet*> &vMagazine, float frameTime);
