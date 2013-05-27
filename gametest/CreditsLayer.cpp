//
//  CreditsLayer.cpp
//  gametest
//
//  Created by MagicStudio on 13-3-29.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "cocos2d.h"  
#include "CreditsLayer.h"  


bool CreditsLayer::init()  
{  
    if (!BaseLayer::init())  
    {  
        return false;  
    }  
    
    CCMenuItemFont* back=CCMenuItemFont::itemFromString("back",this,menu_selector(CreditsLayer::back));  
    
    CCMenu* menu=CCMenu::menuWithItems(back,NULL);  
    //别忘了NULL  
    
    menu->setPosition(ccp(160,150));  
    this->addChild(menu);  
    
    return true;  
}  


void CreditsLayer::back(cocos2d::CCObject *pSender)  
{  
    SceneManager::goMenu();  
}