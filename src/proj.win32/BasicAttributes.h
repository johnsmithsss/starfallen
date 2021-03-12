#pragma once
#include<iostream>
class BasicAttributes
{
public:
	BasicAttributes(std::string Name = std::string(""), float Attack = 0.0f, float Defence = 0.0f, float Crit = 0, float Speed = 0.0f, int Hp = 0) {};
	~BasicAttributes() {};
	void setName(std::string temp) { Name = temp; }
	void setHp(int temp) { Hp = temp; }
	void setAttack(float temp) { Attack = temp; }
	void setDefence(float temp) { Defence = temp; }
	void setSpeed(float temp) { Speed = temp; }
	void setCrit(float temp) { Crit = temp; }
	std::string getName() { return Name; }
	float getAttack() { return Attack; }
	int getHp() { return Hp; }
	float getDefence() { return Defence; }
	float getSpeed() { return Speed; }
	float getCrit() { return Crit; }
private:
	std::string Name;
	int Hp;
	float Attack;
	float Defence;
	float Speed;
	float Crit;
};
