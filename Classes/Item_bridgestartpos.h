#ifndef __Item_bridgestartpos_H__
#define __Item_bridgestartpos_H__

#include "Item.h"

class Item_bridgestartpos : public Item
{
public:
	Item_bridgestartpos();
	~Item_bridgestartpos();

	bool init(CCDictionary* dict);
	virtual void move(float dt, Mario* mario) {}
	virtual void collision(Mario* mario, CCArray* arr) {}
};

#endif