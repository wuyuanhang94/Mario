#include "Mario.h"
#include "SceneGame.h"

Mario::Mario()
{
}

Mario::~Mario()
{

}

bool Mario::init()
{
    CCSprite::init();

	_autoCtrl = false;
	_isTouchFlag = false;
    _isBig = false;
    _isFire = false;
    _isGod = false;
    _isDead = false;
    _isAir = false;
    _isGetFlag = false;
    _speed = 200;
    _speedUp = 0;
    _speedDown = 0;
    _gravity = 10;
    _runDir = DIR_NONE;
    _faceTo = DIR_RIGHT;
	_onLadder = false;

    updateMario();

    return true;
}

void Mario::updateMario()
{
    this->stopAllActions();

	if (this->_isTouchFlag)
	{
		return;
	}

    if(this->_isBig)
    {
        if(this->_isAir)
        {
			if (this->_faceTo == DIR_LEFT)
				this->setDisplayFrame(
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(FRAME_MARIO_BIG_LEFT));
			else
				this->setDisplayFrame(
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(FRAME_MARIO_BIG_RIGHT));
        }
        else
        {
			if (this->_runDir == DIR_NONE)
			{
				if (this->_faceTo == DIR_LEFT)
				{
					//display image facing left
					this->setDisplayFrameWithAnimationName(ANI_MARION_BIG_RUN_LEFT, 0);
				}
				else
				{
					//display image facing right
					this->setDisplayFrameWithAnimationName(ANI_MARION_BIG_RUN_RIGHT, 0);
				}
			}
			else
			{
				if (this->_runDir == DIR_LEFT)
				{
					//play walking aniamtion toward left
					CCAnimate* animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName(ANI_MARION_BIG_RUN_LEFT));
					this->runAction(CCRepeatForever::create(animate));
				}
				else
				{
					//play walking aniamtion toward right
					CCAnimate* animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName(ANI_MARION_BIG_RUN_RIGHT));
					this->runAction(CCRepeatForever::create(animate));
				}
			}
        }
    }
    else
    {
        if(this->_isAir)
        {
#if 1
			if (this->_faceTo == DIR_LEFT)
				this->setDisplayFrame(
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(FRAME_MARIO_SMALL_LEFT));
			else
				this->setDisplayFrame(
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(FRAME_MARIO_SMALL_RIGHT));
#endif
        }
        else
        {
            if(this->_runDir == DIR_NONE)
            {
                if(this->_faceTo == DIR_LEFT)
                {
                    //display image facing left
                    this->setDisplayFrameWithAnimationName(ANI_MARION_SMALL_RUN_LEFT,0);
                }
                else
                {
                    //display image facing right
                    this->setDisplayFrameWithAnimationName(ANI_MARION_SMALL_RUN_RIGHT,0);
                }
            }
            else
            {
                if(this->_runDir == DIR_LEFT)
                {
                    //play walking aniamtion toward left
                    CCAnimate* animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName(ANI_MARION_SMALL_RUN_LEFT));
                    this->runAction(CCRepeatForever::create(animate));
                }
                else
                {
                    //play walking aniamtion toward right
                    CCAnimate* animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName(ANI_MARION_SMALL_RUN_RIGHT));
                    this->runAction(CCRepeatForever::create(animate));
                }
            }
        }
    }
}

void Mario::moveAutoCtrl(float dt)
{
	if (!this->_autoCtrl)
		return;
	MARIO_DIR dir = DIR_RIGHT;
	if (_faceTo != dir || _runDir != dir)
	{
		_faceTo = dir;
		_runDir = dir;
		updateMario();
	}
	runRight(dt);
}

void Mario::run(MARIO_DIR dir, float dt)
{
	if (this->_autoCtrl)
	{
		return;
	}
	//if the current state of Mario is different from the last one, then update
	if (_faceTo != dir || _runDir != dir)
	{
		_faceTo = dir;
		_runDir = dir;
		updateMario();
	}
	if (_runDir == DIR_LEFT) runLeft(dt);
	else if (_runDir == DIR_RIGHT) runRight(dt);
}

void Mario::stop()
{
    if(_runDir != DIR_NONE)
    {
        _runDir = DIR_NONE;
        updateMario();
    }
}

void Mario::jump()
{
	if (this->_isAir || this->_autoCtrl)
		return;

	setOnLadder(false);

	this->_speedUp = MARIO_START_JUMP_SPEED;
	this->_gravity = 10;
	_isAir = true;
	updateMario();
}

bool Mario::canMoveUp(float dt, CCSprite*& blockSprite, const char*& layerName, int& gid)
{
	CCRect rc = this->boundingBox();
	float yoff = dt *_speedUp;

	CCPoint pt[3];
	pt[1] = ccp(rc.getMinX(), rc.getMaxY() + yoff);
	pt[0] = ccp(rc.getMidX(), rc.getMaxY() + yoff);
	pt[2] = ccp(rc.getMaxX(), rc.getMaxY() + yoff);

	if (Common::isBlock3Point(pt, getMap(), &blockSprite, &layerName, &gid))
	{
		return false;
	}

	return true;
}

void Mario::moveUp(float dt)
{
	if (_speedUp <= 0)
		return;

	CCSprite* blockSprite;
	const char* layerName;
	int gid;

	if (!canMoveUp(dt,blockSprite,layerName,gid))
	{
		//如果不能move up，应该做什么？
		//1.下降
		_speedDown = _speedUp;
		_speedUp = 0;
		//2.头顶的那个精灵交给SceneGame处理
//		blockSprite->runAction(CCJumpBy::create(.2f, ccp(0, 0), 30, 1));
		_game->hitBlock(blockSprite, gid, layerName);
		return;
	}

	setPositionY(getPositionY() + dt*_speedUp);
	_speedUp -= _gravity;
}

void Mario::land()
{
	if (_isAir)
	{
		_isAir = false;
		_speedDown = 0;
		updateMario();
	}

	if (_isTouchFlag)
	{
		_isTouchFlag = false;
		updateMario();
	}
}

bool Mario::canMoveDown(float dt)
{
	//如果mario在梯子上，不能往下移动
	if (_onLadder)return false;
	//获取Mario外围矩形
	//让外围矩形往下移动一段距离，距离=dt*_speedDown
	//判断外围矩形下面三个点，是否接触到障碍物
	CCRect rc = this->boundingBox();
	float yoff = dt *_speedDown;

	CCPoint pt[3];
	pt[1] = ccp(rc.getMinX(), rc.getMinY() - yoff);
	pt[0] = ccp(rc.getMidX(), rc.getMinY() - yoff);
	pt[2] = ccp(rc.getMaxX(), rc.getMinY() - yoff);

	if (Common::isBlock3Point(pt,getMap()))
	{
		return false;
	}
	return true;
}

bool Mario::canMoveLeft(float dt)
{
	if (_isTouchFlag)
		return false;
	CCRect rc = this->boundingBox();
	float xoff = dt *_speed;

	CCPoint pt[3];
	pt[1] = ccp(rc.getMinX() - xoff, rc.getMinY());
	pt[0] = ccp(rc.getMinX() - xoff, rc.getMidY());
	pt[2] = ccp(rc.getMinX() - xoff, rc.getMaxY());

	if (Common::isBlock3Point(pt, getMap()))
		return false;

	if (Util::isOutofWindow(getMap()->convertToWorldSpace(pt[0])))
		return false;

	return true;
}

bool Mario::canMoveRight(float dt)
{
	if (_isTouchFlag)
		return false;
	//get three right points of Mario
	CCRect rc = this->boundingBox();
	float xoff = dt *_speed;

	CCPoint pt[3];
	pt[1] = ccp(rc.getMaxX() + xoff, rc.getMinY());
	pt[0] = ccp(rc.getMaxX() + xoff, rc.getMidY());
	pt[2] = ccp(rc.getMaxX() + xoff, rc.getMaxY());

	if (Common::isBlock3Point(pt, getMap()))
	{
		return false;
	}

	if (Util::isOutofWindow(getMap()->convertToWorldSpace(pt[0])))
	{
		return false;
	}

	return true;
}

void Mario::moveDown(float dt)
{
	if (_speedUp > 0)
		return;

	if (!canMoveDown(dt))
	{
		land();//着陆，因为天上是天上的状态，land后是着陆的状态
		return;
	}

	setPositionY(getPositionY() - dt * _speedDown);
	_speedDown += _gravity;
}

void Mario::runRight(float dt)
{
	//check whther Mario can move right
	if (!canMoveRight(dt))
		return;

	int xoff = dt * _speed;
	Util::moveNode(this, ccp(xoff, 0));

	CCTMXTiledMap* map = getMap();
	CCPoint mapLast = ccp(map->getContentSize().width, 0);
	CCPoint ptMapLastInWorld = map->convertToWorldSpace(mapLast);
	if (ptMapLastInWorld.x <= winSize.width)
		return;

	CCPoint ptMario = this->getPosition();
	CCPoint ptInWorld = getMap()->convertToWorldSpace(ptMario);

	if(Util::isInWindow(ptMapLastInWorld))//the last point of map is already in map, illustrating map ends.
		return;

	if (ptInWorld.x > winSize.width / 2)
	{
		Util::moveNode(getMap(), ccp(-xoff, 0));
	}
}

void Mario::runLeft(float dt)
{
	if (!canMoveLeft(dt))
		return;

	int xoff = dt * _speed;
	Util::moveNode(this, ccp(-xoff, 0));
}

void Mario::eatMushroom(ITEM_TYPE mushroomType)
{
	if (mushroomType == IT_MushroomReward)
	{
		if (!_isBig)
		{
			_isBig = true;
			updateMario();
		}
	}
	else if (mushroomType == IT_MushroomAddLife)
	{
		_game->_life++;
	}
}

void Mario::killed(bool over)
{
	if (_isGod && !over)return;

	if (over || !_isBig)
	{
		return;
	}
	_isGod = true;
	_isBig = false;
	updateMario();

	scheduleOnce(schedule_selector(Mario::setNoGod), 1.0f);
}

void Mario::touchFlag()
{
	if (_isTouchFlag)
		return;
	_isTouchFlag = true;
	updateMario();
}

void Mario::autoCtrl()
{
	_autoCtrl = true;
}