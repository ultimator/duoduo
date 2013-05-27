//
//  CreditsLayer.h
//  gametest
//
//  Created by MagicStudio on 13-3-29.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#ifndef gametest_CreditsLayer_h
#define gametest_CreditsLayer_h
#include "cocos2d.h"  
#include "SceneManager.h"  
#include "BaseLayer.h"

using namespace cocos2d;//我还是太懒了 大家不要向我学习  

class CreditsLayer:public BaseLayer  
{  
public:  
    virtual bool init();  
    
    void back (CCObject* pSender);  
    
    LAYER_NODE_FUNC(CreditsLayer);  
    
};  


#endif
