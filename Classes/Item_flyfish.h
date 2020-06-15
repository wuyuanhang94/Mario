#ifndef __Item_flyfish_H__
#define __Item_flyfish_H__

#include "Item.h"

class Item_flyfish : public Item
{
public:
	Item_flyfish();
	~Item_flyfish();

	int _duration;
	int _offsetV;
	int _offsetH;
	MARIO_DIR _dir;
	CCSprite* _body;
	bool _removeFlag;
	bool _runFlag;

	bool init(CCDictionary* dict);
	virtual void move(float dt, Mario* mario);
	virtual void collision(Mario* mario, CCArray* arr);
	void updateStatus();
	void setRemoveFlag(){ _removeFlag = true; }
};

#endif