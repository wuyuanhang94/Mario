#include "Item_MushroomAddlife.h"
#include "Mario.h"

Item_MushroomAddlife::Item_MushroomAddlife()
{
}


Item_MushroomAddlife::~Item_MushroomAddlife()
{
}

bool Item_MushroomAddlife::init(CCDictionary* dict)
{
	Item_MushroomReward::init(dict);

	setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(FRAME_MUSHROOM_ADDLIFE));

	return true;
}

void Item_MushroomAddlife::collision(Mario* mario, CCArray* arr)
{
	if (_status == MR_STATUS_RUN)
	{
		if (mario->boundingBox().intersectsRect(this->boundingBox()))
		{
			mario->eatMushroom(IT_MushroomAddLife);
			arr->removeObject(this);
			this->removeFromParent();
			return;//必须要return，不然和后面clean冲突
		}
	}
	cleanIfMoveOutofWindow(mario, arr);
}