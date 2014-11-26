#include "Hero.h"

//update:2014-10-2 11:20:20
bool Hero::init() {
	//四个方向的行走动画
	setID(0);
	WalkingMan::init();
	moveMap=NULL,moveLegs=NULL;
	//初始化Sprite
	initSprite();
	sprite->setAnchorPoint(CCPointZero+ccp(0.5,-0.625));//x+1人往左跑，y+1人向下跑
	sprite->setTag(IMGSP);
	isHeroWalking=false;
	this->superPower=new SuperPower;
	superPower->teleport=true;superPower->speed=2.0f;//$
	storyCnt=0;
	mapNo=cocos2d::CCUserDefault::sharedUserDefault()->getIntegerForKey(MAPPROCESS_RCD);
	dir=Down;map=NULL;
	//superPower=CCUserDefault::sharedUserDefault()->getBoolForKey("Superpower",false);
	cocos2d::CCUserDefault::sharedUserDefault()->setBoolForKey("Superpower", false);
    return true;
}

void Hero::doEvent(CCPoint heroTilePos)
{
	//获取脚下event层tile id
	int tileGid = map->layerNamed(EVENT_MLYR)->tileGIDAt(heroTilePos); 

	//如果stand属性有值，站触发事件响应
	if (tileGid)
	{
		CCDictionary *properties = map->propertiesForGID(tileGid);
		if (properties)
		{
			const CCString *eventScene = properties->valueForKey("stand");
			//路名事件
			if(!eventScene->compare("place name"))
				this->rwindow->respond(map,properties);
			//场景切换事件inte
			else if(!eventScene->compare("change scene"))
			{
				int id=properties->valueForKey("id")->intValue();
				switch(id)
				{
				case 0:case 1:case 2:case 3:case 4:
				case 5:case 6:case 7:case 8:case 9:
					{
						if(id==storyCnt)
						{
							touchEnded=dir;walkEnd();//endWalking
							this->focus=false;
							cocos2d::CCUserDefault::sharedUserDefault()->setIntegerForKey("PositionX", heroTilePos.x);
							cocos2d::CCUserDefault::sharedUserDefault()->setIntegerForKey("PositionY", heroTilePos.y);
							cocos2d::CCUserDefault::sharedUserDefault()->setIntegerForKey("MapProcess", mapNo);
							cocos2d::CCUserDefault::sharedUserDefault()->flush();
							CCEGLView::sharedOpenGLView()->setDesignResolutionSize(JX_RESOLUWID, JX_RESOLUHEI, kResolutionExactFit);
							CCScene* story=StoryWorld::scene();
							CCDirector::sharedDirector()->pushScene(story);
							cocos2d::CCUserDefault::sharedUserDefault()->setIntegerForKey("Process", storyCnt+1);
							this->gotFocusT();
							storyCnt++;
						}
					}
					break;
					
				case MAP11:
					this->mapNo=MAP12;
					touchEnded=dir;walkEnd();

					map->removeAllChildrenWithCleanup(true);
					map=Map::create(MAP12_PATH);//@
					map->initNPC();
					map->crossMap(heroTilePos,MAP11);
					this->getParent()->addChild(map);
					break;
				case MAP12:
					this->mapNo=MAP11;
					touchEnded=dir;walkEnd();
					map->removeAllChildrenWithCleanup(true);
					map=Map::create(MAP11_PATH);//@
					map->initNPC();
					map->crossMap(heroTilePos,MAP12);
					this->getParent()->addChild(map);
					break;
				default:break;
				}
			}
			else if(!eventScene->compare("combat"))
			{

				float i = CCRANDOM_0_1();
				if (i<0.3)
				{
					touchEnded=dir;walkEnd();//endWalking
					this->focus=false;
					CCEGLView::sharedOpenGLView()->setDesignResolutionSize(JX_RESOLUWID, JX_RESOLUHEI, kResolutionExactFit);

					CCScene* combat=Combat::scene();

					CCDirector::sharedDirector()->pushScene(combat);//@
				}
				this->focus=true;

			}
			else if(!eventScene->compare("portal"))
			{
				touchEnded=dir;walkEnd();//endWalking
				this->focus=false;
				int x=properties->valueForKey("idx")->intValue();//@
				int y=properties->valueForKey("idy")->intValue();
				CCPoint dest=ccp(x,y);
				CCAnimate* spin=CCAnimate::create(this->createAnimationForDirection(5));//行走
				CCRepeat* spinM=CCRepeat::create(spin,6);
				CCCallFunc* regotF=CCCallFunc::create(this,callfunc_selector(Hero::gotFocusT));
				CCSequence* goSpin=CCSequence::create(spinM,regotF,NULL);
				CCDelayTime* delay=CCDelayTime::create(1);
				CCPlace* mov=CCPlace::create(map->humanPosForTileMove(dest));
				CCSequence* fly=CCSequence::create(delay,mov,NULL);
				sprite->runAction(goSpin);
				map->runAction(fly);
			}     
		}
	}
}









void Hero::respond(int dir) {
	if(isHeroWalking||!focus){return;}
	//CCLOG("respond");
	initAnim(dir);
	goWalking(0);
}

void Hero::endRespond()
{
	touchEnded=dir;
}

void Hero::dealEvent()
{
	if (checkEvent(getHeroTilePos())==kEvent)
		doEvent(getHeroTilePos());
}

void Hero::dealCollision()
{
	CCPoint heroPosition = this->getPosition()-map->getPosition();
	if(checkCollision(ccp(heroPosition.x+move.x,heroPosition.y+move.y-map->getTileSize().height/4))==kWall)
	{
		touchEnded=dir;walkEnd();
	}
}

void Hero::walkEnd()
{
	CCPoint thisPoint=map->getPosition();
	CCPoint diff=thisPoint-point;
	CCLOG("%f,%f\t%f,%f",thisPoint.x,thisPoint.y,diff.x,diff.y);
	point=map->getPosition();
	if(touchEnded>-1)
	{
		map->pauseSchedulerAndActions();
		map->stopAction(moveMap);
		sprite->stopAction(moveLegs);
		moveMap=NULL,moveLegs=NULL;
		setFaceDirection(dir);
		isHeroWalking=false;
	}
}

//英雄行走
void Hero::goWalking(float dt)
{
	isHeroWalking = true;
	map->runAction(moveMap);
	sprite->runAction(moveLegs);
}

void Hero::initAnim(int dir)
{
	touchEnded=-1;
	CCPoint moveByPosition,revMoveByPosition;
    switch(dir)
	{
		case Down:moveByPosition=ccp(0,-32);break;
		case Left:moveByPosition=ccp(-32,0);break;
		case Right:moveByPosition=ccp(32,0);break;
		case Up:moveByPosition=ccp(0,32);break;
		default:break;
	}
	revMoveByPosition=-moveByPosition;
	this->move=moveByPosition,this->dir=dir;

	//行走和位移两个动作
	const float duration=0.40f*0.8f/superPower->speed;
	CCJumpBy* jump=CCJumpBy::create(duration,ccp(0,0),16,1);
	CCMoveBy* revShift=CCMoveBy::create(duration,revMoveByPosition);
	CCDelayTime* delay=CCDelayTime::create(1.5f/32.0f*duration*1.8);
	CCAnimate* anim=CCAnimate::create(walkAnimations[dir]);//行走
	CCCallFunc* dealC=CCCallFunc::create(this,callfunc_selector(Hero::dealCollision));
	CCCallFunc* dealE=CCCallFunc::create(this,callfunc_selector(Hero::dealEvent));
	CCCallFunc* endWalk=CCCallFunc::create(this,callfunc_selector(Hero::walkEnd));
	//CCSpawn* animJ=CCSpawn::create(anim,jump,NULL);
	CCSequence* revAct=CCSequence::create(dealC,delay,revShift,dealE,endWalk,NULL);
	moveLegs=CCRepeatForever::create(anim);
	moveMap=CCRepeatForever::create(revAct);
}









//地图事件检测
CollisionType Hero::checkEvent(CCPoint heroTilePos)
{
	int tileGid = map->layerNamed(EVENT_MLYR)->tileGIDAt(heroTilePos);
	if (tileGid)return kEvent;  
	return kNone;
}

//碰撞检测
CollisionType Hero::checkCollision(CCPoint heroPosition)
{
	//cocos2d坐标转换为Tile坐标
	CCPoint tileCoord = map->tileCoordFromPosition(heroPosition);
	//超过地图边界返回kWall
	if (heroPosition.x<0||tileCoord.x>map->getMapSize().width-1||
		tileCoord.y>map->getMapSize().height-2||heroPosition.y<0)
		return kWall;

	//获取地图块ID，在wall层如果没有墙
	int wTileGid= map->layerNamed(WALL_MLYR)->tileGIDAt(tileCoord);
	int bTileGid= map->layerNamed(BUILDING_MLYR)->tileGIDAt(tileCoord);
	int b2TileGid= map->layerNamed(BUILDING2_MLYR)->tileGIDAt(tileCoord);
	int wtTileGid= map->layerNamed(WATER_MLYR)->tileGIDAt(tileCoord);
	int eTileGid= map->layerNamed(EVENT_MLYR)->tileGIDAt(tileCoord);bool batrg=false;
	if(eTileGid)batrg=map->propertiesForGID(eTileGid)->valueForKey("atrg")->compare("")!=0;
	if(wTileGid||bTileGid||b2TileGid||batrg||wtTileGid)return kWall;
	return kNone;
}

CCPoint Hero::getHeroTilePos()
{
	return map->tileCoordFromPosition(getPosition()-map->getPosition());
}

void Hero::gotFocusT()
{
	focus=true;
}

void Hero::setRWindow(PlacenameWindow* win)
{
	this->rwindow=win;
}

void Hero::setTiledMap( Map* map )
{
    this->map = map;
	move=ccp(0,-map->getTileSize().height);
	point=map->getPosition();
}