// C02403 project.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
#include "ModelCreation.h"

using namespace tle;

const float movementSpeed = 0.04f;

class Weapon
{

};

void movement(I3DEngine* myEngine, IModel* camDummy);

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine(kTLX);
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder( ".\\Media" );
	ICamera* myCam = myEngine->CreateCamera(kManual, 0, 15, 90);

	IMesh* dummyMesh = myEngine->LoadMesh("Dummy.x");
	IModel* cameraDummy = dummyMesh->CreateModel(0, 0, 90);

	myCam->AttachToParent(cameraDummy);


	myCam->SetMovementSpeed(50.0f);

	/**** Set up your scene here ****/
	CreateFences(myEngine); CreateScene(myEngine); CreateWalls(myEngine);

	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		/**** Update your scene each frame here ****/
		movement(myEngine, cameraDummy);
		//END
	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}

void movement(I3DEngine* myEngine, IModel* camDummy)
{
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