#include "Item_addmushroom.h"


Item_addmushroom::Item_addmushroom()
{
}


Item_addmushroom::~Item_addmushroom()
{
}

bool Item_addmushroom::init(CCDictionary* dict)
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