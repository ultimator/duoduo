//
//  SceneManager.cpp
//  gametest
//
//  Created by MagicStudio on 13-3-28.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#include <iostream> 
#include "SceneManager.h"  
#include "cocos2d.h"  
#include "PlayerLayer.h"
#include "CreditsLayer.h"
#define TRANSITION_DURATION 1.2f

using namespace cocos2d;  

//--------------Translation类的定义----------------------  
//下面定义了三种不同的转场，  
class FadeWhiteTransition :public CCTransitionFade  
{  
public:  
    static CCTransitionFade* transitionWithDuration (ccTime t ,CCScene* s)  
    {  
        return CCTransitionFade::transitionWithDuration(t, s,ccWHITE);  
    }  
};  

class ZoomFlipXLeftOver : public CCTransitionZoomFlipX  
{  
public:  
    static CCTransitionZoomFlipX* transitionWithDuration(ccTime t, CCScene* s)  
    {  
        return CCTransitionZoomFlipX::transitionWithDuration(t, s,kOrientationLeftOver);  
    }  
    
};  

class FlipYDownOver :public CCTransitionZoomFlipY  
{  
public:  
    static CCTransitionZoomFlipY* transitionWithDuration(ccTime t, CCScene* s)  
    {  
        return CCTransitionZoomFlipY::transitionWithDuration(t, s,kOrientationDownOver);  
    }  
};  
//-----------------end--------------------------------------------  

#define MAX_TRANS_SCENE 3 //定义最大的转换场景数  

int SceneManager::nIdx=0; //初始化静态变量  

CCTransitionScene* SceneManager::createTransition(ccTime t, cocos2d::CCScene *s)  
{  
    //nIdx++;  
    //这块其实写的不好...这个场景现在是从第二个开始播放的 
    nIdx = 0;
    
    nIdx=nIdx%MAX_TRANS_SCENE;  
    
    //这块对最大转场数取余，确保不会出现0-3之外的数  
    switch (nIdx) {  
        case 0: return FadeWhiteTransition::transitionWithDuration(t, s);  
        case 1: return ZoomFlipXLeftOver::transitionWithDuration(t, s);  
        case 2: return FlipYDownOver::transitionWithDuration(t, s);  
            break;            
        default:  
            break;  
    }  
    //分别返回了三种不同的转场  
    return NULL;       
}  



void SceneManager::goMenu()  
{  
    CCLayer* layer=MenuLayer::node();  
    SceneManager::go(layer);  
}  

void SceneManager::go(CCLayer* layer)  
{  
    CCDirector* director=CCDirector::sharedDirector();  
    CCScene* newScene=SceneManager::wrap(layer);  
    if (director->getRunningScene()) //这句话 很有可能写的不对啊  有哪位大侠知道怎么写 告知下...  
    {  
        //director->replaceScene(newScene);  
        director->replaceScene(createTransition(TRANSITION_DURATION, newScene));
    }  
    else   
    {  
        director->runWithScene(newScene);  
    }  
}  

CCScene* SceneManager::wrap(CCLayer* layer)  
{  
    CCScene* newScene=CCScene::node();  
    newScene->addChild(layer);  
    return newScene;  
}  
void SceneManager::goPlay()  
{  
    CCLayer* layer=PlayerLayer::node();   
    //生成一个PlayLayer的节点   
    SceneManager::go(layer);  
    //看看go函数的定义...这个layer直接被他扔到Scene里了  
}  

void SceneManager::goCredits()  
{  
    CCLayer* layer=CreditsLayer::node();  
    //node()思维啊 思维  
    SceneManager::go(layer);  
    //跟他的兄弟一个下场  
}  


