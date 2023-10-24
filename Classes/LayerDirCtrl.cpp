#include "LayerDirCtrl.h"

void LayerDirCtrl::onEnter()
{
    CCLayer::onEnter();

    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("backKeyImage.png");
    _frameNone = CCSpriteFrame::createWithTexture(
                texture, CCRect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
    _frameNone->retain();

    texture = CCTextureCache::sharedTextureCache()->addImage("backKeyLeft.png");
    _frameLeft = CCSpriteFrame::createWithTexture(
                texture, CCRect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
    _frameLeft->retain();

    texture = CCTextureCache::sharedTextureCache()->addImage("backKeyRight.png");
    _frameRight = CCSpriteFrame::createWithTexture(
                texture, CCRect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
    _frameRight->retain();


    _sprite = CCSprite::create();
    _sprite->setDisplayFrame(_frameNone);
    addChild(_sprite);
    _sprite->setPosition(ccp(100, 100));
}

void LayerDirCtrl::onExit()
{
    CCLayer::onExit();
    _frameNone->release();
    _frameLeft->release();
    _frameRight->release();
}

bool LayerDirCtrl::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}

void LayerDirCtrl::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{}

void LayerDirCtrl::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}
