#pragma once
#include"cocos2d.h"
#include"cocos2d\cocos\ui\UILoadingBar.h"
USING_NS_CC;
class LoadScene :public Layer
{
public:
	CREATE_FUNC(LoadScene);
	static Scene* createScene();
	virtual bool init();
	void ResourceLoading();
	void update(float delta);
private:
	float TaskCount;
	float TaskCountCurrent;
	int map;
	int MapNumber;
};