#include "ModelCreation.h"

const int FenceAmmount = 15;
const int OuterWallAmount = 10;

void CreateScene(I3DEngine * myEngine)
{
	IMesh* skyboxMesh = myEngine->LoadMesh("Skybox.x");
	IMesh* floorMesh = myEngine->LoadMesh("Floor.x");
	IMesh* ammoCrateMesh = myEngine->LoadMesh("AmmoCrateAm.x");
	IMesh* BarrierMesh = myEngine->LoadMesh("CementBarrier.x");
	IMesh* crateMesh = myEngine->LoadMesh("LargeCrate.x");
	IMesh* armyTruckMesh = myEngine->LoadMesh("army_truck.x");
	IMesh* transportTruckMesh = myEngine->LoadMesh("transportTruck.x");
	IMesh* apacheMesh = myEngine->LoadMesh("apache.x");
	IMesh* hueyMesh = myEngine->LoadMesh("huey.x");
	IMesh* nickMesh = myEngine->LoadMesh("nick.x");

	IModel* huey = hueyMesh->CreateModel(200, 14, 650);
	huey->RotateY(-180);
	huey->RotateLocalX(-2);
	huey->Scale(10);

	IModel* hueyTwo = hueyMesh->CreateModel(300, 14, 650);
	hueyTwo->RotateY(-180);
	hueyTwo->RotateLocalX(-2);
	hueyTwo->Scale(10);

	IModel* apache = apacheMesh->CreateModel(0, 14, 650);
	apache->RotateY(-180);
	apache->RotateLocalX(-2);
	apache->Scale(10);

	IModel* apacheTwo = apacheMesh->CreateModel(100, 14, 650);
	apacheTwo->RotateY(-180);
	apacheTwo->RotateLocalX(-2);
	apacheTwo->Scale(10);

	IModel* tTruckOne = transportTruckMesh->CreateModel(170, 0, -50);
	tTruckOne->Scale(10);
	tTruckOne->RotateY(90);

	IModel* armyTruck = armyTruckMesh->CreateModel(-10, 0, -60);
	armyTruck->Scale(10);
	armyTruck->RotateY(90);

	IModel* armyTruckTwo = armyTruckMesh->CreateModel(80, 0, -45);
	armyTruckTwo->Scale(10);
	armyTruckTwo->RotateY(90);

	IModel* floor = floorMesh->CreateModel();
	IModel* skybox = skyboxMesh->CreateModel(0.0f, -800.0f, 0.0f);
	IModel* ammoCrate[3];
	IModel* barrier[3];
	IModel* crate[3];
	IModel* nickBox[5];

	IModel* nick = nickMesh->CreateModel(-36, 18, 70);
	nick->Scale(0.9);
	nick->ScaleX(0.1f);

	nickBox[0] = BarrierMesh->CreateModel(-30, 15, 70);
	nickBox[0]->RotateLocalX(180);
	nickBox[0]->Scale(3);
	nickBox[0]->ScaleZ(0.5);
	nickBox[0]->ScaleX(0.2);

	nickBox[1] = BarrierMesh->CreateModel(-30, 20, 70);
	nickBox[1]->ScaleX(0.2);
	nickBox[1]->RotateLocalZ(45);
	nickBox[1]->ScaleZ(0.5);
	nickBox[1]->Scale(3);

	nickBox[2] = BarrierMesh->CreateModel(-35, 10, 62);
	nickBox[2]->RotateLocalX(90);
	nickBox[2]->RotateLocalZ(180);
	nickBox[2]->Scale(3);

	nickBox[3] = BarrierMesh->CreateModel(-35, 10, 78);
	nickBox[3]->RotateLocalX(270);
	nickBox[3]->RotateLocalZ(180);
	nickBox[3]->Scale(3);

	nickBox[4] = BarrierMesh->CreateModel(-38, 25, 70);
	nickBox[4]->RotateLocalZ(180);
	nickBox[4]->ScaleY(8);
	nickBox[4]->ScaleZ(2);

	int currentAmmoX = 0;
	int currentBarrierX = 0;
	int currentSpawnCrate = 0;

	for (int i = 0; i < 3; i++)
	{
		ammoCrate[i] = ammoCrateMesh->CreateModel(0.0f + currentAmmoX, 0.0f, 43.0f);
		ammoCrate[i]->Scale(1.5);
		ammoCrate[i]->ScaleX(1.6);
		currentAmmoX += 35;

		barrier[i] = BarrierMesh->CreateModel(18 + currentBarrierX, 0, 35);
		barrier[i]->ScaleX(1.2);
		barrier[i]->ScaleY(2);
		barrier[i]->ScaleZ(2);
		currentBarrierX += 35;

		crate[i] = crateMesh->CreateModel(0 + currentSpawnCrate, 0, 0);
		crate[i]->Scale(1.5);
		crate[i]->ScaleX(2);
		currentSpawnCrate += 35;
	}
}


void CreateFences(I3DEngine* myEngine, IModel* fence[])
{
	IMesh* FenceMesh = myEngine->LoadMesh("ChainLinkFence.x");
	IMesh* gateMesh = myEngine->LoadMesh("Gate.x");

	IModel* fenceTop[FenceAmmount];
	IModel* fenceBottom[FenceAmmount];
	IModel* fenceLeft[FenceAmmount];
	IModel* fenceRight[FenceAmmount];
	IModel* fenceInnerTop[5];
	IModel* fenceInnerRight[5];
	IModel* gateSides[2];
	IModel* fenceWalkway = FenceMesh->CreateModel(108, 0, 107);
	fenceWalkway->RotateY(-90);
	fenceWalkway->Scale(10);

	IModel* gate = gateMesh->CreateModel(121.3, 9, 94);
	gate->ScaleZ(0.05f);
	gate->ScaleX(1.15f);
	gate->ScaleY(1.7f);

	float fenceXStart[4] = {-5.0f, -5.0f, -15.0f, 360.0f};
	float fenceZStart[4] = { 370.0f, -7.0f, 7.0f, 7.0f };

	int currentFencePos = 0;

	gateSides[0] = FenceMesh->CreateModel(112, 0, 95);
	gateSides[1] = FenceMesh->CreateModel(130, 0, 95);

	const int numOfgates = 3;
	const int numOfhallwayFences1 = 2;

	IModel* courseGates[numOfgates];
	IModel* courseGateSideLeft[numOfgates];
	IModel* courseGateSideRight[numOfgates];

	IModel* hallwayFence1[numOfhallwayFences1];

	courseGates[0] = gateMesh->CreateModel(121.3, 9, 120);
	courseGates[1] = gateMesh->CreateModel(133.5f, 9, 332);
	courseGates[2] = gateMesh->CreateModel(180.5, 9, 332);

	courseGateSideLeft[0] = FenceMesh->CreateModel(112, 0, 121);
	courseGateSideLeft[1] = FenceMesh->CreateModel(134.7f, 0, 341.5f);
	courseGateSideLeft[2] = FenceMesh->CreateModel(179.5, 0, 341);

	courseGateSideRight[0] = FenceMesh->CreateModel(130, 0, 121);
	courseGateSideRight[1] = FenceMesh->CreateModel(134.7f, 0, 323.2f);
	courseGateSideRight[2] = FenceMesh->CreateModel(179.5, 0, 323);

	hallwayFence1[0] = FenceMesh->CreateModel(157, 0, 347);
	hallwayFence1[1] = FenceMesh->CreateModel(159, 0, 317);

	courseGates[1]->RotateY(90);
	courseGateSideLeft[1]->RotateY(90);
	courseGateSideRight[1]->RotateY(90);

	courseGates[2]->RotateY(90);
	courseGateSideLeft[2]->RotateY(-90);
	courseGateSideRight[2]->RotateY(-90);

	hallwayFence1[1]->RotateY(180);

	for (int i = 0; i < numOfgates; i++)
	{
		courseGates[i]->ScaleZ(0.05f);
		courseGates[i]->ScaleX(1.15f);
		courseGates[i]->ScaleY(1.7f);

		courseGateSideLeft[i]->Scale(10);
		courseGateSideLeft[i]->ScaleX(0.25f);

		courseGateSideRight[i]->Scale(10);
		courseGateSideRight[i]->ScaleX(0.25f);
	}

	for (int i = 0; i < numOfhallwayFences1; i++)
	{
		hallwayFence1[i]->Scale(10);
	}

	for (int i = 0; i < FenceAmmount; i++)
	{
		if (i < 2)
		{
			gateSides[i]->Scale(10);
			gateSides[i]->ScaleX(0.25f);
		}

		if (i < 5)
		{
			fenceInnerTop[i] = FenceMesh->CreateModel(fenceXStart[0] + currentFencePos, 0.0f, 95);
			fenceInnerTop[i]->Scale(10);

			fenceInnerRight[i] = FenceMesh->CreateModel(135.0f, 0.0f, 7.0f + currentFencePos);
			fenceInnerRight[i]->Scale(10);
			fenceInnerRight[i]->RotateY(90);
		}

		fenceTop[i] = FenceMesh->CreateModel(fenceXStart[0] + currentFencePos, 0.0f, fenceZStart[0]);
		fenceBottom[i] = FenceMesh->CreateModel(fenceXStart[1] + currentFencePos, 0.0f, fenceZStart[1]);
		fenceLeft[i] = FenceMesh->CreateModel(fenceXStart[2], 0.0f, fenceZStart[2] + currentFencePos);
		fenceRight[i] = FenceMesh->CreateModel(fenceXStart[3], 0.0f, fenceZStart[3] + currentFencePos);

		fenceLeft[i]->Scale(10);
		fenceRight[i]->Scale(10);
		fenceTop[i]->Scale(10);
		fenceBottom[i]->Scale(10);

		fenceLeft[i]->RotateY(90);
		fenceRight[i]->RotateY(90);

		currentFencePos += 25;
	}
}


void CreateWalls(I3DEngine * myEngine)
{
	const int numOfCourseWalls1 = 8;
	const int numOfCourseWalls2 = 12;

	const int numOfCourseWalls1Inner = 2;
	const int numOfCourseWalls2Inner = 11;

	IMesh* FenceMesh = myEngine->LoadMesh("ChainLinkFence.x");
	IMesh* OuterWallMesh = myEngine->LoadMesh("OuterWall.x");
	IMesh* CourseWallMesh = myEngine->LoadMesh("OuterWall2.x");
	IMesh* CourseWallInnerMesh = myEngine->LoadMesh("OuterWall2.x");

	IModel* OuterWallTop[OuterWallAmount];
	IModel* OuterWallBottom[OuterWallAmount];
	IModel* OuterWallLeft[OuterWallAmount];
	IModel* OuterWallRight[OuterWallAmount];

	IModel* CourseWallsRoom1[numOfCourseWalls1];
	IModel* CourseWallsRoom2[numOfCourseWalls2];

	IModel* CourseWallsRoom1Inner[numOfCourseWalls1Inner];
	IModel* CourseWallsRoom2Inner[numOfCourseWalls2Inner];

	float OuterWallXStart[4] = {-100, -100, -100, 700};
	float OuterWallZStart[4] = {-100, 800, -100, -100};
	float outerWallY = 10.0f;

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	CourseWallsRoom1[0] = CourseWallMesh->CreateModel(58.5f, -10, 124.5f);
	CourseWallsRoom1[1] = CourseWallMesh->CreateModel(138.7f, -10, 169.5f);
	CourseWallsRoom1[2] = CourseWallMesh->CreateModel(3.5f, -10, 169.5f);
	CourseWallsRoom1[3] = CourseWallMesh->CreateModel(138.7f, -10, 269.5f);
	CourseWallsRoom1[4] = CourseWallMesh->CreateModel(94, -10, 350);
	CourseWallsRoom1[5] = CourseWallMesh->CreateModel(19, -10, 350);
	CourseWallsRoom1[6] = CourseWallMesh->CreateModel(3.5f, -10, 269.5f);
	CourseWallsRoom1[7] = CourseWallMesh->CreateModel(3.5f, -10, 369.5f);

	CourseWallsRoom1[1]->RotateY(90);
	CourseWallsRoom1[2]->RotateY(90);
	CourseWallsRoom1[3]->RotateY(90);
	CourseWallsRoom1[6]->RotateY(90);
	CourseWallsRoom1[7]->RotateY(90);

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	CourseWallsRoom2[0] = CourseWallMesh->CreateModel(222, -10, 350);
	CourseWallsRoom2[1] = CourseWallMesh->CreateModel(176, -10, 270);
	CourseWallsRoom2[2] = CourseWallMesh->CreateModel(322, -10, 350);
	CourseWallsRoom2[3] = CourseWallMesh->CreateModel(176, -10, 170);
	CourseWallsRoom2[4] = CourseWallMesh->CreateModel(176, -10, 95);
	CourseWallsRoom2[5] = CourseWallMesh->CreateModel(176, -10, 15);
	CourseWallsRoom2[6] = CourseWallMesh->CreateModel(222, -10, 0);
	CourseWallsRoom2[7] = CourseWallMesh->CreateModel(322, -10, 0);
	CourseWallsRoom2[8] = CourseWallMesh->CreateModel(350, -10, 295);
	CourseWallsRoom2[9] = CourseWallMesh->CreateModel(350, -10, 195);
	CourseWallsRoom2[10] = CourseWallMesh->CreateModel(350, -10, 95);
	CourseWallsRoom2[11] = CourseWallMesh->CreateModel(350, -10, 20);

	CourseWallsRoom2[1]->RotateY(90);
	CourseWallsRoom2[3]->RotateY(90);
	CourseWallsRoom2[4]->RotateY(90);
	CourseWallsRoom2[5]->RotateY(90);
	CourseWallsRoom2[8]->RotateY(90);
	CourseWallsRoom2[9]->RotateY(90);
	CourseWallsRoom2[10]->RotateY(90);
	CourseWallsRoom2[11]->RotateY(90);

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	CourseWallsRoom1Inner[0] = CourseWallInnerMesh->CreateModel(60, -20, 178);
	CourseWallsRoom1Inner[1] = CourseWallInnerMesh->CreateModel(70, -20, 230);

	CourseWallsRoom1Inner[0]->RotateY(90);

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	CourseWallsRoom2Inner[0] = CourseWallInnerMesh->CreateModel(230, -20, 278);
	CourseWallsRoom2Inner[1] = CourseWallInnerMesh->CreateModel(290, -20, 278);
	CourseWallsRoom2Inner[2] = CourseWallInnerMesh->CreateModel(302.5, -20, 230.5);
	CourseWallsRoom2Inner[3] = CourseWallInnerMesh->CreateModel(302.5, -20, 100.5);
	CourseWallsRoom2Inner[4] = CourseWallInnerMesh->CreateModel(230, -20, 120);
	CourseWallsRoom2Inner[5] = CourseWallInnerMesh->CreateModel(290, -20, 120);
	CourseWallsRoom2Inner[6] = CourseWallInnerMesh->CreateModel(250, -20, 170);
	CourseWallsRoom2Inner[7] = CourseWallInnerMesh->CreateModel(200, -20, 170);
	CourseWallsRoom2Inner[8] = CourseWallInnerMesh->CreateModel(240, -20, 100);
	CourseWallsRoom2Inner[9] = CourseWallInnerMesh->CreateModel(230, -20, 82);
	CourseWallsRoom2Inner[10] = CourseWallInnerMesh->CreateModel(190, -20, 82);

	CourseWallsRoom2Inner[2]->RotateY(90);
	CourseWallsRoom2Inner[3]->RotateY(90);
	CourseWallsRoom2Inner[6]->RotateY(90);
	CourseWallsRoom2Inner[8]->RotateY(90);

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < numOfCourseWalls1; i++)
	{
		CourseWallsRoom1[i]->Scale(10);
		CourseWallsRoom1[i]->ScaleZ(0.1f);
	}

	CourseWallsRoom1[5]->ScaleX(0.5f);

	for (int i = 0; i < numOfCourseWalls2; i++)
	{
		CourseWallsRoom2[i]->Scale(10);
		CourseWallsRoom2[i]->ScaleZ(0.1f);
	}

	for (int i = 0; i < numOfCourseWalls1Inner; i++)
	{
		CourseWallsRoom1Inner[i]->Scale(10);
		CourseWallsRoom1Inner[i]->ScaleZ(0.05f);
	}

	for (int i = 0; i < numOfCourseWalls2Inner; i++)
	{
		CourseWallsRoom2Inner[i]->Scale(10);
		CourseWallsRoom2Inner[i]->ScaleZ(0.05f);
	}

	CourseWallsRoom2[4]->ScaleX(0.5f);
	CourseWallsRoom2[5]->ScaleX(0.5f);
	CourseWallsRoom2[11]->ScaleX(0.5f);
	CourseWallsRoom1Inner[1]->ScaleX(0.6f);
	CourseWallsRoom2Inner[1]->ScaleX(0.2f);
	CourseWallsRoom2Inner[5]->ScaleX(0.2f);
	CourseWallsRoom2Inner[7]->ScaleX(0.4f);
	CourseWallsRoom2Inner[8]->ScaleX(0.4f);
	CourseWallsRoom2Inner[9]->ScaleX(0.2f);
	CourseWallsRoom2Inner[10]->ScaleX(0.2f);

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	int currentOuterWall = 0;

	for (int i = 0; i < OuterWallAmount; i++)
	{
		OuterWallTop[i] = OuterWallMesh->CreateModel(OuterWallXStart[0] + currentOuterWall, outerWallY, OuterWallZStart[0]);
		OuterWallBottom[i] = OuterWallMesh->CreateModel(OuterWallXStart[1] + currentOuterWall, outerWallY, OuterWallZStart[1]);
		OuterWallLeft[i] = OuterWallMesh->CreateModel(OuterWallXStart[2], outerWallY, OuterWallZStart[2] + currentOuterWall);
		OuterWallRight[i] = OuterWallMesh->CreateModel(OuterWallXStart[3], outerWallY, OuterWallZStart[3] + currentOuterWall);

		OuterWallTop[i]->Scale(10);
		OuterWallTop[i]->ScaleZ(0.1f);
		OuterWallBottom[i]->Scale(10);
		OuterWallBottom[i]->ScaleZ(0.1f);
		OuterWallLeft[i]->Scale(10);
		OuterWallLeft[i]->ScaleZ(0.1f);
		OuterWallLeft[i]->RotateY(90);
		OuterWallRight[i]->Scale(10);
		OuterWallRight[i]->RotateY(90);
		OuterWallRight[i]->ScaleZ(0.1f);

		currentOuterWall += 100;
	}

	OuterWallTop[5]->SetY(60);
	OuterWallTop[5]->ScaleY(0.2f);
}
