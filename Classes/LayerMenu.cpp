#include "LayerMenu.h"
#include "LayerStart.h"
#include "LayerGame.h"

void LayerMenu::onEnter()
{
    CCLayer::onEnter();

    Util::addBackground(IMAGE_BG, this);

    Util::createMenuItemRB(this, IMAGE_BACK_A, IMAGE_BACK_B, this, menu_selector(LayerMenu::Back));

    addScrollViewMenu();
}

void LayerMenu::onExit()
{
    CCLayer::onExit();
}

void LayerMenu::Back(CCObject *)
{
    switchScene(LayerStart);
}

void LayerMenu::addScrollViewMenu()
{
    _dataSource = new MyDataSource();
    MyTableView* view = MyTableView::create(_dataSource, winSize);
    addChild(view);
    view->setDirection(kCCScrollViewDirectionHorizontal);
    view->reloadData();

    view->setDelegate(this);
}


void LayerMenu::tableCellTouched(CCTableView *table, CCTableViewCell *cell)
{
    int index = cell->getIdx();
    switchScene(LayerGame, index);
}
