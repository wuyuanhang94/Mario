#include "Item_finalpoint.h"
#include "Mario.h"
#include "SceneGame.h"

Item_finalpoint::Item_finalpoint()
{
}


Item_finalpoint::~Item_finalpoint()
{
}

bool Item_finalpoint::init(CCDictionary* dict)
{
	CCSprite::init();

	setContentSize(CCSize(MARIO_TileWidth,MARIO_TileHeight));
	const CCString* x = dict->valueForKey("x");
	const CCString* y = dict->valueForKey("y");
	setPosition(ccp(x->intValue(), y->intValue()));
	setAnchorPoint(ccp(0, 1));
	return true;
}

void Item_finalpoint::collision(Mario* mario, CCArray* arr)
{
	if (this->isCollisionWithMario(mario))
	{
		Util::replaceLayer(SceneGame::create(mario->_game->_mapIdx + 1));
	}
}