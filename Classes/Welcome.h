//
//  Welcome.h
//  血色明远湖
//
//  Created by Ring King on 5/20/14.
//
//

#ifndef _________Welcome__
#define _________Welcome__

#include "cocos2d.h"
#include "AppMacros.h"
using namespace cocos2d;
//update：2014-10-1 15:59:03

class Welcome : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Welcome);
	void ccTouchesEnded(CCSet* pTouches, CCEvent *pEvent);
protected:
    void menuStartCallback(CCObject* pSender);
	void menuClearCallback(CCObject* pSender);
private:
	int state;
	CCTouch* prevTouch;
};

#endif /* defined(_________Welcome__) */
