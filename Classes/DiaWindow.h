#ifndef __DIA_WINDOW_H__
#define __DIA_WINDOW_H__
#include "cocos2d.h"
#include "Window.h"
#include "HumanEntity.h"
using namespace cocos2d;

//update:2014-9-26 17:34:44

class DiaWindow:public Window,public Controller
{
public:
	CREATE_FUNC(DiaWindow);
	bool init();
	void initSprite();
	void load(Map* map,CCDictionary *properties);
	void respond();
	void appear();
	void disappear();
	bool hasTouchEnded();
private:
	int nStr;
	int nNext;
};

#endif
