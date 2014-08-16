#include "GameSummaryLayer.h"
#include "cocos2d.h"
#include "CustomEvent.h"

USING_NS_CC;

GameSummaryLayer::GameSummaryLayer()
{

}

bool GameSummaryLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 visibleOrigin = Director::getInstance()->getVisibleSize();

	this->setAnchorPoint(Vec2(0,0));
	this->setPosition(Vec2(0,0));

	auto bg = Sprite::create("Summary_popup.png");
	bg->setAnchorPoint(Vec2(0,0));
	bg->setPosition(Vec2(220,225));
	bg->setScale(1.75f);
	this->addChild(bg);

	auto playAgainItem = MenuItemImage::create("summary_button.png","summary_button01.png",CC_CALLBACK_1(GameSummaryLayer::onPlayAgain, this));
	playAgainItem->setAnchorPoint(Vec2(0,0));
	playAgainItem->setPosition(Vec2(bg->getContentSize().width - 100,bg->getContentSize().height - 10));
	playAgainItem->setScale(1.75f);
	
	auto homeAgainItem = MenuItemImage::create("summary_button.png","summary_button01.png",CC_CALLBACK_1(GameSummaryLayer::onHomeAgain, this));
	homeAgainItem->setAnchorPoint(Vec2(0,0));
	homeAgainItem->setPosition(Vec2(bg->getContentSize().width + 200,bg->getContentSize().height - 10));
	homeAgainItem->setScale(1.75f);
	
	auto titlLabel = LabelTTF::create("DiveIn", "Futura-CondensedExtraBold", 30);
	titlLabel->setAnchorPoint(Vec2(0,0));
	titlLabel->setPosition(Vec2(bg->getContentSize().width/2 - 50,bg->getContentSize().height - 34));
	bg->addChild(titlLabel);

	_meterLabel = LabelTTF::create("320 M", "Futura-CondensedExtraBold", 27);
	_meterLabel->setAnchorPoint(Vec2(0,0));
	_meterLabel->setPosition(Vec2(bg->getContentSize().width/2 - 50,bg->getContentSize().height - 85));
	_meterLabel->setColor(Color3B::BLACK);
	bg->addChild(_meterLabel);

    _earnedCoinsLabel = LabelTTF::create("Earned", "Futura-CondensedExtraBold", 22);
	_earnedCoinsLabel->setAnchorPoint(Vec2(0,0));
	_earnedCoinsLabel->setPosition(Vec2(bg->getContentSize().width/2 - 100,bg->getContentSize().height - 140));
	_earnedCoinsLabel->setColor(Color3B::BLACK);
	bg->addChild(_earnedCoinsLabel);

	auto coins = Sprite::create("coll_coin_1.png");
	coins->setAnchorPoint(Vec2(0,0));
	coins->setPosition(Vec2(bg->getContentSize().width/2 - 20,bg->getContentSize().height - 140));
	//coins->setScale(1.75f);
	bg->addChild(coins);

	auto noLabel = LabelTTF::create("3461", "Futura-CondensedExtraBold", 22);
	noLabel->setAnchorPoint(Vec2(0,0));
	noLabel->setPosition(Vec2(coins->getPositionX()+ coins->getContentSize().width + 10,bg->getContentSize().height - 140));
	noLabel->setColor(Color3B::BLACK);
	bg->addChild(noLabel);

	auto replayLabel = LabelTTF::create("Replay", "Futura-CondensedExtraBold", 25);
	replayLabel->setAnchorPoint(Vec2(0,0));
	replayLabel->setPosition(Vec2(playAgainItem->getContentSize().width/2 - 40,playAgainItem->getContentSize().height/2 - 10));
	replayLabel->setColor(Color3B::BLACK);
	playAgainItem->addChild(replayLabel);

	auto homeLabel = LabelTTF::create("Home", "Futura-CondensedExtraBold", 25);
	homeLabel->setAnchorPoint(Vec2(0,0));
	homeLabel->setPosition(Vec2(homeAgainItem->getContentSize().width/2 - 35,homeAgainItem->getContentSize().height/2 - 10));
	homeLabel->setColor(Color3B::BLACK);
	homeAgainItem->addChild(homeLabel);

	/*auto titlLabel = LabelTTF::create("DiveIn", "Helvetica", 18);
	titlLabel->setAnchorPoint(Vec2(0,0));
	titlLabel->setPosition(Vec2(bg->getContentSize().width/2 - 50,bg->getContentSize().height - 34));*/

	

	auto menuItem = Menu::create(playAgainItem, homeAgainItem, NULL);
	menuItem->setAnchorPoint(Vec2(0,0));
	menuItem->setPosition(Vec2(0,0));
	
	this->addChild(menuItem);
	
	

	return true;
}

void GameSummaryLayer::setData(int* data) {
    _meterLabel->setString(std::to_string(data[0]));
    _earnedCoinsLabel->setString(std::to_string(data[1]));
}

void GameSummaryLayer::onPlayAgain(Ref* pSender)
{
	log("on Play again");
    this->setVisible(false);
    EventCustom event = EventCustom(EVENT_TYPE_DIVEIN_TRIGGRED);
    _eventDispatcher->dispatchEvent(&event);
}

void GameSummaryLayer::onHomeAgain(Ref* pSender)
{
	log("on Home again");
    this->setVisible(false);
    EventCustom event = EventCustom(EVENT_TYPE_SHOW_LOBBY);
    _eventDispatcher->dispatchEvent(&event);
}