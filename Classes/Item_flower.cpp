#include "Item_flower.h"
#include "Mario.h"

Item_flower::Item_flower()
{
}

Item_flower::~Item_flower()
{
}

bool Item_flower::init(CCDictionary* dict)
{
	CCSprite::init();

	//让花运动起来
	CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(ANI_FLOWER);
	CCAnimate* animate = CCAnimate::create(animation);
	runAction(CCRepeatForever::create(animate));

	//设置花的位置
	const CCString* x = dict->valueForKey("x");
	const CCString* y = dict->valueForKey("y");
	setPosition(ccp(x->intValue(), MARIO_TileHeight*2));
		
	setAnchorPoint(ccp(0.5, 0));
	setVisible(false);

	_status = STATUS_INSIDE;
	_top = y->intValue() - MARIO_TileHeight;
	_bottom = MARIO_TileHeight * 2;
	_dir = DIR_UP;
	_speed = 50;

	return true;
}

void Item_flower::updateStatus()
{
	if (_status == STATUS_OUTSIDE)
	{
		setVisible(true);
		setZOrder(Util::GetTmxLayerZORDER(getMap(), "pipe") - 1);
	}
}

void Item_flower::setDirDown(float)
{
	_status = STATUS_OUTSIDE;
	_dir = DIR_DOWN;
}

bool Item_flower::canMove(Mario* mario)
{
	CCRect rcMario = mario->boundingBox();
	CCRect rcFlower = this->boundingBox();
	rcFlower.origin.y = _top;
	if (rcMario.intersectsRect(rcFlower))
		return false;
	return true;
}

void Item_flower::move(float dt, Mario* mario)
{
	if (_status == STATUS_SHOW)
		return;
	//看马里奥是否在
	if (_status == STATUS_INSIDE && _dir == DIR_UP)
	{
		if (!canMove(mario)) return;
	}

	if (_dir == DIR_UP)
	{
		setPositionY(getPositionY() + dt*_speed);
		if (getPositionY() >= _top)
		{
			scheduleOnce(schedule_selector(Item_flower::setDirDown), 2.0f);
			_status = STATUS_SHOW;
		}
		else if (getPositionY() >= _top - boundingBox().size.height)
		{
			_status = STATUS_OUTSIDE;
			updateStatus();
		}
	}
	else
	{
		setPositionY(getPositionY() - dt*_speed);
		if (getPositionY() <= _bottom)
			_dir = DIR_UP;
		else if (getPositionY() <= _top - boundingBox().size.height)
			_status = STATUS_INSIDE;
	}
}

void Item_flower::collision(Mario* mario, CCArray* arr)
{
	if (mario->boundingBox().intersectsRect(this->boundingBox()))
	{
		mario->killed(false);
	}
}