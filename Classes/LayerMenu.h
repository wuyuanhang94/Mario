#ifndef LAYERMENU_H
#define LAYERMENU_H

#include "Common.h"
#include "MyTableView.h"

class MyDataSource: public CCTableViewDataSource
{
public:
    CCArray* _cells;

    MyDataSource()
    {
        _cells = CCArray::create();
        _cells->retain();

        for(int i=0; i<8; i++)
        {
            CCTableViewCell* cell = new CCTableViewCell;
            cell->init();
            cell->autorelease();
            _cells->addObject(cell);

            CCSprite* sprite = CCSprite::create(Util::format(i+1, "select", ".jpg"));
            cell->addChild(sprite);
            sprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        }
    }
    ~MyDataSource()
    {
        _cells->release();
    }

    virtual CCSize cellSizeForTable(CCTableView *table) {
        return winSize;
    }
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx)
    {
        return (CCTableViewCell*)_cells->objectAtIndex(idx);
    }

    virtual unsigned int numberOfCellsInTableView(CCTableView *table)
    {
        return _cells->count();
    }
};

class LayerMenu : public CCLayer, public CCTableViewDelegate
{
public:
    CREATE_FUNC(LayerMenu);

    void onEnter();
    void onExit();

    void Back(CCObject*);

    void addScrollViewMenu();
    MyDataSource* _dataSource;

    virtual void tableCellTouched(CCTableView *table, CCTableViewCell *cell);

    virtual void scrollViewDidScroll(CCScrollView* view){}
    virtual void scrollViewDidZoom(CCScrollView* view){}
};

#endif // LAYERMENU_H
