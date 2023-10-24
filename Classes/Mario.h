#ifndef MARIO_H
#define MARIO_H

#include "Common.h"

class Mario : public CCSprite
{
public:
    CREATE_FUNC(Mario);
    bool init();
};

#endif // MARIO_H
