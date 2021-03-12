#pragma once
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include"cocos2d.h"
USING_NS_CC;
class FirstScene:public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	void LoadFin(float delta);
	CREATE_FUNC(FirstScene);
};
#endif