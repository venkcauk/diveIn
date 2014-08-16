#ifndef __LEVEL_INFO_LAYER_H__
#define __LEVEL_INFO_LAYER_H__

#include "cocos2d.h"

class LevelInfoLayer :public cocos2d::Layer
{
private:
public:
	LevelInfoLayer();
	void updateLevelInfo();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

	CREATE_FUNC(LevelInfoLayer);
};

#endif