//
//  FloatingItems.h
//  diveIn
//
//  Created by Venkatesh Shivashanmugam on 31/07/14.
//
//

#ifndef __diveIn__FloatingItems__
#define __diveIn__FloatingItems__

#include "cocos2d.h"

class FloatingItems {
  
private:
    
    
    cocos2d::Size _visibleSize;
    cocos2d::Vec2 _visibleOrigin;
    
    cocos2d::Layer* _parent;
    
    bool _isCollected;
    
public:
    
    enum ITEM_ID {
        COINS = 1,
        TREASURE,
        PEARL,
        OBS_01,
        OBS_02,
        OBS_03,
        OBS_04,
        OBS_05,
        OBS_06,
        OBS_07,
        OBS_08,
        DOUBLE_UP
    };
    
    ITEM_ID itemID;
    
    int id;
    bool iscollectable;
    
    cocos2d::Sprite* image;
    
    FloatingItems();
    FloatingItems(cocos2d::Layer* parent, ITEM_ID id, bool collectable);
    
    void setCoins();
    void setPearl();
    void setTreasure();
    void setEnemy();
    void setDoubleUp();
    bool checkCollision(cocos2d::Sprite* target);
    void updateHUDByItems(ITEM_ID id);
    void run(float deltaTime);
    bool reset();
    void dispose();
};

#endif /* defined(__diveIn__FloatingItems__) */
