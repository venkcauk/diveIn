#ifndef __OPTION_LAYER_H__
#define __OPTION_LAYER_H__

#include "cocos2d.h"

class OptionLayer :public cocos2d::Layer
{
private:
public:
	OptionLayer();

	virtual bool init();

	void onClose(cocos2d::Ref* pSender);
	void onRateThisApp(cocos2d::Ref* pSender);
	void onRemoveAds(cocos2d::Ref* pSender);

	CREATE_FUNC(OptionLayer);
};
#endif