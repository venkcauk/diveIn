#ifndef __GAME_SUMMARY_LAYER_H__
#define __GAME_SUMMARY_LAYER_H__

#include "cocos2d.h"
#include "GameSummaryData.h"

class GameSummaryLayer :public cocos2d::Layer
{
private:

    cocos2d::LabelTTF* _meterLabel;
    cocos2d::LabelTTF* _earnedCoinsLabel;
    cocos2d::LabelTTF* _earnedPearlLabel;
	void onPlayAgain(cocos2d::Ref* pSender);
	void onHomeAgain(cocos2d::Ref* pSender);

public:
    
    int *collectionData;
	GameSummaryLayer();
	virtual bool init();
    void setData(GameSummaryData* data);
	CREATE_FUNC(GameSummaryLayer);
};
#endif