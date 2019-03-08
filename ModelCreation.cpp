#include "ModelCreation.h"

const int FenceAmmount = 15;

void CreateWalls(I3DEngine* myEngine)
{
	IMesh* skyboxMesh = myEngine->LoadMesh("Skybox.x");
	IMesh* floorMesh = myEngine->LoadMesh("Floor.x");
	IMesh* FenceMesh = myEngine->LoadMesh("ChainLinkFence.x");
	
	//IMesh* cubeM = myEngine->LoadMesh("Gate.x");
	//IModel* cube = cubeM->CreateModel(0, 5, 0);
	//cube->ScaleZ(0.01f);

	IModel* skybox = skyboxMesh->CreateModel(0.0f, -800.0f, 0.0f);
	IModel* floor = floorMesh->CreateModel();
	IModel* fenceTop[FenceAmmount];
	IModel* fenceBottom[FenceAmmount];
	IModel* fenceLeft[FenceAmmount];
	IModel* fenceRight[FenceAmmount];
	IModel* fenceInnerTop[5];
	IModel* fenceInnerRight[5];
	IModel* gateSides[2];


	float fenceXStart[4] = {-5.0f, -5.0f, -15.0f, 360.0f};
	float fenceZStart[4] = { 370.0f, -7.0f, 7.0f, 7.0f };

	int currentFencePos = 0;

	for (int i = 0; i < FenceAmmount; i++)
	{
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
