#ifndef __POPUP_LAYER_H__
#define __POPUP_LAYER_H__

#include "cocos2d.h"
#include "LevelInfoLayer.h";
#include "OptionLayer.h"
#include "ItemSelectionLayer.h"
#include "GameSummaryLayer.h"

class PopupLayer : public cocos2d::Layer
{

	

private:

	LevelInfoLayer *levelInfoLayer;
	OptionLayer *optionLayer;
	ItemSelectionLayer *itemSelectionLayer;
	GameSummaryLayer *gameSummaryLayer;

public:

	enum POPUP_TYPE {
						GOAL,
						OPTIONS,
						SELECTION,
						GAME_SUMMARY,
						INAPP_PURCHASE
					};

	bool isVisible;
	int totalVisiblePoup;
    
    int *gameSummaryData;

	POPUP_TYPE currentPopupID;

	PopupLayer();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

	void showPopup(POPUP_TYPE popupID);
    
    void onPopupEvent(cocos2d::EventCustom* event);

	//~PopupLayer();

	// implement the "static create()" method manually
    CREATE_FUNC(PopupLayer);
};
#endif