#include "Item_mushroom_family.h"


Item_mushroom_family::Item_mushroom_family()
{
	_dir = DIR_LEFT;
	_speedDown = 100;
	_speed = 50;
}


Item_mushroom_family::~Item_mushroom_family()
{
}

void Item_mushroom_family::moveLeft(float dt)
{
	if (canMoveLeft(dt))
	{
		setPositionX(getPositionX() - dt *_speed);
	}
}

void Item_mushroom_family::moveRight(float dt)
{
	if (canMoveRight(dt))
	{
		setPositionX(getPositionX() + dt *_speed);
	}
}

bool Item_mushroom_family::canMoveLeft(float dt)
{
	CCRect rc = this->boundingBox();
	float xoff = dt * _speed;

	CCPoint pt[3];
	pt[1] = ccp(rc.getMinX() - xoff, rc.getMinY());
	pt[0] = ccp(rc.getMinX() - xoff, rc.getMidY());
	pt[2] = ccp(rc.getMinX() - xoff, rc.getMaxY());

	if (Common::isBlock3Point(pt, getMap()))
	{
		_dir = DIR_RIGHT;
		updateStatus();
		return false;
	}
	return true;
}

bool Item_mushroom_family::canMoveRight(float dt)
{
	//get three right points of Mario
	CCRect rc = this->boundingBox();
	float xoff = dt *_speed;

	CCPoint pt[3];
	pt[1] = ccp(rc.getMaxX() + xoff, rc.getMinY());
	pt[0] = ccp(rc.getMaxX() + xoff, rc.getMidY());
	pt[2] = ccp(rc.getMaxX() + xoff, rc.getMaxY());

	if (Common::isBlock3Point(pt, getMap()))
	{
		_dir = DIR_LEFT;
		updateStatus();
		return false;
	}
	return true;
}