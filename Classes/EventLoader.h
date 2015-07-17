#ifndef _EVNET_LOADER_H_
#define _EVNET_LOADER_H_
#include "cocos2d.h"
#include "Event.h"
#include "FileLoadUtil.h"
#include "StringUtil.h"
#include "TalkManEvent.h"
using namespace cocos2d;
#define EVENT_ATT_NUM 9
#define TALKMAN_EVT 0

class EventLoader
{
public:
   static CCArray* start(const char* sFilePath);
};
#endif
