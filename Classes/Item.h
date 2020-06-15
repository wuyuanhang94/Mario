#ifndef __Item_H__
#define __Item_H__

#include "Common.h"
class Mario;

class Item : public CCSprite
{
public:
	Item();
	~Item();

	ITEM_TYPE _type;
	int _speedDown;

	static Item* create(ITEM_TYPE type, CCDictionary* dict);
	virtual bool init(CCDictionary* dict) = 0;
	virtual void move(float dt, Mario* mario) = 0;
	virtual void collision(Mario* mario, CCArray* arr) = 0;

	CCTMXTiledMap* getMap()
	{
		return (CCTMXTiledMap*)this->getParent();
	}

	bool isCollisionWithMario(CCSprite* sprite)
	{
		return sprite->boundingBox().intersectsRect(this->boundingBox());
	}

	bool canStartMove()
	{
		CCPoint ptNode = Util::getPositionLB(this);
		CCPoint ptWorld = getMap()->convertToWorldSpace(ptNode);
		if (Util::isOutofWindow(ptWorld))
			return false;
		return true;
	}

	bool Item::cleanIfMoveOutofWindow(CCSprite* mario, CCArray* arr)
	{
		float mushroomX = getPositionX();
		float marioX = mario->getPositionX();
		float off = marioX - mushroomX;
		if (off > winSize.width)
		{
			arr->removeObject(this);
			this->removeFromParent();
			return true;
		}
		return false;
	}

	bool canMoveDown(float dt);
	void moveDown(float dt);
};

#endif