#include "cocos2d.h"
#include "HumanEntity.h"
#include "Controller.h"
using namespace cocos2d;

#ifndef __WALKING_MAN_H__
#define __WALKING_MAN_H__

class WalkingMan:public HumanEntity,public Controller
{
public:
	bool init();
	virtual void goWalking(float dt);
	void goAct();
public:
	cocos2d::CCAnimation** walkAnimations;
	cocos2d::CCAction* moveLegs;
};

#endif