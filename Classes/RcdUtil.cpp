#include "RcdUtil.h"

CCArray* RcdUtil::loadFile(CCString* sPath)
{
    return FileLoadUtil::sharedFileLoadUtil()->getDataLines(sPath);
}

CCArray* RcdUtil::split(CCString* line, char delim)
{
	//Use std::string member of CCString
	//following assume std::string sline
	//CCArray* list=CCArray::create();
	//int pos=sline.find(delim);
	//while(pos!=sline.size()-1)
	//{
		//CCString* elem=CCString::create(sline.substr(0,pos-0));
		//list.addObject(elem);
		//pos=sline.find(delim);
	//}
	//return list;
}

void RcdUtil::saveList(CCArray* list, char delim)
{
	//conver list ==> string 
	CCString* rcdStr;
	for(int i=0;i<list->count;i++)
	{
		CCString* elem=(CCString*)list->objectAtIndex(i);
		rcdStr+=elem, rcdStr+=delim; //if CCString reloads operator+
	}
	//Save here
	CCUserDefault::sharedUserDefault()->setStringForKey(rcdStr, "Change Key");
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
