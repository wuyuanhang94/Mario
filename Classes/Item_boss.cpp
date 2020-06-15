#include "Item_boss.h"
#include "Item_bullet.h"

Item_boss::Item_boss()
{
}


Item_boss::~Item_boss()
{
}

bool Item_boss::init(CCDictionary* dict)
{
	CCSprite::init();

	//设置蘑菇怪的位置和锚点
	const CCString* x = dict->valueForKey("x");
	const CCString* y = dict->valueForKey("y");
	setPosition(ccp(x->intValue(), y->intValue() - MARIO_TileHeight));
	setPosition(ccp(240, y->intValue() - MARIO_TileHeight));
	setAnchorPoint(ccp(0, 0));
	setZOrder(100);

	_dir = DIR_LEFT;
	_left = getPositionX();
	_right = _left + 96;
	_speed = 50;
	_isJump = false;
	_body = CCSprite::create();
	_body->setDisplayFrameWithAnimationName(ANI_BOSS_LEFT, 0);
	addChild(_body);
	this->setContentSize(_body->getContentSize());
	_body->setAnchorPoint(ccp(0, 0));
	_body->setPosition(ccp(0, 0));
	updateStatus();
	schedule(schedule_selector(Item_boss::fire), 1.0f);
	return true;
}

void Item_boss::move(float dt, Mario* mario)
{
	if (!canStartMove())return;
	if (_dir == DIR_LEFT)
	{
		setPositionX(getPositionX() - dt*_speed);
		if (getPositionX() <= _left)
		{
			_dir = DIR_RIGHT;
			updateStatus();
		}
	}
	else
	{
		setPositionX(getPositionX() + dt*_speed);
		if (getPositionX() >= _right)
		{
			_dir = DIR_LEFT;
			updateStatus();
		}
	}

	if (!_isJump)
	{
		int rValue = CCRANDOM_0_1() * 50;
		_isJump = rValue == 1;
		CCLog("rValue = %d\n", rValue);
		if (_isJump)
		{
			runAction(CCSequence::create(
				CCJumpBy::create(.2f, ccp(0, 0), 16, 1),
				CCCallFunc::create(this, callfunc_selector(Item_boss::setNoJump)),NULL));
		}
		else
			moveDown(dt);
	}
}

void Item_boss::setNoJump()
{
	CCLog("set jump false");
	_isJump = false;
}

void Item_boss::collision(Mario* mario, CCArray* arr)
{

}

void Item_boss::updateStatus()
{
	_body->stopAllActions();
	if (_dir == DIR_LEFT)
	{
		CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(ANI_BOSS_LEFT);
		CCAnimate* animate = CCAnimate::create(animation);
		_body->runAction(CCRepeatForever::create(animate));
	}
	else
	{
		CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(ANI_BOSS_RIGHT);
		CCAnimate* animate = CCAnimate::create(animation);
		_body->runAction(CCRepeatForever::create(animate));
	}
}

void Item_boss::fire(float dt)
{
	Item_bullet* bullet = (Item_bullet*)Item::create(IT_bullet, NULL);
	bullet->initBullet(this);
	_arr->addObject(bullet);
}