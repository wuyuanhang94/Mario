#include "SceneMenu.h"
#include "SceneStart.h"
#include "SceneGame.h"

SceneMenu::SceneMenu()
{
    _cells = CCArray::create();
    _cells->retain();
}

SceneMenu::~SceneMenu()
{
    _cells->release();
}

bool SceneMenu::init()
{
    CCLayer::init();

    Util::addSprite(this,IMAGE_BG2);
    Util::createMenuItemRB(this,IMAGE_BACK_NORMAL,
                           IMAGE_BACK_SELECT,this,
                           menu_selector(SceneMenu::Back));
    addSlideMenu();

    enableTouch();
    setTouchPriority(-1);

    return true;
}

void SceneMenu::Back(CCObject *)
{
    Util::replaceLayer(SceneStart::create());
}

void SceneMenu::addSlideMenu()
{
    for(int i=0;i<8;i++)
    {
        CCTableViewCell* cell = new CCTableViewCell();
        cell->init();
        cell->autorelease();
        _cells->addObject(cell);

        Util::addSprite(cell,Util::format(i+1,"select",".jpg"));
    }

    CCTableView* table = CCTableView::create(this,winSize);
    this->addChild(table);

    table->setDirection(kCCScrollViewDirectionHorizontal);
    table->reloadData();

    table->setDelegate(this);
    _table = table;
}

bool SceneMenu::ccTouchBegan(CCTouch *t, CCEvent *v)
{
    _table->ccTouchBegan(t,v);
    return true;
}

void SceneMenu::ccTouchEnded(CCTouch* t ,CCEvent* v)
{
    _isClickCell = false;

    CCObject* obj;
    CCARRAY_FOREACH(_cells,obj)
    {
        CCTableViewCell* cell = (CCTableViewCell*)obj;
        CCPoint ptInCell = cell->convertTouchToNodeSpace(t);
        CCSprite* sprite = (CCSprite*)cell->getChildren()->objectAtIndex(0);
        if(sprite->boundingBox().containsPoint(ptInCell))
        {
            _isClickCell = true;
            break;
        }
    }

    _table->ccTouchEnded(t,v);
}

void SceneMenu::ccTouchMoved(CCTouch *t, CCEvent *v)
{
    _table->ccTouchMoved(t,v);
}

void SceneMenu::ccTouchCancelled(CCTouch* t,CCEvent* v)
{
    _table->ccTouchCancelled(t,v);
}

void SceneMenu::tableCellTouched(CCTableView *table, CCTableViewCell *cell)
{
    if(_isClickCell)
    {
        int cellid = cell->getIdx();
        Util::replaceLayer(SceneGame::create(cellid));
        //CCLog("cellid = %d\n",cellid);
    }
    else
    {
        CCLog("click out of pic");
    }
}
