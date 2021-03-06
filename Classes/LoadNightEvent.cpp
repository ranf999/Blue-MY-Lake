#include "LoadNightEvent.h"
#include "GlobalRes.h"
#include "AnimLib.h"
#include "EventManager.h"
#include "TimeUtil.h"
#include "Map.h"
#include "ReloadEvent.h"
#include "GlobalTmp.h"
 
void LoadNightEvent::happen()
{
	ReloadEvent::getPrev(this->args)->repeat=false;

  // Switch Background Music
  AudioPlayer::PlayNightBGM();
  
	if(sGlobal->isNight==true) return; 
	sGlobal->isNight=true;
	rGlobal->map->scheduleOnce(schedule_selector(LoadNightEvent::delayedLoad), 0.6f);
	ReloadEvent::action();
}

void LoadNightEvent::delayedLoad(float dt)
{
	ReloadEvent::getPrev(tGlobal->arrForReloads)->repeat=true;

	Map* map=(Map*)rGlobal->map;
	int mapNo=sGlobal->mapState->mapNo;
	for (int i = 0; i < map->NPCs->count(); i++)
	{
		CCNode* npc=(CCNode*)map->NPCs->objectAtIndex(i);
		npc->removeFromParent();
	}
	map->NPCs->release();
	eManager->release();
	eManager->loadNight(mapNo-MAP10);
	map->initNPC();
	eManager->redoAll();
}
