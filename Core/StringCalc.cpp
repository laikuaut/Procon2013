#include "StringCalc.h"

namespace pro{

StringCalc::StringCalc(void)
{
}


StringCalc::~StringCalc(void)
{
}

void StringCalc::randomInit(){
	srand(time(NULL));
}

void StringCalc::randomStringOutput(int length,string filename){

	// ï∂éöóÒê∂ê¨
	char *c_str = new char[length+1];
	for(int i=0;i<length;i++){
		c_str[i] = rand()%STRNUM;
		if(c_str[i]<91-33)
			c_str[i]+=33;
		else
			c_str[i]+=37;
		std::cout << (int)c_str[i] << " " << std::flush;
	}
	c_str[length] = '\0';

	// ï∂éöóÒë|Ç´èoÇµ
	std::ofstream ofs;
	ofs.open(filename);
	ofs << c_str;
	ofs.close();

	delete[] c_str;
}

}