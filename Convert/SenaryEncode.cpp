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
	setDice();
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
//
//vector<int> SenaryEncode::runlength(){
//	int count=1;
//	int _count=1;
//	bool flag;
//	vector<int> dices;
//	int i;
//	for(i=1;dice[i-1+1] != 0;i++){
//		if(dice[i-1+1]==dice[i-1]){
//			count++; // ˜A‘±‚µ‚Ä‚¢‚é•¶Žš”
//		}else {
//			if(count>1){// ˜A‘±•¶Žš—ñ‚©‚ç”²‚¯‚é
//				flag = true;
//				_count=count;
//			}
//			count=1;// ‰Šú‰»
//		}
//		if(count==1){
//			if(flag){
//				if(_count>3){
//				// •ÏŠ·
//					dices.push_back(dice[i-1]);
//					dices.push_back(6);
//					Quinary q;
//					q.init(_count);
//					for(int j=0;j<q.size();j++){
//						dices.push_back(q[j]+1);
//					}
//					dices.push_back(6);
//					_count=1;
//				}else{
//				// ‚»‚Ì‚Ü‚Ü
//					for(int j=0;j<_count;j++)
//						dices.push_back(dice[i-1]);
//					_count=1;
//				}				
//			}else{
//				// ‚»‚Ì‚Ü‚Ü‘‚«‰Á‚¦‚é
//				dices.push_back(dice[i-1]);
//			}
//		}else{
//			// ‘‚«ž‚Ü‚È‚¢
//		}
//	}
//	// ÅŒã‚Ì•¶Žš
//	dices.push_back(dice[i-1]);
//	return dices;
//}

void SenaryEncode::setDice(){
	for(int i=0;i<codes.size();i++){
		Senary s;
		s.init(codes[i]);
		for(int j=0;j<3-s.size();j++){
			dices.push_back(1);
		}
		for(int j=0;j<s.size();j++){
			dices.push_back(s[j]+1);
		}
	}
}

void SenaryEncode::output(){
	std::ofstream ofs;
	ofs.open("DiceEncode.txt");
	for(int i=0;i<dices.size();i++){
		ofs<<dices[i]<<" "<<std::flush;	
	}
	//for(int i=0;i<codes.size();i++){
	//	Senary s;
	//	s.init(codes[i]);
	//	for(int j=0;j<3-s.size();j++){
	//		ofs << 1 << " " << std::flush;
	//	}
	//	for(int j=0;j<s.size();j++){
	//		ofs << s[j]+1 << " " << std::flush;
	//	}
	//}
	ofs.close();
	codes.clear();
	dices.clear();
}

}