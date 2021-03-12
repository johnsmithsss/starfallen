#include"LoadScene.h"
#include"J_RW.h"
#include"Control.h"
#include"MainScene.h"
/*********************************************************************************
for (int i = 0; i < BGMNumber; i++)
{
std::string key=StringUtils::format("BGM_%d",i);
std::string name=StringUtils::format("Resources/Music/BGM/BGM_%d.mp3",i);
Loader->setFile("Resources/Files/MusicPath", (rapidjson::GenericStringRef<char>)key.c_str(), Value(name), FileReader_Writer::J_RW_TYPE::String);
}
for (int i = 0; i < BGMNumber; i++)
{
std::string key = StringUtils::format("Effect_%d", i);
std::string name = StringUtils::format("Resources/Music/Effect/Effect_%d.mp3", i);
Loader->setFile("Resources/Files/MusicPath", (rapidjson::GenericStringRef<char>)key.c_str(), Value(name), FileReader_Writer::J_RW_TYPE::String);
}
*/////////////////////////////////////////////////////////////////////
Scene * LoadScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadScene::create();
	scene->addChild(layer);
	return scene;
}
bool LoadScene::init()
{
	////////////////////////////////////////////////////////////////////////////
	//if test the single Scene, then need the function below
	/*




	for (int i = 0; i < 1; i++)
	{
		std::string key = StringUtils::format("Image_%d_Path", i);
		std::string file = StringUtils::format("Image_%d", i);
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(FileReader_Writer::J_RW::getInstance()->getString("Resources/Files/ResourcesPath", key.c_str()), FileReader_Writer::J_RW::getInstance()->getString("Resources/Files/ResourcesPath", file.c_str()));
		//loadingbar->setPercent(((float)TaskCountCurrent / (float)TaskCount)*100.0);
	}


	*************/////////////////////////////////////////////////////
	map = 0;
	TaskCount = -1;
	TaskCountCurrent = 0;
	auto director = Director::getInstance();
	auto Loader=FileReader_Writer::J_RW::getInstance();
	auto SpFrameCache = SpriteFrameCache::getInstance();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 OriginPoint = Director::getInstance()->getVisibleOrigin();
	auto loadingbar = LoadingBar::create("Resources/Image/UI/LoadingBar_1.png",0);
	auto BackGround = Sprite::createWithSpriteFrame(SpFrameCache->getSpriteFrameByName("MainBackGround.png"));
	auto loadingbar_Back = Sprite::create("Resources/Image/UI/LoadingBar_0.png");
	auto loadingtext = Sprite::createWithSpriteFrame(SpFrameCache->getSpriteFrameByName("Loading_0.png"));
	/////////////////////////////////////////////
	auto LoadingAction = Animation::create();
	for (int i = 0; i < 6; i++)
	{
		std::string animate = StringUtils::format("Loading_%d.png", i);
		LoadingAction->addSpriteFrame(SpFrameCache->getSpriteFrameByName(animate.c_str()));
	}
	LoadingAction->setDelayPerUnit(1.0f / 5.0f);
	loadingtext->setPosition(Vec2(870, 57));
	loadingtext->runAction(RepeatForever::create(Animate::create(LoadingAction)));
	//////////////////////////////////////////
	BackGround->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	loadingbar->setDirection(LoadingBar::Direction::LEFT);
	loadingbar->setPosition(Vec2(1130,57));
	loadingbar_Back->setPosition(Vec2(1130, 57));
	this->addChild(BackGround, -1);
	this->addChild(loadingbar, 0, "LoadingBar");
	this->addChild(loadingtext, 0);
	this->addChild(loadingbar_Back, 1, "LoadingBar_back");
	scheduleUpdate();
	std::thread t1(&LoadScene::ResourceLoading, this);
	t1.detach();
	return true;
}
void LoadScene::ResourceLoading()
{
	auto Loader = FileReader_Writer::J_RW::getInstance();
	auto Controller = Control::getInstance();
	auto loadingbar = (LoadingBar*)this->getChildByName("LoadingBar");
	int BGMNumber = Loader->getInt("Resources/Files/ResourcesPath","BGMNumber");
	int EffectNumber= Loader->getInt("Resources/Files/ResourcesPath","EffectNumber");
	int ImageNumber = Loader->getInt("Resources/Files/ResourcesPath", "ImageNumber");
	MapNumber = Loader->getInt("Resources/Files/ResourcesPath", "MapNumber");
	int n = 2000;
	TaskCount = BGMNumber + EffectNumber+ImageNumber+n;
	for (int i = 0; i < n; i++)
	{
		Sleep(1);
		TaskCountCurrent++;
		loadingbar->setPercent(((float)TaskCountCurrent / (float)TaskCount)*100.0);
	}
	for (int i = 0; i < BGMNumber; i++)
	{
		TaskCountCurrent++;
		std::string key = StringUtils::format("BGM_%d",i);
		Controller->setBGMPath(Loader->getString("Resources/Files/ResourcesPath",key.c_str()).c_str());
		experimental::AudioEngine::preload(Controller->getBGMPathVector().at(i).c_str());
		loadingbar->setPercent(((float)TaskCountCurrent / (float)TaskCount)*100.0);
	}
	for (int i = 0; i < EffectNumber; i++)
	{
		TaskCountCurrent++;
		std::string key = StringUtils::format("Effect_%d",i);
		Controller->setEffectPath(Loader->getString("Resources/Files/ResourcesPath", key.c_str()));
		experimental::AudioEngine::preload(Controller->getEffectPathVector().at(i).c_str());
		loadingbar->setPercent(((float)TaskCountCurrent / (float)TaskCount)*100.0);
	}
	SpriteFrameCache::getInstance()->removeSpriteFrames();
	for (int i = 0; i < ImageNumber; i++)
	{
		std::string key = StringUtils::format("Image_%d_Path", i);
		std::string file= StringUtils::format("Image_%d", i);
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(Loader->getString("Resources/Files/ResourcesPath", key.c_str()),Loader->getString("Resources/Files/ResourcesPath",file.c_str()));
		loadingbar->setPercent(((float)TaskCountCurrent / (float)TaskCount)*100.0);
		TaskCountCurrent++;
	}
}
void LoadScene::update(float delta)
{
	if (TaskCount == TaskCountCurrent)
	{
		for (; map <MapNumber; map++)
		{
			std::string key = StringUtils::format("Map_%d",map);
			//Control::getInstance()->mapbox.push_to_Born(TMXTiledMap::create(FileReader_Writer::J_RW::getInstance()->getString("Resources/Files/ResourcesPath", key.c_str()).c_str()));
		}
		TaskCountCurrent = 0;
		Sleep(1000);
		Director::getInstance()->replaceScene(TransitionFadeTR::create(2.0f, MainScene::createScene()));
		//Disable this function when test this Scene
		experimental::AudioEngine::stop(Control::getInstance()->getBGMVector().at(0));
	}
}