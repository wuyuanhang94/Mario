#include "Item_tortoise.h"
#include "Mario.h"

Item_tortoise::Item_tortoise()
{
}


Item_tortoise::~Item_tortoise()
{
}

bool Item_tortoise::init(CCDictionary* dict)
{
	CCSprite::init();

	_needCollision = true;
	
	//�����ڹ��λ�ú�ê��
	const CCString* x = dict->valueForKey("x");
	const CCString* y = dict->valueForKey("y");
	setPosition(ccp(x->intValue(), y->intValue() + 1));
	Util::moveNode(this, ccp(0, -MARIO_TileHeight));//�����ڹ�ĸ�ͷ�ȵ�ͼ����Ҫ��
	
	setAnchorPoint(ccp(0, 0));
	setZOrder(100);

	_status = STATUS_MOVE;

	return true;
}

void Item_tortoise::move(float dt, Mario* mario)
{
	if (_status == STATUS_STOP) return;

	if (_dir == DIR_LEFT)
		moveLeft(dt);
	else
		moveRight(dt);
	moveDown(dt);
}

void Item_tortoise::collision(Mario* mario, CCArray* arr)
{
	//�����Ƿ���Ҫ����ײ���ı�ǣ���������ֿ���������ײΪtrue
	if (mario->boundingBox().intersectsRect(this->boundingBox()))
	{
		if (!_needCollision)
			return;
	}
	else
	{
		_needCollision = true;
		return;
	}

	if (_status == STATUS_MOVE)
	{
		//��ͨ�ĳ�ͻ����Ģ���ĳ�ͻ���
		float yoff = mario->getPositionY() - this->getPositionY();
		if (yoff > this->boundingBox().size.height*0.6)
		{
			_status = STATUS_STOP;
			updateStatus();
		}
		else
		{
			//mario�ҵ�
			mario->killed(false);
		}
		_needCollision = false;
	}
	else if (_status == STATUS_STOP)
	{
		float xoff = mario->getPositionX() - this->getPositionX();
		if (xoff > 0)
			_dir = DIR_LEFT;
		else
			_dir = DIR_RIGHT;
		_status = STATUS_SPEED;
		_speed *= 4;
		updateStatus();
		_needCollision = false;
	}
	else if (_status == STATUS_SPEED)
	{
		float yoff = mario->getPositionY() - this->getPositionY();
		if (yoff > this->boundingBox().size.height*0.6)
		{
			arr->removeObject(this);
			CCMoveBy* moveBy = CCMoveBy::create(4, ccp(0, -winSize.width));
			CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(
				Item_tortoise::removeFromParent));
			this->runAction(CCSequence::create(moveBy, callFunc, NULL));
		}
		else
		{
			//mario�ҵ�
			mario->killed(false);
		}
	}
}

void Item_tortoise::updateStatus()
{
	stopAllActions();
	if (_status == STATUS_MOVE)
	{
		//��ͨ�ĳ�ͻ����ħ��ĳ�ͻ���
		CCAnimation* animation;
		if (_dir == DIR_LEFT)
			animation = CCAnimationCache::sharedAnimationCache()->animationByName(ANI_TORTOISE_RUN_LEFT);
		else
			animation = CCAnimationCache::sharedAnimationCache()->animationByName(ANI_TORTOISE_RUN_RIGHT);
		CCAnimate* animate = CCAnimate::create(animation);
		runAction(CCRepeatForever::create(animate));
	}
	else if (_status == STATUS_STOP)
	{
		CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(ANI_TORTOISE_STOP);
		CCAnimate* animate = CCAnimate::create(animation);
		runAction(CCRepeatForever::create(animate));
	}
	else if (_status == STATUS_SPEED)
	{
		CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(ANI_TORTOISE_STOP);
		CCAnimate* animate = CCAnimate::create(animation);
		runAction(CCRepeatForever::create(animate));
	}
}