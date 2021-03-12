#pragma once
#include"BasicAttributes.h"
#include"cocos2d.h"
using namespace cocos2d;
class Role
{
public:
	Role() { RoleBasicAttributes = new BasicAttributes();};
	BasicAttributes* getBasicAttributes() { return RoleBasicAttributes; }
	void setBasicAttributes(BasicAttributes* temp) { RoleBasicAttributes = temp; }
	void setApperance(SpriteFrame* App) { Apperance = Sprite::createWithSpriteFrame(App);}
	virtual void Attack(Node* AttackOwner) = 0;
	void Hurt(float Damage)
	{
		if (RoleBasicAttributes->getHp() - Damage <= 0)RoleBasicAttributes->setHp(0);
		else RoleBasicAttributes->setHp(RoleBasicAttributes->getHp() - Damage);
	}
	bool isDead() { if (RoleBasicAttributes->getHp() == 0)return true; else return false;}
	~Role() { if(!RoleBasicAttributes)delete RoleBasicAttributes; };
private:
	BasicAttributes* RoleBasicAttributes;
	Sprite *Apperance;
};
