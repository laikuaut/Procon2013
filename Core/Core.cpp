#include"Core.h"

namespace pro{

std::string charToString(const char* str_c,int n){
	
	std::string str="";
	
	for(int i=0;i<n;i++){
		str += str_c[i];
		if(str_c[i]=='\0') break;
	}

	return str;
}

}