#pragma once
#include<iostream>
#include <reader.h>
#include "cocos2d.h"
class JsonReader
{
public:
	static std::string getString(std::string name, std::string File);
private:
	JsonReader() {};
	~JsonReader() {};
};
std::string JsonReader::getString(std::string name,std::string File) 
{
	Json::Reader reader;
	Json::Value root;
	std::string data = FileUtils::getInstance()->getStringFromFile(File);

	if (reader.parse(data, root, false) == true)
	{
		return root[name].asCString();
	}
}
