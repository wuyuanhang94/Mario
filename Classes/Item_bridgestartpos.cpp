#include "Item_bridgestartpos.h"


Item_bridgestartpos::Item_bridgestartpos()
{
}


Item_bridgestartpos::~Item_bridgestartpos()
{
}

bool Item_bridgestartpos::init(CCDictionary* dict)
{
	CCSprite::init();
#if 0
	//��Ģ�����˶�����
	CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(ANI_MUSHROOM_RUN);
	CCAnimate* animate = CCAnimate::create(animation);
	runAction(CCRepeatForever::create(animate));

	//����Ģ���ֵ�λ�ú�ê��
	const CCString* x = dict->valueForKey("x");
	const CCString* y = dict->valueForKey("y");
	setPosition(ccp(x->intValue(), y->intValue()));
	setAnchorPoint(ccp(0, 1));
	setZOrder(100);
#endif
	return true;
}