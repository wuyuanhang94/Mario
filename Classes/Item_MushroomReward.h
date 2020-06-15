#ifndef __Item_MushroomReward_H__
#define __Item_MushroomReward_H__

#include "Item_mushroom_family.h"

class Item_MushroomReward : public Item_mushroom_family
{
public:
	Item_MushroomReward();
	~Item_MushroomReward();

	enum {MR_STATUS_INIT, MR_STATUS_GROW, MR_STATUS_RUN} _status;

	bool init(CCDictionary* dict);
	virtual void move(float dt, Mario* mario);
	virtual void collision(Mario* mario, CCArray* arr);
	void setStatusRun();

	void updateStatus();
};

#endif