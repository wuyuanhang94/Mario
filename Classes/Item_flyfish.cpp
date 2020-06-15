#include "Item_flyfish.h"
#include "Mario.h"

Item_flyfish::Item_flyfish()
{
}


Item_flyfish::~Item_flyfish()
{
}

bool Item_flyfish::init(CCDictionary* dict)
{
	CCSprite::init();

	_body = CCSprite::create();
	this->addChild(_body);

	const CCString* duration = dict->valueForKey("duration");
	const CCString* offsetH = dict->valueForKey("offsetH");
	const CCString* offsetV = dict->valueForKey("offsetV");
	_duration = duration->intValue();
	_offsetH = offsetH->intValue();
	_offsetV = offsetV->intValue();
	_dir = DIR_LEFT;
	_runFlag = false;
	_removeFlag = false;

	const CCString* x = dict->valueForKey("x");
	const CCString* y = dict->valueForKey("y");
	setPosition(ccp(x->intValue(), y->intValue() - MARIO_TileHeight));
	setAnchorPoint(ccp(0, 0));
	setZOrder(100);

	updateStatus();

	return true;
}

void Item_flyfish::updateStatus()
{
	stopAllActions();
	if (_dir == DIR_LEFT)
	{
		CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(ANI_FLYFISH_LEFT);
		CCAnimate* animate = CCAnimate::create(animation);
		_body->runAction(CCRepeatForever::create(animate));
	}
	else
	{
		CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(ANI_FLYFISH_RIGHT);
		CCAnimate* animate = CCAnimate::create(animation);
		_body->runAction(CCRepeatForever::create(animate));
	}
}

void Item_flyfish::move(float dt, Mario* mario)
{
	if (_runFlag)
		return;

	CCPoint ptNode = Util::getPositionLB(this);
	CCPoint ptWorld = getMap()->convertToWorldSpace(ptNode);
	if (Util::isOutofWindow(ptWorld))
	{
		return;
	}

	_runFlag = true;

	int mapHeight = MARIO_TileHeight * 28;
	cocos2d::ccBezierConfig cfg;
	cfg.endPosition = ccp(-_offsetH, _offsetV);
	cfg.controlPoint_1 = ccp(-CCRANDOM_0_1()*_offsetH, CCRANDOM_0_1()*(mapHeight - _offsetV) + _offsetV);
	cfg.controlPoint_2 = ccp(-CCRANDOM_0_1()*_offsetH, CCRANDOM_0_1()*(mapHeight - _offsetV) + _offsetV);
	CCBezierBy* bezierBy = CCBezierBy::create(_duration, cfg);

	cfg.endPosition = ccp(-_offsetH, -_offsetV);
	cfg.controlPoint_1 = ccp(-CCRANDOM_0_1() *_offsetH, CCRANDOM_0_1()*_offsetV);
	cfg.controlPoint_2 = ccp(-CCRANDOM_0_1() *_offsetH, CCRANDOM_0_1()*_offsetV);
	CCBezierBy* bezierBy2 = CCBezierBy::create(_duration, cfg);

	CCCallFunc* callfunc = CCCallFunc::create(this, callfunc_selector(Item_flyfish::setRemoveFlag));

	this->runAction(CCSequence::create(bezierBy, bezierBy2, callfunc, NULL));
}

void Item_flyfish::collision(Mario* mario, CCArray* arr)
{
	if (isCollisionWithMario(mario))
	{
		//要考虑马里奥无敌状态
		mario->killed(false);
		return;
	}
	if (_removeFlag)
	{
		arr->removeObject(this);
		this->removeFromParent();
	}
}