#ifndef __MENU_H__
#define __MENU_H__
#include "cocos2d.h"
#include "GlobalPath.h"
#include "Hero.h"
#include "GalleryScene.h"
#include "WebViewScene.h"
using namespace cocos2d;

class Menu:public CCLayer
{
public:
	CREATE_FUNC(Menu);
	bool init();
	void setHero(Hero* hero);
private:
	void mssn(CCObject *sender);
	void quit(CCObject *sender);
	void ret(CCObject *sender);
	void show(CCObject* sender);
	void info(CCObject* sender);
	void web(CCObject* sender);
public:
	CCMenu* menu;
	CCMenu* menuButton;
	Hero* hero;
};

#endif
