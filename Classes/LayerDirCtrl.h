#ifndef LAYERDIRCTRL_H
#define LAYERDIRCTRL_H

#include "Common.h"
#include "LayerDirCtrlDelegate.h"

class LayerDirCtrl : public CCLayer
{
public:
    CREATE_FUNC(LayerDirCtrl);

    void onEnter();
    void onExit();

    CCSprite* _sprite;

    CC_SYNTHESIZE(LayerDirCtrlDelegate*, _delegate, Delegate);

    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
};

#endif // LAYERDIRCTRL_H
