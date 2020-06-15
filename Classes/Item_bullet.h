#ifndef __ITEM_BULLET_H__
#define __ITEM_BULLET_H__

#include "Item.h"
class Item_boss;

class Item_bullet:public Item
{
public:
	Item_bullet();
	~Item_bullet();

	MARIO_DIR _dir;

	bool init(CCDictionary* dict);
	void initBullet(Item_boss* boss);
	virtual void move(float dt, Mario* mario);
	virtual void collision(Mario* mario, CCArray* arr);
};

#endif