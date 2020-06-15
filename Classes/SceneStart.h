#ifndef SCENESTART_H
#define SCENESTART_H

#include "Common.h"

class SceneStart:public CCLayer
{
public:
    SceneStart();
    ~SceneStart();

    CREATE_FUNC(SceneStart);
    bool init();

    void Start(CCObject*);
    void Quit(CCObject*);
    void Setting(CCObject*);
    void About(CCObject*);
};

#endif // SCENESTART_H
