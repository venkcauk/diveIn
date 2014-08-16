#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "LobbyLayer.h"
#include "PopupLayer.h"
#include "GameLayer.h"

class DiveInScene : public cocos2d::Layer
{
    
private:
    
    cocos2d::EventDispatcher* _eventDispatcher;
    cocos2d::EventListenerCustom* _playAgainListener;
    cocos2d::EventListenerCustom* _showLobbyListener;
    cocos2d::EventListenerCustom* _gameSummary;
    
public:
    
	enum STATE{LOBBY, GAME, POPUP};
	enum STATE CURRENT_STATE;
    
    // Constructor
    DiveInScene();

	// It is pushed as top layer to bring the emergency popup to alert user.
	PopupLayer *popupLayer;

	// It is pushed as mid layer in the DiveInScene which hold's navigational UI items.
	LobbyLayer *lobbyLayer;

	// It is pushed as base layer in the DiveInScene which hold's the entire game play items.
    GameLayer *gameLayer;
	
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

	// set state.
	void setVisibelState(STATE state);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // Method is called for each frame. Used for animation objects which transform its position(move, rotate, scale)
    // Acts as a main game loop for the game.
    virtual void update(float dt);
    
    
    //void run(float deltaTime);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // Event listener
    void onDiveInTriggred(cocos2d::EventCustom* event);
    void onCharecterTriggred(cocos2d::EventCustom* event);
    void onCollectionTriggred(cocos2d::EventCustom* event);
    void onThemeTriggred(cocos2d::EventCustom* event);
    void onGameCenterTriggred(cocos2d::EventCustom* event);
    void onFBLikeTriggred(cocos2d::EventCustom* event);
    void onSoundTriggred(cocos2d::EventCustom* event);
    void onMusicTriggred(cocos2d::EventCustom* event);
    void onOptionTriggred(cocos2d::EventCustom* event);
    void onGameSummaryTriggred(cocos2d::EventCustom* event);
    
    // implement the "static create()" method manually
    CREATE_FUNC(DiveInScene);
};

#endif // __HELLOWORLD_SCENE_H__
