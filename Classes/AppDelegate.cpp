#include "AppDelegate.h"
#include "SceneStart.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::loadResources()
{
    Common::loadMarioAnimation(IMAGE_MARIO_BIG_LEFT,18,32,10,ANI_MARION_BIG_RUN_LEFT,0.05f);
    Common::loadMarioAnimation(IMAGE_MARIO_BIG_RIGHT,18,32,10,ANI_MARION_BIG_RUN_RIGHT,0.05f);
    Common::loadMarioAnimation(IMAGE_MARIO_SMALL_LEFT,14,16,10,ANI_MARION_SMALL_RUN_LEFT,0.05f);
    Common::loadMarioAnimation(IMAGE_MARIO_SMALL_RIGHT,14,16,10,ANI_MARION_SMALL_RUN_RIGHT,0.05f);

    Common::loadMarioSpriteFrame(IMAGE_MARIO_BIG_LEFT,18,32,10,FRAME_MARIO_BIG_LEFT);
    Common::loadMarioSpriteFrame(IMAGE_MARIO_BIG_RIGHT,18,32,10,FRAME_MARIO_BIG_RIGHT);
    Common::loadMarioSpriteFrame(IMAGE_MARIO_SMALL_LEFT,14,16,10,FRAME_MARIO_SMALL_LEFT);
    Common::loadMarioSpriteFrame(IMAGE_MARIO_SMALL_RIGHT,14,16,10,FRAME_MARIO_SMALL_RIGHT);

	Common::loadMarioAnimation("Mushroom0.png", 16, 16, 2, ANI_MUSHROOM_RUN, .1f);
	Common::loadMarioSpriteFrame("Mushroom0.png", 16, 16, 2, FRAME_MUSHROOM_DIE1);
	Common::loadMarioSpriteFrame("Mushroom0.png", 16, 16, 3, FRAME_MUSHROOM_DIE2);

	Common::loadMarioAnimation("tortoise0.png", 18, 24, 4, ANI_TORTOISE_RUN_LEFT, .1f);
	Common::loadMarioAnimation("tortoise0.png", 18, 24, 4, ANI_TORTOISE_RUN_RIGHT, .1f,4);
	Common::loadMarioAnimation("tortoise0.png", 18, 24, 2, ANI_TORTOISE_STOP, .1f, 8);

	Common::loadMarioAnimation("flower0.png", 16, 24, 2, ANI_FLOWER,.1f);

	Common::loadMarioSpriteFrame("rewardMushroomSet.png", 16, 16, 0, FRAME_MUSHROOM_REWARD);
	Common::loadMarioSpriteFrame("rewardMushroomSet.png", 16, 16, 1, FRAME_MUSHROOM_ADDLIFE);
	Common::loadMarioSpriteFrame("rewardMushroomSet.png", 16, 16, 2, FRAME_MUSHROOM_GOD);

	//Ô¤¼ÓÔØÉùÒô
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("OnLand.wma");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("EatCoin.wma");

	Common::loadMarioAnimation("flyFishLeft.png", 16, 16, 2, ANI_FLYFISH_LEFT, .5f, 4);
	Common::loadMarioAnimation("flyFishRight.png", 16, 16, 2, ANI_FLYFISH_RIGHT, .5f, 4);

	Common::loadMarioAnimation("boss.png", 32, 32, 4, ANI_BOSS_LEFT, .05f);
	Common::loadMarioAnimation("boss.png", 32, 32, 4, ANI_BOSS_RIGHT, .05f, 4);

	Common::loadMarioAnimation("bossBullet.png", 24, 8, 2, ANI_BOSS_BULLET_LEFT, .05f);
	Common::loadMarioAnimation("bossBullet.png", 24, 8, 2, ANI_BOSS_BULLET_RIGHT, .05f, 2);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);

    pEGLView->setDesignResolutionSize(480,320,kResolutionExactFit);
	
    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    loadResources();

    Util::runWithLayer(SceneStart::create());

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
