#pragma once
#include <TL-Engine.h>

using namespace tle;

const int FenceAmmount = 15;
const int OuterWallAmount = 10;
const int numOfgates = 3;
const int numOfhallwayFences1 = 4;
const int numOfCourseWalls1 = 8;
const int numOfCourseWalls2 = 12;
const int numOfCourseWalls1Inner = 2;
const int numOfCourseWalls2Inner = 11;
const int maxWALLLLLLLZZZ = 60;

void CreateScene(I3DEngine* myEngine);

void CreateFences(I3DEngine* myEngine, IModel* fence[]);

void CreateWalls(I3DEngine* myEngine);

const float Walls [maxWALLLLLLLZZZ][5]=
{
//Room 1 Walls
	{1, 14,-10,27,90},		//1 for outer wall, 2 for inner wall.
	{},
	{},
//Room 1 End
//Room 1 Inner Walls
	{2,},
	{},
	{},
	{},
	{},
	{},
	{},
	{}
//Room 1 inner walls end

};