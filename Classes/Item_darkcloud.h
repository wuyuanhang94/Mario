#ifndef __Item_darkcloud_H__
#define __Item_darkcloud_H__

#include "Item.h"

class Item_darkcloud : public Item
{
public:
	Item_darkcloud();
	~Item_darkcloud();

	bool init(CCDictionary* dict);
	virtual void move(float dt, Mario* mario) {}
	virtual void collision(Mario* mario, CCArray* arr) {}
};

#endif