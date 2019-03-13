#pragma once
#include "Bullets.h"


void spawnBullets(int maxBullets,IMesh* bulletMesh, vector<sBullet*> &vBullets)
{
	//vBullets.resize(maxBullets);
	for (int i = 0; i < maxBullets; i++)
	{
		sBullet* bullet = new sBullet;
		bullet->model = bulletMesh->CreateModel(0, 15, 0);
		vBullets.push_back(bullet);
	}
}
void refillNewWeapon(int magSize,vector<sBullet*> &vMagazine,vector<sBullet*> &vBullets)
{
	vMagazine.resize(magSize);
	for (int i = 0; i < magSize; i++)
	{
		vMagazine[i] = move(vBullets[i]);
	}
	
	
}
void moveBullets(int magSize,vector<sBullet*> &vMagazine,float frameTime) 
{
	
	for (int i=0; i<magSize;i++) 
	{
		if (vMagazine[i]->isFired)
		{ 
			//vMagazine[i]->model->Move(vMagazine[i]->tragectory.x, vMagazine[i]->tragectory.y, vMagazine[i]->tragectory.z);
			vMagazine[i]->model->Move(5.0f*frameTime, 5.0f*frameTime, 5.0f*frameTime);
		}
	}
}