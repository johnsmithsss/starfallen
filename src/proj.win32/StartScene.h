#pragma once
#include "cocos2d.h"
#include "cocos2d\cocos\ui\UIButton.h"
#include "cocos2d\cocos\ui\UISlider.h"
#include "cocos2d\cocos\ui\UIWidget.h"
#include"cocos2d\cocos\audio\include\AudioEngine.h"
USING_NS_CC;
using namespace cocos2d::ui;
class StartScene :public Layer
{
public:
	CREATE_FUNC(StartScene);
	static Scene* createScene();
	virtual bool init();
private:
	void StartGameCallback(Ref* pSender);
	void LoadGameCallback(Ref* pSender);
	void OptionCallback(Ref* pSender);
	void ExitCallback(cocos2d::Ref* pSender);
	void ReturnCallback(Ref* pSender, TouchEventType type);
	void ConfirmCallback(Ref* pSender, TouchEventType type);
	void CancelCallback(Ref* pSender, TouchEventType type);
	void LoadBGM();
	void update(float);
	Menu * setMenu();
	Menu * OptionMenu();
	Slider *setBGM();
	Slider *setEffect();
	int BGMLoad;
	int EffectLoad;
};