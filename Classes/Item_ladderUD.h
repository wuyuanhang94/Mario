#ifndef __Item_ladderUD_H__
#define __Item_ladderUD_H__

#include "Item.h"

class Item_ladderUD : public Item
{
public:
	Item_ladderUD();
	~Item_ladderUD();

	bool init(CCDictionary* dict);
	virtual void move(float dt, Mario* mario);
	virtual void collision(Mario* mario, CCArray* arr);

	int _dist;
	int _top;
	int _bottom;
	bool _marioOn;
	MARIO_DIR _dir;
};

#endif