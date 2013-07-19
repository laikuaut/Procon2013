#pragma once

#include"Procon2013/Core/type_c.h"

#include<string>
#include<stdexcept>

namespace pro{


/**
 *  例外処理の自作基底クラス
 */
class PRO_EXPORTS Exception : public std::exception
{
protected:
	string name;
	string message;
	string fileName;
	string functionName;
public:
	Exception();
	Exception(const string& aMessage);
	Exception(const string& aMessage,
				const string& aFile,
				const string& aFunc);
	virtual ~Exception();

	virtual const char* what() const throw();
	virtual const char* getName() const throw();
	virtual const char* getFileName() const throw();
	virtual const char* getFuncName() const throw();
	virtual void showError() const throw();
};

}