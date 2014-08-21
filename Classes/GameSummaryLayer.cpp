#include "GameSummaryLayer.h"
#include "cocos2d.h"
#include "CustomEvent.h"
#include "GameSummaryData.h"

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
	bg->setPosition(Vec2(visibleSize.width*.16f,visibleSize.height*.30f));
	bg->setScale(1.75f);
	this->addChild(bg);

	auto playAgainItem = MenuItemImage::create("summary_button.png","summary_button01.png",CC_CALLBACK_1(GameSummaryLayer::onPlayAgain, this));
	playAgainItem->setAnchorPoint(Vec2(0,0));
	playAgainItem->setPosition(Vec2(bg->getContentSize().width - 165,bg->getContentSize().height - 10));
	playAgainItem->setScale(1.75f);
	
	auto homeAgainItem = MenuItemImage::create("summary_button.png","summary_button01.png",CC_CALLBACK_1(GameSummaryLayer::onHomeAgain, this));
	homeAgainItem->setAnchorPoint(Vec2(0,0));
	homeAgainItem->setPosition(Vec2(bg->getContentSize().width + 135,bg->getContentSize().height - 10));
	homeAgainItem->setScale(1.75f);
	
	auto titlLabel = LabelTTF::create("DiveIn", "Futura-CondensedExtraBold", 30);
	titlLabel->setAnchorPoint(Vec2(0,0));
	titlLabel->setPosition(Vec2(bg->getContentSize().width/2 - 50,(bg->getContentSize().height * .78f)));
	bg->addChild(titlLabel);

	_meterLabel = LabelTTF::create("320 M", "Futura-CondensedExtraBold", 27);
	_meterLabel->setAnchorPoint(Vec2(0,0));
	_meterLabel->setPosition(Vec2(bg->getContentSize().width/2 - 75, (bg->getContentSize().height * .58f)));
	_meterLabel->setColor(Color3B::BLACK);
	bg->addChild(_meterLabel);

    _earnedCoinsLabel = LabelTTF::create("Earned", "Futura-CondensedExtraBold", 22);
	_earnedCoinsLabel->setAnchorPoint(Vec2(0,0));
	_earnedCoinsLabel->setPosition(Vec2(bg->getContentSize().width/2,(bg->getContentSize().height * .40f)));
	_earnedCoinsLabel->setColor(Color3B::BLACK);
	bg->addChild(_earnedCoinsLabel);
    
    _earnedPearlLabel = LabelTTF::create("Earned", "Futura-CondensedExtraBold", 22);
	_earnedPearlLabel->setAnchorPoint(Vec2(0,0));
	_earnedPearlLabel->setPosition(Vec2(bg->getContentSize().width/2,(bg->getContentSize().height * .10f)));
	_earnedPearlLabel->setColor(Color3B::BLACK);
	bg->addChild(_earnedPearlLabel);

	auto coins = Sprite::create("coin2.png");
	coins->setAnchorPoint(Vec2(0,0));
	coins->setPosition(Vec2(bg->getContentSize().width/2 - 75,(bg->getContentSize().height * .40f)));
    coins->setScale(.5f);
	bg->addChild(coins);
    
    auto pearl = Sprite::create("pearl2.png");
	pearl->setAnchorPoint(Vec2(0,0));
	pearl->setPosition(Vec2(bg->getContentSize().width/2 - 80,(bg->getContentSize().height * .10f)));
    pearl->setScale(.5f);
	bg->addChild(pearl);

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

void GameSummaryLayer::setData(GameSummaryData* data) {
    _meterLabel->setString(std::to_string(data->totalMeters).append(" Meters"));
    _earnedCoinsLabel->setString(std::to_string(data->totalCoins));
    _earnedPearlLabel->setString(std::to_string(data->totalPearl));
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