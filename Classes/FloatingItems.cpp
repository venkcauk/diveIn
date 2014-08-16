//
//  FloatingItems.cpp
//  diveIn
//
//  Created by Venkatesh Shivashanmugam on 31/07/14.
//
//

#include "FloatingItems.h"

USING_NS_CC;

FloatingItems::FloatingItems() {
    
    _visibleSize = Director::getInstance()->getVisibleSize();
    _visibleOrigin = Director::getInstance()->getVisibleOrigin();
    iscollectable = false;
    _isCollected = false;
}

FloatingItems::FloatingItems(Layer* parent, ITEM_ID id, bool collectable) {
    
    FloatingItems();
    
    itemID = id;
    iscollectable = collectable;
    _parent = parent;
    
    switch (itemID) {
        case ITEM_ID::COINS:
            setCoins();
            break;
        case ITEM_ID::PEARL:
            setPearl();
            break;
        case ITEM_ID::TREASURE:
            setTreasure();
            break;
            
        case ITEM_ID::OBS_01:
        case ITEM_ID::OBS_02:
        case ITEM_ID::OBS_03:
        case ITEM_ID::OBS_04:
        case ITEM_ID::OBS_05:
        case ITEM_ID::OBS_06:
        case ITEM_ID::OBS_07:
        case ITEM_ID::OBS_08:
            setEnemy();
            break;
            
        case ITEM_ID::DOUBLE_UP:
            setDoubleUp();
            break;
            
        default:
            break;
    }
}

void FloatingItems::setCoins() {
    
    char name[50] = {0};
    Vector<SpriteFrame*> coinFrame(7);
    image = Sprite::create();
    
    for(int i=1; i<8; i++) {
        sprintf(name, "coll_coin_%d.png", i);
        auto frame = SpriteFrame::create(name, Rect(0, 0, 29, 29));
        coinFrame.pushBack(frame);
    }
    
    auto animation = Animation::createWithSpriteFrames(coinFrame, .08f);
    auto animate = Animate::create(animation);
    image->runAction(RepeatForever::create(animate));
    
    image->setAnchorPoint(Vec2(0, 0));
    image->setPosition(Vec2(0, 0));
    _parent->addChild(image);
}

void FloatingItems::setPearl() {
    
}

void FloatingItems::setTreasure() {
    
}

void FloatingItems::setEnemy() {
 
    
    char name[50] = {0};
    Vector<SpriteFrame*> enemyFrame(1);
    
    
    Vec2 enemyResolution[8];
    enemyResolution[0] = Vec2(205,75);
    enemyResolution[1] = Vec2(130,100);
    enemyResolution[2] = Vec2(155,88);
    enemyResolution[3] = Vec2(219,102);
    enemyResolution[4] = Vec2(205,75);
    enemyResolution[5] = Vec2(130,100);
    enemyResolution[6] = Vec2(126,102);
    enemyResolution[7] = Vec2(121,86);
    

    int enemyResolutionID = itemID-4;
    float width = enemyResolution[enemyResolutionID].x;
    float height = enemyResolution[enemyResolutionID].y;
    image = Sprite::create();
    
    int totalFrames = 12;
    if(itemID == ITEM_ID::OBS_03)
        totalFrames = 14;
    
    for(int i=1; i<=totalFrames; i++) {
        sprintf(name, "obs_%d_%d.png", (itemID-4) + 1, i);
        auto frame = SpriteFrame::create(name, Rect(0, 0, width, height));
        enemyFrame.pushBack(frame);
    }
    
    auto animation = Animation::createWithSpriteFrames(enemyFrame, .08f);
    auto animate = Animate::create(animation);
    image->runAction(RepeatForever::create(animate));
    
    image->setAnchorPoint(Vec2(0, 0));
    image->setPosition(Vec2(0, 0));
    _parent->addChild(image);
}

void FloatingItems::setDoubleUp() {
    
}

bool FloatingItems::reset() {
    
    float xpos;
    float ypos;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    _isCollected = false;
    xpos = visibleSize.width + 100;
    image->setPositionX(xpos);
        
    if(itemID > ITEM_ID::TREASURE && itemID < ITEM_ID::DOUBLE_UP)
    {
        int maxHeight = (_visibleSize.height*.5f) + 100;
        ypos = arc4random()% maxHeight;
        ypos += 100;
        image->setPositionY(ypos);
    }
    return true;
}

void FloatingItems::dispose() {
    
}

bool FloatingItems::checkCollision(Sprite* target) {

    bool isCollisionOccured = false;
    Rect floaterRect = *new Rect(image->getPositionX(), image->getPositionY(), image->getContentSize().width/3, image->getContentSize().height/2);
    Rect samsaRewct = *new Rect(target->getPositionX()+(target->getContentSize().width/2), target->getPositionY(), target->getContentSize().width/3, target->getContentSize().height/2);
    
    if(samsaRewct.intersectsRect(floaterRect) && !_isCollected)
    {
        _isCollected = true;
        isCollisionOccured = true;
        reset();
    }
    
    if(!_isCollected)
    {
        if(image->getPositionX() < image->getContentSize().width * -1)
        {
            reset();
        }
    }
    
    return isCollisionOccured;
}

void FloatingItems::updateHUDByItems(ITEM_ID id) {
    /*if(itemID == ITEM_ID::COINS)
    {
        _parent->collectedCoinCount+=1;
        _parent->coinCount->setString(std::to_string(_parent->collectedCoinCount));
    }
    
    if(itemID == ITEM_ID::PEARL)
        _parent->collectedPearlCount+=1;
    if(itemID == ITEM_ID::TREASURE)
        _parent->collectedTreasureCount+=1;*/
}

void FloatingItems::run(float deltaTime) {

    float xpos = image->getPositionX();
    xpos -=3;
    
    image->setPositionX(xpos);
}

