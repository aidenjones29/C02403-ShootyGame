// C02403 project.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
#include "ModelCreation.h"
#include "Collisions.h"
#include "wtypes.h" 
#include <iostream>

using namespace tle;

const float movementSpeed = 0.04f;
const float upperCamYMax = -50.0f;
const float lowerCamYMax = 50.0f;

void movement(I3DEngine* myEngine, IModel* camDummy, float& currentCamRotation, float& currentCamY, float& camYCounter);

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

	IMesh* dummyMesh = myEngine->LoadMesh("Dummy.x");
	IMesh* M4Mesh = myEngine->LoadMesh("M4Colt.x");

	IModel* M4 = M4Mesh->CreateModel(0, 10, 80);
	M4->Scale(13);
	IModel* fence[80];
	IModel* cameraDummy = dummyMesh->CreateModel(0, 15, 90);
	IModel* interactionDummy = dummyMesh->CreateModel(0, 0, 0);

	interactionDummy->Scale(7);

	interactionDummy->AttachToParent(myCam);
	myCam->AttachToParent(cameraDummy);
	myCam->SetMovementSpeed(0.0f);

	float mouseMoveX = 0.0f;
	float mouseMoveY = 0.0f;
	float camYCounter = 0.0f;

	float interactionZspeed = 0.0f;
	float currentInteractionDistance = 0.0f;
	bool canCollide = false;

	float oldPlayerX = 0;
	float oldPlayerZ = 0;
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
		if ( canCollide == true && gunInteraction(interactionDummy, M4))
		{
			M4->AttachToParent(cameraDummy);
			M4->SetLocalPosition(2.0f, -3.0f, 7.0f);
		}

		if (currentInteractionDistance >= 2.0f)
		{
			canCollide = false;
			interactionZspeed = 0.0f;
			currentInteractionDistance = 0.0f;
			interactionDummy->SetLocalPosition(0, 0, 0);
		}

		if (myEngine->KeyHit(Key_R))
		{
			M4->DetachFromParent();
			M4->SetPosition(oldPlayerX, 5, oldPlayerZ);
		}

		interactionDummy->MoveLocalZ(interactionZspeed);
		currentInteractionDistance += interactionZspeed;

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