#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "FloatingItems.h"

class GameLayer :public cocos2d::Layer
{
private:
    
    cocos2d::Size _visibleSize;
    cocos2d::Vec2 _visibleOrigin;
    
    cocos2d::Sprite* _isLand;
    cocos2d::Sprite* _bg;
    cocos2d::Sprite* _doubleUpMeter;
    cocos2d::Sprite* _dblUpFiller;
    

   // cocos2d::Vector<cocos2d::Sprite*> _platforms;
    cocos2d::Sprite* _platformArray[3][2];
    
    // floating vars
    FloatingItems* _coinsList[10];
    FloatingItems* _killerFishList[6];
    cocos2d::Sprite* _cloudList[4];
    
    // game charecter samsa
    cocos2d::Sprite* _samsa;
    FloatingItems* _pearl;
    FloatingItems* _doubleUp;
    
    //jump action
    cocos2d::MoveTo* _samsaMoveToAction;
    cocos2d::MoveTo* _samsaSettleAction;
    cocos2d::MoveTo* _doubleMeterAction;
    cocos2d::ScaleTo* _dblFillerAction;
    
    cocos2d::LabelTTF* _meters;
    
    // stage environment variables
    void setPlatform();
    void setFloatings();
    void setHuds();
    void setDoubleUp();
    void setDoubleUpEnable(bool enable = true);
    
    cocos2d::EventListenerTouchOneByOne* _touchListener;
    
    bool _isTouchBegan;
    bool _isDoubleUpMode;
    double _meterCovered;
    int _activeEnemyList[2];
    float _samsoMaxOnY;
    
public:
    
    static float COIN_OFFSET_X;
    static int GAME_SPEED_LEVEL;
    
    bool isInititalGFXCreated;
    bool isRunning;
    bool isStopped;
    bool isPaused;
    
    int collectedCoinCount;
    int collectedPearlCount;
    int collectedTreasureCount;
    
    cocos2d::LabelTTF* coinCount;
    
	GameLayer();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void update(float dt);
    
    void initGraphics();
    
    void touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void touchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void touchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    void touchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
    
    //virtual void Layer::onTouchesMoved(const std::vector<Touch*>& touches, Event *event);
    //virtual void Layer::onTouchesEnded(const std::vector<Touch*>& touches, Event *event);
    
    //virtual upda
    
    cocos2d::Sprite* getSamsa();
    

    void start();
    void reset();
    //void run(Ref* pSender);
    void run(float deltaTime);
    void pause();
    void resume();
    void stop();
    void clear();
    
    void resetCoins();
    void startParallex(bool resetPosition = false);
    void stopParallex();

	//~GameLayer();

	// implement the "static create()" method manually
    CREATE_FUNC(GameLayer);
};
#endif