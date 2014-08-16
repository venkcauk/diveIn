#ifndef __ITEM_SELECTION_LAYER_H__
#define __ITEM_SELECTION_LAYER_H__

#include "cocos2d.h";

class ItemSelectionLayer :public cocos2d::Layer
{

private:
public:
	ItemSelectionLayer();

	virtual bool init();

	CREATE_FUNC(ItemSelectionLayer);
};
#endif