//
//  BaseLayer.h
//  gametest
//
//  Created by MagicStudio on 13-4-1.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#ifndef gametest_BaseLayer_h
#define gametest_BaseLayer_h
#include "cocos2d.h"
using namespace cocos2d;  

class BaseLayer:public CCLayer  
{  
public:  
    virtual bool init();  
    
    LAYER_NODE_FUNC(BaseLayer);  
};  


#endif
