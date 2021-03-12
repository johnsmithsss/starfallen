#include"MapBox.h"
#include"cocos2d\cocos\2d\CCTMXTiledMap.h"
bool MapBox::RandomMap(int n)
{
	MapBlockNumber = n*n;
	EdgeNumber = n;
	MapBlockNumber = 0;
	for(int i=0;i<n;i++)
		for (int j = 0; j < n; j++)
		{
			MapBlockNumber++;
			if (i == 0 && j == 0)
			{
				int rand=random(0, 1);						
				std::string Path = StringUtils::format("Resources/Image/Map/diyu/diyu/Map_%d.tmx", rand);
				auto Temp = TMXTiledMap::create("Resources/Image/Map/diyu/diyu/background_7.tmx");
				FinalMap.pushBack(Temp);
				BlockSize = this->getMapBox_FinalMap().at(0)->getContentSize();
				TileSize = this->getMapBox_FinalMap().at(0)->getTileSize();
				MapSize = Point(BlockSize.width*n, BlockSize.height*n);
				Temp->setPosition(j*BlockSize.width, i*BlockSize.height);
				RectSize.push_back(Rect(Temp->getPosition().x, Temp->getPosition().y,(j+1)*BlockSize.width,(i+1)*BlockSize.height));
			}
			else if (i==0&&j < n-1)
			{
				int rand = random(0, 1);
				std::string Path = StringUtils::format("Resources/Image/Map/test/Map_%d.tmx", rand);
				auto Temp = TMXTiledMap::create("Resources/Image/Map/diyu/diyu/background_8.tmx");
				Temp->setPosition(j*BlockSize.width, i*BlockSize.height);
				FinalMap.pushBack(Temp);
				RectSize.push_back(Rect(Temp->getPosition().x, Temp->getPosition().y, (j + 1)*BlockSize.width, (i + 1)*BlockSize.height));
			}
			else if (i == 0 && j == n - 1)
			{
				int rand = random(0, 1);
				std::string Path = StringUtils::format("Resources/Image/Map/test/Map_%d.tmx", rand);
				auto Temp = TMXTiledMap::create("Resources/Image/Map/diyu/diyu/background_9.tmx");
				Temp->setPosition(j*BlockSize.width, i*BlockSize.height);
				FinalMap.pushBack(Temp);
				RectSize.push_back(Rect(Temp->getPosition().x, Temp->getPosition().y, (j + 1)*BlockSize.width, (i + 1)*BlockSize.height));
			}
			else if (i >0&&i<n-1&&j==0)
			{
				int rand = random(0, 1);
				std::string Path = StringUtils::format("Resources/Image/Map/test/Map_%d.tmx", rand);
				auto Temp = TMXTiledMap::create("Resources/Image/Map/diyu/diyu/background_4.tmx");
				Temp->setPosition(j*BlockSize.width, i*BlockSize.height);
				FinalMap.pushBack(Temp);
				RectSize.push_back(Rect(Temp->getPosition().x, Temp->getPosition().y, (j + 1)*BlockSize.width, (i + 1)*BlockSize.height));
			}
			else if (i > 0 && i < n - 1 && j < n - 1)
			{
				int rand = random(1, 1);
				std::string Path = StringUtils::format("Resources/Image/Map/test/Map_%d.tmx", rand);
				auto Temp = TMXTiledMap::create("Resources/Image/Map/diyu/diyu/background_5.tmx");
				Temp->setPosition(j*BlockSize.width, i*BlockSize.height);
				FinalMap.pushBack(Temp);
				RectSize.push_back(Rect(Temp->getPosition().x, Temp->getPosition().y, (j + 1)*BlockSize.width, (i + 1)*BlockSize.height));
			}
			else if (i > 0 && i < n - 1 && j == n - 1)
			{
				int rand = random(0, 1);
				std::string Path = StringUtils::format("Resources/Image/Map/test/Map_%d.tmx", rand);
				auto Temp = TMXTiledMap::create("Resources/Image/Map/diyu/diyu/background_6.tmx");
				Temp->setPosition(j*BlockSize.width, i*BlockSize.height);
				FinalMap.pushBack(Temp);
				RectSize.push_back(Rect(Temp->getPosition().x, Temp->getPosition().y, (j + 1)*BlockSize.width, (i + 1)*BlockSize.height));
			}
			else if (i == n - 1 && j == 0)
			{
				int rand = random(0,1);
				std::string Path = StringUtils::format("Resources/Image/Map/test/Map_%d.tmx", rand);
				auto Temp = TMXTiledMap::create("Resources/Image/Map/diyu/diyu/background_1.tmx");
				Temp->setPosition(j*BlockSize.width, i*BlockSize.height);
				FinalMap.pushBack(Temp);
				RectSize.push_back(Rect(Temp->getPosition().x, Temp->getPosition().y, (j + 1)*BlockSize.width, (i + 1)*BlockSize.height));
			}
			else if (i == n - 1 && j < n - 1)
			{
				int rand = random(0, 1);
				std::string Path = StringUtils::format("Resources/Image/Map/test/Map_%d.tmx", rand);
				auto Temp = TMXTiledMap::create("Resources/Image/Map/diyu/diyu/background_2.tmx");
				Temp->setPosition(j*BlockSize.width, i*BlockSize.height);
				FinalMap.pushBack(Temp);
				RectSize.push_back(Rect(Temp->getPosition().x, Temp->getPosition().y, (j + 1)*BlockSize.width, (i + 1)*BlockSize.height));
			}
			else if (i == n - 1 && j == n - 1)
			{
				int rand = random(0,1);
				std::string Path = StringUtils::format("Resources/Image/Map/test/Map_%d.tmx", rand);
				auto Temp = TMXTiledMap::create("Resources/Image/Map/diyu/diyu/background_3.tmx");
				Temp->setPosition(j*BlockSize.width, i*BlockSize.height);
				FinalMap.pushBack(Temp);
				RectSize.push_back(Rect(Temp->getPosition().x, Temp->getPosition().y, (j + 1)*BlockSize.width, (i + 1)*BlockSize.height));
			}
		}
	return true;
}