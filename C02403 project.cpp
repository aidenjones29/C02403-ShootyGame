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
	myEngine->StartWindowed(horizontal, vertical);
	myEngine->StartMouseCapture();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder( ".\\Media" );
	ICamera* myCam = myEngine->CreateCamera(kManual, 0, 5, 0);

	IMesh* dummyMesh = myEngine->LoadMesh("Dummy.x");

	IModel* fence[80];
	IModel* cameraDummy = dummyMesh->CreateModel(0, 10, 90);
	IModel* testDummy = dummyMesh->CreateModel();

	testDummy->AttachToParent(myCam);
	myCam->AttachToParent(cameraDummy);
	myCam->SetMovementSpeed(0.0f);

	float mouseMoveX = 0.0f;
	float mouseMoveY = 0.0f;
	float camYCounter = 0.0f;
	/**** Set up your scene here ****/
	CreateFences(myEngine, fence); CreateScene(myEngine); CreateWalls(myEngine);

	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		/**** Update your scene each frame here ****/
		mouseMoveX = myEngine->GetMouseMovementX();
		mouseMoveY = myEngine->GetMouseMovementY();

		if (camYCounter < upperCamYMax && mouseMoveY < 0) { mouseMoveY = 0; }
		if (camYCounter > lowerCamYMax && mouseMoveY > 0) { mouseMoveY = 0; }

		camYCounter += mouseMoveY * 0.1f;
		//cout << camYCounter;
		movement(myEngine, cameraDummy, mouseMoveX, mouseMoveY, camYCounter);

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

	camDummy->SetY(10);

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