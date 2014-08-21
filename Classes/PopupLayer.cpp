#include "PopupLayer.h"
#include "cocos2d.h"
#include "LevelInfoLayer.h"
#include "OptionLayer.h"
#include "ItemSelectionLayer.h"
#include "GameSummaryLayer.h"
#include "CustomEvent.h"

USING_NS_CC;

PopupLayer::PopupLayer()
{

}

// on "init" you need to initialize your instance
bool PopupLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	//Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();

	this->setAnchorPoint(Vec2(0,0));
	this->setPosition(Vec2(0,0));
	this->setScale(1.0f);

	levelInfoLayer = LevelInfoLayer::create();
	this->addChild(levelInfoLayer);

	optionLayer = OptionLayer::create();
	this->addChild(optionLayer);

	itemSelectionLayer = ItemSelectionLayer::create();
	this->addChild(itemSelectionLayer);

	gameSummaryLayer = GameSummaryLayer::create();
	this->addChild(gameSummaryLayer);

	showPopup(POPUP_TYPE::GOAL);
	//showPopup(POPUP_TYPE::OPTIONS);
	//showPopup(POPUP_TYPE::SELECTION);
	//showPopup(POPUP_TYPE::GAME_SUMMARY);
    
    /*auto playAgainListener = EventListenerCustom::create(EVENT_TYPE_PLAY_AGAIN, [=](EventCustom* event){
        PopupLayer::onPopupEvent(event);
    });*/
    //_eventDispatcher->addEventListenerWithFixedPriority(playAgainListener, 1);

    /*auto showLobbyListener = EventListenerCustom::create(EVENT_TYPE_SHOW_LOBBY, [=](EventCustom* event){
        PopupLayer::onPopupEvent(event);
    });*/
    //_eventDispatcher->addEventListenerWithFixedPriority(showLobbyListener, 1);

    
	return true;
}

void PopupLayer::showPopup(POPUP_TYPE popupID)
{
	currentPopupID = popupID;

	levelInfoLayer->setVisible(false);
	optionLayer->setVisible(false);
	itemSelectionLayer->setVisible(false);
	gameSummaryLayer->setVisible(false);

	switch (currentPopupID)
	{
		case PopupLayer::GOAL:
			// show level info details to user.
			levelInfoLayer->setVisible(true);
			break;
		case PopupLayer::OPTIONS:
			optionLayer->setVisible(true);
			break;
		case PopupLayer::SELECTION:
			itemSelectionLayer->setVisible(true);
			break;
		case PopupLayer::GAME_SUMMARY:
            gameSummaryLayer->setData(gameSummaryData);
			gameSummaryLayer->setVisible(true);
			break;
		case PopupLayer::INAPP_PURCHASE:
			break;
		default:
			levelInfoLayer->setVisible(false);
			optionLayer->setVisible(false);
			break;
	}
}

void PopupLayer::onPopupEvent(EventCustom* event) {
    _eventDispatcher->dispatchEvent(event);
}