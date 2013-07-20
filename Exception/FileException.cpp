#include "FileException.h"

namespace pro{

FileException::FileException(void)
{
	name = "FileExpection";
}

FileException::FileException(const string& aMessage,
				const string& aFile,
				const string& aFunc)
			: Exception(aMessage,aFile,aFunc){
	name = "FileExpection";
}

FileException::FileException(const error_code aNum){
	setErrorCode(aNum);
	name = "FileExpection";
}

FileException::FileException(const error_code aNum,const string& aOpenFName){
	setErrorCode(aNum,aOpenFName);
	name = "FileExpection";
}

FileException::FileException(const error_code aNum,
				const string& aOpenFName,
				const string& aFile,
				const string& aFunc)
				:Exception("",aFile,aFunc){
	setErrorCode(aNum,aOpenFName);
	name = "FileExpection";
}

FileException::~FileException(void)
{
}

void FileException::setErrorCode(const error_code aCode,const string aOpenFName){
	code = aCode;
	switch(aCode){
	case OPEN:
		message = aOpenFName + "が開けませんでした。";
		break;
	case CLOSE:
		message = aOpenFName + "が閉じれませんでした。";
		break;
	case WRITE:
		message = aOpenFName + "が書き込めませんでした。";
		break;
	case READ:
		message = aOpenFName + "が読み込めませんでした。";
		break;
	default:
		message = "予期せぬエラー";
		break;
	}
}

void FileException::setErrorCode(const error_code aCode){
	setErrorCode(aCode,"ファイル");
}

FileException::error_code FileException::getErrorCode() const{
	return code;
}

}