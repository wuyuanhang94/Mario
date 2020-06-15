#ifndef __Item_flagpoint_H__
#define __Item_flagpoint_H__

#include "Item.h"

class Item_flagpoint : public Item
{
public:
	Item_flagpoint();
	~Item_flagpoint();

	bool _isTouch;

	bool init(CCDictionary* dict);
	virtual void move(float dt, Mario* mario) {}
	virtual void collision(Mario* mario, CCArray* arr);
};

#endif