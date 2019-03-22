#pragma once
#include <TL-Engine.h>
using namespace tle;
#include "Bullets.h"
#include "Targets.h"


bool FenceCollision(IModel* cameraDummy);

bool gunInteraction(IModel* gunInteractionDummy, IModel* Gun);
void bulletToTarget(vector<sTarget*> &vTargets, vector<sBullet*> &vBullets);