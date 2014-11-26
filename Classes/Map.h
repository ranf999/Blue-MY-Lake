#ifndef __MAP_H__
#define __MAP_H__
#include "cocos2d.h"
#include "TurningMan.h"
#include "StandingMan.h"
#include "WalkingMan.h"
using namespace cocos2d;

//update:20140926.0049

class Map : public CCTMXTiledMap
{
public:
	static Map* create();
	static Map* create(const char *tmxFile);
	void setGameStartPos();
	void initNPC();
	CCPoint tileCoordFromPosition(CCPoint pos);
	CCPoint positionFromTileCoord(CCPoint tileCoord);
	CCPoint humanPosForTileMove(CCPoint tileCoord);
	Map* crossMap(CCPoint tileBirthPoint,int mapNo);
	virtual void removeAllChildrenWithCleanup(bool cleanup);
public:
	ControllerListener** NPCs;
	int cturnNPC;
private:	
	int initNPCPointer(CCTMXObjectGroup* objGroup);
	void createNPC(CCDictionary *properties,int type,int start);
	int totalNPC;
};
#endif