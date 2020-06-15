#ifndef SCENEMENU_H
#define SCENEMENU_H

#include "Common.h"

class SceneMenu:public CCLayer, public CCTableViewDataSource,public CCTableViewDelegate
{
public:
    SceneMenu();
    ~SceneMenu();

    CCArray* _cells;

    CREATE_FUNC(SceneMenu);
    bool init();

    void Back(CCObject*);
    void addSlideMenu();

    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx)
    {
        return (CCTableViewCell*)_cells->objectAtIndex(idx);
    }

    virtual unsigned int numberOfCellsInTableView(CCTableView *table)
    {
        return _cells->count();
    }

    virtual CCSize cellSizeForTable(CCTableView *table)
    {
        return winSize;
    }

    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);

    virtual void scrollViewDidScroll(CCScrollView* view){}
    virtual void scrollViewDidZoom(CCScrollView* view){}

    bool ccTouchBegan(CCTouch *, CCEvent *);
    void ccTouchEnded(CCTouch* ,CCEvent* );
    void ccTouchMoved(CCTouch *, CCEvent *);
    void ccTouchCancelled(CCTouch* ,CCEvent*);

    CCTableView* _table;
    bool _isClickCell;
};

#endif // SCENEMENU_H
