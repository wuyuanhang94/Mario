#ifndef __Item_boss_H__
#define __Item_boss_H__

#include "Item.h"

class Item_boss : public Item
{
public:
	Item_boss();
	~Item_boss();

	MARIO_DIR _dir;
	int _left;
	int _right;
	int _speed;
	bool _isJump;

	CCSprite* _body;

	bool init(CCDictionary* dict);
	virtual void move(float dt, Mario* mario);
	virtual void collision(Mario* mario, CCArray* arr);
	void updateStatus();
	void setNoJump();
	void fire(float dt);

	CCArray* _arr;
};

#endif