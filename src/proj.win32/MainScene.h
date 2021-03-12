#pragma once
#include"cocos2d.h"
#include"cocos2d\cocos\ui\UILoadingBar.h"
#include"MapBox.h"
#define Key_W 146
#define Key_S 142
#define Key_A 124
#define Key_D 127
#define Key_J 133
USING_NS_CC;
enum Status
{
	Up, Down, Left, Right, No
};
class MainScene :public Layer
{
public:
	CREATE_FUNC(MainScene);
	static Scene* createScene();
	virtual bool init();
	void update(float delta);
	void setKeyboardListener();
	void setStat(Status temp) { MoveDirection = temp; }
	Vec2 TransOpenGLToTile(Vec2 OpenGLPositon);
	Status getStat() { return MoveDirection; }
	void setTileSize();
	bool isPath(Vec2 Position);
	void initDirection();
	void initMap();
	void setCenter(Vec2 Postion);
	void updatePlayer(float delta);
	Vector<Sprite *> Bullet;
private:
	MapBox mapBox;
	Size visiblesize;
	Size MapSize;
	Status MoveDirection;
	int TileWeight;
	int TileHeight;
	int BGMLoad;
	int EffectLoad;
	bool Upwards;
	bool Downwards;
	bool Leftwards;
	bool Rightwards;
	bool Attack;
	int Count;

	
};