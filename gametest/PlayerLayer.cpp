//
//  PlayerLayer.cpp
//  gametest
//
//  Created by MagicStudio on 13-3-29.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "PlayerLayer.h"  
#include "CCAnimation.h"
#include"SimpleAudioEngine.h"
//#include "NSString.h"
//#include <UIKit/UIDevice.h>
using namespace CocosDenshion;

bool PlayerLayer::init()  
{  
    if (!BaseLayer::init())  
    {  
        return false;  
    }  
    tag1 = 0;
    tag2 = 0;
    tag3 = 0;
    const char *plist = "moleall.plist";
        
    //CCTexture2D::PVRImagesHavePremultipliedAlpha(true); 
    ///////////////////////////////临时注销
    //CCMenuItemFont* back=CCMenuItemFont::itemFromString("back",this,menu_selector(PlayerLayer::back));  
    //老问题 别忘记类名 还有这个只需要函数名就够了  
    //CCMenu* menu=CCMenu::menuWithItems(back,NULL);   
    //Items！ 单复数 要注意   
    
    //menu->setPosition(ccp(160,150));  
    //this->addChild(menu);  
    //menu 扔进去了 
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plist); //load resource
    CCSprite *dirt =CCSprite::spriteWithSpriteFrameName("bg_dirt.png"); 
    dirt->setScale(2);
    dirt->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.5));
    this->addChild(dirt,-6);//add sprite
    
    CCSprite *lower =CCSprite::spriteWithSpriteFrameName("grass_lower.png"); 
    lower->setAnchorPoint(ccp(0.5,1));
    
    lower->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.5));
    this->addChild(lower,0);
    
    CCSprite *upper =CCSprite::spriteWithSpriteFrameName("grass_upper.png"); 
    upper->setAnchorPoint(ccp(0.5,0));
    
    upper->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.5));
    this->addChild(upper,-5);
    
    
    moles = CCArray::array();
    moles->retain();
        
    mole1 = CCSprite::spriteWithSpriteFrameName("mole_1.png");
    mole1->setPosition(ccp(85,85));
    this->addChild(mole1,-1);
    mole1->setTag(1);
    moles->addObject(mole1);
    
    //CCSprite* bullet = (CCSprite*)moles->objectAtIndex(0);
    //this->addChild((CCSprite*)moles->objectAtIndex(0));
    
    mole2 = CCSprite::spriteWithSpriteFrameName("mole_1.png");
    mole2->setPosition(ccp(240,85));
    this->addChild(mole2,-1);
    mole2->setTag(2);
    moles->addObject(mole2);
    
    mole3 = CCSprite::spriteWithSpriteFrameName("mole_1.png");
    mole3->setPosition(ccp(395,85));
    this->addChild(mole3,-1);
    mole3->setTag(3);
    moles->addObject(mole3);
    
    CCMutableArray<CCSpriteFrame*>* laughsFrames = new CCMutableArray<CCSpriteFrame*>(6);//creat array for load image frame
    CCMutableArray<CCSpriteFrame*>* hitsFrames = new CCMutableArray<CCSpriteFrame*>(4);
    laughsFrames->retain();
    hitsFrames->retain();
    
    laughsFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()-> spriteFrameByName("mole_laugh1.png"));
    laughsFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()-> spriteFrameByName("mole_laugh2.png"));
    laughsFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()-> spriteFrameByName("mole_laugh3.png"));
    laughsFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()-> spriteFrameByName("mole_laugh2.png"));
    laughsFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()-> spriteFrameByName("mole_laugh3.png"));
    laughsFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()-> spriteFrameByName("mole_laugh1.png"));
    
    hitsFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()-> spriteFrameByName("mole_thump1.png"));
    hitsFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()-> spriteFrameByName("mole_thump2.png"));
    hitsFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()-> spriteFrameByName("mole_thump3.png"));
    hitsFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()-> spriteFrameByName("mole_thump4.png"));
    
    laughAnim = CCAnimation::animationWithFrames(laughsFrames, 0.1);
    hitAnim = CCAnimation::animationWithFrames(hitsFrames, 0.02);
    
    CCAnimationCache::sharedAnimationCache()->addAnimation(laughAnim ,"laughAnim");
    //the animation must be retain
    CCAnimationCache::sharedAnimationCache()->addAnimation(hitAnim ,"hitAnim");
    laughsFrames->release();
    hitsFrames->release();
    
    //std::string
    ///////////////////////////get file full path by cocos2d-x/////////////////////
    std::string fullPath = CCFileUtils::fullPathFromRelativePath("moleall.plist");
    //CCFileData *fileData = new CCFileData(fullPath.c_str(),"r");
    //unsigned char* data = fileData->getBuffer();
    ///////////////////////////////////////////////////////////////////////////////
    
    schedule(schedule_selector(PlayerLayer::tryPopMoles), 2);
    
    this->setIsTouchEnabled(true);
    
    float margin =10;
    label = CCLabelTTF::labelWithString("得分: 00", "Verdana", convertFontSize(14.0)); 
    
    //label = CCLabelTTF::labelWithString("Score: 0", "Verdana", this->convertFontSize(14.0)); 
    label->setAnchorPoint(ccp(1,0));
    label->setPosition(ccp(winSize.width - margin,margin));
    this->addChild(label,10);
    
    //label.anchorPoint = ccp(1, 0);
    //label.position = ccp(winSize.width - margin, margin);
    //[self addChild:label z:10];
    //isTouchEnabled(true);
    SimpleAudioEngine::sharedEngine()->preloadEffect("laugh.caf");
    SimpleAudioEngine::sharedEngine()->preloadEffect("ow.caf");
    SimpleAudioEngine::sharedEngine()->preloadEffect("bang.caf");
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(50.0);
    //SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("whack.cak");
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgmusic.mp3",true);
//    [[SimpleAudioEngine sharedEngine] preloadEffect:@"laugh.caf"];
//    [[SimpleAudioEngine sharedEngine] preloadEffect:@"ow.caf"];
//    [[SimpleAudioEngine sharedEngine] playBackgroundMusic:@"whack.caf" loop:YES];
    return true;  
    
}  
int PlayerLayer::getFlag(cocos2d::CCSprite *mole)
{
    if (mole->getTag() == 1)
    {
        return tag1;
    }
    else if (mole->getTag() == 2)
    {
        return tag2;
    }
    else
    {
        return tag3;
    }


}

void PlayerLayer::setFlag(CCSprite *mole, int flag)
{
    int temp;
    temp = 0;
    temp = mole->getTag();
    if (temp == 1)
    {
        tag1 = flag;
    }
    else if (temp == 2)
    {
        tag2 = flag;
    }
    else
    {
        tag3 = flag;
    }
}

float PlayerLayer::convertFontSize(float fontSize)
{
    
    float ret;
    ret = fontSize;
    
//    //#import <UIKit/UIDevice.h>
//    // Determine device kind
//    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) 
//    {
//        ret = fontSize * 2;
//        // iPad
//    } else 
//    {
//        ret = fontSize;
//        // iPhone
//    }
//    
//    // Determine retina display
//    if ([UIScreen instancesRespondToSelector:@selector(scale)] && UIScreen.mainScreen.scale > 1.0) {
//        // Retina
//    } else {
//        // Non-retina
//    }
    //CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,1, false);
    
    
    return ret;
}

void PlayerLayer::registerWithTouchDispatcher()
{
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,touchStep, false);
    
    //CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,kCCMenuTouchPriority,true);
    //CCDirector::sharedDirector()->gettouchdispatcher()->add
    //[[CCTouchDispatcher sharedDispatcher] addTargetedDelegate:self priority:kCCMenuTouchPriority swallowsTouches:NO];
    
}

bool PlayerLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCSprite *mole;
    
    CCPoint touchLocation = this->convertToNodeSpace(pTouch->locationInView(pTouch->view()));
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    
//    CCPoint touchLocation = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView(pTouch->view()));
//    touchLocation = this->convertToNodeSpace(touchLocation);
                                                              
    
//    mole = CCSprite::spriteWithSpriteFrameName("mole_thump4.png");
//    mole->setPosition(touchLocation);
//    this->addChild(mole);
//    mole->setTag(4);
    
    
    for (int i = 0; i < 3; i++) 
    {
        
        mole = (CCSprite*)moles->objectAtIndex(i);
    
        if (mole->getUserData() == (void*)0) continue;
        if(CCRect::CCRectContainsPoint(mole->boundingBox(), touchLocation) == true)
            {
                //[[SimpleAudioEngine sharedEngine] playEffect:@"ow.caf"];
                SimpleAudioEngine::sharedEngine()->playEffect("ow.caf");
                mole->setUserData((void*)0);
                //this->setFlag(mole, 0);
                score+=10;
                mole->stopAllActions();
                CCAnimate *hit = CCAnimate::actionWithAnimation(hitAnim,false);
                CCMoveBy *moveDown = CCMoveBy::actionWithDuration(0.2, ccp(0,-mole->getContentSize().height));
                CCEaseInOut * easeMoveDown = CCEaseInOut::actionWithAction(moveDown,3.0);
                mole->runAction(CCSequence::actions(hit,easeMoveDown,NULL));
                
                char* str = new char;
                
                sprintf(str, "得分: %d", score);
                label->setString(str);
                //int sco;
                //sco = score%50;
                if (score%50 == 0)
                {
                    SimpleAudioEngine::sharedEngine()->playEffect("bang.caf");
                }
                
//                [mole stopAllActions];
//                CCAnimate *hit = [CCAnimate actionWithAnimation:hitAnim restoreOriginalFrame:NO];
//                CCMoveBy *moveDown = [CCMoveBy actionWithDuration:0.2 position:ccp(0, -mole.contentSize.height)];
//                CCEaseInOut *easeMoveDown = [CCEaseInOut actionWithAction:moveDown rate:3.0];
//                [mole runAction:[CCSequence actions:hit, easeMoveDown, nil]];
            }
        //mole->release();
                
    }
    //CC_SAFE_DELETE(mole);
    
    
    return true;
    
}
//    CCObject* object;
//    
//    CCARRAY_FOREACH(moles,object);
//    {
//        CCSprite *moletemp = (CCSprite*)object;
//        if(moletemp->getUserData() == (void*)1) 
//        {
//            if(CCRect::CCRectContainsPoint(moletemp->boundingBox(), touchLocation) == true)
//            {
//                moletemp->setUserData((void*)0);
//            }
//            
//            //if (CGRectContainsPoint(mole.boundingBox, touchLocation))
//        }
//        
//        //CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()-> spriteFrameByName((char*)object);
//        //animFrames->addObject(frame);
//
//    //CGPoint touchLocation = [self convertTouchToNodeSpace:touch];
//    }
    //return true;
    //for (CCSprite *mole in moles) {
        //if (mole.userData == FALSE) continue;


void PlayerLayer::setTappable(CCNode* sender) 
{
    
    CCSprite *mole = (CCSprite*)sender;
    mole->setUserData((void*)1);
    m_nSoundId = SimpleAudioEngine::sharedEngine()->playEffect("laugh.caf");
    
   // [[SimpleAudioEngine sharedEngine] playEffect:@"laugh.caf"];
}
void PlayerLayer::unsetTappable(CCNode *sender)
{
    CCSprite *mole = (CCSprite*)sender;
    mole->setUserData((void *)0);
    
}

void PlayerLayer::back(cocos2d::CCObject *pSender)  
{  
    SceneManager::goMenu();  
    //back就是回主菜单，这里调用了人见人爱 花见花开的静态函数 goMenu  
}  

void PlayerLayer::tryPopMoles(float dt)
{
    //for (int i = 0; i < numSprites; i++) 
    //(CCSprite*)moles->objectAtIndex(random(3));
    popMole((CCSprite*)moles->objectAtIndex(arc4random()%3));//random pop in 3 sprites
}

void PlayerLayer::popMole(CCSprite *mole)
{
    if(gameOver) return;
    if (totalSpawns >= 50)
    {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        CCLabelTTF *golabel = CCLabelTTF::labelWithString("第一关结束!", "Verdana", 48.0);
        //CCLabelTTF *levelScore = CCLabelTTF::labelWithString();
        golabel->setPosition(ccp(winSize.width/2,winSize.height/2));
        golabel->setScale(0.1);
        this->addChild(golabel);
        golabel->runAction(CCScaleTo::actionWithDuration(0.5, 1.0));
        gameOver = true;
        return;
        
    }
//    if (totalSpawns >=50) 
//    {
//        
//        CGSize winSize = [CCDirector sharedDirector].winSize;
//        
//        CCLabelTTF *goLabel = [CCLabelTTF labelWithString:@"Level Complete!" fontName:@"Verdana" fontSize:[self convertFontSize:48.0]];
//        goLabel.position = ccp(winSize.width/2, winSize.height/2);
//        goLabel.scale =0.1;
//        [self addChild:goLabel z:10]; 
//        [goLabel runAction:[CCScaleTo actionWithDuration:0.5 scale:1.0]];
//        
//        gameOver =true;
//        return;
//        
//    }

    if (totalSpawns >50) return;
    totalSpawns++;
    mole->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("mole_1.png"));
    CCMoveBy *moveUp = CCMoveBy::actionWithDuration(0.2,ccp(0,mole->getContentSize().height)); // 1
    
    CCCallFunc *setTappable = CCCallFuncN::actionWithTarget(this, callfuncN_selector(PlayerLayer::setTappable)); 
    CCEaseInOut *easeMoveUp = CCEaseInOut::actionWithAction(moveUp,3.0);
    CCCallFunc *unsetTappable = CCCallFuncN::actionWithTarget(this, callfuncN_selector(PlayerLayer::unsetTappable));
    CCAction *easeMoveDown = easeMoveUp->reverse();
    CCAnimate *laugh = CCAnimate::actionWithAnimation(laughAnim, true);
    
    
    mole->runAction(CCSequence::actions(easeMoveUp,setTappable,laugh,unsetTappable,easeMoveDown,NULL));//act step by step
    	
}

 CCAnimation *animationFromPlist(CCArray* animImages,float delay)
{
    CCObject* object;
    
    CCMutableArray<CCSpriteFrame*>* animFrames = new CCMutableArray<CCSpriteFrame*>();
        CCARRAY_FOREACH(animImages,object);
    {
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()-> spriteFrameByName((char*)object);
        animFrames->addObject(frame);
    }
        CCAnimation* animation = CCAnimation::animationWithFrames(animFrames,delay);
    return animation;
    
}

