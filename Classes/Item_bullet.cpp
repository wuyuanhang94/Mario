#include "Item_bullet.h"
#include "Item_boss.h"
#include "Mario.h"

Item_bullet::Item_bullet()
{
}


Item_bullet::~Item_bullet()
{
}

bool Item_bullet::init(CCDictionary* dict)
{
	CCSprite::init();
	return true;
}

void Item_bullet::initBullet(Item_boss* boss)
{
	//设置初始位置
	//把子弹加入地图
	//运动
	CCTMXTiledMap* map = boss->getMap();
	map->addChild(this);
	_dir = boss->_dir;

	if(_dir == DIR_LEFT)
	{
		CCPoint pt = Util::getPositionLB(boss);
		setPosition(pt + ccp(0, 30));
		CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(ANI_BOSS_BULLET_LEFT);
		CCAnimate* animate = CCAnimate::create(animation);
		runAction(CCRepeatForever::create(animate));
	}
	else
	{
		CCPoint pt = Util::getPositionRB(boss);
		setPosition(pt + ccp(0, 30));
		CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(ANI_BOSS_BULLET_RIGHT);
		CCAnimate* animate = CCAnimate::create(animation);
		runAction(CCRepeatForever::create(animate));
	}
}

void Item_bullet::move(float dt, Mario* mario)
{
	if (_dir == DIR_LEFT)
	{
		setPositionX(getPositionX() - dt * 100);
	}
	else
	{
		setPositionX(getPositionX() + dt * 100);
	}
}

void Item_bullet::collision(Mario* mario, CCArray* arr)
{
	if (this->getPositionX() < 0 || 
		this->getPositionX() > getMap()->getContentSize().width)
	{
		this->removeFromParent();
		arr->removeObject(this);
		return;
	}
	if (isCollisionWithMario(mario))
	{
		mario->killed(false);
	}
}