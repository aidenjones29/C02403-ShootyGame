#pragma once
#include <TL-Engine.h>

using namespace tle;

<<<<<<< HEAD
void CreateScene(I3DEngine* myEngine);
=======
const int FenceAmmount = 15;
const int OuterWallAmount = 10;
const int numOfgates = 3;
const int numOfhallwayFences1 = 4;
const int maxWALLLLLLLZZZ = 42;
const int numAmmoBoxes = 3;

void CreateScene(I3DEngine* myEngine, IModel* ammoCrate[]);
0d30e956e7c3374e918d01787099c4f3acee6922

void CreateFences(I3DEngine* myEngine);

<<<<<<< HEAD
void CreateWalls(I3DEngine* myEngine);
=======
void CreateWalls(I3DEngine* myEngine);

const float Walls[maxWALLLLLLLZZZ][5] =
{
	//Room 1 Walls
	{1, 58.5f,-10,124.5f,0},		//1 for outer wall, 2 for inner wall.
	{1, 138.7f, -10, 169.5f, 90},
	{1, 3.5f, -10, 169.5f, 90},
	{1, 138.7f, -10, 269.5f, 90},
	{1, 94, -10, 350, 0},
	{1, -6, -10, 350, 0},
	{1, 3.5f, -10, 269.5f, 90},
	{1, 3.5f, -10, 369.5f, 90},
	//Room 1 End

	//Room 1 Inner Walls
	{2,60, -20, 148,90},
	{2,60, -20, 188,90},
	{2,60, -20, 228,90},
	{2,60, -20, 248,0},
	//Room 1 inner walls end

	//Room 2 walls
	{1,222, -10, 350,0},
	{1,176, -10, 270,90},
	{1,322, -10, 350,0},
	{1,176, -10, 170,90},
	{1,176, -10, 95,90},	//scale 0.5f on x.
	{1,176, -10, 18,90},	//scale 0.5f on x.
	{1,222, -10, 0,0},
	{1,322, -10, 0,0},
	{1,350, -10, 295,90},
	{1,350, -10, 195,90},
	{1,350, -10, 95,90},
	{1,350, -10, 20,90},	//scale 0.5f on x.
	//Room 2 End

	//Room 2 Inner Walls
	{2,200, -20, 278,0},
	{2,240, -20, 278,0},
	{2,280, -20, 278,0},
	{2,299, -20, 257,90},
	{2,299, -20, 217,90},
	{2,299, -20, 177,90},
	{2,299, -20, 110,90},
	{2,279, -20, 110,0},
	{2,239, -20, 110,0},
	{2,199, -20, 110,0},
	{2,299, -20, 70,90},
	{2,299, -20, 10,90},
	{2,239, -20, 90,90},
	{2,201, -20, 71,0},
	{2,239, -20, 131,90},
	{2,239, -20, 171,90},
	{2,239, -20, 211,90},
	{2,199, -20, 171,0}
	//Room 2 inner walls end
};
>>>>>>> 0d30e956e7c3374e918d01787099c4f3acee6922
