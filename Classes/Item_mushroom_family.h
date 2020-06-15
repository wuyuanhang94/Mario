#ifndef Item_mushroon_family_H__
#define Item_mushroon_family_H__

#include "Item.h"

class Item_mushroom_family: public Item
{
public:
	Item_mushroom_family();
	~Item_mushroom_family();

	MARIO_DIR _dir;
	int _speed;

	bool canMoveLeft(float dt);
	bool canMoveRight(float dt);

	void moveRight(float dt);
	void moveLeft(float dt);

	virtual void updateStatus(){}
};

#endif