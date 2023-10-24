#include "Mario.h"

bool Mario::init()
{
    CCSprite::initWithSpriteFrameName(Util::format(1, FRAME_SMALL_WALK_RIGHT_FORMAT));
    return true;
}
