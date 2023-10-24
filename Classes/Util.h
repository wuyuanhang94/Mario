#ifndef __UTIL_H__
#define __UTIL_H__

#include "Macro.h"

#define winSize CCDirector::sharedDirector()->getWinSize()
#define switchScene(__layer_name__, ...) CCDirector::sharedDirector()->replaceScene(Util::scene(__layer_name__::create(__VA_ARGS__)));

#define enableTouch() do{ \
	setTouchEnabled(true); \
	setTouchMode(kCCTouchesOneByOne); \
}while (0)


struct Util
{
    static CCScene* scene(CCLayer* layer)
    {
        CCScene* s = CCScene::create();
        s->addChild(layer);
        return s;
    }

	static void replaceLayer(CCLayer* layer)
	{
		CCScene* scene = CCScene::create();
		scene->addChild(layer);
		CCDirector::sharedDirector()->replaceScene(scene);
	}

	static void runWithLayer(CCLayer* layer)
	{
		CCScene* scene = CCScene::create();
		scene->addChild(layer);
		CCDirector::sharedDirector()->runWithScene(scene);
	}

	static CCSprite* addSprite(CCNode* parent, const char* filename, int zorder = 0, int tag = 0)
	{
		CCSprite* sprite = CCSprite::create(filename);
		parent->addChild(sprite);
		sprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		sprite->setZOrder(zorder);
		sprite->setTag(tag);
		return sprite;
	}

    static CCSprite* addBackground(const char* picFile, CCNode* parent)
    {
        CCSprite* sp = CCSprite::create(picFile);
        parent->addChild(sp);
        sp->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        return sp;
    }

	static void scaleToFitWindow(CCNode* node)
	{
		node->setScaleX(winSize.width / node->getContentSize().width);
		node->setScaleY(winSize.height / node->getContentSize().height);
	}

	static void scaleToFitWindowY(CCNode* node, float margin = 0.0f)
	{
		node->setScale((winSize.height - margin * 2) / node->getContentSize().height);
	}

	static void scaleToFitWindowX(CCNode* node, float margin = 0.0f)
	{
		node->setScale((winSize.width - margin * 2) / node->getContentSize().width);
	}

	static void moveNode(CCNode* node, const CCPoint& off)
	{
		node->setPosition(node->getPosition() + off);
	}

	static char* format(int number, const char* prefix="", const char* suffix="")
	{
		static char buf[1024];
		sprintf(buf, "%s%d%s", prefix, number, suffix);
		return buf;
	}

	static void setTexture(CCSprite* sprite, const char* filename)
	{
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage((filename));
		sprite->setTexture(texture);
		sprite->setTextureRect(CCRect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
	}

	static void scaleToSize(CCNode* node, CCSize size)
	{
		CCSize nodeSize = node->getContentSize();
		node->setScaleX(size.width / nodeSize.width);
		node->setScaleY(size.height / nodeSize.height);
	}

	static CCPoint map2GL(const CCPoint& ptMap, CCTMXTiledMap* map)
	{
		CCPoint ptUI;
		ptUI.x = ptMap.x * map->getTileSize().width;
		ptUI.y = (ptMap.y+1) * map->getTileSize().height;

		CCPoint ptGL = ptUI;
		ptGL.y = map->getContentSize().height - ptUI.y;
		return ptGL;
	}

	static CCPoint GL2map(const CCPoint& ptGL, CCTMXTiledMap* map)
	{
		CCPoint ptUI = ptGL;
		ptUI.y = map->getContentSize().height - ptGL.y;

		int x = ptUI.x / map->getTileSize().width;
		int y = ptUI.y / map->getTileSize().height;
		return ccp(x, y);
	}

    static CCMenuItem* createMenuItemRB(CCNode* parent, const char* png1, const char* png2, CCNode* target, SEL_MenuHandler selector)
    {
        CCMenuItem* item = CCMenuItemImage::create(png1, png2, target, selector);
        CCMenu* menu = CCMenu::createWithItem(item);
        parent->addChild(menu);
        item->setPosition(ccp(winSize.width / 2 - item->boundingBox().size.width / 2,
                                  item->boundingBox().size.height / 2 - winSize.height / 2));
        return item;
    }

    static bool isClick(CCTouch* t)
    {
        return t->getLocation().getDistanceSq(t->getStartLocation()) < 25;
    }

    static bool isPartOutOfWindow(CCNode* node, const CCPoint& delta=ccp(0, 0))
    {
        CCRect rcNode = node->boundingBox();
        CCPoint pt[4];
        pt[0] = ccp(rcNode.getMinX(), rcNode.getMinY());
        pt[1] = ccp(rcNode.getMinX(), rcNode.getMaxY());
        pt[2] = ccp(rcNode.getMaxX(), rcNode.getMinY());
        pt[3] = ccp(rcNode.getMaxX(), rcNode.getMaxY());

        CCRect rcWin(0, 0, winSize.width, winSize.height);
        for(int i=0;i<4;i++)
        {
            if (!rcWin.containsPoint(pt[i] + delta)) return true;
        }
        return false;
    }

	static bool isAllOutOfWindow(CCNode* node, const CCPoint& delta=ccp(0, 0))
    {
        CCRect rcWin(0, 0, winSize.width, winSize.height);
		CCRect rcNode = node->boundingBox();
		rcNode.origin = rcNode.origin + delta;
		if (rcNode.intersectsRect(rcWin))
        	return false;
		return true;
    }

    static void setLabel(CCLabelAtlas* label, int change)
    {
        const char* sValue = label->getString();
        int value = atoi(sValue);
        value += change;
        label->setString(format(value));
    }
};


#endif
