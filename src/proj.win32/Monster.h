#pragma once
#include"Role.h"
#include"Goods.h"
class Monster:public Role
{
public:
	Monster() {};
	Monster(int num, SpriteFrame *apperance) { Monster_Number = num; setApperance(apperance); }
	~Monster() {};
	Goods *DropGoods(int Goodsnumber);
private:
	int Monster_Number;
};