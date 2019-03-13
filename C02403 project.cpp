// C02403 project.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
#include "ModelCreation.h"
#include "Collisions.h"
#include "wtypes.h" 
#include <iostream>

enum fireModes {Single, Burst, Auto};

using namespace tle;

const float movementSpeed = 0.04f;
const float upperCamYMax = -50.0f;
const float lowerCamYMax = 50.0f;
const int numGuns = 6;

struct Weapon
{
	IMesh* weaponMesh;
	IModel* weaponModel;
	float fireRate;
	fireModes fireMode;
	int magCapacity;
	int magAmount;
};

void movement(I3DEngine* myEngine, IModel* camDummy, float& currentCamRotation, float& currentCamY, float& camYCounter, bool& crouched);

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

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder( ".\\Media" );
	ICamera* myCam = myEngine->CreateCamera(kManual, 0, 0, 0);
	
	Weapon* WeaponArray[numGuns];

	IMesh* dummyMesh = myEngine->LoadMesh("Dummy.x");

	WeaponArray[0]->weaponMesh = myEngine->LoadMesh("M4Colt.x");
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

	bool crouched = false;

	int whichGunEquipped = numGuns;
	/**** Set up your scene here ****/
	CreateFences(myEngine, fence); CreateScene(myEngine); CreateWalls(myEngine);

	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
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
		movement(myEngine, cameraDummy, mouseMoveX, mouseMoveY, camYCounter, crouched);

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
			if ( canCollide == true && gunInteraction(interactionDummy, WeaponArray[i]->weaponModel) && whichGunEquipped == numGuns)
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

		interactionDummy->MoveLocalZ(interactionZspeed);
		currentInteractionDistance += interactionZspeed;

		//END
	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}

void movement(I3DEngine* myEngine, IModel* camDummy, float& currentCamX, float &mouseMoveY, float& camYCounter, bool& crouched)
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
	if (crouched)
	{
		camDummy->SetY(5);
	}
	else
	{
		camDummy->SetY(15);
	}

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
		crouched != crouched;
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

