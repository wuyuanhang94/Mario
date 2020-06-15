#include "Item_mushroom.h"
#include "Mario.h"

Item_mushroom::Item_mushroom()
{
}

Item_mushroom::~Item_mushroom()
{
}

bool Item_mushroom::init(CCDictionary* dict)
{
	CCSprite::init();

	//��Ģ�����˶�����
	CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(ANI_MUSHROOM_RUN);
	CCAnimate* animate = CCAnimate::create(animation);
	runAction(CCRepeatForever::create(animate));

	//����Ģ���ֵ�λ�ú�ê��
	const CCString* x = dict->valueForKey("x");
	const CCString* y = dict->valueForKey("y");
	setPosition(ccp(x->intValue(), y->intValue() + 1));
	setAnchorPoint(ccp(0, 0));
	Util::moveNode(this, ccp(0, -MARIO_TileWidth));
	setZOrder(100);

	_dir = DIR_LEFT;
	_speed = 50;
	_speedDown = 100;

	return true;
}

void Item_mushroom::move(float dt,Mario* mario)
{
	if (getPositionX() - mario->getPositionX() >= winSize.width)
		return;

	if (_dir == DIR_LEFT)
		moveLeft(dt);
	else
		moveRight(dt);
	moveDown(dt);
}

void Item_mushroom::collision(Mario* mario,CCArray* arr)
{
	if (mario->boundingBox().intersectsRect(this->boundingBox()))
	{
		float my = mario->getPositionY();
		float item_y = getPositionY();
		float yoff = my - item_y;
		float aa = boundingBox().size.height * 0.6;
		
		if (yoff > aa)
		{
			//���������Ĵ���
			stopAllActions();
			setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
				FRAME_MUSHROOM_DIE1));
			arr->removeObject(this);
			
			CCMoveBy* moveBy = CCMoveBy::create(4, ccp(0, -winSize.width));
			CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Item_mushroom::removeFromParent));
			this->runAction(CCSequence::create(moveBy, callFunc, NULL));
		}
		else
		{
			//mario die
			mario->killed(false);
		}
	}
	else
	{
		//ħ����Ƿ�����ˣ�1���볬��һ������ 2����������
		//��������ˣ��ɵ�
		cleanIfMoveOutofWindow(mario, arr);
	}
}