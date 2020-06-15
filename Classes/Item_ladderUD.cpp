#include "Item_ladderUD.h"
#include "Mario.h"

Item_ladderUD::Item_ladderUD()
{
}

Item_ladderUD::~Item_ladderUD()
{
}

bool Item_ladderUD::init(CCDictionary* dict)
{
	CCSprite::init();

	Util::setTexture(this, "ladder.png");

	const CCString* x = dict->valueForKey("x");
	const CCString* y = dict->valueForKey("y");
	setPosition(ccp(x->intValue(), y->intValue()));

	setAnchorPoint(ccp(0.5, 0));

	setZOrder(100);

	_dist = dict->valueForKey("ladderDis")->intValue();
	int UorD = dict->valueForKey("UorD")->intValue();
	if (UorD == 1)
	{
		_bottom = y->intValue();
		_top = _bottom + _dist;
		_dir = DIR_UP;
	}
	else
	{
		_top = y->intValue();
		_bottom = _top - _dist;
		_dir = DIR_DOWN;
	}
	_marioOn = false;
	return true;
}

void Item_ladderUD::move(float dt, Mario* mario)
{
	if (!canStartMove())return;
	if (_dir == DIR_DOWN)
	{
		//mario在梯子上且在当前我这个梯子上
		if (mario->_onLadder && _marioOn)
		{
			mario->setPositionY(mario->getPositionY() - dt*_dist);
		}
		setPositionY(getPositionY() - dt*_dist);
		if (getPositionY() <= _bottom)
		{
			_dir = DIR_UP;
		}
	}
	else
	{
		if (mario->_onLadder && _marioOn)
		{
			mario->setPositionY(mario->getPositionY() + dt*_dist);
		}
		setPositionY(getPositionY() + dt*_dist);
		if (getPositionY() >= _top)
		{
			_dir = DIR_DOWN;
		}
	}
}

void Item_ladderUD::collision(Mario* mario, CCArray* arr)
{
	CCPoint pt[2];
	pt[0] = Util::getPositionLB(mario);
	pt[1] = Util::getPositionRB(mario);
	for (int i = 0; i < 2;i++)
	{
		if (this->boundingBox().containsPoint(pt[i]))
		{
			mario->setOnLadder(true);
			this->_marioOn = true;
			break;
		}
		else
		{
			this->_marioOn = false;
		}
	}
}