#include "ItemSelectionLayer.h"
#include "cocos2d.h";

USING_NS_CC;

ItemSelectionLayer::ItemSelectionLayer()
{

}

bool ItemSelectionLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 visibleOrigin = Director::getInstance()->getVisibleSize();

	this->setAnchorPoint(Vec2(0,0));
	this->setPosition(Vec2(0,0));

	auto bg = Sprite::create("popup_01.png");
	bg->setAnchorPoint(Vec2(0,0));
	bg->setPosition(Vec2(400,100));
	bg->setScale(1.5f);

	this->addChild(bg);

	return true;
}