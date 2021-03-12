#pragma once
#include"Classes\rapidjson\rapidjson.h"
#include "Classes\rapidjson\document.h"
#include "Classes\rapidjson\writer.h"
#include "Classes\rapidjson\stringbuffer.h"
#include "Classes\rapidjson\prettywriter.h"
#include"cocos2d.h"
#include <limits>
USING_NS_CC;
namespace FileReader_Writer{
	enum J_RW_TYPE
	{
		Int,String,Float
	};
class J_RW
{
public:
	static J_RW* getInstance() { return instance; }
	int getInt(const char* FileName, const char* key);
	std::string getString(const char* FileName, const char* key);
	float getfloat(const char* FileName, const char* key);
	void setFile(const char* Filepath, rapidjson::GenericStringRef<char> key,Value value,J_RW_TYPE type);
private:
	J_RW() {}
	~J_RW() {}
	static J_RW * instance;
};
}