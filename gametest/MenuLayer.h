//
//  MenuLayer.h
//  gametest
//
//  Created by MagicStudio on 13-3-28.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#ifndef gametest_MenuLayer_h
#define gametest_MenuLayer_h
#include "cocos2d.h"  
#include "BaseLayer.h"  

using namespace cocos2d;  

class MenuLayer:public BaseLayer   
{  
public:  
    virtual bool init();  
    
    void onNewGame (CCObject* pSender);  
    
    void onCredites (CCObject* pSender);  
    
    LAYER_NODE_FUNC(MenuLayer);  
};  


#endif
