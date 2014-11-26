#include "cocos2d.h"
#include "HumanEntity.h"
#include "ControllerListener.h"
using namespace cocos2d;

#ifndef __TURNING_MAN_H__
#define __TURNING_MAN_H__
class TurningMan: public HumanEntity
{
public:
	CREATE_FUNC(TurningMan);
	static TurningMan* create(int id);
	bool init();
	void respond(int dir);
	void endRespond();
private:
	void initAnim(int dir);
	void goWalking(float dt);
private:
	CCFiniteTimeAction* forever;
};
//在setID中开始初始化过程
#endif