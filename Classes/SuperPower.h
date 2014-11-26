#ifndef _SUPER_POWER_H_
#define _SUPER_POWER_H_
#include "cocos2d.h"

class SuperPower
{
public:
	SuperPower();
	SuperPower(float sp,bool tele,bool st,bool sf,bool fl);
	float speed;
	bool teleport;
	bool stealth;
	bool surf;
	bool flash;
};
#endif