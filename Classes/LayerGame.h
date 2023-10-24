#ifndef LAYERGAME_H
#define LAYERGAME_H

#include "Common.h"
#include "Mario.h"

class LayerGame : public CCLayer
{
public:
    static LayerGame* create(int index)
    {
        LayerGame* layer = new LayerGame;
        layer->autorelease();
        layer->init();
        layer->setMapIndex(index);
        return layer;
    }

    void onEnter();
    void onExit();

    void loadMap();
    void addControls();
    void loadResources();
    void initMario();

    CC_SYNTHESIZE(int, _mapIndex, MapIndex);
    CC_SYNTHESIZE(CCTMXTiledMap*, _map, TileMap);
    CC_SYNTHESIZE(Mario*, _mario, Mario);
};

#endif // LAYERGAME_H
