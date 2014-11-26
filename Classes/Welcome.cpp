//
//  Welcome.cpp
//  血色明远湖
//
//  Created by Ring King on 5/20/14.
//
//
//update:2014-9-30 10:57:51

#include "Welcome.h"
#include "HelloWorldScene.h"
//update：2014-10-1 15:59:03

USING_NS_CC;

CCScene* Welcome::scene() {
    CCScene *scene = CCScene::create();
    Welcome *layer = Welcome::create();
    scene->addChild(layer);
    return scene;
}

bool Welcome::init() {
    if (!CCLayer::init()) {
        return false;
    }

	this->prevTouch=NULL;
	this->setTouchEnabled(true);
	this->state=0;

    CCSprite *mainbackground = CCSprite::create(GATE_PATH);
    mainbackground->setPosition(ccp(CCDirector::sharedDirector()->getVisibleSize().width/2,
		CCDirector::sharedDirector()->getVisibleSize().height/2));
    addChild(mainbackground,0);
    CCMenuItemImage *start = CCMenuItemImage::create(START1_PATH,START2_PATH,
		this,menu_selector(Welcome::menuStartCallback));
	CCMenuItemImage *clear = CCMenuItemImage::create(BUTTONB_PATH,BUTTONBD_PATH,
		this,menu_selector(Welcome::menuClearCallback));
	start->setPosition(ccp(CCDirector::sharedDirector()->getVisibleSize().width/2,
		CCDirector::sharedDirector()->getVisibleSize().height/2));

    CCMenu* pMenu = CCMenu::create(start, clear, NULL);
    pMenu->setPosition(CCPointZero);
    addChild(pMenu, 2);

    return true;
}

void Welcome::menuStartCallback(CCObject* pSender) {
	if (cocos2d::CCUserDefault::sharedUserDefault()->getBoolForKey("FisrtSave", true))
		menuClearCallback(NULL);
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(MAP_RESOLUWID,MAP_RESOLUHEI, kResolutionExactFit);
	CCScene *pScene = HelloWorld::scene();
    CCTransitionFade *scenetrans = CCTransitionFade::create(0.7, pScene);
    CCDirector::sharedDirector()->replaceScene(scenetrans);
}

void Welcome::menuClearCallback(CCObject* pSender) {
	cocos2d::CCUserDefault::sharedUserDefault()->setBoolForKey("FisrtSave", FIRSTSAVE_INI);
	cocos2d::CCUserDefault::sharedUserDefault()->setIntegerForKey("PositionX", POSITIONX_INI);
	cocos2d::CCUserDefault::sharedUserDefault()->setIntegerForKey("PositionY", POSITIONY_INI);
	cocos2d::CCUserDefault::sharedUserDefault()->setIntegerForKey("MapProcess", MAPPROCESS_INI);
	cocos2d::CCUserDefault::sharedUserDefault()->setIntegerForKey("Process", PROCESS_INI);
	cocos2d::CCUserDefault::sharedUserDefault()->flush();
}

void Welcome::ccTouchesEnded(CCSet* pTouches, CCEvent *pEvent)
{
	CCTouch* touch=(CCTouch*)pTouches->anyObject();
	int xnd=touch->getLocation().x,xnu=touch->getStartLocation().x;
	int ynd=touch->getLocation().y,ynu=touch->getStartLocation().y;
	if(state==0)
	{
		bool pie=xnu>xnd&&ynu>ynd&&(xnu-xnd)>((ynu-ynd)/10);
		if(pie)
		{
			state++;
			CC_SAFE_RELEASE(prevTouch);
			prevTouch=touch;
			CC_SAFE_RETAIN(prevTouch);
		}
	}
	else if(state==1)
	{
		int xpd=prevTouch->getLocation().x,xpu=prevTouch->getStartLocation().x;
		int ypd=prevTouch->getLocation().y,ypu=prevTouch->getStartLocation().y;
		bool pie=ypu>ynu&&ypd<ynd&&xnu>xpu&&xnd>xpd&&abs(xnu-xnd)<((ynu-ynd)/2);
		if(pie)
		{
			state++;
			prevTouch->release();
			prevTouch=touch;
			prevTouch->retain();
		}
		else state=0;
	}
	else if(state==2)
	{
		int xpd=prevTouch->getLocation().x,xpu=prevTouch->getStartLocation().x;
		int ypd=prevTouch->getLocation().y,ypu=prevTouch->getStartLocation().y;
		bool pie=ypu<ynu&&ypd>ynd&&xnu>xpu&&xnd>xpd&&abs(xnu-xnd)<((ynu-ynd)/2);
		if(pie)
			cocos2d::CCUserDefault::sharedUserDefault()->setBoolForKey("Superpower", true);
		state=0;
		prevTouch->release();
	}
	cocos2d::CCUserDefault::sharedUserDefault()->setBoolForKey("Superpower", true);//$
}