#include "Item_battery.h"


Item_battery::Item_battery()
{
}


Item_battery::~Item_battery()
{
}

bool Item_battery::init(CCDictionary* dict)
{
	CCSprite::init();

#if 0
	//让蘑菇怪运动起来
	CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(ANI_MUSHROOM_RUN);
	CCAnimate* animate = CCAnimate::create(animation);
	runAction(CCRepeatForever::create(animate));

	//设置蘑菇怪的位置和锚点
	const CCString* x = dict->valueForKey("x");
	const CCString* y = dict->valueForKey("y");
	setPosition(ccp(x->intValue(), y->intValue()));
	setAnchorPoint(ccp(0, 1));
	setZOrder(100);
#endif

	return true;
}