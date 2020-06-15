#include "Item_ladderLR.h"
#include "Mario.h"

Item_ladderLR::Item_ladderLR()
{
}


Item_ladderLR::~Item_ladderLR()
{
}

bool Item_ladderLR::init(CCDictionary* dict)
{
	CCSprite::init();

	Util::setTexture(this, "ladder.png");

	int dist = dict->valueForKey("ladderDis")->intValue();
	int LorR = dict->valueForKey("LorR")->intValue();
	if (LorR == 1)dist = -dist;

	CCMoveBy* moveBy = CCMoveBy::create(1, ccp(dist, 0));
	CCMoveBy* back = (CCMoveBy*)moveBy->reverse();
	this->runAction(
		CCRepeatForever::create(
		CCSequence::create(moveBy, back, NULL)
		));

	const CCString* x = dict->valueForKey("x");
	const CCString* y = dict->valueForKey("y");
	setPosition(ccp(x->intValue(), y->intValue()));
	setAnchorPoint(ccp(0, 1));
	setZOrder(100);

	return true;
}

void Item_ladderLR::collision(Mario* mario, CCArray* arr)
{
	CCPoint pt[2];
	pt[0] = Util::getPositionLB(mario);
	pt[1] = Util::getPositionRB(mario);
	for (int i = 0; i < 2;i++)
	{
		if (this->boundingBox().containsPoint(pt[i]))
		{
			mario->setOnLadder(true);
			break;
		}
	}
}