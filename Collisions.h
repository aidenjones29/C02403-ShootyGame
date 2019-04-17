#pragma once
#include <TL-Engine.h>
#include "Bullets.h"
#include "Targets.h"

using namespace tle;

enum sideHit { NoSide, LeftRight, FrontBack };

bool gunInteraction(IModel* gunInteractionDummy, IModel* Gun);

void bulletToTarget(vector<sTarget*> &vTargets, vector<sBullet*> &vBullets);

sideHit targetBoxCollision(std::vector<sTarget*>& vTargets, IModel* camDummy, float oldPos[]);

sideHit WallCollision(const float Walls[maxWALLLLLLLZZZ][5], IModel* camDummy, float oldPos[]);

sideHit allFenceCollisions(IModel* camDummy, float oldPos[]);

void bulletToTarget(vector<sTarget*> &vTargets, vector<sBullet*> &vBullets);

void bulletToTarget(vector<sTarget*> &vTargets, vector<sBullet*> &vBullets);

sideHit allFenceCollisions(IModel* camDummy, float oldPos[]);

sideHit gateCollisions(IModel* gate, IModel* camDummy, float oldPos[], bool horizontal);