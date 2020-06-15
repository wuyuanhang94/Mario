#include "../Classes/AppDelegate.h"
#include "cocos2d.h"
#include "CCEGLView.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>

#include "../Classes/Macro.h"

USING_NS_CC;

int main(int argc, char **argv)
{
    // create the application instance
    glutInit(&argc,argv);
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setFrameSize(600, 400);
    eglView->setViewName("Mario");
    return CCApplication::sharedApplication()->run();
}
