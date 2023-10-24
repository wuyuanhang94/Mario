#ifndef LAYERSTART_H
#define LAYERSTART_H

#include "Common.h"

class LayerStart : public CCLayer
{
public:
    CREATE_FUNC(LayerStart);
    bool init();

    void onEnter();
    void onExit();

    void Start(CCObject*);
    void Quit(CCObject*);
    void Setting(CCObject*);
    void About(CCObject*);
};

#endif // LAYERSTART_H
