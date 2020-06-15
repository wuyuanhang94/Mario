#ifndef __Item_ladderLR_H__
#define __Item_ladderLR_H__

#include "Item.h"

class Item_ladderLR : public Item
{
public:
	Item_ladderLR();
	~Item_ladderLR();

	bool init(CCDictionary* dict);
	virtual void move(float dt, Mario* mario) {}
	virtual void collision(Mario* mario, CCArray* arr);
};

#endif