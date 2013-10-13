#include "SenaryDecode.h"

namespace pro{

SenaryDecode::SenaryDecode(void)
{
}


SenaryDecode::~SenaryDecode(void)
{
}

void SenaryDecode::init(string name){
	fileRead(name);
}

void SenaryDecode::fileRead(string name){
	std::ifstream ifs;
	ifs.open(name);
	int code;
	while(1){
		ifs>>code;
		if(ifs.eof()) break;
		dices.push_back(code);
	}
	ifs.close();
}

void SenaryDecode::output(){
	std::ofstream ofs;
	ofs.open("CodeDecode.txt");
	for(int i=0;i<dices.size();i+=3){
		vector<short> ss;
		Senary s;
		for(int j=0;j<3;j++){
			if(i+j>=dices.size()) break;
			ss.push_back(dices[i+j]-1);
		}
		s.inits(ss);
		ofs << s.getDec() << " " << std::flush;
	}
	ofs.close();
	dices.clear();
}

}