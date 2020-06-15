#ifndef COMMON_H
#define COMMON_H

#include "Util.h"

enum MARIO_DIR{DIR_NONE,DIR_LEFT,DIR_RIGHT,DIR_UP,DIR_DOWN};
enum ITEM_TYPE {
	IT_mushroom,				//1
	IT_tortoise,					//1
	IT_flower,						//1
	IT_MushroomReward,	//1
	IT_MushroomAddLife,	//1
	IT_flagpoint,					//1
	IT_finalpoint,				//1
	IT_flyfish,						//2
	IT_ladderLR,				//2
	IT_ladderUD,				//3
	IT_tortoise_round,		//3
	IT_tortoise_fly,				//3
	IT_fire_string,				//4
	IT_boss,						//4
	IT_bridgestartpos,		//4
	IT_addmushroom, // 5
	IT_darkcloud,//5
	IT_battery, // 7
	IT_bullet,
};

#define MARIO_TileWidth 16
#define MARIO_TileHeight 16

class Common
{
public:
    static void loadMarioAnimation(const char* pngFile,int width,int height,
		int frameCount,const char* aniName,float delay,int startIdx  = 0)
    {
        CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(pngFile);
        CCArray* arr = CCArray::create();
		for (int i = startIdx ;  i<frameCount + startIdx ; i++)
        {
            CCSpriteFrame* spriteFrame = CCSpriteFrame::createWithTexture(texture,CCRect(i*width,0,width,height));
            arr->addObject(spriteFrame);
        }
        CCAnimation* animation = CCAnimation::createWithSpriteFrames(arr,delay);
        CCAnimationCache::sharedAnimationCache()->addAnimation(animation,aniName);
    }

    static void loadMarioSpriteFrame(const char* pngFile,int width,int height,int idx,const char* frameName)
    {
        CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(pngFile);
        CCSpriteFrame* spriteFrame = CCSpriteFrame::createWithTexture(texture,CCRect(idx*width,0,width,height));
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(spriteFrame,frameName);
    }

	static bool isBlock(CCPoint& pt, CCTMXTiledMap* map,
		CCSprite** blockSprite = NULL, const char** layerName = NULL, int* pgid = NULL)
	{
		//acquire pt coordinates in map coordinate system
		CCPoint ptMap = Util::GL2Map(pt, map);

		//if the point is not inside map, illustrating Mario moving outside the map, no block
		if (!Util::isInMap(ptMap, map))
			return false;

		//define there layers, acquiring elements from these layers
		static const char* layerNames[] = {"block","pipe","land"};
		for (int i = 0; i < sizeof(layerNames) / sizeof(*layerNames); i++)
		{
			CCTMXLayer* layer = map->layerNamed(layerNames[i]);
			int gid = layer->tileGIDAt(ptMap);
			if (gid != 0)
			{
				if(blockSprite)		*blockSprite = layer->tileAt(ptMap);
				if (layerName)		*layerName = layerNames[i];
				if(pgid)			*pgid = gid;
				return true;
			}
		}
		return false;
	}

	static int getGID(const CCPoint& pt, CCTMXTiledMap* map, const char* layername, CCSprite** sprite = NULL)
	{
		//acquire pt coordinates in map coordinate system
		CCPoint ptMap = Util::GL2Map(pt, map);

		//if the point is not inside map, illustrating Mario moving outside the map, no block
		if (!Util::isInMap(ptMap, map))
			return 0;

		CCTMXLayer* layer = map->layerNamed(layername);
		if (sprite) *sprite = layer->tileAt(ptMap);

		return layer->tileGIDAt(ptMap);
	}

	static void setGID(const CCPoint& pt, CCTMXTiledMap* map, const char* layername, int gid)
	{
		CCPoint ptMap = Util::GL2Map(pt, map);

		//if the point is not inside map, illustrating Mario moving outside the map, no block
		if (!Util::isInMap(ptMap, map))
			return;

		CCTMXLayer* layer = map->layerNamed(layername);
		layer->setTileGID(gid, ptMap);
	}

	static bool isBlock3Point(CCPoint pt[3], CCTMXTiledMap* map, 
		CCSprite** blockSprite = NULL, const char** layerName = NULL, int* gid=NULL)
	{
		//check whether  exists a point blocked
		for (int i = 0; i < 3; i++)
		{
			if (isBlock(pt[i], map,blockSprite,layerName,gid))
				return true;
		}
		return false;
	}
};

#endif // COMMON_H
