#ifndef SCENEGAME_H
#define SCENEGAME_H

#include "Mario.h"

class SceneGame:public CCLayer
{
public:
    SceneGame();
    ~SceneGame();

	void onEnter() override;
	void onExit() override;
	void EatCoin();
	void removeCoin(CCNode* coin, void* p);

    static SceneGame* create(int idx);

    bool init(int idx);
    void initMap(int idx);
    void initCtrlPanel();
    void initMario();
    void initItems();

    void marioRun(CCObject* sender);
	void marioJump(CCObject* sender);

    CCTMXTiledMap* _map;
    int _mapIdx;
    CCSprite* _dir;
    Mario* _mario;
	int _life;
    MARIO_DIR _marioDir;
	bool _isJump;
	CCArray* _items;

	void hitBlock(CCSprite* block,int gid, const char* layername);

    void update(float dt);

#ifdef WIN32
    void getKeyPress();
#else
    void getKeyCallback();
    int _key_fd;
#endif
};

#endif // SCENEGAME_H
