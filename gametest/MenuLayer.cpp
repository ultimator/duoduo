//
//  MenuLayer.cpp
//  gametest
//
//  Created by MagicStudio on 13-3-28.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "cocos2d.h"  
#include "MenuLayer.h"  
#include "SceneManager.h"  

using namespace cocos2d;  

bool MenuLayer::init()  
{  
    if (!BaseLayer::init())  
    {  
        return false;  
    }  
    //BaseLayer blayer = CCLayer::
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCLabelTTF* titleLeft=CCLabelTTF::labelWithString("多多打地鼠", "Marker Felt", 48); //创建Label  
    
    //CCLabelTTF* titleRight=CCLabelTTF::labelWithString("System", "Marker Felt", 48);  
    
    //CCLabelTTF* titleQuotes=CCLabelTTF::labelWithString("\"            ", "Marker Felt", 48);  
    
    //CCLabelTTF* titleCenterTop=CCLabelTTF::labelWithString("How to build a...", "Marker Felt", 26);  
    
    //CCLabelTTF* titleCenterBottom=CCLabelTTF::labelWithString("Part 1", "Marker Felt", 48);  
    
    //CCMenuItemFont* startNew=CCMenuItemFont::itemFromString("New Game", this, menu_selector(MenuLayer::onNewGame)); //创建字符型按钮，注意 menu_selector里面的写法！！！ 类名::函数名！！！ 
    CCMenuItemImage* startNew=CCMenuItemImage::itemFromNormalImage("newGameBtn.png", "newGameBtn_over.png","newGameBtn.png",this,menu_selector(MenuLayer::onNewGame));
    
    //CCMenuItemFont* credits=CCMenuItemFont::itemFromString("Credits", this, menu_selector(MenuLayer::onCredites));  
    CCMenuItemImage* credits=CCMenuItemImage::itemFromNormalImage("creditsBtn.png","creditsBtn_over.png","creditsBtn.png",this,menu_selector(MenuLayer::onCredites));
    //CCMenuItemFont* aaa=CCMenuItemFont::itemFromString("aaa", this, menu_selector(MenuLayer::onCredites)); 
    
    CCMenu* menu=CCMenu::menuWithItems(startNew,credits,NULL);  
    //将两个按钮儿子添加到一个menu爹上,大头儿子小头爸爸不分手  
    //注意menuWithItem的单复数！！英文是不一样滴，还有千万别忘了NULL  
    
    //-----------楼下开始大规模setPosition了-----------  
    
    //titleCenterTop->setPosition(ccp(160,380));      
    //this->addChild(titleCenterTop);  
    
    //titleCenterBottom->setPosition(ccp(160,300));  
    //this->addChild(titleCenterBottom);  
    
    //titleQuotes->setPosition(ccp(160,345));  
    //this->addChild(titleQuotes);  
    
    titleLeft->setPosition(ccp(size.width/2,(size.height/5*4)));  
    this->addChild(titleLeft);  
    
    //titleRight->setPosition(ccp(220,345));  
    //this->addChild(titleRight);  
    
    
    menu->setPosition(ccp(size.width/2,size.height/2 - size.height/6));
    //menu->setPosition(ccp(480,320));  
    menu->alignItemsVerticallyWithPadding(40.0f);  
    //上面这句貌似是让menu中心对齐  
    this->addChild(menu);  
    
    //总结，以上这些全是 MenuLayer的node儿子！！！   
    //这之后，所有的的儿子都加到爹身上了，当运行这个MenuLayer之后，儿子们就可以按位置显示了。     
    
    //-----------setPosition end-------------------------  
    
    return true;  
}  

void MenuLayer::onNewGame(cocos2d::CCObject *pSender)  
{  
    SceneManager::goPlay();  
    //运行SceneManager的 goMenu静态方法  
}  

void MenuLayer::onCredites(cocos2d::CCObject *pSender)  
{  
    SceneManager::goCredits();  
    //还是运行goMenu方法  
}  
