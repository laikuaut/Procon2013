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

FileException::FileException(const error_num aNum){
	setErrorNum(aNum);
	name = "FileExpection";
}

FileException::FileException(const error_num aNum,string& aOpenFName){
	setErrorNum(aNum,aOpenFName);
	name = "FileExpection";
}

FileException::FileException(const error_num aNum,
				const string& aOpenFName,
				const string& aFile,
				const string& aFunc)
				:Exception("",aFile,aFunc){
	setErrorNum(aNum,aOpenFName);
	name = "FileExpection";
}

FileException::~FileException(void)
{
}

void FileException::setErrorNum(const error_num aNum,const string aOpenFName){
	switch(aNum){
	case OPEN:
		message = aOpenFName + "���J���܂���ł����B";
		break;
	case CLOSE:
		message = aOpenFName + "������܂���ł����B";
		break;
	case WRITE:
		message = aOpenFName + "���������߂܂���ł����B";
		break;
	case READ:
		message = aOpenFName + "���ǂݍ��߂܂���ł����B";
		break;
	default:
		message = "�\�����ʃG���[";
		break;
	}
}

void FileException::setErrorNum(const error_num aNum){
	setErrorNum(aNum,"�t�@�C��");
}


}