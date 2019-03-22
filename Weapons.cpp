#pragma once 
#include "Weapons.h"

void spawnGuns(deque <unique_ptr<sWeapon>> &vGuns)
{
	unique_ptr <sWeapon> gun (new M4(-3, 8, 43));
	vGuns.push_back(move(gun));
	gun.reset(new AR_18(5, 8, 43));
	vGuns.push_back(move(gun));
	gun.reset(new AK(32, 8, 43));
	vGuns.push_back(move(gun));
	gun.reset( new TOMMY_GUN(38, 8, 43));
	vGuns.push_back(move(gun));
	gun.reset (new MINI_UZI(66, 8, 43));
	vGuns.push_back(move(gun));
	gun.reset(new MP5(75, 8, 43));
	vGuns.push_back(move(gun));
	gun.reset(new Glock(75, 8, 43));
	vGuns.push_back(move(gun));
}