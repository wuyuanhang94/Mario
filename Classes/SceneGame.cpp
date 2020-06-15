#include "SceneGame.h"
#include "Item.h"
#include "Item_MushroomReward.h"
#include "Item_boss.h"

SceneGame::SceneGame()
{
	_items = CCArray::create();
	_items->retain();
	_life = 3;
}

SceneGame::~SceneGame()
{
	_items->release();
#ifndef WIN32
    if(_key_fd > 0)
        close(_key_fd);
#endif
}

void SceneGame::onEnter()
{
	CCLayer::onEnter();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("OnLand.wma", true);
}

void SceneGame::onExit()
{
	CCLayer::onExit();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

SceneGame* SceneGame::create(int idx)
{
    SceneGame* p = new SceneGame();
    p->init(idx);
    p->autorelease();
    return p;
}

bool SceneGame::init(int idx)
{
    CCLayer::init();

    //load map
    initMap(idx);

    initCtrlPanel();

    initMario();

    initItems();

#ifndef WIN32
    _key_fd = open(KEY_EVENT_DEV1_NAME, O_RDONLY | O_NONBLOCK);
#endif

    scheduleUpdate();

    return true;
}

void SceneGame::initMap(int idx)
{
	//create map by index
    _mapIdx = idx;
    _map = CCTMXTiledMap::create(Util::format(idx+1,"MarioMap",".tmx"));
    this->addChild(_map);
    Util::moveNode(_map,ccp(0,winSize.height - _map->getContentSize().height));
}

void SceneGame::initCtrlPanel()
{
    CCSprite* uiPanel = Util::addSprite(this,IMAGE_CTRL_UI);
    uiPanel->setAnchorPoint(CCPointZero);
    uiPanel->setPosition(CCPointZero);

    _dir = Util::addSprite(this,IMAGE_DIR_NONE);
    Util::moveNode(_dir,ccp(-180,-110));

    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(IMAGE_DIR_NONE);
    CCSize textureSize = texture->getContentSize();

    CCSprite* spLeft1 = CCSprite::createWithTexture(texture,CCRect(0,0,textureSize.width/2,textureSize.height));
    CCSprite* spLeft2 = CCSprite::createWithTexture(texture,CCRect(0,0,textureSize.width/2,textureSize.height));
    CCSprite* spRight1 = CCSprite::createWithTexture(texture,CCRect(0,0,textureSize.width/2,textureSize.height));
    CCSprite* spRight2 = CCSprite::createWithTexture(texture,CCRect(0,0,textureSize.width/2,textureSize.height));

    Panel* panel = Panel::create();
    this->addChild(panel);
    CCMenuItemSprite* itemLeft = CCMenuItemSprite::create(spLeft1,spLeft2);
    CCMenuItemSprite* itemRight = CCMenuItemSprite::create(spRight1,spRight2);
    panel->addChild(itemLeft);
    panel->addChild(itemRight);

    CCPoint ptOff = _dir->getPosition() - ccp(winSize.width/2,winSize.height/2);
    Util::moveNode(itemLeft, ptOff - ccp(textureSize.width/4,0));
    Util::moveNode(itemRight, ptOff + ccp(textureSize.width/4,0));
    itemLeft->setOpacity(0);
    itemRight->setOpacity(0);

    itemLeft->setTarget(this,menu_selector(SceneGame::marioRun));
    itemRight->setTarget(this,menu_selector(SceneGame::marioRun));

    itemLeft->setTag(DIR_LEFT);
    itemRight->setTag(DIR_RIGHT);

	CCMenuItem* itemJump = Util::createMenuItemRB(this, "AB_normal.png", "AB_select.png",
		this, menu_selector(SceneGame::marioJump));
	_isJump = false;
	Util::moveNode(itemJump, ccp(-12, 10));
}

void SceneGame::marioJump(CCObject* sender)
{
	_mario->jump();
}

void SceneGame::marioRun(CCObject *sender)
{
    CCNode* node = (CCNode*)sender;
    CCLog("run...............%s",node->getTag()==1?"left":"right");
    if(node->getTag() == 1)
        Util::setTexture(_dir,IMAGE_DIR_LEFT);
    else
        Util::setTexture(_dir,IMAGE_DIR_RIGHT);
    _marioDir = (MARIO_DIR)node->getTag();
}

void SceneGame::initMario()
{
    _mario = Mario::create();
	_mario->_game = this;

    _map->addChild(_mario);
    _mario->setZOrder(100);
    _mario->setAnchorPoint(ccp(0,0));

    CCTMXObjectGroup* objs = _map->objectGroupNamed("objects");
    CCArray* arr = objs->getObjects();
    CCObject* obj;
    CCARRAY_FOREACH(arr,obj)
    {
        CCDictionary* dict = (CCDictionary*)obj;
        const CCString* type = dict->valueForKey("type");
        if(type->m_sString == "BirthPoint")
        {
            const CCString* x = dict->valueForKey("x");
            const CCString* y = dict->valueForKey("y");
            _mario->setPosition(ccp(x->intValue(),y->intValue() + 1 - MARIO_TileHeight));
            CCLog("x=%d,y=%d",x->intValue(),y->intValue());
            break;
        }
    }
}

void SceneGame::initItems()
{
	//遍历所有的objects，创建对应的item
	CCTMXObjectGroup* objs = _map->objectGroupNamed("objects");
	CCArray* arr = objs->getObjects();
	CCObject* obj;
	CCARRAY_FOREACH(arr, obj)
	{
		Item* item = NULL;
		CCDictionary* dict = (CCDictionary*)obj;
		const CCString* type = dict->valueForKey("type");
		
		if (type->m_sString == "mushroom")
			 item = Item::create(IT_mushroom, dict);
		else if (type->m_sString == "tortoise")
			item = Item::create(IT_tortoise, dict);
		else if (type->m_sString == "flower")
			item = Item::create(IT_flower, dict);
		else if (type->m_sString == "MushroomReward")
			item = Item::create(IT_MushroomReward, dict);
		else if (type->m_sString == "MushroomAddLife")
			item = Item::create(IT_MushroomAddLife, dict);
		else if (type->m_sString == "flagpoint")
			item = Item::create(IT_flagpoint, dict);
		else if (type->m_sString == "finalpoint")
			item = Item::create(IT_finalpoint, dict);
		else if (type->m_sString == "flyfish")
			item = Item::create(IT_flyfish, dict);
		else if (type->m_sString == "ladderLR")
			item = Item::create(IT_ladderLR, dict);
		else if (type->m_sString == "ladderUD")
			item = Item::create(IT_ladderUD, dict);
		else if (type->m_sString == "tortoise_round")
			item = Item::create(IT_tortoise_round, dict);
		else if (type->m_sString == "tortoise_fly")
			item = Item::create(IT_tortoise_fly, dict);
		else if (type->m_sString == "fire_string")
			item = Item::create(IT_fire_string, dict);
		else if (type->m_sString == "boss")
		{
			item = Item::create(IT_boss, dict);
			Item_boss* boss = reinterpret_cast<Item_boss*>(item);
			boss->_arr = this->_items;
		}
		else if (type->m_sString == "bridgestartpos")
			item = Item::create(IT_bridgestartpos, dict);
		else if (type->m_sString == "addmushroom")
			item = Item::create(IT_addmushroom, dict);
		else if (type->m_sString == "darkcloud")
			item = Item::create(IT_darkcloud, dict);
		else if (type->m_sString == "battery")
			item = Item::create(IT_battery, dict);
		
		if (item)
		{
			_items->addObject(item);
			_map->addChild(item);
		}
	}
}

#ifdef WIN32
void SceneGame::getKeyPress()
{
    if(GetKeyState('D') < 0)
    {
        _marioDir = DIR_RIGHT;
        if(GetKeyState('A') < 0)
        {
            _marioDir = DIR_NONE;
            return;
        }
    }
    else if(GetKeyState('A') < 0)
    {
        _marioDir = DIR_LEFT;
    }
	if (GetKeyState('J') < 0)
	{
		_mario->jump();
	}
}

#else
void SceneGame::getKeyCallback()
{
    int l_ret;
    struct input_event key_event  = {0};

    if(_key_fd <= 0)
    {
        printf("---open /dev/input/event1 device error!---\n");
        return;
    }

    l_ret = lseek(_key_fd, 0, SEEK_SET);
    l_ret = read(_key_fd, &key_event, sizeof(key_event));

    if(l_ret)
    {
        if(key_event.type == EV_KEY
                && (key_event.value == 0 || key_event.value == 1))
        {
            if(key_event.code == 32)
                _marioDir = DIR_RIGHT;
            else if (key_event.code == 30) {
                _marioDir = DIR_LEFT;
            }
        }
    }
}

#endif

void SceneGame::EatCoin()
{
	CCRect rcMario = _mario->boundingBox();
	CCPoint pt[4];
	pt[0] = ccp(rcMario.getMinX(), rcMario.getMinY());
	pt[1] = ccp(rcMario.getMinX(), rcMario.getMaxY());
	pt[2] = ccp(rcMario.getMaxX(), rcMario.getMinY());
	pt[3] = ccp(rcMario.getMaxX(), rcMario.getMaxY());

	for (int i = 0; i<4 ; i++)
	{
		int gid = Common::getGID(pt[i], this->_map, "coin");
		if (gid > 0)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("EatCoin.wma");
			Common::setGID(pt[i], this->_map, "coin", 0);
		}
	}
}

void SceneGame::update(float dt)
{
#ifdef WIN32
    getKeyPress();
#else
    getKeyCallback();
#endif

	if (dt >= 0.08f)
	{
		dt = 1.0f / 60;
	}

    if(_marioDir != DIR_NONE)
    {
        _mario->run(_marioDir,dt);
        _marioDir = DIR_NONE;
    }
    else
    {
        _mario->stop();
    }

	_mario->moveUp(dt);
	_mario->moveDown(dt);
	_mario->moveAutoCtrl(dt);

	EatCoin();

	int itemCount = _items->count();
	for (int i = itemCount - 1; i >= 0; --i)
	{
		Item* item = (Item*)_items->objectAtIndex(i);
		item->move(dt,_mario);
		item->collision(_mario,_items);
	}
}

void SceneGame::removeCoin(CCNode* coin, void* p)
{
	CCPoint* pt = (CCPoint*)p;
	Common::setGID(*pt + ccp(0, 8), _map, "coin", 0);
	delete pt;
}

void SceneGame::hitBlock(CCSprite* block, int gid, const char* layername)
{
	if (strcmp(layername, "land") == 0)
		return;
	if (strcmp(layername, "pipe") == 0)
		return;

	CCObject* obj;
	CCARRAY_FOREACH(_items, obj)
	{
		Item* item = (Item*)obj;
		if (item->_type != IT_MushroomReward && item->_type != IT_MushroomAddLife)
			continue;
		if (item->boundingBox().intersectsRect(block->boundingBox()))
		{
			Item_MushroomReward* itemM = (Item_MushroomReward*)item;
			if (itemM->_status == Item_MushroomReward::MR_STATUS_INIT)
			{
				itemM->_status = Item_MushroomReward::MR_STATUS_GROW;
				itemM->updateStatus();
				Common::setGID(block->getPosition() + ccp(0, 8), _map, "block", 32);
				return;
			}
		}
	}

	//Common::setGID(block->getPosition() + ccp(0,8), _map, "block", 32);
	if (gid == 1)
	{
		if (_mario->_isBig)
		{
			//碎了
			block->runAction(CCJumpBy::create(.1f, ccp(0, 0), 30, 1));
		}
		else
		{
			//动一下
			block->runAction(CCJumpBy::create(.1f, ccp(0, 0), 30, 1));
		}
	}
	else if (gid == 601)//带问号的砖头 加金币661
	{
		CCSprite* coin = NULL;
		Common::setGID(block->getPosition() + ccp(0, 8), _map, "coin", 661);
		Common::getGID(block->getPosition() + ccp(0, 8), _map, "coin", &coin);

		CCPoint* p = new CCPoint(block->getPosition());
		CCMoveBy* moveBy = CCMoveBy::create(.1f, ccp(0, 50));
		CCCallFuncND* call = CCCallFuncND::create(this, callfuncND_selector(SceneGame::removeCoin), p);
		CCSequence* seq = CCSequence::create(moveBy, call, NULL);
		coin->runAction(seq);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("EatCoin.wma");
		Common::setGID(block->getPosition() + ccp(0, 8), _map, "block", 32);
	}
	else if (gid == 846)//隐藏砖头 不用处理
	{

	}
}