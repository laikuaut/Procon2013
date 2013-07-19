#pragma once
#include "Exception.h"

namespace pro{

/**
 *  ファイル入出力用の例外処理
 */
class PRO_EXPORTS FileException :
	public Exception
{
public:

	typedef enum error_num{
		OPEN,CLOSE,WRITE,READ
	}error_num;

protected:
	
	error_num en;
	string openFileName;

private :
	
	void setErrorNum(error_num num);
	void setErrorNum(error_num num,string file_name);

public:
	
	FileException(void);
	FileException(const error_num aNum);
	FileException(const error_num aNum,string& aOpenFName);
	FileException(const error_num aNum,
				const string& aOpenFName,
				const string& aFile,
				const string& aFunc);
	FileException(const string& aMessage);
	FileException(const string& aMessage,
				const string& aFile,
				const string& aFunc);

	virtual ~FileException(void);

};

}