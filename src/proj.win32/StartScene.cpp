#pragma once
#include "StartScene.h"
#include"JsonReader.h"
#include "Control.h"
#include"J_RW.h"
#include"MessageBoxWithFormat.h"
#include"LoadScene.h"
Scene * StartScene::createScene()
{
	auto scene = Scene::create();
	auto layer = StartScene::create();
	scene->addChild(layer);
	return scene;
}
void StartScene::LoadBGM()
{
	BGMLoad = Control::getInstance()->getVoiceBGM();
	EffectLoad = Control::getInstance()->getVoiceEffect();
}
bool StartScene::init()
{
	LoadBGM();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 OriginPoint = Director::getInstance()->getVisibleOrigin();
	auto SpFramCache = SpriteFrameCache::getInstance();
	auto GameName= Label::create(JsonReader::getString("GameName","Resources/Files/Language"),"Resources/Fonts/Chs.ttf",78);
	auto MainBackGround = Sprite::createWithSpriteFrame(SpFramCache->getSpriteFrameByName("MainBackGround.png"));
	auto TextBox = Sprite::createWithSpriteFrame(SpFramCache->getSpriteFrameByName("TextBox.png"));
	auto StartLabel = Label::create("StarFallen", "Resources/Fonts/OklahomaSoft-Open.ttf", 100);
	auto TextBoxLabel = Label::create(JsonReader::getString("SaveOption", "Resources/Files/Language"), "Resources/Fonts/Chs.ttf", 55);
	auto menu = setMenu();
	auto OpMenu = OptionMenu();
	auto slider = setBGM();
	auto slider1 = setEffect();
	auto Re = Button::create();
	auto Confirm = Button::create();
	auto Cancel = Button::create();
	auto director = Control::getInstance();
	auto VoiceBGM = Label::create(std::to_string(BGMLoad) + "%", "Resources/Fonts/UseAsNumber.ttf", 45);
	auto VoiceEffect = Label::create(std::to_string(EffectLoad)+"%", "Resources/Fonts/UseAsNumber.ttf", 45);
	StartLabel->setPosition(Vec2(visibleSize.width / 2.0, visibleSize.height / 2.0));
	StartLabel->setScale(0);
	TextBoxLabel->setPosition(Vec2(680, 407));
	TextBoxLabel->setOpacity(0);
	TextBoxLabel->setColor(Color3B(185, 49, 63));
	MainBackGround->setPosition(Vec2(visibleSize.width / 2.0, visibleSize.height / 2.0));
	MainBackGround->setOpacity(0);
	TextBox->setPosition(Vec2(visibleSize.width / 2.0, visibleSize.height / 2.0));
	TextBox->setOpacity(0);
	GameName->setPosition(Vec2(visibleSize.width / 5.7, visibleSize.height / 1.2));
	GameName->setOpacity(0);
	GameName->setColor(Color3B(185,49,63));
	menu->setPosition(Vec2(visibleSize.width / 5.7, visibleSize.height / 2.3));
	OpMenu->setPosition(Vec2(visibleSize.width / 5.7, visibleSize.height / 1.4));
	StartLabel->runAction(Sequence::create(Spawn::create(ScaleTo::create(2.0, 1), TintTo::create(2.0, 173, 27, 1), NULL), FadeOut::create(2), NULL));
	MainBackGround->runAction(Sequence::create(DelayTime::create(2),FadeIn::create(2),NULL));
	GameName->runAction(Sequence::create(DelayTime::create(4), FadeIn::create(0.6), NULL));
	slider->setAnchorPoint(Vec2(0, 1.0));
	slider->setPosition(Vec2(visibleSize.width / 4.0, visibleSize.height / 1.2));
	slider1->setAnchorPoint(Vec2(0, 1.0));
	slider1->setPosition(Vec2(visibleSize.width / 4.0, visibleSize.height / 1.345));
	Re->setTitleLabel(Label::create(JsonReader::getString("Return", "Resources/Files/Language"), "Resources/Fonts/Chs.ttf", 50));
	Re->setTitleColor(Color3B(185, 49, 63));
	Re->setAnchorPoint(Vec2(0.5,0.5));
	Re->setPosition(Vec2(visibleSize.width/1.13,visibleSize.height/7));
	Re->setOpacity(0);
	Re->runAction(Hide::create());
	Re->addTouchEventListener(this, toucheventselector(StartScene::ReturnCallback));
	Confirm->setTitleLabel(Label::create(JsonReader::getString("Confirm", "Resources/Files/Language"), "Resources/Fonts/Chs.ttf", 50));
	Confirm->setTitleColor(Color3B(0, 0, 0));
	Confirm->setAnchorPoint(Vec2(0.5, 0.5));
	Confirm->setPosition(Vec2(543, 285));
	Confirm->setOpacity(0);
	Confirm->runAction(Hide::create());
	Confirm->addTouchEventListener(this, toucheventselector(StartScene::ConfirmCallback));
	Cancel->setTitleLabel(Label::create(JsonReader::getString("Cancel", "Resources/Files/Language"), "Resources/Fonts/Chs.ttf", 50));
	Cancel->setTitleColor(Color3B(0, 0, 0));
	Cancel->setAnchorPoint(Vec2(0.5, 0.5));
	Cancel->setPosition(Vec2(829, 285));
	Cancel->setOpacity(0);
	Cancel->runAction(Hide::create());
	Cancel->addTouchEventListener(this, toucheventselector(StartScene::CancelCallback));
	VoiceBGM->setColor(Color3B(106, 0, 0));
	VoiceEffect->setColor(Color3B(106, 0, 0));
	VoiceBGM->setPosition(Vec2(visibleSize.width / 1.6, visibleSize.height / 1.25));
	VoiceEffect->setPosition(Vec2(visibleSize.width / 1.6, visibleSize.height / 1.395));
	VoiceBGM->setOpacity(0);
	VoiceEffect->setOpacity(0);
	this->addChild(MainBackGround, 0);
	this->addChild(VoiceBGM, 1, "VoiceBGM");
	this->addChild(VoiceEffect, 1, "VoiceEffect");
	this->addChild(Re, 1, "Return");
	this->addChild(slider1, 1, "Effect");
	this->addChild(slider, 1,"BGM");
	this->addChild(GameName, 1,"GameName");
	this->addChild(menu, 1,"Menu");
	this->addChild(StartLabel, 1);
	this->addChild(OpMenu, 1, "OptionMenu");
	this->addChild(TextBox, 2, "TextBox");
	this->addChild(TextBoxLabel, 3, "TextBoxLabel");
	this->addChild(Confirm, 3, "Confirm");
	this->addChild(Cancel, 3, "Cancel");
	scheduleUpdate();
 	Control::getInstance()->LoadBGM(experimental::AudioEngine::play2d("Resources/Music/BGM/BGM_0.mp3", true, (float)BGMLoad/100));
	return true;
}
void StartScene::update(float Frametime)
{
	//auto menu = this->getChildByName("Menu");
	//if(tag)menu->setPosition(menu->getPosition() + Vec2(1, 0));
}
Menu * StartScene::setMenu()
{
	float Size = 50;
	float RawSpace=10;
	auto StartGame = MenuItemLabel::create(Label::create(JsonReader::getString("Start", "Resources/Files/Language"), "Resources/Fonts/Chs.ttf", Size), CC_CALLBACK_1(StartScene::StartGameCallback, this));
	auto Load= MenuItemLabel::create(Label::create(JsonReader::getString("Load", "Resources/Files/Language"), "Resources/Fonts/Chs.ttf", Size), CC_CALLBACK_1(StartScene::LoadGameCallback, this));
	auto Option= MenuItemLabel::create(Label::create(JsonReader::getString("Option", "Resources/Files/Language"), "Resources/Fonts/Chs.ttf", Size), CC_CALLBACK_1(StartScene::OptionCallback, this));
	auto Exit = MenuItemLabel::create(Label::create(JsonReader::getString("Exit", "Resources/Files/Language"), "Resources/Fonts/Chs.ttf", Size),CC_CALLBACK_1(StartScene::ExitCallback,this));
	StartGame->setColor(Color3B::BLACK);
	Load->setColor(Color3B::BLACK);
	Option->setColor(Color3B(185, 49, 63));
	Exit->setColor(Color3B(185, 49, 63));
	auto menu = Menu::create(StartGame, Load, Option, Exit,NULL);
	StartGame->setOpacity(0);
	Load->setOpacity(0);
	Option->setOpacity(0);
	Exit->setOpacity(0);
	menu->alignItemsVerticallyWithPadding(RawSpace);
	StartGame->runAction(Sequence::create(DelayTime::create(4.6), FadeIn::create(0.3), NULL));
	Load->runAction(Sequence::create(DelayTime::create(5.2), FadeIn::create(0.3), NULL));
	Option->runAction(Sequence::create(DelayTime::create(5.8), FadeIn::create(0.3), NULL));
	Exit->runAction(Sequence::create(DelayTime::create(6.4), FadeIn::create(0.3), NULL));
	return menu;
}
Menu * StartScene::OptionMenu()
{
	float Size = 50;
	float RawSpace = 20;
	auto BGM = MenuItemLabel::create(Label::create(JsonReader::getString("BGM", "Resources/Files/Language"), "Resources/Fonts/Chs.ttf", Size));
	auto Effect = MenuItemLabel::create(Label::create(JsonReader::getString("Effect", "Resources/Files/Language"), "Resources/Fonts/Chs.ttf", Size));
	auto Instruction = MenuItemLabel::create(Label::create(JsonReader::getString("Instruction", "Resources/Files/Language"), "Resources/Fonts/Chs.ttf", Size));
	BGM->setEnabled(false);
	Effect->setEnabled(false);
	Instruction->setEnabled(false);
	BGM->setColor(Color3B(185, 49, 63));
	Effect->setColor(Color3B(185, 49, 63));
	Instruction->setColor(Color3B(185, 49, 63));
	auto menu = Menu::create(BGM, Effect, Instruction, NULL);
	menu->setOpacity(0);
	menu->alignItemsVerticallyWithPadding(RawSpace);
	return menu;
}
void StartScene::StartGameCallback(Ref* pSender)
{
	experimental::AudioEngine::play2d("Resources/Music/Effect/Effect_0.mp3", false, Control::getInstance()->getVoiceEffect() / 100.0);
	auto Scene = LoadScene::createScene();
	Director::getInstance()->replaceScene(Scene);
}
void StartScene::LoadGameCallback(Ref* pSender)
{
	experimental::AudioEngine::play2d("Resources/Music/Effect/Effect_0.mp3", false, Control::getInstance()->getVoiceEffect() / 100.0);
}
void StartScene::OptionCallback(Ref* pSender)
{
	experimental::AudioEngine::play2d("Resources/Music/Effect/Effect_0.mp3", false, Control::getInstance()->getVoiceEffect() / 100.0);
	auto menu = this->getChildByName("Menu");
	auto Name = this->getChildByName("GameName");
	auto OpMenu = this->getChildByName("OptionMenu");
	auto BGM = this->getChildByName("BGM");
	auto Effect = this->getChildByName("Effect");
	auto Return = this->getChildByName("Return");
	auto VBGM = this->getChildByName("VoiceBGM");
	auto VEff = this->getChildByName("VoiceEffect");
	menu->runAction(Hide::create());
	Name->runAction(Hide::create());
	OpMenu->runAction(FadeIn::create(0.3));
	BGM->runAction(Sequence::create(Show::create(),FadeIn::create(0.3),NULL));
	Effect->runAction(Sequence::create(Show::create(), FadeIn::create(0.3), NULL));
	VBGM->runAction(FadeIn::create(0.3));
	VEff->runAction(FadeIn::create(0.3));
	Return->runAction(Sequence::create(Show::create(), FadeIn::create(0.3), NULL));
}
void StartScene::ExitCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	experimental::AudioEngine::stopAll();
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
void StartScene::ReturnCallback(Ref* pSender,TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
	{
		experimental::AudioEngine::play2d("Resources/Music/Effect/Effect_0.mp3", false, Control::getInstance()->getVoiceEffect() / 100.0);
		auto SliderBGM = (Slider*)this->getChildByName("BGM");
		auto SliderEffect =(Slider*) this->getChildByName("Effect");
		if (SliderBGM->getPercent() == Control::getInstance()->getVoiceBGM() && SliderEffect->getPercent() == Control::getInstance()->getVoiceEffect())
		{
			auto menu = this->getChildByName("Menu");
			auto Name = this->getChildByName("GameName");
			auto OpMenu = this->getChildByName("OptionMenu");
			auto BGM = this->getChildByName("BGM");
			auto Effect = this->getChildByName("Effect");
			auto VBGM = this->getChildByName("VoiceBGM");
			auto VEff = this->getChildByName("VoiceEffect");
			auto TextBox = this->getChildByName("TextBox");
			auto TextBoxLabel = this->getChildByName("TextBoxLabel");
			auto Confirm = this->getChildByName("Confirm");
			auto Cancel = this->getChildByName("Cancel");
			menu->runAction(Show::create());
			Name->runAction(Show::create());
			OpMenu->runAction(Show::create());
			VBGM->runAction(FadeOut::create(0.3));
			VEff->runAction(FadeOut::create(0.3));
			OpMenu->runAction(FadeOut::create(0.3));
			TextBox->runAction(FadeOut::create(0.3));
			TextBoxLabel->runAction(FadeOut::create(0.3));
			BGM->runAction(Sequence::create(FadeOut::create(0.3), Hide::create(), NULL));
			Effect->runAction(Sequence::create(FadeOut::create(0.3), Hide::create(), NULL));
			Confirm->runAction(Sequence::create(FadeOut::create(0.3), Hide::create(), NULL));
			Cancel->runAction(Sequence::create(FadeOut::create(0.3), Hide::create(), NULL));
		}
		else {
			auto TextBox = this->getChildByName("TextBox");
			auto TextBoxLabel = this->getChildByName("TextBoxLabel");
			auto Return = this->getChildByName("Return");
			auto Confirm = this->getChildByName("Confirm");
			auto Cancel = this->getChildByName("Cancel");
			Return->runAction(Sequence::create(FadeOut::create(0.3), Hide::create(), NULL));
			TextBox->runAction(FadeIn::create(0.3));
			TextBoxLabel->runAction(FadeIn::create(0.3));
			Confirm->runAction(Sequence::create(Show::create(), FadeIn::create(0.3), NULL));
			Cancel->runAction(Sequence::create(Show::create(), FadeIn::create(0.3), NULL));
		}
	}
}
void StartScene::ConfirmCallback(Ref * pSender, TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
	{
		auto menu = this->getChildByName("Menu");
		auto Name = this->getChildByName("GameName");
		auto OpMenu = this->getChildByName("OptionMenu");
		auto BGM = this->getChildByName("BGM");
		auto Effect = this->getChildByName("Effect");
		auto VBGM = this->getChildByName("VoiceBGM");
		auto VEff = this->getChildByName("VoiceEffect");
		auto TextBox = this->getChildByName("TextBox");
		auto TextBoxLabel = this->getChildByName("TextBoxLabel");
		auto Confirm = this->getChildByName("Confirm");
		auto Cancel = this->getChildByName("Cancel");
		menu->runAction(Show::create());
		Name->runAction(Show::create());
		OpMenu->runAction(Show::create());
		VBGM->runAction(FadeOut::create(0.3));
		VEff->runAction(FadeOut::create(0.3));
		OpMenu->runAction(FadeOut::create(0.3));
		TextBox->runAction(FadeOut::create(0.3));
		TextBoxLabel->runAction(FadeOut::create(0.3));
		BGM->runAction(Sequence::create(FadeOut::create(0.3), Hide::create(), NULL));
		Effect->runAction(Sequence::create(FadeOut::create(0.3), Hide::create(), NULL));
		Confirm->runAction(Sequence::create(FadeOut::create(0.3), Hide::create(), NULL));
		Cancel->runAction(Sequence::create(FadeOut::create(0.3), Hide::create(), NULL));
		Control::getInstance()->setVoiceEffect(EffectLoad);
		Control::getInstance()->setVoiceBGM(BGMLoad);
		experimental::AudioEngine::play2d("Resources/Music/Effect/Effect_0.mp3", false, Control::getInstance()->getVoiceEffect() / 100.0);
		FileReader_Writer::J_RW::getInstance()->setFile("Resources/Files/Option", "BGM_N", Value(BGMLoad), FileReader_Writer::J_RW_TYPE::Int);
		FileReader_Writer::J_RW::getInstance()->setFile("Resources/Files/Option", "Effect_N", Value(EffectLoad), FileReader_Writer::J_RW_TYPE::Int);
	}
}
void StartScene::CancelCallback(Ref * pSender, TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
	{
		experimental::AudioEngine::play2d("Resources/Music/Effect/Effect_0.mp3", false, Control::getInstance()->getVoiceEffect() / 100.0);
		auto menu = this->getChildByName("Menu");
		auto Name = this->getChildByName("GameName");
		auto OpMenu = this->getChildByName("OptionMenu");
		auto BGM = (Slider*)this->getChildByName("BGM");
		auto Effect = (Slider*)this->getChildByName("Effect");
		auto VBGM = (Label*)this->getChildByName("VoiceBGM");
		auto VEff = (Label*)this->getChildByName("VoiceEffect");
		auto TextBox = this->getChildByName("TextBox");
		auto TextBoxLabel = this->getChildByName("TextBoxLabel");
		auto Confirm = this->getChildByName("Confirm");
		auto Cancel = this->getChildByName("Cancel");
		menu->runAction(Show::create());
		Name->runAction(Show::create());
		OpMenu->runAction(Show::create());
		VBGM->runAction(FadeOut::create(0.3));
		VEff->runAction(FadeOut::create(0.3));
		OpMenu->runAction(FadeOut::create(0.3));
		TextBox->runAction(FadeOut::create(0.3));
		TextBoxLabel->runAction(FadeOut::create(0.3));
		BGM->runAction(Sequence::create(FadeOut::create(0.3), Hide::create(), NULL));
		Effect->runAction(Sequence::create(FadeOut::create(0.3), Hide::create(), NULL));
		Confirm->runAction(Sequence::create(FadeOut::create(0.3), Hide::create(), NULL));
		Cancel->runAction(Sequence::create(FadeOut::create(0.3), Hide::create(), NULL));
		BGMLoad = Control::getInstance()->getVoiceBGM();
		EffectLoad = Control::getInstance()->getVoiceEffect();
		experimental::AudioEngine::setVolume(Control::getInstance()->getBGMVector().at(0), (float)BGMLoad / 100.0);
		VBGM->setString(std::to_string(BGMLoad));
		VEff->setString(std::to_string(EffectLoad));
		BGM->setPercent(BGMLoad);
		Effect->setPercent(EffectLoad);
	}
}
Slider * StartScene::setBGM()
{
	auto fc=SpriteFrameCache::getInstance();
	auto slider = Slider::create();
	slider->loadBarTexture(fc->getSpriteFrameByName("SliderloadBar.png"));
	slider->loadProgressBarTexture(fc->getSpriteFrameByName("SliderloadBarAfter.png"));
	slider->loadSlidBallTexture(fc->getSpriteFrameByName("SliderBall.png"));
	slider->setPercent(BGMLoad);
	slider->setOpacity(0);
	slider->runAction(Hide::create());
	slider->addEventListener([=](Ref *pSender,Slider::EventType status)
	{
		if (status == Slider::EventType::ON_PERCENTAGE_CHANGED)
		{
			auto VBGM = (Label*)this->getChildByName("VoiceBGM");
			VBGM->setString(std::to_string(slider->getPercent()) + "%");
			experimental::AudioEngine::setVolume(Control::getInstance()->getBGMVector().at(0), slider->getPercent() / 100.0);
			BGMLoad = slider->getPercent();
		}
	}
	);
	return slider;
}
Slider * StartScene::setEffect()
{
	auto fc = SpriteFrameCache::getInstance();
	auto slider = Slider::create();
	slider->loadBarTexture(fc->getSpriteFrameByName("SliderloadBar.png"));
	slider->loadProgressBarTexture(fc->getSpriteFrameByName("SliderloadBarAfter.png"));
	slider->loadSlidBallTexture(fc->getSpriteFrameByName("SliderBall.png"));
	slider->setOpacity(0);
	slider->runAction(Hide::create());
	slider->setPercent(EffectLoad);
	slider->addEventListener([=](Ref *pSender, Slider::EventType status)
	{
		if (status == Slider::EventType::ON_PERCENTAGE_CHANGED)
		{
			auto VEff = (Label*) this->getChildByName("VoiceEffect");
			VEff->setString(std::to_string(slider->getPercent()) + "%");
			EffectLoad = slider->getPercent();
		}
	}
	);
	return slider;
}