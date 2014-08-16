#include "DiveInScene.h"
#include "CustomEvent.h"

USING_NS_CC;

DiveInScene::DiveInScene() {
    
    _playAgainListener = NULL;
    _showLobbyListener = NULL;
    _gameSummary = NULL;
}

Scene* DiveInScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
	auto layer = DiveInScene::create();
	scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool DiveInScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	// create popup layer.
	popupLayer = PopupLayer::create();
	    
	// create lobby layer.
	lobbyLayer = LobbyLayer::create();

	//create game layer.
	gameLayer = GameLayer::create();

    /* Add layer as a child to scene
	*
	*  PopupLayer->atIndex = 2;
	*  LobbyLayer->atIndex = 1;
	*  GameLayer->atIndex = 0;
	*/
    this->addChild(gameLayer);
	this->addChild(lobbyLayer);
	this->addChild(popupLayer);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    _eventDispatcher = Director::getInstance()->getEventDispatcher();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(DiveInScene::menuCloseCallback, this));
    
    closeItem->setAnchorPoint(Vec2(0,0));
    closeItem->setPosition(Vec2(0,0));
	//closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                //origin.y + closeItem->getContentSize().height/2));

    auto openItem = MenuItemImage::create(
                                          "CloseNormal.png",
                                          "CloseSelected.png",
                                          CC_CALLBACK_1(DiveInScene::menuCloseCallback,this));
    openItem->setPosition(visibleSize.width/2,openItem->getContentSize().height/2);
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem,openItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Dive In to Swim", "Helvetica", 75);
	label->setColor(Color3B::BLACK);
    
    // position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    //this->addChild(label, 1);
    
    // Add custom event.
    
    // #1 DiveIn
    if(_playAgainListener == NULL)
    {
        _playAgainListener = EventListenerCustom::create(EVENT_TYPE_DIVEIN_TRIGGRED, [=](EventCustom* event){
            DiveInScene::onDiveInTriggred(event);
        });
        _eventDispatcher->addEventListenerWithFixedPriority(_playAgainListener, 1);
    }
    
    // #9 Option
    auto _optionListener = EventListenerCustom::create(EVENT_TYPE_OPTION_TRIGGRED, [=](EventCustom* event){
        DiveInScene::onOptionTriggred(event);
    });
    
    _eventDispatcher->addEventListenerWithFixedPriority(_optionListener, 1);


    // initiate schedul. DiveInScene::run is main game loop.
    //this->getScene()->schedule(schedule_selector(GameLayer::run), 0);
    
    return true;
}

void DiveInScene::update(float deltaTime)
{
    if(gameLayer != NULL)
    {
        if(gameLayer->isRunning)
        {
            gameLayer->update(deltaTime);
        }
    }
}

void DiveInScene::setVisibelState(STATE state)
{
	log("DiveIn Scene setVisible ");
	CURRENT_STATE = state;
	switch (CURRENT_STATE)
	{
	case LOBBY:
		lobbyLayer->setVisible(true);
		gameLayer->setVisible(false);
		popupLayer->setVisible(true);
		break;

	case POPUP:
		lobbyLayer->setVisible(true);
		popupLayer->setVisible(true);
		gameLayer->setVisible(false);
		break;

	case GAME:
		lobbyLayer->setVisible(false);
		popupLayer->setVisible(false);
		gameLayer->setVisible(true);
        break;

	default:
		break;
	}
}

void DiveInScene::onOptionTriggred(EventCustom* event)
{
    log("on Option triggred");
    int *data = static_cast<int*>(event->getUserData());
    log("Command received SHOW/CLOSE option popup %d",*data);
    popupLayer->showPopup(PopupLayer::POPUP_TYPE::OPTIONS);
}

void DiveInScene::onDiveInTriggred(EventCustom* event)
{
    log("Command received SHOW/CLOSE DiveIn Game Screen");
    popupLayer->setVisible(false);
    lobbyLayer->setVisible(false);
   
    if(!gameLayer->isInititalGFXCreated)
        gameLayer->initGraphics();
    
    if(gameLayer->isRunning)
    {
        gameLayer->stop();
        gameLayer->clear();
    }
    
    if(_gameSummary == NULL) {
        _gameSummary = EventListenerCustom::create(EVENT_TYPE_GAME_SUMMARY, [=](EventCustom* event){
            DiveInScene::onGameSummaryTriggred(event);
        });
        _eventDispatcher->addEventListenerWithFixedPriority(_gameSummary, 1);
    }
    
    gameLayer->start();
    gameLayer->setVisible(true);
    this->unscheduleUpdate();
    this->scheduleUpdate();
}

void DiveInScene::onGameSummaryTriggred(EventCustom* event) {

   // int *data = static_cast<int*>(event->getUserData());
   // popupLayer->gameSummaryData = data;
    popupLayer->setVisible(true);
    popupLayer->showPopup(PopupLayer::POPUP_TYPE::GAME_SUMMARY);
    
    if(_showLobbyListener == NULL)
    {
        _showLobbyListener = EventListenerCustom::create(EVENT_TYPE_SHOW_LOBBY, [=](EventCustom* event){
            DiveInScene::setVisibelState(STATE::LOBBY);
        });
        _eventDispatcher->addEventListenerWithFixedPriority(_showLobbyListener, 1);
    }
}


void DiveInScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
