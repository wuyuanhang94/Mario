#include "Item_MushroomReward.h"
#include "Mario.h"

Item_MushroomReward::Item_MushroomReward()
{
}

Item_MushroomReward::~Item_MushroomReward()
{
}

bool Item_MushroomReward::init(CCDictionary* dict)
{
	CCSprite::init();

	setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(FRAME_MUSHROOM_REWARD));

	//设置蘑菇怪的位置和锚点
	const CCString* x = dict->valueForKey("x");
	const CCString* y = dict->valueForKey("y");
	setPosition(ccp(x->intValue(), y->intValue()));
	setAnchorPoint(ccp(0, 1));

	_status = MR_STATUS_INIT;
	_dir = DIR_LEFT;
	_speed = 50;
	_speedDown = 100;

	return true;
}

void Item_MushroomReward::move(float dt, Mario* mario)
{
	if (_status != MR_STATUS_RUN) return;

	if (_dir == DIR_LEFT)
		moveLeft(dt);
	else
		moveRight(dt);
	moveDown(dt);
}

void Item_MushroomReward::collision(Mario* mario, CCArray* arr)
{
	if (_status == MR_STATUS_RUN)
	{
		if (mario->boundingBox().intersectsRect(this->boundingBox()))
		{
			mario->eatMushroom(IT_MushroomReward);
			arr->removeObject(this);
			this->removeFromParent();
			return;//必须要return，不然和后面clean冲突
		}
	}
	cleanIfMoveOutofWindow(mario, arr);
}

void Item_MushroomReward::setStatusRun()
{
	_status = MR_STATUS_RUN;
}

void Item_MushroomReward::updateStatus()
{
	if (_status == MR_STATUS_INIT)
		this->setVisible(false);
	if (_status == MR_STATUS_GROW)
	{
		setZOrder(Util::GetTmxLayerZORDER(getMap(), "block") - 1);
		this->setVisible(true);
		this->runAction(
			CCSequence::create(
			CCMoveBy::create(.1f, ccp(0, MARIO_TileHeight+1)),
			CCCallFunc::create(this,callfunc_selector(Item_MushroomReward::setStatusRun)),NULL)
			);
	}
}