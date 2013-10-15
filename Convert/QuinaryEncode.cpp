#include "QuinaryEncode.h"

namespace pro{

QuinaryEncode::QuinaryEncode(void)
{
}


QuinaryEncode::~QuinaryEncode(void)
{
}

void QuinaryEncode::init(string name){
	fileRead(name);
	stringMatching.init(name,true);
	stringMatching.matching(1);
	max_num=stringMatching.getMax1LengthNums();
	//std::cout<<max_num<<std::endl;
	setDice();
}

void QuinaryEncode::fileRead(string name){
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

void QuinaryEncode::setDice(){
	Quinary max;
	max.init(max_num);
	for(int j=0;j<3-max.size();j++){
		dices.push_back(1);
	}
	for(int j=0;j<max.size();j++){
		dices.push_back(max[j]+1);
	}
	for(int i=0;i<codes.size();i++){
		if(max_num==codes[i]){
			dices.push_back(6);
			continue;
		}
		Quinary s;
		s.init(codes[i]);
		for(int j=0;j<3-s.size();j++){
			dices.push_back(1);
		}
		for(int j=0;j<s.size();j++){
			dices.push_back(s[j]+1);
		}
	}
}

void QuinaryEncode::output(){
	std::ofstream ofs;
	ofs.open("DiceEncode.txt");
	for(int i=0;i<dices.size();i++){
		ofs<<dices[i]<<" "<<std::flush;	
	}
	ofs.close();
	codes.clear();
	dices.clear();
}


}