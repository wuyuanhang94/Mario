#ifndef MARIO_H
#define MARIO_H

#include "Common.h"

class SceneGame;

class Mario : public CCSprite
{
public:
    Mario();
    ~Mario();

	SceneGame* _game;

    CREATE_FUNC(Mario);
    bool init();

	bool _autoCtrl;
	bool _isTouchFlag;
    bool _isBig;
    bool _isFire;
    bool _isGod;
    bool _isDead;
    bool _isAir;
    bool _isGetFlag;
    int _speed;
    int _speedUp;
    int _speedDown;
    int _gravity;
    MARIO_DIR _runDir;
    MARIO_DIR _faceTo;

    void updateMario();

    CCTMXTiledMap* getMap()
    {
        return (CCTMXTiledMap*)this->getParent();
    }

    void run(MARIO_DIR dir,float dt);
	void runLeft(float dt);
	void runRight(float dt);
    void stop();
	void jump();
	void moveUp(float dt);
	void moveDown(float dt);
	void land();
	void moveAutoCtrl(float dt);

	void eatMushroom(ITEM_TYPE mushroomtype);
	
	void killed(bool over);
	void touchFlag();
	void autoCtrl();
	bool _onLadder;
	void setOnLadder(bool on)
	{
		_onLadder = on;
	}
	void setNoGod(float dt)
	{
		_isGod = false;
	}

	bool canMoveDown(float dt);
	bool canMoveUp(float dt, CCSprite*& blockSprite,const char*& layerName,int& gid);
	bool canMoveLeft(float dt);
	bool canMoveRight(float dt);
	
};

#endif // MARIO_H
