#pragma once

#include "PaiDivide.h"

namespace pro{

class PRO_EXPORTS InPaiDivide : PaiDivide
{
private:



public:

	InPaiDivide(void);
	~InPaiDivide(void);

	long getDirNum() const;
	int getOneLineNum() const;
	int getLineNum() const;
	int getFileNum() const;
	
	// ƒ‰ƒCƒ“Žæ“¾
	const char* getLine(long dir_num,int file_num,int line_num);

};

}
