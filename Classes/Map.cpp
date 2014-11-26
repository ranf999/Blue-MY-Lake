#include "Map.h"
#include "cocos2d.h"
USING_NS_CC;

//update:2014-10-1 03:30:49

Map* Map::create()
{
    int mapNo = cocos2d::CCUserDefault::sharedUserDefault()->getIntegerForKey(MAPPROCESS_RCD);
	if(mapNo==MAP11)return Map::create(MAP11_PATH);//读取地图号map11
	else return Map::create(MAP12_PATH);//读取地图号map12	
}

Map* Map::create(const char *tmxFile)
{
    Map *pRet = new Map();
    if (pRet->initWithTMXFile(tmxFile))
    {
		/*CCArray* pchildrenArray = pRet->getChildren();
		CCSpriteBatchNode *child = NULL;
		CCObject *pobject = NULL;
		CCARRAY_FOREACH(pchildrenArray,pobject)
		{
		child = (CCSpriteBatchNode *)pobject;
		if (!child)
		break;
		child->getTexture()->setAntiAliasTexParameters();
		}
		*/
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void Map::setGameStartPos()
{
	int x,y;
	x = cocos2d::CCUserDefault::sharedUserDefault()->getIntegerForKey(POSITIONX_RCD);
	y = cocos2d::CCUserDefault::sharedUserDefault()->getIntegerForKey(POSITIONY_RCD);
	
	//设置地图位置
	CCPoint tileBirthPoint=ccp(x,y);//@读取初始位置63,98
	this->setPosition(humanPosForTileMove(tileBirthPoint));
}

void Map::initNPC()
{
	//NPC
	CCTMXObjectGroup* objGroup=this->objectGroupNamed(INFORMATION_GRP);
	cturnNPC=initNPCPointer(objGroup);

	if (objGroup)
	{
		//创建转圈的小人
		CCDictionary *properties = objGroup->objectNamed(TURNINGMAN_OBJ);
		if (properties)
			createNPC(properties,TURNINGMAN_ATTNUM,0);
		//创建站着的小人
		properties = objGroup->objectNamed(STANDINGMAN_OBJ);
		if (properties)
			createNPC(properties,STANDINGMAN_ATTNUM,cturnNPC);
	}
}

void Map::createNPC(CCDictionary *properties,int type,int start)
{
	//读取属性
	const CCString *snnpc = properties->valueForKey(NNPC_ATT);
	int npcAtt[4];	char attName[]=NPCAX_ATT;
	int innpc=snnpc->intValue();int count=start;
	for(int i=0;i<innpc;i++)
	{
		attName[4]='x';
		for(int j=0;j<type;j++)
		{
			snnpc=properties->valueForKey(attName);
			npcAtt[j]= snnpc->intValue();
			attName[4]+=1;
		}
		//创建人物：原地转圈的NPC
		HumanEntity* man;
		if(type==3)man=TurningMan::create(npcAtt[2]);
		else man=StandingMan::create(npcAtt[2]);
		if(type==4)
		{
			man->setFaceDirection(npcAtt[3]);
			man->dir=npcAtt[3];
		}
		this->addChild(man,4);
		this->NPCs[i+start]=man;
		if(type==3)man->setTag(TURNINGMAN_START+npcAtt[2]);
		else man->setTag(STANDINGMAN_START+npcAtt[2]);
		man->setPosition(positionFromTileCoord(ccp(npcAtt[0],npcAtt[1])));
		attName[3]+=1;
	}
}

int Map::initNPCPointer(CCTMXObjectGroup* objGroup)
{
	CCDictionary *properties1 = objGroup->objectNamed(TURNINGMAN_OBJ);
	int tinnpc = properties1->valueForKey(NNPC_ATT)->intValue();
	CCDictionary *properties2 = objGroup->objectNamed(STANDINGMAN_OBJ);
	int sinnpc = properties2->valueForKey(NNPC_ATT)->intValue();
	totalNPC=tinnpc+sinnpc;
	this->NPCs=new ControllerListener* [totalNPC];
	return tinnpc;
}

void Map::removeAllChildrenWithCleanup(bool cleanup)
{
	CCTMXTiledMap::removeAllChildrenWithCleanup(cleanup);
	//delete []NPCs;
}

Map* Map::crossMap(CCPoint tileBirthPoint,int mapNo)
{
	if(mapNo==MAP11)
		tileBirthPoint=ccp(2+3,tileBirthPoint.y);
	else
		tileBirthPoint=ccp(this->getMapSize().width-3-3,tileBirthPoint.y);
	this->setPosition(this->humanPosForTileMove(tileBirthPoint));
	initNPC();
	return this;
}


//内部工具函数Tilemap坐标转2dx坐标
CCPoint Map::positionFromTileCoord(CCPoint tileCoord)
{
	CCPoint pos=ccp(((tileCoord.x+0.5)*this->getTileSize().width),((this->getMapSize().height-
		tileCoord.y)*this->getTileSize().height+this->getTileSize().height*3/16));//站在地板中央！
	return pos;
}
//内部工具函数2dx坐标转Tilemap坐标
CCPoint Map::tileCoordFromPosition(CCPoint position)
{
	int x=position.x/this->getTileSize().width;
	int y=(((this->getMapSize().height-1)*this->getTileSize().height)-position.y)/this->getTileSize().height;
	return ccp(x,y);
}
//初始化地图时的转换工具
CCPoint Map::humanPosForTileMove(CCPoint tileCoord)
{
	CCPoint deltaMiddle;
	deltaMiddle.x=(int)(CCDirector::sharedDirector()->getWinSize().width/2/this->getTileSize().width);
	deltaMiddle.y=this->getMapSize().height-(int)(CCDirector::sharedDirector()->getWinSize().height/2/this->getTileSize().height)-1;
	CCPoint position=tileCoord-deltaMiddle;//ccp(7,14);
	return ccp(-position.x*this->getTileSize().width,position.y*this->getTileSize().height);
}