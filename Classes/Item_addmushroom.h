#ifndef __Item_addmushroom_H__
#define __Item_addmushroom_H__

#include "Item.h"

class Item_addmushroom : public Item
{
public:
	Item_addmushroom();
	~Item_addmushroom();

	bool init(CCDictionary* dict);

	virtual void move(float dt, Mario* mario) {}
	virtual void collision(Mario* mario, CCArray* arr) {}
};

#endif