#include "TurningMan.h"

bool TurningMan::init()
{
	return true;
}

//由于没有id无法初始化，所以在setID中初始化
TurningMan* TurningMan::create(int id)
{
	TurningMan* man=create();
	man->setID(id);
	man->initSprite();
	man->initAnim(0);
	man->goWalking(0);
	return man;
}

void TurningMan::initAnim(int dir)
{
	CCAnimation* animation=createAnimationForDirection(-1);
	CCAnimate* anim=CCAnimate::create(animation);
	forever=CCRepeatForever::create(anim);
}

void TurningMan::goWalking(float dt)
{
	sprite->runAction(forever);
}

void TurningMan::respond(int dir)
{
	setFaceDirection(dir);
	sprite->stopAllActions();
}

void TurningMan::endRespond()
{
	sprite->resumeSchedulerAndActions();
}