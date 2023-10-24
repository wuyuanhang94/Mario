#include "LayerGame.h"
#include "Mario.h"
#include "LayerDirCtrl.h"

void LayerGame::onEnter()
{
    CCLayer::onEnter();
    loadMap();

    addControls();

    loadResources();

    initMario();
}

void LayerGame::onExit()
{
    CCLayer::onEnter();
}

void LayerGame::addControls()
{
    CCNode* node = Util::addBackground(IMAGE_CONTROL_UI, this);
    node->setPosition(ccp(0, 0));
    node->setAnchorPoint(ccp(0, 0));
}

void LayerGame::loadMap()
{
    const char* mapFile = Util::format(_mapIndex + 1, "MarioMap", ".tmx");
    _map = CCTMXTiledMap::create(mapFile);
    addChild(_map);

    _map->setPositionY(getPositionY() + winSize.height - _map->getContentSize().height);
}

void LayerGame::loadResources()
{
    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(IMAGE_SMALL_WALK_RIGHT);
    for(int i=0;i<11;i++)
    {
        CCSpriteFrame* frame = CCSpriteFrame::createWithTexture(texture, CCRect(i*14, 0, 14, 16));
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, Util::format(i+1, FRAME_SMALL_WALK_RIGHT_FORMAT));
    }
}

void LayerGame::initMario()
{
    _mario = Mario::create();
    _map->addChild(_mario);
    _mario->setZOrder(1000);

    CCTMXObjectGroup* objGroup = _map->objectGroupNamed("objects");

    CCArray* objects = objGroup->getObjects();
    CCObject* obj;
    CCARRAY_FOREACH(objects, obj)
    {
        CCDictionary* dict = (CCDictionary*)obj;
        if (dict->valueForKey("type")->m_sString == "BirthPoint")
        {
            const CCString* x = dict->valueForKey("x");
            const CCString* y = dict->valueForKey("y");

            _mario->setAnchorPoint(ccp(0, 0));
            _mario->setPosition(ccp(x->intValue(), y->intValue() - 16));
            break;
        }
    }
}