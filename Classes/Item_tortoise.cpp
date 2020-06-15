#include "Item_tortoise.h"
#include "Mario.h"

Item_tortoise::Item_tortoise()
{
}


Item_tortoise::~Item_tortoise()
{
}

bool Item_tortoise::init(CCDictionary* dict)
{
	CCSprite::init();

	_needCollision = true;
	
	//设置乌龟的位置和锚点
	const CCString* x = dict->valueForKey("x");
	const CCString* y = dict->valueForKey("y");
	setPosition(ccp(x->intValue(), y->intValue() + 1));
	Util::moveNode(this, ccp(0, -MARIO_TileHeight));//由于乌龟的个头比地图格子要大，
	
	setAnchorPoint(ccp(0, 0));
	setZOrder(100);

	_status = STATUS_MOVE;

	return true;
}

void Item_tortoise::move(float dt, Mario* mario)
{
	if (_status == STATUS_STOP) return;

	if (_dir == DIR_LEFT)
		moveLeft(dt);
	else
		moveRight(dt);
	moveDown(dt);
}

void Item_tortoise::collision(Mario* mario, CCArray* arr)
{
	//增加是否需要做碰撞检测的标记，两个精灵分开后，设置碰撞为true
	if (mario->boundingBox().intersectsRect(this->boundingBox()))
	{
		if (!_needCollision)
			return;
	}
	else
	{
		_needCollision = true;
		return;
	}

	if (_status == STATUS_MOVE)
	{
		//普通的冲突，跟蘑菇的冲突差不多
		float yoff = mario->getPositionY() - this->getPositionY();
		if (yoff > this->boundingBox().size.height*0.6)
		{
			_status = STATUS_STOP;
			updateStatus();
		}
		else
		{
			//mario挂掉
			mario->killed(false);
		}
		_needCollision = false;
	}
	else if (_status == STATUS_STOP)
	{
		float xoff = mario->getPositionX() - this->getPositionX();
		if (xoff > 0)
			_dir = DIR_LEFT;
		else
			_dir = DIR_RIGHT;
		_status = STATUS_SPEED;
		_speed *= 4;
		updateStatus();
		_needCollision = false;
	}
	else if (_status == STATUS_SPEED)
	{
		float yoff = mario->getPositionY() - this->getPositionY();
		if (yoff > this->boundingBox().size.height*0.6)
		{
			arr->removeObject(this);
			CCMoveBy* moveBy = CCMoveBy::create(4, ccp(0, -winSize.width));
			CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(
				Item_tortoise::removeFromParent));
			this->runAction(CCSequence::create(moveBy, callFunc, NULL));
		}
		else
		{
			//mario挂掉
			mario->killed(false);
		}
	}
}

void Item_tortoise::updateStatus()
{
	stopAllActions();
	if (_status == STATUS_MOVE)
	{
		//普通的冲突，跟魔鬼的冲突差不多
		CCAnimation* animation;
		if (_dir == DIR_LEFT)
			animation = CCAnimationCache::sharedAnimationCache()->animationByName(ANI_TORTOISE_RUN_LEFT);
		else
			animation = CCAnimationCache::sharedAnimationCache()->animationByName(ANI_TORTOISE_RUN_RIGHT);
		CCAnimate* animate = CCAnimate::create(animation);
		runAction(CCRepeatForever::create(animate));
	}
	else if (_status == STATUS_STOP)
	{
		CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(ANI_TORTOISE_STOP);
		CCAnimate* animate = CCAnimate::create(animation);
		runAction(CCRepeatForever::create(animate));
	}
	else if (_status == STATUS_SPEED)
	{
		CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(ANI_TORTOISE_STOP);
		CCAnimate* animate = CCAnimate::create(animation);
		runAction(CCRepeatForever::create(animate));
	}
}