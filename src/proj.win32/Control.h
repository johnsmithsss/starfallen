#pragma once
#include"cocos2d.h"
#include<vector>
#include"FirstScene.h"
#include"StartScene.h"
#include"LoadScene.h"
#include"MainScene.h"
#include"MapBox.h"
#include"Monster.h"
USING_NS_CC;
class Control
{
public:
	static Control* getInstance() { return instance; }
	std::vector < int> getEffectVector(){return EffectVector;}
	std::vector <int> getBGMVector(){return BGMVector;}
	std::vector<std::string> getEffectPathVector() { return EffectPath; }
	std::vector<std::string> getBGMPathVector() { return BGMPath; }
	void setBGMPath(std::string temp) { BGMPath.push_back(temp); }
	void setEffectPath(std::string temp) { EffectPath.push_back(temp); }
	void LoadEffect(int temp) { EffectVector.push_back(temp); }
	void LoadBGM(int temp) { BGMVector.push_back(temp); }
	void setVoiceBGM(int temp) { BGMLoad = temp; }
	void setVoiceEffect(int temp) { EffectLoad = temp; }
	int getVoiceBGM() { return BGMLoad; }
	int getVoiceEffect() { return EffectLoad; }
	MapBox mapbox;
private:
	
	static Control* instance;
	Control() {};
	~Control() {};
	std::vector < int> EffectVector;
	std::vector < int> BGMVector;
	std::vector<std::string> EffectPath;
	std::vector<std::string> BGMPath;
	std::vector<Monster*>MonsterVector;
	int BGMLoad;
	int EffectLoad;
};