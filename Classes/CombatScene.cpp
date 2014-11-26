#include "AppMacros.h"//$
#include "CombatScene.h"
USING_NS_CC;

//update:2014-10-4 19:37:38

CCScene* Combat::scene() {
	CCScene *scene = CCScene::create();
	Combat *layer = Combat::create();
	scene->addChild(layer);
	// return the scene
	return scene;
}

bool Combat::init() {

	if (!CCLayer::init()) {
		return false;
	}

	//不要问我从哪里来
	cc_timeval psv;
	CCTime::gettimeofdayCocos2d(&psv,NULL);
	unsigned long int rand_seed = psv.tv_sec*1000+psv.tv_usec/1000;
	srand(rand_seed);

	initSprite();
	initLabel();
	show();
	return true;
}


void Combat::initSprite(){
	background = CCSprite::create(COMBAT_IMG_PATH);//$
	background->setPosition(ccp(background->getContentSize().width/2, background->getContentSize().height/2));
	background->setTag(BACKGROUND);
	addChild(background, 0);

	player = Player1::create();
	player->setPosition(ccp(-(player->getChildByTag(IMGSP)->getContentSize().width+150), 
	player->getChildByTag(IMGSP)->getContentSize().height));
	addChild(player);

	enemy = Enemy::create();
	enemy->setPosition(ccp(CCDirector::sharedDirector()->getVisibleSize().width - enemy->getChildByTag(IMGSP)->getContentSize().width-150,
		CCDirector::sharedDirector()->getVisibleSize().height -enemy->getChildByTag(IMGSP)->getContentSize().height));
	addChild(enemy);	

	CombatCtrl* menu = CombatCtrl::create();
	menu->setPointers(player,enemy,background);
	addChild(menu);
}

//@label显示
void Combat::initLabel(){
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(Combat::ScaleBlood),"gethurt",NULL);
	
	//显示自己与敌人的血条图片
	pBlood = CCSprite::create(BLOOD_IMG_PATH);//$
	pBlood->setPosition(ccp(1047, 250));//138
	pBlood->setAnchorPoint(ccp(1, 1));pBlood->setTag(12);
	pBlood->setScaleX(1);
	addChild(pBlood,1);
	eBlood = CCSprite::create(BLOOD_IMG_PATH);//$
	eBlood->setPosition(ccp(478, 558));
	eBlood->setAnchorPoint(ccp(1, 1));eBlood->setTag(22);
	eBlood->setScale(1);
	addChild(eBlood,1);

	//显示双方血量值
	CCPoint pBloodPos = pBlood->getPosition();CCPoint eBloodPos = eBlood->getPosition();
	char playerHp[10];char enemyHp[10];
	sprintf(playerHp, "%d/%d",player->Hp,player->Hp);
	pBloodLabel = CCLabelTTF::create("" ,"Heiti SC", 30);pBloodLabel->setString(playerHp);pBloodLabel->setPosition(ccp(pBloodPos.x-10,pBloodPos.y-22));pBloodLabel->setAnchorPoint(ccp(1, 0.5));pBloodLabel->setTag(13);
	addChild(pBloodLabel,2);
	sprintf(enemyHp, "%d/%d",enemy->Hp,enemy->Hp);
	eBloodLabel = CCLabelTTF::create("", "Heiti SC", 30);eBloodLabel->setString(enemyHp);eBloodLabel->setPosition(ccp(eBloodPos.x-250,eBloodPos.y-22));eBloodLabel->setAnchorPoint(ccp(1, 0.5));eBloodLabel->setTag(23);
	addChild(eBloodLabel,2);

	//显示双方等级
	char level[10];
	sprintf(level,"Lv.%d",player->level);
	CCLabelTTF *plevel = CCLabelTTF::create("","Heiti SC",30);plevel->setFontFillColor(ccBLACK);plevel->setString(level);plevel->setPosition(ccp(pBloodPos.x-13,pBloodPos.y+32));plevel->setAnchorPoint(ccp(1,1));plevel->setTag(33);
	addChild(plevel,2);
	sprintf(level,"Lv.%d",enemy->level);
	CCLabelTTF *elevel = CCLabelTTF::create("","Heiti SC",30);plevel->setFontFillColor(ccBLACK);elevel->setString(level);elevel->setPosition(ccp(eBloodPos.x-320,eBloodPos.y+32));elevel->setAnchorPoint(ccp(1,1));elevel->setTag(33);
	addChild(elevel,2);

	//显示名字
	const char* pname;
	const char* ename;
	CCLabelTTF *pName = CCLabelTTF::create("","Heiti SC",30);
	pname = player->name.getCString();
	pName->setString(pname);
	pName->setFontFillColor(ccBLACK);pName->setPosition(ccp(pBloodPos.x-300,pBloodPos.y+32));pName->setAnchorPoint(ccp(1,1));pName->setTag(33);
	addChild(pName,2);
	CCLabelTTF *eName = CCLabelTTF::create("","Heiti SC",30);
	ename = enemy->name.getCString();
	eName->setString(ename);
	eName->setFontFillColor(ccBLACK);eName->setString(enemy->name.getCString());eName->setPosition(ccp(eBloodPos.x-10,eBloodPos.y+35));eName->setAnchorPoint(ccp(1,1));eName->setTag(33);
	addChild(eName,2);

	//经验值

}

void Combat::show(){

	CCActionInterval* moveTo1 = CCMoveTo::create(1.5,ccp((player->getChildByTag(IMGSP)->getContentSize().width+150), 
		player->getChildByTag(IMGSP)->getContentSize().height));
	player->runAction(moveTo1);

	CCAction* enemyUp = Animation::getAction(SWAY,enemy->getChildByTag(IMGSP)->getContentSize());
	CCSequence* seq = CCSequence::create(CCDelayTime::create(1.5),enemyUp,NULL);
	enemy->runAction(seq);
}






void Combat::ScaleBlood(CCObject* character){
	Character* p = (Character*)character;

	int ht = p->Hp-p->remainHp;

	float st =  (float)p->remainHp/(float)p->Hp;
	
	CCScaleTo *Scale =CCScaleTo::create(0.5,st,1.0f);


	char blood[10];
	if (p->ishero)
	{
		Player1* player0=(Player1*)p;
		sprintf(blood, "%d/%d", player0->remainHp,player0->Hp);
		pBloodLabel->setString(blood);
		pBlood->runAction(Scale);
	}
	else
	{
		Enemy* enemy0=(Enemy*) p;
		sprintf(blood, "%d/%d", enemy0->remainHp,enemy0->Hp);
		eBloodLabel->setString(blood);
		eBlood->runAction(Scale);
	}
}
