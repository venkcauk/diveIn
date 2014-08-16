#include "LevelInfoLayer.h"
#include "cocos2d.h"

USING_NS_CC;

LevelInfoLayer::LevelInfoLayer()
{
	// constructor
}

bool LevelInfoLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}

	this->setAnchorPoint(Vec2(0,0));
	this->setPosition(Vec2(0,0));
	//this->setScale(2.0f);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("goals_popup.png");
	bg->setAnchorPoint(Vec2(0,0));
	bg->setPosition(Vec2(visibleOrigin.x + visibleSize.width/2 - 130,visibleOrigin.y+visibleSize.height/6));
	bg->setScale(2.0f);
	this->addChild(bg);

	auto titleLabel = LabelTTF::create("Goals", "Futura-CondensedExtraBold", 25);
	titleLabel->setAnchorPoint(Vec2(0,0));
	titleLabel->setPosition(Vec2(visibleOrigin.x + visibleSize.width/1.40f - 130,visibleOrigin.y+visibleSize.height/1.8));
	titleLabel->setScale(2.0F);
	titleLabel->setColor(Color3B::WHITE);
	this->addChild(titleLabel);

	auto infoLabel = LabelTTF::create("- Swim 300 meters.\n - \t\t\tCollect 45 collections without using Powerup.\n - Find 3 treasures.", "Futura-CondensedExtraBold", 20);
	infoLabel->setAnchorPoint(Vec2(0,1));
	infoLabel->setPosition(Vec2(visibleOrigin.x + visibleSize.width/2.65f,visibleOrigin.y+visibleSize.height/2));
	infoLabel->setScale(2.0f);
	infoLabel->setColor(Color3B::GRAY);
	this->addChild(infoLabel);

	return true;
}