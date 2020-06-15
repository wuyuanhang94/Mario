#ifndef _Item_tortoise_H_
#define _Item_tortoise_H_

#include "Item_mushroom_family.h"

class Item_tortoise : public Item_mushroom_family
{
public:
	Item_tortoise();
	~Item_tortoise(); 

	enum{STATUS_MOVE,STATUS_STOP,STATUS_SPEED} _status;
	bool _needCollision;

	bool init(CCDictionary* dict);
	virtual void move(float dt, Mario* mario);
	virtual void collision(Mario* mario, CCArray* arr);
	void updateStatus();
};

#endif