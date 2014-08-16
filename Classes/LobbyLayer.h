#ifndef __LOBBY_LAYER_H__
#define __LOBBY_LAYER_H__

#include "cocos2d.h"

class LobbyLayer :public cocos2d::Layer
{
private:
    
    cocos2d::EventDispatcher* _eventDispatcher;
	//Menu* menus;

	void onGameCenterSelected(cocos2d::Ref* pSender);
	void onFBLikeSelected(cocos2d::Ref* pSender);
	void onSoundModeSelected(cocos2d::Ref* pSender);
	void onMusicModeSelected(cocos2d::Ref* pSender);
	void onSettingsSelected(cocos2d::Ref* pSender);
	void onShowCharecterSelecetion(cocos2d::Ref* pSender);
	void onShowCollectionSelecetion(cocos2d::Ref* pSender);
	void onShowThemeSelecetion(cocos2d::Ref* pSender);
    void diveIn(cocos2d::Ref* pSender);

	//cocos2d::LabelTTF* setLabel(cocos2d::String text);

public:
	LobbyLayer();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

	//~LobbyLayer();

	// implement the "static create()" method manually
    CREATE_FUNC(LobbyLayer);
};

#endif