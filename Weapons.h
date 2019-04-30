#pragma once
#include "Engine.h"
#include <vector>
#include <SFML/Audio.hpp>
#include <memory>

using namespace tle;

enum fireModes { Single, Burst, Auto };

const int soundVolume = 50;

struct sWeapon
{
	string name;
	IMesh* weaponMesh;
	IModel* weaponModel;
	fireModes fireMode;
	int magCapacity;
	int magAmount;
	float fireRate;
	float gunlength;
	sf::SoundBuffer shootingBuffer;
	sf::Sound shootingSound;
};

struct M4 :public sWeapon 
{	
	M4 (int spawnX, int SpawnY, int SpawnZ)
	{
		gunlength = 35.0f;
		weaponMesh = myEngine->LoadMesh("M4Colt.x");
		name = "m4";
		weaponModel = weaponMesh->CreateModel(spawnX, SpawnY, SpawnZ);
		weaponModel->Scale(13);
		weaponModel->RotateLocalZ(90);
		weaponModel->RotateLocalX(180);
		magCapacity = 30;
		magAmount = 30;
		fireRate = 0.04f;
	
		shootingBuffer.loadFromFile("soundeffects\\gunshot.wav");
		shootingSound.setBuffer(shootingBuffer);
		shootingSound.setVolume(soundVolume);
	}
};

struct AK :public sWeapon
{
	AK(int spawnX,int SpawnY,int SpawnZ) 
	{
		gunlength = 35.0f;
		name = "AK-47";
		weaponMesh = myEngine->LoadMesh("kalashinkov.x");
		weaponModel = weaponMesh->CreateModel(spawnX,SpawnY, SpawnZ);
        weaponModel->Scale(13);
    	weaponModel->RotateLocalZ(90);
		weaponModel->RotateLocalX(180);
		magCapacity = 30;
		magAmount = 30;
		fireRate = 0.04f;
		
		shootingBuffer.loadFromFile("soundeffects\\ak-47.wav");
		shootingSound.setBuffer(shootingBuffer);
		shootingSound.setVolume(soundVolume);
	}
};

struct AR_18 :public sWeapon
{

	AR_18(int spawnX, int SpawnY, int SpawnZ)
	{
		gunlength = 35.0f;
		name = "AR-18";
		weaponMesh = myEngine->LoadMesh("ar18_rifle.x");
		weaponModel = weaponMesh->CreateModel(spawnX, SpawnY, SpawnZ);
		weaponModel->Scale(13);
		weaponModel->RotateLocalZ(90);
		weaponModel->RotateLocalX(180);
		magCapacity = 20;
		magAmount = 20;
		fireRate = 0.2f;
		shootingBuffer.loadFromFile("soundeffects\\AR18.wav");
		shootingSound.setBuffer(shootingBuffer);
		shootingSound.setVolume(soundVolume);
	}
};

struct MINI_UZI :public sWeapon
{
	MINI_UZI (int spawnX, int SpawnY, int SpawnZ)
	{
		gunlength = 20.0f;
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
		gunlength = 35.0f;
		name = "Thompson";
		weaponMesh = myEngine->LoadMesh("TommyGun.x");
		weaponModel = weaponMesh->CreateModel(spawnX, SpawnY, SpawnZ);
		weaponModel->Scale(13);
		weaponModel->RotateLocalZ(90);
		weaponModel->RotateLocalX(180);
		magCapacity = 20;
		magAmount = 20;
		fireRate = 0.07f;
		shootingBuffer.loadFromFile("soundeffects\\tommy.wav");
		shootingSound.setBuffer(shootingBuffer);
		shootingSound.setVolume(soundVolume);
	}
};

struct MP5 :public sWeapon
{
	MP5 (int spawnX, int SpawnY, int SpawnZ)
	{
		gunlength = 33.0f;
		name = "MP5";
		weaponMesh = myEngine->LoadMesh("MachineGun.x");
		weaponModel = weaponMesh->CreateModel(spawnX, SpawnY, SpawnZ);
		weaponModel->Scale(13);
		weaponModel->RotateLocalZ(90);
		weaponModel->RotateLocalX(180);
		magCapacity = 25;
		magAmount = 25;
		fireRate = 0.07f;
		shootingBuffer.loadFromFile("soundeffects\\MP5.wav");
		shootingSound.setBuffer(shootingBuffer);
		shootingSound.setVolume(soundVolume);
	}
};

struct  Glock:public sWeapon
{
	Glock(int spawnX, int SpawnY, int SpawnZ)
	{
		gunlength = 27.0f;
		name = "Glock";
		weaponMesh = myEngine->LoadMesh("glock.x");
		weaponModel = weaponMesh->CreateModel(spawnX, SpawnY, SpawnZ);
		weaponModel->Scale(13);
		weaponModel->RotateLocalZ(90);
		weaponModel->RotateLocalX(180);
		magCapacity = 7;
		magAmount = 7;
		fireRate = 0.3f;
		shootingBuffer.loadFromFile("soundeffects\\glock.wav");
		shootingSound.setBuffer(shootingBuffer);
		shootingSound.setVolume(soundVolume);
	}
};

void spawnGuns(deque <unique_ptr<sWeapon>> &vGuns);
