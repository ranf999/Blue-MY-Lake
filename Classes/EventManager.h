#ifndef _EVENT_MANAGER_H_
#define _EVENT_MANAGER_H_
#include "cocos2d.h"
#include "Singleton.hpp"
#include "EventLoader.h"
#include "Emap.h"
#include "ControllerListener.h"
using namespace cocos2d;
//loads the Events in memory
//executes the Events for Hero and ButtonA

#define A_TRIG 0
#define STAND_TRIG 1
#define STAND_TRIG_IMGNO -10
#define ATRIG_NO_MAN_IMGNO -1
#define EVENT_CSV_PATH "csv/event%d.csv"

class EventManager
{
public:
    void load(int sTime);
    ControllerListener* happen(CCPoint coord, int ent);//entrance through hero or buttonA
	void next();
	void release();
    ~EventManager();
public:
    CCArray* events;
    Emap* eStand;
    Emap* eAtrgr;
	Event* onGoing;
private:
    Event* findEventById(int id);
    ControllerListener* listener(int type);
    void loadAllEvents(int sTime);
    void loadEmap();
    void markHappened(Event* event);
};
typedef Singleton<EventManager> sEventManager;
#define eManager sEventManager::instance()
#endif
