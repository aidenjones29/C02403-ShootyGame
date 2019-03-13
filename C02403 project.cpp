// C02403 project.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
#include "ModelCreation.h"
#include "Collisions.h"
#include "wtypes.h" 
#include <iostream>
#include <vector>
#include "Bullets.h"



struct vector3D
{
	float x;
	float y;
	float z;

};

using namespace tle;

const float movementSpeed = 0.04f;
const float upperCamYMax = -50.0f;
const float lowerCamYMax = 50.0f;
const int numGuns = 6;

void movement(I3DEngine* myEngine, IModel* camDummy, float& currentCamRotation, float& currentCamY, float& camYCounter);

void desktopResolution(int& horizontal, int& vertical);

//struct test
//{
//	int mX;
//	int mY;
//
//	test(int x, int y)
//	{
//		mX = x;
//		mY = y;
//	}
//
//	int DoThing()
//	{
//		return (mX * mY);
//	}
//};
//
//struct newTest : public test
//{
//};

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine(kTLX);
	int horizontal = 0; int vertical = 0;
	desktopResolution(horizontal, vertical);
	myEngine->StartWindowed(horizontal, vertical);
	myEngine->StartMouseCapture();
	vector<sBullet*> vBullets;
	vector<sBullet*> vMagazine;


	// Add default folder for meshes and other media
	myEngine->AddMediaFolder( ".\\Media" );
	ICamera* myCam = myEngine->CreateCamera(kManual, 0, 0, 0);

	IMesh* dummyMesh = myEngine->LoadMesh("Dummy.x");
	IMesh* M4Mesh = myEngine->LoadMesh("M4Colt.x");
	IMesh* stenMK2Mesh = myEngine->LoadMesh("ar18_rifle.x");
	IMesh* kalashinkovMesh = myEngine->LoadMesh("kalashinkov.x");
	IMesh* TommyGunMesh = myEngine->LoadMesh("TommyGun.x");
	IMesh* UziMesh = myEngine->LoadMesh("Mini_Uzi.x");
	IMesh* machineGunMesh = myEngine->LoadMesh("MachineGun.x");
	IMesh* bulletMesh = myEngine->LoadMesh("MachineGun.x");

	IModel* WeaponArray[numGuns];
	WeaponArray[0] = M4Mesh->CreateModel(-3, 8, 43);
	WeaponArray[1] = stenMK2Mesh->CreateModel(5, 8, 43);
	WeaponArray[2] = kalashinkovMesh->CreateModel(32, 8, 43);
	WeaponArray[3] = TommyGunMesh->CreateModel(38, 8, 43);
	WeaponArray[4] = UziMesh->CreateModel(66, 8, 43);
	WeaponArray[5] = machineGunMesh->CreateModel(75, 8, 43);

	for (int i = 0; i < numGuns; i++)
	{
		WeaponArray[i]->Scale(13);
		WeaponArray[i]->RotateLocalZ(90);
		WeaponArray[i]->RotateLocalX(180);
	}
	//spawnBullets(200, bulletMesh, vBullets);

	IModel* fence[80];
	IModel* cameraDummy = dummyMesh->CreateModel(0, 15, 90);
	IModel* interactionDummy = dummyMesh->CreateModel(0, 0, 0);
	

	interactionDummy->Scale(7);
	interactionDummy->AttachToParent(myCam);

	myCam->AttachToParent(cameraDummy);
	myCam->SetMovementSpeed(0.0f);
	cameraDummy->RotateY(180);

	float mouseMoveX = 0.0f;
	float mouseMoveY = 0.0f;
	float camYCounter = 0.0f;

	float interactionZspeed = 0.0f;
	float currentInteractionDistance = 0.0f;
	bool canCollide = false;

	float oldPlayerX = 0;
	float oldPlayerZ = 0;

	int whichGunEquipped = numGuns;
	/**** Set up your scene here ****/
	CreateFences(myEngine, fence); CreateScene(myEngine); CreateWalls(myEngine);
	myEngine->Timer();
	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		float frameTime = myEngine->Timer();
		// Draw the scene
		myEngine->DrawScene();
		oldPlayerX = cameraDummy->GetX();
		oldPlayerZ = cameraDummy->GetZ();

		/**** Update your scene each frame here ****/
		mouseMoveX = myEngine->GetMouseMovementX();
		mouseMoveY = myEngine->GetMouseMovementY();

		if (camYCounter < upperCamYMax && mouseMoveY < 0) { mouseMoveY = 0; }
		if (camYCounter > lowerCamYMax && mouseMoveY > 0) { mouseMoveY = 0; }

		camYCounter += mouseMoveY * 0.1f;
		//cout << camYCounter;
		movement(myEngine, cameraDummy, mouseMoveX, mouseMoveY, camYCounter);

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
			if ( canCollide == true && gunInteraction(interactionDummy, WeaponArray[i]) && whichGunEquipped == numGuns)
			{
				whichGunEquipped = i;
				WeaponArray[i]->ResetOrientation();
				WeaponArray[i]->AttachToParent(cameraDummy);
				WeaponArray[i]->SetLocalPosition(2.0f, -2.0f, 7.0f);
				WeaponArray[i]->RotateY(-0.2f);
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
			WeaponArray[whichGunEquipped]->DetachFromParent();
			WeaponArray[whichGunEquipped]->SetPosition(oldPlayerX, 0.2, oldPlayerZ);
			WeaponArray[whichGunEquipped]->RotateLocalZ(90.0f);
			whichGunEquipped = numGuns;
		}
		if(myEngine->KeyHeld(Key_Space))
		{
		}

		//END
	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}

void movement(I3DEngine* myEngine, IModel* camDummy, float& currentCamX, float &mouseMoveY, float& camYCounter)
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
	camDummy->SetY(15);

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
}

void desktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;						      //Gets a handle to the current window
	const HWND hDesktop = GetDesktopWindow(); //Gets the size and places it to a variable
	GetWindowRect(hDesktop, &desktop);        //Gets the coordinates for the corner of the screen

	horizontal = desktop.right;               //Holds the values for the screen resolution.
	vertical = desktop.bottom;				  //Holds the values for the screen resolution.
}