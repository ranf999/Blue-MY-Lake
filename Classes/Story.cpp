#include "Story.h"
#include "AppMacros.h"

USING_NS_CC;
//update: 2014-9-30 13:29:52

CCScene* StoryWorld::scene() {
    CCScene *scene = CCScene::create();
    
    StoryWorld *layer = StoryWorld::create();
	layer->setTag(1);

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool StoryWorld::init() {
    
    if ( !CCLayer::init() )
    {
        return false;
    }

	//theName = reader.PlayerNames();
    char theName[10][11]={"","穆婧:", "子轩:", "少杰:", "建国", "路人A:", "路人B:", "路人C:", "老爷爷:", "江姐:"};
    
    char play[20] = SCRIPT_PATH;
    //CCUserDefault::sharedUserDefault()->setIntegerForKey("Process", '7');@
    //CCUserDefault::sharedUserDefault()->flush();@
    current = CCUserDefault::sharedUserDefault()->getIntegerForKey("Process")+'0';//stay
	//if(current>'9'||current<'0')current='0';
	//current = saver.getProcess();
//	current='9';//delete
    play[SCRIPT_PATH_LEN] = current;
    //CCLog(play);
    //cocos2d::CCString fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(play);
    reader.ReadFileWithFullPath(CCFileUtils::sharedFileUtils()->fullPathForFilename(play));
    
    
    setTouchEnabled(true);
    
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        CLOSEN_IMG_PATH,
                                        CLOSES_IMG_PATH,
                                        this,
                                        menu_selector(StoryWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    addChild(pMenu, 2);
    

    
    char bg_name[30] = BGNAME_IMG_PATH;
    bg_name[BGNAME_PATH_LEN] = current;
    CCSprite* pBackground = CCSprite::create(bg_name);
    pBackground->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    pBackground->setScale(1);
    pBackground->setTag(108);
    addChild(pBackground, 0);
    
    CCSprite* dialogBox = CCSprite::create(DUIHUAKUANG_IMG_PATH);
    dialogBox->setPosition(ccp(visibleSize.width/2, dialogBox->getContentSize().height/2));
    dialogBox->setOpacity(220);
    addChild(dialogBox,1);
    
    CCLabelTTF* pName = CCLabelTTF::create(theName[0], "Heiti SC", 40);
    pName->setTag(101);
    pName->setPosition(ccp(pName->getContentSize().width/2, dialogBox->getContentSize().height - 2 * pName->getContentSize().height));
    pName->setAnchorPoint(CCPointZero);
    addChild(pName, 1);
    
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Click to Start", "Heiti SC", 40);
    pLabel->setTag(100);
    pLabel->setPosition(ccp(40, origin.y + dialogBox->getContentSize().height - 3.4 * pLabel->getContentSize().height));
    pLabel->setAnchorPoint(CCPointZero);
    pLabel->setDimensions(CCSizeMake(1100, 0));
//    pLabel->setFontFillColor(ccc3(255, 0, 0));
    pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
    addChild(pLabel, 1);
    
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("vdrawing.plist");
    CCSpriteBatchNode *spriteBatch=CCSpriteBatchNode::create("vdrawing.png");
    spriteBatch->setTag(102);
    addChild(spriteBatch, 0);
    spriteBatch->setPosition(CCPointZero);

    CCSprite *leftSprite=CCSprite::createWithSpriteFrameName("me_1.png");
    leftSprite->setScale(0.8);
    leftSprite->setPosition(ccp(leftSprite->getContentSize().width*0.8, leftSprite->getContentSize().height/2 *0.8));
    leftSprite->setTag(1);
    leftSprite->setOpacity(0);
    spriteBatch->addChild(leftSprite, 0);
    
    CCSprite *rightSprite=CCSprite::createWithSpriteFrameName("blank.png");
    //rightSprite->setScale(0.8);
    rightSprite->setPosition(ccp(800, 130));
    rightSprite->setTag(2);
    rightSprite->setOpacity(0);
    spriteBatch->addChild(rightSprite, 0);
    
    avgGame();
    return true;
}

void StoryWorld::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    avgGame();
}

void StoryWorld::avgGame(void) {
    CCLabelTTF* myDialog = (CCLabelTTF *)getChildByTag(100);
    CCLabelTTF* myName = (CCLabelTTF *)getChildByTag(101);
    CCSpriteBatchNode *spriteBatch = (CCSpriteBatchNode *)getChildByTag(102);
    CCSprite *myLeftSprite = (CCSprite *)spriteBatch->getChildByTag(1);
    CCSprite *myRightSprite = (CCSprite *)spriteBatch->getChildByTag(2);
    
    strcpy(dialog, reader.GetNextDialog().c_str());

	char theName[10][11]={"","穆婧1:", "子轩:", "少杰:", "建国", "路人A:", "路人B:", "路人C:", "老爷爷:", "江姐:"};

	myName->setString(theName[dialog[0]-48]);
    //任务立绘切换
    switch (dialog[0]) {
        case '0': {   //无人
            char b[10]="me_ .png";
            b[3] = dialog[1]+1;
            myLeftSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(b));
        }
            break;
            
        case '1': {   //ME
            char b[10]="me_ .png";
            b[3] = dialog[1]+1;
            myLeftSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(b));
        }
            break;
        case '2': {   //子轩
            char b[10]="zx_ .png";
            b[3] = dialog[1]+1;
            myRightSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(b));
        }
            break;
        case '3': {   //少杰
            char b[10]="sj_ .png";
            b[3] = dialog[1];
            myRightSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(b));
        }
            break;
        case '4': {   //建国
            char b[10]="jg_ .png";
            b[3] = dialog[1];
            myRightSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(b));
        }
            break;
        case '5': {  
            char b[10]="la_ .png";
            b[3] = dialog[1];
            myRightSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(b));
        }
            break;
        case '6': { 
            char b[10]="lb_ .png";
            b[3] = dialog[1];
            myRightSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(b));
        }
            break;
        case '7': {
            char b[10]="lc_ .png";
            b[3] = dialog[1];
            myRightSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(b));
        }
            break;
        case '8': { 
            char b[10]="yy_ .png";
            b[3] = dialog[1];
            myRightSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(b));
        }
            break;
        case '9': { 
            char b[10]="jj_ .png";
            b[3] = dialog[1];
            myRightSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(b));
        }
            break;
            
        default:
            break;
    }

    switch (dialog[2]) {
            // 选择走向
        case '1': {
            //开始选择走向
            //停止触摸
            setTouchEnabled(false);
            CCSprite *back = CCSprite::create("Landscape.png");
            back->setPosition(ccp(CCDirector::sharedDirector()->getVisibleSize().width/2, CCDirector::sharedDirector()->getVisibleSize().height/2));
            back->setOpacity(150);
            back->setTag(3);
            addChild(back, 3);
            switch (current) {
                case '3': {
                    CCLabelTTF *Label1 = CCLabelTTF::create("Yes", "Heiti SC", 40);
                    CCLabelTTF *Label2 = CCLabelTTF::create("No", "Heiti SC", 40);
                    CCMenuItemLabel *firstChoice = CCMenuItemLabel::create(Label1, this, menu_selector(StoryWorld::makeAChoice));
                    CCMenuItemLabel *secondChoice = CCMenuItemLabel::create(Label2, this, menu_selector(StoryWorld::makeAChoice));
                    firstChoice->setTag(fChoice);
                    secondChoice->setTag(sChoice);
                    firstChoice->setPosition(ccp(CCDirector::sharedDirector()->getVisibleSize().width/2, CCDirector::sharedDirector()->getVisibleSize().height/5 * 4.1));
                    secondChoice->setPosition(ccp(CCDirector::sharedDirector()->getVisibleSize().width/2, CCDirector::sharedDirector()->getVisibleSize().height/5 * 2.9));
                    CCMenu *menu = CCMenu::create(firstChoice, secondChoice, NULL);
                    menu->setPosition(CCPointZero);
                    menu->setTag(2);
                    addChild(menu, 3);
                    return;
                }
                    break;
                case '9': {
                    //创建CCMenu
                    CCLabelTTF *Label1 = CCLabelTTF::create("子轩", "Heiti SC", 40);
                    CCLabelTTF *Label2 = CCLabelTTF::create("少杰", "Heiti SC", 40);
                    CCLabelTTF *Label3 = CCLabelTTF::create("建国", "Heiti SC", 40);
                    CCMenuItemLabel *firstChoice = CCMenuItemLabel::create(Label1, this, menu_selector(StoryWorld::makeAChoice));
                    CCMenuItemLabel *secondChoice = CCMenuItemLabel::create(Label2, this, menu_selector(StoryWorld::makeAChoice));
                    CCMenuItemLabel *thirdChoice = CCMenuItemLabel::create(Label3, this, menu_selector(StoryWorld::makeAChoice));
                    
                    firstChoice->setTag(fChoice);
                    secondChoice->setTag(sChoice);
                    thirdChoice->setTag(tChoice);
                    
                    firstChoice->setPosition(ccp(CCDirector::sharedDirector()->getVisibleSize().width/2, CCDirector::sharedDirector()->getVisibleSize().height/5 * 4.1));
                    secondChoice->setPosition(ccp(CCDirector::sharedDirector()->getVisibleSize().width/2, CCDirector::sharedDirector()->getVisibleSize().height/5 * 2.9));
                    thirdChoice->setPosition(ccp(CCDirector::sharedDirector()->getVisibleSize().width/2, CCDirector::sharedDirector()->getVisibleSize().height/5 * 1.8));
                    
                    CCMenu *menu = CCMenu::create(firstChoice, secondChoice, thirdChoice, NULL);
                    menu->setPosition(CCPointZero);
                    menu->setTag(2);
                    addChild(menu, 3);
                    return;
                }
                    break;
                    
                default:
                    break;
            }
        }
            break;
        case '2': {
            CCScene *combatScene = Combat::scene();
            CCDirector::sharedDirector()->pushScene(combatScene);
        }
            break;
        case '3': {
            if (myLeftSprite->getOpacity() == 0)
                myLeftSprite->setOpacity(255);
            else
                myLeftSprite->runAction(CCFadeOut::create(1));
        }
            break;
        case '4': {
            if (myRightSprite->getOpacity() == 0)
                myRightSprite->setOpacity(255);
            else
                myRightSprite->runAction(CCFadeOut::create(1));
        }
            break;
        case '5': {
            if (myRightSprite->getOpacity()==0 && myLeftSprite->getOpacity()==0) {
                myLeftSprite->setOpacity(255);
                myRightSprite->setOpacity(255);
            } else if (myRightSprite->getOpacity()!=0 && myLeftSprite->getOpacity()!=0) {
                myLeftSprite->runAction(CCFadeOut::create(1));
                myRightSprite->runAction(CCFadeOut::create(1));
            }
        }
            break;
        default:
            break;
    }
    
    // 剧本切换及完结及特效
    switch (dialog[3]) {
        case '1':{    // 保存进度
            current+=1;
//            saver.saveProcess(current);
            CCUserDefault::sharedUserDefault()->setIntegerForKey("Process", current-'0');
            CCUserDefault::sharedUserDefault()->flush();
            
//            char play[8] = "Script ";
//            play[6] = current;
            //cocos2d::CCString fullPath = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(play);
			CCEGLView::sharedOpenGLView()->setDesignResolutionSize(672, 448, kResolutionExactFit);
//            reader.ChangeFile(CCFileUtils::sharedFileUtils()->fullPathForFilename(play));
            CCDirector::sharedDirector()->popScene();
            // TODO: POP OUT
        }
            break;
        case '2':{    // wanjie
            //CCLog("jieshule");
           //wanjie animation
			CCSprite* staff_bg = CCSprite::create("staff_bg.png");
			staff_bg->setPosition(ccp(CCDirector::sharedDirector()->getVisibleSize().width/2 + CCDirector::sharedDirector()->getVisibleOrigin().x, CCDirector::sharedDirector()->getVisibleSize().height/2 + CCDirector::sharedDirector()->getVisibleOrigin().y));
			addChild(staff_bg, 4);

			CCSprite* staff = CCSprite::create("staff.png");
			staff->setPosition(ccp(CCDirector::sharedDirector()->getVisibleSize().width/2, -CCDirector::sharedDirector()->getVisibleSize().height/2));
			addChild(staff, 5);

			CCActionInterval * moveTo = CCMoveTo::create(20,ccp(CCDirector::sharedDirector()->getVisibleSize().width/2, CCDirector::sharedDirector()->getVisibleSize().height*3/2));
			CCFiniteTimeAction*  sequneceAction = CCSequence::create(
				moveTo,
				CCCallFunc::create(this, callfunc_selector(StoryWorld::over)),
				NULL);

			staff->runAction(sequneceAction);
            // return to zhujiemians
			
        }
            break;
        case '3':{
            //this->runAction(CCSequence::create(CCFadeOut::create(1),CCFadeIn::create(1),NULL));
            //CCLog("fade");
            /*CCArray *children = getChildren();
             CCObject *pobj;
             CCARRAY_FOREACH(children, pobj) {
             ((CCNode *)pobj)->runAction(CCFadeOut::create(1));
             }*/
            CCSprite *black = CCSprite::create("black.png");
            black->setPosition(ccp(CCDirector::sharedDirector()->getVisibleSize().width/2, CCDirector::sharedDirector()->getVisibleSize().height/2));
            black->setOpacity(0);
            addChild(black, 4);
            black->runAction(CCSequence::create(CCFadeIn::create(0.5), CCFadeOut::create(0.5), NULL));
            
        }
            break;
        default:
            break;
    }
    
    //音效
    switch (dialog[4]) {
        case '1': 
        case '2': 
        case '3':
        case '4':
        case '5':
        case '6':{
            char musicName[7] = " .mp3";
            musicName[0] = dialog[4];
            if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
                CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
            }
            CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(CCFileUtils::sharedFileUtils()->fullPathForFilename(musicName).c_str());
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(CCFileUtils::sharedFileUtils()->fullPathForFilename(musicName).c_str(), true);
        }
            break;
        case '7': {
            CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
        }
            break;
        case '8':
        case '9':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'G':{
            char effectName[7] = " .wav";
            effectName[0] = dialog[4];
            
            CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename(effectName).c_str());
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename(effectName).c_str());
        }
            break;
        case 'E': 
        case 'F': 
        case 'H':{
            char effectName[7] = " .mp3";
            effectName[0] = dialog[4];
            
            CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename(effectName).c_str());
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename(effectName).c_str());
        }
            break;

        default:
            break;
    }
    
    // 背景
    char all_bg[8][4] = {"010", "030", "204", "701", "717", "725", "732"};
    char bg_num[4]="000";
    int curLine = reader.getCurLine();
    sprintf(bg_num, "%c%02d", current, curLine);
    if (curLine == 0) {
        CCSprite *Background = (CCSprite *)getChildByTag(108);
        char bg_name[30]=BGNAME_IMG_PATH;
        bg_name[BGNAME_PATH_LEN] = current;
        Background->setTexture(CCTextureCache::sharedTextureCache()->addImage(bg_name));
    } else {
        for (int i =0; i<8; i++) {
            if (strcmp(all_bg[i], bg_num)==0) {
                CCSprite *Background = (CCSprite *)getChildByTag(108);
                char bg_name[30]="img/story/bg_000.jpg";
                sprintf(bg_name, "img/story/bg_%s.jpg", bg_num);
                Background->setTexture(CCTextureCache::sharedTextureCache()->addImage(bg_name));
            }
        }
    }
	////CCLog(dialog+5);
    myDialog->setString(dialog+5);
}

void StoryWorld::makeAChoice(CCObject *sender) {
    int choice = ((CCNode *)sender)->getTag();
    if (current == '3') {
        switch (choice) {
            case fChoice: {
                // 显示宣传单一
                cout << "xuanchuan " << endl;
                removeChildByTag(2);
                removeChildByTag(3);
                CCSprite *blackBG = CCSprite::create("black.png");
                blackBG->setPosition(ccp(CCDirector::sharedDirector()->getVisibleSize().width/2, CCDirector::sharedDirector()->getVisibleSize().height/2));
                blackBG->setScale(1);
                blackBG->setTag(21);
                addChild(blackBG, 2);
                // TODO
                CCLabelTTF *xuanchuan = CCLabelTTF::create();//"        四川大学的历史源头最早可以追溯到康熙年间的锦江书院。锦江书院在清代雍正十一年(1733年)，被御定为全国22所最著名的省级书院之一，时人曾誉以“石室云霞思古梦，锦江风雨读书灯”。\n        锦江书院最有名的“功名富贵”楹联是：有补于天地曰功，有益于世教曰名，有精神之谓富，有廉耻之谓贵；不涉鄙陋斯为文，不入暧昧斯为章，溯乎始之谓道，信乎己之谓德。\n         锦江书院聘请了许多名流学者主讲，其中最有名的是担任山长近20年的四川丹棱人彭端淑（约1699一约1779年）。他与李调元、张问陶并称清代四川三才子，《为学一首示子侄》收入今天的中小学教材。\n        锦江书院学生刘光第（1859-1898），四川富顺人，1879-1882年在锦江书院就读，光绪九年（1883）进士，是戊戌变法殉难的“六君子”之一。", "Heiti SC", 40);
                xuanchuan->setPosition(ccp(0, 40));
                xuanchuan->setHorizontalAlignment(kCCTextAlignmentLeft);
                xuanchuan->setAnchorPoint(CCPointZero);
                xuanchuan->setDimensions(CCSizeMake(1100, 0));
                xuanchuan->setTag(22);
                addChild(xuanchuan, 3);
                
                // 关闭按钮
                CCMenuItemImage *start = CCMenuItemImage::create("leafletsclose.png",
                                                                 "leafletsclose.png",
                                                                 this,
                                                                 menu_selector(StoryWorld::menuLeafletsCloseCallback));
                
                start->setPosition(ccp(CCDirector::sharedDirector()->getVisibleSize().width-40, CCDirector::sharedDirector()->getVisibleSize().height-40));
                
                //菜单
                CCMenu* pMenu = CCMenu::create(start, NULL);
                pMenu->setPosition(CCPointZero);
                pMenu->setTag(23);
                addChild(pMenu, 4);
                
                
            }
                return;
            case sChoice:
			default:{
				current+=1;
				CCUserDefault::sharedUserDefault()->setIntegerForKey("Process", current);
				CCUserDefault::sharedUserDefault()->flush();

				CCEGLView::sharedOpenGLView()->setDesignResolutionSize(480, 320, kResolutionExactFit);
//				reader.ChangeFile(CCFileUtils::sharedFileUtils()->fullPathForFilename(play));
				CCDirector::sharedDirector()->popScene();
//                removeChildByTag(2);
//                removeChildByTag(3);
//                setTouchEnabled(true);
//                reader.ChangeFile(CCFileUtils::sharedFileUtils()->fullPathForFilename("Script4"));
//                avgGame();
            }
                return;
//            default:
//                break;
        }
    }
    char fileName[8] = "Fin ";
    
    switch (choice) {
        case fChoice:
            fileName[3]='1';
            break;
        case sChoice:
            fileName[3]='2';
            break;
        case tChoice:
            fileName[3]='3';
            break;
            
        default:
            break;
    }
    reader.ChangeFile(cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName));
    
    removeChildByTag(2);
    removeChildByTag(3);
    setTouchEnabled(true);
    
    avgGame();
    //CCLog("choice %d is selected!", choice);
}

void StoryWorld::over() {
	CCScene *welcome = Welcome::scene();
	CCTransitionCrossFade *backToWelcome = CCTransitionCrossFade::create(0.7, welcome);
	CCDirector::sharedDirector()->replaceScene(backToWelcome);
}

void StoryWorld::menuLeafletsCloseCallback(CCObject* sender) {
    removeChildByTag(21);
    removeChildByTag(22);
    removeChildByTag(23);
    setTouchEnabled(true);
    current+=1;
//    saver.saveProcess(current);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("Process", current);
    CCUserDefault::sharedUserDefault()->flush();
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(480, 320, kResolutionExactFit);
//	reader.ChangeFile(CCFileUtils::sharedFileUtils()->fullPathForFilename(play));
	CCDirector::sharedDirector()->popScene();
//    reader.ChangeFile(CCFileUtils::sharedFileUtils()->fullPathForFilename("Script4"));
//    CCSprite *Background = (CCSprite *)getChildByTag(108);
//    Background->setTexture(CCTextureCache::sharedTextureCache()->addImage("bg_400.jpg"));
}

void StoryWorld::menuCloseCallback(CCObject* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}