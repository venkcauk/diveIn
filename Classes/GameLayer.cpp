#include "GameLayer.h"
#include "cocos2d.h"
#include "CustomEvent.h"

USING_NS_CC;

GameLayer::GameLayer()
{
    _touchListener = NULL;
    _isTouchBegan = false;
    isRunning = false;
    _meterCovered = 0.0f;
    isInititalGFXCreated = false;
    
    collectedCoinCount = 0;
    collectedPearlCount = 0;
    collectedTreasureCount = 0;
    _samsoMaxOnY = 0.0f;
    
    
    _visibleOrigin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();

}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    return true;
}

void GameLayer::initGraphics() {
    
    this->setVisible(false);
    this->setAnchorPoint(Vec2(0,0));
    this->setPosition(Vec2(0,0));
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();
    
    auto sky = Sprite::create("sky.png");
    sky->setAnchorPoint(Vec2(0,0));
    sky->setPosition(Vec2(0,visibleSize.height - sky->getContentSize().height));
    this->addChild(sky);
    
    auto cloud1 = Sprite::create("cloud_01.png");
    cloud1->setAnchorPoint(Vec2(0,0));
    cloud1->setPosition(Vec2((sky->getContentSize().width * .10f),sky->getPositionY()+ (sky->getContentSize().height * .75f)));
    cloud1->setScale(.5f);
    this->addChild(cloud1);
    
    auto cloud2 = Sprite::create("cloud_02.png");
    cloud2->setAnchorPoint(Vec2(0,0));
    cloud2->setPosition(Vec2((sky->getContentSize().width  * .45f),sky->getPositionY()+ (sky->getContentSize().height * .80f)));
    cloud2->setScale(.75f);
    this->addChild(cloud2);
    
    auto cloud3 = Sprite::create("cloud_01.png");
    cloud3->setAnchorPoint(Vec2(0,0));
    cloud3->setPosition(Vec2((sky->getContentSize().width  * .65f),sky->getPositionY()+ (sky->getContentSize().height * .75f)));
    cloud3->setScale(.5f);
    this->addChild(cloud3);
    
    auto cloud4 = Sprite::create("cloud_02.png");
    cloud4->setAnchorPoint(Vec2(0,0));
    cloud4->setPosition(Vec2((sky->getContentSize().width  * .80f),sky->getPositionY()+ (sky->getContentSize().height * .80f)));
    cloud4->setScale(.5f);
    this->addChild(cloud4);
    
    _cloudList[0] = cloud1;
    _cloudList[1] = cloud2;
    _cloudList[2] = cloud3;
    _cloudList[3] = cloud4;
    
    auto water = Sprite::create("water_01.png");
    water->setAnchorPoint(Vec2(0,0));
    water->setPosition(Vec2(0,sky->getPositionY() - (water->getContentSize().height) * .30f));
    this->addChild(water);
    
    auto ripples = Sprite::create("ripples1_01.png");
    ripples->setAnchorPoint(Vec2(0,0));
    ripples->setPosition(Vec2(water->getPositionX(),water->getPositionY() + (water->getContentSize().height * .5f)));
    this->addChild(ripples);
    
    _isLand = Sprite::create("float_00.png");
    _isLand->setAnchorPoint(Vec2(0,0));
    _isLand->setPosition(Vec2(visibleSize.width * .13f,water->getPositionY() +  (water->getContentSize().height) * .97));
    this->addChild(_isLand);
    
    char frameName[100] = {0};
    _samsa = Sprite::create();
    Vector<SpriteFrame*> samsaFrame(10);
    //char frameName[100] = {0};
    for (int i=1; i<=13; i++) {
        sprintf(frameName, "samsa_%d.png", i);
        auto frame = SpriteFrame::create(frameName, Rect(0,0,148, 66));
        samsaFrame.pushBack(frame);
    }
    auto samsaAnimation = Animation::createWithSpriteFrames(samsaFrame, .08f);
    auto samsaAnimate = Animate::create(samsaAnimation);
    _samsa->runAction(RepeatForever::create(samsaAnimate));
    //_samsa->setScale(1.35f);
    _samsa->setAnchorPoint(Vec2(0,0));
    _samsa->setPosition(Vec2(0,100));
    
    auto wave = Sprite::create();
    Vector<SpriteFrame*> waveFrame(30);
    
    for (int i=1; i<=30; i++) {
        sprintf(frameName, "wave01_%d.png", i);
        auto frame = SpriteFrame::create(frameName, Rect(0,0,1024, 40));
        waveFrame.pushBack(frame);
    }
    auto waveAnimation = Animation::createWithSpriteFrames(waveFrame, .08f);
    auto waveAnimate = Animate::create(waveAnimation);
    wave->runAction(RepeatForever::create(waveAnimate));
    wave->setAnchorPoint(Vec2(0,0));
    wave->setPosition(Vec2(0,water->getPositionY() + water->getContentSize().height * .35f));
   
    // add "DiveIn" screen"
    _bg = Sprite::create("water_00.png");
    _bg->setAnchorPoint(Vec2(0,0));
    _bg->setScaleY(.90f);
    _bg->setPosition(Vec2(0,0));
    
    
    this->addChild(_bg);
    this->addChild(_samsa);
    this->addChild(wave);
    
     _samsoMaxOnY = wave->getPositionY() ;//- (_samsa->getContentSize().height * 6);
    _samsoMaxOnY -= (_samsoMaxOnY * .10f);
    
    setPlatform();
    setFloatings();
    setHuds();
    
    isInititalGFXCreated = true;
}

void GameLayer::setPlatform()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();
    
   // _platforms = Vector<Sprite*>(3);
    
    //auto platform;
    char name[100] = {0};
    int elementYPos[3] = {20,100,150};
    //Vector<Sprite*> platformGroup(2);
    float ypos;
    
    for (int i=2; i>=0; i--) {
        for (int j=1; j>=0; j--) {
            
            sprintf(name, "pf%d_1.png",i+1);
            
            auto platform = Sprite::create(name);
            platform->setAnchorPoint(Vec2(0,0));
            platform->setPosition(Vec2(visibleSize.width*(j),0));
            _platformArray[i][j] = platform;
            
            for (int k=1; k<8; k++) {
                sprintf(name, "pf%d_item%d_1.png",i+1,k);
                auto elements = Sprite::create(name);
                elements->setAnchorPoint(Vec2(0,0));
                elements->setTag(k);
                
                if(k==1)
                    ypos = 100;
                else
                    ypos = 150;
                
                elements->setPosition(Vec2(k*ypos,elementYPos[i]));
                platform->addChild(elements);
                elements->setVisible(false);
            }
            int random = arc4random()%7;
            platform->getChildByTag(random+1)->setVisible(true);
            
            _bg->addChild(platform);
        }
    }
}

void GameLayer::setFloatings() {
    
    float xpos = (arc4random()% int(_visibleSize.width*.5f)) +_visibleSize.width;
    float ypos = (arc4random()% int(_visibleSize.height*.5f)) +(100);
    float xOffSet;
    
    for (int i=0; i<10; i++) {
        //
        auto coin = new FloatingItems(this, FloatingItems::ITEM_ID::COINS, true);
        
        if(i==0)
            coin->image->setPosition(Vec2(xpos, ypos));
        else
            coin->image->setPosition(Vec2(xOffSet, ypos));
        
        xOffSet = coin->image->getPositionX() + 33;
        _coinsList[i] = coin;
    } //return;
    
    xOffSet = 0;
    auto ENEMY_COUNT = 3;
    int enemyID = FloatingItems::ITEM_ID::OBS_01;
    for (int i=0; i<(ENEMY_COUNT*2); i++) {
        
        enemyID = FloatingItems::ITEM_ID::OBS_01;
        
        if(i<ENEMY_COUNT)
            enemyID +=i;
        else
            enemyID += i-ENEMY_COUNT;
        
        xpos = (arc4random()% int(_visibleSize.width*.5f)) +_visibleSize.width;
        ypos = (arc4random()% int(_visibleSize.height*.5f)) +(100);
        
        auto enemy = new FloatingItems(this, (FloatingItems::ITEM_ID)enemyID, true);
        enemy->image->setPosition(Vec2(xpos, ypos));
        enemy->image->setVisible(false);
        
        _killerFishList[i] = enemy;
    }
    
    _activeEnemyList[0] = arc4random()%(ENEMY_COUNT*2);
    _activeEnemyList[1] = arc4random()%(ENEMY_COUNT*2);
    
    
    
}

void GameLayer::setHuds() {
    
    _meters = LabelTTF::create("0000000 M", "Futura-CondensedExtraBold", 30);
    _meters->setColor(Color3B::BLACK);
    _meters->setAnchorPoint(Vec2(0,0));
    _meters->setHorizontalAlignment(TextHAlignment::RIGHT);
    _meters->setPosition(Vec2(_visibleOrigin.x + (_visibleSize.width * .05f),_visibleOrigin.y + (_visibleSize.height * .93f)));
    this->addChild(_meters);
    
    coinCount = LabelTTF::create("0000000", "Futura-CondensedExtraBold", 30);
    coinCount->setColor(Color3B::BLACK);
    coinCount->setAnchorPoint(Vec2(0,0));
    coinCount->setHorizontalAlignment(TextHAlignment::RIGHT);
    coinCount->setPosition(Vec2(_visibleOrigin.x + (_visibleSize.width * .80f),_visibleOrigin.y + (_visibleSize.height * .93f)));
    this->addChild(coinCount);
    
    auto coinIcon = Sprite::create("coll_coin_1.png");
    coinIcon->setAnchorPoint(Vec2(0,0));
    coinIcon->setPosition(Vec2(coinCount->getPositionX() + coinCount->getContentSize().width + 2,coinCount->getPositionY() - coinCount->getContentSize().height * .15f));
    coinIcon->setScale(2);
    this->addChild(coinIcon);
}

void GameLayer::start()
{
    log("DiveIn Game Start");
    isRunning =true;
    
    _meterCovered = 0;
    
    for (int i=2; i>=0; i--) {
        for (int j=1; j>=0; j--) {
            auto platform = (Sprite*)_platformArray[i][j];
            auto moveAction = MoveBy::create((i+6), Point(-1024, platform->getPositionY()));
            platform->runAction(RepeatForever::create(Sequence::create(moveAction, NULL)));
        }
    }
    
    if(_touchListener == NULL)
    {
        _touchListener = EventListenerTouchOneByOne::create();
        _touchListener->setSwallowTouches(true);
        _touchListener->onTouchBegan = [&](Touch* touch, Event* event) {
            Vec2 p = touch->getLocation();
            Rect rect = this->getBoundingBox();
            
            if(rect.containsPoint(p))
            {
                touchBegan(touch, event);
                return true; // to indicate that we have consumed it.
            }
            return false; // we did not consume this event, pass thru.
        };
        _touchListener->onTouchMoved = [&](Touch* touch, Event* event) {
            touchMoved(touch, event);
        };
        _touchListener->onTouchEnded = [&](Touch* touch, Event* event) {
            touchEnded(touch, event);
        };
        
        _touchListener->onTouchCancelled = [&](Touch* touch, Event* event) {
            touchCancelled(touch, event);
        };
        
        Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_touchListener, 1);
    }
}

void GameLayer::touchBegan(Touch* touch, Event *event)
{
    if(!isRunning || (_samsa->getPositionY() > _samsoMaxOnY))
        return;
    
    
    if(_samsaMoveToAction!=NULL)
    {
        //_samsaJumpByAction->stop();
    }
    
    _isTouchBegan = true;

    _samsaMoveToAction = MoveTo::create(.2f, Vec2(_samsa->getPositionX(), _samsa->getPositionY()+(100 * .5)));
    _samsa->runAction(_samsaMoveToAction);
}

void GameLayer::touchMoved(Touch* touch, Event* event) {
    
}

void GameLayer::touchEnded(Touch* touch, Event* event) {
    _isTouchBegan = false;
}

void GameLayer::touchCancelled(Touch* touch, Event* event) {
    _isTouchBegan = false;
}

void GameLayer::stop()
{
    log("Divein Game Stop");
}

void GameLayer::pause()
{
    log("DiveIn Game Pause");
}

void GameLayer::resume()
{
    log("DiveIn Game Resume");
}

void GameLayer::update(float dt)
{
    //log("GameLater update");
    
    if(isRunning)
        run(dt);
}

void GameLayer::run(float deltaTime)
{
    //log("DiveIn Game Run");
    
    float xpos;
    float maxWidth = _visibleSize.width + 10  ;
    float deltaCloudTransit = (-100 * deltaTime);
    for(int i =0; i<4;i++)
    {
        Sprite* cloud = _cloudList[i];
        if(cloud->getPositionX() >= -100)
        {
            xpos = cloud->getPositionX();
            xpos = xpos + (deltaCloudTransit * .05f);
            cloud->setPositionX(xpos);
        }
        else{
            cloud->setPositionX(maxWidth);
        }
    }
    
    xpos = _isLand->getPositionX();
    
    if(_isLand->getPositionX() >= (_isLand->getContentSize().width * -1))
    {
        xpos = xpos + (deltaCloudTransit *.1f);
        _isLand->setPositionX(xpos);
    }
    else
    {
        _isLand->setPositionX(maxWidth);
    }
    
    for (int i=2; i>=0; i--) {
        for (int j=1; j>=0; j--) {
            auto platform = (Sprite*)_platformArray[i][j];
            if(platform->getPositionX() < -1024)
            {
                int random = arc4random()%7;
                for (int k=1; k<8; k++) {
                    platform->getChildByTag(k)->setVisible(false);
                }
                
                platform->setPositionX(1024);
                platform->getChildByTag(random+1)->setVisible(true);
            }
        }
    }
    
    if(_samsa!=NULL && !_isTouchBegan)
    {
        float ypos = _samsa->getPositionY();
        float moveY = ypos - ypos * deltaTime;
        if(ypos>100)
        {
            _samsa->setPositionY(moveY);
        }

    }
    
    for (int i=0; i<10; i++) {
        //
        auto coin = _coinsList[i];
        coin->run(deltaTime);
        
        if(coin->checkCollision(_samsa)) {
            collectedCoinCount+=1;
            coinCount->setString(std::to_string(collectedCoinCount));
        }
    }
    
    int activeEnemyID = 0;
    FloatingItems* enemy;
   
    for(int i =0; i<2; i++) {
        activeEnemyID = _activeEnemyList[i];
        enemy = _killerFishList[activeEnemyID];
        enemy->run(deltaTime);
        enemy->image->setVisible(true);
    
        if(enemy->checkCollision(_samsa))
        {
            isRunning = false;
            _activeEnemyList[i] = arc4random()%6; // total killerFish
            enemy = _killerFishList[_activeEnemyList[i]];
            EventCustom event(EVENT_TYPE_GAME_SUMMARY);
            //int* data[] = {collectedTreasureCount};
            //data[0] = collectedCoinCount;
            //data[1] = collectedPearlCount;
            //data[2] = collectedTreasureCount;
            //event.setUserData(data);
            _eventDispatcher->dispatchEvent(&event);
            
        }
    }
    
    _meterCovered += .05f;
    int totalMeter = _meterCovered;
    _meters->setString(std::to_string(totalMeter).append(" M"));
}

Sprite* GameLayer::getSamsa() {
    return _samsa;
}

void GameLayer::reset()
{
    log("DiveIn Game Reset");
}

void GameLayer::clear()
{
    log("DiveIn Game Clear");
}