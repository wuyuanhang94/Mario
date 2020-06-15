#include "SceneStart.h"
#include "SceneMenu.h"

SceneStart::SceneStart()
{
}

SceneStart::~SceneStart()
{
}

bool SceneStart::init()
{
    CCLayer::init();

    Util::addSprite(this,IMAGE_BG);

    CCMenuItemImage* menuItemStart = CCMenuItemImage::create(
                IMAGE_START_GAME_NORMAL,
                IMAGE_START_GAME_SELECT,
                this,menu_selector(SceneStart::Start));

    CCMenuItemImage* menuItemQuit = CCMenuItemImage::create(
                IMAGE_QUIT_GAME_NORMAL,
                IMAGE_QUIT_GAME_SELECT,
                this,menu_selector(SceneStart::Quit));

    CCMenuItemImage* menuItemSetting = CCMenuItemImage::create(
                IMAGE_SETTING_NORMAL,
                IMAGE_SETTING_SELECT,
                this,menu_selector(SceneStart::Setting));

    CCMenuItemImage* menuItemAbout = CCMenuItemImage::create(
                IMAGE_ABOUT_NORMAL,
                IMAGE_ABOUT_SELECT,
                this,menu_selector(SceneStart::About));

    CCMenu* menu = CCMenu::create(menuItemStart,menuItemQuit,menuItemSetting,menuItemAbout,NULL);
    this->addChild(menu);

    menu->alignItemsVerticallyWithPadding(-5);
    Util::moveNode(menu,ccp(0,-50));

    Util::moveNode(menuItemAbout,ccp(180,-40));

    return true;
}

void SceneStart::Start(CCObject*)
{
    Util::replaceLayer(SceneMenu::create());
}

void SceneStart::Quit(CCObject*)
{

}

void SceneStart::Setting(CCObject*)
{

}

void SceneStart::About(CCObject*)
{

}
