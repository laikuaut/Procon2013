#include "QuinaryDecode.h"

namespace pro{

QuinaryDecode::QuinaryDecode(void)
{
}


QuinaryDecode::~QuinaryDecode(void)
{
}

void QuinaryDecode::init(string name){
	fileRead(name);
	if(dices.size()<3) return;
	vector<short> max_dice;
	for(int j=0;j<3;j++){
		max_dice.push_back(dices[j]-1);
	}
	Quinary q;
	q.initq(max_dice);
	max=q.getDec();
	//std::cout<<max<<std::endl;
}

void QuinaryDecode::fileRead(string name){
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

void QuinaryDecode::output(){
	std::ofstream ofs;
	ofs.open("CodeDecode.txt");
	for(int i=3;i<dices.size();i+=3){
		vector<short> ss;
		Quinary s;
		if(i>=dices.size()) break;
		if(dices[i]==6){
			ofs << max << " " << std::flush;
			i-=2;
			continue;
		}
		for(int j=0;j<3;j++){
			if(i+j>=dices.size()) break;
			ss.push_back(dices[i+j]-1);
		}
		s.initq(ss);
		ofs << s.getDec() << " " << std::flush;
	}
	ofs.close();
	dices.clear();
}

}