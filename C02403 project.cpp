// C02403 project.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <vector>
#include <vector>
#include <iostream>
#include <sstream>
#include "ModelCreation.h"
#include "Collisions.h"
#include "wtypes.h" 
#include "Bullets.h"
#include "Targets.h"
#include <stdlib.h> // General console window includes
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <SFML/Audio.hpp>


enum fireModes { Single, Burst, Auto };
enum standingState { Standing, Crouching, Prone };

using namespace tle;
using namespace std;

const float upperCamYMax = -50.0f;
const float lowerCamYMax = 50.0f;

const int numGuns = 6;

float Time = 0;
float countDownTime = 1.0f;

float WeaponTime = 0;
bool canShoot = true;

int bulletsFired = 0;
struct Weapon
{
	string name;
	IMesh* weaponMesh;
	IModel* weaponModel;
	float fireRate;
	fireModes fireMode;
	int magCapacity;
	int magAmount;
	sf::SoundBuffer shootingbuffer;
	sf::Sound shootingsound;
};


void Fire(IModel* &cameraDummy, float& frametime, float& shoottimer);

void movement(I3DEngine* myEngine, IModel* camDummy, float& currentCamRotation, float& currentCamY, float& camYCounter, standingState& currPlayerStandState, float& movementSpeed, float& currentMoveSpeed);

void gunSwapAndDrop(I3DEngine* myEngine, float& interactionZspeed, float& currentInteractionDistance, IModel*& interactionDummy, bool& canCollide, Weapon* WeaponArray[], int whichGunEquipped, IModel*& cameraDummy, float& oldPlayerX, float& oldPlayerZ);

void desktopResolution(int& horizontal, int& vertical);

vector<sBullet*> vBullets;
vector<sBullet*> vMagazine;
vector<sTarget*> vTargets;	
vector <Weapon*> WeaponArray;


int whichGunEquipped = numGuns;
fireModes CurrentFireMode = Auto;
I3DEngine* myEngine = New3DEngine(kTLX);


void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
    
	int horizontal = 0; int vertical = 0;
	float reloadTimer=0;
	desktopResolution(horizontal, vertical);
	myEngine->StartFullscreen(horizontal, vertical);
	myEngine->StartMouseCapture();
	


	// Add default folder for meshes and other media
	myEngine->AddMediaFolder(".\\Media");
	ICamera* myCam = myEngine->CreateCamera(kManual, 0, 0, 0);



	for (int i = 0; i < numGuns; i++)
	{
		Weapon* Gun(new Weapon);
		WeaponArray.push_back(Gun);
	}

	ISprite* Crosshair = myEngine->CreateSprite("crosshair.png", (horizontal / 2) - 60 , (vertical / 2) - 60);
	ISprite* ammoUI = myEngine->CreateSprite("ammoUIPNG.png", 10 , vertical - 150);

	ISprite* fireModeSemi = myEngine->CreateSprite("SemiAutoUI.png", 13, vertical - 105);
	ISprite* fireModeBurstUI = myEngine->CreateSprite("burstFireUI.png", 29, vertical - 105);
	ISprite* fireModeFullUI = myEngine->CreateSprite("FullAutoUI.png", 43, vertical - 105);

	IFont* MainFont = myEngine->LoadFont("D Day Stencil", 60);

	IMesh* dummyMesh = myEngine->LoadMesh("Dummy.x");
	IMesh* bulletMesh = myEngine->LoadMesh("Bullet.x");
	IMesh* targetMesh = myEngine->LoadMesh("Target.x");

	
	IModel* fence[80];
	IModel* cameraDummy = dummyMesh->CreateModel(5, 15, 80);
	IModel* interactionDummy = dummyMesh->CreateModel(0, 0, 0);
	IModel* gunFireTest = dummyMesh->CreateModel(0, 0, 0);

	gunFireTest->AttachToParent(cameraDummy);

	spawnTargets(targetMesh, vTargets);


	/*WeaponArray[1]->shootingbuffer1.loadFromFile("soundeffects\\gunshot.wav");
	WeaponArray[1]->shootingsound.setBuffer(WeaponArray[1]->shootingbuffer1);
	WeaponArray[1]->shootingsound.setPitch(1.0);
	WeaponArray[1]->shootingsound.setVolume(20.0f);

	WeaponArray[2]->shootingbuffer2.loadFromFile("soundeffects\\gunshot.wav");
	WeaponArray[2]->shootingsound.setBuffer(WeaponArray[2]->shootingbuffer2);
	WeaponArray[2]->shootingsound.setPitch(1.0);
	WeaponArray[2]->shootingsound.setVolume(20.0f);

	WeaponArray[3]->shootingbuffer3.loadFromFile("soundeffects\\gunshot.wav");
	WeaponArray[3]->shootingsound.setBuffer(WeaponArray[3]->shootingbuffer3);

	WeaponArray[3]->shootingsound.setPitch(1.0);
	WeaponArray[3]->shootingsound.setVolume(20.0f);

	WeaponArray[4]->shootingbuffer4.loadFromFile("soundeffects\\gunshot.wav");
	WeaponArray[4]->shootingsound.setBuffer(WeaponArray[4]->shootingbuffer4);
	WeaponArray[4]->shootingsound.setPitch(1.0);
	WeaponArray[4]->shootingsound.setVolume(20.0f);

	WeaponArray[5]->shootingbuffer5.loadFromFile("soundeffects\\gunshot.wav");
	WeaponArray[5]->shootingsound.setBuffer(WeaponArray[5]->shootingbuffer5);
	WeaponArray[5]->shootingsound.setPitch(1.0);
	WeaponArray[5]->shootingsound.setVolume(20.0f);*/

	WeaponArray[0]->weaponMesh = myEngine->LoadMesh("M4Colt.x");
	WeaponArray[0]->name = "M4";
	WeaponArray[0]->magCapacity = 30;
	WeaponArray[0]->magAmount = 30;
	WeaponArray[0]->fireRate = 0.04f;
	WeaponArray[0]->shootingbuffer.loadFromFile("soundeffects\\gunshot.wav");
	WeaponArray[0]->shootingsound.setBuffer(WeaponArray[0]->shootingbuffer);
	WeaponArray[0]->shootingsound.setPitch(1.0);
	WeaponArray[0]->shootingsound.setVolume(20.0f);

	WeaponArray[1]->weaponMesh = myEngine->LoadMesh("ar18_rifle.x");
	WeaponArray[1]->name = "AR-18";
	WeaponArray[1]->magCapacity = 20;
	WeaponArray[1]->magAmount = 20;
	WeaponArray[1]->fireRate = 0.2f;

	WeaponArray[2]->weaponMesh = myEngine->LoadMesh("kalashinkov.x");
	WeaponArray[2]->name = "AK-47";
	WeaponArray[2]->magCapacity = 30;
	WeaponArray[2]->magAmount = 30;
	WeaponArray[2]->fireRate = 0.04f;

	WeaponArray[3]->weaponMesh = myEngine->LoadMesh("TommyGun.x");
	WeaponArray[3]->name = "Thompson";
	WeaponArray[3]->magCapacity = 20;
	WeaponArray[3]->magAmount = 20;
	WeaponArray[3]->fireRate = 0.07f;

	WeaponArray[4]->weaponMesh = myEngine->LoadMesh("Mini_Uzi.x");
	WeaponArray[4]->name = "Uzi";
	WeaponArray[4]->magCapacity = 25;
	WeaponArray[4]->magAmount = 25;
	WeaponArray[4]->fireRate = 0.03f;

	WeaponArray[5]->weaponMesh = myEngine->LoadMesh("MachineGun.x");
	WeaponArray[5]->name = "MP5";
	WeaponArray[5]->magCapacity = 25;
	WeaponArray[5]->magAmount = 25;
	WeaponArray[5]->fireRate = 0.07f;

	WeaponArray[0]->weaponModel = WeaponArray[0]->weaponMesh->CreateModel(-3, 8, 43);
	WeaponArray[1]->weaponModel = WeaponArray[1]->weaponMesh->CreateModel(5, 8, 43);
	WeaponArray[2]->weaponModel = WeaponArray[2]->weaponMesh->CreateModel(32, 8, 43);
	WeaponArray[3]->weaponModel = WeaponArray[3]->weaponMesh->CreateModel(38, 8, 43);
	WeaponArray[4]->weaponModel = WeaponArray[4]->weaponMesh->CreateModel(66, 8, 43);
	WeaponArray[5]->weaponModel = WeaponArray[5]->weaponMesh->CreateModel(75, 8, 43);

	for (int i = 0; i < numGuns; i++)
	{
		WeaponArray[i]->weaponModel->Scale(13);
		WeaponArray[i]->weaponModel->RotateLocalZ(90);
		WeaponArray[i]->weaponModel->RotateLocalX(180);
	}
	spawnBullets(500, bulletMesh, vBullets);
	refillNewWeapon(100, vMagazine, vBullets);

	interactionDummy->Scale(7);
	interactionDummy->AttachToParent(myCam);

	myCam->AttachToParent(cameraDummy);
	myCam->SetMovementSpeed(0.0f);
	cameraDummy->RotateY(180);

	float frameTime = myEngine->Timer();
	float movementSpeed = frameTime;
	float shoottimer = 0.04f;
	float currentMoveSpeed = 50.0f;

	float mouseMoveX = 0.0f;
	float mouseMoveY = 0.0f;
	float camYCounter = 0.0f;

	float interactionZspeed = 0.0f;
	float currentInteractionDistance = 0.0f;
	bool canCollide = false;

	float oldPlayerX = 0;
	float oldPlayerZ = 0;

	standingState currPlayerStandState = Standing;
	bool crouched = false;
	bool prone = false;

	stringstream ammoText;

	


	/**** Set up your scene here ****/
	CreateFences(myEngine, fence); CreateScene(myEngine); CreateWalls(myEngine);

	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		WeaponTime = WeaponTime + frameTime;
		frameTime = myEngine->Timer();
		// Draw the scene
		myEngine->DrawScene();

		if (CurrentFireMode == Auto)
		{
			fireModeBurstUI->SetPosition(29, vertical - 105);
			fireModeFullUI->SetPosition(43, vertical - 105);
		}
		else if (CurrentFireMode == Burst)
		{
			fireModeFullUI->SetPosition(-28, vertical - 105);
		}
		else
		{
			fireModeFullUI->SetPosition(-28, vertical - 105);
			fireModeBurstUI->SetPosition(-28, vertical - 105);
		}

		if (whichGunEquipped < numGuns)
		{
			ammoText << WeaponArray[whichGunEquipped]->magAmount << " / " << WeaponArray[whichGunEquipped]->magCapacity;
			MainFont->Draw(ammoText.str(), 100, vertical - 90, kWhite);
			ammoText.str("");
		}

		oldPlayerX = cameraDummy->GetX();
		oldPlayerZ = cameraDummy->GetZ();

		movementSpeed = currentMoveSpeed * frameTime;

		/**** Update your scene each frame here ****/
		mouseMoveX = myEngine->GetMouseMovementX();
		mouseMoveY = myEngine->GetMouseMovementY();

		if (camYCounter < upperCamYMax && mouseMoveY < 0) { mouseMoveY = 0; }
		if (camYCounter > lowerCamYMax && mouseMoveY > 0) { mouseMoveY = 0; }

		camYCounter += mouseMoveY * 0.1f;

		movement(myEngine, cameraDummy, mouseMoveX, mouseMoveY, camYCounter, currPlayerStandState, movementSpeed, currentMoveSpeed);

		//if (!FenceCollision(cameraDummy))
		//{
		//	cameraDummy->SetPosition(oldPlayerX, 15, oldPlayerZ);
		//}

		if (myEngine->KeyHit(Key_E))
		{
			interactionZspeed = 0.0f;
			currentInteractionDistance = 0.0f;
			interactionDummy->SetLocalPosition(0, 0, 0);
			interactionZspeed = 0.01f;
			canCollide = true;
		}

		for (int i = 0; i < numGuns; i++)
		{
			if (canCollide == true && gunInteraction(interactionDummy, WeaponArray[i]->weaponModel) && whichGunEquipped == numGuns)
			{
				whichGunEquipped = i;
				WeaponArray[i]->weaponModel->ResetOrientation();
				WeaponArray[i]->weaponModel->AttachToParent(cameraDummy);
				WeaponArray[i]->weaponModel->SetLocalPosition(2.0f, -2.0f, 7.0f);
				WeaponArray[i]->weaponModel->RotateY(-0.2f);
				reloadMagazine(WeaponArray[whichGunEquipped]->magCapacity, vMagazine);
				WeaponArray[whichGunEquipped]->magAmount = WeaponArray[whichGunEquipped]->magCapacity;
			}
		}

		if (currentInteractionDistance >= 2.0f)
		{
			canCollide = false;
			interactionZspeed = 0.0f;
			currentInteractionDistance = 0.0f;
			interactionDummy->SetLocalPosition(0, 0, 0);
		}

		if (myEngine->KeyHit(Key_Q) && whichGunEquipped < numGuns)
		{
			WeaponArray[whichGunEquipped]->weaponModel->DetachFromParent();
			WeaponArray[whichGunEquipped]->weaponModel->SetPosition(oldPlayerX, 0.2, oldPlayerZ);
			WeaponArray[whichGunEquipped]->weaponModel->RotateLocalZ(90.0f);
			WeaponArray[whichGunEquipped]->weaponModel->RotateY(rand());
			whichGunEquipped = numGuns;
		}

		interactionDummy->MoveLocalZ(interactionZspeed);
		currentInteractionDistance += interactionZspeed;

		
		if (myEngine->KeyHit(Key_X) )
		{
			if (CurrentFireMode == Auto)
			{
			CurrentFireMode = Burst;
			}
			else if (CurrentFireMode == Burst)
			{
				CurrentFireMode = Single;
			}
			else if (CurrentFireMode == Single)
			{
				CurrentFireMode = Auto;
			}
		}

		if (myEngine->KeyHeld(Key_R))
		{
			reloadTimer += frameTime;
			if (reloadTimer > 1.2f)
			{
				reloadMagazine(WeaponArray[whichGunEquipped]->magCapacity, vMagazine);
				WeaponArray[whichGunEquipped]->magAmount = WeaponArray[whichGunEquipped]->magCapacity;
				reloadTimer = 0;
			}
		}

		if (myEngine->KeyHit(Key_N))
		{
			for (auto& i : vTargets)
			{
				i->model->SetY(12);
				i->state = Ready;
			}
		}

		if (whichGunEquipped != numGuns)
		{
			Fire(cameraDummy,frameTime, shoottimer);
		}



		moveBullets(100, vMagazine, frameTime);
		moveTargets(vTargets, frameTime);
		bulletToTarget(vTargets, vMagazine);
		//END
	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}

void movement(I3DEngine* myEngine, IModel* camDummy, float& currentCamX, float &mouseMoveY, float& camYCounter, standingState& currPlayerStandState, float& movementSpeed, float& currentMoveSpeed)
{
	if (camYCounter > upperCamYMax && mouseMoveY < 0)
	{
		camDummy->RotateLocalX(mouseMoveY * 0.1f);
	}

	if (camYCounter < lowerCamYMax && mouseMoveY > 0)
	{
		camDummy->RotateLocalX(mouseMoveY * 0.1f);
	}

	camDummy->RotateY(currentCamX * 0.1f);

	if (myEngine->KeyHeld(Key_W))
	{
		camDummy->MoveLocalZ(movementSpeed);
	}

	if (myEngine->KeyHeld(Key_S))
	{
		camDummy->MoveLocalZ(-movementSpeed);
	}

	if (myEngine->KeyHeld(Key_A))
	{
		camDummy->MoveLocalX(-movementSpeed);
	}

	if (myEngine->KeyHeld(Key_D))
	{
		camDummy->MoveLocalX(movementSpeed);
	}

	if (myEngine->KeyHeld(Key_Escape))
	{
		myEngine->Stop();
	}

	if (myEngine->KeyHit(Key_C))
	{
		if (currPlayerStandState == Standing)
		{
			currPlayerStandState = Crouching;
			currentMoveSpeed = 25.0f;
		}
		else if (currPlayerStandState == Crouching)
		{
			currPlayerStandState = Prone;
			currentMoveSpeed = 10.0f;
		}
		else if (currPlayerStandState == Prone)
		{
			currPlayerStandState = Standing;
			currentMoveSpeed = 50.0f;
		}
	}

	if (currPlayerStandState == Crouching)
	{
		camDummy->SetY(9);
	}
	else if (currPlayerStandState == Prone)
	{
		camDummy->SetY(3);
	}
	else if (currPlayerStandState == Standing)
	{
		camDummy->SetY(15);
	}
}

void gunSwapAndDrop(I3DEngine* myEngine, float& interactionZspeed, float& currentInteractionDistance, IModel*& interactionDummy, bool& canCollide, Weapon* WeaponArray[], int whichGunEquipped, IModel*& cameraDummy, float& oldPlayerX, float& oldPlayerZ)
{
	if (myEngine->KeyHit(Key_E))
	{
		interactionZspeed = 0.0f;
		currentInteractionDistance = 0.0f;
		interactionDummy->SetLocalPosition(0, 0, 0);
		interactionZspeed = 0.01f;
		canCollide = true;
	}

	for (int i = 0; i < numGuns; i++)
	{
		if (canCollide == true && gunInteraction(interactionDummy, WeaponArray[i]->weaponModel) && whichGunEquipped == numGuns)
		{
			whichGunEquipped = i;
			WeaponArray[i]->weaponModel->ResetOrientation();
			WeaponArray[i]->weaponModel->AttachToParent(cameraDummy);
			WeaponArray[i]->weaponModel->SetLocalPosition(2.0f, -2.0f, 7.0f);
			WeaponArray[i]->weaponModel->RotateY(-0.2f);
		}
	}

	if (currentInteractionDistance >= 2.0f)
	{
		canCollide = false;
		interactionZspeed = 0.0f;
		currentInteractionDistance = 0.0f;
		interactionDummy->SetLocalPosition(0, 0, 0);
	}

	if (myEngine->KeyHit(Key_R) && whichGunEquipped < numGuns)
	{
		WeaponArray[whichGunEquipped]->weaponModel->DetachFromParent();
		WeaponArray[whichGunEquipped]->weaponModel->SetPosition(oldPlayerX, 0.2, oldPlayerZ);
		WeaponArray[whichGunEquipped]->weaponModel->RotateLocalZ(90.0f);
		whichGunEquipped = numGuns;
	}
}


void desktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;						      //Gets a handle to the current window
	const HWND hDesktop = GetDesktopWindow(); //Gets the size and places it to a variable
	GetWindowRect(hDesktop, &desktop);        //Gets the coordinates for the corner of the screen

	horizontal = desktop.right;               //Holds the values for the screen resolution.
	vertical = desktop.bottom;				  //Holds the values for the screen resolution.
}

void Fire(IModel* &cameraDummy, float& frameTime, float& shoottimer)
{
	switch (CurrentFireMode)
	{
	case Auto:
		if (myEngine->KeyHeld(Mouse_LButton))
		{
			shoottimer -= frameTime;
			if (shoottimer <= 0 && WeaponArray[whichGunEquipped]->magAmount > 0)
			{
				WeaponArray[whichGunEquipped]->shootingsound.play();
				shoottimer = WeaponArray[whichGunEquipped]->fireRate * 3;
			}

			for (int i = 0; i < WeaponArray[whichGunEquipped]->magCapacity; i++)
			{
				if (WeaponTime > WeaponArray[whichGunEquipped]->fireRate)
				{
					if (vMagazine[i]->status == Reloaded)
					{
						float matrix[4][4];
						cameraDummy->GetMatrix(&matrix[0][0]);
						vMagazine[i]->model->SetMatrix(&matrix[0][0]);
						vMagazine[i]->model->MoveLocalZ(10.0f);
						vMagazine[i]->model->RotateLocalX(90.0f);
						vMagazine[i]->model->Scale(0.004f);
						vMagazine[i]->status = Fired;
						WeaponArray[whichGunEquipped]->magAmount--;
						WeaponTime = 0.0f;

					}
				}

			}
		}
		break;
	case Burst:
		
		if (myEngine->KeyHit(Mouse_LButton))
		{
			canShoot = false;
		}
		
		if (!canShoot)
		{
			for (int i = 0; i < WeaponArray[whichGunEquipped]->magCapacity; i++)
			{
				if (WeaponTime > (WeaponArray[whichGunEquipped]->fireRate / 2))
				{
					if (vMagazine[i]->status == Reloaded)
					{
						WeaponArray[whichGunEquipped]->shootingsound.play();
						float matrix[4][4];
						cameraDummy->GetMatrix(&matrix[0][0]);
						vMagazine[i]->model->SetMatrix(&matrix[0][0]);
						vMagazine[i]->model->MoveLocalZ(10.0f);
						vMagazine[i]->model->RotateLocalX(90.0f);
						vMagazine[i]->model->Scale(0.004f);
						vMagazine[i]->status = Fired;
						WeaponArray[whichGunEquipped]->magAmount--;
						WeaponTime = 0.0f;
						bulletsFired++;
					}

				}
			}
		}
		if (bulletsFired == 3)
		{
			canShoot = true;
			bulletsFired = 0;
		}



		break;
	case Single:
		if (myEngine->KeyHit(Mouse_LButton))
		{
			
			for (int i = 0; i < WeaponArray[whichGunEquipped]->magCapacity; i++)
			{

				if (vMagazine[i]->status == Reloaded)
				{
					WeaponArray[whichGunEquipped]->shootingsound.play();
					float matrix[4][4];
					cameraDummy->GetMatrix(&matrix[0][0]);
					vMagazine[i]->model->SetMatrix(&matrix[0][0]);
					vMagazine[i]->model->MoveLocalZ(10.0f);
					vMagazine[i]->model->RotateLocalX(90.0f);
					vMagazine[i]->model->Scale(0.004f);
					vMagazine[i]->status = Fired;
					WeaponArray[whichGunEquipped]->magAmount--;
					break;
				}

			}



			break;

		}
		

	}
}

