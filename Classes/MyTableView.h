#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H

#include "Common.h"

class MyTableView : public CCTableView
{
public:
    static MyTableView* create(CCTableViewDataSource* source, CCSize size);
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
};

#endif // MYTABLEVIEW_H
