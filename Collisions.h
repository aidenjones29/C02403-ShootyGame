#pragma once
#include <TL-Engine.h>
using namespace tle;
#include "Bullets.h"
#include "Targets.h"

bool FenceCollision(IModel* cameraDummy);

bool gunInteraction(IModel* gunInteractionDummy, IModel* Gun);

<<<<<<< HEAD
<<<<<<< HEAD
void bulletToTarget(vector<sTarget*> &vTargets, vector<sBullet*> &vBullets);

sideHit targetBoxCollision(std::vector<sTarget*>& vTargets, IModel* camDummy, float oldPos[]);

sideHit ammoBoxCollision(IModel* boxes[], IModel* camDummy, float oldPos[]);

<<<<<<< HEAD
sideHit WallCollision(const float Walls[maxWALLLLLLLZZZ][5], IModel* camDummy, float oldPos[]);

sideHit allFenceCollisions(IModel* camDummy, float oldPos[]);
=======
void bulletToTarget(vector<sTarget*> &vTargets, vector<sBullet*> &vBullets);
>>>>>>> parent of 28f65e9... fdg
=======
void bulletToTarget(vector<sTarget*> &vTargets, vector<sBullet*> &vBullets);
>>>>>>> parent of 28f65e9... fdg
=======
sideHit WallCollision(IModel* Walls[], IModel* camDummy, float oldPos[]);
>>>>>>> parent of 37e4753... wallCollisions
