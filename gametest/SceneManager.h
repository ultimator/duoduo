//
//  SceneManager.h
//  gametest
//
//  Created by MagicStudio on 13-3-28.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#ifndef gametest_SceneManager_h
#define gametest_SceneManager_h

#include "cocos2d.h"  
#include "MenuLayer.h"  
using namespace cocos2d;  

class SceneManager:public CCObject  
{  
    public:
    static void goMenu();  
    static void go(CCLayer* layer);  
    static CCScene* wrap(CCLayer* layer);  
    static void goPlay();  
    //去PlayLayer那边去  
    static void goCredits();  
    //去CreditsLayer那边去 
    static int nIdx;  
    //声明静态旗标  
    static CCTransitionScene* createTransition(ccTime t,CCScene* s);  
    //用来返回 CCTransitionScene 对象，具体看.cpp中的实现  
};

#endif

	