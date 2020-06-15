#ifndef __Item_flower_H__
#define __Item_flower_H__

#include "Item.h"

class Item_flower : public Item
{
public:
	Item_flower();
	~Item_flower();

	enum {STATUS_INSIDE, STATUS_OUTSIDE, STATUS_SHOW} _status;
	float _top;
	float _bottom;
	MARIO_DIR _dir;
	float _speed;

	void updateStatus();
	void setDirDown(float);

	bool canMove(Mario* mario);

	bool init(CCDictionary* dict);
	virtual void move(float dt, Mario* mario);
	virtual void collision(Mario* mario, CCArray* arr);
};

#endif