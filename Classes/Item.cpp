#include "Item.h"
#include "Item_mushroom.h"
#include "Item_tortoise.h"
#include "Item_flower.h"
#include "Item_MushroomReward.h"
#include "Item_MushroomAddLife.h"
#include "Item_battery.h"
#include "Item_boss.h"
#include "Item_darkcloud.h"
#include "Item_finalpoint.h"
#include "Item_fire_string.h"
#include "Item_flagpoint.h"
#include "Item_flower.h"
#include "Item_flyfish.h"
#include "Item_ladderLR.h"
#include "Item_ladderUD.h"
#include "Item_tortoise_fly.h"
#include "Item_tortoise_round.h"
#include "Item_bridgestartpos.h"
#include "Item_addmushroom.h"
#include "Item_bullet.h"

Item::Item()
{
	_speedDown = 100;
}


Item::~Item()
{
}

Item* Item::create(ITEM_TYPE type, CCDictionary* dict)
{
	Item* item;
	
	if (type == IT_mushroom)
		item = new Item_mushroom();
	else if (type == IT_tortoise)
		item = new Item_tortoise();
	else if (type == IT_flower)
		item = new Item_flower();
	else if (type == IT_MushroomReward)
		item = new Item_MushroomReward();
	else if (type == IT_MushroomAddLife)
		item = new Item_MushroomAddlife();
	else if (type == IT_MushroomAddLife)
		item = new Item_MushroomAddlife();
	else if (type == IT_flagpoint)
		item = new Item_flagpoint();
	else if (type == IT_finalpoint)
		item = new Item_finalpoint();
	else if (type == IT_flyfish)
		item = new Item_flyfish();
	else if (type == IT_ladderLR)
		item = new Item_ladderLR();
	else if (type == IT_ladderUD)
		item = new Item_ladderUD();
	else if (type == IT_tortoise_round)
		item = new Item_tortoise_round();
	else if (type == IT_tortoise_fly)
		item = new Item_tortoise_fly();
	else if (type == IT_fire_string)
		item = new Item_fire_string();
	else if (type == IT_boss)
		item = new Item_boss();
	else if (type == IT_bridgestartpos)
		item = new Item_bridgestartpos();
	else if (type == IT_addmushroom)
		item = new Item_addmushroom();
	else if (type == IT_darkcloud)
		item = new Item_darkcloud();
	else if (type == IT_battery)
		item = new Item_battery();
	else if (type == IT_bullet)
		item = new Item_bullet();

	item->_type = type;
	item->init(dict);
	item->autorelease();
	return item;
}

bool Item::canMoveDown(float dt)
{
	CCRect rc = this->boundingBox();
	float yoff = dt *_speedDown;

	CCPoint pt[3];
	pt[1] = ccp(rc.getMinX(), rc.getMinY() - yoff);
	pt[0] = ccp(rc.getMidX(), rc.getMinY() - yoff);
	pt[2] = ccp(rc.getMaxX(), rc.getMinY() - yoff);

	if (Common::isBlock3Point(pt, getMap()))
	{
		return false;
	}
	return true;
}
void Item::moveDown(float dt)
{
	if (canMoveDown(dt))
	{
		setPositionY(getPositionY() - dt *_speedDown);
	}
}
