#include "LobbyLayer.h"
#include "cocos2d.h"
#include "CustomEvent.h"

USING_NS_CC;

LobbyLayer::LobbyLayer()
{

}

// on "init" you need to initialize your instance
bool LobbyLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();
    _eventDispatcher = Director::getInstance()->getEventDispatcher();
	
	auto lobbyBG = Sprite::create("gamebg_01.png");
	lobbyBG->setAnchorPoint(Vec2(0,0));


	lobbyBG->setPosition(Vec2(visibleOrigin.x,visibleOrigin.y));
	lobbyBG->setScale(1);
	this->addChild(lobbyBG);

	auto gameCenterItem = MenuItemImage::create(
											"gc_01.png",
											"gc_00.png",
											CC_CALLBACK_1(LobbyLayer::onGameCenterSelected, this));
	gameCenterItem->setAnchorPoint(Vec2(0,0));
	gameCenterItem->setPosition(Vec2(visibleOrigin.x + 20,visibleOrigin.y));
	//gameCenterItem->setScale(.5f);

	auto fbLikeItem = MenuItemImage::create(
											"fb_01.png",
											"fb_00.png",
											CC_CALLBACK_1(LobbyLayer::onFBLikeSelected, this));
	fbLikeItem->setAnchorPoint(Vec2(0,0));
	fbLikeItem->setPosition(Vec2(visibleOrigin.x + gameCenterItem->getContentSize().width + 20,visibleOrigin.y));
	
	auto soundItem = MenuItemImage::create(
											"sound1_00.png",
											"sound1_01.png",
											CC_CALLBACK_1(LobbyLayer::onSoundModeSelected, this));
	soundItem->setAnchorPoint(Vec2(0,0));
	soundItem->setPosition(Vec2(visibleSize.width/2 + 200, visibleSize.height - soundItem->getContentSize().height));
    log("Sound Visible content width %4.5f",soundItem->getContentSize().width);
    log("Sound Visible content height %4.5f",soundItem->getContentSize().height);


	auto musicItem = MenuItemImage::create(
											"music1_00.png",
											"music1_01.png",
											CC_CALLBACK_1(LobbyLayer::onMusicModeSelected, this));
	musicItem->setAnchorPoint(Vec2(0,0));
	musicItem->setPosition(Vec2(soundItem->getPositionX() + soundItem->getContentSize().width + 10, visibleSize.height - musicItem->getContentSize().height));
    log("Music Visible content width %4.5f",musicItem->getContentSize().width);
    log("Music Visible content height %4.5f",musicItem->getContentSize().height);


	auto settingItem = MenuItemImage::create(
											 "option_00.png",
											 "option_01.png",
											 CC_CALLBACK_1(LobbyLayer::onSettingsSelected, this));
	settingItem->setAnchorPoint(Vec2(0,0));
	settingItem->setPosition(Vec2(musicItem->getPositionX() + musicItem->getContentSize().width + 10, visibleSize.height - settingItem->getContentSize().height));
    
    log("Option Visible content width %4.5f",settingItem->getContentSize().width);
    log("Option Visible content height %4.5f",settingItem->getContentSize().height);


	auto charectersLabel = LabelTTF::create("Charecters", "Futura-CondensedExtraBold", 20);
	charectersLabel->setAnchorPoint(Vec2(0,0));
	charectersLabel->setPosition(Vec2(0,charectersLabel->getContentSize().height/5));
	charectersLabel->setColor(Color3B::BLACK);

	auto charecterItem = MenuItemImage::create(
												"buttons_01.png",
												"buttons_02.png",
												CC_CALLBACK_1(LobbyLayer::onShowCharecterSelecetion, this));
	charecterItem->addChild(charectersLabel);
	charecterItem->setAnchorPoint(Vec2(0,0));
	charecterItem->setPosition(Vec2(visibleOrigin.x+100,visibleSize.height/2));
	charecterItem->setScale(2);

	auto collectionsLabel = LabelTTF::create("Collections", "Futura-CondensedExtraBold", 20);
	collectionsLabel->setAnchorPoint(Vec2(0,0));
	collectionsLabel->setPosition(Vec2(0,collectionsLabel->getContentSize().height/5));
	collectionsLabel->setColor(Color3B::BLACK);

	auto collectionItem = MenuItemImage::create(
												"buttons_01.png",
												"buttons_02.png",
												CC_CALLBACK_1(LobbyLayer::onShowCollectionSelecetion, this));
	collectionItem->addChild(collectionsLabel);
	collectionItem->setAnchorPoint(Vec2(0,0));
	collectionItem->setPosition(Vec2(visibleOrigin.x+100,charecterItem->getPositionY() - charecterItem->getContentSize().height - 50));
	collectionItem->setScale(2);

	auto themeLabel = LabelTTF::create("Theme", "Futura-CondensedExtraBold", 20);
	themeLabel->setAnchorPoint(Vec2(0,0));
	themeLabel->setPosition(Vec2(0,themeLabel->getContentSize().height/5));
	themeLabel->setColor(Color3B::BLACK);

	auto themeItem = MenuItemImage::create(
												"buttons_01.png",
												"buttons_02.png",
												CC_CALLBACK_1(LobbyLayer::onShowThemeSelecetion, this));
	themeItem->addChild(themeLabel);
	themeItem->setAnchorPoint(Vec2(0,0));
	themeItem->setPosition(Vec2(visibleOrigin.x+100,collectionItem->getPositionY() - collectionItem->getContentSize().height - 50));
	themeItem->setScale(2);
    
    auto diveLabel = LabelTTF::create("Play", "Futura-CondensedExtraBold", 20);
	diveLabel->setAnchorPoint(Vec2(0,0));
	diveLabel->setPosition(Vec2(0,diveLabel->getContentSize().height/5));
	diveLabel->setColor(Color3B::BLACK);
    
    auto diveIn = MenuItemImage::create("summary_button.png","summary_button01.png",CC_CALLBACK_1(LobbyLayer::diveIn, this));
    diveIn->setAnchorPoint(Vec2(0,0));
    diveIn->setPosition(Vec2(visibleOrigin.x+100,collectionItem->getPositionY() - collectionItem->getContentSize().height - 150));
    diveIn->setScale(2);
    diveIn->addChild(diveLabel);

	auto menus = Menu::create(gameCenterItem, fbLikeItem, soundItem, musicItem, settingItem, charecterItem, collectionItem, themeItem, diveIn, NULL);
	menus->setPosition(Vec2::ZERO);
	this->addChild(menus);

	//this->setVisible(false);

	return true;
}

void LobbyLayer::onGameCenterSelected(Ref *pSender)
{
	log("Game center is selected");
}

void LobbyLayer::onFBLikeSelected(Ref* pSender)
{
	log("FB like is seleceted");
}

void LobbyLayer::onSoundModeSelected(Ref* pSender)
{
	log("Sound mode is selected");
}

void LobbyLayer::onMusicModeSelected(Ref* pSender)
{
	log("Music mode is selected");
}

void LobbyLayer::onSettingsSelected(Ref* pSender)
{
	log("Setting options is selected");
    EventCustom event(EVENT_TYPE_OPTION_TRIGGRED);
    int *data[] = {0};
    event.setUserData(data);
    _eventDispatcher->dispatchEvent(&event);
}

void LobbyLayer::onShowCharecterSelecetion(Ref* pSender)
{
	log("on show charecter selection");
}

void LobbyLayer::onShowCollectionSelecetion(Ref* pSender)
{
	log("on show collection popup");
}

void LobbyLayer::onShowThemeSelecetion(Ref* pSender)
{
	log("on show theme selection popup");
}

void LobbyLayer::diveIn(Ref* pSender)
{
    log("dive In start");
    EventCustom event(EVENT_TYPE_DIVEIN_TRIGGRED);
    _eventDispatcher->dispatchEvent(&event);
    
}
/*LabelTTF* LobbyLayer::setLabel(String text)
{
	auto label = LabelTTF::create(text, "Arial", 25);
	label->setAnchorPoint(Vec2(0,0));
	label->setPosition(Vec2(0,label->getContentSize().height/5));

	return label;
}*/