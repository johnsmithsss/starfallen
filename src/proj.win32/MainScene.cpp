#include"MainScene.h"
#include"Control.h"
Scene * MainScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainScene::create();
	scene->addChild(layer);
	return scene;
}
void MainScene::initDirection()
{
	Upwards = false;
	Downwards = false;
	Leftwards = false;
	Rightwards = false;
}

void MainScene::initMap()
{

	Control::getInstance()->mapbox.RandomMap(4);
	mapBox = Control::getInstance()->mapbox;
	MapSize = mapBox.getMapSize();
	setTileSize();
}
bool MainScene::init()
{
	initDirection();
	initMap();


	

	ShowCursor(false);
	//BGMLoad = Control::getInstance()->getVoiceBGM();
	//EffectLoad = Control::getInstance()->getVoiceEffect();
	BGMLoad = 100;
	EffectLoad = 100;
	Count = 0;


	visiblesize=Director::getInstance()->getVisibleSize();
	// map = Sprite::create("Resources/Image/MainBackGround.png");
	auto test = Sprite::create("Resources/Image/front.png");
	auto test1 = Sprite::create("Resources/Image/mywife.png");


	//setTileSize();

	auto animation=Animation::create();
	animation->addSpriteFrameWithFileName("Resources/Image/Move/wife_1.png");
	animation->addSpriteFrameWithFileName("Resources/Image/Move/wife_2.png");
	animation->addSpriteFrameWithFileName("Resources/Image/Move/wife_3.png");
	animation->addSpriteFrameWithFileName("Resources/Image/Move/wife_4.png");
	//animation->addSpriteFrameWithFileName("Resources/Image/Move/wife_1.png");
	animation->setDelayPerUnit(1.0/10.0);


	auto animation1 = Animation::create();
	animation1->addSpriteFrameWithFileName("Resources/Image/mywife-1.png");
	animation1->addSpriteFrameWithFileName("Resources/Image/mywife-2.png");
	animation1->addSpriteFrameWithFileName("Resources/Image/mywife-2.png");
	animation1->addSpriteFrameWithFileName("Resources/Image/mywife-2.png");
	animation1->addSpriteFrameWithFileName("Resources/Image/mywife-2.png");
	animation1->setDelayPerUnit(1.0 / 20.0);
	


	test1->setPosition(Vec2(visiblesize.width / 2+100, visiblesize.height / 2+100));
	test1->setScale(0.2);
	test->setPosition(Vec2(visiblesize.width/2-250,visiblesize.height/2));
	test->setScale(0.2);

	auto Action1 = RepeatForever::create(Animate::create(animation));
	Action1->setTag(5);
	test->runActionWithTag(Action1,true);
	////////////////////////////////////////////////


	int speed = 2000;
	auto pup=RepeatForever::create(MoveBy::create(10.0f, Vec2(0, speed)));
	auto pdown= RepeatForever::create(MoveBy::create(10.0f, Vec2(0, -speed)));
	auto pleft = RepeatForever::create(MoveBy::create(10.0f, Vec2(-speed, 0)));
	auto pright = RepeatForever::create(MoveBy::create(10.0f, Vec2(speed, 0)));
	pup->setTag(1);
	pdown->setTag(2);
	pleft->setTag(3);
	pright->setTag(4);
	test->runActionWithTag(pup,false);
	test->runActionWithTag(pdown,false);
	test->runActionWithTag(pleft,false);
	test->runActionWithTag(pright,false);
	////////////////////////////////////////////////////////////////////
	
	//this->runActionWithTag(tup,false);
	//this->runActionWithTag(tdown,false);
	//this->runActionWithTag(tleft,false);
	//this->runActionWithTag(tright,false);

	////////////////////////////////////
	test1->runAction(RepeatForever::create(Animate::create(animation1)));

	//test->runAction(Up);


	this->addChild(test, 1, "test");
	this->addChild(test1, 1, "test1");
	for(int i = 0; i <mapBox.getMapBox_FinalMap().size(); i++)
	{
		this->addChild(mapBox.getMapBox_FinalMap().at(i), 0,"");
	}
	


	setKeyboardListener();

	this->setAnchorPoint(Vec2::ZERO);
	this->setPosition(Vec2::ZERO);

	scheduleUpdate();
	//experimental::AudioEngine::play2d("Resources/Music/BGM/BGM_0.mp3", true, (float)BGMLoad / 100);
	Control::getInstance()->LoadBGM(experimental::AudioEngine::play2d("Resources/Music/BGM/BGM_1.mp3", true, (float)BGMLoad/100));
	

	
	return true;
}
void MainScene::setKeyboardListener()
{
	auto listener = EventListenerKeyboard::create();
	auto test = (Sprite*)this->getChildByName("test");
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		if ((int)keyCode == Key_W)
		{
			Upwards = true;
		}
		else if ((int)keyCode == Key_S) 
		{
			Downwards = true;
		}
		else if ((int)keyCode == Key_A)
		{
			test->setFlipX(true);
			Leftwards = true;
		}
		else if ((int)keyCode == Key_D)
		{
			Rightwards = true;
		}
		else if ((int)keyCode == Key_J)
		{
			Attack = true;
		}
	};

	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		switch ((int)keyCode)
		{
		case Key_W:
			Upwards = false;
			break;
		case Key_S:
			Downwards = false;
			break;
		case Key_A:
			test->setFlipX(false);
			Leftwards = false;
			break;
		case Key_D:
			Rightwards = false;
			break;
		case Key_J:
			Attack = false;
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void MainScene::updatePlayer(float delta)
{
	auto test = this->getChildByName("test");
	if (isPath(test->getPosition() + Vec2(0, test->getContentSize().height*0.2 - 30)))
	{
		if (Upwards)
		{
			test->getActionByTag(1)->Resume();
		}
		else
		{
			test->getActionByTag(1)->Pause();
		}
	}
	else
	{
		test->getActionByTag(1)->Pause();
	}
	if (isPath(test->getPosition() + Vec2(0, -(test->getContentSize().height*0.2 - 30))))
	{
		if (Downwards)
		{
			test->getActionByTag(2)->Resume();

		}
		else
		{

			test->getActionByTag(2)->Pause();
		}
	}
	else
	{
		test->getActionByTag(2)->Pause();

	}
	if (isPath(test->getPosition() + Vec2(-(test->getContentSize().width*0.2 - 30), 0)))
	{
		if (Leftwards)
		{
			test->getActionByTag(3)->Resume();

		}
		else
		{
			test->getActionByTag(3)->Pause();

		}
	}
	else
	{
		test->getActionByTag(3)->Pause();

	}
	if (isPath(test->getPosition() + Vec2(test->getContentSize().width*0.2 - 30, 0)))
	{
		if (Rightwards)
		{
			test->getActionByTag(4)->Resume();

		}
		else
		{
			test->getActionByTag(4)->Pause();

		}
	}
	else
	{
		test->getActionByTag(4)->Pause();

	}
	setCenter(test->getPosition());
}
void MainScene::update(float delta)
{
	updatePlayer(delta);
	auto test = this->getChildByName("test");
	if (Count++ % 10 == 0 && Attack)
	{
		for (int i = 0; i < 5; i++) 
		{
			auto s = Sprite::create("Resources/Image/Extra_56.png");
			s->setPosition(this->getChildByName("test")->getPosition() + Vec2(20, i*70));
			s->runActionWithTag(Spawn::create(MoveBy::create(2, Vec2(visiblesize.width*2, 0)), TintTo::create(0.5, random(125, 255), random(125, 255), random(125, 255)), NULL), true);
			s->setScale(5);
			s->setFlipX(true);
			this->addChild(s);
			Bullet.pushBack(s);
		}
		if (Count == 100)Count = 0;
	}
	for (int i=0; i<Bullet.size(); i++)
	{
		auto bullet = Bullet.at(i);
		if (bullet->getPosition().x -test->getPosition().x>visiblesize.width)
		{
			this->removeChild(bullet);
		}
	}
}
void MainScene::setTileSize()
{
	TileWeight = mapBox.getTileSize().width;
	TileHeight = mapBox.getTileSize().height;
}
Vec2 MainScene::TransOpenGLToTile(Vec2 position)
{
	int x = position.x / mapBox.getBlockSize().width;
	int y = position.y / mapBox.getBlockSize().height;
	position.x = position.x - mapBox.getBlockSize().width*x;
	position.y = position.y - mapBox.getBlockSize().height*y;
	int Tilex = position.x / TileWeight;
	int Tiley = (mapBox.getBlockSize().height- position.y )/ TileHeight;
	return Vec2(Tilex,Tiley);
}
bool MainScene::isPath(Vec2 position)
{
	int x = position.x / mapBox.getBlockSize().width;
	int y = position.y / mapBox.getBlockSize().height;
	int Count = x + y*mapBox.getEdgeNumber();
	auto CallidableLayer = mapBox.getMapAt_FinalMap(Count)->getLayer("BackGround");
	int Gid = CallidableLayer->getTileGIDAt(TransOpenGLToTile(position));
	if (Gid)
	{

		Value properties = mapBox.getMapAt_FinalMap(Count)->getPropertiesForGID(Gid);
		ValueMap m = properties.asValueMap();
		return m.at("temp").asBool();
	}
	else return true;
}
void MainScene::setCenter(Vec2 postion)
{
	if (postion.y > visiblesize.height / 2)
	{
		if (postion.y + visiblesize.height / 2<MapSize.height)
			this->setPosition(Vec2(this->getPosition().x,visiblesize.height / 2 - postion.y));
	}
	if (postion.x > visiblesize.width / 2)
	{
		if (postion.x + visiblesize.width / 2<MapSize.width)
			this->setPosition(Vec2(visiblesize.width / 2 - postion.x, this->getPosition().y));
	}
}