#include "MyTableView.h"

MyTableView* MyTableView::create(CCTableViewDataSource *source, CCSize size)
{
    MyTableView* table = new MyTableView;

    table->initWithViewSize(size, NULL);
    table->autorelease();
    table->setDataSource(source);
    table->_updateCellPositions();
    table->_updateContentSize();

    return table;
}

void MyTableView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!this->isVisible()) {
        return;
    }

    if (m_pTouchedCell){
        CCSprite* sprite = (CCSprite*)m_pTouchedCell->getChildren()->objectAtIndex(0);
        CCRect rcSprite = sprite->boundingBox();
        CCPoint ptInWorld = pTouch->getLocation();
        CCPoint ptInCell = m_pTouchedCell->convertToNodeSpace(ptInWorld);
        if (rcSprite.containsPoint(ptInCell) && m_pTableViewDelegate != NULL)
        {
            m_pTableViewDelegate->tableCellUnhighlight(this, m_pTouchedCell);
            m_pTableViewDelegate->tableCellTouched(this, m_pTouchedCell);
        }

        m_pTouchedCell = NULL;
    }
}
