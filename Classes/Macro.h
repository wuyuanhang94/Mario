#ifndef MACRO_H
#define MACRO_H

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#ifndef WIN32
#include <GL/glut.h>
#include <linux/input.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#endif

USING_NS_CC;
USING_NS_CC_EXT;

#define IMAGE_BG "background.png"
#define IMAGE_BG2 "bg.png"

#define IMAGE_START_GAME_NORMAL  "startgame_normal.png"
#define IMAGE_START_GAME_SELECT "startgame_select.png"

#define IMAGE_QUIT_GAME_NORMAL "quitgame_normal.png"
#define IMAGE_QUIT_GAME_SELECT "quitgame_select.png"

#define IMAGE_SETTING_NORMAL "Setting_n.png"
#define IMAGE_SETTING_SELECT "setting_s.png"

#define IMAGE_ABOUT_NORMAL "about_normal.png"
#define IMAGE_ABOUT_SELECT "about_select.png"

#define IMAGE_BACK_NORMAL "backA.png"
#define IMAGE_BACK_SELECT "backB.png"

#define IMAGE_CTRL_UI  "controlUI.png"

#define IMAGE_DIR_NONE "backKeyImage.png"
#define IMAGE_DIR_LEFT "backKeyLeft.png"
#define IMAGE_DIR_RIGHT "backKeyRight.png"

#define IMAGE_MARIO_SMALL_LEFT  "smallWalkLeft.png"
#define IMAGE_MARIO_SMALL_RIGHT "smallWalkRight.png"
#define IMAGE_MARIO_BIG_LEFT "walkLeft.png"
#define IMAGE_MARIO_BIG_RIGHT "walkRight.png"

#define ANI_MARION_BIG_RUN_LEFT "ANI_MARION_BIG_RUN_LEFT"
#define ANI_MARION_BIG_RUN_RIGHT "ANI_MARION_BIG_RUN_RIGHT"
#define ANI_MARION_SMALL_RUN_LEFT "ANI_MARION_SMALL_RUN_LEFT"
#define ANI_MARION_SMALL_RUN_RIGHT "ANI_MARION_SMALL_RUN_RIGHT"

#define FRAME_MARIO_BIG_LEFT "FRAME_MARIO_BIG_LEFT"
#define FRAME_MARIO_BIG_RIGHT "FRAME_MARIO_BIG_RIGHT"
#define FRAME_MARIO_SMALL_LEFT "FRAME_MARIO_SMALL_LEFT"
#define FRAME_MARIO_SMALL_RIGHT "FRAME_MARIO_SMALL_RIGHT"

#define KEY_EVENT_DEV1_NAME     "/dev/input/event1"

#define MARIO_START_JUMP_SPEED	300

#define ANI_MUSHROOM_RUN "ANI_MUSHROOM_RUN"
#define FRAME_MUSHROOM_DIE1 "FRAME_MUSHROOM_DIE1"
#define FRAME_MUSHROOM_DIE2 "FRAME_MUSHROOM_DIE2"

#define ANI_TORTOISE_RUN_LEFT "ANI_TORTOISE_RUN_LEFT"
#define ANI_TORTOISE_RUN_RIGHT "ANI_TORTOISE_RUN_RIGHT"
#define ANI_TORTOISE_STOP "ANI_TORTOISE_STOP"

#define ANI_FLOWER "ANI_FLOWER"

#define FRAME_MUSHROOM_REWARD "FRAME_MUSHROOM_REWARD"
#define FRAME_MUSHROOM_ADDLIFE "FRAME_MUSHROOM_ADDLIFE"
#define FRAME_MUSHROOM_GOD "FRAME_MUSHROOM_GOD"

#define ANI_FLYFISH_LEFT "ANI_FLYFISH_LEFT"
#define ANI_FLYFISH_RIGHT "ANI_FLYFISH_RIGHT"

#define ANI_BOSS_LEFT "ANI_BOSS_LEFT"
#define ANI_BOSS_RIGHT "ANI_BOSS_RIGHT"

#define ANI_BOSS_BULLET_LEFT "ANI_BOSS_BULLET_LEFT"
#define ANI_BOSS_BULLET_RIGHT "ANI_BOSS_BULLET_RIGHT"

#endif // MACRO_H
