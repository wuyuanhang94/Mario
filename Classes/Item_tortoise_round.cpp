#include "Item_tortoise_round.h"

Item_tortoise_round::Item_tortoise_round()
{
}

Item_tortoise_round::~Item_tortoise_round()
{
}

bool Item_tortoise_round::init(CCDictionary* dict)
{
	Item_tortoise::init(dict);

	const CCString* x = dict->valueForKey("x");
	_speed = dict->valueForKey("roundDis")->intValue();
	_right = x->intValue();
	_left = _right - _speed;
	setAnchorPoint(ccp(0.5, 0));

	setDisplayFrameWithAnimationName(ANI_TORTOISE_RUN_LEFT, 0);

	return true;
}

void Item_tortoise_round::move(float dt, Mario* mario)
{
	if (!canStartMove())return;
	if (_dir == DIR_LEFT)
	{
		setPositionX(getPositionX() - dt*_speed);
		if (getPositionX() <= _left && _status != STATUS_SPEED)
		{
			_dir = DIR_RIGHT;
			updateStatus();
		}
	}
	else
	{
		setPositionX(getPositionX() + dt*_speed);
		if (getPositionX() >= _right && _status != STATUS_SPEED)
		{
			_dir = DIR_LEFT;
			updateStatus();
		}
	}
	moveDown(dt);
}