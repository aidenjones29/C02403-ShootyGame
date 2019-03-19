#pragma once 
#include "Weapons.h"

void spawnGuns(vector <sWeapon*> &vGuns)
{
	sWeapon* gun;
	gun = new M4(-3, 8, 43);
	vGuns.push_back(gun);
	gun = new AR_18(5, 8, 43);;
	vGuns.push_back(gun);
	gun = new AK(32, 8, 43);
	vGuns.push_back(gun);
	gun = new TOMMY_GUN(38, 8, 43);
	vGuns.push_back(gun);
	gun = new MINI_UZI(66, 8, 43);
	vGuns.push_back(gun);
	gun = new MP5(75, 8, 43);
	vGuns.push_back(gun);
}