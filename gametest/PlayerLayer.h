//
//  PlayerLayer.h
//  gametest
//
//  Created by MagicStudio on 13-3-29.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#ifndef gametest_PlayerLayer_h
#define gametest_PlayerLayer_h
#include "cocos2d.h"  
#include "SceneManager.h"
#include "BaseLayer.h"

using namespace cocos2d; //我实在太懒了  

class PlayerLayer:public BaseLayer  
{  
public:  
    virtual bool init(); //CCLayer的儿子们都有这玩意儿。别忘了virtual关键字  
    
    void back (CCObject* pSender);  
    void tryPopMoles(float dt);
    void popMole(CCSprite *mole);
    float convertFontSize(float fontSize);
    //(void) popMole:(CCSprite *)mole
    LAYER_NODE_FUNC(PlayerLayer);   
    //千万别忘了这个风情万种的宏  
    
    CCSprite *mole1;
    CCSprite *mole2;
    CCSprite *mole3;
    CCArray* moles;
    int tag1; //作为可打击标记
    int tag2;
    int tag3;
    int m_nSoundId;
    //CCAnimate *laugh;
    //CCAnimate *laugh1;
    int touchStep;
    void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent); 
    void setTappable(CCNode* sender);
    void unsetTappable(CCNode* sender);
    int getFlag(CCSprite *mole);
    void setFlag(CCSprite *mole,int flag);
    
    
protected:
    CCAnimation* pAnimation;
    CCAnimation *laughAnim;
    CCAnimation *hitAnim;
    CCLabelTTF *label;
    int score;
    int totalSpawns;
    bool gameOver;
    
    

    //CCArray* laughsFrames;
    //CCArray* hitsFrames;
    // = new CCMutableArray();//new CCMutableArray(4);
    
    
    //CCDictionary* plistDic = new ;
   
    
    //CCSprite *mole1 = CCSprite::spriteWithSpriteFrameName("mole_1.png");
};

#endif
