#include "HumanEntity.h"

//update:2014-9-26 16:59:11

void HumanEntity::setID(int id)
{
	this->id=id;
}






//英雄静止朝向
void HumanEntity::setFaceDirection(int dirc)
{
	sprite->setTextureRect(CCRectMake(0,48*dirc,32,48));
}

//创建四个方向的行走动画
CCAnimation* HumanEntity::createAnimationForDirection(int dirc)
{
	char addr[20]=MAN_IMG_PATH;
	IntToAddrForPNG(addr,MAN_PATH_LEN,id);
	CCTexture2D* HumanEntityTexture=CCTextureCache::sharedTextureCache()->addImage(addr);
	
	CCSpriteFrame* frame=new CCSpriteFrame;
	const int nFrames=4;float delay;
	CCArray* animFrames=CCArray::create();
	if(dirc>=0&&dirc<4)
	{
		for(int i=0;i<nFrames;i++)
		{
			frame=CCSpriteFrame::createWithTexture(HumanEntityTexture,cocos2d::CCRectMake(32*i,48*dirc,32,48));
			animFrames->addObject(frame);
		}
		frame=CCSpriteFrame::createWithTexture(HumanEntityTexture,cocos2d::CCRectMake(32*0,48*dirc,32,48));
		delay=0.1f;
	}
	else if(dirc==-1)
	{
		for(int i=0;i<nFrames+CCRANDOM_0_1()*6;i++)
		{
			frame=CCSpriteFrame::createWithTexture(HumanEntityTexture,cocos2d::CCRectMake(32*0,48*(int)(CCRANDOM_0_1()*4),32,48));
			animFrames->addObject(frame);
		}
		delay=1.5f+CCRANDOM_0_1()*1;
	}
	else if(dirc==5)
	{
		for(int i=0;i<nFrames;i++)
		{
			frame=CCSpriteFrame::createWithTexture(HumanEntityTexture,cocos2d::CCRectMake(32*0,48*i,32,48));
			animFrames->addObject(frame);
		}
		delay=0.1f;
	}
	CCAnimation* animation=new CCAnimation;

	animation->initWithSpriteFrames(animFrames,delay);
	return animation;
}

void HumanEntity::initSprite()
{
	char addr[20]=MAN_IMG_PATH;
	IntToAddrForPNG(addr,MAN_PATH_LEN,id);
	CCTexture2D* HumanEntityTexture=CCTextureCache::sharedTextureCache()->addImage(addr);
	
	//人物静止图像设置
	const int downStatic=0;
	sprite=CCSprite::createWithTexture(HumanEntityTexture);
	sprite->setTextureRect(CCRectMake(0,32*downStatic,32,48));//初始静止图片！
	bindSprite(sprite);
}






void HumanEntity::IntToAddrForPNG(char addr[],int len,int n)
{
	if(n>9)
		addr[len++]=n/10+'0';
	addr[len++]=n%10+'0';
	addr[len++]='.';
	addr[len++]='p';
	addr[len++]='n';
	addr[len++]='g';
	addr[len++]='\0';
}
void HumanEntity::initAnim(int dir)
{
}
void HumanEntity::goWalking(float dt)
{
}
void HumanEntity::respond(int dir)
{
}