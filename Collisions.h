#pragma once
#include <TL-Engine.h>
using namespace tle;
#include "Bullets.h"
#include "Targets.h"
#include "ModelCreation.h"

enum sideHit { NoSide, LeftRight, FrontBack };

bool FenceCollision(IModel* cameraDummy);

bool gunInteraction(IModel* gunInteractionDummy, IModel* Gun);

void bulletToTarget(vector<sTarget*> &vTargets, vector<sBullet*> &vBullets);

sideHit targetBoxCollision(std::vector<sTarget*>& vTargets, IModel* camDummy, float oldPos[]);

sideHit ammoBoxCollision(IModel* boxes[], IModel* camDummy, float oldPos[]);

sideHit WallCollision(IModel* Walls[], IModel* camDummy, float oldPos[]);