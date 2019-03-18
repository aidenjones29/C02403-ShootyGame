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
 			vMagazine[i]->model->MoveLocalZ(25.0f*frameTime);
			vMagazine[i]->timeAlive = vMagazine[i]->timeAlive + frameTime;
		}
		if (vMagazine[i]->timeAlive > 1.0f)
		{
			vMagazine[i]->isFired = false;
			vMagazine[i]->model->SetPosition(0.0f, -15.0f, 0.0f);
			vMagazine[i]->timeAlive = 0.0f;
		}
	}
}
//void fireBullets()