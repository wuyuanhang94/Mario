#ifndef _Item_tortoise_round_H_
#define _Item_tortoise_round_H_

#include "Item_tortoise.h"
//16:10
class Item_tortoise_round : public Item_tortoise
{
public:
	Item_tortoise_round();
	~Item_tortoise_round(); 

	bool init(CCDictionary* dict);
	virtual void move(float dt, Mario* mario);

	int _left;
	int _right;
#if 0

	virtual void collision(Mario* mario, CCArray* arr) {}
	void updateStatus();
#endif
};

#endif