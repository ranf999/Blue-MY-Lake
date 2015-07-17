#include "GlobalState.h"
#define SAVE_INT CCUserDefault::sharedUserDefault()->setIntegerForKey
#define SAVE_BOOL CCUserDefault::sharedUserDefault()->setBoolForKey
#define LOAD_INT CCUserDefault::sharedUserDefault()->getIntegerForKey
#define LOAD_BOOL CCUserDefault::sharedUserDefault()->getBoolForKey

void GlobalState::load()
{
    loadMapState();
    loadSuperPower();
    loadPlayerState();
    loadDoneList();
}

void GlobalState::save()
{
   SAVE_INT(POSITIONX_MRCD, mapState->positionX);
   SAVE_INT(POSITIONY_MRCD, mapState->positionY);
   SAVE_INT(FACEDIR_MRCD, mapState->faceDir);
   SAVE_INT(MAPNO_MRCD, mapState->mapNo);
   SAVE_INT(STORYCNT_MRCD, mapState->storyCnt);

   SAVE_INT(SPEED_SRCD, superPower->speed);
   SAVE_BOOL(TELEPORT_SRCD, superPower->teleport);
   SAVE_BOOL(STEALTH_SRCD, superPower->stealth);
   SAVE_BOOL(SURF_SRCD, superPower->surf);
}

void GlobalState::newr()
{
   SAVE_INT(POSITIONX_MRCD,POSITIONX_INI);
   SAVE_INT(POSITIONY_MRCD,POSITIONY_INI);
   SAVE_INT(FACEDIR_MRCD,FACEDIR_INI);
   SAVE_INT(MAPNO_MRCD,MAPNO_INI);
   SAVE_INT(STORYCNT_MRCD,STORYCNT_INI);

   SAVE_INT(SPEED_SRCD,SPEED_INI);
   SAVE_BOOL(TELEPORT_SRCD,TELEPORT_INI);
   SAVE_BOOL(STEALTH_SRCD,STEALTH_INI);
   SAVE_BOOL(SURF_SRCD,SURF_INI);
}

GlobalState::~GlobalState()
{
    delete []doneList;
}



void GlobalState::loadMapState()
{
    mapState=new MapState;
    mapState->positionX = LOAD_INT(POSITIONX_MRCD, POSITIONX_INI);
    mapState->positionY = LOAD_INT(POSITIONY_MRCD, POSITIONY_INI);
    mapState->faceDir= LOAD_INT(FACEDIR_MRCD, FACEDIR_INI);
    mapState->mapNo = LOAD_INT(MAPNO_MRCD, MAPNO_INI);
    mapState->storyCnt = LOAD_INT(STORYCNT_MRCD, STORYCNT_INI);
}

void GlobalState::loadSuperPower()
{
    superPower=new SuperPower;
    superPower->speed = LOAD_INT(SPEED_SRCD, SPEED_INI);
    superPower->teleport = LOAD_BOOL(TELEPORT_SRCD, TELEPORT_INI);
    superPower->stealth = LOAD_BOOL(STEALTH_SRCD, STEALTH_INI);
    superPower->surf = LOAD_BOOL(SURF_SRCD, SURF_INI);
    superPower->flash= LOAD_BOOL(FLASH_SRCD, FLASH_INI);
}

void GlobalState::loadDoneList()
{
	doneList=new bool[100];//@macro
	for(int i=0;i<100;i++)
		doneList[i]=false;
	//load from file
}

void GlobalState::loadPlayerState()
{

}
