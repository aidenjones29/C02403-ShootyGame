#pragma once
#include <TL-Engine.h>
#include <vector>
#include <deque>

const int FenceAmmount = 15;
const int OuterWallAmount = 10;
const int numOfgates = 3;
const int numOfhallwayFences1 = 2;

using namespace tle;

struct fenceStruct
{
	IModel* fenceModel;
	int fenceRotation;
};

deque<fenceStruct> allFences;


void CreateScene(I3DEngine* myEngine);

void CreateFences(I3DEngine* myEngine, IModel* fence[]);

void CreateWalls(I3DEngine* myEngine);