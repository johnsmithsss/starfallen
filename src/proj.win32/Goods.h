#pragma once
#include"BasicAttributes.h"
class Goods
{
public:
	Goods() {};
	~Goods() {};
	BasicAttributes* getBasicAttributes() { return GoodsBasic; }
	void setBasicAttributes(BasicAttributes* temp) { GoodsBasic = temp; }
private:
	int GoodsType;
	BasicAttributes* GoodsBasic;
};
