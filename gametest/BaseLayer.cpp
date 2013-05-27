//
//  BaseLayer.cpp
//  gametest
//
//  Created by MagicStudio on 13-4-1.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "BaseLayer.h"  
#include "cocos2d.h"  

bool BaseLayer::init()  
{  
    if (!CCLayer::init())  
    {  
        return false;  
    }  
    this->setIsTouchEnabled(true);  
    //启用触摸  
    
    CCSprite *bg=CCSprite::spriteWithFile("background.png");  
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    bg->setPosition(ccp(size.width/2,size.height/2));  
    
    this->addChild(bg,-10);  
    
    return true;  
    
}  