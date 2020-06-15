#include "Item_tortoise_fly.h"
#include "Mario.h"

Item_tortoise_fly::Item_tortoise_fly()
{
}


Item_tortoise_fly::~Item_tortoise_fly()
{
}

bool Item_tortoise_fly::init(CCDictionary* dict)
{
	CCSprite::init();

	_dis = dict->valueForKey("flyDis")->intValue();
	_face = DIR_LEFT;
	_dir1 = DIR_DOWN;
	_isAlive = true;


	//设置蘑菇怪的位置和锚点
	const CCString* x = dict->valueForKey("x");
	const CCString* y = dict->valueForKey("y");
	setPosition(ccp(x->intValue(), y->intValue()));
	
	setAnchorPoint(ccp(0, 1));
	setZOrder(100);

	_maxY = y->intValue();
	_minY = _maxY - _dis;

	updateStatus();

	return true;
}

void Item_tortoise_fly::updateStatus()
{
	stopAllActions();
	if (!_isAlive)
	{
		setDisplayFrameWithAnimationName(ANI_TORTOISE_STOP, 0);
		CCMoveBy* moveBy = CCMoveBy::create(1, ccp(0, -winSize.height));
		this->runAction(moveBy);
		return;
	}
	if (_face == DIR_LEFT)
	{
		CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(ANI_TORTOISE_RUN_LEFT);
		CCAnimate* animate = CCAnimate::create(animation);
		this->runAction(CCRepeatForever::create(animate));
	}
	else
	{
		CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(ANI_TORTOISE_RUN_RIGHT);
		CCAnimate* animate = CCAnimate::create(animation);
		this->runAction(CCRepeatForever::create(animate));
	}
}

void Item_tortoise_fly::move(float dt, Mario* mario)
{
	if (!canStartMove())
		return;

	if (_dir1 == DIR_DOWN)
	{
		setPositionY(getPositionY() - dt*_dis);
		if (getPositionY() <= _minY)
			_dir1 = DIR_UP;
	}
	else
	{
		setPositionY(getPositionY() + dt*_dis);
		if (getPositionY() >= _maxY)
			_dir1 = DIR_DOWN;
	}
}

void Item_tortoise_fly::collision(Mario* mario, CCArray* arr)
{
	if (cleanIfMoveOutofWindow(mario, arr))
		return;
	
	if (!_isAlive)
		return;
	
	if (!isCollisionWithMario(mario))
		return;

	float yoff = Util::getPositionLB(mario).y - Util::getPositionLB(this).y;
	if (yoff > this->boundingBox().size.height*0.6)
	{
		_isAlive = false;
		updateStatus();
	}
	else
	{
		mario->killed(false);
	}
}