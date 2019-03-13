#pragma once
#include "Bullets.h"

void spawnBullets(int maxBullets,IMesh* bulletMesh, vector<sBullet*> &vBullets)
{
	vBullets.resize(maxBullets);
	for (int i = 0; i < maxBullets; i++)
	{
		sBullet* bullet = new sBullet;
		bullet->model = bulletMesh->CreateModel(0, 15, 0);
		vBullets.push_back(bullet);
	}
}
//void refillNewWeapon(int magSize)
//{
//	bullets->resize(magSize);
//	for (int i = 0; i < magSize; i++)
//	{
//		bullets->push_back(bullet);
//	}
//}
//void moveBullets(int magSize) 
//{
//	for (int i; i<magSize;i++) 
//	{
//		for(auto i :bullets)
//		 
//		{
//		
//		}
//	
//	}
//}