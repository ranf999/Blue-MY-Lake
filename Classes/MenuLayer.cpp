#include "MenuLayer.h"
USING_NS_CC;


CCScene* MenuLayer::scene()
{
    CCScene *scene = CCScene::create();
    MenuLayer *layer = MenuLayer::create();
    scene->addChild(layer);
    return scene;
}


bool MenuLayer::init()
{
    if ( !CCLayer::init() )
        return false;

	//³õÊ¼»¯
	
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
	CCSize size = CCDirector::sharedDirector()->getWinSize();
    pSprite->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pSprite, 0);

	//CCScene* story=StoryWorld::scene();
	//CCDirector::sharedDirector()->pushScene(story);//@
	//CCDirector::sharedDirector()->replaceScene(story);



	//touch×¢²á
	this->setTouchEnabled(true);
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);

	return true;
}

bool MenuLayer::ccTouchBegan(CCTouch *pTouch,CCEvent *pEvent)
{
	//CCDirector::sharedDirector()->popScene();
	return true;
}

void MenuLayer::ccTouchEnded(CCTouch *pTouch,CCEvent *pEvent)
{
}

void MenuLayer::ccTouchMoved(CCTouch *pTouch,CCEvent *pEvent)
{
}