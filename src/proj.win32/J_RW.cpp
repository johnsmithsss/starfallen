#include"J_RW.h"
using namespace FileReader_Writer;
J_RW* J_RW::instance = new J_RW();
int J_RW::getInt(const char* FileName, const char* key)
{
	SSIZE_T size;
	unsigned char* ch = FileUtils::getInstance()->getFileData(FileName, "r", &size);
	std::string data = std::string((const char*)ch, size);
	rapidjson::Document doc;                          ///< 创建一个Document对象 rapidJson的相关操作都在Document类中
	doc.Parse(data.c_str());               ///< 通过Parse方法将Json数据解析出来
	if (doc.HasParseError())
	{
		CCLOG("GetParseError%s\n", doc.GetParseError());
	}
	rapidjson::Value& value = doc[key];
	if (value.IsInt())
		return value.GetInt();
	else
		return INT_MIN;
}
float J_RW::getfloat(const char* FileName, const char* key)
{
	SSIZE_T size;
	unsigned char* ch = FileUtils::getInstance()->getFileData(FileName, "r", &size);
	std::string data = std::string((const char*)ch, size);
	rapidjson::Document doc;                          ///< 创建一个Document对象 rapidJson的相关操作都在Document类中
	doc.Parse(data.c_str());               ///< 通过Parse方法将Json数据解析出来
	if (doc.HasParseError())
	{
		CCLOG("GetParseError%s\n", doc.GetParseError());
	}
	rapidjson::Value& value = doc[key];
	if (value.IsFloat())
		return value.GetFloat();
	else
		return INT_MIN;
}
std::string J_RW::getString(const char* FileName, const char* key)
{
	SSIZE_T size;
	unsigned char* ch = FileUtils::getInstance()->getFileData(FileName, "r", &size);
	std::string data = std::string((const char*)ch, size);
	rapidjson::Document doc;                          ///< 创建一个Document对象 rapidJson的相关操作都在Document类中
	doc.Parse(data.c_str());               ///< 通过Parse方法将Json数据解析出来
	if (doc.HasParseError())
	{
		CCLOG("GetParseError%s\n", doc.GetParseError());
	}
	if (doc[key].IsString())
		return doc[key].GetString();
	else
		return "get_string_error";
}
void J_RW::setFile(const char* FilePath_FileName, rapidjson::GenericStringRef<char> key, Value value, J_RW_TYPE type)
{
	FILE* file = fopen(FilePath_FileName, "r");
	//if file not exist,then create a new file
	if (!file) {
		rapidjson::Document writedoc;
		writedoc.SetObject();
		rapidjson::Document::AllocatorType& allocator = writedoc.GetAllocator();
		if (type == J_RW_TYPE::Int)
		{
			writedoc.AddMember(key, value.asInt(), allocator);
		}
		else if (type == J_RW_TYPE::String)
		{
			rapidjson::Value StringObject(rapidjson::kStringType);
			StringObject.SetString(value.asString().c_str(), value.asString().size(), allocator);
			writedoc.AddMember(key, StringObject, allocator);
		}
		else if (type == J_RW_TYPE::Float)
		{
			writedoc.AddMember(key, value.asFloat(), allocator);
		}
		else;
		rapidjson::StringBuffer buffer;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
		writedoc.Accept(writer);
		FILE *filetoW = fopen(FilePath_FileName, "wb");
		if (filetoW)
		{
			fputs(buffer.GetString(), filetoW);
			fclose(filetoW);
		}
	}
	// else open the exist file to change or add
	else
	{
		SSIZE_T size;
		unsigned char* ch = FileUtils::getInstance()->getFileData(FilePath_FileName, "r", &size);
		std::string data = std::string((const char*)ch, size);
		rapidjson::Document doc;                          ///< 创建一个Document对象 rapidJson的相关操作都在Document类中
		doc.Parse(data.c_str());               ///< 通过Parse方法将Json数据解析出来

		if (doc.HasParseError())
		{
			CCLOG("GetParseError%s\n", doc.GetParseError());
		}
		//if has the key,then change the value
		if (doc.HasMember(key)) {
			if (type == J_RW_TYPE::String)
			{
				doc[(const char *)key].SetString(value.asString().c_str(), value.asString().size(), doc.GetAllocator());
			}
			else if (type == J_RW_TYPE::Int)
			{
				doc[(const char *)key].SetInt(value.asInt());
			}
			else if (type == J_RW_TYPE::Float)
			{
				doc[(const char *)key].SetFloat(value.asFloat());
			}
			rapidjson::StringBuffer buffer;
			rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
			doc.Accept(writer);
			FILE *filetoW = fopen(FilePath_FileName, "wb");
			if (filetoW)
			{
				fputs(buffer.GetString(), filetoW);
				fclose(filetoW);
			}
		}
		//while there is no key in doc, then
		else
		{
			if (type == J_RW_TYPE::String)
			{
				rapidjson::Value StringObject(rapidjson::kStringType);
				StringObject.SetString(value.asString().c_str(), value.asString().size(), doc.GetAllocator());
				doc.AddMember(key, StringObject, doc.GetAllocator());
			}
			else if (type == J_RW_TYPE::Int)
			{
				rapidjson::Value IntObject(rapidjson::kObjectType);
				IntObject.SetInt(value.asInt());
				doc.AddMember(key, IntObject, doc.GetAllocator());
			}
			else if (type == J_RW_TYPE::Float)
			{
				rapidjson::Value FloatObject(rapidjson::kObjectType);
				FloatObject.SetFloat(value.asFloat());
				doc.AddMember(key, FloatObject, doc.GetAllocator());
			}
			rapidjson::StringBuffer buffer;
			rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
			doc.Accept(writer);
			FILE *filetoW = fopen(FilePath_FileName, "wb");
			if (filetoW)
			{
				fputs(buffer.GetString(), filetoW);
				fclose(filetoW);
			}
		}
	}
}