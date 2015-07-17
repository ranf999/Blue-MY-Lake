#ifndef __RCD_UTIL__
#define __RCD_UTIL__

#include "cocos2d.h"
using namespace cocos2d;

class RcdUtil
{
public:
	static CCArray* loadFile(CCString* sPath); //loads file to line list
	static CCArray* split(CCArray* line, char delim);
	static void saveList(CCArray* list, char delim, CCString* sPath);
	static void saveLines(CCArray* lines, CCString* sPath);
	static int getInt(CCString* str);
};

#endif
