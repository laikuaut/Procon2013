#include "SenaryEncode.h"

namespace pro{

SenaryEncode::SenaryEncode(void)
{
}

SenaryEncode::~SenaryEncode(void)
{
}

void SenaryEncode::init(string name){
	fileRead(name);
}

void SenaryEncode::fileRead(string name){
	std::ifstream ifs;
	ifs.open(name);
	int code;
	while(1){
		ifs>>code;
		if(ifs.eof()) break;
		codes.push_back(code);
	}
	ifs.close();
}

void SenaryEncode::output(){
	std::ofstream ofs;
	ofs.open("DiceEncode.txt");
	for(int i=0;i<codes.size();i++){
		Senary s;
		s.init(codes[i]);
		for(int j=0;j<3-s.size();j++){
			ofs << 1 << " " << std::flush;
		}
		for(int j=0;j<s.size();j++){
			ofs << s[j]+1 << " " << std::flush;
		}
	}
	ofs.close();
	codes.clear();
}

}