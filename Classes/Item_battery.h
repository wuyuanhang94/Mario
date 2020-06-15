#ifndef __Item_battery_H__
#define __Item_battery_H__

#include "Item.h"

class Item_battery : public Item
{
public:
	Item_battery();
	~Item_battery();

	bool init(CCDictionary* dict);	
	virtual void move(float dt, Mario* mario) {}
	virtual void collision(Mario* mario, CCArray* arr) {}
};

#endif