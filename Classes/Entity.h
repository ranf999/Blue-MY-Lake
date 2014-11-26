#ifndef _Entity_H_
#define _Entity_H_

#include "cocos2d.h"
using namespace cocos2d;

class Entity: public CCNode
{
public:
	void bindSprite(CCSprite* sprite);
protected:
    CCSprite* sprite;
};

#endif