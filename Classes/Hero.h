#ifndef __HERO_H__
#define __HERO_H__

#include "Map.h"
#include "BigWindow.h"
#include "PlacenameWindow.h"
#include "Story.h"
#include "SuperPower.h"
#include "AppMacros.h"

class Hero : public WalkingMan{
public:
    CREATE_FUNC(Hero);
    virtual bool init();
	void setTiledMap(Map* map);
	void setRWindow(PlacenameWindow* win);
	void gotFocusT();
	
	void respond(int dir);
	void endRespond();
	
	CCPoint getHeroTilePos();
	CollisionType checkCollision(CCPoint heroPosition);
	CollisionType checkEvent(CCPoint heroPosition);
public:
	Map* map;
	CCPoint move;
	bool isHeroWalking;
	int mapNo;
	int storyCnt;	
	SuperPower* superPower;
private:
	void initAnim(int dir);
	void goWalking(float dt);
	void walkEnd();
	void dealEvent();
	void doEvent(CCPoint heroPosition);
	void dealCollision();
	cocos2d::CCAction* moveMap;
	int touchEnded;
	bool focus;
	PlacenameWindow* rwindow;
	CCPoint point;
};

#endif