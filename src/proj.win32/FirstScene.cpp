#pragma once
#include "FirstScene.h"
#include"Control.h"
#include"J_RW.h"
Scene * FirstScene::createScene()
{
	auto scene = Scene::create();
	auto layer = FirstScene::create();
	scene->addChild(layer);
	return scene;
}
bool FirstScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	scheduleOnce(schedule_selector(FirstScene::LoadFin),1.0f);
	return true;
}
void FirstScene::LoadFin(float delta)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Resources/Image/Scene/Scene_1.plist","Resources/Image/Scene/Scene_1");
	auto reader = FileReader_Writer::J_RW::getInstance();
	auto Controller = Control::getInstance();
	Controller->setVoiceBGM(reader->getInt("Resources/Files/Option", "BGM_N"));
	Controller->setVoiceEffect(reader->getInt("Resources/Files/Option", "Effect_N"));
	experimental::AudioEngine::preload("Resources/Music/BGM/BGM_0.mp3");
	experimental::AudioEngine::preload("Resources/Music/Effect/Effect_0.mp3");
	auto scene = StartScene::createScene();
	Director::getInstance()->replaceScene(scene);
}