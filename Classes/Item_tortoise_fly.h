#ifndef _Item_tortoise_fly_H_
#define _Item_tortoise_fly_H_

#include "Item.h"

class Item_tortoise_fly : public Item
{
public:
	Item_tortoise_fly();
	~Item_tortoise_fly(); 

	bool init(CCDictionary* dict);
	virtual void move(float dt, Mario* mario);
	virtual void collision(Mario* mario, CCArray* arr);

	int _dis;
	MARIO_DIR _face;
	MARIO_DIR _dir1;
	float _maxY;
	float _minY;
	bool _isAlive;

	void updateStatus();
};

#endif