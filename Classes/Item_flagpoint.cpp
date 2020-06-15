#include "Item_flagpoint.h"
#include "Mario.h"

Item_flagpoint::Item_flagpoint()
{
}


Item_flagpoint::~Item_flagpoint()
{
}

bool Item_flagpoint::init(CCDictionary* dict)
{
	CCSprite::init();

	Util::setTexture(this,"flag.png");

	const CCString* x = dict->valueForKey("x");
	const CCString* y = dict->valueForKey("y");
	setPosition(ccp(x->intValue(), y->intValue()));
	
	setAnchorPoint(ccp(0, 0));
	Util::moveNode(this, ccp(-MARIO_TileWidth, -MARIO_TileHeight));
	setZOrder(100);
	_isTouch = false;

	return true;
}

void Item_flagpoint::collision(Mario* mario, CCArray* arr)
{
	if (_isTouch)
		return;

	CCRect rc = mario->boundingBox();
	int gid = Common::getGID(ccp(rc.getMidX(), rc.getMidY()), getMap(), "flagpole");
	if (gid != 0)
	{
		_isTouch = true;
		mario->touchFlag();
		this->runAction(
			CCSequence::create(
			CCMoveBy::create(3, ccp(0,-9*MARIO_TileHeight)),
			CCCallFunc::create(mario, callfunc_selector(Mario::autoCtrl)),NULL)
			);
	}
}