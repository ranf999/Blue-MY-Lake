#include "RcdUtil.h"

CCArray* RcdUtil::loadFile(CCString* sPath)
{
    return FileLoadUtil::sharedFileLoadUtil()->getDataLines(sPath);
}

CCArray* RcdUtil::split(CCString* line, char delim)
{
	//Use std::string member of CCString
}

void RcdUtil::saveList(CCArray* list, char delim, CCString* sPath)
{
	for(int i=0;i<list->count;i++)
	{
		CCString* elem=(CCString*)list->objectAtIndex(i);
		//Save here 
	}
}

void RcdUtil::saveLines(CCArray* lines, CCString* sPath)
{
	for(int i=0;i<lines->count();i++)
	{
		CCString* list=(CCArray*)lines->objectAtIndex(i);
		saveList(list);
	}
}

int RcdUtil::getInt(CCString* str)
{
	return atoi(str.getCString());
}
