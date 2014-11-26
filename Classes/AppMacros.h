#ifndef _APPMACROS_H_
#define _APPMACROS_H_

#include "GlobalPath.h"
#include "cocos2d.h"
//update:2014-9-29 13:23:33


//layer的命名法是scene的首字母加layer名加LAYER
//layer是100+
#define HELLOWORLDLAYER 100

//HelloWorld的儿子
#define MAPLAYER 101
#define CONTROLPANELLAYER 102

//MapLayer的儿子
#define MAP 590
#define HERO 510

//Map的儿子
#define TURNINGMAN_START 36 
#define TURNINGMAN_END 45
#define STANDINGMAN_START 46
#define STANDINGMAN_END 55

//ControlPanel的儿子
#define RWINDOW 521
#define BIGWINDOW 522
#define DIAWINDOW 523
#define DIRBUTTON 1
#define BUTTONA 10
#define TOUCHSCREEN 100

//Combat的儿子
#define BACKGROUND 100 



//Entity bind的sprite命名是IMGSP
#define IMGSP 500
#define DIABOXSP 501
#define LABELSP 502
#define CONTENTSP 503

//地图层的命名法是图层名加_MLYR
#define EVENT_MLYR "event"
#define BUILDING2_MLYR "building2"
#define BUILDING_MLYR "building"
#define WALL_MLYR "wall"
#define FLOOR2_MLYR "floor2"
#define FLOOR_MLYR "floor"
#define WATER_MLYR "water"

//游戏记录的属性名命名法是属性名加_RCD
#define FIRSTSAVE_RCD "FisrtSave"
#define POSITIONX_RCD "PositionX"
#define POSITIONY_RCD "PositionY"
#define MAPPROCESS_RCD "MapProcess"
#define PROCESS_RCD "Process"

//游戏记录的初始值命名法是属性名加_INI
#define FIRSTSAVE_INI false
#define POSITIONX_INI 63
#define POSITIONY_INI 98
#define MAPPROCESS_INI MAP11
#define PROCESS_INI 0

//画面分辨率
#define JX_RESOLUWID 1136
#define JX_RESOLUHEI 640
#define MAP_RESOLUWID 672
#define MAP_RESOLUHEI 448


//事件的命名法是事件名加_EVT
//事件有两种触发方式：站触发和A触发
//事件在地图event层
//站触发看stand属性，A触发看atrg属性
//属性名的命名法是属性名加_ATT
#define STANDTRG_ATT "stand"
#define ATRG_ATT "atrg"

#define ID_ATT "id"



#define ROADSIGN_EVT "road sign"

#define TALKATIVEMAN_EVT "talkative man"
#define NSTR_ATT "nstr"

#define PORTAL_EVT "portal"
#define IDX_ATT "idx"
#define IDY_ATT "idy"

#define CHANGESCENE_EVT "change scene"
#define MAP11 19
#define MAP12 20



#define ANIMATE_EVT "animate"
#define PLACENAME_EVT "place name"

/*新建事件的步骤：
1.选定一个块儿，新建属性stand/atrg=事件名，id=参数。
2.在event层把这个块儿画在合适的位置。
//3.若为atrg事件，在wall层对应位置画块儿。
(若为place name事件，要在地图的information对象层加placenameID对象，属性名为id值，属性值为地名)
(若为portal事件,参数为idx和idy，代表传送目的地的坐标)
(若为talkative man事件，id是对应字母减'a'，属性nstr为共有几句话，属性0~9为语句值)
把信息存在块儿里的问题在于每个事件需要一个不一样的块儿。
但是即使不存字参数不一样，也还是得每个一个块儿。*/
/*另一个方案是把它放在对象层，在一开始加载的时候就按照id
初始化给人和路标对象。这样块儿里只存事件名，不存id。
这样块儿就变成了单纯的事件的代表。可以一色一事件。
然后归一为走动NPC的交互方法。这样倒是也可以。
甚至我们可以把人都加载进来，放一层，不显示，作为位置形象提示。
*/


#define INFORMATION_GRP "information"
#define	TURNINGMAN_OBJ "turningMan"
#define STANDINGMAN_OBJ "standingMan"
#define PLACENAMEID_OBJ "placenameID"

#define NNPC_ATT "nnpc"
#define NPCAX_ATT "npcax"

#define TURNINGMAN_ATTNUM 3
#define STANDINGMAN_ATTNUM 4
#define MARK 100
/*
新建NPC的步骤：
1.在NPC所在位置在wall层画障碍
2.在information层的对应man对象的属性中，新建属性 npc?x, npc?y，npc?z（，npc?{）并更改属性nnpc（用XML编辑）
3.如果有交互在NPC所在位置在event层画块儿，并新建属性atrg，id
*/

#define EGLVIEW 0.3
#define ZOOMSTROKELEN 200

typedef enum{kNone=1,kWall=17,kEvent=41}CollisionType;
typedef enum{Down=0,Left=1,Right=2,Up=3}HeroDirection;

#endif /* __APPMACROS_H__ */
