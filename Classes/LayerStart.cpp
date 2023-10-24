#include "LayerStart.h"
#include "LayerMenu.h"

void LayerStart::onEnter()
{
    CCLayer::onEnter();

    Util::addBackground(IMAGE_BACKGROUND, this);

    CCMenuItem* itemStart = CCMenuItemImage::create(IMAGE_START_1, IMAGE_START_2, this, menu_selector(LayerStart::Start));
    CCMenuItem* itemQuit = CCMenuItemImage::create(IMAGE_QUIT_1, IMAGE_QUIT_2, this, menu_selector(LayerStart::Quit));
    CCMenuItem* itemSetting = CCMenuItemImage::create(IMAGE_SETTING_1, IMAGE_SETTING_2, this, menu_selector(LayerStart::Setting));
    CCMenuItem* itemAbout = CCMenuItemImage::create(IMAGE_ABOUT_1, IMAGE_ABOUT_2, this, menu_selector(LayerStart::About));

    CCMenu* menu = CCMenu::create(itemStart, itemQuit, itemSetting, itemAbout, NULL);
    addChild(menu);

    menu->alignItemsVertically();

    CCArray* items = menu->getChildren();
    CCObject* obj;
    CCARRAY_FOREACH(items, obj)
    {
        CCNode* node = (CCNode*)obj;
        Util::moveNode(node, ccp(0, -70));
    }
    Util::moveNode(itemAbout, ccp(150, 0));
}

void LayerStart::onExit()
{
    CCLayer::onExit();
}

void LayerStart::Start(CCObject *)
{
    switchScene(LayerMenu);
}

void LayerStart::About(CCObject *)
{

}

void LayerStart::Setting(CCObject *)
{

}

void LayerStart::Quit(CCObject *)
{
    exit(0);
}

bool LayerStart::init()
{
    CCLayer::init();
    return true;
}
