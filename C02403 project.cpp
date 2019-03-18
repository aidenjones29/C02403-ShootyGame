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


enum fireModes { Single, Burst, Auto };
enum standingState { Standing, Crouching, Prone };

using namespace tle;
using namespace std;

const float upperCamYMax = -50.0f;
const float lowerCamYMax = 50.0f;
const int numGuns = 6;
float time = 0;


struct Weapon
{
	IMesh* weaponMesh;
	IModel* weaponModel;
	float fireRate;
	fireModes fireMode;
	int magCapacity;
	int magAmount;
};
struct AK :public Weapon {};


void movement(I3DEngine* myEngine, IModel* camDummy, float& currentCamRotation, float& currentCamY, float& camYCounter, standingState& currPlayerStandState, float& movementSpeed, float& currentMoveSpeed);

void gunSwapAndDrop(I3DEngine* myEngine, float& interactionZspeed, float& currentInteractionDistance, IModel*& interactionDummy, bool& canCollide, Weapon* WeaponArray[], int whichGunEquipped, IModel*& cameraDummy, float& oldPlayerX, float& oldPlayerZ);

void desktopResolution(int& horizontal, int& vertical);

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine(kTLX);
	int horizontal = 0; int vertical = 0;
	desktopResolution(horizontal, vertical);
	myEngine->StartFullscreen(horizontal, vertical);
	myEngine->StartMouseCapture();
	vector<sBullet*> vBullets;
	vector<sBullet*> vMagazine;
	vector<sTarget*> vTargets;


	// Add default folder for meshes and other media
	myEngine->AddMediaFolder(".\\Media");
	ICamera* myCam = myEngine->CreateCamera(kManual, 0, 0, 0);

	vector <Weapon*> WeaponArray;

	for (int i = 0; i < numGuns; i++)
	{
		Weapon* Gun(new Weapon);
		WeaponArray.push_back(Gun);
	}

	ISprite* Crosshair = myEngine->CreateSprite("crosshair.png", (horizontal / 2) - 60 , (vertical / 2) - 60);

	IFont* MainFont = myEngine->LoadFont("D Day Stencil", 60);

	IMesh* dummyMesh = myEngine->LoadMesh("Dummy.x");
	IMesh* bulletMesh = myEngine->LoadMesh("Bullet.x");
	IMesh* targetMesh = myEngine->LoadMesh("Target.x");

	IModel* target[3];
	IModel* fence[80];
	IModel* cameraDummy = dummyMesh->CreateModel(5, 15, 80);
	IModel* interactionDummy = dummyMesh->CreateModel(0, 0, 0);
	IModel* gunFireTest = dummyMesh->CreateModel(0, 0, 0);

	gunFireTest->AttachToParent(cameraDummy);

	spawnTargets(targetMesh, vTargets);

	WeaponArray[0]->weaponMesh = myEngine->LoadMesh("M4Colt.x");
	WeaponArray[0]->magCapacity = 30;
	WeaponArray[0]->magAmount = 30;
	WeaponArray[1]->weaponMesh = myEngine->LoadMesh("ar18_rifle.x");
	WeaponArray[2]->weaponMesh = myEngine->LoadMesh("kalashinkov.x");
	WeaponArray[3]->weaponMesh = myEngine->LoadMesh("TommyGun.x");
	WeaponArray[4]->weaponMesh = myEngine->LoadMesh("Mini_Uzi.x");
	WeaponArray[5]->weaponMesh = myEngine->LoadMesh("MachineGun.x");

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

	int whichGunEquipped = numGuns;

	/**** Set up your scene here ****/
	CreateFences(myEngine, fence); CreateScene(myEngine); CreateWalls(myEngine);

	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		frameTime = myEngine->Timer();
		// Draw the scene
		myEngine->DrawScene();

		if (whichGunEquipped < numGuns)
		{
			ammoText << WeaponArray[whichGunEquipped]->magAmount << " / " << WeaponArray[whichGunEquipped]->magCapacity;
			MainFont -> Draw(ammoText.str(), (horizontal / 2) - 60, (vertical / 2) - 60);
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

		if (!FenceCollision(cameraDummy))
		{
			cameraDummy->SetPosition(oldPlayerX, 15, oldPlayerZ);
		}

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
			WeaponArray[whichGunEquipped]->weaponModel->RotateY(rand());
			whichGunEquipped = numGuns;
		}

		interactionDummy->MoveLocalZ(interactionZspeed);
		currentInteractionDistance += interactionZspeed;

		if (myEngine->KeyHeld(Mouse_LButton))
		{
			time = time + frameTime;

			for (int i = 0; i < 100; i++)
			{
				if (time > 0.04f)
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
						time = 0.0f;
					}
				}
			}
		}

		if (myEngine->KeyHit(Key_Space))
		{
			reloadMagazine(100, vMagazine);
		}

		if (myEngine->KeyHit(Key_N))
		{
			for (auto& i : vTargets)
			{
				i->model->SetY(12);
				i->state = Ready;
			}
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

