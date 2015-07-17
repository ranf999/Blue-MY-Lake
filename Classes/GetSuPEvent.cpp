#include "GlobalState.h"
#include "GetSuPEvent.h"

void GetSuPEvent::happen()
{
    superPower->speed = 3;
    superPower->teleport = true;
    superPower->stealth = true;
    superPower->surf = true;
    superPower->flash= true;
}
