#pragma once
#include"cocos2d.h"
USING_NS_CC;
class MapBox
{
public:
	MapBox() {};
	~MapBox() {};


	Vector<TMXTiledMap*> getMapBox_FinalMap() { return FinalMap; }
	void push_to_FinalMap(TMXTiledMap* temp) { FinalMap.pushBack(temp); }
	TMXTiledMap* getMapAt_FinalMap(int tag) { return FinalMap.at(tag); }

	bool RandomMap(int n);

	Size getTileSize() { return TileSize; }
	Size getBlockSize() { return BlockSize; }
	Size getMapSize() { return MapSize; }
	int getMapBlockNumber() { return MapBlockNumber; }
	int getEdgeNumber() { return EdgeNumber; }
	std::vector<Rect> getRectangle() { return RectSize; }
private:
	Vector<TMXTiledMap*> FinalMap;
	std::vector<Rect> RectSize;
	Size TileSize;
	Size BlockSize;
	Size MapSize;
	int MapBlockNumber;
	int EdgeNumber;
};
