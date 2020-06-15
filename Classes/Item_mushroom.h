#ifndef __Item_mushroom_H__
#define __Item_mushroom_H__

#include "Item_mushroom_family.h"

class Item_mushroom : public Item_mushroom_family
{
public:
	Item_mushroom();
	~Item_mushroom();
	
	bool init(CCDictionary* dict);
	virtual void move(float dt, Mario* mario);
	virtual void collision(Mario* mario, CCArray* arr);
};

#endif