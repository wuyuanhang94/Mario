#ifndef __Item_MushroomAddlife_H__
#define __Item_MushroomAddlife_H__

#include "Item_MushroomReward.h"

class Item_MushroomAddlife : public Item_MushroomReward
{
public:
	Item_MushroomAddlife();
	~Item_MushroomAddlife();

	bool init(CCDictionary* dict);
	virtual void collision(Mario* mario, CCArray* arr);
};

#endif