#include "DiceDecode.h"
#include<Windows.h>

namespace pro{

void DiceDecode::send(){
	//std::cout<<(LPCWSTR)dir.pwd("submitExe.exe").c_str()<<std::endl;
	ShellExecute(NULL, "open", "submitExe.exe", NULL, NULL, SW_SHOW);
}

}