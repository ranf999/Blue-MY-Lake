#include <cstdlib>
#include "cocos2d.h"
#include "AppMacros.h"
#include "Entity.h"
#include "Animation.h"
#include "Ability.h"
using namespace cocos2d;

#ifndef __CHARACTER_H__
#define __CHARACTER_H__

class Character :public Entity
{
public:
	virtual bool init();
	bool ishero;
	int ID;
	CCString name;
	int Hp;
	int remainHp;
	int level;
	int attack;
	int defence;
	int speAtt;
	int speDef;
	int speed;
	int nAbility;
	CCArray* abilities;//技能
	Ability* ability;
public:	
	void getability(int num);
	int	giveHurt(int abilityNum,int& type);//参数：
	CCFiniteTimeAction* getGiveHurtAction(int abilityNum);
	CCFiniteTimeAction* getRecvHurtAction(int abilityNum);
	CCFiniteTimeAction* exitAction();
	void receiveHurt(int hurt,int& type);
	bool isDead();

};
#endif