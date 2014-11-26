#include "WalkingMan.h"

bool WalkingMan::init()
{
	walkAnimations=new CCAnimation*[4];
	for(int i=0;i<4;i++)
		walkAnimations[i]=createAnimationForDirection(i);
	return true;
}

void WalkingMan::goWalking(float dt)
{
	CCAnimate* anim=CCAnimate::create(walkAnimations[dir]);//ÐÐ×ß
	moveLegs=CCRepeatForever::create(anim);
	this->runAction(moveLegs);
}

void WalkingMan::goAct()
{
	//read in 
	//this->controllerListener->respond(
	//this->goWalking(
	//schedule endrespond
	//schedule this->stopAction setFaceDir

}