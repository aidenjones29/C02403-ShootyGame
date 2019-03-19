#pragma once
#include "Engine.h"
#include <vector>
using namespace tle;
enum fireModes { Single, Burst, Auto };
struct sWeapon
{
	string name;
	IMesh* weaponMesh;
	IModel* weaponModel;
	fireModes fireMode;
	int magCapacity;
	int magAmount;
	float fireRate;
};
struct M4 :public sWeapon 
{	
	M4 (int spawnX, int SpawnY, int SpawnZ)
	{
		weaponMesh = myEngine->LoadMesh("M4Colt.x");
		name = "m4";
		weaponModel = weaponMesh->CreateModel(spawnX, SpawnY, SpawnZ);
		weaponModel->Scale(13);
		weaponModel->RotateLocalZ(90);
		weaponModel->RotateLocalX(180);
		magCapacity = 30;
		magAmount = 30;
		fireRate = 0.04f;
	}
};
struct AK :public sWeapon
{
	AK(int spawnX,int SpawnY,int SpawnZ) 
	{
		name = "AK-47";
		weaponMesh = myEngine->LoadMesh("kalashinkov.x");
		weaponModel = weaponMesh->CreateModel(spawnX,SpawnY, SpawnZ);
        weaponModel->Scale(13);
    	weaponModel->RotateLocalZ(90);
		weaponModel->RotateLocalX(180);
		magCapacity = 30;
		magAmount = 30;
		fireRate = 0.04f;
	}
};
struct AR_18 :public sWeapon
{
	string name = "AR-18";
	IMesh* weaponMesh = myEngine->LoadMesh("ar18_rifle.x");
	IModel* weaponModel;
	fireModes fireMode;
	int magCapacity = 20;
	int magAmount = 20;
	float fireRate = 0.2f;
	AR_18(int spawnX, int SpawnY, int SpawnZ)
		{
		 name = "AR-18";
		 weaponMesh = myEngine->LoadMesh("ar18_rifle.x");
	weaponModel = weaponMesh->CreateModel(spawnX, SpawnY, SpawnZ);
	weaponModel->Scale(13);
	weaponModel->RotateLocalZ(90);
	weaponModel->RotateLocalX(180);
	 magCapacity = 20;
	 magAmount = 20;
	 fireRate = 0.2f;
	}
};
struct MINI_UZI :public sWeapon
{
	MINI_UZI (int spawnX, int SpawnY, int SpawnZ)
	{

		name = "Uzi";
		weaponMesh = myEngine->LoadMesh("Mini_Uzi.x");
		weaponModel = weaponMesh->CreateModel(spawnX, SpawnY, SpawnZ);
		weaponModel->Scale(13);
		weaponModel->RotateLocalZ(90);
		weaponModel->RotateLocalX(180);
		magCapacity = 25;
		magAmount = 25;
		fireRate = 0.03f;
	}
};
struct TOMMY_GUN :public sWeapon
{
	TOMMY_GUN (int spawnX, int SpawnY, int SpawnZ)
	{
		name = "Thompson";
		weaponMesh = myEngine->LoadMesh("TommyGun.x");
		weaponModel = weaponMesh->CreateModel(spawnX, SpawnY, SpawnZ);
		weaponModel->Scale(13);
		weaponModel->RotateLocalZ(90);
		weaponModel->RotateLocalX(180);
		magCapacity = 20;
		magAmount = 20;
		fireRate = 0.07f;
	}
};
struct MP5 :public sWeapon
{
	MP5 (int spawnX, int SpawnY, int SpawnZ)
	{
		name = "MP5";
		weaponMesh = myEngine->LoadMesh("MachineGun.x");
		weaponModel = weaponMesh->CreateModel(spawnX, SpawnY, SpawnZ);
		weaponModel->Scale(13);
		weaponModel->RotateLocalZ(90);
		weaponModel->RotateLocalX(180);
		magCapacity = 25;
		magAmount = 25;
		fireRate = 0.07f;
	}
};

void spawnGuns(vector <sWeapon*> &vGuns);


//struct / :public sWeapon
//{
//	/(int spawnX, int SpawnY, int SpawnZ)
//	{
//		name = "/";
//	weaponMesh = myEngine->LoadMesh("/.x");
//	weaponModel = weaponMesh->CreateModel(spawnX, SpawnY, SpawnZ);
//	weaponModel->Scale(13);
//	weaponModel->RotateLocalZ(90);
//	weaponModel->RotateLocalX(180);
//	magCapacity = /;
//	magAmount = /;
//	fireRate = /;
//	}
//};