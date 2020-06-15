#ifndef __Item_fire_string_H__
#define __Item_fire_string_H__

#include "Item.h"

class Item_fire_string : public Item
{
public:
	Item_fire_string();
	~Item_fire_string();

	bool init(CCDictionary* dict);
	virtual void move(float dt, Mario* mario);
	virtual void collision(Mario* mario, CCArray* arr);

	bool _isRun;
	int _angle;
	int _duration;
};

#endif