#ifndef __Item_finalpoint_H__
#define __Item_finalpoint_H__

#include "Item.h"

class Item_finalpoint : public Item
{
public:
	Item_finalpoint();
	~Item_finalpoint();

	bool init(CCDictionary* dict);
	virtual void move(float dt, Mario* mario) {}
	virtual void collision(Mario* mario, CCArray* arr);
};

#endif