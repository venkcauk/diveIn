#include "OptionLayer.h"
#include "cocos2d.h"

USING_NS_CC;

OptionLayer::OptionLayer()
{
}

bool OptionLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();

	this->setAnchorPoint(Vec2(0,0));
	this->setPosition(Vec2(0,0));

	auto bg = Sprite::create("option_popup.png");
	bg->setAnchorPoint(Vec2(0,0));
	bg->setPosition(Vec2(visibleOrigin.x + 120,visibleOrigin.y+130));
	bg->setScale(2.0f);
	this->addChild(bg);

	auto grouptitle = LabelTTF::create("Remove Ads					                   Rate this app", "Futura-CondensedExtraBold", 18);
	grouptitle->setAnchorPoint(Vec2(0,0));
	grouptitle->setPosition(Vec2(visibleOrigin.x + visibleSize.width/3 - 130,visibleOrigin.y+visibleSize.height/1.6f));
	grouptitle->setColor(Color3B::BLACK);
	grouptitle->setScale(2.0f);
	this->addChild(grouptitle);

	auto closeItem = MenuItemImage::create("close_button.png","close_button.png",CC_CALLBACK_1(OptionLayer::onClose, this));
	//auto closeBtn = Sprite::create("close_button.png");
	closeItem->setAnchorPoint(Vec2(0,0));
	//closeItem->setPosition(Vec2(0,0));
	closeItem->setPosition(Vec2(bg->getPositionX() + bg->getContentSize().width + 380,bg->getPositionY() + bg->getContentSize().height+ 150));
	closeItem->setScale(2.0f);

	auto removeAdsItem = MenuItem::create(CC_CALLBACK_1(OptionLayer::onRemoveAds, this));
	removeAdsItem->setAnchorPoint(Vec2(0,0));
	removeAdsItem->setPosition(Vec2(bg->getPositionX() + 130,bg->getPositionY() + bg->getContentSize().height));
	removeAdsItem->setScale(2.0f);

	auto currencyLabel = LabelTTF::create("1$","Futura-CondensedExtraBold",36);
	currencyLabel->setAnchorPoint(Vec2(0,0));
	currencyLabel->setPosition(Vec2(0,0));
	currencyLabel->setColor(Color3B::BLACK);
	//currencyLabel->setScale(2.0f);
	removeAdsItem->addChild(currencyLabel);

	auto rateThisApp = MenuItemImage::create("close_button.png","close_button.png",CC_CALLBACK_1(OptionLayer::onRateThisApp, this));
	rateThisApp->setAnchorPoint(Vec2(0,0));
	rateThisApp->setPosition(Vec2(bg->getPositionX() + 550,bg->getPositionY() + bg->getContentSize().height));
	rateThisApp->setScale(2.0f);
	//bg->addChild(closeBtn);

	auto menus = Menu::create(closeItem, removeAdsItem, rateThisApp, NULL);
	//menus->setScale(1.0f);
	menus->setAnchorPoint(Vec2(0,0));
	//menus->setPosition(Vec2(bg->getPositionX() + bg->getContentSize().width,bg->getPositionY() + bg->getContentSize().height));
	menus->setPosition(Vec2(0,0));
	this->addChild(menus);

	return true;
}

void OptionLayer::onClose(Ref* pSender)
{
	log("On close option popup");
}

void OptionLayer::onRemoveAds(Ref* pSender)
{
	log("on Remove Ads from App");
}

void OptionLayer::onRateThisApp(Ref* pSender)
{
	log("Do on Rating this app");
}