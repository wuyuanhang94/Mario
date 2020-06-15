#include "Item_fire_string.h"
#include "Mario.h"

Item_fire_string::Item_fire_string()
{
}


Item_fire_string::~Item_fire_string()
{
}

bool Item_fire_string::init(CCDictionary* dict)
{
	CCSprite::init();

	const CCString* x = dict->valueForKey("x");
	const CCString* y = dict->valueForKey("y");
	setPosition(ccp(x->intValue(), y->intValue()));
	setAnchorPoint(ccp(0, 0.5));
	setScaleX(0.33f);
	setZOrder(100);
	
	Util::setTexture(this, "fireLeft.png");

	_duration = dict->valueForKey("time")->intValue();
	_angle = dict->valueForKey("begAngle")->intValue();
	if(_angle == 0)
		_angle = 90;

	_isRun = false;

	return true;
}

void Item_fire_string::move(float dt, Mario* mario)
{
	if (!canStartMove() || _isRun)return;
	
	_isRun = true;

	CCRotateBy* r = CCRotateBy::create(_duration, _angle);
	CCRepeatForever* rep = CCRepeatForever::create(r);
	runAction(rep);
}

void Item_fire_string::collision(Mario* mario, CCArray* arr)
{
	//计算两个线段
	//1.mario
	CCRect rc = mario->boundingBox();
	CCPoint marioPt1 = ccp(rc.getMinX(), rc.getMidY());
	CCPoint marioPt2 = ccp(rc.getMaxX(), rc.getMidY());

	//2.fire string
	CCRect rcFs = this->boundingBox();
	CCPoint fsPt1 = getPosition();
	int angle = getRotation();
	angle %= 360;
	CCPoint fsPt2;
	if (angle > 270)
		fsPt2 = ccp(rcFs.getMaxX(), rcFs.getMaxY());
	else if (angle > 180)
		fsPt2 = ccp(rcFs.getMinX(), rcFs.getMaxY());
	else if (angle > 90)
		fsPt2 = ccp(rcFs.getMinX(), rcFs.getMinY());
	else
		fsPt2 = ccp(rcFs.getMaxX(), rcFs.getMinY());
	bool result = ccpSegmentIntersect(marioPt1, marioPt2, fsPt1, fsPt2);
	if (result)
	{
		mario->killed(false);
	}
	cleanIfMoveOutofWindow(mario, arr);
}